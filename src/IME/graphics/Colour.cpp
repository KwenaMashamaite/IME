#include "IME/graphics/Colour.h"

namespace IME::Graphics {
    const Colour Colour::Black{0, 0, 0, 255};
    const Colour Colour::White{255, 255, 255, 255};
    const Colour Colour::Red{255, 0, 0, 255};
    const Colour Colour::Green{0, 255, 0, 255};
    const Colour Colour::Blue{0, 0, 255, 255};
    const Colour Colour::Yellow{255, 255, 0, 255};
    const Colour Colour::Orange{255, 165, 0, 255};
    const Colour Colour::Cyan{0, 255, 255, 255};
    const Colour Colour::Purple{128, 0, 128, 255};
    const Colour Colour::Violet{238, 130, 238, 255};
    const Colour Colour::Magenta{255, 0, 255, 255};
    const Colour Colour::Pink{255, 192, 203, 255};
    const Colour Colour::Grey{128, 128, 128, 255};
    const Colour Colour::Turquoise{64, 224, 208, 255};
    const Colour Colour::Gold{255, 215, 0, 255};
    const Colour Colour::Transparent{0, 0, 0, 0};

    Colour::Colour() : red(0), green (0), blue(0), opacity(255)
    {}

    Colour::Colour(unsigned int red, unsigned int green, unsigned int blue, unsigned int opacity){
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->opacity = opacity;
    }

    bool Colour::operator==(const Colour &rhs) {
        return red == rhs.red
            && green == rhs.green
            && blue == rhs.blue
            && opacity == rhs.opacity;
    }

    bool Colour::operator!=(const Colour &rhs) {
        return !(*this == rhs);
    }
}
