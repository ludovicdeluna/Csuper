/*!
 * \file    csu_application.cpp
 * \author  Remi BERTHO
 * \date    28/07/15
 * \version 4.3.0
 */

/*
 * csu_application.cpp
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

#include <iostream>
#include <glibmm/i18n.h>

#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace std;
using namespace csuper;
using namespace sigc;

//
// Constructor and destructor
//
CsuApplication::CsuApplication(int& argc, char**& argv) : Gtk::Application(argc,argv,"org.dalan.csuper-gtk")
{
    signal_startup().connect(sigc::mem_fun(*this,&CsuApplication::onStartup));

    pref_ = csuper::Preferences::get();
    list_game_config_ = ListGameConfiguration::getMainList();
}

CsuApplication::~CsuApplication()
{
    delete pref_;
    delete list_game_config_;
    delete import_export_game_config_dialog_;
}


//
// Function
//
void CsuApplication::init(RefPtr<Builder>& builder)
{
    builder_ = builder;
    CsuWidget::setApp(this);

    builder_->get_widget_derived("main_window", main_window_);
    builder_->get_widget_derived("about_dialog", about_);
    builder_->get_widget_derived("game_configuration_window", game_config_window_);
    builder_->get_widget_derived("new_game_configuration_dialog", new_game_config_dialog_);
    import_export_game_config_dialog_ = new ImportExportGameConfigurationDialog();
}

int CsuApplication::launch()
{
    return this->run(*main_window_);
}

void CsuApplication::onStartup()
{
    //Load the menu
    add_action("about",mem_fun(*about_,&About::launch));
    add_action("quit",mem_fun(*this,&CsuApplication::onQuit));
    add_action("game_config",mem_fun(*game_config_window_,&GameConfigurationWindow::launch));
    #if GTK_MINOR_VERSION >= 12
    set_accel_for_action("app.about","<primary>a");
    set_accel_for_action("app.quit","<primary>q");
    set_accel_for_action("app.game_config","<primary>g");
    #else
    add_accelerator("<primary>a","app.about");
    add_accelerator("<primary>q","app.quit");
    add_accelerator("<primary>g","app.game_config");
    #endif // GTK_MINOR_VERSION

    RefPtr<Gio::Menu> menu = Gio::Menu::create();
    menu->append(_("Preferences"),"app.preferences");
    menu->append(_("Game configuration"),"app.game_config");
    menu->append(_("About"),"app.about");
    menu->append(_("Quit"),"app.quit");
    set_app_menu(RefPtr<Gio::MenuModel>::cast_static(menu));
}

void CsuApplication::onQuit()
{
    quit();
    about_->hide();
}

