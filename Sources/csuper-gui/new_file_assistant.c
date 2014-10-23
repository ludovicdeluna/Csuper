/*!
 * \file    new_file_assistant.c
 * \brief   The new file assistant function
 * \author  Remi BERTHO
 * \date    26/06/14
 * \version 4.0.1
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
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void openAssistantNewCsu(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    char home_path[SIZE_MAX_FILE_NAME]="";
    gchar system_path[SIZE_MAX_FILE_NAME]="";
    list_game_config *ptr_list_config;
    gint i;

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    readSystemPath(system_path);
    #else
    readHomePath(system_path);
    #endif // PORTABLE

    /* creating of the assistant */
    user_data->ptr_new_csu_file_assistant = gtk_assistant_new();

    /* Set the assistant windows */
    gtk_window_set_transient_for(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),GTK_WINDOW(user_data->ptr_main_window));
    gtk_window_set_gravity(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),GDK_GRAVITY_CENTER);
    gtk_window_set_position(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_modal(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),TRUE);
    gtk_window_set_type_hint(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),GDK_WINDOW_TYPE_HINT_DIALOG);
    gtk_window_resize(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),700,400);
    gtk_window_set_title(GTK_WINDOW(user_data->ptr_new_csu_file_assistant),_("New csu file assistant"));

    /*Set the signal pf the assistant */
    g_signal_connect(user_data->ptr_new_csu_file_assistant,"delete-event", G_CALLBACK(deleteEventAssistantNewCsu),user_data);
    g_signal_connect(user_data->ptr_new_csu_file_assistant,"cancel", G_CALLBACK(deleteAssistantNewCsu),user_data);
    g_signal_connect(user_data->ptr_new_csu_file_assistant,"prepare", G_CALLBACK(preparePageAssistantNewCsu),user_data);
    g_signal_connect(user_data->ptr_new_csu_file_assistant,"close", G_CALLBACK(endAssistantNewCsu),user_data);


    /* Set the first page */
    GtkWidget *grid_1 = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!grid_1)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));
    gtk_assistant_append_page(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_1);
    gtk_assistant_set_page_type(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_1,GTK_ASSISTANT_PAGE_INTRO);
    gtk_assistant_set_page_title(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_1,_("General informations"));

    /* Configure the file chooser */
    gtk_entry_set_max_length(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid_1),1,0)),SIZE_MAX_FILE_NAME/8);
    #ifdef _WIN32
    gtk_file_chooser_set_current_folder_file(GTK_FILE_CHOOSER(gtk_grid_get_child_at(GTK_GRID(grid_1),1,1)),g_file_new_for_path(g_convert(system_path,-1,"UTF-8","ISO-8859-1",NULL,NULL,NULL)),NULL);
    #else
    gtk_file_chooser_set_current_folder_file(GTK_FILE_CHOOSER(gtk_grid_get_child_at(GTK_GRID(grid_1),1,1)),g_file_new_for_path(system_path),NULL);
    #endif

    /* Set the combo  box of the game configuration */
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
    gtk_assistant_append_page(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),scrolled_window_name);
    gtk_assistant_set_page_type(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),scrolled_window_name,GTK_ASSISTANT_PAGE_CONTENT);
    gtk_assistant_set_page_title(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),scrolled_window_name,_("Player's names"));

    /* Set the grid */
    GtkWidget *grid_name = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid_name),10);
    gtk_grid_set_row_spacing(GTK_GRID(grid_name),10);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_name),TRUE);
    #if GTK_MINOR_VERSION >= 12
    gtk_widget_set_margin_end(grid_name,10);
    gtk_widget_set_margin_start(grid_name,10);
    #else
    gtk_widget_set_margin_right(grid_name,10);
    gtk_widget_set_margin_left(grid_name,10);
    #endif // GTK_MINOR_VERSION
    gtk_widget_set_margin_top(grid_name,10);
    gtk_widget_set_margin_bottom(grid_name,10);
    gtk_container_add(GTK_CONTAINER(gtk_bin_get_child(GTK_BIN(scrolled_window_name))),grid_name);


    /* Set the third page */
    GtkWidget *grid_3 = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_3"));
    if (!grid_1)
        g_critical(_("Widget grid_new_csu_file_assistant_3 is missing in file csuper-gui.glade."));
    gtk_assistant_append_page(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_3);
    gtk_assistant_set_page_type(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_3,GTK_ASSISTANT_PAGE_CONFIRM);
    gtk_assistant_set_page_title(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_3,_("Distributor and validation"));

    GtkWidget *combo_distributor = gtk_combo_box_text_new();
    gtk_grid_attach(GTK_GRID(grid_3),combo_distributor,1,0,1,1);
    g_signal_connect(combo_distributor,"changed", G_CALLBACK(validAssistantNewCsuThree),user_data);

    cleanAssistantNewCsu(user_data);
    gtk_widget_show_all(user_data->ptr_new_csu_file_assistant);
}

