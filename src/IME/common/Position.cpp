#include "IME/common/Position.h"

namespace IME {
    bool Position::operator==(const Position &other) {
        return x == other.x && y == other.y;
    }

    bool Position::operator!=(const Position &other) {
        return !(*this == other);
    }
}