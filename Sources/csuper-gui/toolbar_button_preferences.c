/*!
 * \file    toolbar_button_preferences.c
 * \brief   The preferences of csuper
 * \author  Remi BERTHO
 * \date    10/01/15
 * \version 4.2.0
 */

 /*
 * toolbar_button_preferences.c
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-gui.
 *
 * Csuper-gui is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-gui is distributed in the hope that it will be useful,
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

 #include "toolbar_button_preferences.h"


/*!
 * \fn void updateToolbarButtonPreferencesSwitch(globalData *data)
 *  Update the switch of the toolbar button preferences
 * \param[in] data the globalData
 */
void updateToolbarButtonPreferencesSwitch(globalData *data)
{
    toolbar_button_preferences_struct toolbar;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFileToolbarButtonPreferences(home_path,&toolbar);

    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"grid_toolbar_button_preferences"));
    if (!grid)
        g_critical(_("Widget grid_toolbar_button_preferences is missing in file csuper-gui.glade."));

    gint i;

    for (i=0 ; i<= 22 ; i++)
        gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),(i/12)*2+1,i%12)),*(&toolbar.new+i));

    /*gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,0)),toolbar.new);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,1)),toolbar.open);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,2)),toolbar.save_as);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,3)),toolbar.separator_6);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,4)),toolbar.delete_file);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,5)),toolbar.print);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,6)),toolbar.separator_1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,7)),toolbar.undo);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,8)),toolbar.redo);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,9)),toolbar.separator_2);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,10)),toolbar.cut);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,0)),toolbar.copy);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,1)),toolbar.paste);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,2)),toolbar.delete);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,3)),toolbar.separator_3);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,4)),toolbar.properties);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,5)),toolbar.separator_4);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,6)),toolbar.preferences);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,7)),toolbar.game_configuration_preferences);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,8)),toolbar.toolbar_button_preferences);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,9)),toolbar.separator_5);
    gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,10)),toolbar.about);*/
}

/*!
 * \fn void readToolbarButtonPreferencesSwitch(globalData *data, toolbar_button_preferences_struct *toolbar)
 *  Read the toolbar_button_preferences_struct with the switch of the toolbar button preferences window
 * \param[in] data the globalData
 * \param[in] toolbar the toolbar button preferences
 */
void readToolbarButtonPreferencesSwitch(globalData *data, toolbar_button_preferences_struct *toolbar)
{
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"grid_toolbar_button_preferences"));
    if (!grid)
        g_critical(_("Widget grid_toolbar_button_preferences is missing in file csuper-gui.glade."));

    gint i;

    for (i=0 ; i<= 22 ; i++)
        *(&toolbar->new+i)=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),(i/12)*2+1,i%12)));

    /*toolbar->new=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,0)));
    toolbar->open=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,1)));
    toolbar->save_as=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,2)));
    toolbar->separator_6=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,3)));
    toolbar->delete_file=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,4)));
    toolbar->print=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,5)));
    toolbar->separator_1=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,6)));
    toolbar->undo=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,7)));
    toolbar->redo=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,8)));
    toolbar->separator_2=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,9)));
    toolbar->cut=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,10)));
    toolbar->copy=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,0)));
    toolbar->paste=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,1)));
    toolbar->delete=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,2)));
    toolbar->separator_3=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,3)));
    toolbar->properties=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,4)));
    toolbar->separator_4=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,5)));
    toolbar->preferences=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,6)));
    toolbar->game_configuration_preferences=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,7)));
    toolbar->toolbar_button_preferences=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,8)));
    toolbar->separator_5=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,9)));
    toolbar->about=gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,10)));*/
}

/*!
 * \fn G_MODULE_EXPORT void checkToolbarButtonPreferencesChanged(GtkWidget *widget,gpointer data)
 *  Check if the toolbar button preferences change relative to this save in the file
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void checkToolbarButtonPreferencesChanged(GtkWidget *widget,gpointer data)
{
    globalData *user_data = (globalData*) data;
    toolbar_button_preferences_struct toolbar_file;
    toolbar_button_preferences_struct toolbar_preferences;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFileToolbarButtonPreferences(home_path,&toolbar_file);
    readToolbarButtonPreferencesSwitch(user_data,&toolbar_preferences);

    GtkWidget *apply_button = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"apply_button_toolbar_preferences"));
    if (!apply_button)
        g_critical(_("Widget apply_button_toolbar_preferences is missing in file csuper-gui.glade."));

    gtk_widget_set_sensitive(apply_button,differentsToolbarButtonPreferencesStruct(toolbar_file,toolbar_preferences));
}


/*!
 * \fn G_MODULE_EXPORT void validToolbarButtonPreferences(GtkWidget *widget, gpointer data)
 *  Validate the new toolbar button preferences
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void validToolbarButtonPreferences(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    toolbar_button_preferences_struct toolbar;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readToolbarButtonPreferencesSwitch(user_data,&toolbar);

    createFileToolbarButtonPreferences(home_path,toolbar);
    updateToolbarButton(user_data);
    checkToolbarButtonPreferencesChanged(NULL,user_data);
}
