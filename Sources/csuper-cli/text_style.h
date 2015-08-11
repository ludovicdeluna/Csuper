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
 * along with this program; if not, write to the Free Software
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
        TEXT_FOREGROUND_BLACK=30,
        TEXT_FOREGROUND_RED=31,
        TEXT_FOREGROUND_GREEN=32,
        TEXT_FOREGROUND_BROWN=33,
        TEXT_FOREGROUND_BLUE=34,
        TEXT_FOREGROUND_MAGENTA=35,
        TEXT_FOREGROUND_CYAN=36,
        TEXT_FOREGROUND_WHITE=37,
        TEXT_FOREGROUND_DEFAULT=39,
        TEXT_FOREGROUND_NO_CHANGE
    };

    enum BackgroundColor
    {
        TEXT_BACKGROUND_BLACK=40,
        TEXT_BACKGROUND_RED=41,
        TEXT_BACKGROUND_GREEN=42,
        TEXT_BACKGROUND_BROWN=43,
        TEXT_BACKGROUND_BLUE=44,
        TEXT_BACKGROUND_MAGENTA=45,
        TEXT_BACKGROUND_CYAN=46,
        TEXT_BACKGROUND_WHITE=47,
        TEXT_BACKGROUND_DEFAULT=49,
        TEXT_BACKGROUND_NO_CHANGE
    };

    enum Style
    {
        TEXT_BOLD=1,
        TEXT_UNDERLINE=4,
        TEXT_STYLE_NO_CHANGE
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
    TextStyle(const ForegroundColor foreground, const BackgroundColor background=TEXT_BACKGROUND_NO_CHANGE, const Style style=TEXT_STYLE_NO_CHANGE);

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
    static Glib::ustring Ustring(const ForegroundColor foreground, const BackgroundColor background=TEXT_BACKGROUND_NO_CHANGE, const Style style=TEXT_STYLE_NO_CHANGE);

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
