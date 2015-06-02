/*!
 * \file    game_configuration.cpp
 * \author  Remi BERTHO
 * \date    25/05/15
 * \version 4.3.0
 */

/*
* game_configuration.cpp
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

#include "game_configuration.h"
#include <iostream>

using namespace std;
using namespace Glib;
using namespace xmlpp;

namespace csuper
{

    GameConfiguration::GameConfiguration(const double nb_max_min, const bool use_maximum, const bool turn_based, const bool use_distributor,
                                         const int decimal_place, const bool max_winner, const Glib::ustring &name,const double initial_score)
                        : nb_max_min_(nb_max_min), use_maximum_(use_maximum), turn_based_(turn_based), use_distributor_(use_distributor),
                        decimal_place_(decimal_place), max_winner_(max_winner), name_(name), initial_score_(initial_score)
    {

    }

    GameConfiguration::GameConfiguration()
    {

    }

    GameConfiguration::GameConfiguration(Node* xml_node)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        nb_max_min_ = ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        max_winner_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        turn_based_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        use_distributor_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        decimal_place_ = ustringToInt(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        use_maximum_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        name_ = static_cast<Element*>(tmp_node)->get_child_text()->get_content();

        nextXmlElement(tmp_node);
        initial_score_ = ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content());
    }

    void GameConfiguration::createXmlNode(Element *parent_node) const
    {
        Element *node = parent_node->add_child("game_configuration");

        Element *node_nb_max = node->add_child("nb_max_min");
        node_nb_max->add_child_text(nbMaxMinUstring());

        Element *node_max_winner = node->add_child("max_winner");
        node_max_winner->add_child_text(boolToUstring(max_winner_));

        Element *node_turn_by_turn = node->add_child("turn_by_turn");
        node_turn_by_turn->add_child_text(boolToUstring(turn_based_));

        Element *node_use_distributor = node->add_child("use_distributor");
        node_use_distributor->add_child_text(boolToUstring(use_distributor_));

        Element *node_decimal_place = node->add_child("decimal_place");
        node_decimal_place->add_child_text(decimalPlaceUstring());

        Element *node_use_maximum = node->add_child("use_maximum");
        node_use_maximum->add_child_text(boolToUstring(use_maximum_));

        Element *node_name = node->add_child("name");
        node_name->add_child_text(name_);

        Element *node_begin_score = node->add_child("begin_score");
        node_begin_score->add_child_text(initialScoreUstring());
    }


    bool GameConfiguration::operator==(const GameConfiguration &game_config) const
    {
        return (nb_max_min_ == game_config.nb_max_min_) &&
                (use_maximum_ == game_config.use_maximum_) &&
                (turn_based_ == game_config.turn_based_) &&
                (use_distributor_ == game_config.use_distributor_) &&
                (decimal_place_ == game_config.decimal_place_) &&
                (max_winner_ == game_config.max_winner_) &&
                (name_ == game_config.name_) &&
                (initial_score_ == game_config.initial_score_);
    }

    ustring GameConfiguration::toUstring() const
    {
        ustring res = _("Name of the game configuration: ") + nameUstring() + "\n"
            + _("The first has the highest score: ") + maxWinnerUstring() + "\n"
            + _("Initial score: ") + initialScoreUstring() + "\n"
            + _("Number of decimals displayed: ") + decimalPlaceUstring() + "\n"
            + _("Turn-based game: ") + turnBasedUstring() + "\n"
            + _("Use of a distributor: ") + useDistributorUstring() + "\n"
            + _("Use of a maximum score: ") + useMaximumUstring()  + "\n"
            + _("Maximum/minimum number of points: ") + nbMaxMinUstring();

        return res;
    }

    ostream& operator<<(ostream& os, const GameConfiguration& game_config)
    {
        os << game_config.toUstring() << endl;
        return os;
    }
}
