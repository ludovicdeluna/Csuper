/*!
 * \file    menu_display.cpp
 * \author  Remi BERTHO
 * \date    06/08/15
 * \version 4.3.0
 */

/*
 * menu_display.cpp
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

#include "menu_display.h"

#include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace Gdk;
using namespace csuper;

MenuDisplay::MenuDisplay(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Menu(cobject)
{
    set_accel_group(app()->mainAccelGroup());


    // Glade
    refGlade->get_widget("menu_display_podium", podium_);
    refGlade->get_widget("menu_display_chart_total_points", chart_total_points_);
    refGlade->get_widget("menu_display_chart_points", chart_points_);
    refGlade->get_widget("menu_display_statistics", statistics_);

    refGlade->get_widget("menuitem_separator_1", sep_1_);

    refGlade->get_widget("menu_display_consecutive", cons_);
    refGlade->get_widget("menu_display_first", first_);
    refGlade->get_widget("menu_display_last", last_);

    refGlade->get_widget("menuitem_separator_2", sep_2_);

    refGlade->get_widget("menu_display_totalpoints", total_points_);
    refGlade->get_widget("menu_display_ranking", ranking_);
    refGlade->get_widget("menu_display_edit_suppr", edit_suppr_);

    refGlade->get_widget("menuitem_separator3", sep_3_);

    refGlade->get_widget("menu_display_ranking_side", ranking_side_);
    refGlade->get_widget("menu_display_calculator", calculator_);
    refGlade->get_widget("menu_display_game_information", game_information_);


    podium_->set_sensitive(false);
    chart_total_points_->set_sensitive(false);
    chart_points_->set_sensitive(false);
    statistics_->set_sensitive(false);


    // Set from pref
    cons_->set_active(app()->pref()->differenceBetweenPlayer().consecutive());
    first_->set_active(app()->pref()->differenceBetweenPlayer().first());
    last_->set_active(app()->pref()->differenceBetweenPlayer().last());

    total_points_->set_active(app()->pref()->scoreDisplay().totalPoints());
    ranking_->set_active(app()->pref()->scoreDisplay().ranking());
    edit_suppr_->set_active(app()->pref()->scoreDisplay().editSuppr());

    ranking_side_->set_active(app()->pref()->mainWindowDisplay().ranking());
    calculator_->set_active(app()->pref()->mainWindowDisplay().calculator());
    game_information_->set_active(app()->pref()->mainWindowDisplay().gameInformation());


    // Connect signal
    podium_->signal_activate().connect(mem_fun(*this,&MenuDisplay::showGameOver));
    statistics_->signal_activate().connect(mem_fun(*this,&MenuDisplay::showStatistics));

    cons_->signal_toggled().connect(mem_fun(*this,&MenuDisplay::diffChanged));
    first_->signal_toggled().connect(mem_fun(*this,&MenuDisplay::diffChanged));
    last_->signal_toggled().connect(mem_fun(*this,&MenuDisplay::diffChanged));

    total_points_->signal_toggled().connect(mem_fun(*this,&MenuDisplay::scoreDisplayChanged));
    ranking_->signal_toggled().connect(mem_fun(*this,&MenuDisplay::scoreDisplayChanged));
    edit_suppr_->signal_toggled().connect(mem_fun(*this,&MenuDisplay::scoreDisplayChanged));

    ranking_side_->signal_toggled().connect(mem_fun(*this,&MenuDisplay::mainWindowDisplayChanged));
    calculator_->signal_toggled().connect(mem_fun(*this,&MenuDisplay::mainWindowDisplayChanged));
    game_information_->signal_toggled().connect(mem_fun(*this,&MenuDisplay::mainWindowDisplayChanged));


    // Accelerator
    podium_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_I,CONTROL_MASK,ACCEL_VISIBLE);
    chart_total_points_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_W,CONTROL_MASK,ACCEL_VISIBLE);
    chart_points_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_D,CONTROL_MASK,ACCEL_VISIBLE);
    statistics_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_J,CONTROL_MASK,ACCEL_VISIBLE);

    cons_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_C,CONTROL_MASK | SHIFT_MASK,ACCEL_VISIBLE);
    first_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_F,CONTROL_MASK | SHIFT_MASK,ACCEL_VISIBLE);
    last_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_L,CONTROL_MASK | SHIFT_MASK,ACCEL_VISIBLE);

    total_points_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_T,CONTROL_MASK | SHIFT_MASK,ACCEL_VISIBLE);
    ranking_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_N,CONTROL_MASK | SHIFT_MASK,ACCEL_VISIBLE);
    edit_suppr_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_M,CONTROL_MASK | SHIFT_MASK,ACCEL_VISIBLE);

    ranking_side_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_Q,CONTROL_MASK | SHIFT_MASK,ACCEL_VISIBLE);
    calculator_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_Z,CONTROL_MASK | SHIFT_MASK,ACCEL_VISIBLE);
    game_information_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_D,CONTROL_MASK | SHIFT_MASK,ACCEL_VISIBLE);
}


//
// Function
//
void MenuDisplay::setSensitive()
{
    podium_->set_sensitive(true);
    chart_total_points_->set_sensitive(true);
    chart_points_->set_sensitive(true);
    statistics_->set_sensitive(true);
}

void MenuDisplay::diffChanged()
{
    app()->pref()->differenceBetweenPlayer().setConsecutive(cons_->get_active());
    app()->pref()->differenceBetweenPlayer().setFirst(first_->get_active());
    app()->pref()->differenceBetweenPlayer().setLast(last_->get_active());
    app()->pref()->writeToFile();
    app()->ranking()->update();
}


void MenuDisplay::scoreDisplayChanged()
{
    app()->pref()->scoreDisplay().setTotalPoints(total_points_->get_active());
    app()->pref()->scoreDisplay().setRanking(ranking_->get_active());
    app()->pref()->scoreDisplay().setEditSuppr(edit_suppr_->get_active());
    app()->pref()->writeToFile();
}

void MenuDisplay::mainWindowDisplayChanged()
{
    app()->pref()->mainWindowDisplay().setRanking(ranking_side_->get_active());
    app()->pref()->mainWindowDisplay().setCalculator(calculator_->get_active());
    app()->pref()->mainWindowDisplay().setGameInformation(game_information_->get_active());

    if(! app()->pref()->mainWindowDisplay().calculator())
        app()->calculator()->hide();
    else
        app()->calculator()->show();

    if(! app()->pref()->mainWindowDisplay().ranking())
        app()->ranking()->hide();
    else
        app()->ranking()->show();

    if(! app()->pref()->mainWindowDisplay().gameInformation())
        app()->gameInformation()->hide();
    else
        app()->gameInformation()->show();

    app()->pref()->writeToFile();
}

void MenuDisplay::showGameOver()
{
    app()->gameOverDialog()->launch();
}

void MenuDisplay::showStatistics()
{
    app()->statisticsDialog()->launch();
}
