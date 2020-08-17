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

TEST_CASE("Adding an event listener to a non-existent event creates that event"){
    auto eventEmitter = EventEmitter();
    CHECK_FALSE(eventEmitter.hasEvent("event"));
    eventEmitter.addEventListener("event", Callback<>([]{}));
    CHECK(eventEmitter.hasEvent("event"));
}

TEST_CASE("Creating duplicate events ony creates one event") {
    auto eventEmitter = EventEmitter();
    eventEmitter.addEventListener("event", Callback<>([]{}));
    eventEmitter.addEventListener("event", Callback<>([]{}));
    eventEmitter.addEventListener("event", Callback<>([]{}));
    CHECK_EQ(eventEmitter.getNumberOfEvents(), 1);
}

TEST_CASE("Multiple event listeners can be registered with the same event"){
    auto eventEmitter = EventEmitter();
    eventEmitter.addEventListener("event", Callback<>([]{}));
    eventEmitter.addEventListener("event", Callback<int>([](int){}));
    eventEmitter.addEventListener("event", Callback<int, char>([](int, char){}));
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("event"), 3);
}

TEST_CASE("An event does not exist unless created") {
    auto eventEmitterOne = EventEmitter();
    eventEmitterOne.addEventListener("event", Callback<>([]{}));
    auto eventEmitterTwo = EventEmitter();
    CHECK_FALSE(eventEmitterTwo.hasEvent("event"));
}

TEST_CASE("Events with the same name can be created in different instances") {
    auto eventEmitterOne = EventEmitter();
    auto eventEmitterTwo = EventEmitter();
    eventEmitterOne.addEventListener("event", Callback<>([]{}));
    eventEmitterTwo.addEventListener("event", Callback<>([]{}));
    CHECK(eventEmitterOne.hasEvent("event"));
    CHECK(eventEmitterTwo.hasEvent("event"));
}

TEST_CASE("Issued identification numbers are valid"){
    auto eventEmitter = EventEmitter();
    auto handlerId = eventEmitter.addEventListener("event", Callback<>([]{}));
    CHECK(eventEmitter.hasEventListener("event", handlerId).first);
}

TEST_CASE("Event listener counter increases by one when a listener is added to any event") {
    auto eventEmitter = EventEmitter();
    auto handlerOneId = eventEmitter.addEventListener("eventOne", Callback<>([]{}));
    auto handlerTwoId = eventEmitter.addEventListener("eventTwo", Callback<>([]{}));
    auto handlerThreeId = eventEmitter.addEventListener("eventThree", Callback<>([]{}));
    auto handlerFourId = eventEmitter.addEventListener("eventFour", Callback<>([]{}));
    CHECK_EQ(handlerTwoId, handlerOneId + 1);
    CHECK_EQ(handlerThreeId, handlerTwoId + 1);
    CHECK_EQ(handlerFourId, handlerThreeId + 1);
}

TEST_CASE("An event is created with a single event listener") {
    auto eventEmitter = EventEmitter();
    eventEmitter.addEventListener("event", Callback<>([]{}));
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("event"), 1);
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

TEST_CASE("The same callback function is treated as a unique event listener"){
    auto doSomething = std::function<void()>([](){});
    auto eventEmitter = EventEmitter();
    auto handlerOneId = eventEmitter.addEventListener("event", doSomething);
    auto handlerTwoId = eventEmitter.addEventListener("event", doSomething);
    CHECK(handlerOneId != handlerTwoId);
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("event"), 2);
}

TEST_CASE("The same callback function can be added to different events") {
    auto doSomething = std::function<void()>([](){});
    auto eventEmitter = EventEmitter();
    eventEmitter.addEventListener("event", doSomething);
    eventEmitter.addEventListener("eventTwo", doSomething);
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("event"), 1);
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("eventTwo"), 1);
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
    eventEmitter.addEventListener("increaseCounter", Callback<>([&counter]() { counter += 1; }));
    eventEmitter.addEventListener("increaseCounter", Callback<>([&counter]() { counter += 5; }));
    eventEmitter.addEventListener("increaseCounter", Callback<>([&counter]() { counter += 4; }));
    eventEmitter.addEventListener("increaseCounter", Callback<>([&counter]() { counter += 10; }));
    eventEmitter.emit("increaseCounter");
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
    mouse.addEventListener("click", Callback<int, int>([&](int x, int y) {
        mouseClickCoordinates = {x, y};
    }));

    bool isMouseClicked = false;
    mouse.on("click", Callback<int, int>([&isMouseClicked](int x, int y){
        isMouseClicked = true;
    }));

    mouse.click(50, 100);
    CHECK_EQ(mouseClickCoordinates.first, 50);
    CHECK_EQ(mouseClickCoordinates.second, 100);
    CHECK(isMouseClicked);
}

TEST_CASE("An event listener can be invoked multiple times"){
    auto eventEmitter = EventEmitter();
    auto numOfTimeCallbackInvoked = 0u;
    auto increaseCounterByOne = [&numOfTimeCallbackInvoked]{++numOfTimeCallbackInvoked;};
    eventEmitter.addEventListener("event", Callback<>(increaseCounterByOne));
    eventEmitter.emit("event");
    eventEmitter.emit("event");
    eventEmitter.emit("event");
    CHECK_EQ(numOfTimeCallbackInvoked, 3u);
}

TEST_CASE("A once event listener is invoked only once"){
    auto eventEmitter = EventEmitter();
    auto numOfTimeCallbackInvoked = 0u;
    auto increaseCounterByOne = [&numOfTimeCallbackInvoked]{++numOfTimeCallbackInvoked;};
    eventEmitter.addOnceEventListener("event", Callback<>(increaseCounterByOne));
    eventEmitter.emit("event");
    eventEmitter.emit("event");
    eventEmitter.emit("event");
    CHECK_EQ(numOfTimeCallbackInvoked, 1);
}

TEST_CASE("A once event listener is removed from the event list after invocation") {
    auto eventEmitter = EventEmitter();
    auto onceHandlerId = eventEmitter.addOnceEventListener("once", Callback<>([]{}));
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("once"), 1);
    eventEmitter.emit("once");
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("once"), 0);
    CHECK_FALSE(eventEmitter.hasEventListener("once", onceHandlerId).first);
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
