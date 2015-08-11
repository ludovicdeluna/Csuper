/*!
 * \file    new_game_configuration_dialog.h
 * \author  Remi BERTHO
 * \date    04/08/15
 * \version 4.3.0
 */

/*
 * new_game_configuration_dialog.h
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

#ifndef NEW_GAME_CONFIGURATION_DIALOG_H_INCLUDED
#define NEW_GAME_CONFIGURATION_DIALOG_H_INCLUDED

#include <gtkmm.h>

#include "../libcsuper/libcsuper.h"


#include "csu_widget.h"

/*! \class NewGameConfigurationDialog
*   \brief This class represent the new game configuration dialog
*/
class NewGameConfigurationDialog : public CsuWidget, public Gtk::Dialog
{
protected:
    Gtk::Button* cancel_button_;    /*!< The HeaderBar */
    Gtk::Button* ok_button_;        /*!< The HeaderBar */

    Gtk::Grid* main_grid_;  /*!< The main grid */

    Gtk::Label* name_label_;            /*!< The name label */
    Gtk::Label* use_maximum_label_;     /*!< The use initial score label */
    Gtk::Label* initial_score_label_;   /*!< The name label */
    Gtk::Label* nb_digit_label_;        /*!< The nb digit label */
    Gtk::Label* max_winner_label_;      /*!< The max winner label */
    Gtk::Label* turn_based_label_;      /*!< The turn based label */
    Gtk::Label* distributor_label_;     /*!< The distributor label */
    Gtk::Label* nb_max_label_;          /*!< The nb max label */

    Gtk::Entry* name_entry_;                    /*!< The name entry */
    Gtk::Switch* max_winner_switch_;            /*!< The max winner switch */
    Gtk::Switch* turn_based_switch_;            /*!< The turn based switch */
    Gtk::Switch* distributor_switch_;           /*!< The distributor switch */
    Gtk::SpinButton* decimal_place_spinbutton_; /*!< The nb digit spinbutton */
    Gtk::ComboBoxText* use_maximum_combobox_;   /*!< The use maximum combobox */
    Gtk::SpinButton* initial_score_spinbutton_; /*!< The initial score spinbutton */
    Gtk::SpinButton* nb_max_spinbutton_;        /*!< The nb max spinbutton */

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    NewGameConfigurationDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);



    /*!
     *  \brief Show the game preferences window
     *  \param game_config the game configuration to be edit
     *  \param parent_window the parent window
     *  \return true if the user validate the dialog, false otherwise
     */
    bool launch(csuper::GameConfiguration& game_config, Gtk::Window& parent_window);


    /*!
     *  \brief Show the game preferences window
     */
    void checkAnswer();


    /*!
     *  \brief Change text editable propriety of the max/min value
     */
    void onUseMaximumChanged();


};



#endif // NEW_GAME_CONFIGURATION_DIALOG_H_INCLUDED
