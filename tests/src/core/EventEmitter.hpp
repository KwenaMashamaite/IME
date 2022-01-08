////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "doctest.h"
#include "IME/core/event/EventEmitter.h"

/*
 * @note In the following tests, event listener, event handler and callback
 * function or just callback are synonymous and interchangeable
 */

/////////////////////////////////////////////////////////////////
/// Event listener registration tests
/////////////////////////////////////////////////////////////////

TEST_CASE("The event emitter has no events by default") {
    auto eventEmitter = ime::EventEmitter();
    CHECK_EQ(eventEmitter.getNumberOfEvents(), 0);
}

TEST_CASE("Only the first ever event listener has an identification number of one"){
    auto eventEmitter = ime::EventEmitter();
    CHECK_EQ(eventEmitter.addEventListener("event", ime::Callback<>([]{})), 1);
    CHECK_NE(eventEmitter.addEventListener("event", ime::Callback<>([]{})), 1);
    auto eventEmitter2 = ime::EventEmitter();
    CHECK_NE(eventEmitter2.addEventListener("event", ime::Callback<>([]{})), 1);
}

TEST_CASE("Adding an event listener to a non-existent event creates that event"){
    auto eventEmitter = ime::EventEmitter();
    CHECK_FALSE(eventEmitter.hasEvent("event"));
    eventEmitter.addEventListener("event", ime::Callback<>([]{}));
    CHECK(eventEmitter.hasEvent("event"));
}

TEST_CASE("Creating duplicate events ony creates one event") {
    auto eventEmitter = ime::EventEmitter();
    eventEmitter.addEventListener("event", ime::Callback<>([]{}));
    eventEmitter.addEventListener("event", ime::Callback<>([]{}));
    eventEmitter.addEventListener("event", ime::Callback<>([]{}));
    CHECK_EQ(eventEmitter.getNumberOfEvents(), 1);
}

TEST_CASE("Multiple event listeners can be registered with the same event"){
    auto eventEmitter = ime::EventEmitter();
    eventEmitter.addEventListener("event", ime::Callback<>([]{}));
    eventEmitter.addEventListener("event", ime::Callback<int>([](int){}));
    eventEmitter.addEventListener("event", ime::Callback<int, char>([](int, char){}));
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("event"), 3);
}

TEST_CASE("An event does not exist unless its created") {
    auto eventEmitterOne = ime::EventEmitter();
    eventEmitterOne.addEventListener("event", ime::Callback<>([]{}));
    auto eventEmitterTwo = ime::EventEmitter();
    CHECK_FALSE(eventEmitterTwo.hasEvent("event"));
}

TEST_CASE("Events with the same name can be created in different instances") {
    auto eventEmitterOne = ime::EventEmitter();
    auto eventEmitterTwo = ime::EventEmitter();
    eventEmitterOne.addEventListener("event", ime::Callback<>([]{}));
    eventEmitterTwo.addEventListener("event", ime::Callback<>([]{}));
    CHECK(eventEmitterOne.hasEvent("event"));
    CHECK(eventEmitterTwo.hasEvent("event"));
}

TEST_CASE("Issued identification numbers are valid"){
    auto eventEmitter = ime::EventEmitter();
    auto handlerId = eventEmitter.addEventListener("event", ime::Callback<>([]{}));
    CHECK(eventEmitter.hasEventListener("event", handlerId));
}

TEST_CASE("Event listener counter increases by one when a listener is added to any event") {
    auto eventEmitter = ime::EventEmitter();
    auto handlerOneId = eventEmitter.addEventListener("eventOne", ime::Callback<>([]{}));
    auto handlerTwoId = eventEmitter.addEventListener("eventTwo", ime::Callback<>([]{}));
    auto handlerThreeId = eventEmitter.addEventListener("eventThree", ime::Callback<>([]{}));
    auto handlerFourId = eventEmitter.addEventListener("eventFour", ime::Callback<>([]{}));
    CHECK_EQ(handlerTwoId, handlerOneId + 1);
    CHECK_EQ(handlerThreeId, handlerTwoId + 1);
    CHECK_EQ(handlerFourId, handlerThreeId + 1);
}

