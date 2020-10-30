#include "IME/graphics/ui/layout/VerticalLayout.h"
#include <cassert>

namespace IME::Graphics::UI {
    VerticalLayout::VerticalLayout(float width, float height)
        : layout_{tgui::VerticalLayout::create({width, height})},
          renderer_{std::make_shared<BoxLayoutRenderer>()}
    {
        renderer_->setInternalPtr(layout_->getRenderer());
        initEvents();
    }

    void VerticalLayout::setRenderer(std::shared_ptr<BoxLayoutRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        layout_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<BoxLayoutRenderer> VerticalLayout::getRenderer() {
        return renderer_;
    }

    void VerticalLayout::setTextSize(unsigned int charSize) {
        layout_->setTextSize(charSize);
    }

    void VerticalLayout::setText(const std::string &content) {

    }

    void VerticalLayout::setSize(float width, float height) {
        layout_->setSize({width, height});
    }

    Dimensions VerticalLayout::getSize() const {
        return {layout_->getSize().x, layout_->getSize().y};
    }

    Dimensions VerticalLayout::getAbsoluteSize() {
        return {layout_->getFullSize().x, layout_->getFullSize().y};
    }

    std::string VerticalLayout::getText() const {
        return "";
    }

    unsigned int VerticalLayout::getTextSize() const {
        return layout_->getTextSize();
    }

    std::string VerticalLayout::getType() const {
        return "VerticalLayout";
    }

    void VerticalLayout::toggleVisibility() {
        if (isHidden())
            show();
        else
            hide();
    }

    bool VerticalLayout::contains(float x, float y) const {
        return layout_->isMouseOnWidget({x, y});
    }

    void VerticalLayout::hide() {
        layout_->hideWithEffect(tgui::ShowAnimationType::Fade, fadeAnimDuration_);
    }

    void VerticalLayout::show() {
        layout_->showWithEffect(tgui::ShowAnimationType::Fade, fadeAnimDuration_);
    }

    bool VerticalLayout::isHidden() const {
        return !layout_->isVisible();
    }

    void VerticalLayout::setPosition(float x, float y) {
        layout_->setPosition({x, y});
    }

    void VerticalLayout::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void VerticalLayout::setRotation(float angle) {
        layout_->setRotation(angle);
    }

    void VerticalLayout::setScale(float factorX, float factorY) {
        layout_->setScale({factorX, factorY});
    }

    void VerticalLayout::setOrigin(float x, float y) {
        layout_->setOrigin({x, y});
    }

    Position VerticalLayout::getPosition() const {
        return {layout_->getPosition().x, layout_->getPosition().y};
    }

    Position VerticalLayout::getOrigin() const {
        return {layout_->getOrigin().x, layout_->getOrigin().y};
    }

    float VerticalLayout::getRotation() const {
        return layout_->getRotation();
    }

    void VerticalLayout::move(float offsetX, float offsetY) {
        layout_->setPosition(getPosition().x + offsetX,
            getPosition().y + offsetY);
    }

    void VerticalLayout::rotate(float angle) {
        setRotation(getRotation() + angle);
    }

    void VerticalLayout::scale(float factorX, float factorY) {
        setScale(layout_->getScale().x + factorX, layout_->getScale().y + factorY);
    }

    void VerticalLayout::insertWidget(std::size_t index,
        std::shared_ptr<IWidget> widget, const std::string &widgetName)
    {
        layout_->insert(index, widget->getInternalPtr(), widgetName);
    }

    bool VerticalLayout::removeWidgetAt(std::size_t index) {
        return layout_->remove(index);
    }

    std::shared_ptr<IWidget>
    VerticalLayout::getWidgetAt(std::size_t index) const {
        return std::shared_ptr<IWidget>();
    }

    void VerticalLayout::addSpace(float ratio) {
        layout_->addSpace(ratio);
    }

    void VerticalLayout::insertSpace(std::size_t index, float ratio) {
        layout_->insertSpace(index, ratio);
    }

    bool VerticalLayout::setRatio(std::shared_ptr<IWidget> widget, float ratio) {
        return layout_->setRatio(widget->getInternalPtr(), ratio);
    }

    bool VerticalLayout::setRatio(std::size_t index, float ratio) {
        return layout_->setRatio(index, ratio);
    }

    float VerticalLayout::getRatio(std::shared_ptr<IWidget> widget) const {
        return layout_->getRatio(widget->getInternalPtr());
    }

    float VerticalLayout::getRatio(std::size_t index) const {
        return layout_->getRatio(index);
    }

    void VerticalLayout::addWidget(const std::shared_ptr<UI::IWidget> widgetPtr,
        const std::string &widgetName)
    {
        layout_->add(widgetPtr->getInternalPtr(), widgetName);
    }

    std::shared_ptr<IWidget> VerticalLayout::getWidget(const std::string &widgetName) const {
        return std::shared_ptr<IWidget>();
    }

    const std::vector<IWidget> &VerticalLayout::getWidgets() const {

    }

    bool VerticalLayout::removeWidget(std::shared_ptr<UI::IWidget> widget) {
        return false;
    }

    void VerticalLayout::removeAllWidgets() {
        layout_->removeAllWidgets();
    }

    void VerticalLayout::moveWidgetToFront(std::shared_ptr<IWidget> widget) {
        layout_->moveWidgetToFront(widget->getInternalPtr());
    }

    void VerticalLayout::moveWidgetToBack(std::shared_ptr<IWidget> widget) {
        layout_->moveWidgetToBack(widget->getInternalPtr());
    }

    size_t VerticalLayout::moveWidgetForward(std::shared_ptr<UI::IWidget> widget) {
        return layout_->moveWidgetForward(widget->getInternalPtr());
    }

    size_t VerticalLayout::moveWidgetBackward(std::shared_ptr<UI::IWidget> widget) {
        return layout_->moveWidgetBackward(widget->getInternalPtr());
    }

    std::shared_ptr<UI::IWidget> VerticalLayout::getFocusedWidget() const {
        return std::shared_ptr<UI::IWidget>();
    }

    std::shared_ptr<UI::IWidget> VerticalLayout::getFocusedLeaf() const {
        return std::shared_ptr<UI::IWidget>();
    }

    std::shared_ptr<UI::IWidget> VerticalLayout::getWidgetAtPosition(Position pos) const {
        return std::shared_ptr<UI::IWidget>();
    }

    bool VerticalLayout::focusNextWidget(bool recursive) {
        return layout_->focusNextWidget(recursive);
    }

    bool VerticalLayout::focusPreviousWidget(bool recursive) {
        return layout_->focusPreviousWidget(recursive);
    }

    std::shared_ptr<tgui::Widget> VerticalLayout::getInternalPtr() {
        return layout_;
    }

    void VerticalLayout::initEvents() {
        layout_->onMouseEnter([this]{emit("mouseEnter");});
        layout_->onMouseLeave([this]{emit("mouseLeave");});
        layout_->onFocus([this]{emit("focus");});
        layout_->onUnfocus([this]{emit("unfocus");});
        layout_->onAnimationFinish([this]{emit("animationFinish");});
        layout_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        layout_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });
    }
}