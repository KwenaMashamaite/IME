#include "doctest.h"
#include "IME/event/EventEmitter.h"

/*
 * @note In the following tests, event listener, event handler and callback
 * function or just callback are synonymous and interchangeable
 */

/////////////////////////////////////////////////////////////////
/// Event listener registration tests
/////////////////////////////////////////////////////////////////

using IME::EventEmitter;
using IME::Callback;

TEST_CASE("Only the first event listener has an identification number of one"){
    auto eventEmitter = EventEmitter();
    CHECK_EQ(eventEmitter.addEventListener("event", Callback<>([]{})), 1);
    CHECK_NE(eventEmitter.addEventListener("event", Callback<>([]{})), 1);
    auto eventEmitter2 = EventEmitter();
    CHECK_NE(eventEmitter2.addEventListener("event", Callback<>([]{})), 1);
}

TEST_CASE("Event listener counter increases by one when an event listener is added") {
    auto eventEmitter = EventEmitter();
    auto handlerOneId = eventEmitter.addEventListener("event", Callback<>([]{}));
    auto handlerTwoId = eventEmitter.addEventListener("event", Callback<>([]{}));
    auto handlerThreeId = eventEmitter.addEventListener("event", Callback<>([]{}));
    auto handlerFourId = eventEmitter.addEventListener("event", Callback<>([]{}));
    CHECK_EQ(handlerTwoId, handlerOneId + 1);
    CHECK_EQ(handlerThreeId, handlerTwoId + 1);
    CHECK_EQ(handlerFourId, handlerThreeId + 1);
}

TEST_CASE("Issued identification numbers are valid"){
    auto eventEmitter = EventEmitter();
    auto handlerId = eventEmitter.addEventListener("event", Callback<>([]{}));
}

TEST_CASE("Adding an event listener to a non-existent event creates that event"){
    auto eventEmitter = EventEmitter();
    CHECK_FALSE(eventEmitter.hasEvent("event"));
    eventEmitter.addEventListener("event", Callback<>([]{}));
    CHECK(eventEmitter.hasEvent("event"));
}

TEST_CASE("Adding a listern to an event increases that events listener count by one"){
    auto eventEmitter = EventEmitter();
    eventEmitter.addEventListener("event", Callback<>([]{}));
    eventEmitter.addEventListener("event", Callback<>([]{}));
    eventEmitter.addEventListener("event", Callback<>([]{}));
    eventEmitter.addEventListener("event", Callback<>([]{}));
    eventEmitter.addEventListener("event", Callback<>([]{}));
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("event"), 5);
}

TEST_CASE("The first event listeners of different events have different identification numbers"){
    auto eventEmitter = EventEmitter();
    auto eventListOneId = eventEmitter.addEventListener("event", Callback<>([]{}));
    auto eventListTwoId = eventEmitter.addEventListener("event1", Callback<>([]{}));
    auto eventListThreeId = eventEmitter.addEventListener("event2", Callback<>([]{}));
    CHECK_NE(eventListOneId, eventListTwoId);
    CHECK_NE(eventListOneId, eventListThreeId);
    CHECK_NE(eventListTwoId, eventListThreeId);
}

TEST_CASE("The same callback function is treated as a unique handler when added to an event multiple times"){
    auto eventEmitter = EventEmitter();
    auto doSomething = [](){/*Code that does something*/};
    CHECK_NE(eventEmitter.addEventListener("somethingChanged", Callback<>(doSomething)),
            eventEmitter.addEventListener("somethingChanged",Callback<>(doSomething)));
}

TEST_CASE("Multiple listeners can be registered with the same event"){
    struct Button : public EventEmitter{};
    auto button = Button();
    auto listenerOneId = button.addEventListener("click", Callback<int, int>([](int, int) {}));
    auto listenerTwoId = button.addEventListener("click", Callback<int, int>([](int, int) {}));
    auto listenerThreeId = button.addEventListener("click", Callback<int, int>([](int, int) {}));
    CHECK_EQ(listenerTwoId, listenerOneId + 1);
    CHECK_EQ(listenerThreeId, listenerTwoId + 1);
}

/////////////////////////////////////////////////////////////////
/// Event publishing tests
/////////////////////////////////////////////////////////////////

TEST_CASE("Raising an event executes a callback function registered to that event") {
    auto eventEmitter = EventEmitter();
    auto testString = std::string("callback function not executed");
    eventEmitter.addEventListener("test", Callback<>([&testString] {
        testString = "callback function executed";
    }));
    eventEmitter.emit("test"); //Raising event
    CHECK_EQ(testString, "callback function executed");
}

TEST_CASE("Raising an event executes all listeners of that event"){
    auto eventEmitter = EventEmitter();
    auto counter = 0u;
    eventEmitter.addEventListener("increaseCounterButtonPressed", Callback<>([&counter]() { counter += 1; }));
    eventEmitter.addEventListener("increaseCounterButtonPressed", Callback<>([&counter]() { counter += 5; }));
    eventEmitter.addEventListener("increaseCounterButtonPressed", Callback<>([&counter]() { counter += 4; }));
    eventEmitter.addEventListener("increaseCounterButtonPressed", Callback<>([&counter]() { counter += 10; }));
    eventEmitter.emit("increaseCounterButtonPressed");
    CHECK_EQ(counter, 20u);
}

