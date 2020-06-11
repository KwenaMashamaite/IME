#include "UIElement.h"
#include "resources/ResourceManager.h"
#include "utility/Utility.h"

Gui::UIElement::UIElement() : UIElement("")
{}

Gui::UIElement::UIElement(const std::string &textContent)
    : isHidden_(false)
{
    setText(textContent);
    initialize();
}

void Gui::UIElement::initialize() {
    initEvents();
    setTextFont("secret-code.ttf");
    setTextCharSize(25u);
    parentRectangle_.setFillColor({0, 0, 0, 0}); //Transparent
    setFillColour({220, 220, 220}); //Gainsboro
    setOutlineColour({128, 128, 128}); //Grey
    setTextFillColour({0, 0, 0}); //Black
    setOutlineThickness(0.0f);
    setPadding(0.0f);
    setMargin(0.0f);
    text_.setOrigin(text_.getLocalBounds().left, text_.getLocalBounds().top);
}

void Gui::UIElement::initEvents() {
    addListener("textLocalBoundsChanged", Callback<>([this] {
        text_.setOrigin(text_.getLocalBounds().left, text_.getLocalBounds().top);
    }));

    addListener("textFontChanged", Callback<>([this] {
        onTextDimensionsChange();
    }));

    addListener("textContentChanged", Callback<>([this] {
        onTextDimensionsChange();
    }));

    addListener("textCharSizeChanged", Callback<>([this] {
        onTextDimensionsChange();
    }));

    addListener("marginChanged", Callback<>([this] {
        onElementDimensionChange();
    }));

    addListener("paddingChanged", Callback<>([this] {
        onElementDimensionChange();
    }));

    addListener("outlineThicknessChanged", Callback<>([this] {
        onElementDimensionChange();
    }));
}

void Gui::UIElement::setPadding(float padding) {
    padding_ = {padding, padding, padding, padding};
    emit("paddingChanged");
}

void Gui::UIElement::setPadding(const Gui::Padding &padding) {
    padding_ = padding;
    emit("paddingChanged");
}

void Gui::UIElement::setMargin(float margin) {
    margin_ = {margin, margin, margin, margin};
    emit("marginChanged");
}

void Gui::UIElement::setMargin(const Gui::Margin &margin) {
    margin_ = margin;
    emit("marginChanged");
}

void Gui::UIElement::setPosition(float x, float y) {
    parentRectangle_.setPosition(x, y);
    border_.setPosition(
        parentRectangle_.getPosition().x + border_.getOutlineThickness() + margin_.left,
        parentRectangle_.getPosition().y + border_.getOutlineThickness() + margin_.top
    );
    text_.setPosition(
        border_.getPosition().x + padding_.left,
        border_.getPosition().y + padding_.top
    );
}

void Gui::UIElement::setPosition(Position position) {
    setPosition(position.x, position.y);
}

void Gui::UIElement::setTextFont(const std::string &contentFont) {
    text_.setFont(ResourceManager::getFont(contentFont));
    emit("textFontChanged");
    emit("textLocalBoundsChanged");
}

void Gui::UIElement::setTextCharSize(unsigned int charSize) {
    text_.setCharacterSize(charSize);
    emit("textCharSizeChanged");
    emit("textLocalBoundsChanged");
}

void Gui::UIElement::setText(const std::string &content) {
    text_.setString(content);
    emit("textContentChanged");
}

void Gui::UIElement::setOutlineThickness(float outlineThickness) {
    border_.setOutlineThickness(outlineThickness);
    emit("outlineThicknessChanged");
}

void Gui::UIElement::setEnable(bool isEnable) {
    isEnabled_ = isEnable;
}

void Gui::UIElement::setFillColour(Gui::Colour fillColour) {
    border_.setFillColor(Utility::convertOwnColourTo3rdPartyColour(fillColour));
}

void Gui::UIElement::setTextFillColour(Gui::Colour textFillColour) {
    text_.setFillColor(Utility::convertOwnColourTo3rdPartyColour(textFillColour));
}

void Gui::UIElement::setOutlineColour(Gui::Colour outlineColour) {
    border_.setOutlineColor(Utility::convertOwnColourTo3rdPartyColour(outlineColour));
}

Gui::Padding Gui::UIElement::getPadding() const {
    return padding_;
}

Gui::Margin Gui::UIElement::getMargin() const {
    return margin_;
}

Position Gui::UIElement::getPosition() const {
    return {parentRectangle_.getPosition().x,
            parentRectangle_.getPosition().y};
}

Dimensions Gui::UIElement::getDimensions() const {
    return {parentRectangle_.getGlobalBounds().width,
            parentRectangle_.getGlobalBounds().height};
}

Gui::Colour Gui::UIElement::getFillColour() const {
    return Utility::convert3rdPartyColourToOwnColour(border_.getFillColor());
}

Gui::Colour Gui::UIElement::getTextFillColour() const {
    return Utility::convert3rdPartyColourToOwnColour(text_.getFillColor());
}

Gui::Colour Gui::UIElement::getOutlineColour() const {
    return Utility::convert3rdPartyColourToOwnColour(border_.getOutlineColor());
}

void Gui::UIElement::toggleVisibility() {
    if (isHidden_)
        unhide();
    else
        hide();
}

bool Gui::UIElement::isHidden() const {
    return isHidden_;
}

bool Gui::UIElement::isEnabled() const{
    return isEnabled_;
}

bool Gui::UIElement::contains(float x, float y) const{
    //For some reasons SFML doesn't account for the outline thickness when
    //getting the position, so we need to account for it
    auto xBorderPos = border_.getPosition().x - border_.getOutlineThickness();
    auto yBorderPos = border_.getPosition().y - border_.getOutlineThickness();
    return ((x >= xBorderPos && x <= xBorderPos + border_.getGlobalBounds().width)
            && (y >= yBorderPos && y <= yBorderPos + border_.getGlobalBounds().height));
}

void Gui::UIElement::draw(Gui::Window &renderTarget) {
    renderTarget.draw(parentRectangle_);
    renderTarget.draw(border_);
    renderTarget.draw(text_);
}

void Gui::UIElement::hide() {
    isHidden_ = true;
    Utility::makeInvisible(parentRectangle_);
    Utility::makeInvisible(border_);
    Utility::makeInvisible(text_);
}

void Gui::UIElement::unhide() {
    isHidden_ = false;
    Utility::makeVisible(parentRectangle_);
    Utility::makeVisible(border_);
    Utility::makeVisible(text_);
}

void Gui::UIElement::onTextDimensionsChange() {
    border_.setSize(sf::Vector2f(
        text_.getGlobalBounds().width + padding_.left + padding_.right,
        text_.getGlobalBounds().height + padding_.top + padding_.bottom
    ));
    parentRectangle_.setSize(sf::Vector2f(
		border_.getGlobalBounds().width + margin_.left + margin_.right,
        border_.getGlobalBounds().height + margin_.top + margin_.bottom
    ));
    //Alert listeners with the new dimensions of the element
    emit("dimensionsChanged", getDimensions());
}

void Gui::UIElement::onElementDimensionChange() {
    onTextDimensionsChange(); //Update padding and margin
    setPosition(getPosition().x, getPosition().y); //Update padding and margin
}

Gui::UIElement::~UIElement() = default;
