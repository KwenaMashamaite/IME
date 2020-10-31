/**
 * @brief A window that can be displayed on top of the another window
 */

#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

#include "IContainer.h"
#include "IME/graphics/ui/renderers/ChildWindowRenderer.h"
#include <TGUI/Widgets/ChildWindow.hpp>

namespace IME {
    namespace Graphics::UI {
        class ChildWindow : public IContainer {
        public:
            /// Title alignments, possible options for the setTitleAlignment function
            enum class TitleAlignment {
                Left,   //!< Places the title on the left side of the title bar
                Center, //!< Places the title in the middle of the title bar
                Right   //!< Places the title on the right side of the title bar
            };

            /// Title buttons (use bitwise OR to combine)
            enum TitleButton{
                None     = 0,      //!< No buttons
                Close    = 1 << 0, //!< Include a close button
                Maximize = 1 << 1, //!< Include a maximize button
                Minimize = 1 << 2  //!< Include a minimize button
            };

            /**
             * @brief Construct a child window
             * @param title Title of the window
             * @param titleButtons Title buttons
             */
            explicit ChildWindow(const std::string& title = "",
                 unsigned int titleButtons = TitleButton::Close);

            /**
             * @brief Set the child window renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the button is displayed. The window
             * has a default renderer which can be manipulated using the
             * @see getRenderer() function
             */
            void setRenderer(std::shared_ptr<ChildWindowRenderer> renderer);

            /**
             * @brief Get the child window renderer
             * @return The child window  renderer
             *
             * The renderer gives access to functions that determine how the
             * window is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             */
            std::shared_ptr<ChildWindowRenderer> getRenderer();

            /**
             * @brief Set the client size of the child window
             * @param size New size of the child window contents
             *
             * This sets the size of the child window excluding the title
             * bar and the borders.
             */
            void setClientSize(Dimensions size);

            /**
             * @brief Get the client size of the child window
             * @return Size of the child window contents
             *
             * This is the size of the child window excluding the title bar and
             * the borders
             */
            Dimensions getClientSize() const;

            /**
             * @brief Sets the maximum size of the child window
             * @param size New maximum size of the child window
             *
             * This function sets the maximum size of the entire window,
             * including borders and titlebar. If the window is larger than
             * the new maximum size, it will automatically be shrunk
             */
            void setMaximumSize(Dimensions size);

            /**
             * @brief Get the maximum size of the child window
             * @return Maximum size of the child window
             *
             * This size includes the title bar and the borders
             */
            Dimensions getMaximumSize() const;

            /**
             * @brief Sets the minimum size of the child window
             * @param size New minimum size of the child window
             *
             * This function sets the minimum size of the entire window,
             * including borders and titlebar. If the window is smaller
             * than the new minimum size, it will automatically be enlarged
             */
            void setMinimumSize(Dimensions size);

            /**
             * @brief Get the minimum size of the child window
             * @return Minimum size of the child window
             *
             * This size includes the title bar and the borders
             */
            Dimensions getMinimumSize() const;

            /**
             * @brief Set the title that is displayed in the title bar of the
             *         child window
             * @param title New title for the child window
             */
            void setTitle(const std::string& title);

            /**
             * @brief Get the title that is displayed in the title bar of the
             *          child window
             * @return Title of the child window
             */
            std::string getTitle() const;

            /**
             * @brief Set the character size of the title
             * @param size The new title text size
             *
             * If the size is set to 0 then the character size is determined by
             * the height of the title bar
             */
            void setTitleTextSize(unsigned int size);

            /**
             * @brief Get the character size of the title
             * @return The current title text size
             */
            unsigned int getTitleTextSize() const;

            /**
             * @brief Set the title alignment
             * @param alignment Alignment to be set
             */
            void setTitleAlignment(TitleAlignment alignment);

            /**
             * @brief Get the title alignment
             * @return The title alignment
             */
            TitleAlignment getTitleAlignment() const;

            /**
             * @brief Set the title buttons
             * @param buttons Title buttons to set
             *
             * By default ChildWindows only display a close button.
             * The following example gives the ChildWindow both a minimize and
             * close button.
             * @code
             * childWindow->setTitleButtons(ChildWindow::TitleButtons::Minimize
             *      | ChildWindow::TitleButtons::Close);
             * @endcode
             */
            void setTitleButtons(unsigned int buttons);

            /**
             * @brief Try to close the window
             *
             * This will trigger the onClosing event. If a callback function
             * for this event sets the abort parameter to true then the window
             * will remain open. Otherwise the onClose event is triggered and
             * the window is removed from its parent.
             *
             * If you want to close the window without those callbacks being
             * triggered then you need to use the @see destroy() function
             */
            void close();

            /**
             * @brief Close the window
             *
             * This function is equivalent to removing the window from its
             * parent. If you want to be receive a callback and have the
             * ability to abort the operation then you should use the close()
             * function instead
             */
            void destroy();

            /**
             * @brief Set whether the child window can be resized by dragging
             *          its borders or not
             * @param resizable True to make window resizable, otherwise false
             */
            void setResizable(bool resizable = true);

            /**
             * @brief Check if window is resizable or not
             * @return True if window is resizable, otherwise false
             */
            bool isResizable() const;

            /**
             * @brief Set whether the child window can be moved by dragging
             *        its title bar or not
             * @param draggable True to make window draggable, otherwise false
             *
             * A draggable window can be moved by dragging its title bar and one
             * that is not will remain locked in place. @note Locking the
             * position only affects user interaction, the setPosition function
             * will still move the window.
             */
            void setDraggable(bool draggable);

            /**
             * @brief Check if window is draggable or not
             * @return True if draggable, otherwise false
             */
            bool isDraggable() const;

