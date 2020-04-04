/**
 * @brief Interface for menus
 */

#ifndef IMENU_H
#define IMENU_H

namespace Gui {
    class IMenu {
    public:
        /**
         * @brief Draw menu on a render target
         */
        virtual void draw() = 0;

        /**
         * @brief Remove menu from a render target
         */
        virtual void clear() = 0;

        /**
         * @brief Destructor
         */
        virtual ~IMenu() = default;
    };
}
#endif
