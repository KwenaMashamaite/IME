#include "IME/core/engine/State.h"

namespace IME {
    State::State(Engine &app) : app_(app) {}

    Engine &State::app() const {
        return app_;
    }
}