/*!
 * \file    text_style.h
 * \author  Remi BERTHO
 * \date    10/07/15
 * \version 4.3.0
 */

/*
 * text_style.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-cli.
 *
 * Csuper-cli is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-cli is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include "glibmm.h"
#include "iostream"


/*! \class TextStyle
*   \brief This class is used to set a text style in a terminal
*/
class TextStyle
{
public:
    //
    // Enum
    //
    enum ForegroundColor
    {
        FOREGROUND_BLACK=30,
        FOREGROUND_RED=31,
        FOREGROUND_GREEN=32,
        FOREGROUND_BROWN=33,
        FOREGROUND_BLUE=34,
        FOREGROUND_MAGENTA=35,
        FOREGROUND_CYAN=36,
        FOREGROUND_WHITE=37,
        FOREGROUND_DEFAULT=39,
        FOREGROUND_NO_CHANGE
    };

    enum BackgroundColor
    {
        BACKGROUND_BLACK=40,
        BACKGROUND_RED=41,
        BACKGROUND_GREEN=42,
        BACKGROUND_BROWN=43,
        BACKGROUND_BLUE=44,
        BACKGROUND_MAGENTA=45,
        BACKGROUND_CYAN=46,
        BACKGROUND_WHITE=47,
        BACKGROUND_DEFAULT=49,
        BACKGROUND_NO_CHANGE
    };

    enum Style
    {
        BOLD=1,
        UNDERLINE=4,
        STYLE_NO_CHANGE
    };

private:
    ForegroundColor foreground_; /*!< The foreground color */
    BackgroundColor background_; /*!< The background color */
    Style style_;                /*!< The style */
    bool reset_;                 /*!< Reset the text style */

public:
    /*!
     *  \brief Constructor with parameters
     *  \param foreground the foreground color
     *  \param background the background color
     *  \param style the style
     */
    TextStyle(const ForegroundColor foreground, const BackgroundColor background=BACKGROUND_NO_CHANGE, const Style style=STYLE_NO_CHANGE);

    /*!
     *  \brief Reset constructor
     */
    TextStyle();

    /*!
     *  \brief Convert to a ustring
     *  \return the text style code
     */
    Glib::ustring toUstring() const;


    /*!
     *  \brief Create a ustring with the code
     *  \param foreground the foreground color
     *  \param background the background color
     *  \param style the style
     *  \return the text style code
     */
    static Glib::ustring Ustring(const ForegroundColor foreground, const BackgroundColor background=BACKGROUND_NO_CHANGE, const Style style=STYLE_NO_CHANGE);

    /*!
     *  \brief Create a ustring with the reset code
     *  \return the text style code
     */
    static Glib::ustring Ustring();

    /*!
     *  \brief Operator <<
     *  \param os the ostream
     *  \param text_style the text style
     *  \return the ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const TextStyle& text_style);
};



#endif // COLOR_H_INCLUDED
