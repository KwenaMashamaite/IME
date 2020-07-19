#include "State.h"

namespace IME {
    State::State(Engine &app) : app_(app) {}

    Engine &State::getApp() const {
        return app_;
    }
}