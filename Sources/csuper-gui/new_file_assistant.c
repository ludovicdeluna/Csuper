/*!
 * \file    new_file_assistant.c
 * \brief   The new file assistant function
 * \author  Remi BERTHO
 * \date    04/05/14
 * \version 4.0.0
 */

 /*
 * new_file_assistant.c
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
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

 #include "new_file_assistant.h"

 /*!
 * \fn G_MODULE_EXPORT void openAssistantNewCsu(GtkWidget *widget, gpointer data)
 *  Open the assistant for a new csu file
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void openAssistantNewCsu(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    char home_path[SIZE_MAX_FILE_NAME]="";
    list_game_config *ptr_list_config;
    gint i;

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE

    /* creating of the assistant */
    user_data->ptr_new_csu_file_assistant = gtk_assistant_new();
    gtk_window_set_transient_for(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),GTK_WINDOW(user_data->ptr_main_window));
    gtk_window_set_gravity(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),GDK_GRAVITY_CENTER);
    gtk_window_set_position(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_modal(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),TRUE);
    gtk_window_set_hide_titlebar_when_maximized(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),TRUE);
    gtk_window_set_type_hint(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),GDK_WINDOW_TYPE_HINT_DIALOG);
    g_signal_connect(user_data->ptr_new_csu_file_assistant,"delete-event", G_CALLBACK(deleteAssistantNewCsu),user_data);
    g_signal_connect(user_data->ptr_new_csu_file_assistant,"cancel", G_CALLBACK(deleteAssistantNewCsu),user_data);
    gtk_window_set_title(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),_("New csu file assistant"));

    /* Set the first page */
    GtkWidget *grid_1 = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!grid_1)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));
    gtk_entry_set_max_length(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid_1),1,0)),SIZE_MAX_NAME);
    gtk_assistant_append_page(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_1);
    gtk_assistant_set_page_type(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_1,GTK_ASSISTANT_PAGE_INTRO);
    GtkWidget *combo_config = gtk_combo_box_text_new();
    ptr_list_config = readConfigListFile(home_path);
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
        gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(combo_config),i,NULL,ptr_list_config->name_game_config[i]);
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(combo_config),ptr_list_config->nb_config,NULL,_("Add a new game configuration"));
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(combo_config),ptr_list_config->nb_config +1,NULL,_("Use an other game configuration"));
    gtk_grid_attach(GTK_GRID(grid_1),combo_config,1,2,1,1);
    g_signal_connect(combo_config,"changed", G_CALLBACK(chooseGameConfigurationNewAssistant),user_data);
    closeListGameConfig(ptr_list_config);

    /* Set the second page */
    GtkWidget *grid_2 = gtk_grid_new();
    gtk_assistant_append_page(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_2);
    gtk_assistant_set_page_type(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_2,GTK_ASSISTANT_PAGE_CONTENT);

    /* Set the third page */
    GtkWidget *grid_3 = gtk_grid_new();
    gtk_assistant_append_page(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_3);
    gtk_assistant_set_page_type(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_3,GTK_ASSISTANT_PAGE_CONFIRM);

    gtk_widget_show_all(user_data->ptr_new_csu_file_assistant);
}

/*!
 * \fn G_MODULE_EXPORT void openAssistantNewCsu(GtkWidget *widget, gpointer data)
 *  Open the assistant for a new csu file
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void deleteAssistantNewCsu(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    gtk_widget_destroy(widget);

    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!grid)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));
    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(grid),1,2));

    if (user_data->ptr_csu_struct_tmp != NULL)
    {
        closeCsuStruct(user_data->ptr_csu_struct_tmp);
        user_data->ptr_csu_struct_tmp = NULL;
    }
}

/*!
 * \fn G_MODULE_EXPORT void validAssistantNewCsuOneName(GtkWidget *widget, gpointer data)
 *  Valid name of the first page of the assistant for a new csu file
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void validAssistantNewCsuOneName(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    validAssistantNewCsuOne(user_data);
}

/*!
 * \fn void validAssistantNewCsuOne(globalData *data)
 *  Valid the first page of the assistant for a new csu file
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
void validAssistantNewCsuOne(globalData *data)
{
    gchar name[SIZE_MAX_FILE_NAME];
    gint index;

    GtkWidget *entry = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"grid_new_csu_file_assistant_1_entry_name"));
    if (!entry)
        g_critical(_("Widget grid_new_csu_file_assistant_1_entry_name is missing in file csuper-gui.glade."));

    GtkWidget *grid_1 = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!grid_1)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));

    strcpy(name,gtk_entry_get_text(GTK_ENTRY(entry)));
    index = gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid_1),1,2)));

    if (strcmp(name,"") != 0 && index >=0)
    {
        gtk_assistant_set_page_complete(GTK_ASSISTANT(data->ptr_new_csu_file_assistant),grid_1,TRUE);
        if (data->ptr_csu_struct_tmp != NULL)
            closeCsuStruct(data->ptr_csu_struct_tmp);
        data->ptr_csu_struct_tmp = newCsuStruct(gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid_1),1,1))),data->config);
    }
    else
        gtk_assistant_set_page_complete(GTK_ASSISTANT(data->ptr_new_csu_file_assistant),grid_1,FALSE);
}

/*!
 * \fn G_MODULE_EXPORT void chooseGameConfigurationNewAssistant(GtkWidget *widget, gpointer data)
 *  Load the game configuration
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void chooseGameConfigurationNewAssistant(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gint index;
    game_config *ptr_config = NULL;
    game_config config = {0,1,1,0,-1,-1,"",0};

    char home_path[SIZE_MAX_FILE_NAME]="";
    list_game_config *ptr_list_config;
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);

    index = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));

    if (index < 0)
    {
        closeListGameConfig(ptr_list_config);
        return;
    }

    if (index < ptr_list_config->nb_config)
        readConfigFile(index,ptr_list_config,&(user_data->config),home_path);
    else
    {
        changeNewGameConfigurationDialog(user_data,config);
        ptr_config=newGameConfiguration(user_data,GTK_WINDOW(user_data->ptr_new_csu_file_assistant));
        if (ptr_config == NULL)
        {
            gtk_combo_box_set_active(GTK_COMBO_BOX(widget),-1);
            validAssistantNewCsuOne(data);
            return;
        }
        if (index == ptr_list_config->nb_config)
            newConfigFile(*ptr_config,home_path);
        user_data->config = *ptr_config;
        free(ptr_config);
    }

    validAssistantNewCsuOne(data);
    closeListGameConfig(ptr_list_config);
}