TEST_CASE("An event is created with a single event listener") {
    auto eventEmitter = ime::EventEmitter();
    eventEmitter.addEventListener("event", ime::Callback<>([]{}));
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("event"), 1);
}

TEST_CASE("The first event listeners of different events have different identification numbers"){
    auto eventEmitter = ime::EventEmitter();
    auto eventListOneId = eventEmitter.addEventListener("event", ime::Callback<>([]{}));
    auto eventListTwoId = eventEmitter.addEventListener("event1", ime::Callback<>([]{}));
    auto eventListThreeId = eventEmitter.addEventListener("event2", ime::Callback<>([]{}));
    CHECK_NE(eventListOneId, eventListTwoId);
    CHECK_NE(eventListOneId, eventListThreeId);
    CHECK_NE(eventListTwoId, eventListThreeId);
}

TEST_CASE("The same callback function is treated as a unique event listener"){
    auto doSomething = std::function<void()>([](){});
    auto eventEmitter = ime::EventEmitter();
    auto handlerOneId = eventEmitter.addEventListener("event", doSomething);
    auto handlerTwoId = eventEmitter.addEventListener("event", doSomething);
    CHECK(handlerOneId != handlerTwoId);
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("event"), 2);
}

TEST_CASE("The same callback function can be added to different events") {
    auto doSomething = std::function<void()>([](){});
    auto eventEmitter = ime::EventEmitter();
    eventEmitter.addEventListener("event", doSomething);
    eventEmitter.addEventListener("eventTwo", doSomething);
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("event"), 1);
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("eventTwo"), 1);
}

/////////////////////////////////////////////////////////////////
/// Event publishing tests
/////////////////////////////////////////////////////////////////

TEST_CASE("Raising an event executes a callback function registered to that event") {
    auto eventEmitter = ime::EventEmitter();
    auto testString = std::string("callback function not executed");
    eventEmitter.addEventListener("test", ime::Callback<>([&testString] {
        testString = "callback function executed";
    }));
    eventEmitter.emit("test"); //Raising event
    CHECK_EQ(testString, "callback function executed");
}

TEST_CASE("Raising an event executes all event listeners registered to that event"){
    auto eventEmitter = ime::EventEmitter();
    auto counter = 0u;
    eventEmitter.addEventListener("increaseCounter", ime::Callback<>([&counter]() { counter += 1; }));
    eventEmitter.addEventListener("increaseCounter", ime::Callback<>([&counter]() { counter += 5; }));
    eventEmitter.addEventListener("increaseCounter", ime::Callback<>([&counter]() { counter += 4; }));
    eventEmitter.addEventListener("increaseCounter", ime::Callback<>([&counter]() { counter += 10; }));
    eventEmitter.emit("increaseCounter");
    CHECK_EQ(counter, 20u);
}

TEST_CASE("An event listener is not notified when sn event is not raised"){
    auto eventEmitter = ime::EventEmitter();
    auto testString = std::string("callback function not executed");
    eventEmitter.addEventListener("test", ime::Callback<>([&testString] {
        testString = "callback function executed";
    }));
    CHECK_EQ(testString, "callback function not executed");
}

