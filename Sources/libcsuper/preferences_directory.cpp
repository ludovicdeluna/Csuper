/*!
 * \file    preferences_score_display.cpp
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_score_display.cpp
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


#include "preferences_directory.h"
#include "config.h"

using namespace Glib;
using namespace std;
using namespace xmlpp;

namespace csuper
{
    //
    // Constructor
    //
    DirectoryPreferences::DirectoryPreferences()
    {
        if (Portable::getPortable())
            open_ = "";
        else
            open_ = get_home_dir();
    }

    DirectoryPreferences::DirectoryPreferences(const ustring& open) :
        open_(open)
    {

    }

    DirectoryPreferences::DirectoryPreferences(Node* xml_node)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        open_ = static_cast<Element*>(tmp_node)->get_child_text()->get_content();
    }


    //
    // Function
    //
    bool DirectoryPreferences::operator==(const DirectoryPreferences& dir) const
    {
        return (open() == dir.open());
    }

    ustring DirectoryPreferences::toUstring() const
    {
        return ustring::compose(_("Directory preferences:\n - Open: %1"),
                                openUstring());
    }

    ostream& operator<<(ostream& os, const DirectoryPreferences& dir)
    {
        os << dir.toUstring();
        return os;
    }

    void DirectoryPreferences::createXmlNode(Element *parent_node) const
    {
        Element *node = parent_node->add_child("directory");

        Element *node_open = node->add_child("open");
        node_open->add_child_text(openUstring());
    }
}
