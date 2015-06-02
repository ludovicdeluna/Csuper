/*!
 * \file    list_game_configuration.h
 * \author  Remi BERTHO
 * \date    25/05/15
 * \version 4.3.0
 */

/*
* list_game_configuration.h
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

#ifndef LIST_GAME_CONFIGURATION_H_INCLUDED
#define LIST_GAME_CONFIGURATION_H_INCLUDED

#include "game_configuration.h"

namespace csuper
{
    /*! \class ListGameConfiguration
    * \brief This class represent a list of game configuration
    */
    class ListGameConfiguration
    {
    private:
        std::vector<GameConfiguration*> game_configuration_list_; /*!< Tab of game configuration */
        static double version_;

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        ListGameConfiguration();

        /*!
         *  \brief Copy constructor
         */
        ListGameConfiguration(ListGameConfiguration &list_game_config);

        /*!
         *  \brief Constructor from a filename
         *  \exception csuper::xmlError if bad file
         */
        ListGameConfiguration(const Glib::ustring filename);



        //
        // Destuctor
        //
        /*!
         *  \brief Destructor
         */
        ~ListGameConfiguration();



        //
        // Getter and setter
        //
        /*!
         *  \brief Access to the reference of the game configuration at position i
         *  \param i the index of the game configuration
         *  \return the game configuration
         *  \exception std::length_error if i is greater the the number of game configuration
         */
        const GameConfiguration &operator[](const int i) const;

        /*!
         *  \brief Access to the reference of the game configuration at position i
         *  \param i the index of the game configuration
         *  \return the game configuration
         *  \exception std::length_error if i is greater the the number of game configuration
         */
        GameConfiguration &operator[](const int i);

        /*!
         *  \brief Get the number of game configuration the contain the object
         *  \return the number of game configuration the contain the object
         */
        int size() const;

        /*!
         *  \brief Add a game configuration to the object
         *  \param game_config the game configuration
         *  \exception csuper::alreadyExist if the game configuration already exist in the object
         */
        void add(GameConfiguration* game_config);

        /*!
         *  \brief Add all game configuration that contain another list of game configuration to the object
         *  \param list_game_config the game configuration
         */
        void add(const ListGameConfiguration& list_game_config);

        /*!
         *  \brief Add some game configuration that contain another list of game configuration to the object
         *  \param list_game_config the game configuration
         *  \param indexes of the games configuration that will be add
         */
        void add(const ListGameConfiguration& list_game_config,const std::vector<int>& indexes);

        /*!
         *  \brief remove a game configuration from the object
         *  \param i the index of the game configuration
         *  \exception std::length_error if i is greater the the number of game configuration
         */
        void remove(const int i);

        /*!
         *  \brief remove a game configuration from the object and delete it
         *  \param game_config the game configuration which will be deleted if found
         *  \exception csuper::notFound if the game configuration is not in the list
         */
        void remove(const GameConfiguration& game_config);




        //
        // Function
        //
        /*!
         *  \brief operator =
         *  \param list_game_config a list_game_config
         *  \return a reference to the object
         */
        ListGameConfiguration &operator=(const ListGameConfiguration &list_game_config);

        /*!
         *  \brief Convert the list of game configuration to a ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param list_game_config the list of game configuration
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const ListGameConfiguration &list_game_config);

        /*!
         *  \brief Write the list of game configuration to a file
         *  \param filename the filename
         *  \exception xmlpp::internal_error if bad filename
         */
        void writeToFile(const Glib::ustring filename) const;

        /*!
         *  \brief Write the list of game configuration to a file with specific indexes
         *  \param filename the filename
         *  \param indexes of the games configuration that will be write to the file
         *  \exception xmlpp::internal_error if bad filename
         */
        void writeToFile(const Glib::ustring filename, const std::vector<int>& indexes) const;

        /*!
         *  \brief Write the list of game configuration to the file which contain the main list
         */
        void writeToFile() const;

        /*!
         *  \brief Get the main list of game configuration
         *  \return the main list of game configuration
         */
        static ListGameConfiguration *getMainList();
    };
}


#endif // LIST_GAME_CONFIGURATION_H_INCLUDED
