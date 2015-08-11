/*!
 * \file    menu_display.h
 * \author  Remi BERTHO
 * \date    06/08/15
 * \version 4.3.0
 */

/*
 * menu_display.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-gtk.
 *
 * Csuper-gtk is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-gtk is distributed in the hope that it will be useful,
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

#ifndef MENU_DISPLAY_H_INCLUDED
#define MENU_DISPLAY_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class MenuDisplay
*   \brief This class represent the menu display
*/
class MenuDisplay : public CsuWidget, public Gtk::Menu
{
protected:
    Gtk::MenuItem* podium_;                 /*!< The podium button */
    Gtk::MenuItem* chart_total_points_;     /*!< The chart total points button */
    Gtk::MenuItem* chart_points_;           /*!< The chart points button */
    Gtk::MenuItem* statistics_;             /*!< The statistics button */

    Gtk::SeparatorMenuItem* sep_1_;         /*!< The separator 1 */

    Gtk::CheckMenuItem* cons_;              /*!< The consecutive button */
    Gtk::CheckMenuItem* first_;             /*!< The first button */
    Gtk::CheckMenuItem* last_;              /*!< The last button */

    Gtk::SeparatorMenuItem* sep_2_;         /*!< The separator 2 */

    Gtk::CheckMenuItem* total_points_;      /*!< The total points button */
    Gtk::CheckMenuItem* ranking_;           /*!< The ranking button */
    Gtk::CheckMenuItem* edit_suppr_;        /*!< The edit suppr button */

    Gtk::SeparatorMenuItem* sep_3_;         /*!< The separator 3 */

    Gtk::CheckMenuItem* ranking_side_;      /*!< The ranking side button */
    Gtk::CheckMenuItem* calculator_;        /*!< The calculator button */
    Gtk::CheckMenuItem* game_information_;  /*!< The game information button */

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    MenuDisplay(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);



    //
    // Function
    //
    /*!
     *  \brief Slot used when a difference between player is changed
     */
    void diffChanged();

    /*!
     *  \brief Slot used when a score display is changed
     */
    void scoreDisplayChanged();

    /*!
     *  \brief Slot used when a main window display is changed
     */
    void mainWindowDisplayChanged();
};

#endif // MENU_DISPLAY_H_INCLUDED
