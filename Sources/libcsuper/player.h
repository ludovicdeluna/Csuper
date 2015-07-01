/*!
 * \file    player.h
 * \author  Remi BERTHO
 * \date    03/06/15
 * \version 4.3.0
 */

/*
* player.h
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


#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "share.h"
#include "game_configuration.h"
#include <vector>

namespace csuper
{
    /*! \class Player
    *   \brief This class represent a player
    */
    class Player
    {
    private:
        friend class Game;

        Glib::ustring name_;                /*!< Name of the player */
        double total_points_;               /*!< Total points of the player*/
        std::vector<double> points_;        /*!< Points of the player */
        unsigned int ranking_;                       /*!< Ranking of the player */
        unsigned int nb_turn_;              /*!< Number of turn of the player */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        Player();

        /*!
         *  \brief Constructor with all intern component
         *  \param name
         *  \param ranking
         *  \param points
         */
        Player( const Glib::ustring& name,
                const unsigned int ranking,
                const std::vector<double>& points);

        /*!
         *  \brief Constructor with a name and the initial points
         *  \param total_points
         *  \param initial_points
         */
        Player(const double initial_points, const Glib::ustring& name = "");

        /*!
         *  \brief Constructor with a name and the initial points
         *  \param total_points
         *  \param game_config a game configuration for the decimal places
         */
        Player(const GameConfiguration& game_config, const Glib::ustring& name = "");

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \exception csuper::XmlError if bad xmlpp node
         */
        Player(xmlpp::Node* xml_node);




        //
        // Operator
        //
        /*!
         *  \brief Operator ==, compare only the name
         *  \param player another Player
         */
        bool operator==(const Player& player) const;

        /*!
         *  \brief Operator == with a name
         *  \param name the name
         */
        bool operator==(const Glib::ustring& name) const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param player the player
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const Player& player);



        //
        // Function
        //
        /*!
         *  \brief Convert the game configuration to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Convert the game configuration to a ustring
         *  \param game_config a game configuration for the decimal places
         *  \return the ustring
         */
        Glib::ustring toUstring(const GameConfiguration& game_config) const;

        /*!
         *  \brief Calculate the mean points
         */
         double meanPoints() const;

        /*!
         *  \brief Add the player into a xmlpp element
         *  \param parent_node the parent node
         *  \param game_config a game configuration for the decimal places
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node, const GameConfiguration& game_config) const;

        /*!
         *  \brief Indicate if the player has a specific turn
         *  \param turn the turn
         */
        bool hasTurn(const unsigned int turn) const;




        //
        // Setter
        //
        /*!
         *  \brief Set the name
         *  \param name the name
         */
        inline void setName(const Glib::ustring& name)
        {
            name_ = name;
        }

        /*!
         *  \brief Add points to the player
         *  \param points the points
         */
        void addPoints(const double points);

        /*!
         *  \brief Set the ranking
         *  \param ranking the ranking
         */
        inline void setRanking(const unsigned int ranking)
        {
            ranking_ = ranking;
        }

        /*!
         *  \brief Set the points at a specific turn
         *  \param turn the turn
         *  \param points the points
         *  \exception csuper::OutOfRange if turn is greater than the number of turn
         */
        void setPoints(const unsigned int turn, const double point);

        /*!
         *  \brief Delete a turn
         *  \param turn the turn
         *  \exception csuper::OutOfRange if turn is greater than the number of turn
         */
        void deleteTurn(const unsigned int turn);




        //
        // Getter
        //
        /*!
         *  \brief return the name
         *  \return the name
         */
        inline Glib::ustring name() const
        {
            return name_;
        }

        /*!
         *  \brief return the number of turn
         *  \return the number of turn
         */
        inline unsigned int nbTurn() const
        {
            return nb_turn_;
        }

        /*!
         *  \brief return the total points at a specific turn
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the total points
         *  \exception csuper::OutOfRange if turn is greater than the number of turn
         */
        double totalPoints(const int turn=-1) const;

        /*!
         *  \brief return the points at a specific turn
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the points
         *  \exception csuper::OutOfRange if turn is greater than the number of turn
         */
        inline double points(const int turn=-1) const
        {
            if (turn == -1)
                return points_.back();
            else
                return points_[turn];
        }

        /*!
         *  \brief return the ranking
         *  \return the ranking
         */
        inline unsigned int ranking() const
        {
            return ranking_;
        }





        //
        // Ustring Getter
        //
        /*!
         *  \brief return the name in a ustring
         *  \return the ustring
         */
        inline Glib::ustring nameUstring() const
        {
            return name_;
        }

        /*!
         *  \brief return the number of turn in a ustring
         *  \return the ustring
         */
        inline Glib::ustring nbTurnUstring() const
        {
            return intToUstring(nb_turn_);
        }

        /*!
         *  \brief return the total points at a specific turn in a ustring
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the ustring
         *  \exception csuper::OutOfRange if turn is greater than the number of turn
         */
        inline Glib::ustring totalPointsUstring(const int turn = -1) const
        {
            return doubleToUstring(totalPoints(turn));
        }

        /*!
         *  \brief return the total points at a specific turn in a ustring
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \param game_config a game configuration for the decimal places
         *  \param width the width in character of the result ustring
         *  \return the ustring
         *  \exception csuper::OutOfRange if turn is greater than the number of turn
         */
        inline Glib::ustring totalPointsUstring(const GameConfiguration& game_config, const int turn=-1, const unsigned int width=0) const
        {
            return doubleToUstring(totalPoints(turn),game_config.decimalPlace(),width);
        }


        /*!
         *  \brief return the points at a specific turn in a ustring
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the ustring
         *  \exception csuper::OutOfRange if turn is greater than the number of turn
         */
        inline Glib::ustring pointsUstring(const int turn=-1) const
        {
            return doubleToUstring(points(turn));
        }

        /*!
         *  \brief return the points at a specific turn in a ustring
         *  \param turn the turn
         *  \param game_config a game configuration for the decimal places
         *  \param width the width in character of the result ustring
         *  \return the ustring
         *  \exception csuper::OutOfRange if turn is greater than the number of turn
         */
        inline Glib::ustring pointsUstring(const GameConfiguration& game_config,const int turn=-1, const unsigned int width=0) const
        {
            return doubleToUstring(points(turn),game_config.decimalPlace(),width);
        }

        /*!
         *  \brief return the ranking in a ustring
         *  \return the ustring
         */
        inline Glib::ustring rankingUstring(const unsigned int width=0) const
        {
            return intToUstring(ranking_,width);
        }

    };
}

#endif // PLAYER_H_INCLUDED
