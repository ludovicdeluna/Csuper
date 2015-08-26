/*!
 * \file    preferences_version.h
 * \author  Remi BERTHO
 * \date    26/08/15
 * \version 4.3.0
 */

/*
* preferences_version.h
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

#include "preferences_version.h"
#include "config.h"

using namespace Glib;
using namespace std;
using namespace xmlpp;

namespace csuper
{
    //
    // Constructor
    //
    VersionPreferences::VersionPreferences() : last_version_check_()
    {

    }

    VersionPreferences::VersionPreferences(const Version& version) :
        last_version_check_(version)
    {

    }

    VersionPreferences::VersionPreferences(Node* xml_node)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        last_version_check_ = static_cast<Element*>(tmp_node)->get_child_text()->get_content();
    }


    //
    // Function
    //
    bool VersionPreferences::operator==(const VersionPreferences& pref) const
    {
        return (lastCheckVersion() == pref.lastCheckVersion());
    }

    ustring VersionPreferences::toUstring() const
    {
        return ustring::compose(_("Version preferences:\n - Last version check: %1"),
                                lastCheckVersionUstring());
    }

    ostream& operator<<(ostream& os, const VersionPreferences& pref)
    {
        os << pref.toUstring();
        return os;
    }

    void VersionPreferences::createXmlNode(Element *parent_node) const
    {
        Element *node = parent_node->add_child("version");

        Element *node_open = node->add_child("last_version_check");
        node_open->add_child_text(lastCheckVersionUstring());
    }
}
