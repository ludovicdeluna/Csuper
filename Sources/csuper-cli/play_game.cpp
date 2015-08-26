/*!
 * \file    play_game.cpp
 * \author  Remi BERTHO
 * \date    20/07/15
 * \version 4.3.0
 */

/*
 * play_game.cpp
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include "play_game.h"
#include "share.h"
#include "cin.h"
#include <glibmm/i18n.h>


using namespace Glib;
using namespace std;
using namespace csuper;

PlayGame::PlayGame(GameCli* game, const ustring& filename) : game_(game), filename_(filename)
{

}

void PlayGame::play() const
{
    bool stop = false;

    clearScreen();
    cout << game_->toUstringPoints() << endl;

    do
    {
        playersPoints();

        try
        {
            game_->writeToFile(filename_);
        }
        catch (Glib::Exception& e)
        {
            cout << e.what() << endl;
        }

        clearScreen();
        cout << game_->toUstringPoints() << endl;

        if (game_->exceedMaxNumber())
        {
            cout << game_->toUstringGameOver() << endl;
            systemPause();
            stop = true;
        }
        else
            stop = quit();

    } while (!stop);


    if (deleteFile())
    {
        try
        {
            trashFile(filename_);
            cout << ustring::compose(_("The file %1 was successfully deleted."),filename_) << endl;
        }
        catch (csuper::FileError& e)
        {
            cout << e.what() << endl;
        }

        systemPause();
    }
}


void PlayGame::playersPoints() const
{
    bool validate;
    vector<double> vec_points;
    double points;
    ustring player_name;

    if (!(game_->config().turnBased()))
        player_name = playerName();

    do
    {
        validate = true;

        if (game_->config().turnBased())
        {
            double total = 0;
            double tmp_points;
            vec_points.clear();

            for (unsigned int i=0 ; i<game_->nbPlayer() ; i++)
            {
                cout << endl << ustring::compose(_("Give the points of %1 : "),game_->playerName(i));
                tmp_points = Cin::getDouble();
                total += tmp_points;
                cout << ustring::compose(_("You chose %1\n\n"
                                           "Total number of points distributed in that turn: %2"),
                                         doubleToUstring(tmp_points,game_->config().decimalPlace()),
                                         doubleToUstring(total,game_->config().decimalPlace())) << endl;
                vec_points.push_back(tmp_points);
            }
        }
        else
        {
            cout << endl << ustring(_("Give their points: "));
            points = Cin::getDouble();
            cout << ustring::compose(_("You chose %1"),points) << endl;
        }

        cout << endl << ustring(_("Do you confirm these scores (Y/n)? "));
        if (Cin::getNo())
            validate = false;

    } while (!validate);

    if (game_->config().turnBased())
        game_->newTurn(vec_points);
    else
    {
        try
        {
            game_->newTurn(player_name,points);
        }
        catch (Glib::Exception& e)
        {
            cout << e.what() << endl;
            systemPause();
        }
    }
}


ustring PlayGame::playerName() const
{
    ustring player_name;

    cout << endl << ustring(_("Give the name (or the first letters of the name) of the person who will earn points."
                              "\nYour choice: "));
    player_name = Cin::getUstring();
    cout << ustring::compose(_("You chose %s"),player_name) << endl;

    return player_name;
}

bool PlayGame::quit() const
{
    bool quit;

    cout << endl << ustring(_("Do you want to continue (Y/n)? "));
    if (Cin::getNo())
        quit = true;

    return quit;
}

bool PlayGame::deleteFile() const
{
    cout << endl << ustring(_("Would you like to delete the file (y/N)? "));
    if (Cin::getYes())
        return true;

    return false;
}
