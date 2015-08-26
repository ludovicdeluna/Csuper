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
 * along with this program; if not, write to the Free Software
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
using namespace Gio;
using namespace std;
using namespace csuper;
using namespace sigc;

//
// Constructor and destructor
//
CsuApplication::CsuApplication(int& argc, char**& argv) : Gtk::Application(argc,argv,"org.dalan.csuper-gtk",APPLICATION_HANDLES_OPEN)
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
    delete new_file_assistant_;

    if (game_ != nullptr)
        delete game_;
}


//
// Function
//
void CsuApplication::init(RefPtr<Builder>& builder)
{
    builder_ = builder;
    CsuWidget::setApp(this);

    builder_->get_widget_derived("menu_file", menu_file_);
    builder_->get_widget_derived("menu_edit", menu_edit_);
    builder_->get_widget_derived("menu_display", menu_display_);
    builder_->get_widget_derived("about_dialog", about_);
    builder_->get_widget_derived("game_configuration_window", game_config_window_);
    builder_->get_widget_derived("new_game_configuration_dialog", new_game_config_dialog_);
    builder_->get_widget_derived("preferences_window", pref_window_);
    new_file_assistant_ = new NewFileAssistant(builder);
    builder_->get_widget_derived("preferences_exportation_scrolledwindow", export_pref_window_);
    builder_->get_widget_derived("preferences_display_scrolledwindow", display_pref_window_);
    builder_->get_widget_derived("main_window", main_window_);
    builder_->get_widget_derived("file_properties_dialog", file_properties_dialog_);
    builder_->get_widget_derived("game_over_dialog", game_over_dialog_);
    import_export_game_config_dialog_ = new ImportExportGameConfigurationDialog();
}

int CsuApplication::launch()
{
    int res = this->run(*main_window_);
    mainWindow()->saveSize();
    return res;
}

void CsuApplication::onStartup()
{
    //Load the menu
    if (pref()->mainWindowTitleBar().disableWindowManagerDecoration())
    {
        add_action("about",mem_fun(*about_,&About::launch));
        add_action("quit",mem_fun(*this,&CsuApplication::onQuit));
        add_action("game_config",mem_fun(*game_config_window_,&GameConfigurationWindow::launch));
        add_action("preferences",mem_fun(*pref_window_,&PreferencesWindow::launch));
        add_action("update",bind<-1, const bool>(mem_fun(*this,&CsuApplication::checkForUpdate),false));
        #if GTK_MINOR_VERSION >= 12
        set_accel_for_action("app.about","<primary>a");
        set_accel_for_action("app.quit","<primary>q");
        set_accel_for_action("app.game_config","<primary>g");
        set_accel_for_action("app.preferences","<primary>p");
        set_accel_for_action("app.update","<primary>u");
        #else
        add_accelerator("<primary>a","app.about");
        add_accelerator("<primary>q","app.quit");
        add_accelerator("<primary>g","app.game_config");
        add_accelerator("<primary>p","app.preferences");
        #endif // GTK_MINOR_VERSION

        RefPtr<Gio::Menu> menu = Gio::Menu::create();
        menu->append(_("Preferences"),"app.preferences");
        menu->append(_("Game configuration"),"app.game_config");
        menu->append(_("About"),"app.about");
        menu->append(_("Check for update"),"app.update");
        menu->append(_("Quit"),"app.quit");
        set_app_menu(RefPtr<Gio::MenuModel>::cast_static(menu));
    }

    Rand rand;
    if (rand.get_int_range(0,5) == 0)
        checkForUpdate(true);
}

void CsuApplication::on_open(const type_vec_files& files, const ustring& hint)
{
    RefPtr<File> file = files[0];
    if (file->query_exists())
    {
        try
        {
            ustring filename = filename_to_utf8(file->get_path());
            Game* tmp_game = new Game(file);
            setGame(tmp_game);
            setFilename(filename);
        }
        catch(Glib::Exception& e)
        {
            cerr << e.what() << endl;
            MessageDialog* error = new MessageDialog(*mainWindow(),e.what(),false,MESSAGE_ERROR,BUTTONS_OK,true);
            error->run();
            error->hide();
            delete error;
        }
    }
    activate();
}

void CsuApplication::onQuit()
{
    quit();
    about_->hide();
    new_game_config_dialog_->hide();
}

void CsuApplication::checkForUpdate(const bool auto_check)
{
    // Check the version
    RefPtr<File> file = File::create_for_uri("http://www.dalan.rd-h.fr/binaries/Csuper/latest_version.txt");
    char* data;
    gsize length;
    try
    {
        file->load_contents(data,length);
        Version version(data);
        g_free(data);

        if (auto_check && version <= pref()->version().lastCheckVersion())
            return;

        ustring msg;
        if (version > Version())
        {
            msg = ustring::compose(_("A update is available: you use the version %1 of Csuper whereas the version %2 is available.\n"
                                     "You can download the new version on this website: http://www.dalan.rd-h.fr/wordpress/"),
                                   Version().toUstring(),version.toUstring());
        }
        else
        {
            msg = ustring::compose(_("You use the version %1 of Csuper which is the latest version."),
                                   Version().toUstring());
        }

        MessageDialog* dial = new MessageDialog(*(mainWindow()),msg,false,MESSAGE_INFO,BUTTONS_OK,true);
        dial->run();
        dial->hide();
        delete dial;

        pref()->version().setLastCheckVersion(version);
        pref()->writeToFile();
    }
    catch (Glib::Exception& e)
    {
        cerr << e.what() << endl;
        if (!auto_check)
        {
            ustring msg = _("Cannot access to the latest version file on the internet");
            MessageDialog* error = new MessageDialog(*(mainWindow()),msg,false,MESSAGE_ERROR,BUTTONS_OK,true);
            error->run();
            error->hide();
            delete error;
        }
    }
}

void CsuApplication::updateGame(csuper::Game* game)
{
    if (game == nullptr)
        undoRedoManager().add(game_);
    else
    {
        if (game_ != nullptr)
            delete game_;
        game_ = game;
    }

    if (game_->exceedMaxNumber())
    {
        gameOverDialog()->launch();
    }

    // Update points
    // update ranking
}


//
// Setter and getter
//
void CsuApplication::setGame(csuper::Game* game)
 {
    if (game_ != nullptr)
        delete game_;
    else
    {
        menuFile()->setSensitive();
        menuDisplay()->setSensitive();
    }

    game_ = game;

    undoRedoManager().clear();
    undoRedoManager().add(game);
    // Update points
    // update ranking
    // fill calculator names
 }

void CsuApplication::setFilename(ustring& filename)
{
    filename_ = filename;
    mainWindow()->setFilename();

    pref()->directory().setOpen(path_get_dirname(filename));
    pref()->writeToFile();
}
