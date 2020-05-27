/**
 * @brief Interface for menus
 */

#ifndef IMENU_H
#define IMENU_H

#include "gui/IDrawable.h"

namespace Gui {
    class IMenu : public IDrawable {
    public:
        /**
         * @brief Destructor
         */
        virtual ~IMenu() = default;
    };
}
#endif
