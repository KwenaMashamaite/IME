/**
 * @brief Interface for drawable GUI elements
 */

#ifndef IDRAWABLE_H
#define IDRAWABLE_H

namespace Gui{
    class Window; //Forward declaration
}

namespace Gui {
    class IDrawable {
    public:
        /**
         * @brief Draw drawable on a render target
         * @param renderTarget Target to draw menu on
         */
        virtual void draw(Window &renderTarget) = 0;

        /**
         * @brief Remove drawable from a render target
         * @param renderTarget Target to remove drawable from
         */
        virtual void remove(Window &renderTarget) = 0;
    };
}

#endif