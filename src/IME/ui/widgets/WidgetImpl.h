////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef IME_WIDGETIMPL_H
#define IME_WIDGETIMPL_H

#include "IME/ui/widgets/Widget.h"
#include "IME/common/ITransformable.h"
#include <TGUI/Widget.hpp>
#include <TGUI/Renderers/WidgetRenderer.hpp>
#include <TGUI/Widgets/TabContainer.hpp>
#include <TGUI/Widgets/SpinControl.hpp>

namespace ime {
    namespace priv {
        /**
         * @brief Interface for WidgetImpl class template
         * 
         * This interface allows us to store instances of WidgetImpl inside
         * non-template classes. The interface is necessary because you canr
         * have a template variable inside a non-template class unless the
         * variable is static which is not the case in this case because each
         * widget is a different type
         */
        class IWidgetImpl : public ITransformable {
        public:
            /**
             * @brief Make a copy of the the implementation
             * @return A copy of the implementation
             *
             * We returning std::unique_ptr to make sure each widget has its
             * own implementation
             */
            virtual std::unique_ptr<IWidgetImpl> clone() = 0;

            /**
             * @brief Set the widgets renderer
             * @param renderer The renderer to set
             *
             * The renderer determines how the widget is displayed.
             *
             * @see getRenderer
             */
            virtual void setRenderer(ui::IWidgetRenderer::Ptr renderer) = 0;

            /**
             * @brief Get the widgets renderer
             * @return The widgets renderer
             *
             * The renderer gives access to functions that determine how the
             * widget is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            virtual ui::IWidgetRenderer* getRenderer() const = 0;

            /**
             * @brief Set the position of the widget relative to the
             *        size of its parent
             * @param x New x coordinate of the widget
             * @param y New y coordinate of the widget
             *
             * The position is specified using percentages as shown below:
             *
             * @code
             * widget->setPosition({"5%", "10%"});
             * @endcode
             */
            virtual void setPosition(const std::string& x, const std::string& y) = 0;
            using ITransformable::setPosition;

            /**
             * @brief Get the absolute position of the widget
             * @return The absolute position of the widget
             *
             * Unlike getPosition, this function returns the absolute
             * position of the top-left point of the widget instead
             * of the relative position to its parent
             *
             * @see setPosition
             */
            virtual Vector2f getAbsolutePosition() const = 0;

            /**
             * @brief Set the character size of the text
             * @param charSize New character size
             */
            virtual void setTextSize(unsigned int charSize) = 0;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            virtual unsigned int getTextSize() const = 0;

            /**
             * @brief Set the size of the widget
             * @param width The width of the widget
             * @param height The height of the widget
             */
            virtual void setSize(float width, float height) = 0;

            /**
             * @brief Set the size of the widget relative to the size of
             *        its parent
             * @param width The new width of the widget
             * @param height The new height of the widget
             *
             * The size is specified in percentages as shown below
             *
             * @code
             * widget->setSize({"20%", "5%"});
             * @endcode
             */
            virtual void setSize(const std::string& width, const std::string& height) = 0;

            /**
             * @brief Get the size of the widget
             * @return Current size of the widget
             *
             * This function only returns the size of the widget (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            virtual Vector2f getSize() const = 0;

            /**
             * @brief Get the absolute size of the widget
             * @return The absolute size of the widget
             *
             * The absolute size includes the size of the widget, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            virtual Vector2f getAbsoluteSize() = 0;

            /**
             * @brief Set the width of the widget
             * @param width New width of the widget
             *
             * This function sets the width while keeping the height
             * the same
             *
             * @see setSize
             */
            virtual void setWidth(float width) = 0;

            /**
             * @brief Set the width of the widget relative to its parent
             * @param width New width
             *
             * The relative width is given in percentages as shown:
             *
             * @code
             * widget->setWidth("10%");
             * @endcode
             *
             * This function sets the width of the widget while keeping the
             * height the same
             *
             * @see setSize
             */
            virtual void setWidth(const std::string& width) = 0;

            /**
             * @brief Set the height of the widget
             * @param height New height of the widget
             *
             * This function sets the height while keeping the width
             * the same
             *
             * @see setSize
             */
            virtual void setHeight(float height) = 0;

            /**
             * @brief Set the height of the widget relative to its parent
             * @param height New height
             *
             * The relative height is given in percentages as shown:
             *
             * @code
             * widget->setHeight("10%");
             * @endcode
             *
             * This function sets the height of the widget while keeping the
             * width the same
             *
             * @see setSize
             */
            virtual void setHeight(const std::string& height) = 0;

