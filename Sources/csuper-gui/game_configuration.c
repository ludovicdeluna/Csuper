/*!
 * \file    game_configuration.c
 * \brief   Game configuration
 * \author  Remi BERTHO
 * \date    03/05/14
 * \version 4.0.0
 */

 /*
 * game_configuration.c
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

 #include "game_configuration.h"

/*!
 * \fn G_MODULE_EXPORT void openGameConfigurationPreferences(GtkWidget *widget, gpointer data)
 *  Open the game configuration preferences
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void openGameConfigurationPreferences(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    GtkWidget *window_game = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"game_configuration_preferences"));
    if (!window_game)
        g_critical(_("Widget game_configuration_preferences is missing in file csuper-gui.glade."));

    displayGameConfiguration(user_data);

    gtk_widget_show_all(window_game);
}

/*!
 * \fn G_MODULE_EXPORT void closeGameConfigurationPreferences(GtkWidget *widget, gpointer data)
 *  Close the game configuration preferences
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void closeGameConfigurationPreferences(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    GtkWidget *window_game = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"game_configuration_preferences"));
    if (!window_game)
        g_critical(_("Widget game_configuration_preferences is missing in file csuper-gui.glade."));

    deleteDisplayGameConfiguration(user_data);

    gtk_widget_hide(window_game);
}

/*!
 * \fn G_MODULE_EXPORT gboolean closeGameConfigurationPreferencesQuit(GtkWidget *widget, GdkEvent  *event, gpointer user_data)
 *  Close the game configuration preferences
 * \param[in] widget the widget which send the interrupt
 * \param[in] event the event which triggered this signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT gboolean closeGameConfigurationPreferencesQuit(GtkWidget *widget, GdkEvent  *event, gpointer user_data)
{
    closeGameConfigurationPreferences(widget,user_data);
    return TRUE;
}

/*!
 * \fn G_MODULE_EXPORT void chooseExportedFile(GtkWidget *widget, gpointer data)
 *  Exporte the games configurations
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void chooseExportedFile(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    char home_path[SIZE_MAX_FILE_NAME];
    int error=FALSE;

    /* Create the file chooser dialog*/
    GtkWidget *window_file_export = gtk_file_chooser_dialog_new (_("Export game configuration"),GTK_WINDOW(user_data->ptr_main_window),
                GTK_FILE_CHOOSER_ACTION_SAVE,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-save",GTK_RESPONSE_ACCEPT,NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(window_file_export), TRUE);

    /* Give the home path to the current folder */
    readHomePathSlash(home_path);
    gtk_file_chooser_set_current_folder_file(GTK_FILE_CHOOSER(window_file_export),g_file_new_for_path(home_path),NULL);

	switch (gtk_dialog_run (GTK_DIALOG (window_file_export)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
		    char *filename;

			#ifdef _WIN32
		    filename=g_convert(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_export)),-1,"ISO-8859-1","UTF-8",NULL,NULL,NULL);
		    #else
		    filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_export));
		    #endif

            #ifdef PORTABLE
            strcpy(home_path,"");
            #endif // PORTABLE
            if(exportConfigFile(home_path,filename) == MY_FALSE)
                error=TRUE;
            g_free(filename);
			break;
		}
		default:
			break;
	}
	gtk_widget_destroy(window_file_export);
	if (error)
        exportGameConfigurationError(user_data);
}

/*!
 * \fn void exportGameConfigurationError(globalData *data)
 *  Display a dialog box which said that there is a problem when export the games configurations.
 * \param[in] data the globalData
 */
void exportGameConfigurationError(globalData *data)
{
    GtkWidget *window_error = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"game_configuration_not_exported"));
    if (!window_error)
        g_critical(_("Widget game_configuration_not_exported is missing in file csuper-gui.glade."));

    gtk_dialog_run (GTK_DIALOG (window_error));
    gtk_widget_hide (window_error);
}

