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


#include "preferences_score_display.h"
#include "config.h"

using namespace Glib;
using namespace std;
using namespace xmlpp;

namespace csuper
{
    //
    // Constructor
    //
    ScoreDisplayPreferences::ScoreDisplayPreferences() : total_points_(false), ranking_(false), edit_suppr_(false)
    {

    }

    ScoreDisplayPreferences::ScoreDisplayPreferences(const bool total_points, const bool ranking, const bool edit_suppr) :
        total_points_(total_points), ranking_(ranking), edit_suppr_(edit_suppr)
    {

    }

    ScoreDisplayPreferences::ScoreDisplayPreferences(Node* xml_node)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        total_points_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        ranking_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        edit_suppr_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());
    }


    //
    // Function
    //
    bool ScoreDisplayPreferences::operator==(const ScoreDisplayPreferences& score) const
    {
        return (totalPoints() == score.totalPoints() && ranking() == score.ranking() && editSuppr() == score.editSuppr());
    }

    ustring ScoreDisplayPreferences::toUstring() const
    {
        return ustring::compose(_("Score display preferences:\n - Total points: %1\n - Ranking: %2\n - Edit/suppr: %3"),
                                totalPointsUstring(),rankingUstring(),editSupprUstring());
    }

    ostream& operator<<(ostream& os, const ScoreDisplayPreferences& score)
    {
        os << score.toUstring();
        return os;
    }

    void ScoreDisplayPreferences::createXmlNode(Element *parent_node) const
    {
        Element *node = parent_node->add_child("score_display");

        Element *node_total_points = node->add_child("total_points");
        node_total_points->add_child_text(totalPointsUstring());

        Element *node_ranking = node->add_child("ranking");
        node_ranking->add_child_text(rankingUstring());

        Element *node_edit_suppr = node->add_child("edit_suppr");
        node_edit_suppr->add_child_text(editSupprUstring());
    }
}