            /**
             * @brief Set the mouse cursor that is displayed when the mouse
             *        is on top of the widget
             * @param cursor The cursor to be shown
             *
             * By default, the arrow cursor is shown
             */
            virtual void setMouseCursor(CursorType cursor) = 0;

            /**
             * @brief Get the mouse cursor that is displayed when the mouse
             *        is on top of the widget
             * @return The cursor shown when hovering above the widget
             */
            virtual CursorType getMouseCursor() const = 0;

            /**
             * @brief Show the widget with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the widget currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the widget
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            virtual void showWithEffect(ui::AnimationType type, Time duration) = 0;

            /**
             * @brief Hide the widget with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the widget currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the widget
             * will be back in the state in which it was when this function
             * was called
             *
             * @see showWithEffect
             * @see isAnimationPlaying
             */
            virtual void hideWithEffect(ui::AnimationType type, Time duration) = 0;

            /**
             * @brief Check whether or not an animation is currently playing
             * @return True if an animation is playing, otherwise false
             *
             * @see showWithEffect
             * @see hideWithEffect
             */
            virtual bool isAnimationPlaying() const = 0;

            /**
             * @brief Show or hide a widget
             * @param visible True to show or false to hide
             *
             * If the widget is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The widget is visible by default.
             */
            virtual void setVisible(bool visible) = 0;

            /**
             * @brief Check if the widget is visible or not
             * @return True if the widget is visible or false if hidden
             */
            virtual bool isVisible() const = 0;

            /**
             * @brief Toggle the visibility of the widget
             *
             * This function will hide the widget if its currently
             * visible and vice versa
             *
             * @see setVisible
             */
            virtual void toggleVisibility() = 0;

            /**
             * @brief Check if coordinates lie inside the widget
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the widget, false if
             *         coordinates do not lie inside the widget
             */
            virtual bool contains(float x, float y) const = 0;

            /**
             * @internal
             * @brief Get the internal pointer to a third party widget object
             * @return The internal pointer to a third party widget object
             *
             * @warning This function is intended for internal use only and
             * should never be called
             */
            virtual std::shared_ptr<tgui::Widget> getInternalPtr() = 0;
        }; // class IWidgetImpl

        /**
         * @brief Widget implementation
         * 
         * This class aims to reduce code repetition since all classes
         * keep an instance of a third party widget and delegate to it,
         * so most of the implementation is the same for some common 
         * functions
         */
        template <typename T>
        class WidgetImpl : public IWidgetImpl {
        public:
            explicit WidgetImpl(std::shared_ptr<T> widget) :
                widget_{std::move(widget)}
            {}

            WidgetImpl(const WidgetImpl& other) :
                widget_{std::make_shared<T>(*other.widget_)}
            {
                setRenderer(other.getRenderer()->clone());
            }

            WidgetImpl& operator=(const WidgetImpl& rhs) {
                if (this != &rhs) {
                    widget_ = rhs.widget_;
                    setRenderer(rhs.getRenderer()->clone());
                }

                return *this;
            }

            WidgetImpl(WidgetImpl&& other) noexcept {
                *this = std::move(other);
            }

            WidgetImpl& operator=(WidgetImpl&& rhs) noexcept {
                if (this != &rhs) {
                    widget_ = std::move(rhs.widget_);
                    setRenderer(std::move(rhs.renderer_));
                }

                return *this;
            }

            std::unique_ptr<IWidgetImpl> clone() override {
                return std::make_unique<WidgetImpl<T>>(*this);
            }

            void setRenderer(ui::IWidgetRenderer::Ptr renderer) override {
                IME_ASSERT(renderer, "Cannot set nullptr as renderer")
                renderer_ = std::move(renderer);

                // tgui::SpinControl and tgui::TabContainer have two different renderers, so
                // they are sort of special cases to this function. Since IME only supports
                // one renderer per widget we will have to choose one and leave out the other
                // (The left out part will have its default look unchangeable). For tgui::SpinControl
                // we choose to use the renderer for tgui::SpinButton part of the control.
                // For tgui::TabContainer, we choose the renderer for the tgui::Tabs part.
                if (auto* tabContainer = dynamic_cast<tgui::TabContainer*>(widget_.get()); tabContainer) {
                    renderer_->setInternalPtr(tabContainer->getTabsRenderer());
                    return;
                } else if (auto* spinControl = dynamic_cast<tgui::SpinControl*>(widget_.get()); spinControl) {
                    renderer_->setInternalPtr(spinControl->getSpinButtonRenderer());
                    return;
                } else
                    renderer_->setInternalPtr(widget_->getRenderer());

                if (renderer_->getInternalPtr())
                    widget_->setRenderer(renderer_->getInternalPtr()->getData());
            }