/*!
 * \fn G_MODULE_EXPORT void chooseImportedFile(GtkWidget *widget, gpointer data)
 *  Exporte the games configurations
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void chooseImportedFile(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    char home_path[SIZE_MAX_FILE_NAME];
    int error=FALSE;

    /* Create the file chooser dialog*/
    GtkWidget *window_file_import = gtk_file_chooser_dialog_new (_("Import game configuration"),GTK_WINDOW(user_data->ptr_main_window),
                GTK_FILE_CHOOSER_ACTION_OPEN,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-save",GTK_RESPONSE_ACCEPT,NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(window_file_import), TRUE);

    /* Give the home path to the current folder */
    readHomePathSlash(home_path);
    gtk_file_chooser_set_current_folder_file(GTK_FILE_CHOOSER(window_file_import),g_file_new_for_path(home_path),NULL);

	switch (gtk_dialog_run (GTK_DIALOG (window_file_import)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
		    char *filename;

			#ifdef _WIN32
		    filename=g_convert(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_import)),-1,"ISO-8859-1","UTF-8",NULL,NULL,NULL);
		    #else
		    filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_import));
		    #endif

            #ifdef PORTABLE
            strcpy(home_path,"");
            #endif // PORTABLE
            if(importConfigFile(home_path,filename) == MY_FALSE)
                error=TRUE;
            g_free(filename);
			break;
		}
		default:
			break;
	}
	gtk_widget_destroy(window_file_import);
	if (error)
        importGameConfigurationError(user_data);

    updateDisplayGameConfiguration(user_data);
}

/*!
 * \fn void importGameConfigurationError(globalData *data)
 *  Display a dialog box which said that there is a problem when export the games configurations.
 * \param[in] data the globalData
 */
void importGameConfigurationError(globalData *data)
{
    GtkWidget *window_error = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"game_configuration_not_imported"));
    if (!window_error)
        g_critical(_("Widget game_configuration_not_imported is missing in file csuper-gui.glade."));

    gtk_dialog_run (GTK_DIALOG (window_error));
    gtk_widget_hide (window_error);
}

/*!
 * \fn void displayGameConfiguration(globalData *data)
 *  Display a all the game configuration on the window
 * \param[in] data the globalData
 */
void displayGameConfiguration(globalData *data)
{
    gint i;

    /* Get the windows scrolled*/
    GtkWidget *window_scrolled = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"scrolled_window_game_configuration_preferences"));
    if (!window_scrolled)
        g_critical(_("Widget scrolled_window_game_configuration_preferences is missing in file csuper-gui.glade."));

    /*Read the game configurations*/
    list_game_config *ptr_list_config;
    char home_path[SIZE_MAX_FILE_NAME]="";
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);

    /* Set the grid*/
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid),10);
    gtk_grid_set_row_spacing(GTK_GRID(grid),10);
    gtk_widget_set_margin_right(grid,10);
    gtk_widget_set_margin_left(grid,10);
    gtk_widget_set_margin_top(grid,10);
    gtk_widget_set_margin_bottom(grid,10);

    /* Fill the grid */
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
    {
        gtk_grid_attach(GTK_GRID(grid),gtk_label_new(ptr_list_config->name_game_config[i]),0,i,1,1);
        gtk_widget_set_hexpand(gtk_grid_get_child_at(GTK_GRID(grid),0,i),TRUE);
        //gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,i)),TRUE);
        #ifdef _WIN32
        gtk_grid_attach(GTK_GRID(grid),gtk_button_new_from_stock("gtk-edit"),1,i,1,1);
        gtk_grid_attach(GTK_GRID(grid),gtk_button_new_from_stock("gtk-properties"),2,i,1,1);
        gtk_grid_attach(GTK_GRID(grid),gtk_button_new_from_stock("gtk-delete"),3,i,1,1);
        #else
        gtk_grid_attach(GTK_GRID(grid),gtk_button_new_from_icon_name("gtk-edit",GTK_ICON_SIZE_BUTTON),1,i,1,1);
        gtk_grid_attach(GTK_GRID(grid),gtk_button_new_from_icon_name("gtk-properties",GTK_ICON_SIZE_BUTTON),2,i,1,1);
        gtk_grid_attach(GTK_GRID(grid),gtk_button_new_from_icon_name("gtk-delete",GTK_ICON_SIZE_BUTTON),3,i,1,1);
        gtk_button_set_label(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),1,i)),_("Edit"));
        gtk_button_set_label(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),2,i)),_("Properties"));
        gtk_button_set_label(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),3,i)),_("Delete"));
        #endif // _WIN32
        g_signal_connect (gtk_grid_get_child_at(GTK_GRID(grid),3,i),"clicked", G_CALLBACK(deleteGameConfiguration),data);
        g_signal_connect (gtk_grid_get_child_at(GTK_GRID(grid),2,i),"clicked", G_CALLBACK(viewGameConfiguration),data);
        g_signal_connect (gtk_grid_get_child_at(GTK_GRID(grid),1,i),"clicked", G_CALLBACK(editGameConfiguration),data);

        gtk_widget_set_tooltip_markup(gtk_grid_get_child_at(GTK_GRID(grid),2,i),_("View the details of the game configuration"));
        gtk_widget_set_tooltip_markup(gtk_grid_get_child_at(GTK_GRID(grid),3,i),_("Delete the game configuration"));
    }

    /* Add the different containers */
    GtkWidget *viewport = gtk_viewport_new(gtk_adjustment_new(0,0,0,0,0,0),gtk_adjustment_new(0,0,0,0,0,0));
    gtk_container_add(GTK_CONTAINER(viewport),grid);
    gtk_container_add(GTK_CONTAINER(window_scrolled),viewport);

    gtk_widget_show_all(window_scrolled);

    closeListGameConfig(ptr_list_config);
}

