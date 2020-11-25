#include "IME/core/tilemap/Index.h"

namespace IME {
    bool operator!=(const Index &lhs, const Index &rhs) {
        return lhs.row != rhs.row || lhs.colm != rhs.colm;
    }

    bool operator==(const Index &lhs, const Index &rhs) {
        return lhs.row == rhs.row && lhs.colm == rhs.colm;
    }
}