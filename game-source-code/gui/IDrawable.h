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
         * @brief Draw object on a render target
         * @param renderTarget Target to draw object on
         */
        virtual void draw(Window &renderTarget) = 0;
    };
}

#endif