/*!
 * \file    preferences_main_window_title_bar.cpp
 * \author  Remi BERTHO
 * \date    06/08/15
 * \version 4.3.0
 */

/*
* preferences_main_window_title_bar.cpp
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

#include "preferences_main_window_title_bar.h"
#include "config.h"

using namespace Glib;
using namespace std;
using namespace xmlpp;

namespace csuper
{
    //
    // Constructor
    //
    MainWindowTitleBarPreferences::MainWindowTitleBarPreferences() : disable_window_manager_decoration_(false), print_title_(false)
    {

    }

    MainWindowTitleBarPreferences::MainWindowTitleBarPreferences(const bool disable_window_manager_decoration, const bool print_title) :
        disable_window_manager_decoration_(disable_window_manager_decoration), print_title_(print_title)
    {

    }

    MainWindowTitleBarPreferences::MainWindowTitleBarPreferences(Node* xml_node)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        disable_window_manager_decoration_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        print_title_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());
    }


    //
    // Function
    //
    bool MainWindowTitleBarPreferences::operator==(const MainWindowTitleBarPreferences& pref) const
    {
        return (disableWindowManagerDecoration() == pref.disableWindowManagerDecoration() && printTitle() == pref.printTitle());
    }


    bool MainWindowTitleBarPreferences::operator!=(const MainWindowTitleBarPreferences& pref) const
    {
        return !(*this == pref);
    }

    ustring MainWindowTitleBarPreferences::toUstring() const
    {
        return ustring::compose(_("Main window title bar preferences:\n - Disable window manager decoration: %1\n - Print title: %2"),
                                disableWindowManagerDecorationUstring(),printTitleUstring());
    }

    ostream& operator<<(ostream& os, const MainWindowTitleBarPreferences& pref)
    {
        os << pref.toUstring();
        return os;
    }

    void MainWindowTitleBarPreferences::createXmlNode(Element *parent_node) const
    {
        Element *node = parent_node->add_child("main_window_title_bar");

        Element *node_disable_window_manager_decoration = node->add_child("disable_window_manager_decoration");
        node_disable_window_manager_decoration->add_child_text(disableWindowManagerDecorationUstring());

        Element *node_print_title = node->add_child("print_title");
        node_print_title->add_child_text(printTitleUstring());
    }
}
