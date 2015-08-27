/*!
 * \file    statistics_dialog.cpp
 * \author  Remi BERTHO
 * \date    27/08/15
 * \version 4.3.0
 */

/*
 * statistics_dialog.cpp
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

 #include "statistics_dialog.h"

 #include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace csuper;
using namespace std;


//
// Constructor and destructor
//
StatisticsDialog::StatisticsDialog(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Dialog(cobject)
{
    refGlade->get_widget("statistics_dialog_validate_button", ok_button_);
    refGlade->get_widget("statistics_dialog_main_grid", main_grid_);
    refGlade->get_widget("statistics_dialog_scrolledwindow", scrolled_window_);
    refGlade->get_widget("statistics_dialog_viewport", viewport_);
    refGlade->get_widget("statistics_dialog_title_label", stat_label_);

    ok_button_->set_image_from_icon_name("gtk-ok",ICON_SIZE_BUTTON);


}

//
// Function
//
void StatisticsDialog::launch()
{
    Grid* stat_grid = new Grid();

    stat_grid->set_column_spacing(5);
    stat_grid->set_row_spacing(5);
    #if GTK_MINOR_VERSION >= 12
    stat_grid->set_margin_end(10);
    stat_grid->set_margin_start(10);
    #else
    stat_grid->set_margin_right(10);
    stat_grid->set_margin_left(10);
    #endif // GTK_MINOR_VERSION
    stat_grid->set_margin_top(10);
    stat_grid->set_margin_bottom(10);
    stat_grid->set_hexpand(true);
    stat_grid->set_vexpand(true);

    unsigned int nb_row;
    if (app()->game()->config().turnBased())
        nb_row = 7;
    else
        nb_row = 3;

    for (unsigned int i=0 ; i< nb_row + 1 ; i++)
        stat_grid->attach(*(manage(new Separator(ORIENTATION_HORIZONTAL))),0,2*i,2*app()->game()->nbPlayer() + 3,1);

    stat_grid->attach(*(manage(new Label(_("Name")))),1,1,1,1);
    stat_grid->attach(*(manage(new Label(_("Mean points")))),1,3,1,1);
    stat_grid->attach(*(manage(new Label(_("Number of turn")))),1,5,1,1);
    if (app()->game()->config().turnBased())
    {
        stat_grid->attach(*(manage(new Label(_("Number of turn with the best score")))),1,7,1,1);
        stat_grid->attach(*(manage(new Label(_("Number of turn with the worst score")))),1,9,1,1);
        stat_grid->attach(*(manage(new Label(_("Number of turn first")))),1,11,1,1);
        stat_grid->attach(*(manage(new Label(_("Number of turn last")))),1,13,1,1);
    }
    stat_grid->attach(*(manage(new Separator(ORIENTATION_VERTICAL))),0,0,1,2*nb_row+1);
    stat_grid->attach(*(manage(new Separator(ORIENTATION_VERTICAL))),2,0,1,2*nb_row+1);

    for (unsigned int i=0 ; i<app()->game()->nbPlayer() ; i++)
    {
        Label* tmp_label;

        tmp_label = manage(new Label(app()->game()->playerName(i)));
        tmp_label->set_hexpand(true);
        tmp_label->set_hexpand(true);
        stat_grid->attach(*tmp_label,2*(i+1)+1,1,1,1);

        tmp_label = manage(new Label(app()->game()->meanPointsUstring(i)));
        tmp_label->set_hexpand(true);
        tmp_label->set_hexpand(true);
        stat_grid->attach(*tmp_label,2*(i+1)+1,3,1,1);

        tmp_label = manage(new Label(app()->game()->nbTurnUstring(i)));
        tmp_label->set_hexpand(true);
        tmp_label->set_hexpand(true);
        stat_grid->attach(*tmp_label,2*(i+1)+1,5,1,1);

        if (app()->game()->config().turnBased())
        {
            tmp_label = manage(new Label(app()->game()->nbTurnBestUstring(i)));
            tmp_label->set_hexpand(true);
            tmp_label->set_hexpand(true);
            stat_grid->attach(*tmp_label,2*(i+1)+1,7,1,1);

            tmp_label = manage(new Label(app()->game()->nbTurnWorstUstring(i)));
            tmp_label->set_hexpand(true);
            tmp_label->set_hexpand(true);
            stat_grid->attach(*tmp_label,2*(i+1)+1,9,1,1);

            tmp_label = manage(new Label(app()->game()->nbTurnFirstUstring(i)));
            tmp_label->set_hexpand(true);
            tmp_label->set_hexpand(true);
            stat_grid->attach(*tmp_label,2*(i+1)+1,11,1,1);

            tmp_label = manage(new Label(app()->game()->nbTurnLastUstring(i)));
            tmp_label->set_hexpand(true);
            tmp_label->set_hexpand(true);
            stat_grid->attach(*tmp_label,2*(i+1)+1,13,1,1);
        }

        stat_grid->attach(*(manage(new Separator(ORIENTATION_VERTICAL))),2*(2+i),0,1,2*nb_row+1);
    }

    viewport_->add(*stat_grid);
    show_all();
    run();

    hide();
    delete stat_grid;
}
