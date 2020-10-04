#include "IME/graphics/Colour.h"

namespace IME::Graphics {
    const Colour Colour::Black{0, 0, 0, 255};
    const Colour Colour::White{255, 255, 255, 255};
    const Colour Colour::Red{255, 0, 0, 255};
    const Colour Colour::Green{0, 255, 0, 255};
    const Colour Colour::Blue{0, 0, 255, 255};
    const Colour Colour::Transparent{0, 0, 0, 0};

    Colour::Colour() : red(0), green (0), blue(0), opacity(255)
    {}

    Colour::Colour(unsigned int red, unsigned int green, unsigned int blue, unsigned int opacity){
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->opacity = opacity;
    }

    bool Colour::operator==(const Colour &right) {
        return red == right.red
            && green == right.green
            && blue == right.blue
            && opacity == right.opacity;
    }
}