TEST_CASE("A callback function is not executed if the event is not raised"){
    auto eventEmitter = EventEmitter();
    auto testString = std::string("callback function not executed");
    eventEmitter.addEventListener("test", Callback<>([&testString] {
        testString = "callback function executed";
    }));
    CHECK_EQ(testString, "callback function not executed");
}

//What to take away from this test is that argument types must match Parameter types exactly
TEST_CASE("Raising an event with different parameter types to that of the callback does not execute it"){
    auto eventEmitter = EventEmitter();
    auto testString = std::string("callback function not executed");
    eventEmitter.addEventListener("click", Callback<int, int>([&testString](int x, int y) {
        testString = "callback function executed";
    }));
    eventEmitter.emit("click", 25.0f, 25.0f); //callback expecting int, float provided
    CHECK_EQ(testString, "callback function not executed");
    eventEmitter.emit("click", 25u, 25u); //callback expecting int, unsigned int provided
    CHECK_EQ(testString, "callback function not executed");
    eventEmitter.emit("click", 25, 25); //callback expecting int, int provided
    CHECK_EQ(testString, "callback function executed");
}

TEST_CASE("Event listeners receive correct arguments upon notification"){
    auto eventEmitter = EventEmitter();
    auto recivedArguments = std::make_pair(-1, -1);
    eventEmitter.addEventListener("positionChanged", Callback<int, int>([&](int x, int y) {
        recivedArguments.first = x;
        recivedArguments.second = y;
    }));
    eventEmitter.emit("positionChanged", 127, 25);
    CHECK_EQ(recivedArguments.first, 127);
    CHECK_EQ(recivedArguments.second, 25);
}

TEST_CASE("Both the 'addEventListener' and the 'on' function register event listeners to events"){
    struct Mouse : public EventEmitter{
        void click(int x, int y){
            emit("click", x, y);
        }
    };
    auto mouse = Mouse();
    auto mouseClickCoordinates = std::make_pair(-1, -1);
    bool isMouseClicked = false;
    mouse.addEventListener("click", Callback<int, int>([&](int x, int y) {
        mouseClickCoordinates = {x, y};
    }));
    mouse.on("click", Callback<int, int>([&isMouseClicked](int x, int y){
        isMouseClicked = true;
    }));

    mouse.click(50, 100);
    CHECK_EQ(mouseClickCoordinates.first, 50);
    CHECK_EQ(mouseClickCoordinates.second, 100);
    CHECK(isMouseClicked);
}

TEST_CASE("Event listeners can be invoked multiple times"){
    auto eventEmitter = EventEmitter();
    auto counter = 0u;
    auto increaseCounterByOne = [&counter]{++counter;};
    eventEmitter.addEventListener("increaseCounterButtonClicked", Callback<>(increaseCounterByOne));
    eventEmitter.emit("increaseCounterButtonClicked");
    eventEmitter.emit("increaseCounterButtonClicked");
    eventEmitter.emit("increaseCounterButtonClicked");
    eventEmitter.emit("increaseCounterButtonClicked");
    eventEmitter.emit("increaseCounterButtonClicked");
    CHECK_EQ(counter, 5u);
}

TEST_CASE("A once event listener is removed from an event after it executes"){
    auto eventEmitter = EventEmitter();
    auto counter = 0u;
    auto increaseCounterByOne = [&counter]{++counter;};
    eventEmitter.addOnceEventListener("increaseCounterButtonClicked", Callback<>(increaseCounterByOne));
    eventEmitter.emit("increaseCounterButtonClicked");
    eventEmitter.emit("increaseCounterButtonClicked");
    eventEmitter.emit("increaseCounterButtonClicked");
    CHECK_EQ(counter, 1u);
}

/////////////////////////////////////////////////////////////////
/// Event listener removal tests
/////////////////////////////////////////////////////////////////

TEST_CASE("A callback function can be removed from an event"){
    auto eventEmitter = EventEmitter();
    auto handlerId = eventEmitter.addEventListener("click", Callback<>([] {}));
    CHECK(eventEmitter.removeEventListener("click", handlerId));
}

TEST_CASE("An event listener that is removed from an event does not execute"){
    auto eventEmitter = EventEmitter();
    auto testString = std::string("callback function not executed");
    auto handlerId = eventEmitter.addEventListener("test", Callback<>([&testString] {
        testString = "callback function executed";
    }));
    eventEmitter.emit("test");
    CHECK_EQ(testString, "callback function executed");
    eventEmitter.removeEventListener("test", handlerId);
    testString = "";
    eventEmitter.emit("test");
    CHECK_NE(testString, "callback function executed");
}

TEST_CASE("Removing a non-existent handler from an event returns false"){
    auto eventEmitter = EventEmitter();
    eventEmitter.addEventListener("test", Callback<>([] {}));
    auto invalidHandlerId = -99;
    CHECK_FALSE(eventEmitter.removeEventListener("test", invalidHandlerId));
}
