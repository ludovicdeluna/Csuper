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
    gtk_window_resize(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),700,400);
    g_signal_connect(user_data->ptr_new_csu_file_assistant,"delete-event", G_CALLBACK(deleteAssistantNewCsu),user_data);
    g_signal_connect(user_data->ptr_new_csu_file_assistant,"cancel", G_CALLBACK(deleteAssistantNewCsu),user_data);
    g_signal_connect(user_data->ptr_new_csu_file_assistant,"prepare", G_CALLBACK(preparePageAssistantNewCsu),user_data);
    gtk_window_set_title(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),_("New csu file assistant"));

    /* Set the first page */
    GtkWidget *grid_1 = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!grid_1)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));
    gtk_file_chooser_set_current_folder_file(GTK_FILE_CHOOSER(gtk_grid_get_child_at(GTK_GRID(grid_1),1,1)),g_file_new_for_path(home_path),NULL);
    gtk_entry_set_max_length(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid_1),1,0)),SIZE_MAX_NAME);
    gtk_assistant_append_page(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_1);
    gtk_assistant_set_page_type(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_1,GTK_ASSISTANT_PAGE_INTRO);
    gtk_assistant_set_page_title(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_1,_("General informations"));
    GtkWidget *combo_config = gtk_combo_box_text_new();
    ptr_list_config = readConfigListFile(home_path);
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
        gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(combo_config),i,NULL,ptr_list_config->name_game_config[i]);
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(combo_config),ptr_list_config->nb_config,NULL,_("Add a new game configuration"));
    gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(combo_config),ptr_list_config->nb_config +1,NULL,_("Use an other game configuration"));
    gtk_grid_attach(GTK_GRID(grid_1),combo_config,1,3,1,1);
    g_signal_connect(combo_config,"changed", G_CALLBACK(chooseGameConfigurationNewAssistant),user_data);
    closeListGameConfig(ptr_list_config);

    /* Set the second page */
    GtkWidget *scrolled_window_name = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"scrolled_window_new_csu_file_assistant_2"));
    if (!scrolled_window_name)
        g_critical(_("Widget scrolled_window_new_csu_file_assistant_2 is missing in file csuper-gui.glade."));
    GtkWidget *grid_name = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(gtk_bin_get_child(GTK_BIN(scrolled_window_name))),grid_name);

    gtk_grid_set_column_spacing(GTK_GRID(grid_name),10);
    gtk_grid_set_row_spacing(GTK_GRID(grid_name),10);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_name),TRUE);
    gtk_widget_set_margin_right(grid_name,10);
    gtk_widget_set_margin_left(grid_name,10);
    gtk_widget_set_margin_top(grid_name,10);
    gtk_widget_set_margin_bottom(grid_name,10);

    gtk_assistant_append_page(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),scrolled_window_name);
    gtk_assistant_set_page_type(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),scrolled_window_name,GTK_ASSISTANT_PAGE_CONTENT);
    gtk_assistant_set_page_title(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),scrolled_window_name,_("Player names"));

    /* Set the third page */
    GtkWidget *grid_3 = gtk_grid_new();
    gtk_assistant_append_page(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_3);
    gtk_assistant_set_page_type(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_3,GTK_ASSISTANT_PAGE_CONFIRM);
    gtk_assistant_set_page_title(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_3,_("Distributor and validation"));

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

    GtkWidget *page_1 = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!page_1)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));
    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(page_1),1,3));

    GtkWidget *page_2 = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"scrolled_window_new_csu_file_assistant_2"));
    if (!page_2)
        g_critical(_("Widget scrolled_window_new_csu_file_assistant_2 is missing in file csuper-gui.glade."));
    gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(page_2)))));

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
 * \fn G_MODULE_EXPORT void validAssistantNewCsuOneNumber(GtkWidget *widget, gpointer data)
 *  Valid name of the first page of the assistant for a new csu file
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void validAssistantNewCsuOneNumber(GtkWidget *widget, gpointer data)
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
    gchar name[SIZE_MAX_NAME];
    gint index;

    GtkWidget *grid_1 = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!grid_1)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));

    strcpy(name,gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid_1),1,0))));
    index = gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid_1),1,3)));

    if (strcmp(name,"") != 0 && index >=0)
    {
        gtk_assistant_set_page_complete(GTK_ASSISTANT(data->ptr_new_csu_file_assistant),grid_1,TRUE);
        if (data->ptr_csu_struct_tmp != NULL)
            closeCsuStruct(data->ptr_csu_struct_tmp);
        data->ptr_csu_struct_tmp = newCsuStruct(gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid_1),1,2))),data->config);
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

