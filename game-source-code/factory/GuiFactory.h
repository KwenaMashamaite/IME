/**
 * @brief Class for instantiating GUI objects
 */

#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include "gui/layout/Panel.h"
#include "gui/control/UIElement.h"
#include <memory>

class GuiFactory {
public:
    /**
     * @brief Get a UI element
     * @tparam T Type of the GUI object to be instantiated
     * @param args Arguments passed to the constructor of the object to be
     *        instantiated
     * @return A unique pointer to the requested UI element
     */
    template<class T, typename... Args>
    std::unique_ptr<Gui::UIElement> getUIElement(Args&&... args) const;

    /**
     * @brief Get a UI panel
     * @tparam T Type of the GUI object to be instantiated
     * @param args Arguments passed to the constructor of the object to be
     *        instantiated
     * @return A unique pointer to the requested panel or a null pointer if
     *         the type is invalid
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

#include "GuiFactory.inl"

#endif
