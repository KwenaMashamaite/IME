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

#ifndef IME_IBOXLAYOUT_H
#define IME_IBOXLAYOUT_H

#include "IME/Config.h"
#include "IME/ui/widgets/WidgetContainer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Interface for box layouts
         */
        class IME_API IBoxLayout : public WidgetContainer {
        public:
            using Ptr = std::shared_ptr<IBoxLayout>; //!< Shared widget pointer

            /**
             * @brief Insert a widget to the container
             * @param index Where the widget should be inserted
             * @param widget Pointer to the widget to be inserted
             * @param widgetName Unique Name of the widget
             *
             * The name must be unique and contain no whitespaces because the
             * container cannot store two distinct widgets with the same name
             *
             * @note If @a index is too high, the widget will simply be
             * added at the end of the list
             */
            virtual void insertWidget(std::size_t index, std::shared_ptr<Widget> widget,
                const std::string& widgetName) = 0;

            /**
             * @brief Remove a widget from the container
             * @param index Position of the widget to be removed
             * @return True if the widget was removed, or false if the index is
             *         invalid
             */
            virtual bool removeWidgetAt(std::size_t index) = 0;

            /**
             * @brief Add an extra space after the last widget
             * @param ratio Ratio to determine the size compared to other widgets
             *
             * The space will act as an invisible non-interactable widget, the
             * ratio will be part of the total ratio of all widgets
             */
            virtual void addSpace(float ratio) = 0;

            /**
             * @brief Insert an extra space between widgets
             * @param index Index of the widget in the container
             * @param ratio Ratio to determine the size compared to other widgets
             *
             * The ratio will be part of the total ratio of all widgets.
             */
            virtual void insertSpace(std::size_t index, float ratio) = 0;

            /**
             * @brief Set the ratio of a widget
             * @param widget Widget from which the ratio should be changed
             * @param ratio New ratio to determine the size compared to other
             *         widgets
             * @return True if the widget was valid and the ratio was changed,
             *          or false if the widget was not found
             */
            virtual bool setRatio(std::shared_ptr<Widget> widget, float ratio) = 0;

            /**
             * @brief Set the ratio of a widget at a certain index
             * @param index Index of the widget or space
             * @param ratio ew ratio to determine the size compared to other
             *         widgets
             * @return True if the index is valid and the ratio was changed,
             *          otherwise false
             */
            virtual bool setRatio(std::size_t index, float ratio) = 0;

            /**
             * @brief Get the ratio of a widget at a certain index
             * @param widget Widget from which the ratio should be returned
             * @return The ratio of the widget or 0 when the widget was not
             *         found
             */
            virtual float getRatio(std::shared_ptr<Widget> widget) const = 0;

            /**
             * @brief Get the ratio of a widget at a certain index
             * @param index Index of the widget from which the ratio should be
             *         returned
             * @return The ratio of the widget or 0 when the widget was not
             *         found
             */
            virtual float getRatio(std::size_t index) const = 0;

        protected:
            /**
             * @brief Constructor
             * @param widgetImpl Widget implementation
             */
            IBoxLayout(std::unique_ptr<priv::IWidgetImpl> widgetImpl);
        };
    }
}

#endif
