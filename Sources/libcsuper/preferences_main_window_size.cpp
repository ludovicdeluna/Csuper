/*!
 * \file    preferences_main_window_size.cpp
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_main_window_size.cpp
*
* Copyright 2014-2015
 Remi BERTHO <remi.bertho@openmailbox.org>
*
* This file is part of LibCsuper.
*
* LibCsuper is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* LibCsuper is distributed in the hope that it will be useful,
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


#include "preferences_main_window_size.h"
#include "config.h"

using namespace Glib;
using namespace std;
using namespace xmlpp;

namespace csuper
{
    //
    // Constructor
    //
    MainWindowSizePreferences::MainWindowSizePreferences() : width_(850), height_(450), is_maximize_(false)
    {

    }

    MainWindowSizePreferences::MainWindowSizePreferences(const unsigned int width, const unsigned int height, const bool is_maximize) :
        width_(width), height_(height), is_maximize_(is_maximize)
    {

    }

    MainWindowSizePreferences::MainWindowSizePreferences(Node* xml_node)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        width_ = ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        height_ = ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        is_maximize_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());
    }


    //
    // Function
    //
    bool MainWindowSizePreferences::operator==(const MainWindowSizePreferences& size) const
    {
        return (height() == size.height() && width() == size.width() && isMaximize() == size.isMaximize());
    }

    ustring MainWindowSizePreferences::toUstring() const
    {
        return ustring::compose(_("Main window size preferences:\n - Width: %1\n - Height: %2\n - Is maximize: %3"),
                                widthUstring(),heightUstring(),isMaximizeUstring());
    }

    ostream& operator<<(ostream& os, const MainWindowSizePreferences& size)
    {
        os << size.toUstring();
        return os;
    }

    void MainWindowSizePreferences::createXmlNode(Element *parent_node) const
    {
        Element *node = parent_node->add_child("main_window_size");

        Element *node_width = node->add_child("width");
        node_width->add_child_text(Ascii::dtostr(width()));

        Element *node_height = node->add_child("height");
        node_height->add_child_text(Ascii::dtostr(height()));

        Element *node_is_maximize = node->add_child("is_maximize");
        node_is_maximize->add_child_text(isMaximizeUstring());
    }
}
