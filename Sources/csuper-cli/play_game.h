/*!
 * \file    play_game.h
 * \author  Remi BERTHO
 * \date    20/07/15
 * \version 4.3.0
 */

/*
 * play_game.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-cli.
 *
 * Csuper-cli is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-cli is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef PLAY_GAME_H_INCLUDED
#define PLAY_GAME_H_INCLUDED

#include "game_cli.h"

/*! \class PlayGame
*   \brief This class is used to play a game
*/
class PlayGame
{
private:
    GameCli* game_;         /*!< The GameCli */
    Glib::ustring filename_;/*!< The filename */



    /*!
    *  Ask and save the new points
    */
    void playersPoints() const;

    /*!
     *  Ask a player name
     * \return the player name
     */
    Glib::ustring playerName() const;

    /*!
     *  Ask if we want to continue or quit
     * \return true if we want to quit, false otherwise
     */
    bool quit() const;

    /*!
     *  Ask if we want to delete a file.
     * \return true if we want to deleted the file, false otherwise
     */
    bool deleteFile() const;

public:
    //
    // Constructor
    //
    /*!
     *  \brief Constructor
     *  \param game tha game
     */
    PlayGame(GameCli* game, const Glib::ustring& filename);


    //
    // Menu function
    //
    /*!
     *  \brief Play the game
     */
    void play() const;
};




#endif // PLAY_GAME_H_INCLUDED
