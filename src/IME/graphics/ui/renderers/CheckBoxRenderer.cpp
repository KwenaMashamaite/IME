#include "IME/graphics/ui/renderers/CheckBoxRenderer.h"

namespace IME::Graphics::UI {
    void CheckBoxRenderer::setBorders(const Borders &borders) {

    }

    Borders CheckBoxRenderer::getBorders() const {
        return Borders();
    }

    void CheckBoxRenderer::setTextDistanceRatio(float ratio) {

    }

    float CheckBoxRenderer::getTextDistanceRatio() const {
        return 0;
    }

    void CheckBoxRenderer::setTextColour(Colour textColour) {

    }

    void CheckBoxRenderer::setTextHoverColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getTextHoverColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setDisabledTextColour(Colour textColour) {

    }

    Colour CheckBoxRenderer::getDisabledTextColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckedTextColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getTextColorChecked() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckedTextHoverColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getTextColorCheckedHover() const {
        return Colour();
    }

    void CheckBoxRenderer::setTextColourCheckedDisabled(Colour colour) {

    }

    Colour CheckBoxRenderer::getTextColorCheckedDisabled() const {
        return Colour();
    }

    void CheckBoxRenderer::setBackgroundColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getBackgroundColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setBackgroundHoverColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getBackgroundColorHover() const {
        return Colour();
    }

    void CheckBoxRenderer::setDisabledBackgroundColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getDisabledBackgroundColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckedBackgroundColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getCheckedBackgroundColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckedHoverBackgroundColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getCheckedHoverBackgroundColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckedDisabledBackgroundColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getCheckedDisabledBackgroundColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setBorderColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getBorderColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setBorderHoverColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getBorderHoverColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setDisabledBorderColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getDisabledBorderColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setFocusedBorderColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getFocusedBorderColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckedBorderColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getBorderColorChecked() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckedHoverBorderColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getCheckedHoverBorderColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckedDisabledBorderColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getCheckedDisabledBorderColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckedFocusedBorderColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getBorderColourCheckedFocused() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getCheckColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setCheckHoverColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getCheckHoverColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setDisabledCheckColour(Colour colour) {

    }

    Colour CheckBoxRenderer::getDisabledCheckColour() const {
        return Colour();
    }

    void CheckBoxRenderer::setUncheckedTexture(const std::string &filename) {

    }

    void CheckBoxRenderer::setCheckedTexture(const std::string &filename) {

    }

    void
    CheckBoxRenderer::setTextureUncheckedHover(const std::string &filename) {

    }

    void CheckBoxRenderer::setCheckedHoverTexture(const std::string &texture) {

    }

    void
    CheckBoxRenderer::setUncheckedDisabledTexture(const std::string &texture) {

    }

    void
    CheckBoxRenderer::setCheckedDisabledTexture(const std::string &texture) {

    }

    void
    CheckBoxRenderer::setUncheckedFocusedTexture(const std::string &texture) {

    }

    void
    CheckBoxRenderer::setCheckedFocusedTexture(const std::string &texture) {

    }

    void CheckBoxRenderer::setTextStyle(TextStyle style) {

    }

    TextStyle CheckBoxRenderer::getTextStyle() const {
        return TextStyle::Underlined;
    }

    void CheckBoxRenderer::setCheckedTextStyle(TextStyle style) {

    }

    TextStyle CheckBoxRenderer::getCheckedTextStyle() const {
        return TextStyle::Underlined;
    }

    void CheckBoxRenderer::setOpacity(float opacity) {

    }

    float CheckBoxRenderer::getOpacity() const {
        return 0;
    }

    void CheckBoxRenderer::setOpacityDisabled(float opacity) {

    }

    float CheckBoxRenderer::getOpacityDisabled() const {
        return 0;
    }

    void CheckBoxRenderer::setFont(const std::string &font) {

    }

    void
    CheckBoxRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {

    }

    bool CheckBoxRenderer::isTransparentTextureIgnored() const {
        return false;
    }

    int CheckBoxRenderer::onPropertyChange(const std::string &property,
                                           Callback<const std::string &> callback) {
        return 0;
    }

    void CheckBoxRenderer::unsubscribe(int id) {

    }

    void CheckBoxRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {

    }

    tgui::WidgetRenderer *CheckBoxRenderer::getInternalPtr() {
        return nullptr;
    }
}