            ui::IWidgetRenderer* getRenderer() const override {
                return renderer_.get();
            }

            void setTextSize(unsigned int charSize) override {
                widget_->setTextSize(charSize);
            }

            unsigned int getTextSize() const override {
                return widget_->getTextSize();
            }

            void setSize(float width, float height) override {
                widget_->setSize({width, height});
            }

            void setSize(const std::string &width, const std::string &height) override {
                widget_->setSize({width.c_str(), height.c_str()});
            }

            Vector2f getSize() const override {
                return {widget_->getSize().x, widget_->getSize().y};
            }

            Vector2f getAbsoluteSize() override {
                return {widget_->getFullSize().x, widget_->getFullSize().y};
            }

            void setWidth(float width) override {
                widget_->setWidth(width);
            }

            void setWidth(const std::string &width) override {
                widget_->setWidth(width.c_str());
            }

            void setHeight(float height) override {
                widget_->setHeight(height);
            }

            void setHeight(const std::string &height) override {
                widget_->setHeight(height.c_str());
            }

            void setMouseCursor(CursorType cursor) override {
                widget_->setMouseCursor(static_cast<tgui::Cursor::Type>(cursor));
            }

            CursorType getMouseCursor() const override {
                return static_cast<CursorType>(widget_->getMouseCursor());
            }

            void showWithEffect(ui::AnimationType type, Time duration) override {
                widget_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration.asMilliseconds());
            }

            void hideWithEffect(ui::AnimationType type, Time duration) override {
                widget_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration.asMilliseconds());
            }

            bool isAnimationPlaying() const override {
                return widget_->isAnimationPlaying();
            }

            void setVisible(bool visible) override {
                widget_->setVisible(visible);
            }

            bool isVisible() const override {
                return widget_->isVisible();
            }

            void toggleVisibility() override {
                widget_->setVisible(!widget_->isVisible());
            }

            bool contains(float x, float y) const override {
                return widget_->isMouseOnWidget({x, y});
            }

            void setPosition(float x, float y) override {
                widget_->setPosition({x, y});
            }

            void setPosition(Vector2f position) override {
                setPosition(position.x, position.y);
            }

            void setPosition(const std::string &x, const std::string &y) override {
                widget_->setPosition({x.c_str(), y.c_str()});
            }

            Vector2f getPosition() const override {
                return {widget_->getPosition().x, widget_->getPosition().y};
            }

            Vector2f getAbsolutePosition() const override {
                return {widget_->getAbsolutePosition().x, widget_->getAbsolutePosition().y};
            }

            void setRotation(float angle) override {
                widget_->setRotation(angle);
            }

            void rotate(float angle) override {
                widget_->setRotation(widget_->getRotation() + angle);
            }

            float getRotation() const override {
                return widget_->getRotation();
            }

            void setScale(float factorX, float factorY) override {
                widget_->setScale({factorX, factorY});
            }

            void setScale(Vector2f scale) override {
                setScale(scale.x, scale.y);
            }

            void scale(float factorX, float factorY) override {
                widget_->setScale({widget_->getScale().x + factorX,
                    widget_->getScale().y + factorY});
            }

            void scale(Vector2f offset) override {
                scale(offset.x, offset.y);
            }

            Vector2f getScale() const override {
                return {widget_->getScale().x, widget_->getScale().y};
            }

            void setOrigin(float x, float y) override {
                widget_->setOrigin({x, y});
            }

            void setOrigin(Vector2f origin) override {
                setOrigin(origin.x, origin.y);
            }

            Vector2f getOrigin() const override {
                return {widget_->getOrigin().x, widget_->getOrigin().y};
            }

            void move(float offsetX, float offsetY) override {
                widget_->setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
            }

            void move(Vector2f offset) override {
                move(offset.x, offset.y);
            }

            std::shared_ptr<tgui::Widget> getInternalPtr() override {
                return widget_;
            }

            ~WidgetImpl() override = default;

        private:
            std::shared_ptr<T> widget_; //!< Pointer to third party widget
            ui::IWidgetRenderer::Ptr renderer_;
        };
    } // namespace priv
} // namespace ime

#endif //IME_WIDGETIMPL_H
