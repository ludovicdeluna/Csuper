/*!
 * \file    new_game_configuration_dialog.cpp
 * \author  Remi BERTHO
 * \date    04/08/15
 * \version 4.3.0
 */

/*
 * new_game_configuration_dialog.cpp
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
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include "new_game_configuration_dialog.h"

#include <glibmm/i18n.h>

using namespace Gtk;
using namespace Glib;
using namespace csuper;
using namespace sigc;
using namespace std;


//
// Constructor and destructor
//
NewGameConfigurationDialog::NewGameConfigurationDialog(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Dialog(cobject)
{
    refGlade->get_widget("new_game_configuration_button_cancel", cancel_button_);
    refGlade->get_widget("new_game_configuration_button_ok", ok_button_);

    refGlade->get_widget("new_game_configuration_dialog_grid", main_grid_);

    refGlade->get_widget("new_game_configuration_label_name", name_label_);
    refGlade->get_widget("new_game_configuration_label_use_maximum", use_maximum_label_);
    refGlade->get_widget("new_game_configuration_label_initial_score", initial_score_label_);
    refGlade->get_widget("new_game_configuration_label_nb_digit", nb_digit_label_);
    refGlade->get_widget("new_game_configuration_label_max_winner", max_winner_label_);
    refGlade->get_widget("new_game_configuration_label_turn_based", turn_based_label_);
    refGlade->get_widget("new_game_configuration_label_distrubutor", distributor_label_);
    refGlade->get_widget("new_game_configuration_label_nb_max", nb_max_label_);

    refGlade->get_widget("new_game_configuration_entry_name", name_entry_);
    refGlade->get_widget("new_game_configuration_switch_max_winner", max_winner_switch_);
    refGlade->get_widget("new_game_configuration_switch_turn_based", turn_based_switch_);
    refGlade->get_widget("new_game_configuration_switch_distrubutor", distributor_switch_);
    refGlade->get_widget("new_game_configuration_spin_decimal_place", decimal_place_spinbutton_);
    refGlade->get_widget("new_game_configuration_combo_max", use_maximum_combobox_);
    refGlade->get_widget("new_game_configuration_spin_initial_score", initial_score_spinbutton_);
    refGlade->get_widget("new_game_configuration_spin_nb_max", nb_max_spinbutton_);

    cancel_button_->set_image_from_icon_name("gtk-cancel",ICON_SIZE_BUTTON);
    ok_button_->set_image_from_icon_name("gtk-ok",ICON_SIZE_BUTTON);

    name_entry_->signal_changed().connect(mem_fun(*this,&NewGameConfigurationDialog::checkAnswer));
    use_maximum_combobox_->signal_changed().connect(mem_fun(*this,&NewGameConfigurationDialog::onUseMaximumChanged));
}


bool NewGameConfigurationDialog::launch(GameConfiguration& game_config, Window& parent_window)
{
    bool res= true;

    set_transient_for(parent_window);


    //Set the dialog from the game configuration
    name_entry_->set_text(game_config.name());

    if (game_config.useMaximum())
    {
        if (game_config.nbMaxMin() == INFINITY)
            use_maximum_combobox_->set_active(2);
        else
            use_maximum_combobox_->set_active(0);
    }
    else
        use_maximum_combobox_->set_active(1);

    nb_max_spinbutton_->set_value(game_config.nbMaxMin());
    initial_score_spinbutton_->set_value(game_config.initialScore());
    max_winner_switch_->set_active(game_config.maxWinner());
    turn_based_switch_->set_active(game_config.turnBased());
    distributor_switch_->set_active(game_config.useDistributor());
    decimal_place_spinbutton_->set_value(game_config.decimalPlace());

    checkAnswer();



    switch(run())
    {
    case RESPONSE_ACCEPT:
        game_config.setName(name_entry_->get_text());

        if (use_maximum_combobox_->get_active_id() == "max")
            game_config.setUseMaximum(true);
        else if (use_maximum_combobox_->get_active_id() == "min")
            game_config.setUseMaximum(false);
        if (use_maximum_combobox_->get_active_id() == "neither")
        {
            game_config.setUseMaximum(true);
            game_config.setNbMaxMin(INFINITY);
        }
        else
            game_config.setNbMaxMin(nb_max_spinbutton_->get_value());

        game_config.setInitialScore(initial_score_spinbutton_->get_value());
        game_config.setMaxWinner(max_winner_switch_->get_active());
        game_config.setTurnBased(turn_based_switch_->get_active());
        game_config.setUseDistributor(distributor_switch_->get_active());
        game_config.setDecimalPlace(decimal_place_spinbutton_->get_value());

        res = true;
        break;
    case RESPONSE_CANCEL:
        res = false;
        break;

    default:
        break;
    }
    hide();

    return res;
}

void NewGameConfigurationDialog::checkAnswer()
{
    if (name_entry_->get_text() == "")
    {
        name_label_->set_markup(ustring::compose("%1%2%3","<span foreground=\"red\">",_("Name of the game configuration"),"</span>"));
        ok_button_->set_sensitive(false);
    }
    else
    {
        name_label_->set_markup( _("Name of the game configuration"));
        ok_button_->set_sensitive(true);
    }
}

void NewGameConfigurationDialog::onUseMaximumChanged()
{
    if (use_maximum_combobox_->get_active_id() == "neither")
        nb_max_spinbutton_->set_editable(false);
    else
        nb_max_spinbutton_->set_editable(true);
}



