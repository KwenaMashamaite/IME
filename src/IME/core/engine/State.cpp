#include "IME/core/engine/State.h"

namespace IME {
    State::State(Engine &app) : app_(app) {}

    Engine &State::engine() const {
        return app_;
    }
}