#include "IME/gui/control/UIElement.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"

namespace IME::Gui {
    UIElement::UIElement() : UIElement("")
    {}

    UIElement::UIElement(const std::string &textContent)
        : isHidden_(false)
    {
        setText(textContent);
        initialize();
    }

    void UIElement::initialize() {
        initEvents();
        setTextFont("secret-code.ttf");
        setTextCharSize(25u);
        setTextAlignment(TextAlignment::Left);
        parentRectangle_.setFillColor({0, 0, 0, 0}); //Transparent
        setBackgroundColour({220, 220, 220}); //Gainsboro
        setOutlineColour({128, 128, 128}); //Grey
        setTextColour(Colour::Black); //Black
        setOutlineThickness(0.0f);
        setPadding(0.0f);
        setMargin(0.0f);
        text_.setOrigin(text_.getLocalBounds().left, text_.getLocalBounds().top);
    }

    void UIElement::initEvents() {
        addEventListener("textLocalBoundsChanged", Callback<>([this] {
            text_.setOrigin(text_.getLocalBounds().left, text_.getLocalBounds().top);
        }));
    }

    void UIElement::setPadding(float padding) {
        setPadding({padding, padding, padding, padding});
    }

    void UIElement::setPadding(const Padding &padding) {
        padding_ = padding;
        updateDimensions();
        setPosition(getPosition().x, getPosition().y); //Reposition to indicate new padding
        emit("paddingChanged", padding_);
    }

    void UIElement::setMargin(float margin) {
        setMargin({margin, margin, margin, margin});
    }

    void UIElement::setMargin(const Margin &margin) {
        margin_ = margin;
        updateDimensions();
        setPosition(getPosition().x, getPosition().y); //Reposition to indicate new margin
        emit("marginChanged", margin_);
    }

    void UIElement::setPosition(float x, float y) {
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

    void UIElement::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void UIElement::setTextFont(const std::string &textFont) {
        textFontName_ = textFont;
        text_.setFont(ResourceManager::getInstance()->getFont(textFontName_));
        updateDimensions();
        emit("textFontChanged", textFontName_);
        emit("textLocalBoundsChanged");
    }

    void UIElement::setTextCharSize(unsigned int charSize) {
        text_.setCharacterSize(charSize);
        updateDimensions();
        emit("textCharSizeChanged", charSize);
        emit("textLocalBoundsChanged");
    }

    void UIElement::setText(const std::string &textContent) {
        text_.setString(textContent);
        updateDimensions();
        emit("textChanged", textContent);
    }

    void UIElement::setOutlineThickness(float outlineThickness) {
        border_.setOutlineThickness(outlineThickness);
        updateDimensions();
        setPosition(getPosition().x, getPosition().y); //Reposition to indicate new outline thickness
        emit("outlineThicknessChanged", outlineThickness);
    }

    void UIElement::setBackgroundColour(Colour backgroundColour) {
        border_.setFillColor(Utility::convertTo3rdPartyColour(backgroundColour));
        emit("backgroundColourChanged", backgroundColour);
    }

    void UIElement::setTextColour(Colour textColour) {
        text_.setFillColor(Utility::convertTo3rdPartyColour(textColour));
        emit("textColourChanged", textColour);
    }

    void UIElement::setOutlineColour(Colour outlineColour) {
        border_.setOutlineColor(Utility::convertTo3rdPartyColour(outlineColour));
        emit("outlineColourChanged", outlineColour);
    }

    void UIElement::setTextAlignment(TextAlignment textAlignment) {
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
                    + (getSize().width / 2.0f - text_.getGlobalBounds().width / 2.0f),
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

    Padding UIElement::getPadding() const {
        return padding_;
    }

    Gui::Margin UIElement::getMargin() const {
        return margin_;
    }

    Position UIElement::getPosition() const {
        return {parentRectangle_.getPosition().x,
                parentRectangle_.getPosition().y};
    }

    Dimensions UIElement::getSize() const {
        return {parentRectangle_.getGlobalBounds().width,
                parentRectangle_.getGlobalBounds().height};
    }

    Colour UIElement::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(border_.getFillColor());
    }

    Colour UIElement::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(text_.getFillColor());
    }

    Colour UIElement::getOutlineColour() const {
        return Utility::convertFrom3rdPartyColour(border_.getOutlineColor());
    }

    std::string UIElement::getText() const {
        return text_.getString();
    }

    unsigned int UIElement::getOutlineThickness() const {
        return border_.getOutlineThickness();
    }

    unsigned int UIElement::getTextCharSize() const {
        return text_.getCharacterSize();
    }

    TextAlignment UIElement::getTextAlignment() const {
        return textAlignment_;
    }

    const std::string &UIElement::getFontName() const {
        return textFontName_;
    }

    void UIElement::toggleVisibility() {
        if (isHidden_)
            show();
        else
            hide();
    }

    bool UIElement::isHidden() const {
        return isHidden_;
    }

    bool UIElement::contains(float x, float y) const{
        //For some reasons SFML doesn't account for the outline thickness when
        //getting the position, so we need to account for it
        auto xBorderPos = border_.getPosition().x - border_.getOutlineThickness();
        auto yBorderPos = border_.getPosition().y - border_.getOutlineThickness();
        return ((x >= xBorderPos && x <= xBorderPos + border_.getGlobalBounds().width)
                && (y >= yBorderPos && y <= yBorderPos + border_.getGlobalBounds().height));
    }

    void UIElement::draw(Window &renderTarget) {
        if (!isHidden_) {
            renderTarget.draw(parentRectangle_);
            renderTarget.draw(border_);
            renderTarget.draw(text_);
        }
    }

    void UIElement::hide() {
        if (!isHidden()) {
            isHidden_ = true;
            emit("hidden");
        }
    }

    void UIElement::show() {
        if (isHidden()) {
            isHidden_ = false;
            emit("shown");
        }
    }

    void UIElement::handleEvent(sf::Event event) {

    }

    void UIElement::updateDimensions() {
        border_.setSize(sf::Vector2f(
            text_.getGlobalBounds().width + padding_.left + padding_.right,
            text_.getGlobalBounds().height + padding_.top + padding_.bottom
        ));
        parentRectangle_.setSize(sf::Vector2f(
            border_.getGlobalBounds().width + margin_.left + margin_.right,
            border_.getGlobalBounds().height + margin_.top + margin_.bottom
        ));
        emit("dimensionsChanged", getSize());
    }

    UIElement::~UIElement() = default;
}
