/**
 * @brief Interface for drawable objects
 */

#ifndef IDRAWABLE_H
#define IDRAWABLE_H

namespace IME {
    namespace Gui {
        class Window; //Forward declaration
    }

    class IDrawable {
    public:
        /**
         * @brief Draw object on a render target
         * @param renderTarget Target to draw object on
         */
        virtual void draw(Gui::Window &renderTarget) = 0;

        /**
         * @brief Hide object from a render target
         *
         * A hidden object will not be drawn on a render target when calling
         * draw(Window)
         */
        virtual void hide() = 0;

        /**
         * @brief Show a hidden object
         *
         * This function will reveal an object that was hidden prior to function
         * call. Calling this function on an object that is not hidden has no
         * effect. This function does not show the object on a render target, it
         * only allows the object to be drawn on a render target
         */
        virtual void show() = 0;

        /**
         * @brief Check is object is hidden or not
         * @return True if object is hidden, false if object is not hidden
         */
        virtual bool isHidden() const = 0;
    };
} // namespace IME

#endif