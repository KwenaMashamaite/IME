#include "IME/graphics/ui/Gui.h"
#include "IME/graphics/Window.h"
#include "IME/graphics/ui/widgets/IWidget.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME::Graphics {
    Gui::Gui(Window &target) : sfmlGui_{target.window_}
    {}

    void Gui::handleEvent(sf::Event event) {
        sfmlGui_.handleEvent(event);
    }

    void Gui::setTabKeyUsageEnabled(bool enabled) {
        sfmlGui_.setTabKeyUsageEnabled(enabled);
    }

    bool Gui::isTabKeyUsageEnabled() const {
        return sfmlGui_.isTabKeyUsageEnabled();
    }

    void Gui::draw() {
        sfmlGui_.draw();
    }

    void Gui::updateAnimationClock() {
        sfmlGui_.updateTime();
    }

    void Gui::setFont(const std::string& filename) {
        //@TODO - somehow contruct tgui::Font from sf::Font
        //sfmlGui_.setFont(IME::ResourceManager::getInstance()->getFont(filename));
    }

    void Gui::removeAllWidgets() {
        sfmlGui_.removeAllWidgets();
    }

    void Gui::setTarget(Window &target) {
        sfmlGui_.setTarget(target.window_);
    }

    const std::vector<UI::IWidget> &Gui::getWidgets() const {

    }

    void Gui::addWidget(const std::shared_ptr<UI::IWidget> widgetPtr,
        const std::string &widgetName)
    {
        sfmlGui_.add(widgetPtr->getInternalPtr(), widgetName);
    }

    std::shared_ptr<UI::IWidget>
    Gui::getWidget(const std::string &widgetName) const {
        return std::shared_ptr<UI::IWidget>();
    }

    bool Gui::removeWidget(const std::shared_ptr<UI::IWidget> widget) {
        return false;
    }

    std::shared_ptr<UI::IWidget> Gui::getFocusedWidget() const {
        return std::shared_ptr<UI::IWidget>();
    }

    std::shared_ptr<UI::IWidget> Gui::getFocusedLeaf() const {
        return std::shared_ptr<UI::IWidget>();
    }

    std::shared_ptr<UI::IWidget> Gui::getWidgetAtPosition(Position pos) const {
        return std::shared_ptr<UI::IWidget>();
    }

    std::shared_ptr<UI::IWidget>
    Gui::getWidgetBelowMouseCursor(Position mousePos) const {
        return std::shared_ptr<UI::IWidget>();
    }

    bool Gui::focusNextWidget(bool recursive) {
        return sfmlGui_.focusNextWidget(recursive);
    }

    bool Gui::focusPreviousWidget(bool recursive) {
        return sfmlGui_.focusPreviousWidget(recursive);
    }

    void Gui::unfocusAllWidgets() {
        sfmlGui_.unfocusAllWidgets();
    }

    void Gui::moveWidgetToFront(const std::shared_ptr<UI::IWidget> widget) {

    }

    void Gui::moveWidgetToBack(const std::shared_ptr<UI::IWidget> widget) {

    }

    void Gui::setOpacity(float opacity) {
        sfmlGui_.setOpacity(opacity);
    }

    float Gui::getOpacity() const {
        return sfmlGui_.getOpacity();
    }

    void Gui::setTextSize(unsigned int size) {
        sfmlGui_.setTextSize(size);
    }

    unsigned int Gui::getTextSize() const {
        return sfmlGui_.getTextSize();
    }

    void Gui::setMouseCursor(CursorType cursorType) {
        sfmlGui_.setOverrideMouseCursor(static_cast<tgui::Cursor::Type>(cursorType));
    }

    void Gui::restoreMouseCursor() {
        sfmlGui_.restoreOverrideMouseCursor();
    }

    void Gui::requestMouseCursor(CursorType cursorType) {
        sfmlGui_.requestMouseCursor(static_cast<tgui::Cursor::Type>(cursorType));
    }
}
