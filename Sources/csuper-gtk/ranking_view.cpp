/*!
 * \file    ranking_view.cpp
 * \author  Remi BERTHO
 * \date    18/09/15
 * \version 4.3.0
 */

/*
 * ranking_view.cpp
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

#include "ranking_view.h"

#include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace csuper;
using namespace std;

//
// Constructor and destructor
//
RankingView::RankingView(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Box(cobject)
{
    refGlade->get_widget("main_window_side_ranking_label", rank_label_);
    refGlade->get_widget("main_window_side_ranking_scrolledwindow", scroll_);
    refGlade->get_widget("main_window_side_ranking_viewport", viewport_);
    refGlade->get_widget("main_window_side_separator1", sep_);

    Label* no_csu_file = manage(new Label(_("No csu file loaded")));
    no_csu_file->set_vexpand(true);
    viewport_->add(*no_csu_file);
}


//
// Function
//
void RankingView::update()
{
    if (app()->game() == nullptr)
        return;

    delete viewport_->get_child();


    // Set the grid
    Grid* grid = new Grid();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    #if GTK_MINOR_VERSION >= 12
    grid->set_margin_end(10);
    grid->set_margin_start(10);
    #else
    grid->set_margin_right(10);
    grid->set_margin_left(10);
    #endif // GTK_MINOR_VERSION
    grid->set_margin_top(10);
    grid->set_margin_bottom(10);


    // Set the column name
    grid->attach(*manage(new Label(_("Position"))),0,0,1,1);
    grid->attach(*manage(new Label(_("Name"))),1,0,1,1);
    grid->attach(*manage(new Label(_("Points"))),2,0,1,1);
    if (app()->pref()->differenceBetweenPlayer().consecutive())
        grid->attach(*manage(new Label(_("Diff cons"))),3,0,1,1);
    if (app()->pref()->differenceBetweenPlayer().first())
        grid->attach(*manage(new Label(_("Diff first"))),4,0,1,1);
    if (app()->pref()->differenceBetweenPlayer().last())
        grid->attach(*manage(new Label(_("Diff last"))),5,0,1,1);


    // Get info
    auto rank_index = app()->game()->playerIndexFromPosition();
    double first_points = app()->game()->totalPoints(rank_index[0]);
    double last_points = app()->game()->totalPoints(rank_index[app()->game()->nbPlayer()-1]);
    double previous_points;
    unsigned int rank = 1;


    // Set all the information
    for (unsigned int i=0 ; i<app()->game()->nbPlayer() ; i++)
    {
        double points = app()->game()->totalPoints(rank_index[i]);

        int pos = 3;

        if (i>0 && points != previous_points)
            rank = i+1;

        grid->attach(*manage(new Label(intToUstring(rank))),0,i+1,1,1);
        grid->attach(*manage(new Label(app()->game()->playerName(rank_index[i]))),1,i+1,1,1);
        grid->attach(*manage(new Label(app()->game()->totalPointsUstring(rank_index[i]))),2,i+1,1,1);
        if (app()->pref()->differenceBetweenPlayer().consecutive() && i>0)
        {
            grid->attach(*manage(new Label(doubleToUstring(fabs(previous_points-points),
                                                           app()->game()->config().decimalPlace())))
                         ,pos,i+1,1,1);
            pos++;
        }
        if (app()->pref()->differenceBetweenPlayer().first())
        {
            grid->attach(*manage(new Label(doubleToUstring(fabs(first_points-points),
                                                           app()->game()->config().decimalPlace()))),
                         pos,i+1,1,1);
            pos++;
        }
        if (app()->pref()->differenceBetweenPlayer().last())
        {
            grid->attach(*manage(new Label(doubleToUstring(fabs(last_points-points),
                                                           app()->game()->config().decimalPlace()))),
                         pos,i+1,1,1);
        }

        previous_points = points;
    }


    viewport_->add(*grid);
    grid->show_all();
}
