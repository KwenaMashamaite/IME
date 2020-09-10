#include "IME/common/Dimensions.h"

namespace IME {
    bool Dimensions::operator==(const Dimensions &other) {
        return width == other.width && height == other.height;
    }

    bool Dimensions::operator!=(const Dimensions &other) {
        return !(*this == other);
    }
}
