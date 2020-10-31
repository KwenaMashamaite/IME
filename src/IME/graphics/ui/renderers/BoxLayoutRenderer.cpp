#include "IME/graphics/ui/renderers/BoxLayoutRenderer.h"

namespace IME::Graphics::UI {
    void BoxLayoutRenderer::setPadding(const Padding &padding) {
        boxLayoutRenderer_->setPadding({padding.left, padding.top, 
            padding.right, padding.bottom});
    }

    Padding BoxLayoutRenderer::getPadding() const {
        return {boxLayoutRenderer_->getPadding().getLeft(),
                boxLayoutRenderer_->getPadding().getTop(),
                boxLayoutRenderer_->getPadding().getRight(),
                boxLayoutRenderer_->getPadding().getBottom()};
    }

    void BoxLayoutRenderer::setSpaceBetweenWidgets(float distance) {
        boxLayoutRenderer_->setSpaceBetweenWidgets(distance);
    }

    float BoxLayoutRenderer::getSpaceBetweenWidgets() const {
        return boxLayoutRenderer_->getSpaceBetweenWidgets();
    }

    void BoxLayoutRenderer::setOpacity(float opacity) {
        boxLayoutRenderer_->setOpacity(opacity);
    }

    float BoxLayoutRenderer::getOpacity() const {
        return boxLayoutRenderer_->getOpacity();
    }

    void BoxLayoutRenderer::setOpacityDisabled(float opacity) {
        boxLayoutRenderer_->setOpacityDisabled(opacity);
    }

    float BoxLayoutRenderer::getOpacityDisabled() const {
        return boxLayoutRenderer_->getOpacity();
    }

    void BoxLayoutRenderer::setFont(const std::string &font) {
        boxLayoutRenderer_->setFont(font.c_str());
    }

    void BoxLayoutRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        boxLayoutRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool BoxLayoutRenderer::isTransparentTextureIgnored() const {
        return boxLayoutRenderer_->getTransparentTexture();
    }

    int BoxLayoutRenderer::onPropertyChange(const std::string &property,
         Callback<const std::string &> callback)
    {
        return 0;
    }

    void BoxLayoutRenderer::unsubscribe(int id) {

    }

    void BoxLayoutRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        boxLayoutRenderer_ = dynamic_cast<tgui::BoxLayoutRenderer*>(renderer);
    }

    tgui::WidgetRenderer *BoxLayoutRenderer::getInternalPtr() {
        return boxLayoutRenderer_;
    }

    BoxLayoutRenderer::~BoxLayoutRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        boxLayoutRenderer_ = nullptr;
    }
}
