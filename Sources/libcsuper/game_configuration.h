/*!
 * \file    game_configuration.h
 * \author  Remi BERTHO
 * \date    25/05/15
 * \version 4.3.0
 */

/*
* game_configuration.h
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

#ifndef GAME_CONFIGURATION_H_INCLUDED
#define GAME_CONFIGURATION_H_INCLUDED

#include <glibmm.h>
//#include <string>

namespace csuper
{
    class GameConfiguration
    {
    private:
        double nb_max_;         /*!< Number maximum or minimum that can reach a player. */
        bool first_way_;        /*!< True if the first is those has the maximum of points, false otherwise */
        bool turn_based_;       /*!< True if this is a turn-based game, false otherwise */
        bool use_distributor_;  /*!< True if the game use a distributor, false otherwise */
        int decimal_place_;     /*!< The number of decimal place which are display */
        bool max_;              /*!< True if the game use a maximum, false if it's a minimum */
        Glib::ustring name_;    /*!< The name of the game configuration */
        double begin_score_;    /*!< The score of all players in the beginning of the game */

    public:
        // Constructor
        GameConfiguration();
        GameConfiguration(const double nb_max,
                          const bool first_way,
                          const bool turn_based,
                          const bool use_distributor,
                          const int decimal_place,
                          const bool max,
                          const Glib::ustring &name,
                          const double begin_score);


        // Operator
        bool operator==(const GameConfiguration &game_config) const;


        // Getter
        inline double nb_max() const
        {
            return nb_max_;
        }

        inline bool first_way() const
        {
            return first_way_;
        }

        inline bool turn_based() const
        {
            return turn_based_;
        }

        inline bool use_distributor() const
        {
            return use_distributor_;
        }

        inline bool max() const
        {
            return max_;
        }

        inline int decimal_place() const
        {
            return decimal_place_;
        }

        inline Glib::ustring name() const
        {
            return name_;
        }

        /*inline std::string name_std() const
        {
            return name_;
        }*/

        inline double begin_score() const
        {
            return begin_score_;
        }


        // Setter
        inline void set_nb_max(const double nb_max)
        {
            nb_max_ = nb_max;
        }

        inline void set_first_way(const bool first_way)
        {
            first_way_ = first_way;
        }

        inline void set_turn_based(const bool turn_based)
        {
            turn_based_ = turn_based;
        }

        inline void set_use_distributor(const bool use_distributor)
        {
            use_distributor_ = use_distributor;
        }

        inline void set_max(const bool max)
        {
            max_ = max;
        }

        inline void set_decimal_place(const int decimal_place)
        {
            decimal_place_ = decimal_place;
        }

        inline void set_name(const Glib::ustring &name)
        {
            name_ = name;
        }

        /*inline void set_name(const std::string name)
        {
            name_ = name;
        }*/

        inline void set_begin_score(const double begin_score)
        {
            begin_score_ = begin_score;
        }

    };
}


#endif // GAME_CONFIGURATION_H_INCLUDED
