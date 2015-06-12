/*!
 * \file    preferences_difference_between_player.cpp
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_difference_between_player.cpp
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


#include "preferences_difference_between_player.h"
#include "config.h"

using namespace Glib;
using namespace std;
using namespace xmlpp;

namespace csuper
{
    //
    // Constructor
    //
    DifferenceBetweenPlayerPreferences::DifferenceBetweenPlayerPreferences() : consecutive_(false), first_(false), last_(false)
    {

    }

    DifferenceBetweenPlayerPreferences::DifferenceBetweenPlayerPreferences(const bool consecutive, const bool first, const bool last) :
        consecutive_(consecutive), first_(first), last_(last)
    {

    }

    DifferenceBetweenPlayerPreferences::DifferenceBetweenPlayerPreferences(Node* xml_node)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        consecutive_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        first_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        last_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());
    }


    //
    // Function
    //
    bool DifferenceBetweenPlayerPreferences::operator==(const DifferenceBetweenPlayerPreferences& diff) const
    {
        return (consecutive() == diff.consecutive() && last() == diff.last() && first() == diff.first());
    }

    ustring DifferenceBetweenPlayerPreferences::toUstring() const
    {
        return ustring::compose(_("Difference between player preferences:\n - Consecutive: %1\n - First: %2\n - Last: %3"),
                                consecutiveUstring(),firstUstring(),lastUstring());
    }

    ostream& operator<<(ostream& os, const DifferenceBetweenPlayerPreferences& diff)
    {
        os << diff.toUstring();
        return os;
    }

    void DifferenceBetweenPlayerPreferences::createXmlNode(Element *parent_node) const
    {
        Element *node = parent_node->add_child("difference_between_player");

        Element *node_consecutive = node->add_child("consecutive");
        node_consecutive->add_child_text(consecutiveUstring());

        Element *node_first = node->add_child("first");
        node_first->add_child_text(firstUstring());

        Element *node_last = node->add_child("last");
        node_last->add_child_text(lastUstring());
    }
}
