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
 * along with this program; if not, write to the Free Software
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
using namespace std;
using namespace csuper;

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
        pref_menu_item_->signal_activate().connect(mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::launch));
        about_menu_item_->signal_activate().connect(mem_fun(*(app()->about()),&About::launch));
        quit_menu_item_->signal_activate().connect(mem_fun(*(app()),&CsuApplication::onQuit));

        game_config_menu_item_->add_accelerator("activate",get_accel_group(),GDK_KEY_G,Gdk::CONTROL_MASK,ACCEL_VISIBLE);
        pref_menu_item_->add_accelerator("activate",get_accel_group(),GDK_KEY_P,Gdk::CONTROL_MASK,ACCEL_VISIBLE);
        about_menu_item_->add_accelerator("activate",get_accel_group(),GDK_KEY_A,Gdk::CONTROL_MASK,ACCEL_VISIBLE);
        quit_menu_item_->add_accelerator("activate",get_accel_group(),GDK_KEY_Q,Gdk::CONTROL_MASK,ACCEL_VISIBLE);

        csuper_menu_button_->set_popup(*csuper_menu_);
        csuper_menu_->show_all();

        header_bar_->pack_start(*csuper_menu_button_);

        main_grid_->attach(*header_bar_,0,0,1,1);
    }


    // New button
    new_button_ = manage(new Button(_("New")));
    new_button_->set_image_from_icon_name("document-new",ICON_SIZE_SMALL_TOOLBAR);
    new_button_->set_always_show_image(true);
    new_button_->add_accelerator("clicked",get_accel_group(),GDK_KEY_N,Gdk::CONTROL_MASK,ACCEL_VISIBLE);
    new_button_->set_tooltip_text(_("Create a new CSU file"));
    new_button_->show_all();
    new_button_->signal_clicked().connect(mem_fun(*(app()->newFileAssistant()),&NewFileAssistant::launch));
    header_bar_->pack_start(*new_button_);


    // Open button
    open_button_ = manage(new Button(_("Open")));
    open_button_->set_image_from_icon_name("document-open",ICON_SIZE_SMALL_TOOLBAR);
    open_button_->set_always_show_image(true);
    open_button_->add_accelerator("clicked",get_accel_group(),GDK_KEY_O,Gdk::CONTROL_MASK,ACCEL_VISIBLE);
    open_button_->set_tooltip_text(_("Open a existing CSU file"));
    open_button_->show_all();
    open_button_->signal_clicked().connect(mem_fun(*this,&MainWindow::openFile));
    header_bar_->pack_start(*open_button_);


    // Open recent button
    open_recent_button_ = manage(new MenuButton());
    open_recent_button_->add_label(_("Recent"));
    open_recent_button_->set_tooltip_text(_("Open a recent CSU file"));
    open_recent_menu_ = manage(new RecentChooserMenu());
    open_recent_button_->set_popup(*open_recent_menu_);
    open_recent_filter_ = RecentFilter::create();
    open_recent_filter_->add_pattern("*.csu");
    open_recent_filter_->add_mime_type("application/csu");
    open_recent_menu_->set_filter(open_recent_filter_);
    open_recent_button_->show_all();
    open_recent_menu_->signal_item_activated().connect(mem_fun(*this,&MainWindow::openRecentFile));
    header_bar_->pack_start(*open_recent_button_);



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


    // Resize
    resize(app()->pref()->mainWindowSize().width(),app()->pref()->mainWindowSize().height());
    if (app()->pref()->mainWindowSize().isMaximize())
        maximize();
    else
        unmaximize();


    main_grid_->show_all();
}


//
// function
//
void MainWindow::saveSize()
{
    int width;
    int height;
    bool is_maximize = false;
    get_size(width,height);

    #if GTK_MINOR_VERSION >= 12
    is_maximize = is_maximized();
    #endif // GTK_MINOR_VERSION

    app()->pref()->mainWindowSize().setIsMaximize(is_maximize);

    if (!is_maximize)
    {
        app()->pref()->mainWindowSize().setWidth(width);
        app()->pref()->mainWindowSize().setHeight(height);
    }

    app()->pref()->writeToFile();
}

void MainWindow::openFile()
{
    // File chooser dialog
    FileChooserDialog* file_chooser = new FileChooserDialog(*this,_("Open file"),FILE_CHOOSER_ACTION_OPEN);
    file_chooser->add_button(_("Open"),RESPONSE_ACCEPT);
    file_chooser->add_button(_("Cancel"),RESPONSE_CANCEL);
    file_chooser->set_current_folder(filename_from_utf8(app()->pref()->directory().open()));


    // File filter
    RefPtr<FileFilter> csu_file_filter = FileFilter::create();
    csu_file_filter->add_mime_type("application/csu");
    csu_file_filter->add_pattern("*.csu");
    csu_file_filter->set_name(_("CSU file"));
    RefPtr<FileFilter> all_file_filter = FileFilter::create();
    all_file_filter->add_pattern("*");
    all_file_filter->set_name(_("All file"));
    file_chooser->add_filter(csu_file_filter);
    file_chooser->add_filter(all_file_filter);


    // Run
    ustring new_filename;

    switch (file_chooser->run())
    {
    case RESPONSE_ACCEPT:
        file_chooser->hide();

        new_filename = filename_to_utf8(file_chooser->get_filename());

        try
        {
            Game* tmp_game = new Game(new_filename);
            app()->setGame(tmp_game);
            app()->setFilename(new_filename);
        }
        catch(Glib::Exception& e)
        {
            cerr << e.what() << endl;
            MessageDialog* error = new MessageDialog(*this,e.what(),false,MESSAGE_ERROR,BUTTONS_OK,true);
            error->run();
            error->hide();
            delete error;
        }
        break;
    default:
        file_chooser->hide();
        break;
    }

    delete file_chooser;
}


void MainWindow::openRecentFile()
{
    ustring filename = filename_to_utf8(filename_from_uri(open_recent_menu_->get_current_uri()));

    try
    {
        Game* tmp_game = new Game(filename);
        app()->setGame(tmp_game);
        app()->setFilename(filename);
    }
    catch(Glib::Exception& e)
    {
        cerr << e.what() << endl;
        MessageDialog* error = new MessageDialog(*this,e.what(),false,MESSAGE_ERROR,BUTTONS_OK,true);
        error->run();
        error->hide();
        delete error;
    }
}
