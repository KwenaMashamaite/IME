/**
 * @brief Class for drawing game graphics (textures, texts, sprites, images, etc)
 */

#ifndef DRAWER_H
#define DRAWER_H

#include "../window/Window.h"
#include "IME/core/IEntity.h"
#include "IME/core/animation/Animator.h"
#include <memory>

namespace IME {
    namespace Gui {
        class Drawer final {
        public:
            using EntityAnimatorPair = std::pair<std::shared_ptr<IEntity>&, Animator&>;
            /**
             * @brief Constructor
             * @param renderTarget Target to draw on
             */
            explicit Drawer(Window &renderTarget);

            /**
             * @brief Draw entity on a render target
             * @param entityAnimatorPair entity to draw
             */
            void drawEntity(const EntityAnimatorPair &entityAnimatorPair);

            /**
             * @brief Draw multiple entities at the same time on a render target
             * @param entityAnimatorPairs Entities to be drawn
             */
            void drawEntities(const std::initializer_list<EntityAnimatorPair> &entityAnimatorPairs);

            /**
             * @brief Draw background texture
             * @param background filename of the background texture
             *
             * The background texture must at least have the same dimensions as
             * the render target, otherwise the texture will be stretched to fit the
             * the size of the render target. This may lead to an unpleasant looking
             * backgrounds
             */
            void drawBackground(const std::string &background);

        private:
            //Reference to a render target
            Window& renderTarget_;
        };
    } // namespace Gui
} // namespace IME

#endif
