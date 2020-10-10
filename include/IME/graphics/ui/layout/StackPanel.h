/**
 * @brief UI layout that stacks panel vertically or horizontally
 */

#ifndef STACKPANEL_H
#define STACKPANEL_H

#include "Panel.h"
#include "IME/graphics/ui/elements/Label.h"

namespace IME {
    namespace Graphics::UI {
        class StackPanel final : public Panel{
        public:
            /***
             * @brief Panel orientation
             */
            enum class Orientation{
                Vertical,
                Horizontal
            };

            /**
             * @brief Create a new Stack Panel
             * @param orientation Specify how the UI elements are
             *        stacked to each other
             * The default position is (0, 0)
             */
            explicit StackPanel(Orientation orientation);

            /**
             * @brief Create a new Stack Panel object
             * @param x X coordinate of the panel
             * @param y Y coordinate of the panel
             * @param orientation Specify how the UI elements are
             *        stacked to each other
             */
            StackPanel(float x, float y, Orientation orientation);

            /**
             * @brief Set the panel title
             * @param title Title to set
             */
            void setTitle(const std::string& title);

            /**
             * @brief Get the title of the panel
             * @return The title of the panel
             */
            std::string getTitle() const;

            /**
             * @brief Add a UI element to the panel
             * @param alias Name that can be used to refer to element
             * @param uiElement Element to be added
             */
            bool addElement(const std::string &alias,
                    std::unique_ptr<UIElement> uiElement) override;

            /**
             * @brief Render the panel and it's UI elements on a render target
             * @param renderTarget Render target to draw panel on
             */
            void draw(Window &renderTarget) override;

        private:
            /**
             * @brief Initialize stack panel events
             *
             * This function will create the stack panel events and attach
             * default listeners to those events if any
             */
            void initEvents();

            /**
             * @brief Set the position of a UI element relative to another
             *        UI element
             * @param uiElem UI element to position relative to another
             * @param refUIElem UI element to use as reference
             *
             * The element whose position is changed will have the same
             * orientation (vertical or horizontal) as the element which
             * is used as reference. This means that, when the orientation
             * is vertical the UI element will be positioned directly below
             * the reference UI element, otherwise the UI element will be
             * positioned directly on the right of the reference element
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
            //Stack panel title
            Label title_;
            //Panel orientation state
            Orientation orientation_;
        };
    }
} // namespace IME

#endif