/*!
 * \fn void deleteDisplayGameConfiguration(GtkWidget *window_game)
 *  Delete the display a all the game configuration on the window
 * \param[in] data the globalData
 */
void deleteDisplayGameConfiguration(globalData *data)
{
    GtkWidget *window_scrolled = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"scrolled_window_game_configuration_preferences"));
    if (!window_scrolled)
        g_critical(_("Widget scrolled_window_game_configuration_preferences is missing in file csuper-gui.glade."));

    gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(window_scrolled)));
}

/*!
 * \fn void deleteDisplayGameConfiguration(GtkWidget *window_game)
 *  Update the display a all the game configuration on the window
 * \param[in] data the globalData
 */
void updateDisplayGameConfiguration(globalData *data)
{
    deleteDisplayGameConfiguration(data);
    displayGameConfiguration(data);
}

/*!
 * \fn G_MODULE_EXPORT void deleteGameConfiguration(GtkWidget *widget, gpointer data)
 *  Delete a game configuration
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void deleteGameConfiguration(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gint i=0;

    /* Get the button clicked*/
    GtkWidget *window_scrolled = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"scrolled_window_game_configuration_preferences"));
    if (!window_scrolled)
        g_critical(_("Widget scrolled_window_game_configuration_preferences is missing in file csuper-gui.glade."));
    GtkGrid *grid = GTK_GRID(gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(window_scrolled)))));
    while (1)
    {
        if (gtk_grid_get_child_at(GTK_GRID(grid),3,i) == widget)
            break;
        i++;
    }

    /* Manage the game configurations */
    list_game_config *ptr_list_config;
    char home_path[SIZE_MAX_FILE_NAME]="";
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);
    removeConfigListFile(i,ptr_list_config,home_path);
    closeListGameConfig(ptr_list_config);

    updateDisplayCurrentGameConfiguration(user_data,i,TRUE);
    updateDisplayGameConfiguration(user_data);
}

/*!
 * \fn G_MODULE_EXPORT void editGameConfiguration(GtkWidget *widget, gpointer data)
 *  Edit a game configuration
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void editGameConfiguration(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gint i=0;
    game_config config;
    game_config *ptr_config;
    list_game_config *ptr_list_config;
    char home_path[SIZE_MAX_FILE_NAME]="";

    /* Get the button clicked*/
    GtkWidget *window_scrolled = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"scrolled_window_game_configuration_preferences"));
    if (!window_scrolled)
        g_critical(_("Widget scrolled_window_game_configuration_preferences is missing in file csuper-gui.glade."));
    GtkGrid *grid = GTK_GRID(gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(window_scrolled)))));
    while (1)
    {
        if (gtk_grid_get_child_at(GTK_GRID(grid),1,i) == widget)
            break;
        i++;
    }

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);
    readConfigFile(i,ptr_list_config,&config,home_path);

    GtkWidget *preferences = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"game_configuration_preferences"));
    if (!preferences)
        g_critical(_("Widget game_configuration_preferences is missing in file csuper-gui.glade."));

    changeNewGameConfigurationDialog(user_data,config);
    ptr_config = newGameConfiguration(user_data,GTK_WINDOW(preferences));
    if(ptr_config != NULL)
    {
        removeConfigListFile(i,ptr_list_config,home_path);
        newConfigFile(*ptr_config,home_path);
        free(ptr_config);
        updateDisplayGameConfiguration(user_data);
        updateDisplayCurrentGameConfiguration(user_data,i,TRUE);
    }

    closeListGameConfig(ptr_list_config);
}

