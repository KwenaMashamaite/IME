/**
 * @brief Interface for menus
 */

#ifndef IMENU_H
#define IMENU_H

#include "../common/IDrawable.h"
#include "factory/GuiFactory.h"

namespace Gui {
    class IMenu : public IDrawable {
    public:
        /**
         * @brief Destructor
         */
        virtual ~IMenu() = default;

    protected:
        /**
         * @brief Get gui factory
         * @return Pointer to a gui factory
         *
         * @note The reference pointer cannot be invalidated while the object
         *       is still "alive"
         */
        const std::shared_ptr<const GuiFactory>& getGuiFactory() const;

    private:
        //Factory for instantiating GUI components used by menu objects
        static std::shared_ptr<const GuiFactory> guiFactory_;
    };
}

#endif
