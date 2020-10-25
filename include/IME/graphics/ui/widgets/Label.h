/**
 * @brief Widget that displays a single line of text
 */

#ifndef LABEL_H
#define LABEL_H

#include "IWidget.h"
#include <TGUI/Widgets/Label.hpp>
#include "IME/graphics/ui/renderers/LabelRenderer.h"
#include <string>

namespace IME {
    namespace Graphics::UI {
        class Label : public IWidget {
        public:
            /**
             * @brief Create a label
             *
             * The label has no text, is located at (0, 0), has the
             * dimensions (0, 0) and a character size of 25 by default
             * @note The elements text font must be set before it is drawn,
             * @see setTextFont() in @class UIElement
             */
            Label();

            /**
             * @brief Create a label
             * @param text Text to be displayed on the label
             *
             * The label has the dimensions of the label text, a
             * character size of 30 and it's position is (0, 0) by
             * default. @note The elements text font must be set before
             * it is drawn, @see setTextFont() in @class UIElement
             */
            explicit Label(const std::string &text);

            /**
             * @brief Set the labels renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the label is displayed. The label
             * has a default renderer which can be manipulated using the
             * @see getRenderer() function
             */
            void setRenderer(std::shared_ptr<LabelRenderer> renderer);

            /**
             * @brief Get the labels renderer
             * @return The labels renderer
             *
             * The renderer gives access to functions that determine how the
             * widget is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             */
            std::shared_ptr<LabelRenderer> getRenderer();

            /**
             * @brief Set the position of the widget
             * @param X coordinate of the new position
             * @param Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * See the move function to apply an offset based on the previous
             * position instead. The default position of a transformable widget
             * is (0, 0).
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the widget
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * See the move function to apply an offset based on the previous
             * position instead. The default position of a transformable widget
             * is (0, 0).
             */
            void setPosition(Position position) override;

            /**
             * @brief Set the orientation of the widget
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead. The default rotation of a transformable widget
             * is 0.
             */
            void setRotation(float angle) override;

            /**
             * @brief Set the scale factors of the widget
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale.
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the local origin of the widget
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of an widget defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the widget, and ignore all
             * transformations (position, scale, rotation).
             * The default origin of a transformable widget is (0, 0).
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Get the position of the widget
             * @return Current position of the widget
             */
            Position getPosition() const override;

            /**
             * @brief Get the local origin of the widget
             * @return get the local origin of the widget
             */
            Position getOrigin() const override;

            /**
             * @brief Get the orientation of the widget
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360].
             */
            float getRotation() const override;

            /**
             * @brief Move the widget by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the widget,
             * unlike setPosition which overwrites it.
             */
            void move(float xOffset, float yOffset) override;

            /**
             * @brief Rotate the widget
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the widget,
             * unlike setRotation() which overwrites it
             */
            void rotate(float offset) override;

            /**
             * @brief Scale the widget
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the widget,
             * unlike setScale() which overwrites it.
             */
            void scale(float factorX, float factorY) override;

            /**
            * @brief Hide widget from a render target
            *
            * A hidden widget will not be drawn on a render target when calling
            * draw()
            */
            void hide() override;

            /**
             * @brief Show a hidden widget
             *
             * This function will reveal an widget that was hidden prior to
             * function call. Calling this function on an widget that is not
             * hidden has no effect
             */
            void show() override;

            /**
             * @brief Check if widget is hidden or not
             * @return True if widget is hidden, false if widget is not hidden
             */
            bool isHidden() const override;

            /**
             * @brief Set the character size of the widget's text
             * @param charSize New character size
             *
             * The default character size is 30
             */
            void setTextSize(unsigned int charSize) override;

            /**
             * @brief Set the text content of the widget
             * @param content New text content
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &content) override;

            /**
             * @brief Set the size of the widget
             * @param width The width of the widget
             * @param height The height of the widget
             */
            void setSize(float width, float height) override;

            /**
             * @brief Get the size of the widget
             * @return Current size of the widget
             *
             * This function only returns the size of the widget, to get the
             * absolute size (with the margin, outline thickness etc...)
             * @see getAbsoluteSize()
             */
            Dimensions getSize() const override;

            /**
             * @brief Get the absolute size of the widget
             * @return The absolute size of the widget
             *
             * The absolute size includes the size of the widget, the padding,
             * margin and outline thickness. To get just the size of the widget
             * use @see getSize()
             */
            Dimensions getAbsoluteSize() override;

            /**
             * @brief Get the widgets text content
             * @return Widgets text content
             */
            std::string getText() const override;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            unsigned int getTextSize() const override;

            /**
             * @brief Get the type of the widget
             * @return Type of the widget
             */
            std::string getType() const override;

            /**
             * @brief Toggle the visibility of the widget
             *
             * This function will make the widget invisible if its currently
             * visible and vice versa. The visibility is not automatically
             * reflected on the render target. A call to draw() must be made
             * after calling this function
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the widget
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the widget, false if
             *         coordinates do not lie inside the widget
             */
            bool contains(float x, float y) const override;

            /**
             * @internal
             * @brief Get the internal pointer to a third party widget
             * @return The internal pointer to a third party widget
             *
             * @warning This function is intended for internal use only and
             * should never be called under any circumstance
             */
            std::shared_ptr<tgui::Widget> getInternalPtr() override;

        private:
            //Pointer to third party label
            std::shared_ptr<tgui::Label> label_;
            //Renderer for this label
            std::shared_ptr<LabelRenderer> renderer_;
            //How long the label takes before its completely hidden or shown
            static const int fadeAnimDuration_ = 100;
        };
    }
} 

#endif
