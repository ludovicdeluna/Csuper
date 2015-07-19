/*!
 * \file    game_cli.h
 * \author  Remi BERTHO
 * \date    10/07/15
 * \version 4.3.0
 */

/*
 * game_cli.h
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

#ifndef GAMECLI_H
#define GAMECLI_H

#include "../libcsuper/libcsuper.h"

class GameCli : public csuper::Game
{
private:
    //
    // Set style
    //
    /*!
     *  \brief Set the text style with the player
     *  \param player the player
     *  \param use_distributor if set the text will be underline if the player is the distributor
     *  \return the text style code
     */
    Glib::ustring setTextStyle(const csuper::Player& player, const bool use_distributor=false) const;

    /*!
     *  \brief Reset the text style
     *  \return the text style code
     */
    Glib::ustring resetTextStyle() const;

    /*!
     *  Print a string center into a space of three tabulations.
     * \param str a ustring
     * \return a ustring
     */
    Glib::ustring printUstringThreeTabs(const Glib::ustring& str) const;

protected:
    /*!
     *  \brief Convert the names to a ustring and calculate the line size
     *  \param line_size the size of the line
     *  \param change_line_size indicate if the function must change the line size
     *  \return the ustring
     */
    virtual Glib::ustring toUstringNames(unsigned int& line_size, const bool change_line_size = false) const;

    /*!
     *  \brief Convert all the points to a ustring
     *  \return the ustring
     */
    virtual Glib::ustring toUstringAllPoints() const;

    /*!
     *  \brief Convert the total points to a ustring
     *  \return the ustring
     */
    virtual Glib::ustring toUstringTotalPoints() const;

    /*!
     *  \brief Convert the ranking to a ustring
     *  \return the ustring
     */
    virtual Glib::ustring toUstringRanking() const;

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor
     *  \param nb_player the number of player
     *  \param game_config the game configuration used
     */
    GameCli(const unsigned int nb_player,const csuper::GameConfiguration& game_config);

    /*!
     *  \brief Constructor from a filename
     *  \exception csuper::XmlError if bad file
     */
    GameCli(const Glib::ustring filename);

    /*!
     *  \brief Destructor
     */
    virtual ~GameCli();



    //
    // Operator
    //
    /*!
     *  \brief Operator <<
     *  \param os the ostream
     *  \param game_cli the game_cli
     *  \return the ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const GameCli& game_cli);



    //
    // Function
    //
    /*!
     *  \brief Convert to a game over ustring
     *  \return the ustring
     */
    Glib::ustring toUstringGameOver() const;
};

#endif // GAMECLI_H
