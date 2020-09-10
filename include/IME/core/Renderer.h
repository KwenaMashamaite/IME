/**
 * @brief
 */

#ifndef IME_RENDERER_H
#define IME_RENDERER_H

#include "IME/gui/window/Window.h"

namespace IME {
    class Renderer {
    public:
        /**
         *
         * @param window
         */
        Renderer(Gui::Window& window);

        /**
         * @brief Draw an image on the render target
         * @param filename Filename of the image to draw
         * @param x X coordinate of the image
         * @param y Y coordinate of the image
         */
        void drawImage(const std::string& filename, float x, float y);

        /**
         *
         * @param filename
         * @param x
         * @param y
         */
        void drawSprite(const std::string& filename, float x, float y);
    };
}

#endif
