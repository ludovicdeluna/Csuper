/*!
 * \file    player.cpp
 * \author  Remi BERTHO
 * \date    03/06/15
 * \version 4.3.0
 */

/*
* player.cpp
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


#include "player.h"

namespace csuper
{
    using namespace std;
    using namespace Glib;
    using namespace xmlpp;

    //
    // Constructor
    //

    Player::Player()
    {

    }

    Player::Player( const ustring& name, const unsigned int ranking,const vector<double>& points) :
                    name_(name), points_(points), ranking_(ranking), nb_turn_(points.size()-1)
    {
        double total=0;
        vector<double>::const_iterator it;
        for (it=points.cbegin() ; it != points.cend() ; it++)
            total += *it;
        total_points_ = total;
    }


    Player::Player(const double initial_points, const Glib::ustring& name) : name_(name), nb_turn_(0)
    {
        points_.push_back(initial_points);
        total_points_ = initial_points;
        ranking_ = 1;
    }

    Player::Player(const GameConfiguration& game_config, const Glib::ustring& name) : name_(name), nb_turn_(0)
    {
        points_.push_back(game_config.initialScore());
        total_points_ = game_config.initialScore();
        ranking_ = 1;
    }

    Player::Player(Node* xml_node)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        name_ = static_cast<Element*>(tmp_node)->get_child_text()->get_content();

        nextXmlElement(tmp_node);
        total_points_ = ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        ranking_ = ustringToInt(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        nb_turn_ = ustringToInt(static_cast<Element*>(tmp_node)->get_child_text()->get_content()) -1;

        nextXmlElement(tmp_node);
        firstChildXmlElement(tmp_node);
        points_.push_back(ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content()));
        for (unsigned int i=0 ; i<nb_turn_ ; i++)
        {
            nextXmlElement(tmp_node);
            points_.push_back(ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content()));
        }
    }


    //
    // Operator
    //

    bool Player::operator==(const Player& player) const
    {
        return (name_ == player.name_);
    }

    bool Player::operator==(const ustring& name) const
    {
        return (name_ == name);
    }


    ostream& operator<<(ostream& os, const Player& player)
    {
        os << player.toUstring();
        return os;
    }


    //
    // Function
    //

    ustring Player::toUstring() const
    {
        ustring res = _("Name of the player: ") + nameUstring() + "\n"
                    + _("Number of turn: ") + nbTurnUstring() + "\n"
                    + _("Ranking: ") + rankingUstring() + "\n"
                    + _("\tPoints\tTotal points") + "\n";

        for (unsigned int i=0 ; i<nbTurn()+1 ; i++)
        {
            res += _("Turn ") + intToUstring(i)
                + "\t" + pointsUstring(i)
                + "\t" + totalPointsUstring(i) + "\n";
        }

        return res;
    }

    ustring Player::toUstring(const GameConfiguration& game_config) const
    {
        ustring res = _("Name of the player: ") + nameUstring() + "\n"
                    + _("Number of turn: ") + nbTurnUstring() + "\n"
                    + _("Ranking: ") + rankingUstring() + "\n"
                    + _("\tPoints\tTotal points") + "\n";

        for (unsigned int i=0 ; i<nbTurn()+1 ; i++)
        {
            res += _("\nTurn ") + intToUstring(i)
                + "\t" + pointsUstring(game_config,i)
                + "\t" + totalPointsUstring(game_config,i);
        }

        return res;
    }

    double Player::meanPoints() const
    {
        return total_points_ / (nb_turn_);
    }


    void Player::createXmlNode(Element *parent_node, const GameConfiguration& game_config) const
    {
        Element *node = parent_node->add_child("player");

        Element *node_player_name = node->add_child("player_name");
        node_player_name->add_child_text(nameUstring());

        Element *node_total_points = node->add_child("total_points");
        node_total_points->add_child_text(totalPointsUstring(game_config));

        Element *node_rank = node->add_child("rank");
        node_rank->add_child_text(rankingUstring());

        Element *node_number_of_turn = node->add_child("number_of_turn");
        node_number_of_turn->add_child_text(intToUstring(nb_turn_+1));

        Element *node_points = node->add_child("points");
        for (unsigned int i=0 ; i<nbTurn()+1 ; i++)
        {
            Element *node_tmp_points = node_points->add_child("turn");
            node_tmp_points->add_child_text(pointsUstring(game_config,i));
            node_tmp_points->set_attribute("num",intToUstring(i));
        }

    }

    bool Player::hasTurn(const unsigned int turn) const
    {
        return (turn <= nb_turn_);
    }



    //
    // Setter
    //

    void Player::addPoints(const double points)
    {
        points_.push_back(points);
        total_points_ += points;
        nb_turn_++;
    }

    void Player::setPoints(const unsigned int turn, const double point)
    {
        if (turn > nb_turn_)
            throw length_error(ustring::compose(_("Cannot access to the %1th turn, there is only %2 turn"),turn,nbTurn()));

        double points_diff = points(turn) - point;
        points_[turn] = point;

        total_points_ -= points_diff;
    }

    void Player::deleteTurn(const unsigned int turn)
    {
        if (turn > nb_turn_)
            throw length_error(ustring::compose(_("Cannot delete the %1th turn, there is only %2 turn"),turn,nbTurn()));

        total_points_ -= points(turn);
        points_.erase(points_.begin()+turn);
        nb_turn_--;
    }


    //
    // Getter
    //
    double Player::totalPoints(const int turn) const
    {
        if (turn ==-1)
            return total_points_;

        double total=0;
        for (int i=0 ; i<turn+1 ; i++)
            total += points(i);
        return total;
    }
}
