/*!
 * \file    main_menu.c
 * \brief   Main menu
 * \author  Remi BERTHO
 * \date    04/05/14
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
 * \fn G_MODULE_EXPORT void displayAbout(GtkWidget *widget, gpointer data)
 *  Display the about window
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void displayAbout(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    GError *error = NULL;
    GdkPixbuf *logo;
    GtkWidget *window_about = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"about_window"));
    if (!window_about)
        g_critical(_("Widget about_windows is missing in file csuper-gui.glade."));

    logo=gdk_pixbuf_new_from_file("Images/Logo_200.png",&error);
    if (error)
    {
        g_printerr("%s\n", error->message);
        g_error_free (error);
    }else
        gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(window_about),logo);

    gtk_dialog_run (GTK_DIALOG (window_about));
    gtk_widget_hide (window_about);
    if (!error)
        g_object_unref(logo);
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
    gboolean error=FALSE;

    /* Create the file chooser dialog*/
    GtkWidget *window_file_open = gtk_file_chooser_dialog_new (_("Open csu file"),GTK_WINDOW(user_data->ptr_main_window),
                GTK_FILE_CHOOSER_ACTION_OPEN,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-open",GTK_RESPONSE_ACCEPT,NULL);

     /*Add a .csu and a all filter*/
    GtkFileFilter *csu_filter= GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefiltercsu"));
    GtkFileFilter *all_filter = GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefilterall"));
    gtk_file_filter_set_name(csu_filter,_("csu files"));
    gtk_file_filter_set_name(all_filter,_("All"));
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_open),csu_filter);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_open),all_filter);

    /* Give the home path to the current folder or the last filename if there is one*/

    if (strcmp(user_data->csu_filename,"") == 0)
    {
        #ifdef PORTABLE
        char home_path[SIZE_MAX_FILE_NAME];
        readHomePath(home_path);
        gtk_file_chooser_set_current_folder_file(GTK_FILE_CHOOSER(window_file_open),g_file_new_for_path(home_path),NULL);
        #else
        gchar system_path[SIZE_MAX_FILE_NAME]="";
        readSystemPath(system_path);
        #ifndef _WIN32
        gtk_file_chooser_set_current_folder_file(GTK_FILE_CHOOSER(window_file_open),g_file_new_for_path(system_path),NULL);
        #else
        gtk_file_chooser_set_current_folder_file(GTK_FILE_CHOOSER(window_file_open),g_file_new_for_path(g_convert(system_path,-1,"UTF-8","ISO-8859-1",NULL,NULL,NULL)),NULL);
        #endif // _WIN32
        #endif
    }
    else
    {
        #ifdef _WIN32
        gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(window_file_open),g_convert(user_data->csu_filename,-1,"UTF-8","ISO-8859-1",NULL,NULL,NULL));
        #else
        gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(window_file_open),user_data->csu_filename);
        #endif
    }

	switch (gtk_dialog_run (GTK_DIALOG (window_file_open)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
		    gchar *filename;
		    #ifdef _WIN32
		    filename=g_convert(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_open)),-1,"ISO-8859-1","UTF-8",NULL,NULL,NULL);
		    #else
		    filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(window_file_open));
		    #endif

		    #ifndef PORTABLE
		    gchar folder[SIZE_MAX_FILE_NAME];
		    strcpy(folder,filename);
		    if (getFolderFromFilename(folder) == MY_TRUE)
                changeSystemPath(folder);
		    #endif // PORTABLE

			if (user_data->ptr_csu_struct != NULL)
                closeCsuStruct(user_data->ptr_csu_struct);

            user_data->ptr_csu_struct=NULL;
            (user_data->ptr_csu_struct) = readCsuFile(filename);
            if((user_data->ptr_csu_struct) == NULL)
                error=TRUE;
            else
            {
                strcpy(user_data->csu_filename,filename);
                updateMainWindow(user_data);
            }
            g_free(filename);
			break;
		}
		default:
			break;
	}
	gtk_widget_destroy(window_file_open);
	if (error)
        openFileError(user_data);
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

/*!
 * \fn G_MODULE_EXPORT void chooseCsuFileSave(GtkWidget *widget, gpointer data)
 *  Choose and save a csu file.
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void chooseCsuFileSave(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    int error=FALSE;

    if(user_data->ptr_csu_struct == NULL)
    {
        noCsuFileOpened(user_data);
        return;
    }

    /* Create the file chooser dialog*/
    GtkWidget *window_file_save = gtk_file_chooser_dialog_new (_("Save csu file"),GTK_WINDOW(user_data->ptr_main_window),
                GTK_FILE_CHOOSER_ACTION_SAVE,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-save",GTK_RESPONSE_ACCEPT,NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(window_file_save), TRUE);

     /*Add filters*/
    GtkFileFilter *csu_filter= GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefiltercsu"));
    GtkFileFilter *all_filter = GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefilterall"));
    gtk_file_filter_set_name(csu_filter,_("csu files"));
    gtk_file_filter_set_name(all_filter,_("All"));
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_save),csu_filter);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_save),all_filter);

    /* Give filename to the old filename*/
    #ifdef _WIN32
    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(window_file_save),g_convert(user_data->csu_filename,-1,"UTF-8","ISO-8859-1",NULL,NULL,NULL));
    #else
    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(window_file_save),user_data->csu_filename);
    #endif

	switch (gtk_dialog_run (GTK_DIALOG (window_file_save)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
		    char *filename;
			#ifdef _WIN32
		    filename=g_convert(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_save)),-1,"ISO-8859-1","UTF-8",NULL,NULL,NULL);
		    #else
		    filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_save));
		    #endif

            /* Add the csu extension if the filter is csu */
			if(gtk_file_chooser_get_filter(GTK_FILE_CHOOSER(window_file_save))==csu_filter)
                addFileCsuExtension(filename);

            if (writeCsuFile(filename,user_data->ptr_csu_struct) == MY_FALSE)
                error=TRUE;
            else
                strcpy(user_data->csu_filename,filename);

            g_free(filename);
			break;
		}
		default:
			break;
	}
	gtk_widget_destroy(window_file_save);
	if (error)
        saveFileError(user_data);
}

