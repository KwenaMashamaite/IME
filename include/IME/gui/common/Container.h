#ifndef CONTAINER_H
#define CONTAINER_H

#include "IME/common/Definitions.h"
#include <string>

namespace IME {
    using Definitions::Position;
    using Definitions::Dimensions;

    namespace Gui {
        class Container {
        public:
            /**
             * @brief Set the title
             * @param title Title to set
             */
            void setTitle(const std::string &title);

            void setTitleFont(const std::string &font);

            void setTitleTextSize(unsigned int textSize);

            void remove(const std::string& uiElemName);

            void setPosition(int x, int y);

            void setPosition(const Position &position);

            void setDimension(const Dimensions dimensions);

            Position getPosition() const;

            Dimensions getDimensions() const;

        };
    } // namespace Gui
} // namespace IME

#endif
