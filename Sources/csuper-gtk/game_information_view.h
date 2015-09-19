/*!
 * \file    game_information_view.h
 * \author  Remi BERTHO
 * \date    18/09/15
 * \version 4.3.0
 */

/*
 * game_information_view.h
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

#ifndef GAME_INFORMATION_VIEW_H_INCLUDED
#define GAME_INFORMATION_VIEW_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class GameInformationView
*   \brief This class represent the game information view
*/
class GameInformationView : public CsuWidget, public Gtk::Box
{
protected:
    Gtk::Separator* sep_;               /*!< The separator */
    Gtk::Label* distributor_;           /*!< The distributor label */
    Gtk::Label* game_info_label_;       /*!< The game information label */
    Gtk::Button* change_distributor_;   /*!< The change distributor button */
    Gtk::Label* total_poins_;           /*!< The total points label */


    //
    // Function
    //
    /*!
     *  \brief Change distributor
     */
    void changeDistributor();

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    GameInformationView(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);


    //
    // Function
    //
    /*!
     *  \brief Update distributor
     */
    void updateDistributor();


};

#endif // GAME_INFORMATION_VIEW_H_INCLUDED
