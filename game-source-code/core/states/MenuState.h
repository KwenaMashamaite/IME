
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../State.h"
#include "factory/GuiFactory.h"
#include <memory>

namespace IME {
    class MenuState : public State {
    public:
        /**
         *
         * @param engine
         */
        MenuState(Engine& engine);

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
