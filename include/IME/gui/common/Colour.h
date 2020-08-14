
#ifndef COLOUR_H
#define COLOUR_H

namespace IME{
    namespace Gui{
        class Colour {
        public:
            // Predefined colours
            static const Colour Black;
            static const Colour White;
            static const Colour Transparent;

            /**
             * @brief Default constructor
             *
             * Constructs an opaque black color
             */
            Colour();

            /**
             * @brief Construct the color from its 4 RGBA components
             * @param red Red component
             * @param green Green component
             * @param blue Blue component
             * @param opacity Alpha component
             *
             * All components must be in the range [0, 255]
             */
            Colour(unsigned int red, unsigned int green, unsigned int blue, unsigned opacity = 255);

            /**
             * @brief Check if a colour is the same as this colour
             * @param right Right operand
             * @return True if the colours are the same, otherwise false
             */
             bool operator==(const Colour& right);

            // Colour components
            unsigned int red = 0;
            unsigned int green = 0;
            unsigned int blue = 0;
            unsigned int opacity = 255;
        };
    } // namespace Gui
} // namespace IME

#endif