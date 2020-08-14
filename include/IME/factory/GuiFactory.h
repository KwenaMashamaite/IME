/**
 * @brief Class for instantiating GUI objects
 */

#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include "IME/gui/layout/Panel.h"
#include "IME/gui/control/UIElement.h"
#include <memory>

namespace IME {
    class GuiFactory {
    public:
        /**
         * @brief Get a UI element
         * @tparam T Type of the GUI object to be instantiated
         * @param args Arguments passed to the constructor of the object to be
         *        instantiated
         * @return A unique pointer to the requested UI element
         *
         * This function template will generate a compile time error if the template
         * argument T is not derived from Gui::UIElement
         */
        template<class T, typename... Args>
        std::unique_ptr<Gui::UIElement> getUIElement(Args&&... args) const;

        /**
         * @brief Get a UI panel
         * @tparam T Type of the GUI object to be instantiated
         * @param args Arguments passed to the constructor of the object to be
         *        instantiated
         * @return A unique pointer to the requested panel
         *
         * This function template will generate a compile time error if the template
         * argument T is not derived from Gui::Panel
         */
        template<class T, typename...Args>
        std::unique_ptr<Gui::Panel> getPanel(Args&&... args) const;

    private:
        /**
         * @brief Instantiate a GUI object
         * @tparam T Type of the GUI object to be instantiated
         * @tparam Args Parameter pack
         * @param args Arguments passed to the constructor of the object to be instantiated
         * @return A unique pointer to the created GUI object
         */
        template<class T, typename... Args>
        std::unique_ptr<T> instantiate(Args&&...args) const;
    };

    #include "IME/factory/GuiFactory.inl"
} // namespace IME

#endif
