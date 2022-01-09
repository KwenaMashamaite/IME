////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_CHILDWINDOW_H
#define IME_CHILDWINDOW_H

#include "IME/Config.h"
#include "IME/ui/widgets/WidgetContainer.h"
#include "IME/ui/renderers/ChildWindowRenderer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief A rectangular window that is launched and contained
         *        inside of a parent window
         */
        class IME_API ChildWindow : public WidgetContainer {
        public:
            using Ptr = std::unique_ptr<ChildWindow>; //!< Unique widget pointer
            using ConstPtr = std::unique_ptr<const ChildWindow>; //!< Const unique widget pointer

            /**
             * @brief Title alignments, possible options for the setTitleAlignment function
             */
            enum class TitleAlignment {
                Left,   //!< Places the title on the left side of the title bar
                Center, //!< Places the title in the middle of the title bar
                Right   //!< Places the title on the right side of the title bar
            };

            /**
             * @brief Title buttons (use bitwise OR to combine)
             */
            enum TitleButton {
                None     = 0,      //!< No buttons
                Close    = 1 << 0, //!< Include a close button
                Maximize = 1 << 1, //!< Include a maximize button
                Minimize = 1 << 2  //!< Include a minimize button
            };

            /**
             * @brief Copy constructor
             */
            ChildWindow(const ChildWindow&);

            /**
             * @brief Copy assignment operator
             */
            ChildWindow& operator=(const ChildWindow&);

            /**
             * @brief Move constructor
             */
            ChildWindow(ChildWindow&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            ChildWindow& operator=(ChildWindow&&) noexcept;

            /**
             * @brief Create a child window
             * @param title Title of the window
             * @param titleButtons Title buttons
             * @return The new child window
             */
            static ChildWindow::Ptr create(const std::string& title = "",
                unsigned int titleButtons = TitleButton::Close);

            /**
             * @brief Create a copy of this widget
             * @return A copy of this widget
             *
             * @see clone
             */
            ChildWindow::Ptr copy() const;

            /**
             * @brief Get the child window renderer
             * @return The child window  renderer
             *
             * The renderer gives access to functions that determine how the
             * window is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            ChildWindowRenderer* getRenderer();
            const ChildWindowRenderer* getRenderer() const;

            /**
             * @brief Set the client size of the child window
             * @param size New size of the child window contents
             *
             * This sets the size of the child window excluding the title
             * bar and the borders.
             */
            void setClientSize(Vector2f size);

            /**
             * @brief Get the client size of the child window
             * @return Size of the child window contents
             *
             * This is the size of the child window excluding the title bar and
             * the borders
             */
            Vector2f getClientSize() const;

            /**
             * @brief Sets the maximum size of the child window
             * @param size New maximum size of the child window
             *
             * This function sets the maximum size of the entire window,
             * including borders and title bar. If the window is larger than
             * the new maximum size, it will automatically be shrunk
             */
            void setMaximumSize(Vector2f size);

            /**
             * @brief Get the maximum size of the child window
             * @return Maximum size of the child window
             *
             * This size includes the title bar and the borders
             */
            Vector2f getMaximumSize() const;

            /**
             * @brief Sets the minimum size of the child window
             * @param size New minimum size of the child window
             *
             * This function sets the minimum size of the entire window,
             * including borders and titlebar. If the window is smaller
             * than the new minimum size, it will automatically be enlarged
             */
            void setMinimumSize(Vector2f size);

            /**
             * @brief Get the minimum size of the child window
             * @return Minimum size of the child window
             *
             * This size includes the title bar and the borders
             */
            Vector2f getMinimumSize() const;

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
             * triggered then you need to use the destroy function
             *
             * @see destroy
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
             * @brief Make a copy of this widget
             * @return A copy of this widget
             *
             * You should use this function if you don't care about the type
             * of the widget, otherwise use the widgets copy function
             *
             * @see copy
             */
            Widget::Ptr clone() const override;

            /**
             * @brief Get the type of the window
             * @return The type of the window
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~ChildWindow() override;

        private:
            /**
             * @brief Construct a child window
             * @param title Title of the window
             * @param titleButtons Title buttons
             */
            explicit ChildWindow(const std::string& title = "",
                unsigned int titleButtons = TitleButton::Close);

            /**
             * @brief Initialize events emitted by the widget
             */
            void initEvents();

        private:
            class ChildWindowImpl;
            std::unique_ptr<ChildWindowImpl> pimpl_;
        };
    }
}

/**
 * @class ime::ui::ChildWindow
 * @ingroup ui
 *
 * <table>
 * <caption>Events generated by ime::ui::ChildWindow </caption>
 * <tr><th> Name            <th> Argument Type  <th> Description
 * <tr><td> close           <td> void           <td> The window was closed
 * <tr><td> minimize        <td> void           <td> The window was minimized
 * <tr><td> maximize        <td> void           <td> The window was maximized
 * <tr><td> escapeKeyPress  <td> void           <td> The escape key was pressed while window was focused
 * </table>
 *
 * Usage Example:
 * @code
 * window.on("close", ime::Callback<>([] {
 *      std::cout << "Pop up window closed" << "\n";
 * }));
 * @endcode
 */

#endif // IME_CHILDWINDOW_H
