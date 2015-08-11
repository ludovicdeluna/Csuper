/*!
 * \file    preferences.cpp
 * \author  Remi BERTHO
 * \date    10/08/15
 * \version 4.3.0
 */

/*
 * preferences.cpp
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

#include "preferences_window.h"

#include <glibmm/i18n.h>
#include "csu_application.h"


using namespace Gtk;
using namespace Glib;
using namespace csuper;

PreferencesWindow::PreferencesWindow(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), ApplicationWindow(cobject)
{
    refGlade->get_widget("preferences_main_grid", main_grid_);
    refGlade->get_widget("preferences_notebook", notebook_);
    refGlade->get_widget("preferences_buttonbox", button_box_);
    refGlade->get_widget("preferences_apply_button", apply_button_);
    refGlade->get_widget("preferences_ok_button", ok_button_);
    refGlade->get_widget("preferences_close_button", close_button_);
    refGlade->get_widget("preferences_exportation_label", exportation_label_);
    refGlade->get_widget("preferences_display_label", display_label_);

    close_button_->set_image_from_icon_name("window-close",ICON_SIZE_BUTTON);
    apply_button_->set_image_from_icon_name("gtk-apply",ICON_SIZE_BUTTON);
    ok_button_->set_image_from_icon_name("gtk-ok",ICON_SIZE_BUTTON);

    close_button_->signal_clicked().connect(mem_fun(*this,&PreferencesWindow::stop));
    apply_button_->signal_clicked().connect(mem_fun(*this,&PreferencesWindow::apply));
    ok_button_->signal_clicked().connect(mem_fun(*this,&PreferencesWindow::validate));
}


//
// Launch, stop
//
void PreferencesWindow::launch()
{
    app()->displayPreferencesWindow()->update();
    app()->exportationPreferencesWindow()->update();
    apply_button_->set_sensitive(false);
    ok_button_->set_sensitive(false);
    notebook_->set_current_page(0);
    show_all();
}

void PreferencesWindow::stop()
{
    hide();
}

//
// Function
//
void PreferencesWindow::hasChange()
{
    auto pdf = app()->exportationPreferencesWindow()->readPdf();
    auto chart = app()->exportationPreferencesWindow()->readChart();
    auto title_bar = app()->displayPreferencesWindow()->readTitleBar();

    if (pdf != app()->pref()->exportPdf() ||
        chart != app()->pref()->chartExportation() ||
        title_bar != app()->pref()->mainWindowTitleBar())
    {
        apply_button_->set_sensitive(true);
        ok_button_->set_sensitive(true);
    }
    else
    {
        apply_button_->set_sensitive(false);
        ok_button_->set_sensitive(false);
    }
}

void PreferencesWindow::apply()
{
    auto pdf = app()->exportationPreferencesWindow()->readPdf();
    auto chart = app()->exportationPreferencesWindow()->readChart();
    auto title_bar = app()->displayPreferencesWindow()->readTitleBar();

    app()->pref()->exportPdf() = pdf;
    app()->pref()->chartExportation() = chart;
    app()->pref()->mainWindowTitleBar() = title_bar;
    app()->pref()->writeToFile();

    apply_button_->set_sensitive(false);
    ok_button_->set_sensitive(false);
}

void PreferencesWindow::validate()
{
    auto pdf = app()->exportationPreferencesWindow()->readPdf();
    auto chart = app()->exportationPreferencesWindow()->readChart();
    auto title_bar = app()->displayPreferencesWindow()->readTitleBar();

    app()->pref()->exportPdf() = pdf;
    app()->pref()->chartExportation() = chart;
    app()->pref()->mainWindowTitleBar() = title_bar;
    app()->pref()->writeToFile();

    stop();
}
