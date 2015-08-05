/*!
 * \file    import_export_game_configuration_dialog.cpp
 * \author  Remi BERTHO
 * \date    05/08/15
 * \version 4.3.0
 */

/*
 * import_export_game_configuration_dialog.cpp
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

#include "import_export_game_configuration_dialog.h"

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
ImportExportGameConfigurationDialog::ImportExportGameConfigurationDialog() :  CsuWidget(),
    Dialog("",*(app()->gameConfigurationWindow()),true)
{
    add_button(_("Cancel"),RESPONSE_CANCEL);
    add_button(_("Validate"),RESPONSE_OK);

    scrolled_window_ = manage(new ScrolledWindow());
    scrolled_window_->set_hexpand(true);
    scrolled_window_->set_vexpand(true);
    scrolled_window_->set_min_content_height(300);
    scrolled_window_->set_min_content_width(450);
    get_content_area()->pack_start(*scrolled_window_,true,true);

    viewport_ = manage(new Viewport(Adjustment::create(0,0,0),Adjustment::create(0,0,0)));
    viewport_->set_hexpand(true);
    viewport_->set_vexpand(true);
    scrolled_window_->add(*viewport_);
}



ImportExportGameConfigurationDialog::~ImportExportGameConfigurationDialog()
{
    if (main_grid_)
        delete main_grid_;
}


//
// Launch
//
vector<unsigned int> ImportExportGameConfigurationDialog::launch(const ListGameConfiguration& list_game_config, bool import)
{
    vector<unsigned int> id;
    unsigned int i;
    vector<CheckButton*>::iterator it;

    if (import)
        set_title(_("Import game configuration"));
    else
        set_title(_("Export game configuration"));


    if (main_grid_)
        delete main_grid_;
    check_buttons_.clear();

    // Set the grid
    main_grid_ = new Grid();
    main_grid_->set_row_spacing(10);
    main_grid_->set_column_spacing(10);
    #if GTK_MINOR_VERSION >= 12
    main_grid_->set_margin_end(10);
    main_grid_->set_margin_start(10);
    #else
    main_grid_->set_margin_right(10);
    main_grid_->set_margin_left(10);
    #endif // GTK_MINOR_VERSION
    main_grid_->set_margin_top(10);
    main_grid_->set_margin_bottom(10);


    // Set the contain of the grid
    Label* tmp_label;
    CheckButton* tmp_check_button;
    Button* tmp_button;
    for (i=0 ; i < list_game_config.size() ; i++)
    {
        tmp_label = manage(new Label(list_game_config[i].name()));
        tmp_label->set_halign(ALIGN_CENTER);
        tmp_label->set_hexpand(true);
        main_grid_->attach(*tmp_label,0,i,1,1);

        tmp_check_button = manage(new CheckButton());
        tmp_check_button->set_halign(ALIGN_CENTER);
        check_buttons_.push_back(tmp_check_button);
        main_grid_->attach(*tmp_check_button,1,i,1,1);
    }
    tmp_button = manage(new Button(_("Select all")));
    tmp_button->set_halign(ALIGN_CENTER);
    tmp_button->set_valign(ALIGN_CENTER);
    tmp_button->signal_clicked().connect(mem_fun(*this,&ImportExportGameConfigurationDialog::selectAll));
    main_grid_->attach(*tmp_button,1,i,1,1);

    tmp_button = manage(new Button(_("Deselect all")));
    tmp_button->set_halign(ALIGN_CENTER);
    tmp_button->set_valign(ALIGN_CENTER);
    tmp_button->signal_clicked().connect(mem_fun(*this,&ImportExportGameConfigurationDialog::deselectAll));
    main_grid_->attach(*tmp_button,2,i,1,1);

    viewport_->add(*main_grid_);


    show_all();
    switch(run())
    {
    case RESPONSE_OK:
        for (it = check_buttons_.begin() , i=0; it != check_buttons_.end() ; it++ , i++)
        {
            if ((*it)->get_active())
                id.push_back(i);
        }
        break;
    case RESPONSE_CANCEL:
        break;
    default:
        break;
    }

    hide();

    return id;
}


//
// Select function
//
void ImportExportGameConfigurationDialog::selectAll()
{
    vector<CheckButton*>::iterator it;
    for (it = check_buttons_.begin() ; it != check_buttons_.end() ; it++)
        (*it)->set_active(true);
}

void ImportExportGameConfigurationDialog::deselectAll()
{
    vector<CheckButton*>::iterator it;
    for (it = check_buttons_.begin() ; it != check_buttons_.end() ; it++)
        (*it)->set_active(false);
}
