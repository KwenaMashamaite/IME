#include "doctest.h"
#include "../game-source-code/event/EventEmitter.h"

/*
 * @note In the following tests, event listener, event handler and callback
 * function or just callback are synonymous and interchangeable
 */

/////////////////////////////////////////////////////////////////
/// Registering event listeners to events tests
/////////////////////////////////////////////////////////////////

//This test must always be the first test as the handler id counter belongs to the class
//not the object
TEST_CASE("The first event listener has an identification number of one (1)"){
    auto eventEmitter = EventEmitter();
    auto clickEventHandlerId = eventEmitter.addListener("click", Callback<>([](){}));
    CHECK_EQ(clickEventHandlerId, 1);
}

TEST_CASE("The first event listeners of different events have different identification numbers"){
    auto eventEmitter = EventEmitter();
    auto clickListenerId = eventEmitter.addListener("click", Callback<int, int>([](int xCoord, int yCoord){}));
    auto nameChangeListenerId = eventEmitter.addListener("nameChanged", Callback<std::string>([](std::string newName){}));
    CHECK_NE(clickListenerId, nameChangeListenerId);
}

TEST_CASE("The same callback function is treated as a unique handler when added to an event multiple times"){
    auto eventEmitter = EventEmitter();
    auto doSomething = [](){/*Code that does something*/};
    CHECK_NE(eventEmitter.addListener("somethingChanged", Callback<>(doSomething)),
             eventEmitter.addListener("somethingChanged", Callback<>(doSomething)));
}

TEST_CASE("Multiple listeners can be registered with the same event"){
    struct Button : public EventEmitter{};
    auto button = Button();
    auto listenerOneId = button.addListener("click", Callback<int, int>([](int, int){}));
    auto listenerTwoId = button.addListener("click", Callback<int, int>([](int, int){}));
    auto listenerThreeId = button.addListener("click", Callback<int, int>([](int, int){}));
    CHECK_EQ(listenerTwoId, listenerOneId + 1);
    CHECK_EQ(listenerThreeId, listenerTwoId + 1);
}

/////////////////////////////////////////////////////////////////
/// Publishing events tests
/////////////////////////////////////////////////////////////////

TEST_CASE("Raising an event executes a callback function registered to that event") {
    auto eventEmitter = EventEmitter();
    auto testString = std::string("callback function not executed");
    eventEmitter.addListener("test", Callback<>([&testString]{
        testString = "callback function executed";
    }));
    eventEmitter.emit("test"); //Raising event
    CHECK_EQ(testString, "callback function executed");
}

TEST_CASE("Raising an event executes all listeners of that event"){
    auto eventEmitter = EventEmitter();
    auto counter = 0u;
    eventEmitter.addListener("increaseCounterButtonPressed", Callback<>([&counter](){counter += 1;}));
    eventEmitter.addListener("increaseCounterButtonPressed", Callback<>([&counter](){counter += 5;}));
    eventEmitter.addListener("increaseCounterButtonPressed", Callback<>([&counter](){counter += 4;}));
    eventEmitter.addListener("increaseCounterButtonPressed", Callback<>([&counter](){counter += 10;}));
    eventEmitter.emit("increaseCounterButtonPressed");
    CHECK_EQ(counter, 20u);
}

TEST_CASE("A callback function is not executed if the event is not raised"){
    auto eventEmitter = EventEmitter();
    auto testString = std::string("callback function not executed");
    eventEmitter.addListener("test", Callback<>([&testString]{
        testString = "callback function executed";
    }));
    CHECK_EQ(testString, "callback function not executed");
}

//What to take away from this test is that argument types must match Parameter types exactly
TEST_CASE("Raising an event with different parameter types to that of the callback does not execute it"){
    auto eventEmitter = EventEmitter();
    auto testString = std::string("callback function not executed");
    eventEmitter.addListener("click", Callback<int, int>([&testString](int x, int y){
        testString = "callback function executed";
    }));
    eventEmitter.emit("click", 25.0f, 25.0f); //callback expecting int, float provided
    CHECK_EQ(testString, "callback function not executed");
    eventEmitter.emit("click", 25u, 25u); //callback expected int, unsigned int provided
    CHECK_EQ(testString, "callback function not executed");
    eventEmitter.emit("click", 25, 25); //callback expected int, int provided
    CHECK_EQ(testString, "callback function executed");
}

TEST_CASE("Event listeners receive correct arguments upon notification"){
    auto eventEmitter = EventEmitter();
    auto recivedArguments = std::make_pair(-1, -1);
    eventEmitter.addListener("positionChanged", Callback<int, int>([&](int x, int y){
        recivedArguments.first = x;
        recivedArguments.second = y;
    }));
    eventEmitter.emit("positionChanged", 127, 25);
    CHECK_EQ(recivedArguments.first, 127);
    CHECK_EQ(recivedArguments.second, 25);
}

TEST_CASE("Both the 'addListener' and the 'on' function register event listeners to events"){
    struct Mouse : public EventEmitter{
        void click(int x, int y){
            emit("click", x, y);
        }
    };
    auto mouse = Mouse();
    auto mouseClickCoordinates = std::make_pair(-1, -1);
    bool isMouseClicked = false;
    mouse.addListener("click", Callback<int, int>([&](int x, int y){
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
    eventEmitter.addListener("increaseCounterButtonClicked", Callback<>(increaseCounterByOne));
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
    eventEmitter.addOnceListener("increaseCounterButtonClicked", Callback<>(increaseCounterByOne));
    eventEmitter.emit("increaseCounterButtonClicked");
    eventEmitter.emit("increaseCounterButtonClicked");
    eventEmitter.emit("increaseCounterButtonClicked");
    CHECK_EQ(counter, 1u);
}

/////////////////////////////////////////////////////////////////
/// Removing event listeners from events tests
/////////////////////////////////////////////////////////////////

TEST_CASE("A callback function can be removed from an event"){
    auto eventEmitter = EventEmitter();
    auto handlerId = eventEmitter.addListener("click", Callback<>([]{}));
    CHECK(eventEmitter.removeListener("click", handlerId));
}

TEST_CASE("An event listener that is removed from an event does not execute"){
    auto eventEmitter = EventEmitter();
    auto testString = std::string("callback function not executed");
    auto handlerId = eventEmitter.addListener("test", Callback<>([&testString]{
        testString = "callback function executed";
    }));
    eventEmitter.emit("test");
    CHECK_EQ(testString, "callback function executed");
    eventEmitter.removeListener("test", handlerId);
    testString = "";
    eventEmitter.emit("test");
    CHECK_NE(testString, "callback function executed");
}

TEST_CASE("Removing a non-existent handler from an event returns false"){
    auto eventEmitter = EventEmitter();
    eventEmitter.addListener("test", Callback<>([]{}));
    auto invalidHandlerId = -99;
    CHECK_FALSE(eventEmitter.removeListener("test", invalidHandlerId));
}

