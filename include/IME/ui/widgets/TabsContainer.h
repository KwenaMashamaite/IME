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

#ifndef IME_TABSCONTAINER_H
#define IME_TABSCONTAINER_H

#include "IME/Config.h"
#include "IME/ui/widgets/Widget.h"
#include "IME/ui/widgets/Panel.h"
#include "IME/ui/renderers/TabsRenderer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief A container widget for a Tabs widget
         *
         * This widget can hold multiple panels which are displayed
         * one panel at a time. The widget uses Tabs to switch
         * between panels
         *
         * If you are looking for Tabs without a panel, check out the
         * Tabs class
         */
        class IME_API TabsContainer : public Widget {
        public:
            using Ptr = std::unique_ptr<TabsContainer>; //!< Unique widget pointer
            using ConstPtr = std::unique_ptr<const TabsContainer>; //!< Const unique widget pointer

            /**
             * @brief Copy constructor
             */
            TabsContainer(const TabsContainer&);

            /**
             * @brief Copy assignment operator
             */
            TabsContainer& operator=(const TabsContainer&);

            /**
             * @brief Move constructor
             */
            TabsContainer(TabsContainer&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            TabsContainer& operator=(TabsContainer&&) noexcept;

            /**
             * @brief Create a new TabsContainer widget
             * @param width Width of the panel relative to the size of its 
             *        parent
             * @param height Height of the panel relative to the size of its
             *        parent
             * @return The new TabsContainer
             * 
             * * The relative size is specified in percentages as shown:
             * 
             * @code
             * TabsContainer::create({"50%", "20%"});
             * @endcode
             * 
             * By default, the new panel is the same size as its parent
             */
            static TabsContainer::Ptr create(const std::string& width = "100%",
                const std::string& height = "100%");

            /**
             * @brief Create a copy of this widget
             * @return A copy of this widget
             *
             * @see clone
             */
            TabsContainer::Ptr copy() const;

            /**
             * @brief Get the tabs renderer
             * @return The tabs renderer
             *
             * The renderer gives access to functions that determine how the
             * container is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            TabsRenderer* getRenderer();
            const TabsRenderer* getRenderer() const;

            /**
             * @brief Set the height of the tabs part of the widget
             * @param height New height of the tabs part of the widget
             */
            void setTabsHeight(float height);

            /**
             * @brief Add a panel
             * @param panel Panel to be added
             * @param text Text for the container
             * @param select True to immediately select the panel, otherwise
             *        false
             * @return Pointer to the panel after its added to the panel
             *
             * The panel is added after the panel that was added during
             * the last call to this function
             *
             * By default, the panel is selected after being added
             */
            Panel* addPanel(Panel::Ptr panel, const std::string& text, bool select = true);

            /**
             * @brief Insert a panel between other panels
             * @param panel Panel to be added
             * @param text Text for the container
             * @param index Index where the panel should be inserted
             * @param select True to immediately select the panel, otherwise
             *               false
             * @return True if the panel was inserted or false if the given
             *         index is out of bounds
             *
             * By default, the panel is selected after successful insertion
             * 
             * @warning This function os experimental
             */
            bool insertPanel(Panel::Ptr panel, const std::string& text,
                std::size_t index, bool select = true);

            /**
             * @brief Remove a panel from the container
             * @param panel Panel to remove
             */
            void removePanel(Panel* panel);

            /**
             * @brief Select a panel
             * @param index Index of the panel to select
             */
            void select(std::size_t index);

            /**
             * @brief Get the number of panel in the container
             * @return The current number of panels in the container
             */
            std::size_t getPanelCount() const;

            /**
             * @brief Get the index of a given panel
             * @param panel Panel to get the index for
             * @return The index of the panel or -1 if the panel does not
             *         exist in the container
             */
            int getIndex(const Panel* panel);

            /**
             * @brief Get the currently selected panel
             * @return The panel that is selected or a nullptr if no panel
             *         is selected
             */
            Panel* getSelected();

            /**
             * @brief Get the index of the currently selected panel
             * @return The index of the selected panel or -1 if not panel
             *         is selected
             */
            int getSelectedIndex() const;

            /**
             * @brief Get a panel with a given index
             * @param index The index of the panel to retrieve
             * @return Panel with the given index or a nullptr if the index
             *         is out of bounds
             */
            Panel* getPanel(int index) const;

            /**
             * @brief Get the text of a container
             * @param index Index of the container to get the index of
             * @return The text on the container or an empty string if the index
             *         is out of bounds
             *
             * The index of the first container is 0
             */
            std::string getTabText(std::size_t index) const;

            /**
             * @brief Set the text of a container
             * @param index The index of the container whose text is to be ste
             * @param text The new text of the container
             * @return True if the text was successfully changed or false
             *         if the index is out of bounds
             *
             * The index of the first container is 0
             */
            bool changeTabText(std::size_t index, const std::string& text);

            /**
             * @brief Make a copy of the widget
             * @return A copy of the widget
             *
             * You should use this function if you don't care about the type
             * of the widget, otherwise use the widgets copy function for
             * copying purposes
             */
            Widget::Ptr clone() const override;

            /**
             * @brief Get the type of the container
             * @return The type of the container
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~TabsContainer() override;

        private:
            /**
             * @brief Constructor
             * @param width Width of the container relative to the size of its
             *        parent
             * @param height Height of the container relative to the size of its
             *        parent
             *
             * The relative size is specified in percentages as shown:
             *
             * @code
             * TabsContainer({"50%", "20%"});
             * @endcode
             *
             * By default, the container is the same size as its parent
             */
            explicit TabsContainer(const std::string& width = "100%",
                const std::string& height = "100%");

            /**
             * @brief Initialize events emitted by the widget
             */
            void initEvents();

        private:
            class TabsContainerImpl;
            std::unique_ptr<TabsContainerImpl> pimpl_;
        };
    }
}

/**
 * @class ime::ui::TabsContainer
 * @ingroup ui
 *
 * <table>
 * <caption>Events generated by ime::ui::TabsContainer </caption>
 * <tr><th> Name             <th> Argument Type          <th> Description
 * <tr><td> selectionChange  <td> int                    <td> Selection of the tab container changed.
 *                                                            Parameter = Index of the panel with the selection
 * </table>
 *
 * Event usage example:
 * @code
 * tabsContainer.on("selectionChange", ime::Callback<int>([](int index) {
 *      std::cout << "Currently displaying panel at index " << index << "\n";
 * }));
 * @endcode
 */

#endif //IME_TABSCONTAINER_H
