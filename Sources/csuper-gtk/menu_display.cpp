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
 * aint with this program; if not, write to the Free Software
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

MenuDisplay::MenuDisplay(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Menu(cobject)
{
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
}