/*!
 * \fn G_MODULE_EXPORT void deleteEventAssistantNewCsu(GtkWidget *widget,GdkEvent  *event, gpointer data)
 *  Open the assistant for a new csu file
 * \param[in] widget the widget which send the signal
 * \param[in] event the GdkEvent
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void deleteEventAssistantNewCsu(GtkWidget *widget,GdkEvent *event, gpointer data)
{
    deleteAssistantNewCsu(widget,data);
}

/*!
 * \fn G_MODULE_EXPORT void openAssistantNewCsu(GtkWidget *widget, gpointer data)
 *  Open the assistant for a new csu file
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void deleteAssistantNewCsu(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    /* Destroy the combo box for the game configuration */
    GtkWidget *page_1 = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!page_1)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));
    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(page_1),1,3));

    /* Destroy the grid of the page 2 */
    GtkWidget *page_2 = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"scrolled_window_new_csu_file_assistant_2"));
    if (!page_2)
        g_critical(_("Widget scrolled_window_new_csu_file_assistant_2 is missing in file csuper-gui.glade."));
    gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(page_2)))));

    /* Destroy the combo box for the distributor */
    GtkWidget *page_3 = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_3"));
    if (!page_3)
        g_critical(_("Widget grid_new_csu_file_assistant_3 is missing in file csuper-gui.glade."));
    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(page_3),1,0));

    /* Close the csu structure */
    if (user_data->ptr_csu_struct_tmp != NULL)
    {
        closeCsuStruct(user_data->ptr_csu_struct_tmp);
        user_data->ptr_csu_struct_tmp = NULL;
    }

    gtk_widget_destroy(user_data->ptr_new_csu_file_assistant);
}

/*!
 * \fn G_MODULE_EXPORT void validAssistantNewCsuOne(GtkWidget *widget, gpointer data)
 *  Valid the first page of the assistant for a new csu file
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void validAssistantNewCsuOne(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gchar name[SIZE_MAX_FILE_NAME];
    gint index;
    gchar *folder;
    bool folder_ok;
    bool filename_ok;

    GtkWidget *grid_1 = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!grid_1)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));

    /* Get the filename, the index of the game configuration and the folder */
    g_utf8_strncpy(name,gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid_1),1,0))),SIZE_MAX_FILE_NAME/8);
    index = gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid_1),1,3)));
    #ifdef _WIN32
    folder = g_convert(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gtk_grid_get_child_at(GTK_GRID(grid_1),1,1))),-1,"ISO-8859-1","UTF-8",NULL,NULL,NULL);
    #else
    folder = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gtk_grid_get_child_at(GTK_GRID(grid_1),1,1)));
    #endif // _WIN32
    #ifndef PORTABLE
    folder_ok = changeSystemPath(folder);
    #else
    folder_ok = checkPath(folder);
    #endif // PORTABLE
    filename_ok = checkFilename(name,folder);

    /* Test the filename */
    if (strcmp(name,"") == 0 || filename_ok == false)
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid_1),0,0)),0,TRUE,100,0,0,FALSE,0,0,0);
    else
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid_1),0,0)),0,FALSE,100,0,0,FALSE,0,0,0);

    /* Test if a game configuration is selected */
    if (index < 0 )
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid_1),0,3)),0,TRUE,100,0,0,FALSE,0,0,0);
    else
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid_1),0,3)),0,FALSE,100,0,0,FALSE,0,0,0);

    /* Test the folder */
    if (folder_ok == false)
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid_1),0,1)),0,TRUE,100,0,0,FALSE,0,0,0);
    else
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid_1),0,1)),0,FALSE,100,0,0,FALSE,0,0,0);

    /* Test if the page one is valid or not */
    if (strcmp(name,"") != 0 && index >=0 && folder_ok != false && filename_ok == true)
    {
        gtk_assistant_set_page_complete(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_1,TRUE);
        if (user_data->ptr_csu_struct_tmp != NULL)
            closeCsuStruct(user_data->ptr_csu_struct_tmp);
        user_data->ptr_csu_struct_tmp = newCsuStruct(gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid_1),1,2))),user_data->config);
    }
    else
        gtk_assistant_set_page_complete(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),grid_1,FALSE);

    g_free(folder);
}

