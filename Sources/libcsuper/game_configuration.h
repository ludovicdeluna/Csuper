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
#include <libxml++/libxml++.h>
#include "share.h"

namespace csuper
{
    /*! \class GameConfiguration
    *   \brief This class represent a game configuration
    */
    class GameConfiguration
    {
    private:
        double nb_max_min_;     /*!< Number maximum or minimum that can reach a player. */
        bool use_maximum_;      /*!< True if the first is those has the maximum of points, false otherwise */
        bool turn_based_;       /*!< True if this is a turn-based game, false otherwise */
        bool use_distributor_;  /*!< True if the game use a distributor, false otherwise */
        int decimal_place_;     /*!< The number of decimal place which are display */
        bool max_winner_;       /*!< True if the game use a maximum, false if it's a minimum */
        Glib::ustring name_;    /*!< The name of the game configuration */
        double initial_score_;  /*!< The score of all players in the beginning of the game */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        GameConfiguration();

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \exception csuper::XmlError if bad xmlpp node
         */
        GameConfiguration(xmlpp::Node* xml_node);

        /*!
         *  \brief Constructor with all intern component
         *  \param nb_max_min
         *  \param use_maximum
         *  \param turn_based
         *  \param use_distributor
         *  \param decimal_place
         *  \param max_winner
         *  \param name
         *  \param initial_score
         */
        GameConfiguration(const double nb_max_min,
                          const bool use_maximum,
                          const bool turn_based,
                          const bool use_distributor,
                          const int decimal_place,
                          const bool max_winner,
                          const Glib::ustring &name,
                          const double initial_score);


        //
        // Operator
        //
        /*!
         *  \brief Operator ==
         *  \param game_config another GameConfiguration
         */
        bool operator==(const GameConfiguration& game_config) const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param game_config the game configuration
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const GameConfiguration& game_config);



        //
        // Function
        //
        /*!
         *  \brief Convert the game configuration to a ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Add the game configuration into a xmlpp element
         *  \param parent_node the parent node
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node) const;


        //
        // Getter
        //
        /*!
         *  \brief return the number max or min
         *  \return the number max or min
         */
        inline double nbMaxMin() const
        {
            return nb_max_min_;
        }

        /*!
         *  \brief return the us maximum
         *  \return the us maximum
         */
        inline bool useMaximum() const
        {
            return use_maximum_;
        }

        /*!
         *  \brief return the turn based
         *  \return the turn based
         */
        inline bool turnBased() const
        {
            return turn_based_;
        }

        /*!
         *  \brief return the use distributor
         *  \return the use distributor
         */
        inline bool useDistributor() const
        {
            return use_distributor_;
        }

        /*!
         *  \brief return the max winner
         *  \return the max winner
         */
        inline bool maxWinner() const
        {
            return max_winner_;
        }

        /*!
         *  \brief return the decimal place
         *  \return the decimal place
         */
        inline int decimalPlace() const
        {
            return decimal_place_;
        }

        /*!
         *  \brief return the name
         *  \return the name
         */
        inline Glib::ustring name() const
        {
            return name_;
        }

        /*!
         *  \brief return the initial score
         *  \return the initial score
         */
        inline double initialScore() const
        {
            return initial_score_;
        }



        //
        // Ustring Getter
        //
        /*!
         *  \brief return the number max or min in a ustring
         *  \return the ustring
         */
        inline Glib::ustring nbMaxMinUstring() const
        {
            return doubleToUstring(nb_max_min_,decimal_place_);
        }

        /*!
         *  \brief return the use maximum
         *  \return the ustring
         */
        inline Glib::ustring useMaximumUstring() const
        {
            return boolToYesNo(use_maximum_);
        }

        /*!
         *  \brief return the turn based
         *  \return the ustring
         */
        inline Glib::ustring turnBasedUstring() const
        {
            return boolToYesNo(turn_based_);
        }

        /*!
         *  \brief return the use distributor
         *  \return the ustring
         */
        inline Glib::ustring useDistributorUstring() const
        {
            return boolToYesNo(use_distributor_);
        }

        /*!
         *  \brief return the max winner
         *  \return the ustring
         */
        inline Glib::ustring maxWinnerUstring() const
        {
            return boolToYesNo(max_winner_);
        }

        /*!
         *  \brief return the decimals place
         *  \return the ustring
         */
        inline Glib::ustring decimalPlaceUstring() const
        {
            return intToUstring(decimal_place_);
        }

        /*!
         *  \brief return the name
         *  \return the ustring
         */
        inline Glib::ustring nameUstring() const
        {
            return name_;
        }

        /*!
         *  \brief return the initial score
         *  \return the ustring
         */
        inline Glib::ustring initialScoreUstring() const
        {
            return doubleToUstring(initial_score_,decimal_place_);
        }



        // Setter
        /*!
         *  \brief change the number max or min
         *  \param nb_max_min the new nb max min
         */
        inline void setNbMaxMin(const double nb_max_min)
        {
            nb_max_min_ = nb_max_min;
        }

        /*!
         *  \brief change the use maximum
         *  \param use_maximum the new use maximum
         */
        inline void setUseMaximum(const bool use_maximum)
        {
            use_maximum_ = use_maximum;
        }

        /*!
         *  \brief change the turn based
         *  \param turn_based the new turn based
         */
        inline void setTurnBased(const bool turn_based)
        {
            turn_based_ = turn_based;
        }

        /*!
         *  \brief change the use distributor
         *  \param use_distributor the new use distributor
         */
        inline void setUseDistributor(const bool use_distributor)
        {
            use_distributor_ = use_distributor;
        }


        /*!
         *  \brief change the max winner
         *  \param max_winner the new max winner
         */
        inline void setMaxWinner(const bool max_winner)
        {
            max_winner_ = max_winner;
        }

        /*!
         *  \brief change the decimal place
         *  \param decimal_place the new decimal place
         */
        inline void setDecimalPlace(const int decimal_place)
        {
            decimal_place_ = decimal_place;
        }

        /*!
         *  \brief change the name
         *  \param name the new name
         */
        inline void setName(const Glib::ustring &name)
        {
            name_ = name;
        }

        /*!
         *  \brief change the initial score
         *  \param initial_score the new initial score
         */
        inline void setInitialScore(const double initial_score)
        {
            initial_score_ = initial_score;
        }

    };
}


#endif // GAME_CONFIGURATION_H_INCLUDED
