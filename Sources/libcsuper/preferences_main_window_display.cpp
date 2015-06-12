/*!
 * \file    preferences_main_window_display.cpp
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_main_window_display.cpp
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


#include "preferences_main_window_display.h"
#include "config.h"

using namespace Glib;
using namespace std;
using namespace xmlpp;

namespace csuper
{
    //
    // Constructor
    //
    MainWindowDisplayPreferences::MainWindowDisplayPreferences() : ranking_(true), calculator_(false), game_information_(true)
    {

    }

    MainWindowDisplayPreferences::MainWindowDisplayPreferences(const bool ranking, const bool calculator, const bool game_information) :
        ranking_(ranking), calculator_(calculator), game_information_(game_information)
    {

    }

    MainWindowDisplayPreferences::MainWindowDisplayPreferences(Node* xml_node)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        ranking_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        calculator_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        game_information_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());
    }


    //
    // Function
    //
    bool MainWindowDisplayPreferences::operator==(const MainWindowDisplayPreferences& display) const
    {
        return (calculator() == display.calculator() && ranking() == display.ranking() && gameInformation() == display.gameInformation());
    }

    ustring MainWindowDisplayPreferences::toUstring() const
    {
        return ustring::compose(_("Main window display preferences:\n - Ranking: %1\n - Calculator: %2\n - Game information: %3"),
                                rankingUstring(),calculatorUstring(),gameInformationUstring());
    }

    ostream& operator<<(ostream& os, const MainWindowDisplayPreferences& display)
    {
        os << display.toUstring();
        return os;
    }

    void MainWindowDisplayPreferences::createXmlNode(Element *parent_node) const
    {
        Element *node = parent_node->add_child("main_window_display");

        Element *node_ranking = node->add_child("ranking");
        node_ranking->add_child_text(rankingUstring());

        Element *node_calculator = node->add_child("calculator");
        node_calculator->add_child_text(calculatorUstring());

        Element *node_game_information = node->add_child("game_information");
        node_game_information->add_child_text(gameInformationUstring());
    }
}
