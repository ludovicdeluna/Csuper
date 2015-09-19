/*!
 * \file    game_information_view.cpp
 * \author  Remi BERTHO
 * \date    18/09/15
 * \version 4.3.0
 */

/*
 * game_information_view.cpp
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

#include "game_information_view.h"

#include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace csuper;


//
// Constructor and destructor
//
GameInformationView::GameInformationView(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Box(cobject)
{
    refGlade->get_widget("main_window_side_game_information_label", game_info_label_);
    refGlade->get_widget("main_window_side_game_information_distributor", distributor_);
    refGlade->get_widget("main_window_side_game_information_change_distributor_button", change_distributor_);
    refGlade->get_widget("main_window_side_game_information_total_points_in_turn_label", total_poins_);
    refGlade->get_widget("main_window_side_separator3", sep_);

    change_distributor_->signal_clicked().connect(mem_fun(*this,&GameInformationView::changeDistributor));
    change_distributor_->set_sensitive(false);
}


//
// Function
//
void GameInformationView::updateDistributor()
{
    if (app()->game()->config().useDistributor())
    {
        change_distributor_->set_sensitive(true);
        distributor_->set_text(ustring::compose(_("The distributor is %1"),app()->game()->distributorName()));
    }
    else
    {
        change_distributor_->set_sensitive(false);
        distributor_->set_text(_("There is no distributor in this game"));
    }
}

void GameInformationView::changeDistributor()
{
    if(app()->changeDistributorDialog()->launch())
        distributor_->set_text(ustring::compose(_("The distributor is %1"),app()->game()->distributorName()));
}
