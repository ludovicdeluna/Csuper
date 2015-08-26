/*!
 * \file    game_over_dialog.cpp
 * \author  Remi BERTHO
 * \date    26/08/15
 * \version 4.3.0
 */

/*
 * game_over_dialog.cpp
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

#include "game_over_dialog.h"

#include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace Gdk;
using namespace csuper;
using namespace std;


//
// Constructor and destructor
//
GameOverDialog::GameOverDialog(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Dialog(cobject)
{
    refGlade->get_widget("dialog_game_over_button", ok_button_);
    refGlade->get_widget("game_over_dialog_fixed", fixed_);
    refGlade->get_widget("game_over_dialog_label", label_);

    try
    {
        RefPtr<Pixbuf> podium_pixbuf = Pixbuf::create_from_file("Images/Podium.png",500,280);
        podium_ = manage(new Image(podium_pixbuf));
    }
    catch (Glib::Exception& e)
    {
        cerr << e.what() << endl;
    }

    fixed_->put(*podium_,0,20);

    ok_button_->set_image_from_icon_name("gtk-ok",ICON_SIZE_BUTTON);


}

//
// Function
//
void GameOverDialog::launch()
{
    vector<unsigned int> rank = app()->game()->playerIndexFromPosition();

    ustring tmp_player_name = app()->game()->playerName(rank[0]);
    Label* first_label = new Label(ustring::compose("<span foreground=\"green\" size=\"x-large\">%1</span>",tmp_player_name));
    first_label->set_use_markup(true);
    fixed_->put(*first_label,250-tmp_player_name.length()*9/2,47);

    Label* secound_label = nullptr;
    if (app()->game()->nbPlayer() >= 2)
    {
        tmp_player_name = app()->game()->playerName(rank[1]);
        secound_label = new Label(ustring::compose("<span foreground=\"blue\" size=\"x-large\">%1</span>",tmp_player_name));
        secound_label->set_use_markup(true);
        fixed_->put(*secound_label,90-tmp_player_name.length()*9/2,118);
    }

    Label* third_label = nullptr;
    if (app()->game()->nbPlayer() >= 3)
    {
        tmp_player_name = app()->game()->playerName(rank[2]);
        third_label = new Label(ustring::compose("<span foreground=\"red\" size=\"x-large\">%1</span>",tmp_player_name));
        third_label->set_use_markup(true);
        fixed_->put(*third_label,410-tmp_player_name.length()*9/2,158);
    }

    show_all();
    run();

    hide();

    delete first_label;
    if (secound_label != nullptr)
        delete secound_label;
    if (third_label != nullptr)
        delete third_label;
}
