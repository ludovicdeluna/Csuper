/*!
 * \file    display_preferences.cpp
 * \author  Remi BERTHO
 * \date    10/08/15
 * \version 4.3.0
 */

/*
 * display_preferences.cpp
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

#include "display_preferences.h"

#include <glibmm/i18n.h>
#include "csu_application.h"


using namespace Gtk;
using namespace Glib;
using namespace csuper;

DisplayPreferences::DisplayPreferences(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), ScrolledWindow(cobject)
{
    refGlade->get_widget("preferences_display_grid", main_grid_);
    refGlade->get_widget("preferences_display_viewport", viewport_);

    refGlade->get_widget("preferences_display_title_bar_label", title_bar_label_);
    refGlade->get_widget("preferences_display_main_window_decoration_label", title_bar_decoration_label_);
    refGlade->get_widget("preferences_display_main_window_decoration_switch", title_bar_decoration_switch_);
    refGlade->get_widget("preferences_display_title_bar_title_label", title_bar_title_label_);
    refGlade->get_widget("preferences_display_title_bar_title_switch", title_bar_title_switch_);

    title_bar_decoration_switch_->property_active().signal_changed().connect(
                                    mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));

    title_bar_title_switch_->property_active().signal_changed().connect(
                                    mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
}


//
// Function
//
void DisplayPreferences::update()
{
    title_bar_decoration_switch_->set_active(app()->pref()->mainWindowTitleBar().disableWindowManagerDecoration());
    title_bar_title_switch_->set_active(app()->pref()->mainWindowTitleBar().printTitle());
}

MainWindowTitleBarPreferences DisplayPreferences::readTitleBar()
{
    MainWindowTitleBarPreferences pref;

    pref.setDisableWindowManagerDecoration(title_bar_decoration_switch_->get_active());
    pref.setPrintTitle(title_bar_title_switch_->get_active());

    return pref;
}
