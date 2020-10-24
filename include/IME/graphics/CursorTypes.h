/**
 * @brief Mouse cursor types
*/

#ifndef CURSORTYPES_H
#define CURSORTYPES_H

namespace IME {
    enum class CursorType {
        Arrow,                  //!< Arrow cursor (default)
        Text,                   //!< I-beam, cursor when hovering over a text field
        Hand,                   //!< Pointing hand cursor
        SizeLeft,               //!< Left arrow on Linux, horizontal double arrow cursor on Windows and macOS
        SizeRight,              //!< Right arrow on Linux, horizontal double arrow cursor on Windows and macOS
        SizeTop,                //!< Up arrow on Linux, vertical double arrow cursor on Windows and macOS
        SizeBottom,             //!< Down arrow on Linux, vertical double arrow cursor on Windows and macOS
        SizeTopLeft,            //!< Top-left arrow on Linux, double arrow cursor going from top-left to bottom-right on Windows and macOS
        SizeBottomRight,        //!< Bottom-right arrow on Linux, double arrow cursor going from top-left to bottom-right on Windows and
        SizeBottomLeft,         //!< Bottom-left arrow on Linux, double arrow cursor going from bottom-left to top-right on Windows and macOS
        SizeTopRight,           //!< Top-right arrow on Linux, double arrow cursor going from bottom-left to top-right on Windows and macOS
        Crosshair,              //!< Crosshair cursor
        Help,                   //!< Help cursor
        NotAllowed              //!< Action not allowed cursor
    };
}

#endif
