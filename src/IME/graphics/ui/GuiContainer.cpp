#include "IME/graphics/ui/GuiContainer.h"
#include "IME/graphics/Window.h"
#include "IME/graphics/ui/widgets/IWidget.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"

namespace IME::Graphics::UI {
    GuiContainer::GuiContainer(Window &target) : sfmlGui_{target.window_}
    {}

    void GuiContainer::handleEvent(sf::Event event) {
        sfmlGui_.handleEvent(event);
    }

    void GuiContainer::setTabKeyUsageEnabled(bool enabled) {
        sfmlGui_.setTabKeyUsageEnabled(enabled);
    }

    bool GuiContainer::isTabKeyUsageEnabled() const {
        return sfmlGui_.isTabKeyUsageEnabled();
    }

    void GuiContainer::draw() {
        sfmlGui_.draw();
    }

    void GuiContainer::setFont(const std::string& filename) {
        sfmlGui_.setFont(Utility::get_TGUI_Font(filename));
    }

    void GuiContainer::removeAllWidgets() {
        sfmlGui_.removeAllWidgets();
        widgets_.clear();
    }

    void GuiContainer::setTarget(Window &target) {
        sfmlGui_.setTarget(target.window_);
    }

    std::shared_ptr<IWidget>
    GuiContainer::getWidgetBelowMouseCursor(Position mousePos) const {
        return std::shared_ptr<IWidget>();
    }

    void GuiContainer::unfocusAllWidgets() {
        sfmlGui_.unfocusAllWidgets();
    }

    void GuiContainer::setOpacity(float opacity) {
        sfmlGui_.setOpacity(opacity);
    }

    float GuiContainer::getOpacity() const {
        return sfmlGui_.getOpacity();
    }

    void GuiContainer::setMouseCursor(CursorType cursorType) {
        sfmlGui_.setOverrideMouseCursor(static_cast<tgui::Cursor::Type>(cursorType));
    }

    void GuiContainer::restoreMouseCursor() {
        sfmlGui_.restoreOverrideMouseCursor();
    }

    void GuiContainer::requestMouseCursor(CursorType cursorType) {
        sfmlGui_.requestMouseCursor(static_cast<tgui::Cursor::Type>(cursorType));
    }

    const std::vector<IWidget> &GuiContainer::getWidgets() const {

    }

    void GuiContainer::addWidget(std::shared_ptr<IWidget> widget,
         const std::string &widgetName)
    {
        sfmlGui_.add(widget->getInternalPtr(), widgetName);
        widgets_.insert({widgetName, std::move(widget)});
    }

    std::shared_ptr<IWidget>
    GuiContainer::getWidget(const std::string &widgetName) const {

        return std::shared_ptr<IWidget>();
    }

    bool GuiContainer::removeWidget(std::shared_ptr<IWidget> widget) {
        return sfmlGui_.remove(widget->getInternalPtr());
    }

    std::shared_ptr<IWidget> GuiContainer::getFocusedWidget() const {
        return std::shared_ptr<IWidget>();
    }

    std::shared_ptr<IWidget> GuiContainer::getFocusedLeaf() const {
        return std::shared_ptr<IWidget>();
    }

    std::shared_ptr<IWidget> GuiContainer::getWidgetAtPosition(Position pos) const {
        return std::shared_ptr<IWidget>();
    }

    bool GuiContainer::focusNextWidget(bool recursive) {
        return sfmlGui_.focusNextWidget(recursive);
    }

    bool GuiContainer::focusPreviousWidget(bool recursive) {
        return sfmlGui_.focusPreviousWidget(recursive);
    }

    void GuiContainer::moveWidgetToFront(const std::shared_ptr<IWidget> &widget) {
        sfmlGui_.moveWidgetToFront(widget->getInternalPtr());
    }

    void GuiContainer::moveWidgetToBack(const std::shared_ptr<IWidget> &widget) {
        sfmlGui_.moveWidgetToBack(widget->getInternalPtr());
    }

    size_t
    GuiContainer::moveWidgetForward(std::shared_ptr<IWidget> widget) {
        return sfmlGui_.moveWidgetForward(widget->getInternalPtr());
    }

    size_t
    GuiContainer::moveWidgetBackward(std::shared_ptr<IWidget> widget) {
        return sfmlGui_.moveWidgetBackward(widget->getInternalPtr());
    }

    void GuiContainer::setTextSize(unsigned int size) {
        sfmlGui_.setTextSize(size);
    }

    unsigned int GuiContainer::getTextSize() const {
        return sfmlGui_.getTextSize();
    }
}