/*!
 * \fn G_MODULE_EXPORT void chooseGameConfigurationNewAssistant(GtkWidget *widget, gpointer data)
 *  Load the game configuration
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void chooseGameConfigurationNewAssistant(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gint index;
    game_config *ptr_config = NULL;
    game_config config = {0,1,1,0,-1,-1,"",0};

    /* Read the game configuration list */
    char home_path[SIZE_MAX_FILE_NAME]="";
    list_game_config *ptr_list_config;
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);

    index = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));

    /* If the index if not valid return */
    if (index < 0)
    {
        closeListGameConfig(ptr_list_config);
        return;
    }

    /* if the index correspond to to a game configuration, read it */
    if (index < ptr_list_config->nb_config)
        readConfigFile(index,ptr_list_config,&(user_data->config),home_path);
    /* Otherwise ask a new game configuration */
    else
    {
        changeNewGameConfigurationDialog(user_data,config);
        ptr_config=newGameConfiguration(user_data,GTK_WINDOW(user_data->ptr_new_csu_file_assistant));
        if (ptr_config == NULL)
        {
            gtk_combo_box_set_active(GTK_COMBO_BOX(widget),-1);
            validAssistantNewCsuOne(NULL,data);
            return;
        }

        /* Save the game configuration if ask */
        if (index == ptr_list_config->nb_config)
            user_data->save_new_game_config = TRUE;
        else
            user_data->save_new_game_config = FALSE;

        user_data->config = *ptr_config;
        free(ptr_config);
    }

    validAssistantNewCsuOne(NULL,data);
    closeListGameConfig(ptr_list_config);
}

/*!
 * \fn G_MODULE_EXPORT void preparePageAssistantNewCsu(GtkAssistant *assistant,GtkWidget *widget, gpointer data)
 *  Prepare the new pages
 * \param[in] assistant the GtkAssistant
 * \param[in] widget the widget which send the signal
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
            gtk_entry_set_placeholder_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,i)),g_strdup_printf(_("Type here the name of the %dth player"),i+1));
            gtk_entry_set_alignment(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,i)),0.5);
            g_signal_connect(gtk_grid_get_child_at(GTK_GRID(grid),1,i),"changed", G_CALLBACK(validAssistantNewCsuTwo),user_data);
        }

        /* Remove the unwanted lines */
        for (i = nb_ligne ; i > user_data->ptr_csu_struct_tmp->nb_player ; i--)
        {
            gtk_widget_destroy(gtk_grid_get_child_at(grid,0,i-1));
            gtk_widget_destroy(gtk_grid_get_child_at(grid,1,i-1));
        }
        validAssistantNewCsuTwo(NULL,user_data);
        gtk_widget_show_all(GTK_WIDGET(grid));
    }

    if (page == 2)
    {
        GtkGrid *grid = GTK_GRID(widget);

        /* If there is no distributor valid the page 3 */
        if (user_data->ptr_csu_struct_tmp->config.use_distributor == 0)
        {
            gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(gtk_grid_get_child_at(grid,1,0)));
            gtk_assistant_set_page_complete(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),GTK_WIDGET(grid),TRUE);
        }
        /* Otherwise Create a combo box to choose the distributor */
        else
        {
            gint index = gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(grid,1,0)));
            gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(gtk_grid_get_child_at(grid,1,0)));
            for (i = 0 ; i<user_data->ptr_csu_struct_tmp->nb_player ; i++)
                gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(gtk_grid_get_child_at(grid,1,0)),i,NULL,user_data->ptr_csu_struct_tmp->player_names[i]);

            /* If the last distributor still exist, choose it */
            if (index <= user_data->ptr_csu_struct_tmp->nb_player)
                gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(grid,1,0)),index);

            validAssistantNewCsuThree(NULL,user_data);
        }
    }

    if (page == 0)
        validAssistantNewCsuOne(NULL,user_data);
}

