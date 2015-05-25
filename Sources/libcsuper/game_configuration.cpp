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
#include "share.h"

namespace csuper
{
    bool GameConfiguration::operator==(const GameConfiguration &game_config) const
    {
        return (nb_max_ == game_config.nb_max_) &&
                (first_way_ == game_config.first_way_) &&
                (turn_based_ == game_config.turn_based_) &&
                (use_distributor_ == game_config.use_distributor_) &&
                (decimal_place_ == game_config.decimal_place_) &&
                (max_ == game_config.max_) &&
                (name_ == game_config.name_) &&
                (begin_score_ == game_config.begin_score_);
    }

    GameConfiguration::GameConfiguration()
    {
        libcsuper_initialize();
    }


    GameConfiguration::GameConfiguration(const double nb_max, const bool first_way, const bool turn_based, const bool use_distributor,
                                         const int decimal_place, const bool max, const Glib::ustring &name,const double begin_score)
                        : nb_max_(nb_max), first_way_(first_way), turn_based_(turn_based), use_distributor_(use_distributor),
                        decimal_place_(decimal_place), max_(max), name_(name), begin_score_(begin_score)
    {
        libcsuper_initialize();
    }
}
