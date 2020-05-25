/**
 * @brief UI layout that stacks panel vertically or horizontally
 */

#ifndef STACKPANEL_H
#define STACKPANEL_H

#include "Panel.h"

namespace Gui {
    enum class Orientation{
        Vertical,
        Horizontal
    };

    class StackPanel final : public Panel{
    public:
        /**
         * @brief Create a new Stack Panel
         * @param orientation Specify how the UI elements
         *        are stacked to each other
         *
         * The created stack panel is located at (0, 0)
         */
        explicit StackPanel(Orientation orientation);

        /**
         * @brief Create a new Stack Panel object
         * @param x X coordinate of the panel
         * @param y Y coordinate of the panel
         * @param orientation Specify how the UI elements
         *        are stacked to each other
         */
        StackPanel(float x, float y, Orientation orientation);

        /**
         * @brief Add a UI element to the panel
         * @param alias Name that can be used to refer to element
         * @param guiElement Element to be added
         */
        void addElement(const std::string &alias,
                std::unique_ptr<UIElement> guiElement) override;

    private:
        /**
         * @brief Initialize stack panel events
         */
        void initEvents();

        /**
         * @brief Set the position of a UI element relative to
         *        another UI element
         * @param uiElem UI element to position relative to another
         * @param refUIElem Reference UI element
         *
         * The element whose position is changed will have the
         * same orientation (vertical or horizontal) as the
         * element which is used as reference
         */
        void setElemPosRelativeTo(const std::unique_ptr<UIElement> &uiElem,
              const std::unique_ptr<UIElement> &refUIElem) const;

        /**
         * @brief Fit element to panel
         * @param uiElem Element to fit to panel
         *
         * This function will adjust the dimensions  of an element
         * (depending on the orientation of the panel) such that it
         * fits the panel. If the orientation of the panel is vertical,
         * the width of the element will be adjusted whereas the height
         * will be adjusted if the orientation if horizontal
         */
        void fitElementToPanel(const std::unique_ptr<UIElement> &uiElem);

    private:
        //Panel orientation state
        Orientation orientation_;
    };
}

#endif
