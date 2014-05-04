/*!
 * \file    main_menu.c
 * \brief   Main menu
 * \author  Remi BERTHO
 * \date    03/05/14
 * \version 3.0.0
 */

 /*
 * main_menu.c
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

 #include "main_menu.h"

/*!
 * \fn G_MODULE_EXPORT void openAbout(GtkWidget *widget, gpointer data)
 *  Open the window about
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void openAbout(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    GtkWidget *window_about = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"about_window"));
    if (!window_about)
        g_critical(_("Widget about_windows is missing in file csuper-gui.glade."));

    gtk_dialog_run (GTK_DIALOG (window_about));
    gtk_widget_hide (window_about);
}

/*!
 * \fn G_MODULE_EXPORT void chooseCsuFileOpen(GtkWidget *widget, gpointer data)
 *  Choose and open a csu file.
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void chooseCsuFileOpen(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    char home_path[SIZE_MAX_FILE_NAME];

    /* Create the file chooser dialog*/
    GtkWidget *window_file_open = gtk_file_chooser_dialog_new (_("Open csu File"),GTK_WINDOW(user_data->main_window),
                GTK_FILE_CHOOSER_ACTION_OPEN,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-open",GTK_RESPONSE_ACCEPT,NULL);

     /*Add a .csu filter*/
    GtkFileFilter *csu_filter= GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefiltercsu"));
    GtkFileFilter *all_filter = GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefilterall"));
    gtk_file_filter_set_name(csu_filter,_("csu files"));
    gtk_file_filter_set_name(all_filter,_("All"));
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_open),csu_filter);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_open),all_filter);

    /* Give the home path to the current folder*/
    readHomePath(home_path);
    gtk_file_chooser_set_current_folder_file(GTK_FILE_CHOOSER(window_file_open),g_file_new_for_path(home_path),NULL);

	switch (gtk_dialog_run (GTK_DIALOG (window_file_open)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
			strcpy(user_data->csu_filename,gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (window_file_open)));
			if (user_data->ptr_csu_struct != NULL)
                closeCsuStruct(user_data->ptr_csu_struct);

            user_data->ptr_csu_struct=NULL;
            (user_data->ptr_csu_struct) = readCsuFile(user_data->csu_filename);
            if((user_data->ptr_csu_struct) == NULL)
                openFileError(user_data);
			break;
		}
		default:
			break;
	}
	gtk_widget_destroy(window_file_open);
}

/*!
 * \fn void openFileError(globalData *data)
 *  Display a dialog box which said that there is a problem when loading the file.
 * \param[in] data the globalData
 */
void openFileError(globalData *data)
{
    GtkWidget *window_error = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"file_not_open"));
    if (!window_error)
        g_critical(_("Widget about_windows is missing in file csuper-gui.glade."));

    gtk_dialog_run (GTK_DIALOG (window_error));
    gtk_widget_hide (window_error);
}
