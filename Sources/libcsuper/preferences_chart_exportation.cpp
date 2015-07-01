/*!
 * \file    preferences_chart_exportation.cpp
 * \author  Remi BERTHO
 * \date    25/06/15
 * \version 4.3.0
 */

/*
* preferences_chart_exportation.cpp
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


#include "preferences_chart_exportation.h"
#include "config.h"

using namespace Glib;
using namespace std;
using namespace xmlpp;

namespace csuper
{
    //
    // Constructor
    //
    ChartExportationPreferences::ChartExportationPreferences() : width_(800), height_(500), total_points_(true)
    {

    }

    ChartExportationPreferences::ChartExportationPreferences(const int width, const int height, const bool total_points) :
        width_(width), height_(height), total_points_(total_points)
    {

    }

    ChartExportationPreferences::ChartExportationPreferences(Node* xml_node)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        width_ = ustringToInt(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        height_ = ustringToInt(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        total_points_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());
    }


    //
    // Function
    //
    bool ChartExportationPreferences::operator==(const ChartExportationPreferences& pref) const
    {
        return (totalPoints() == pref.totalPoints() && width() == pref.width() && height() == pref.height());
    }

    ustring ChartExportationPreferences::toUstring() const
    {
        return ustring::compose(_("Chart exportation preferences:\n - Width: %1\n - Height: %2\n - Total points: %3"),
                                widthUstring(),heightUstring(),totalPointsUstring());
    }

    ostream& operator<<(ostream& os, const ChartExportationPreferences& pref)
    {
        os << pref.toUstring();
        return os;
    }

    void ChartExportationPreferences::createXmlNode(Element *parent_node) const
    {
        Element *node = parent_node->add_child("chart_export_preferences");

        Element *node_width = node->add_child("width");
        node_width->add_child_text(Ascii::dtostr(width()));

        Element *node_height= node->add_child("height");
        node_height->add_child_text(Ascii::dtostr(height()));

        Element *node_total_points = node->add_child("total_points");
        node_total_points->add_child_text(totalPointsUstring());
    }
}
