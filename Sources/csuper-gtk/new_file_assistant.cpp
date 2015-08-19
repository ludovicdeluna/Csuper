/*!
 * \file    new_file_assistant.cpp
 * \author  Remi BERTHO
 * \date    12/08/15
 * \version 4.3.0
 */

/*
 * new_file_assistant.cpp
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

#include "new_file_assistant.h"


#include <glibmm/i18n.h>
#include "csu_application.h"


using namespace Gtk;
using namespace Glib;
using namespace Gdk;
using namespace csuper;
using namespace std;


//
// Constructor, destructor
//
NewFileAssistant::NewFileAssistant(const RefPtr<Builder>& refGlade) :  CsuWidget(), Assistant()
{
    // Set the assistant window
    //set_transient_for(*(app()->mainWindow()));
    set_gravity(GRAVITY_CENTER);
    set_position(WIN_POS_CENTER_ON_PARENT);
    set_modal(true);
    set_type_hint(WINDOW_TYPE_HINT_DIALOG);
    resize(700,400);
    set_title(_("New csu file assistant"));


    // Set the signal
    signal_delete_event().connect(mem_fun(*this,&NewFileAssistant::deleteAssistant));
    signal_cancel().connect(mem_fun(*this,&NewFileAssistant::cancel));
    signal_prepare().connect(mem_fun(*this,&NewFileAssistant::preparePage));
    signal_close().connect(mem_fun(*this,&NewFileAssistant::validate));


    // Set the first page
    refGlade->get_widget_derived("new_csu_file_assistant_page_1_grid", page_1_);
    append_page(*page_1_);
    set_page_type(*page_1_,ASSISTANT_PAGE_INTRO);
    set_page_title(*page_1_,_("General information"));
    page_1_->name_entry_->signal_changed().connect(mem_fun(*this,&NewFileAssistant::validatePageOne));
    page_1_->nb_player_spinbutton_->signal_changed().connect(mem_fun(*this,&NewFileAssistant::validatePageOne));
    page_1_->folder_chooser_->signal_selection_changed().connect(mem_fun(*this,&NewFileAssistant::validatePageOne));


    // Set the second page
    page_2_ = new NewFileAssistantPage2();
    append_page(*page_2_);
    set_page_type(*page_2_,ASSISTANT_PAGE_CONTENT);
    set_page_title(*page_2_,_("Player's names"));


    // Set the third page
    page_3_ = new NewFileAssistantPage3();
    page_3_->distributor_combobox_->signal_changed().connect(mem_fun(*this,&NewFileAssistant::validatePageThree));
    append_page(*page_3_);
    set_page_type(*page_3_,ASSISTANT_PAGE_CONFIRM);
    set_page_title(*page_3_,_("Distributor and validation"));
}

NewFileAssistant::~NewFileAssistant()
{
    delete page_2_;
    delete page_3_;
}


//
// function
//
void NewFileAssistant::launch()
{
    unsigned int i;
    set_transient_for(*(app()->mainWindow()));


    // Set page 1
    page_1_->folder_chooser_->set_current_folder(locale_from_utf8(app()->pref()->directory().open()));

    if (page_1_->game_config_combobox_ != nullptr)
        delete page_1_->game_config_combobox_;
    page_1_->game_config_combobox_ = manage(new ComboBoxText());
    for (i = 0 ; i<app()->listGameConfig()->size() ; i++)
        page_1_->game_config_combobox_->append(intToUstring(i),app()->listGameConfig()->at(i).name());
    page_1_->game_config_combobox_->append(intToUstring(i),_("Add a new game configuration"));
    page_1_->game_config_combobox_->append(intToUstring(i+1),_("Use an other game configuration"));
    page_1_->attach(*(page_1_->game_config_combobox_),1,3,1,1);
    page_1_->game_config_combobox_->signal_changed().connect(mem_fun(*this,&NewFileAssistant::validatePageOne));
    page_1_->game_config_combobox_->signal_changed().connect(mem_fun(*this,&NewFileAssistant::chooseGameConfig));
    page_1_->name_entry_->set_text("");
    page_1_->nb_player_spinbutton_->set_value(1);


    // Set page 2

    show_all();
}


bool NewFileAssistant::deleteAssistant(GdkEventAny* event)
{
    cancel();
    return false;
}

void NewFileAssistant::cancel()
{
    delete page_1_->game_config_combobox_;
    page_1_->game_config_combobox_ = nullptr;
    page_2_->deleteLines();

    names_.clear();
    nb_player_ = 1;
    page_3_->distributor_combobox_->remove_all();

    hide();
}

void NewFileAssistant::validatePageOne()
{
    ustring index_game_config;
    bool folder_ok;
    bool filename_ok;

    filename_ok = checkFilename(page_1_->name_entry_->get_text());
    folder_ok = checkFolder(locale_to_utf8(page_1_->folder_chooser_->get_filename()));
    index_game_config = page_1_->game_config_combobox_->get_active_id();

    nb_player_ = page_1_->nb_player_spinbutton_->get_value_as_int();

    if (!filename_ok)
    {
        page_1_->name_label_->set_markup(ustring::compose("%1%2%3","<span foreground=\"red\">",
                                                          _("Name of the new CSU file"),
                                                          "</span>"));
    }
    else
        page_1_->name_label_->set_text(_("Name of the new CSU file"));


    if (!folder_ok)
    {
        page_1_->folder_label_->set_markup(ustring::compose("%1%2%3","<span foreground=\"red\">",
                                                          _("Folder where the new csu file will be saved"),
                                                          "</span>"));
    }
    else
        page_1_->folder_label_->set_text(_("Folder where the new csu file will be saved"));


    if (index_game_config == "")
    {
        page_1_->game_config_label_->set_markup(ustring::compose("%1%2%3","<span foreground=\"red\">",
                                                          _("Your game configuration"),
                                                          "</span>"));
    }
    else
        page_1_->game_config_label_->set_text(_("Your game configuration"));

    if (filename_ok && folder_ok && index_game_config != "")
        set_page_complete(*page_1_,true);
    else
        set_page_complete(*page_1_,false);
}

void NewFileAssistant::validatePageTwo()
{
    unsigned int i,j;
    bool valid = true;

    names_.clear();

    // Save all the name and check if there are non null
    for (i=0 ; i < nb_player_ ; i++)
    {
        names_.push_back(dynamic_cast<Entry*>(page_2_->grid_->get_child_at(1,i))->get_text());
        if (names_[i] == "")
        {
            valid = false;
            static_cast<Label*>(page_2_->grid_->get_child_at(0,i))->set_markup(
                    ustring::compose("<span foreground=\"red\">%1</span>",
                                     ustring::compose(_("Name of the %1th player"),i+1)));
        }
        else
            static_cast<Label*>(page_2_->grid_->get_child_at(0,i))->set_text(ustring::compose(_("Name of the %1th player"),i+1));
    }

    // Check if all the name are different
    auto it1 = names_.begin();
    for (i=0 ; it1 != names_.end() ; it1++, i++)
    {
        auto it2 = it1 + 1;
        for ( j=i+1 ; it2 != names_.end() ; it2++, j++)
        {
            if (*it1 == *it2)
            {
                static_cast<Label*>(page_2_->grid_->get_child_at(0,i))->set_markup(
                    ustring::compose("<span foreground=\"red\">%1</span>",
                                     ustring::compose(_("Name of the %1th player"),i+1)));
                static_cast<Label*>(page_2_->grid_->get_child_at(0,j))->set_markup(
                    ustring::compose("<span foreground=\"red\">%1</span>",
                                     ustring::compose(_("Name of the %1th player"),j+1)));
                valid = false;
            }
        }
    }


    if (valid)
        set_page_complete(*page_2_,true);
    else
        set_page_complete(*page_2_,false);
}

void NewFileAssistant::validatePageThree()
{
    ustring index = page_3_->distributor_combobox_->get_active_id();

    if (index == "")
    {
        set_page_complete(*page_3_,false);
        page_3_->distributor_label_->set_markup(ustring::compose("%1%2%3","<span foreground=\"red\">",
                                                                 _("Select the distributor"),
                                                                 "</span>"));
    }
    else
    {
        set_page_complete(*page_3_,true);
        page_3_->distributor_label_->set_text(_("Select the distributor"));
    }
}

void NewFileAssistant::chooseGameConfig()
{
    unsigned int index_game_config;
    ustring str_index = page_1_->game_config_combobox_->get_active_id();

    if (str_index == "")
        return;

    index_game_config = ustringToInt(str_index);


    if (index_game_config < app()->listGameConfig()->size())
    {
        save_game_config_ = false;
        game_config_ = app()->listGameConfig()->at(index_game_config);
    }
    else
    {
        GameConfiguration config;
        if (!(app()->newGameConfigurationDialog()->launch(config,*this)))
        {
            page_1_->game_config_combobox_->set_active(-1);
            return;
        }

        if (index_game_config == app()->listGameConfig()->size())
            save_game_config_ = true;
        else
            save_game_config_ = false;

        game_config_ = config;
    }
}


void NewFileAssistant::preparePage(Widget* page)
{
    if (page == page_1_)
        validatePageOne();
    else if (page == page_2_)
    {
        page_2_->createLines(nb_player_);
        validatePageTwo();
    } if (page == page_3_)
    {
        if (game_config_.useDistributor())
        {
            ustring name_active = page_3_->distributor_combobox_->get_active_id();
            page_3_->distributor_combobox_->remove_all();

            for (auto it = names_.begin() ; it != names_.end() ; it++)
                page_3_->distributor_combobox_->append(*it,*it);

            page_3_->distributor_combobox_->set_active_text(name_active);

            validatePageThree();
        }
        else
        {
            page_3_->distributor_combobox_->remove_all();
            set_page_complete(*page_3_,true);
        }
    }
}


void NewFileAssistant::validate()
{
    ustring filename = build_filename(locale_to_utf8(page_1_->folder_chooser_->get_filename()),page_1_->name_entry_->get_text());
    app()->setFilename(addFileExtension(filename,"csu"));

    if (save_game_config_)
    {
        app()->listGameConfig()->add(game_config_);
        app()->listGameConfig()->writeToFile();
    }

    Game* new_game = new Game(nb_player_,game_config_);

    unsigned int i = 0;
    auto it=names_.begin();
    for ( ; it != names_.end() ; it++, i++)
        new_game->setPlayerName(i,*it);

    new_game->setDistributor(page_3_->distributor_combobox_->get_active_id());

    try
    {
        new_game->writeToFile(filename);
    }
    catch (Glib::Exception& e)
    {
        cerr << e.what() << endl;
        MessageDialog* error = new MessageDialog(*this,e.what(),false,MESSAGE_ERROR,BUTTONS_OK,true);
        error->run();
        error->hide();
        delete error;
    }

    app()->setGame(new_game);

    hide();

    cancel();
}
