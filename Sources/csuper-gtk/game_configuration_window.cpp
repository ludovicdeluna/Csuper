/*!
 * \file    game_configuration_window.cpp
 * \author  Remi BERTHO
 * \date    04/08/15
 * \version 4.3.0
 */

/*
 * game_configuration_window.cpp
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


#include "game_configuration_window.h"

#include "../libcsuper/libcsuper.h"
#include <glibmm/i18n.h>
#include "csu_application.h"


using namespace Gtk;
using namespace Glib;
using namespace csuper;
using namespace sigc;
using namespace std;


//
// Constructor and destructor
//
GameConfigurationWindow::GameConfigurationWindow(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), ApplicationWindow(cobject)
{
    refGlade->get_widget("game_configuration_preferences_grid", main_grid_);
    refGlade->get_widget("game_configuration_preferences_scrolled_window", scrolled_window_);
    refGlade->get_widget("game_configuration_preferences_viewport", viewport_);
    refGlade->get_widget("game_configuration_preferences_buttonbox", button_box_);
    refGlade->get_widget("add_game_configuration_button", add_button_);
    refGlade->get_widget("import_game_configuration_button", import_button_);
    refGlade->get_widget("export_game_configuration_button", export_button_);
    refGlade->get_widget("close_game_configuration_preferences_button", close_button_);
    refGlade->get_widget("game_configuration_preferences_label_list", list_label_);
    refGlade->get_widget("game_configuration_preferences_label_details", detail_label_);
    refGlade->get_widget("game_configuration_preferences_label", selected_pref_label_);
    refGlade->get_widget("game_configuration_preferences_label_name", config_name_label_);

    close_button_->set_image_from_icon_name("window-close",ICON_SIZE_BUTTON);
    add_button_->set_image_from_icon_name("list-add",ICON_SIZE_BUTTON);

    close_button_->signal_clicked().connect(mem_fun(*this,&GameConfigurationWindow::stop));
    add_button_->signal_clicked().connect(mem_fun(*this,&GameConfigurationWindow::addGameConfig));
    import_button_->signal_clicked().connect(mem_fun(*this,&GameConfigurationWindow::importGameConfig));
    export_button_->signal_clicked().connect(mem_fun(*this,&GameConfigurationWindow::exportGameConfig));
}



GameConfigurationWindow::~GameConfigurationWindow()
{
    if (game_config_grid_)
        delete game_config_grid_;
}



//
// Launch, stop
//
void GameConfigurationWindow::launch()
{
    updateList();
    show_all();
}

void GameConfigurationWindow::stop()
{
    hide();
}

//
// Function
//
void GameConfigurationWindow::updateList()
{
    if (game_config_grid_)
        delete game_config_grid_;


    game_config_grid_ = new Grid();
    game_config_grid_->set_row_spacing(10);
    game_config_grid_->set_column_spacing(10);
    #if GTK_MINOR_VERSION >= 12
    game_config_grid_->set_margin_end(10);
    game_config_grid_->set_margin_start(10);
    #else
    game_config_grid_->set_margin_right(10);
    game_config_grid_->set_margin_left(10);
    #endif // GTK_MINOR_VERSION
    game_config_grid_->set_margin_top(10);
    game_config_grid_->set_margin_bottom(10);

    Label* tmp_label;
    Button* tmp_edit_button;
    Button* tmp_propertie_button;
    Button* tmp_delete_button;
    for (unsigned int i=0 ; i < app()->listGameConfig()->size() ; i++)
    {
        // Label
        tmp_label = manage(new Label(app()->listGameConfig()->at(i).name()));
        tmp_label->set_hexpand(true);
        game_config_grid_->attach(*tmp_label,0,i,1,1);


        // Button
        tmp_edit_button = manage(new Button(_("Edit")));
        tmp_propertie_button = manage(new Button(_("Properties")));
        tmp_delete_button = manage(new Button(_("Delete")));

        tmp_edit_button->set_image_from_icon_name("gtk-edit",ICON_SIZE_BUTTON);
        tmp_propertie_button->set_image_from_icon_name("document-properties",ICON_SIZE_BUTTON);
        tmp_delete_button->set_image_from_icon_name("edit-delete",ICON_SIZE_BUTTON);

        tmp_edit_button->set_always_show_image(true);
        tmp_propertie_button->set_always_show_image(true);
        tmp_delete_button->set_always_show_image(true);

        tmp_edit_button->set_tooltip_text(_("View the details of the game configuration"));
        tmp_propertie_button->set_tooltip_text(_("Delete the game configuration"));
        tmp_delete_button->set_tooltip_text(_("Edit the game configuration"));

        game_config_grid_->attach(*tmp_edit_button,1,i,1,1);
        game_config_grid_->attach(*tmp_propertie_button,2,i,1,1);
        game_config_grid_->attach(*tmp_delete_button,3,i,1,1);

        tmp_delete_button->signal_clicked().connect
            (bind<-1, const unsigned int>(mem_fun(*this,&GameConfigurationWindow::deleteGameConfig),i));
        tmp_propertie_button->signal_clicked().connect
            (bind<-1, const unsigned int>(mem_fun(*this,&GameConfigurationWindow::viewGameConfig),i));
        tmp_edit_button->signal_clicked().connect
            (bind<-1, const unsigned int>(mem_fun(*this,&GameConfigurationWindow::editGameConfig),i));
    }


    viewport_->add(*game_config_grid_);
    viewport_->show_all();
}


//
// Edit, delete, view
//
void GameConfigurationWindow::deleteGameConfig(const unsigned int id)
{
    app()->listGameConfig()->remove(id);
    app()->listGameConfig()->writeToFile();

    if (id == game_config_displayed_)
    {
        detail_label_->set_markup("<span size=\"large\">You have no game configuration selected.</span>");
        config_name_label_->set_markup("");
    }

    updateList();
}

void GameConfigurationWindow::viewGameConfig(const unsigned int id)
{
    game_config_displayed_ = id;

    detail_label_->set_markup("<span size=\"large\">" + app()->listGameConfig()->at(id).toUstringWithoutName() + "</span>");
    config_name_label_->set_markup("<span size=\"x-large\">" + app()->listGameConfig()->at(id).name() + "</span>");
}

void GameConfigurationWindow::editGameConfig(const unsigned int id)
{
    if (app()->newGameConfigurationDialog()->launch(app()->listGameConfig()->at(id),*this))
    {
        app()->listGameConfig()->writeToFile();
        updateList();
        if (id == game_config_displayed_)
            viewGameConfig(id);
    }
}


//
// Add' export, import
//
void GameConfigurationWindow::addGameConfig()
{
    GameConfiguration* game_config = new GameConfiguration();

    if (app()->newGameConfigurationDialog()->launch(*game_config,*this))
    {
        app()->listGameConfig()->add(game_config);
        app()->listGameConfig()->writeToFile();
        updateList();
    }
    else
        delete game_config;
}


void GameConfigurationWindow::exportGameConfig()
{
    vector<unsigned int> id = app()->importExportGameConfigurationDialog()->launch(*(app()->listGameConfig()),false);

    if (id.empty())
        return;

    FileChooserDialog* file_chooser = new FileChooserDialog(*this,_("Export file"),FILE_CHOOSER_ACTION_SAVE);
    file_chooser->add_button(_("Accept"),RESPONSE_ACCEPT);
    file_chooser->add_button(_("Cancel"),RESPONSE_CANCEL);
    file_chooser->set_current_folder(filename_from_utf8(app()->pref()->directory().open()));

    switch (file_chooser->run())
    {
    case RESPONSE_ACCEPT:
        file_chooser->hide();
        try
        {
            app()->listGameConfig()->writeToFile(filename_to_utf8(file_chooser->get_filename()),id);
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


void GameConfigurationWindow::importGameConfig()
{
    FileChooserDialog* file_chooser = new FileChooserDialog(*this,_("Import file"),FILE_CHOOSER_ACTION_SAVE);
    file_chooser->add_button(_("Accept"),RESPONSE_ACCEPT);
    file_chooser->add_button(_("Cancel"),RESPONSE_CANCEL);
    file_chooser->set_current_folder(filename_from_utf8(app()->pref()->directory().open()));

    switch (file_chooser->run())
    {
    case RESPONSE_ACCEPT:
        file_chooser->hide();

        try
        {
             ListGameConfiguration list_game_config(filename_to_utf8(file_chooser->get_filename()));

            vector<unsigned int> id = app()->importExportGameConfigurationDialog()->launch(list_game_config,false);

            if (!(id.empty()))
            {
                app()->listGameConfig()->add(list_game_config,id);
                app()->listGameConfig()->writeToFile();
                updateList();
            }
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
