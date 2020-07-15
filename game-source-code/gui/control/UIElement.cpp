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
    setTextAlignment(TextAlignment::Left);
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
    addEventListener("textLocalBoundsChanged", Callback<>([this] {
        text_.setOrigin(text_.getLocalBounds().left, text_.getLocalBounds().top);
    }));
}

void Gui::UIElement::setPadding(float padding) {
    setPadding({padding, padding, padding, padding});
}

void Gui::UIElement::setPadding(const Gui::Padding &padding) {
    padding_ = padding;
    updateDimensions();
    setPosition(getPosition().x, getPosition().y); //Reposition to indicate new padding
    emit("paddingChanged", padding_);
}

void Gui::UIElement::setMargin(float margin) {
    setMargin({margin, margin, margin, margin});
}

void Gui::UIElement::setMargin(const Gui::Margin &margin) {
    margin_ = margin;
    updateDimensions();
    setPosition(getPosition().x, getPosition().y); //Reposition to indicate new margin
    emit("marginChanged", margin_);
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
    emit("positionChanged", getPosition());
}

void Gui::UIElement::setPosition(Position position) {
    setPosition(position.x, position.y);
}

void Gui::UIElement::setTextFont(const std::string &textFont) {
    textFontName_ = textFont;
    text_.setFont(ResourceManager::getFont(textFontName_));
    updateDimensions();
    emit("textFontChanged", textFontName_);
    emit("textLocalBoundsChanged");
}

void Gui::UIElement::setTextCharSize(unsigned int charSize) {
    text_.setCharacterSize(charSize);
    updateDimensions();
    emit("textCharSizeChanged", charSize);
    emit("textLocalBoundsChanged");
}

void Gui::UIElement::setText(const std::string &textContent) {
    text_.setString(textContent);
    updateDimensions();
    emit("textContentChanged", textContent);
}

void Gui::UIElement::setOutlineThickness(float outlineThickness) {
    border_.setOutlineThickness(outlineThickness);
    updateDimensions();
    setPosition(getPosition().x, getPosition().y); //Reposition to indicate new outline thickness
    emit("outlineThicknessChanged", outlineThickness);
}

void Gui::UIElement::setFillColour(Gui::Colour fillColour) {
    border_.setFillColor(Utility::convertOwnColourTo3rdPartyColour(fillColour));
    emit("fillColourChanged", fillColour);
}

void Gui::UIElement::setTextFillColour(Gui::Colour textFillColour) {
    text_.setFillColor(Utility::convertOwnColourTo3rdPartyColour(textFillColour));
    emit("textFillColourChanged", textFillColour);
}

void Gui::UIElement::setOutlineColour(Gui::Colour outlineColour) {
    border_.setOutlineColor(Utility::convertOwnColourTo3rdPartyColour(outlineColour));
    emit("outlineColourChanged", outlineColour);
}

void Gui::UIElement::setTextAlignment(Gui::TextAlignment textAlignment) {
    if (textAlignment_ == textAlignment)
        return;
    else
        textAlignment_ = textAlignment;

    switch (textAlignment) {
        case TextAlignment::Left:
            text_.setPosition(border_.getPosition().x, border_.getPosition().y + padding_.top
            );
            setPadding({
                0.0f,
                border_.getLocalBounds().width - text_.getLocalBounds().width
                - 2 * border_.getOutlineThickness(),
                getPadding().top,
                getPadding().bottom
            });
            break;
        case TextAlignment::Right:
            text_.setPosition(
                (border_.getPosition().x + border_.getLocalBounds().width) - text_.getLocalBounds().width,
                border_.getPosition().y + getPadding().top
            );
            setPadding({
                border_.getLocalBounds().width - text_.getLocalBounds().width
                - 2 * border_.getOutlineThickness(),
                0.0f,
                getPadding().top,
                getPadding().bottom
            });
            break;
        case TextAlignment::Center:
            text_.setPosition(
                border_.getPosition().x - border_.getOutlineThickness()
                + (getDimensions().width / 2.0f - text_.getGlobalBounds().width / 2.0f),
                border_.getPosition().y + getPadding().top
            );
            setPadding({
                text_.getPosition().x - border_.getPosition().x,
                border_.getPosition().x + border_.getLocalBounds().width
                - (text_.getPosition().x  + text_.getLocalBounds().width)
                - 2 * border_.getOutlineThickness(),
                getPadding().top,
                getPadding().bottom
            });
            break;
    }
    emit("textAlignmentChanged", textAlignment_);
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

Gui::TextAlignment Gui::UIElement::getTextAlignment() const {
    return textAlignment_;
}

const std::string &Gui::UIElement::getFontName() const {
    return textFontName_;
}

void Gui::UIElement::toggleVisibility() {
    if (isHidden_)
        show();
    else
        hide();
}

bool Gui::UIElement::isHidden() const {
    return isHidden_;
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
    if (!isHidden_) {
        renderTarget.draw(parentRectangle_);
        renderTarget.draw(border_);
        renderTarget.draw(text_);
    }
}

void Gui::UIElement::hide() {
    if (!isHidden()) {
        isHidden_ = true;
        Utility::makeInvisible(parentRectangle_);
        Utility::makeInvisible(border_);
        Utility::makeInvisible(text_);
        emit("visibilityChanged", isHidden_);
    }
}

void Gui::UIElement::show() {
    if (isHidden()) {
        isHidden_ = false;
        Utility::makeVisible(parentRectangle_);
        Utility::makeVisible(border_);
        Utility::makeVisible(text_);
        emit("visibilityChanged", isHidden_);
    }
}

void Gui::UIElement::updateDimensions() {
    border_.setSize(sf::Vector2f(
        text_.getGlobalBounds().width + padding_.left + padding_.right,
        text_.getGlobalBounds().height + padding_.top + padding_.bottom
    ));
    parentRectangle_.setSize(sf::Vector2f(
		border_.getGlobalBounds().width + margin_.left + margin_.right,
        border_.getGlobalBounds().height + margin_.top + margin_.bottom
    ));
    emit("dimensionsChanged", getDimensions());
}

Gui::UIElement::~UIElement() = default;
