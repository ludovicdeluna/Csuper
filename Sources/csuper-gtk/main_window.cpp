/*!
 * \file    main_window.cpp
 * \author  Remi BERTHO
 * \date    28/07/15
 * \version 4.3.0
 */

/*
 * main_window.cpp
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

#include "main_window.h"

#include <glibmm/i18n.h>
#include "csu_application.h"


using namespace Gtk;
using namespace Glib;

MainWindow::MainWindow(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), ApplicationWindow(cobject)
{
    refGlade->get_widget("main_grid", main_grid_);

    // Header bar
    header_bar_ = manage(new HeaderBar());
    #if GTK_MINOR_VERSION >= 12
    header_bar_->set_has_subtitle(true);
    #endif // GTK_MINOR_VERSION

    if (app()->pref()->mainWindowTitleBar().disableWindowManagerDecoration())
    {
        header_bar_->set_title(_("Csuper"));
        header_bar_->set_show_close_button(true);
        header_bar_->show_all();
        set_titlebar(*header_bar_);
    }
    else
    {
        if (app()->pref()->mainWindowTitleBar().printTitle())
            header_bar_->set_title(_("Csuper"));

        header_bar_->set_show_close_button(false);
        header_bar_->set_hexpand(true);

        csuper_menu_button_ = manage(new MenuButton());
        csuper_menu_button_->add_label(_("Csuper"));
        csuper_menu_ = manage(new Gtk::Menu());

        game_config_menu_item_ = manage(new MenuItem(_("Game configuration")));
        pref_menu_item_ = manage(new MenuItem(_("Preferences")));
        about_menu_item_ = manage(new MenuItem(_("About")));
        quit_menu_item_ = manage(new MenuItem(_("Quit")));

        csuper_menu_->attach(*game_config_menu_item_,0,1,0,1);
        csuper_menu_->attach(*pref_menu_item_,0,1,1,2);
        csuper_menu_->attach(*about_menu_item_,0,1,2,3);
        csuper_menu_->attach(*quit_menu_item_,0,1,3,4);

        game_config_menu_item_->signal_activate().connect(mem_fun(*(app()->gameConfigurationWindow()),&GameConfigurationWindow::launch));
        about_menu_item_->signal_activate().connect(mem_fun(*(app()->about()),&About::launch));
        quit_menu_item_->signal_activate().connect(mem_fun(*(app()),&CsuApplication::onQuit));

        game_config_menu_item_->add_accelerator("activate",get_accel_group(),GDK_KEY_G,Gdk::CONTROL_MASK,ACCEL_VISIBLE);
        about_menu_item_->add_accelerator("activate",get_accel_group(),GDK_KEY_A,Gdk::CONTROL_MASK,ACCEL_VISIBLE);
        quit_menu_item_->add_accelerator("activate",get_accel_group(),GDK_KEY_Q,Gdk::CONTROL_MASK,ACCEL_VISIBLE);

        csuper_menu_button_->set_popup(*csuper_menu_);
        csuper_menu_->show_all();

        header_bar_->pack_start(*csuper_menu_button_);

        main_grid_->attach(*header_bar_,0,0,1,1);
    }



    // Display menu
    menu_display_button_ = manage(new MenuButton());
    menu_display_button_->add_label(_("Display"));
    menu_display_button_->set_popup(*(app()->menuDisplay()));
    header_bar_->pack_end(*menu_display_button_);
    menu_display_button_->show_all();


    // Edit menu
    menu_edit_button_ = manage(new MenuButton());
    menu_edit_button_->add_label(_("Edit"));
    menu_edit_button_->set_popup(*(app()->menuEdit()));
    header_bar_->pack_end(*menu_edit_button_);
    menu_edit_button_->show_all();


    // File menu
    menu_file_button_ = manage(new MenuButton());
    menu_file_button_->add_label(_("File"));
    menu_file_button_->set_popup(*(app()->menuFile()));
    header_bar_->pack_end(*menu_file_button_);
    menu_file_button_->show_all();

    main_grid_->show_all();
}
