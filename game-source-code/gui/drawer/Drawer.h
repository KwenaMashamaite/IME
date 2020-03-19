/**
 * @brief Class for drawing game graphics (textures, texts, sprites, images, etc)
 */

#ifndef DRAWER_H
#define DRAWER_H

#include "gui/window/Window.h"
#include <memory>

class Entity;

namespace Gui {
    class Drawer {
    public:
        /**
		 * @brief Constructor
		 * @param renderTarget Target to draw on
		 */
        explicit Drawer(Window &renderTarget);

        /**
         * @brief Draw entity on a render target
         * @param entity entity to draw
         */
        void drawEntity(const std::shared_ptr<Entity> &entity);

        /**
         * @brief Draw multiple entities all at once
         * @param entities Entities to be drawn
         */
        void drawEntities(const std::initializer_list<std::shared_ptr<Entity>> &entities);

        /**
         * @brief Draw background tex
         * @param background filename of the background texture
         *
         * The background texture must at least have the same dimensions as
         * the render target, otherwise the texture will be stretched to fit the
         * the entire window. This may lead to an unpleasant looking background
         */
        void drawBackground(const std::string &background);

    private:
        //Reference to a render target
        Window& renderTarget_;
    };
}

#endif