/*!
 * \fn G_MODULE_EXPORT viewGameConfiguration(GtkWidget *widget, gpointer data)
 *  Display the game configuration
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void viewGameConfiguration(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gint i=0;

    /* Get the button clicked*/
    GtkWidget *window_scrolled = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"scrolled_window_game_configuration_preferences"));
    if (!window_scrolled)
        g_critical(_("Widget scrolled_window_game_configuration_preferences is missing in file csuper-gui.glade."));
    GtkGrid *grid = GTK_GRID(gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(window_scrolled)))));
    while (1)
    {
        if (gtk_grid_get_child_at(GTK_GRID(grid),2,i) == widget)
            break;
        i++;
    }

    updateDisplayCurrentGameConfiguration(user_data,i,FALSE);
}

/*!
 * \fn void updateDisplayCurrentGameConfiguration(globalData *data , gint index, gboolean clear)
 *  Update the current game configuration label
 * \param[in] data the globalData
 * \param[in] index the index of the game configuration, -1 if you want to clear the label
 * \param[in] clear if TRUE the label is reset if the index is the same than the last call to the function otherwise the label is update
 */
void updateDisplayCurrentGameConfiguration(globalData *data , gint index, gboolean clear)
{
    globalData *user_data = (globalData*) data;
    static gint last_index=-1;char *yes=_("yes");
    char *no=_("no");

    if (last_index == index && clear)
        index = -1;

    if (!clear)
        last_index = index;
    else
    {
        if (index < last_index)
            last_index--;
    }

    /* Get the labels */
    GtkWidget *label_details = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"game_configuration_preferences_label_details"));
    if (!label_details)
        g_critical(_("Widget game_configuration_preferences_label_details is missing in file csuper-gui.glade."));
    GtkWidget *label_name = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"game_configuration_preferences_label_name"));
    if (!label_name)
        g_critical(_("Widget game_configuration_preferences_label_name is missing in file csuper-gui.glade."));

    if (index >= 0 && !clear)
    {
        /* Manage the game configurations */
        game_config config;
        list_game_config *ptr_list_config;
        char home_path[SIZE_MAX_FILE_NAME]="";
        #ifndef PORTABLE
        readHomePathSlash(home_path);
        #endif // PORTABLE
        ptr_list_config = readConfigListFile(home_path);
        readConfigFile(index,ptr_list_config,&config,home_path);

        /* Print the game config */
        #ifdef _WIN32
        if (config.nb_max != INFINITY)
        {
            gtk_label_set_text(GTK_LABEL(label_details),g_strdup_printf(_("Use a maximum score : %s\nNumber of points maximum/minimum : %.3f\n"
                "Initial score : %.3f\nNumber of decimal place : %d\nThe first has the highest score : %s\n"
                "Game in turn by turn : %s\nUse a distributor : %s"),integerToYesNo(config.max,yes,no),config.nb_max
                ,config.begin_score,config.decimal_place,integerToYesNo(config.first_way,yes,no),
                integerToYesNo(config.turn_by_turn,yes,no),integerToYesNo(config.use_distributor,yes,no)));
        }
        else
        {
            gtk_label_set_text(GTK_LABEL(label_details),g_strdup_printf(_("Use a maximum score : %s\nNumber of points maximum/minimum : inf\n"
                "Initial score : %.3f\nNumber of decimal place : %d\nThe first has the highest score : %s\n"
                "Game in turn by turn : %s\nUse a distributor : %s"),integerToYesNo(config.max,yes,no)
                ,config.begin_score,config.decimal_place,integerToYesNo(config.first_way,yes,no),
                integerToYesNo(config.turn_by_turn,yes,no),integerToYesNo(config.use_distributor,yes,no)));
        }
        #else
        gtk_label_set_text(GTK_LABEL(label_details),g_strdup_printf(_("Use a maximum score : %s\nNumber of points maximum/minimum : %.3f\n"
            "Initial score : %.3f\nNumber of decimal place : %d\nThe first has the highest score : %s\n"
            "Game in turn by turn : %s\nUse a distributor : %s"),integerToYesNo(config.max,yes,no),config.nb_max
            ,config.begin_score,config.decimal_place,integerToYesNo(config.first_way,yes,no),
            integerToYesNo(config.turn_by_turn,yes,no),integerToYesNo(config.use_distributor,yes,no)));
        #endif // _win32
        gtk_label_set_text(GTK_LABEL(label_name),g_strdup_printf(_("%s"),config.name));

        closeListGameConfig(ptr_list_config);
    }
    else
    {
        if (index < 0)
        {
            gtk_label_set_text(GTK_LABEL(label_details),g_strdup_printf(_("You have no game configuration selected.")));
            gtk_label_set_text(GTK_LABEL(label_name),"");
        }
    }

    gtk_widget_show(label_details);
}