TEST_CASE("Raising an event with different parameter types to that of the callback does not execute it"){
    auto eventEmitter = ime::EventEmitter();
    auto testString = std::string("callback function not executed");
    eventEmitter.addEventListener("click", ime::Callback<int, int>([&testString](int x, int y) {
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
    auto eventEmitter = ime::EventEmitter();
    auto receivedArguments = std::make_pair(-1, -1);
    eventEmitter.addEventListener("test", ime::Callback<int, int>([&](int x, int y) {
        receivedArguments.first = x;
        receivedArguments.second = y;
    }));
    eventEmitter.emit("test", 127, 25);
    CHECK_EQ(receivedArguments.first, 127);
    CHECK_EQ(receivedArguments.second, 25);
}

TEST_CASE("Both the 'addEventListener' and the 'on' function register event listeners to events"){
    auto eventEmitter = ime::EventEmitter();
    auto testString = std::string("callback function not executed");

    eventEmitter.addEventListener("testOne", ime::Callback<>([&testString] {
        testString = "Executed callback function added via addEventListener()";
    }));
    
    eventEmitter.on("testTwo", ime::Callback<>([&testString] {
        testString = "Executed callback function added via on()";
    }));

    eventEmitter.emit("testOne");
    CHECK_EQ(testString, "Executed callback function added via addEventListener()");
    eventEmitter.emit("testTwo");
    CHECK_EQ(testString, "Executed callback function added via on()");
}

TEST_CASE("An event can be published multiple times"){
    auto eventEmitter = ime::EventEmitter();
    auto numOfTimeCallbackInvoked = 0u;
    
    eventEmitter.addEventListener("event", ime::Callback<>([&numOfTimeCallbackInvoked] {
        ++numOfTimeCallbackInvoked;
    }));

    eventEmitter.emit("event");
    eventEmitter.emit("event");
    eventEmitter.emit("event");
    CHECK_EQ(numOfTimeCallbackInvoked, 3u);
}

TEST_CASE("A once event listener is invoked only once"){
    auto eventEmitter = ime::EventEmitter();
    auto numOfTimeCallbackInvoked = 0u;
    auto increaseCounterByOne = [&numOfTimeCallbackInvoked]{
        ++numOfTimeCallbackInvoked;
    };
    eventEmitter.addOnceEventListener("event", ime::Callback<>(increaseCounterByOne));
    eventEmitter.emit("event");
    eventEmitter.emit("event");
    eventEmitter.emit("event");
    CHECK_EQ(numOfTimeCallbackInvoked, 1);
}

TEST_CASE("A once event listener is removed from the event list after invocation") {
    auto eventEmitter = ime::EventEmitter();
    auto onceHandlerId = eventEmitter.addOnceEventListener("once", ime::Callback<>([]{}));
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("once"), 1);
    eventEmitter.emit("once");
    CHECK_EQ(eventEmitter.getNumOfEventListenersFor("once"), 0);
    CHECK_FALSE(eventEmitter.hasEventListener("once", onceHandlerId));
}

/////////////////////////////////////////////////////////////////
/// Event listener removal tests
/////////////////////////////////////////////////////////////////

TEST_CASE("An event listener can be removed from an event"){
    auto eventEmitter = ime::EventEmitter();
    auto handlerId = eventEmitter.addEventListener("event", ime::Callback<>([]{}));
    CHECK(eventEmitter.hasEventListener("event", handlerId));
    CHECK(eventEmitter.removeEventListener("event", handlerId));
    CHECK_FALSE(eventEmitter.hasEventListener("event", handlerId));
}

TEST_CASE("An event listener that is removed from an event does not execute"){
    auto eventEmitter = ime::EventEmitter();
    auto testString = std::string("");
    auto handlerId = eventEmitter.addEventListener("test", ime::Callback<>([&testString] {
        testString = "callback function executed";
    }));
    eventEmitter.emit("test");
    CHECK_EQ(testString, "callback function executed");
    eventEmitter.removeEventListener("test", handlerId);
    testString = "";
    eventEmitter.emit("test");
    CHECK_NE(testString, "callback function executed");
}

TEST_CASE("Removing a non-existent event listener from an event returns false"){
    auto eventEmitter = ime::EventEmitter();
    CHECK_FALSE(eventEmitter.removeEventListener("test", -1));
}

TEST_CASE("Removing an existent event listener from an "){
    auto eventEmitter = ime::EventEmitter();
    CHECK_FALSE(eventEmitter.removeEventListener("test", -1));
}
