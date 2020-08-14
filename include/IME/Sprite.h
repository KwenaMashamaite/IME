
#ifndef SPRITE_H
#define SPRITE_H

#include <string>

namespace IME {
    class Sprite {
    public:
        void setPosition(float x, float y);
        float setPosition(Position position);

        void setTexture(const std::string& name);
        Position getPosition() const;
    };
} // namespace IME

#endif