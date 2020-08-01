
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "IME/core/engine/State.h"
#include "IME/factory/GuiFactory.h"
#include <memory>

namespace SI {
class MenuState : public IME::State {
    public:
        /**
         *
         * @param engine
         */
        MenuState(IME::Engine& engine);

    protected:
        /**
         * @brief Get gui factory
         * @return Pointer to a gui factory
         */
        const std::shared_ptr<const GuiFactory>& getGuiFactory() const;

    private:
        //Factory for instantiating GUI components used by menu objects
        static std::shared_ptr<const GuiFactory> guiFactory_;
    };
}

#endif