/*!
 * \fn G_MODULE_EXPORT addGameConfiguration(GtkWidget *widget, gpointer data)
 *  Add a game configuration
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void addGameConfiguration(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    game_config *ptr_config = NULL;
    char home_path[SIZE_MAX_FILE_NAME]="";
    game_config config = {0,1,1,0,-1,-1,"",0};

    GtkWidget *preferences = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"game_configuration_preferences"));
    if (!preferences)
        g_critical(_("Widget game_configuration_preferences is missing in file csuper-gui.glade."));

    changeNewGameConfigurationDialog(user_data,config);
    ptr_config=newGameConfiguration(user_data,GTK_WINDOW(preferences));
    if (ptr_config == NULL)
        return;

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE

    newConfigFile(*ptr_config,home_path);

    free(ptr_config);

    updateDisplayGameConfiguration(user_data);
}


/*!
 * \fn game_config *newGameConfiguration(globalData *data, GtkWindow *parent_window)
 *  Display the window of creating a game configuration and return the game configuration created
 * \param[in] data the globalData
 * \param[in] parent_window the parent window
 */
game_config *newGameConfiguration(globalData *data, GtkWindow *parent_window)
{
    game_config config;
    game_config *ptr_config = NULL;
    gchar *buffer;

    /* Get the dialog box */
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"new_game_configuration_dialog"));
    if (!dialog)
        g_critical(_("Widget new_game_configuration_dialog is missing in file csuper-gui.glade."));

    gtk_window_set_transient_for(GTK_WINDOW(dialog),parent_window);

    /* Get the grid */
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"new_game_configuration_dialog_grid"));
    if (!grid)
        g_critical(_("Widget new_game_configuration_dialog_grid is missing in file csuper-gui.glade."));

    /* Define the size max of the game configuration name */
    gtk_entry_set_max_length(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,0)),SIZE_MAX_NAME);

    checkGoodNewGameConfiguration(NULL,data);

    gtk_widget_show_all(dialog);

    switch (gtk_dialog_run(GTK_DIALOG(dialog)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
		    /* Name */
		    strcpy(config.name,gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,0))));
		    if (strcmp(config.name,"") == 0)
                break;

		    /* Max / min */
		    buffer = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(gtk_grid_get_child_at(GTK_GRID(grid),1,1)));
		    if (buffer == NULL)
                break;
            else
            {
                if (strcmp(buffer,_("Maximum")) == 0)
                    config.max = 1;
                if (strcmp(buffer,_("Minimum")) == 0)
                    config.max = 0;
                if (strcmp(buffer,_("Neither")) == 0)
                {
                    config.max = 1;
                    config.nb_max = INFINITY;
                }
                else
                {
                    config.nb_max = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),1,2)));
                }
                g_free(buffer);
            }

            /* Initial score */
            config.begin_score = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),1,3)));

            /* First way */
            if (gtk_switch_get_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,4))))
                config.first_way = 1;
            else
                config.first_way = -1;

            /* Turn by turn */
            if (gtk_switch_get_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,5))))
                config.turn_by_turn = 1;
            else
                config.turn_by_turn = 0;

            /* Distributor */
            if (gtk_switch_get_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,6))))
                config.use_distributor = 1;
            else
                config.use_distributor = 0;

            /* Decimal place*/
		    buffer = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(gtk_grid_get_child_at(GTK_GRID(grid),1,7)));
		    if (buffer == NULL)
                break;
            else
            {
                if (strcmp(buffer,_("0")) == 0)
                    config.decimal_place = 0;
                if (strcmp(buffer,_("1")) == 0)
                    config.decimal_place = 1;
                if (strcmp(buffer,_("2")) == 0)
                    config.decimal_place = 2;
                if (strcmp(buffer,_("3")) == 0)
                    config.decimal_place = 3;

                g_free(buffer);
            }

            ptr_config = myAlloc(sizeof(game_config));
            *ptr_config = config;

			break;
		}
		case GTK_RESPONSE_CANCEL:
        {
            return ptr_config;
            break;
        }
		default:
		    return ptr_config;
			break;
	}

	return ptr_config;
}

