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

#ifndef IME_TABS_H
#define IME_TABS_H

#include "IME/Config.h"
#include "IME/ui/widgets/Widget.h"
#include "IME/ui/renderers/TabsRenderer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief A Tabs widget
         *
         * This widget can hold multiple tabs. If you want Tabs with
         * panels, checkout the TabsContainer class
         */
        class IME_API Tabs : public Widget {
        public:
            using sharedPtr = std::shared_ptr<Tabs>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const Tabs>; //!< const shared widget pointer

            /**
             * @brief Move constructor
             */
            Tabs(Tabs&&);

            /**
             * @brief Move assignment operator
             */
            Tabs& operator=(Tabs&&);

            /**
             * @brief Create a new tabs widget
             * @return The new tabs widget
             */
            static sharedPtr create();

            /**
             * @brief Create a copy of another tabs
             * @param other The tabs to copy
             * @param shareRenderer True if the new tabs should have the
             *          same renderer as the copied tabs
             * @return The new tabs widget
             *
             * When the tabs share a renderer, changes in a render
             * property of one of the tabs automatically reflect on
             * the other tabs, otherwise each tabs has its own renderer
             * and changes in render properties are isolated to the specific
             * tabs.
             *
             * @note when the tabs don't share a render, the renderer of
             * the new tabs widget will initially have the properties of
             * the copied tabs such that the two look the same after this
             * function returns
             *
             * By default, the tabs share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Get the tabs renderer
             * @return The tabs renderer
             *
             * The renderer gives access to functions that determine how the
             * tab is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            TabsRenderer::sharedPtr getRenderer();
            const TabsRenderer::sharedPtr getRenderer() const;

            /**
             * @brief Set whether or not the tabs auto-size
             * @param autoSize True to enable auto-size, otherwise false
             *
             * When the tabs are in auto-size mode, the width of the tabs
             * will be dependent on the text which they contain. Otherwise,
             * all tabs have an equal width to fill the size of the widget
             *
             * The tabs are auto-sized by default
             */
            void setAutoSize(bool autoSize);

            /**
             * @brief Check whether if the tabs are auto-sized or not
             * @return True if auto-sized, otherwise false
             *
             * @see setAutoSize
             */
            bool getAutoSize() const;

            /**
             * @brief Add a new tab
             * @param text The text of the tab that will be drawn on top of it
             * @param select True to immediately select tab, otherwise false
             * @return The index of the tab in the list
             *
             * @warning The index returned by this function may be invalid
             *          when a tab is removed
             */
            std::size_t add(const std::string& text, bool select = true);

            /**
             * @brief Insert a new tab between other tabs
             * @param index The index where the tab is inserted
             * @param text The text of the tab that will be drawn on top of it
             * @param select True to immediately select tab, otherwise false
             *
             * @a index of 0 means before the first tab and 1 means behind
             * the first tab
             */
            void insert(std::size_t index, const std::string& text, bool select = true);

            /**
             * @brief Get the text of a tab
             * @param index Index of the tab to get the text of
             * @return The text of the specified tab or an empty string if the
             *         index is invalid
             *
             * The first tab has an index of 0
             */
            std::string getText(std::size_t index) const;

            /**
             * @brief Change the text of a tab
             * @param index Index of the tab whose text is to be changed
             * @param text The new tab text
             * @return True if the text was successfully changed or false if
             *         the index is invalid
             */
            bool changeText(std::size_t index, const std::string& text);

            /**
             * @brief Select tab with a given text
             * @param text The text of the tab t select
             * @return True if the tab was selected or false if the tab with
             *         @a text doesn't exists or the tab is hidden or disabled
             *
             * If there are multiple tabs with the same text, then the first
             * one will be selected. When false is returned, the selected tab
             * will be deselected
             *
             * @see select(int)
             */
            bool select(const std::string& text);

            /**
             * @brief Select a tab with a given index
             * @param index Index of the tab to be selected
             * @return True if the tab was selected or false if the index is
             * invalid or the tab is hidden or disabled
             *
             * When false is returned, the selected tab will be deselected
             *
             * @see select(const std::string&)
             */
            bool select(std::size_t index);

            /**
             * @brief Deselect the selected tab
             */
            void deselect();

            /**
             * @brief Remove a tab with a given text
             * @param text The text on the tab to remove
             * @return True if the tab was removed or false if there is no
             *         tab with the given text
             *
             * @see remove(std::size_t)
             */
            bool remove(const std::string& text);

            /**
             * @brief Remove a tab with a given index
             * @param index The index of the tab to remove
             * @return True if the tab was removed or false if the index is
             *         invalid
             */
            bool remove(std::size_t index);

            /**
             * @brief Remove all tabs
             */
            void removeAll();

            /**
             * @brief Get the text that is drawn on the currently selected tab
             * @return The texts on the selected tab or an empty string if
             *         no tab is currently selected
             */
            std::string getSelected() const;

            /**
             * @brief Get the index of the currently selected tab
             * @return The index of the selected tab or -1 if not tab is
             *         currently selected
             *
             * @warning The index returned by this function may be invalid
             *          if a tab is removed
             */
            int getSelectedIndex() const;

            /**
             * @brief Hide or show a tab
             * @param index Index of the tab to hide or show
             * @param visible True to show or false to hide
             */
            void setTabVisible(std::size_t index, bool visible);

            /**
             * @brief Check if a tab is visible or not
             * @param index Index of the tab to be checked
             * @return True if the tab is visible or false if the tab is not
             *         visible or the index is invalid
             */
            bool isTabVisible(std::size_t index) const;

            /**
             * @brief Enable or disable a tab
             * @param index Index of the tab t enable or disable
             * @param enabled True to enable or false to disable
             */
            void setTabEnabled(std::size_t index, bool enabled);

            /**
             * @brief Check whether a tab is enabled or not
             * @param index The index of the tab to be checked
             * @return True if the tab is enabled, otherwise false
             */
            bool isTabEnabled(std::size_t index) const;

            /**
             * @brief Set the height of the tabs
             * @param height New height of the tabs
             *
             * When the tabs are auto-sizing, this function allows changing
             * the width of the tabs without setting a fixed width like calling
             * setSize would do
             *
             * @see setAutoSize
             */
            void setTabHeight(float height);

            /**
             * @brief Set the maximum tab width of the tabs
             * @param maximumWidth Maximum width of a single tab
             *
             * This property only has effect when the tabs are auto-sizing.
             * If the text on the tab is longer than this width then it will
             * be cropped to fit inside the tab.
             *
             * By default, the maximum width is 0 which means that there is
             * no limitation
             *
             * @see setAutoSize
             */
            void setMaximumTabWidth(float maximumWidth);

            /**
             * @brief Get the maximum tab width of the tabs
             * @return The maximum tab width of a single tab
             *
             * This property only has effect when the tabs are auto-sizing.
             * If the text on the tab is longer than this width then it will
             * be cropped to fit inside the tab.
             *
             * By default, the maximum width is 0 which means that there is no
             * limitation
             *
             * @see setAutoSize
             */
            float getMaximumTabWidth() const;

            /**
             * @brief Set the minimum width of the tabs
             * @param minimumWidth Minimum width of a single tab
             *
             * This property only has effect when the tabs are auto-sizing.
             * Every tab is at least as wide as this minimum or twice the
             * distance to side
             *
             * @see setAutoSize
             */
            void setMinimumTabWidth(float minimumWidth);

            /**
             * @brief Get teh minimum tab width of the tabs
             * @return Minimum width of a single tab
             *
             * This property only has effect when the tabs are auto-sizing.
             * Every tab is at least as wide as this minimum or twice the
             * distance to side
             */
            float getMinimumTabWidth() const;

            /**
             * @brief Get the number of tabs
             * @return The number of tabs
             */
            std::size_t getTabsCount() const;

            /**
             * @brief Get the type of the tab
             * @return The type of the tab
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~Tabs();

        private:
            /**
             * @brief Constructor
             */
            Tabs();

        private:
            class TabsImpl;
            std::unique_ptr<TabsImpl> pimpl_;
        };
    }
}

#endif //IME_TABS_H
