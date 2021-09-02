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

#ifndef IME_HORIZONTALLAYOUT_H
#define IME_HORIZONTALLAYOUT_H

#include "IME/Config.h"
#include "IME/ui/widgets/IBoxLayout.h"
#include "IME/ui/renderers/BoxLayoutRenderer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief A widget container stores other widgets inside of it side by
         *        side horizontally
         * 
         * The widget automatically resizes children to fit the entire 
         * size of the container
         */
        class IME_API HorizontalLayout : public IBoxLayout {
        public:
            using Ptr = std::unique_ptr<HorizontalLayout>;            //!< Unique widget pointer
            using ConstPtr = std::unique_ptr<const HorizontalLayout>; //!< const Unique widget pointer

            /**
             * @brief Copy constructor
             */
            HorizontalLayout(const HorizontalLayout&);

            /**
             * @brief Copy assignment operator
             */
            HorizontalLayout& operator=(const HorizontalLayout&);

            /**
             * @brief Move constructor
             */
            HorizontalLayout(HorizontalLayout&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            HorizontalLayout& operator=(HorizontalLayout&&) noexcept;

            /**
             * @brief Create a new HorizontalLayout widget
             * @param width Width of the panel relative to the size of its parent
             * @param height Height of the panel relative to the size of its parent
             * @return The new HorizontalLayout
             * 
             * * The relative size is specified in percentages as shown:
             * 
             * @code
             * HorizontalLayout::create({"50%", "20%"});
             * @endcode
             * 
             * By default, the new panel is the same size as its parent
             */
            static HorizontalLayout::Ptr create(const std::string& width = "100%",
                const std::string& height = "100%");

            /**
             * @brief Create a copy of this widget
             * @return A copy of this widget
             *
             * @see clone
             */
            HorizontalLayout::Ptr copy() const;

            /**
             * @brief Get the layout renderer
             * @return The layout renderer
             *
             * The renderer gives access to functions that determine how the
             * layout is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            BoxLayoutRenderer* getRenderer();
            const BoxLayoutRenderer* getRenderer() const;

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
             * @brief Get the type of the layout
             * @return The type of the layout
             */
            std::string getWidgetType() const override;

            /**
             * @brief Insert a widget to the container
             * @param index Where the widget should be inserted
             * @param widget Pointer to the widget to be inserted
             * @param name Name of the widget
             *
             * The name must be unique and contain no whitespaces because the
             * container cannot store two distinct widgets with the same name
             *
             * @note If @a index is too high, the widget will simply be
             * added at the end of the list
             */
            void insertWidget(std::size_t index, Widget* widget,
                const std::string &name) override;

            /**
             * @brief Remove a single widget that was added to the container
             * @param index Position of the widget to be removed
             * @return True if the widget was removed, or false if the index is
             *          invalid
             */
            bool removeWidgetAt(std::size_t index) override;

            /**
             * @brief Add an extra space after the last widget
             * @param ratio Ratio to determine the size compared to other widgets
             *
             * The space will act as an invisible non-interactable widget, the
             * ratio will be part of the total ratio of all widgets
             */
            void addSpace(float ratio) override;

            /**
             * @brief Insert an extra space between widgets
             * @param index Index of the widget in the container
             * @param ratio Ratio to determine the size compared to other widgets
             *
             * The space will act as an invisible non-interactable widget, the
             * ratio will be part of the total ratio of all widgets.
             */
            void insertSpace(std::size_t index, float ratio) override;

            /**
             * @brief Set the ratio of a widget
             * @param widget Widget from which the ratio should be changed
             * @param ratio New ratio to determine the size compared to other
             *         widgets
             * @return True if the widget was valid and the ratio was changed,
             *          or false if the widget was not found
             */
            bool setRatio(Widget* widget, float ratio) override;

            /**
             * @brief Set the ratio of a widget at a certain index
             * @param index Index of the widget or space
             * @param ratio ew ratio to determine the size compared to other
             *         widgets
             * @return True if the index is valid and the ratio was changed,
             *          otherwise false
             */
            bool setRatio(std::size_t index, float ratio) override;

            /**
             * @brief Get the ratio of a widget at a certain index
             * @param widget Widget from which the ratio should be returned
             * @return The ratio of the widget or 0 when the widget was not
             *         found
             */
            float getRatio(const Widget* widget) const override;

            /**
             * @brief Get the ratio of a widget at a certain index
             * @param index Index of the widget from which the ratio should be
             *         returned
             * @return The ratio of the widget or 0 when the widget was not
             *         found
             */
            float getRatio(std::size_t index) const override;

            /**
             * @brief Destructor
             */
            ~HorizontalLayout() override;

        private:
            /**
             * @brief Constructor
             * @param width Width of the layout relative to the size of its parent
             * @param height Height of the layout relative to the size of its
             *        parent
             *
             * The relative size is specified in percentages as shown:
             *
             * @code
             * HorizontalLayout({"50%", "20%"});
             * @endcode
             *
             * By default, the layout is the same size as its parent
             */
            explicit HorizontalLayout(const std::string& width = "100%", const std::string& height = "100%");

        private:
            class HorizontalLayoutImpl;
            std::unique_ptr<HorizontalLayoutImpl> pimpl_;
        };
    }
}

#endif // IME_HORIZONTALLAYOUT_H
