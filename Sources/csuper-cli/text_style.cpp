/*!
 * \file    text_style.cpp
 * \author  Remi BERTHO
 * \date    10/07/15
 * \version 4.3.0
 */

/*
 * text_style.cpp
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

 #include "text_style.h"

 using namespace Glib;
 using namespace std;

 TextStyle::TextStyle(const ForegroundColor foreground, const BackgroundColor background, const Style style) :
     foreground_(foreground), background_(background), style_(style), reset_(false)
 {

 }

 TextStyle::TextStyle() : foreground_(TEXT_FOREGROUND_NO_CHANGE), background_(TEXT_BACKGROUND_NO_CHANGE),
    style_(TEXT_STYLE_NO_CHANGE), reset_(true)
{

}

ustring TextStyle::toUstring() const
{
    ustring res;
    #ifdef G_OS_UNIX
    if (reset_)
        res = "\033[0m";
    else
    {
        if (foreground_ != TEXT_FOREGROUND_NO_CHANGE)
            res += ustring::compose("\033[%1m",foreground_);
        if (background_ != TEXT_BACKGROUND_NO_CHANGE)
            res += ustring::compose("\033[%1m",background_);
        if (style_ != TEXT_STYLE_NO_CHANGE)
            res += ustring::compose("\033[%1m",style_);
    }
    #endif // G_OS_UNIX
    return res;
}

ustring TextStyle::Ustring(const ForegroundColor foreground, const BackgroundColor background, const Style style)
{
    TextStyle text_style(foreground,background,style);
    return text_style.toUstring();
}

ustring TextStyle::Ustring()
{
    TextStyle text_style;
    return text_style.toUstring();
}

ostream& operator<<(ostream& os, const TextStyle& text_style)
{
    os << text_style.toUstring();
    return os;
}
