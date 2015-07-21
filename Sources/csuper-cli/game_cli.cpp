/*!
 * \file    game_cli.cpp
 * \author  Remi BERTHO
 * \date    10/07/15
 * \version 4.3.0
 */

/*
 * game_cli.cpp
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

#include "game_cli.h"
#include "text_style.h"
#include <glibmm/i18n.h>
#include <iomanip>

using namespace csuper;
using namespace Glib;
using namespace std;


//
// Constructor and Destructor
//
GameCli::GameCli(const unsigned int nb_player,const csuper::GameConfiguration& game_config) :
    Game(nb_player,game_config)
{

}

GameCli::GameCli(const Glib::ustring filename) : Game(filename)
{

}

GameCli::~GameCli()
{

}



//
// Set style
//
ustring GameCli::setTextStyle(const Player& player, const bool use_distributor) const
{
    TextStyle::ForegroundColor foreground_color = TextStyle::TEXT_FOREGROUND_NO_CHANGE;
    TextStyle::BackgroundColor background_color = TextStyle::TEXT_BACKGROUND_NO_CHANGE;
    TextStyle::Style style = TextStyle::TEXT_STYLE_NO_CHANGE;

    if (use_distributor && config().useDistributor() && player == this->player(distributor()))
        style = TextStyle::TEXT_UNDERLINE;

    switch (player.ranking())
    {
    case 1:
        foreground_color = TextStyle::TEXT_FOREGROUND_GREEN;
        break;
    case 2:
        foreground_color = TextStyle::TEXT_FOREGROUND_CYAN;
        break;
    case 3:
        foreground_color = TextStyle::TEXT_FOREGROUND_RED;
        break;
    default:
        foreground_color = TextStyle::TEXT_FOREGROUND_BROWN;
    }

    return TextStyle::Ustring(foreground_color,background_color,style);
}

ustring GameCli::resetTextStyle() const
{
    return TextStyle::Ustring();
}



//
// To ustring
//
ustring GameCli::toUstringNames(unsigned int& line_size, const bool change_line_size) const
{
    ustring str;
    int i;
    vector<Player*>::const_iterator it;

    //TRANSLATORS:The number of characters before the | must be eight
    str = _("Names   | ");

    for (it = players_.cbegin() ; it != players_.cend() ; it++)
    {
        ustring name((*it)->name());
        str += setTextStyle(**it,true);
        str += name;
        str += resetTextStyle();

        for (i=name.size() ; i < 4 ; i++)
        {
            str += " ";
            if (change_line_size)
                line_size+=1;
        }

        str += " | ";

        if (change_line_size)
            line_size += name.size() + 3;
    }


    return str + "\n";
}

ustring GameCli::toUstringAllPoints() const
{
    ustring str;
    unsigned int i,j;
    vector<Player*>::const_iterator it;

    for (i=0 ; i<=maxNbTurn() ; i++)
    {
        //TRANSLATORS:The number of characters before the | and without the %1 must be six
        str += ustring::compose(_("Turn %1 |"),ustring::format(setw(2),i));

        for (it=players_.cbegin() ; it != players_.cend() ; it++)
        {
            if ((*it)->hasTurn(i))
            {
                str += setTextStyle(**it);
                str += (*it)->pointsUstring(*config_,i,6);
                str += resetTextStyle();
            }
            else
                str += "      ";

            for (j=4 ; j<(*it)->name().size(); j++)
                str += " ";

            str += "|";
        }
        str += "\n";
    }

    return str;
}

ustring GameCli::toUstringTotalPoints() const
{
    ustring str;
    unsigned int i;
    vector<Player*>::const_iterator it;


    //TRANSLATORS:The number of characters before the | must be eight
    str += _("Total   |");

    for (it = players_.cbegin() ; it != players_.cend() ; it++)
    {
        str += setTextStyle(**it);
        str += (*it)->totalPointsUstring(*config_,-1,6);
        str += resetTextStyle();

        for (i=4 ; i<(*it)->name().size(); i++)
            str += " ";

        str += "|";
    }

    return str + "\n";
}

ustring GameCli::toUstringRanking() const
{
    ustring str;
    unsigned int i;
    vector<Player*>::const_iterator it;


    //TRANSLATORS:The number of characters before the | must be eight
    str += _("Ranking |");

    for (it = players_.cbegin() ; it != players_.cend() ; it++)
    {
        str += setTextStyle(**it);
        str += (*it)->rankingUstring(6);
        str += resetTextStyle();

        for (i=4 ; i<(*it)->name().size(); i++)
            str += " ";

        str += "|";
    }

    return str + "\n";
}


ustring GameCli::toUstringGameOver() const
{
    ustring res;

    res += _("The game is over.\n");

    std::vector<unsigned int> player_index = playerIndexFromPosition();

    // Print the first line
    res += "\n\t\t\t";
    res += TextStyle::Ustring(TextStyle::TEXT_FOREGROUND_GREEN);
    res += printUstringThreeTabs(player(player_index[0]).name());
    res += resetTextStyle();
    res += "\n";

    // Print the second line
    if(nbPlayer() >=2)
    {
        res += TextStyle::Ustring(TextStyle::TEXT_FOREGROUND_CYAN);
        res += printUstringThreeTabs(player(player_index[1]).name());
    }
    else
        res += "\t\t\t";
    res += TextStyle::Ustring(TextStyle::TEXT_FOREGROUND_GREEN);
    res += "------------------------\n";
    res += resetTextStyle();

    // Print the bottom of the second podium
    if(nbPlayer() >=2)
    {
        res += TextStyle::Ustring(TextStyle::TEXT_FOREGROUND_CYAN);
        res += "------------------------";
        res += resetTextStyle();
    }

    // Print the third podium
    if (nbPlayer() >= 3)
    {
        res += "\t\t\t";
        res += TextStyle::Ustring(TextStyle::TEXT_FOREGROUND_RED);
        res += printUstringThreeTabs(player(player_index[2]).name());
        res += "\n\t\t\t\t\t\t";
        res += "------------------------";
        res += resetTextStyle();
    }

    return res;
}


//
// Others
//
ustring GameCli::printUstringThreeTabs(const ustring& str) const
{
    ustring res;

    unsigned int i;
    unsigned int length = str.length();

    for (i=0 ; i<(24-length)/2 ; i++)
    {
        res += " ";
    }

    res += str;

    for (i=0 ; i<(24-length)/2 ; i++)
    {
        res += " ";
    }

    return res;
}


//
// Operator
//
ostream& operator<<(ostream& os, const GameCli& game_cli)
{
    os << game_cli.toUstring();
    if (game_cli.exceedMaxNumber())
        os << endl << game_cli.toUstringGameOver();
    return os;
}
