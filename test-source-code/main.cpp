/**
 * @brief Entry point for running unit tests
 *
 * This file does not define any tests, all it does is run them.
 * Unit tests are defined in a seperate file for each unit under
 * test and included here to be run
 */

//Initialize Doctest unit testing framework
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

//Include unit tests to run
#include "WindowTests.hpp"
#include "EventEmitterTests.hpp"