/*!
 * \fn G_MODULE_EXPORT void validAssistantNewCsuTwo(GtkWidget *widget, gpointer data)
 *  Valid name of the second page of the assistant for a new csu file
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void validAssistantNewCsuTwo(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gboolean valid = TRUE;
    gint i;
    gint j;

    /* Get the grid */
    GtkWidget *scrolled_window = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"scrolled_window_new_csu_file_assistant_2"));
    if (!scrolled_window)
        g_critical(_("Widget scrolled_window_new_csu_file_assistant_2 is missing in file csuper-gui.glade."));
    GtkGrid *grid = GTK_GRID(gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(scrolled_window)))));

    /* Save all the name in the csu structure and check if there are non null */
    for (i=0 ; i<user_data->ptr_csu_struct_tmp->nb_player ; i++)
    {
        strncpy(user_data->ptr_csu_struct_tmp->player_names[i],gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(grid,1,i))),SIZE_MAX_NAME-1);
        if (strcmp(user_data->ptr_csu_struct_tmp->player_names[i],"") == 0)
        {
            valid = FALSE;
            setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,i)),0,TRUE,100,0,0,FALSE,0,0,0);
        }
        else
            setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,i)),0,FALSE,100,0,0,FALSE,0,0,0);
    }

    /* Check if all the name are different */
    for (i=0 ; i<user_data->ptr_csu_struct_tmp->nb_player ; i++)
    {
        for (j=i+1 ; j<user_data->ptr_csu_struct_tmp->nb_player ; j++)
        {
            if (strcmp(user_data->ptr_csu_struct_tmp->player_names[i],user_data->ptr_csu_struct_tmp->player_names[j]) == 0)
            {
                setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,i)),0,TRUE,100,0,0,FALSE,0,0,0);
                setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,j)),0,TRUE,100,0,0,FALSE,0,0,0);
            }
        }
    }

    /* Check if the page is valid */
    if (valid && differentsPlayerName(user_data->ptr_csu_struct_tmp) == true)
        gtk_assistant_set_page_complete(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),GTK_WIDGET(scrolled_window),TRUE);
    else
        gtk_assistant_set_page_complete(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),GTK_WIDGET(scrolled_window),FALSE);
}

/*!
 * \fn G_MODULE_EXPORT void validAssistantNewCsuThree(GtkWidget *widget, gpointer data)
 *  Valid the third page of the assistant for a new csu file
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void validAssistantNewCsuThree(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gint index;

    GtkWidget *grid= GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_3"));
    if (!grid)
        g_critical(_("Widget grid_new_csu_file_assistant_3 is missing in file csuper-gui.glade."));

    index = gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,0)));

    if (index >= 0)
    {
        user_data->ptr_csu_struct_tmp->distributor = index;
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,0)),0,FALSE,100,0,0,FALSE,0,0,0);
        gtk_assistant_set_page_complete(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),GTK_WIDGET(grid),TRUE);
    }
    else
    {
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,0)),0,TRUE,100,0,0,FALSE,0,0,0);
        gtk_assistant_set_page_complete(GTK_ASSISTANT(user_data->ptr_new_csu_file_assistant),GTK_WIDGET(grid),FALSE);
    }
}

/*!
 * \fn G_MODULE_EXPORT void endAssistantNewCsu(GtkWidget *widget, gpointer data)
 *  End the assistant for a new csu file
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void endAssistantNewCsu(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gchar name[SIZE_MAX_FILE_NAME];
    gchar *folder;

    /* Read the game configuration list */
    char home_path[SIZE_MAX_FILE_NAME]="";
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE


    /* Get the filename */
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!grid)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));

    #ifdef _WIN32
    folder = g_convert(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gtk_grid_get_child_at(GTK_GRID(grid),1,1))),-1,"ISO-8859-1","UTF-8",NULL,NULL,NULL);
    strncpy(name,g_convert(gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,0))),-1,"ISO-8859-1","UTF-8",NULL,NULL,NULL),SIZE_MAX_NAME-1);
    #else
    folder = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gtk_grid_get_child_at(GTK_GRID(grid),1,1)));
    g_utf8_strncpy(name,gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,0))),SIZE_MAX_FILE_NAME/8);
    #endif // _WIN32


    sprintf(user_data->csu_filename,"%s/%s",folder,name);
    addFileCsuExtension(user_data->csu_filename);

    /* Save the game configuration if ask */
    if (user_data->save_new_game_config)
        newConfigFile(user_data->config,home_path);

    /* Update the information of the global data */
    if (user_data->ptr_csu_struct != NULL)
        closeCsuStruct(user_data->ptr_csu_struct);
    user_data->ptr_csu_struct = user_data->ptr_csu_struct_tmp;
    user_data->ptr_csu_struct_tmp = NULL;

    updateMainWindow(user_data,!exceedMaxNumber(user_data->ptr_csu_struct));
    if (writeCsuFile(user_data->csu_filename,user_data->ptr_csu_struct) == false)
        saveFileError(user_data);
    deleteAllLastCsuStruct(user_data);
    addLastCsuStruct(user_data);

    deleteAssistantNewCsu(NULL,user_data);
    setButtonMainWindow(user_data);
    g_free(folder);
}

/*!
 * \fn cleanAssistantNewCsu(globalData *data)
 *  Clean all value of the assistant
 * \param[in] data the globalData
 */
void cleanAssistantNewCsu(globalData *data)
{
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"grid_new_csu_file_assistant_1"));
    if (!grid)
        g_critical(_("Widget grid_new_csu_file_assistant_1 is missing in file csuper-gui.glade."));

    gtk_entry_set_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,0)),"");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),1,2)),1);
}
