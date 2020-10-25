
#ifndef IBOXLAYOUT_H
#define IBOXLAYOUT_H

#include "IContainer.h"

namespace IME {
    namespace Graphics::UI {
        class IBoxLayout : public IContainer {
        public:
            /**
             * @brief Insert a widget to the container
             * @param index Where the widget should be inserted
             * @param widget Pointer to the widget to be inserted
             * @param widgetName Name of the widget
             *
             * The widget name must be set if the widget is to be retrieved at
             * a later time. In addition, the name must not contain whitespaces
             * @note If the index is too high, the widget will simply be added
             * at the end of the list
             */
            virtual void insertWidget(std::size_t index, std::shared_ptr<IWidget> widget,
                const std::string& widgetName = "") = 0;

            /**
             * @brief Remove a single widget that was added to the container
             * @param index Position of the widget to be removed
             * @return True if the widget was removed, or false if the index is
             *          invalid
             */
            virtual bool removeWidgetAt(std::size_t index) = 0;

            /**
             * @brief Get the widget at a certain position
             * @param index Position of the widget to retrieve
             * @return Widget at the given position or nullptr if the index is
             *         invalid
             */
            virtual std::shared_ptr<IWidget> getWidgetAt(std::size_t index) const = 0;

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
             * The space will act as an invisible non-interactable widget, the
             * ratio will be part of the total ratio of all widgets.
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
            virtual bool setRatio(std::shared_ptr<IWidget> widget, float ratio) = 0;

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
            virtual float getRatio(std::shared_ptr<IWidget> widget) const = 0;

            /**
             * @brief Get the ratio of a widget at a certain index
             * @param index Index of the widget from which the ratio should be
             *         returned
             * @return The ratio of the widget or 0 when the widget was not
             *         found
             */
            virtual float getRatio(std::size_t index) const = 0;
        };
    }
}

#endif
