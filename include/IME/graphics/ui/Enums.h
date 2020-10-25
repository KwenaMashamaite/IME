
#ifndef ENUMS_H
#define ENUMS_H

namespace IME {
    enum class Orientation {
        Horizontal,
        Vertical
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief The horizontal text alignment
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class HorizontalAlignment
    {
        Left,   //!< Put the text on the left side (default)
        Center, //!< Center the text horizontally
        Right   //!< Put the text on the right side (e.g. for numbers)
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief The vertical text alignment
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class VerticalAlignment
    {
        Top ,   //!< Put the text at the top (default)
        Center, //!< Center the text vertically
        Bottom  //!< Put the text at the bottom
    };

    /**
     * @brief Position of the text within the widgets border
     */
    enum class TextAlignment {
        Center,      //!< Center the widget in the cell
        UpperLeft,   //!< Draw the widget in the upper left corner of the cell
        Up,          //!< Draw the widget at the upper side of the cell (horizontally centered)
        UpperRight,  //!< Draw the widget in the upper right corner of the cell
        Right,       //!< Draw the widget at the right side of the cell (vertically centered)
        BottomRight, //!< Draw the widget in the bottom right corner of the cell
        Bottom,      //!< Draw the widget at the bottom of the cell (horizontally centered)
        BottomLeft,  //!< Draw the widget in the bottom left corner of the cell
        Left         //!< Draw the widget at the left side of the cell (vertically centered)
    };

    enum class TextStyle {
        Regular       = 0,      //!< Regular characters, no style
        Bold          = 1 << 0, //!< Bold characters
        Italic        = 1 << 1, //!< Italic characters
        Underlined    = 1 << 2, //!< Underlined characters
        StrikeThrough = 1 << 3  //!< Strike through characters
    };
}

#endif