/*!
 * \fn G_MODULE_EXPORT void preparePageAssistantNewCsu(GtkAssistant *assistant,GtkWidget *widget, gpointer data)
 *  Prepare the new pages
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void preparePageAssistantNewCsu(GtkAssistant *assistant,GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gint page = gtk_assistant_get_current_page(assistant);
    gint nb_ligne=0;
    gint i;

    if (page == 1)
    {
        /* Calculate the number of line which already exist */
        GtkGrid *grid = GTK_GRID(gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(widget)))));
        while(gtk_grid_get_child_at(grid,0,nb_ligne) != 0)
            nb_ligne++;

        /* Add the missing lines */
        for (i=nb_ligne ; i<user_data->ptr_csu_struct_tmp->nb_player ; i++)
        {
            gtk_grid_attach(grid,gtk_label_new(g_strdup_printf(_("Name of the %dth player"),i+1)),0,i,1,1);
            gtk_grid_attach(grid,gtk_entry_new(),1,i,1,1);
            gtk_entry_set_max_length(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,i)),SIZE_MAX_NAME);
            gtk_entry_set_alignment(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,i)),0.5);
            g_signal_connect(gtk_grid_get_child_at(GTK_GRID(grid),1,i),"changed", G_CALLBACK(validAssistantNewCsuTwo),user_data);
        }

        /* Remove the lines */
        for (i = nb_ligne ; i > user_data->ptr_csu_struct_tmp->nb_player ; i--)
        {
            gtk_widget_destroy(gtk_grid_get_child_at(grid,0,i-1));
            gtk_widget_destroy(gtk_grid_get_child_at(grid,1,i-1));
            #ifndef  _WIN32
            //gtk_grid_remove_row(grid,i-1);
            #endif // _WIN32
        }
        validAssistantNewCsuTwo(NULL,user_data);
        gtk_widget_show_all(GTK_WIDGET(grid));
    }

    if (page == 2)
    {
        /*
        recharche si bouton mis en place, si non le cre, si oui met a jour le nom des joueurs et le cureseur si changement du nombre de personnes
        */
    }
}

/*!
 * \fn G_MODULE_EXPORT void validAssistantNewCsuTwo(GtkWidget *widget, gpointer data)
 *  Valid name of the second page of the assistant for a new csu file
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void validAssistantNewCsuTwo(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gboolean valid = TRUE;
    gint i;

    GtkWidget *scrolled_window = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"scrolled_window_new_csu_file_assistant_2"));
    if (!scrolled_window)
        g_critical(_("Widget scrolled_window_new_csu_file_assistant_2 is missing in file csuper-gui.glade."));
    GtkGrid *grid = GTK_GRID(gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(scrolled_window)))));

    for (i=0 ; i<user_data->ptr_csu_struct_tmp->nb_player ; i++)
    {
        strcpy(user_data->ptr_csu_struct_tmp->player_names[i],gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(grid,1,i))));
        if (strcmp(user_data->ptr_csu_struct_tmp->player_names[i],"") == 0)
        {
            valid = FALSE;
            break;
        }
    }

    if (valid)
        gtk_assistant_set_page_complete(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),GTK_WIDGET(scrolled_window),TRUE);
    else
        gtk_assistant_set_page_complete(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),GTK_WIDGET(scrolled_window),FALSE);
}