            /**
             * @brief Set whether the child window should be kept inside its
             *          parent or not
             * @param enabled True to keep window inside parent, otherwise false
             *
             * By default, thw window can be moved outside of its parent
             */
            void setKeepInParent(bool enabled = true);

            /**
             * @brief Check whether the child window is kept inside its parent
             *         or not
             * @return True if window is kept inside parent, otherwise false
             */
            bool isKeptInParent() const;

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
             * @param height The hieght of teh widget
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
             * @return Elements text content
             */
            std::string getText() const override;

            /**
             * @brief Set the character size of the widget's text
             * @param charSize New character size
             *
             * The default character size is 30
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
             * @brief Hide widget from a render target
             */
            void hide() override;

            /**
             * @brief Show a hidden widget
             *
             * This function will reveal the widget that was hidden prior to
             * function call. Calling this function on an object that is not
             * hidden has no effect
             */
            void show() override;

            /**
             * @brief Check is the widget is hidden or not
             * @return True if the widget is hidden, otherwise false
             */
            bool isHidden() const override;

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
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Rotate the widget
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the widget,
             * unlike setRotation() which overwrites it
             */
            void rotate(float angle) override;

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
             * @brief Add a widget to the container
             * @param widgetPtr Widget to be added
             * @param widgetName Unique name of the widget
             * @return True if the widget was added to the container or false
             *         if the container already has a widget with the same name
             *         as the specified widget name
             *
             * The name of the widget must not contain whitespaces
             */
             bool addWidget(std::shared_ptr<IWidget> widgetPtr,
                const std::string &widgetName) override;

            /**
             * @brief Get a widget in the container
             * @param widgetName Name of the widget to retrieve
             * @return Pointer to the specified widget or a nullptr if the
             *         container does not have a widget with the specified
             *         name
             *
             * The container will first search for widgets that are direct
             * children of it, but when none of the child widgets match the
             * given name, a recursive search will be performed.
             */
            std::shared_ptr<IWidget> getWidget(const std::string &widgetName)
            const override;

            /**
             * @brief Get a list of all widgets in the container
             * @return A vector of all widgets in the container
             */
            const std::vector<IWidget> &getWidgets() const override;

            /**
             * @brief Remove a widget from the container
             * @param widget Name of the widget to be removed from the container
             * @return True if the widget was removed or false if the widget
             *         does not exist in the container
             */
            bool removeWidget(const std::string &widget) override;

            /**
             * @brief Remove all widgets from the container
             */
            void removeAllWidgets() override;

            /**
             * @brief Place a widget before all other widgets, to the front
             *        of the z-order
             * @param widget The widget that should be moved to the front
             */
            void moveWidgetToFront(std::shared_ptr<IWidget> widget) override;

            /**
            * @brief Place a widget behind all other widgets, to the back
            *        of the z-order
            * @param widget The widget that should be moved to the front
            */
            void moveWidgetToBack(std::shared_ptr<IWidget> widget) override;

            /**
             * @brief Place a widget one step forward in the z-order
             * @param widget The widget that should be moved one step forward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t
            moveWidgetForward(std::shared_ptr<IWidget> widget) override;

            /**
             * @brief Place a widget one step backwards in the z-order
             * @param widget The widget that should be moved one step backward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t
            moveWidgetBackward(std::shared_ptr<IWidget> widget) override;

            /**
             * @brief Get the currently focused widget inside the container
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note If the focused widget is a container, then a pointer to
             * the container is returned rather than a pointer to the focused
             * widget inside that container. @see getFocusedLeaf() should be
             * used to get the widget that is focused inside a container
             */
            std::shared_ptr<IWidget> getFocusedWidget() const override;

            /**
             * @brief Get the currently focused widget inside the container
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note Unlike @see getFocusedWidget() which returns a pointer to
             * a container when the focused widget is a child of another
             * container within the container, this function will always return
             * the focused widget regardless of whether its a direct child of
             * the container or not
             */
            std::shared_ptr<IWidget> getFocusedLeaf() const override;

            /**
             * @brief Get a widget at a given position
             * @param pos The position of the widget relative to the container
             *          view
             * @return Pointer to the widget at the specified position or a
             *         nullptr if there is no widget at that position
             */
            std::shared_ptr<IWidget>
            getWidgetAtPosition(Position pos) const override;

            /**
             * @brief Focus the next widget in the container
             * @param recursive Set true to focus next widget when the currently
             *        focused widget is a container or false to focus the sibling
             *        of that container
             * @return True if the next widget was focused, otherwise false
             */
            bool focusNextWidget(bool recursive) override;

            /**
             * @brief Focus the previous widget in the container
             * @param recursive Set true to focus next widget when the currently
             *        focused widget is a container or false to focus the sibling
             *        of that container
             * @return True if the next widget was focused, otherwise false
             */
            bool focusPreviousWidget(bool recursive) override;

            /**
             * @internal
             * @brief Get the internal pointer to a third party widget object
             * @return The internal pointer to a third party widget object
             *
             * @warning This function is intended for internal use only and
             * must never be called under any circumstance
             */
            std::shared_ptr<tgui::Widget> getInternalPtr() override;

        private:
            /**
             * @brief Initialize events
             *
             * These events will notify event listeners about an internal state
             * change of the object when that state changes
             */
            void initEvents();

        private:
            //Widgets container
            std::unordered_map<std::string, std::shared_ptr<IWidget>> widgets_;
            //Pointer to third party window
            std::shared_ptr<tgui::ChildWindow> window_;
            //Renderer for this layout
            std::shared_ptr<ChildWindowRenderer> renderer_;
            //How long the layout takes before its completely hidden or shown
            static const int fadeAnimDuration_ = 100;
        };
    }
}

#endif
