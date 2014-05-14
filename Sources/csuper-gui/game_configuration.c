/*!
 * \file    game_configuration.c
 * \brief   Game configuration
 * \author  Remi BERTHO
 * \date    03/05/14
 * \version 3.0.0
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
        g_critical(_("Widget about_windows is missing in file csuper-gui.glade."));

    gtk_widget_show(window_game);
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
        g_critical(_("Widget about_windows is missing in file csuper-gui.glade."));

    gtk_widget_hide(window_game);
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
			filename=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (window_file_export));
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
        g_critical(_("Widget about_windows is missing in file csuper-gui.glade."));

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
			filename=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (window_file_import));
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
        g_critical(_("Widget about_windows is missing in file csuper-gui.glade."));

    gtk_dialog_run (GTK_DIALOG (window_error));
    gtk_widget_hide (window_error);
}