/*!
 * \fn void saveFileError(globalData *data)
 *  Display a dialog box which said that there is a problem when loading the file.
 * \param[in] data the globalData
 */
void saveFileError(globalData *data)
{
    GtkWidget *window_error = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"file_not_save"));
    if (!window_error)
        g_critical(_("Widget file_not_save is missing in file csuper-gui.glade."));

    gtk_dialog_run (GTK_DIALOG (window_error));
    gtk_widget_hide (window_error);
}

/*!
 * \fn void noCsuFileOpened(globalData *data)
 *  Display a dialog box which said that there is a problem when loading the file.
 * \param[in] data the globalData
 */
void noCsuFileOpened(globalData *data)
{
    GtkWidget *window_error = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"no_csu_file_opened"));
    if (!window_error)
        g_critical(_("Widget no_csu_file_opened is missing in file csuper-gui.glade."));

    gtk_dialog_run (GTK_DIALOG (window_error));
    gtk_widget_hide (window_error);
}

/*!
 * \fn G_MODULE_EXPORT void copyToClipboard(GtkWidget *widget, gpointer data)
 *  Copy the selected text to clipboard
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void copyToClipboard(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gtk_clipboard_set_text(user_data->ptr_clipboard,gtk_clipboard_wait_for_text(user_data->ptr_clipboard_selected),-1);
}

/*!
 * \fn void updateCsuInfo(globalData *data)
 *  Update the csu informations in the right panel.
 * \param[in] data the globalData
 */
void updateCsuInfo(globalData *data)
{
    char *yes=_("yes");
    char *no=_("no");

    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_date"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Created the : %02.0f/%02.0f/%4.0f"),data->ptr_csu_struct->day,data->ptr_csu_struct->month,data->ptr_csu_struct->year));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_version"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("File's version : %1.1f"),data->ptr_csu_struct->version));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_size_max_name"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Size max of the names : %.0f"),data->ptr_csu_struct->size_max_name));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_number_player"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of players : %.0f"),data->ptr_csu_struct->nb_player));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Numbers maximum of turns : %d"),maxNbTurn(data->ptr_csu_struct)-1));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_config_name"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Name of the game configuration : %s"),data->ptr_csu_struct->config.name));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_use_max"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Use a maximum score : %s"),integerToYesNo(data->ptr_csu_struct->config.max,yes,no)));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_initial_score"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Initial score : %.3f"),data->ptr_csu_struct->config.begin_score));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_digit"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of decimal place : %d"),data->ptr_csu_struct->config.decimal_place));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_first_way"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("The first has the highest score : %s"),integerToYesNo(data->ptr_csu_struct->config.first_way,yes,no)));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Game in turn by turn : %s"),integerToYesNo(data->ptr_csu_struct->config.turn_by_turn,yes,no)));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_distributor_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Use a distributor : %s"),integerToYesNo(data->ptr_csu_struct->config.use_distributor,yes,no)));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_max"));
    #ifdef __unix__
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of points maximum/minimum : %.3f"),data->ptr_csu_struct->config.nb_max));
    #elif _WIN32
    if (data->ptr_csu_struct->config.nb_max == INFINITY)
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of points maximum/minimum : inf")));
    else
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of points maximum/minimum : %.3f"),data->ptr_csu_struct->config.nb_max));
    #endif

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_distributor"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Distributor : %s"),data->ptr_csu_struct->player_names[(int)data->ptr_csu_struct->distributor]));
}

/*!
 * \fn void propertiesFileError(globalData *data)
 *  Display a dialog box which said that there is a problem when loading the file.
 * \param[in] data the globalData
 */
void propertiesFileError(globalData *data)
{
    GtkWidget *window_error = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"no_csu_file_opened_properties"));
    if (!window_error)
        g_critical(_("Widget no_csu_file_opened_properties is missing in file csuper-gui.glade."));

    gtk_dialog_run (GTK_DIALOG (window_error));
    gtk_widget_hide (window_error);
}

/*!
 * \fn G_MODULE_EXPORT void showPropertiesDialogBox(GtkWidget *widget, gpointer data)
 *  Show the properties window
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void showPropertiesDialogBox(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    if (user_data->ptr_csu_struct == NULL)
    {
        propertiesFileError(user_data);
        return;
    }

    /* Get the dialog box */
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"csu_file_properties_dialog_box"));
    if (!dialog)
        g_critical(_("Widget csu_file_properties_dialog_box is missing in file csuper-gui.glade."));

    updateCsuInfo(user_data);

    gtk_widget_show_all(dialog);

    gtk_dialog_run(GTK_DIALOG(dialog));
}