/*!
 * \fn G_MODULE_EXPORT checkGoodNewGameConfiguration(GtkWidget *widget, gpointer data)
 *  Check if the game configuration is complete
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void checkGoodNewGameConfiguration(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gchar name[SIZE_MAX_NAME];
    gint index,index_2;

    /* Get the grid */
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"new_game_configuration_dialog_grid"));
    if (!grid)
        g_critical(_("Widget new_game_configuration_dialog_grid is missing in file csuper-gui.glade."));

    /* Get the button */
    GtkWidget *validat_button = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"button_ok_new_game_configuration"));
    if (!validat_button)
        g_critical(_("Widget button_ok_new_game_configuration is missing in file csuper-gui.glade."));

    strcpy(name,gtk_entry_get_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,0))));
    if (strcmp(name,"") == 0)
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,0)),0,TRUE,65535,0,0,FALSE,0,0,0);
    else
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,0)),0,FALSE,65535,0,0,FALSE,0,0,0);

    index = gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,1)));
    if (index < 0)
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,1)),0,TRUE,65535,0,0,FALSE,0,0,0);
    else
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,1)),0,FALSE,65535,0,0,FALSE,0,0,0);

    index_2 = gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,7)));
    if (index_2 < 0)
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,7)),0,TRUE,65535,0,0,FALSE,0,0,0);
    else
        setGtkLabelAttributes(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(grid),0,7)),0,FALSE,65535,0,0,FALSE,0,0,0);

    if (strcmp(name,"") == 0 || index < 0 || index_2 < 0)
        gtk_widget_set_sensitive(validat_button,FALSE);
    else
        gtk_widget_set_sensitive(validat_button,TRUE);

}

/*!
 * \fn G_MODULE_EXPORT noMaxMinNewGameConfiguration(GtkWidget *widget, gpointer data)
 *  Change text editable propriety of the max/min value
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void noMaxMinNewGameConfiguration(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gchar *buffer;

    GtkWidget *max = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"new_game_configuration_spin_nb_max"));
    if (!max)
        g_critical(_("Widget new_game_configuration_spin_nb_max is missing in file csuper-gui.glade."));

    buffer = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));
    if (buffer == NULL)
        return;

    if (strcmp(buffer,_("Neither")) == 0)
        gtk_editable_set_editable(GTK_EDITABLE(max),FALSE);
    else
        gtk_editable_set_editable(GTK_EDITABLE(max),TRUE);

    g_free(buffer);
}

/*!
 * \fn void changeNewGameConfigurationDialog(globalData *data,game_config config)
 *  Enter the game configuration into the new game configuration dialog
 * \param[in] data the globalData
 * \param[in] config a game config
 */
void changeNewGameConfigurationDialog(globalData *data,game_config config)
{
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"new_game_configuration_dialog_grid"));
    if (!grid)
        g_critical(_("Widget new_game_configuration_dialog_grid is missing in file csuper-gui.glade."));

    gtk_entry_set_text(GTK_ENTRY(gtk_grid_get_child_at(GTK_GRID(grid),1,0)),config.name);

    if (config.max == 0)
        gtk_combo_box_set_active_id(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,1)),"min");
    else
    {
        if (config.max == 1)
        {
            if (config.nb_max == INFINITY)
                gtk_combo_box_set_active_id(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,1)),"neither");
            else
                gtk_combo_box_set_active_id(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,1)),"max");
        }
        else
            gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,1)),-1);
    }


    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),1,2)),config.nb_max);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),1,3)),config.begin_score);

    if(config.first_way == 1)
        gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,4)),TRUE);
    else
        gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,4)),FALSE);

    if(config.turn_by_turn == 1)
        gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,5)),TRUE);
    else
        gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,5)),FALSE);

    if(config.use_distributor == 1)
        gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,6)),TRUE);
    else
        gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,6)),FALSE);

    switch(config.decimal_place)
    {
    case 0:
        gtk_combo_box_set_active_id(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,7)),"0");
        break;
    case 1:
        gtk_combo_box_set_active_id(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,7)),"1");
        break;
    case 2:
        gtk_combo_box_set_active_id(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,7)),"2");
        break;
    case 3:
        gtk_combo_box_set_active_id(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,7)),"3");
        break;
    default:
        gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,7)),-1);
        break;
    }
}

