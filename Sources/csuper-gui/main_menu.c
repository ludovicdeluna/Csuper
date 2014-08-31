/*!
 * \file    main_menu.c
 * \brief   Main menu
 * \author  Remi BERTHO
 * \date    31/08/14
 * \version 4.2.0
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
 * \param[in] widget the widget which send the signal
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

    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(window_about),CSUPER_VERSION);

    gtk_dialog_run (GTK_DIALOG (window_about));
    gtk_widget_hide (window_about);
    if (!error)
        g_object_unref(logo);
}

/*!
 * \fn G_MODULE_EXPORT void chooseCsuFileOpen(GtkWidget *widget, gpointer data)
 *  Choose and open a csu file.
 * \param[in] widget the widget which send the signal
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
		    /* Get the filename*/
		    gchar *filename;
		    #ifdef _WIN32
		    filename=g_convert(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_open)),-1,"ISO-8859-1","UTF-8",NULL,NULL,NULL);
		    #else
		    filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(window_file_open));
		    #endif

			if (user_data->ptr_csu_struct != NULL)
                closeCsuStruct(user_data->ptr_csu_struct);

            user_data->ptr_csu_struct=NULL;
            (user_data->ptr_csu_struct) = readCsuFile(filename);
            if((user_data->ptr_csu_struct) == NULL)
                error=TRUE;
            else
            {
                /* Save the folder */
                #ifndef PORTABLE
                gchar folder[SIZE_MAX_FILE_NAME];
                strcpy(folder,filename);
                if (getFolderFromFilename(folder) == true)
                    changeSystemPath(folder);
                #endif // PORTABLE

                strcpy(user_data->csu_filename,filename);
                updateMainWindow(user_data,!exceedMaxNumber(user_data->ptr_csu_struct));
                deleteAllLastCsuStruct(user_data);
                addLastCsuStruct(user_data);
                setButtonMainWindowSensitive(user_data);
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
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void chooseCsuFileSave(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    int error=FALSE;

    if(user_data->ptr_csu_struct == NULL)
        return;

    /* Create the file chooser dialog*/
    GtkWidget *window_file_save = gtk_file_chooser_dialog_new (_("Save csu file"),GTK_WINDOW(user_data->ptr_main_window),
                GTK_FILE_CHOOSER_ACTION_SAVE,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-save",GTK_RESPONSE_ACCEPT,NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(window_file_save), true);

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
		    char true_filename[SIZE_MAX_FILE_NAME];
			#ifdef _WIN32
		    filename=g_convert(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_save)),-1,"ISO-8859-1","UTF-8",NULL,NULL,NULL);
		    #else
		    filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_save));
		    #endif
		    strcpy(true_filename,filename);

            /* Add the csu extension if the filter is csu */
			if(gtk_file_chooser_get_filter(GTK_FILE_CHOOSER(window_file_save))==csu_filter)
                addFileCsuExtension(true_filename);

            if (writeCsuFile(true_filename,user_data->ptr_csu_struct) == false)
                error=TRUE;
            else
                strncpy(user_data->csu_filename,true_filename,SIZE_MAX_FILE_NAME-1);

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
 * \fn G_MODULE_EXPORT void copyToClipboard(GtkWidget *widget, gpointer data)
 *  Copy the selected text to clipboard
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void copyToClipboard(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    if (GTK_IS_EDITABLE(gtk_window_get_focus(GTK_WINDOW(user_data->ptr_main_window))))
        gtk_editable_copy_clipboard(GTK_EDITABLE(gtk_window_get_focus(GTK_WINDOW(user_data->ptr_main_window))));
}

/*!
 * \fn G_MODULE_EXPORT void pastFromClipboard(GtkWidget *widget, gpointer data)
 *  Past a text from the clipboard
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void pastFromClipboard(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    if (GTK_IS_EDITABLE(gtk_window_get_focus(GTK_WINDOW(user_data->ptr_main_window))))
        gtk_editable_paste_clipboard(GTK_EDITABLE(gtk_window_get_focus(GTK_WINDOW(user_data->ptr_main_window))));
}

/*!
 * \fn G_MODULE_EXPORT void deleteSelectedText(GtkWidget *widget, gpointer data)
 *  Delete the selected text
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void deleteSelectedText(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    if (GTK_IS_EDITABLE(gtk_window_get_focus(GTK_WINDOW(user_data->ptr_main_window))))
        gtk_editable_delete_selection(GTK_EDITABLE(gtk_window_get_focus(GTK_WINDOW(user_data->ptr_main_window))));
}

/*!
 * \fn G_MODULE_EXPORT void cutToClipboard(GtkWidget *widget, gpointer data)
 *  Cut the selected text to clipboard
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void cutToClipboard(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    if (GTK_IS_EDITABLE(gtk_window_get_focus(GTK_WINDOW(user_data->ptr_main_window))))
        gtk_editable_cut_clipboard(GTK_EDITABLE(gtk_window_get_focus(GTK_WINDOW(user_data->ptr_main_window))));
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

    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_filename"));
    gchar filename[SIZE_MAX_FILE_NAME];
    getSimpleFilenameFromFullFilename(data->csu_filename,filename);
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Filename: %s"),filename));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_date"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Created on the: %02.0f/%02.0f/%4.0f"),data->ptr_csu_struct->day,data->ptr_csu_struct->month,data->ptr_csu_struct->year));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_version"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("File's version: %1.1f"),data->ptr_csu_struct->version));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_size_max_name"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Maximum size of the names: %.0f"),data->ptr_csu_struct->size_max_name));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_number_player"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of players: %.0f"),data->ptr_csu_struct->nb_player));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Maximum number of turns: %d"),maxNbTurn(data->ptr_csu_struct)-1));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_config_name"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Name of the game configuration: %s"),data->ptr_csu_struct->config.name));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_use_max"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Use a maximum score: %s"),integerToYesNo(data->ptr_csu_struct->config.max,yes,no)));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_initial_score"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Initial score: %.3f"),data->ptr_csu_struct->config.begin_score));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_digit"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of decimals displayed: %d"),data->ptr_csu_struct->config.decimal_place));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_first_way"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("The winner is the player who has the highest score: %s"),integerToYesNo(data->ptr_csu_struct->config.first_way,yes,no)));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Turn-based game: %s"),integerToYesNo(data->ptr_csu_struct->config.turn_based,yes,no)));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_distributor_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Use a distributor: %s"),integerToYesNo(data->ptr_csu_struct->config.use_distributor,yes,no)));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_max"));
    #ifdef __unix__
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Maximum/minimum number of points: %.3f"),data->ptr_csu_struct->config.nb_max));
    #elif _WIN32
    if (data->ptr_csu_struct->config.nb_max == INFINITY)
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Maximum/minimum number of points: inf")));
    else
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Maximum/minimum number of points: %.3f"),data->ptr_csu_struct->config.nb_max));
    #endif

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_distributor"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Distributor: %s"),data->ptr_csu_struct->player_names[(int)data->ptr_csu_struct->distributor]));
}

/*!
 * \fn G_MODULE_EXPORT void showPropertiesDialogBox(GtkWidget *widget, gpointer data)
 *  Show the properties window
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void showPropertiesDialogBox(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    if (user_data->ptr_csu_struct == NULL)
        return;

    /* Get the dialog box */
    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"csu_file_properties_dialog_box"));
    if (!dialog)
        g_critical(_("Widget csu_file_properties_dialog_box is missing in file csuper-gui.glade."));

    updateCsuInfo(user_data);

    gtk_widget_show_all(dialog);

    gtk_dialog_run(GTK_DIALOG(dialog));
}

/*!
 * \fn void addLastCsuStruct(globalData *data)
 *  Add the current csu structure into the last csu structure
 * \param[in] data the globalData
 */
void addLastCsuStruct(globalData *data)
{
    gint i;

    /* Delete the last redo available */
    if (data->indexLastCsuStruct > 0)
    {
        for (i=0 ; i < data->nbLastCsuStruct - data->indexLastCsuStruct ; i++)
            data->lastCsuStruct[i] = data->lastCsuStruct[i+data->indexLastCsuStruct];

        data->nbLastCsuStruct -= data->indexLastCsuStruct;
        data->indexLastCsuStruct = 0;
    }


    /* Delete the last csu structure if the array is full */
    if (data->nbLastCsuStruct == NB_LAST_CSU_STRUCT)
        closeCsuStruct(data->lastCsuStruct[NB_LAST_CSU_STRUCT-1]);
    else
        data->nbLastCsuStruct++;

    /* Add the current csu structure */
    for (i=data->nbLastCsuStruct - 2 ; i >= 0 ; i--)
        data->lastCsuStruct[i+1] = data->lastCsuStruct[i];
    data->lastCsuStruct[0] = copyCsuStruct(data->ptr_csu_struct);

}

/*!
 * \fn void deleteAllLastCsuStruct(globalData *data)
 *  Delete all the last csu structure
 * \param[in] data the globalData
 */
void deleteAllLastCsuStruct(globalData *data)
{
    gint i;

    for (i=0 ; i < data->nbLastCsuStruct -1 ; i++)
        closeCsuStruct(data->lastCsuStruct[i]);

    data->indexLastCsuStruct = 0;
    data->nbLastCsuStruct = 0;
}

/*!
 * \fn G_MODULE_EXPORT void undoCsuStruct(GtkWidget *widget, gpointer data)
 *  Get the last csu structure
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void undoCsuStruct(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    if (user_data->indexLastCsuStruct < user_data->nbLastCsuStruct-1)
    {
        closeCsuStruct(user_data->ptr_csu_struct);
        user_data->indexLastCsuStruct++;
        user_data->ptr_csu_struct = copyCsuStruct(user_data->lastCsuStruct[user_data->indexLastCsuStruct]);
        writeFileNewTurn(user_data->csu_filename,user_data->ptr_csu_struct);
        updateMainWindow(user_data,TRUE);
    }
}

/*!
 * \fn G_MODULE_EXPORT void redoCsuStruct(GtkWidget *widget, gpointer data)
 *  Get the last new csu structure
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void redoCsuStruct(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    if (user_data->indexLastCsuStruct > 0)
    {
        closeCsuStruct(user_data->ptr_csu_struct);
        user_data->indexLastCsuStruct--;
        user_data->ptr_csu_struct = copyCsuStruct(user_data->lastCsuStruct[user_data->indexLastCsuStruct]);
        writeFileNewTurn(user_data->csu_filename,user_data->ptr_csu_struct);
        updateMainWindow(user_data,!exceedMaxNumber(user_data->ptr_csu_struct));
    }
}

/*!
 * \fn void updateToolbarButton(globalData *data)
 *  Show or hide button of the toolbar
 * \param[in] data the globalData
 */
void updateToolbarButton(globalData *data)
{
    toolbar_button_preferences_struct toolbar_preferences;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFileToolbarButtonPreferences(home_path,&toolbar_preferences);

    GtkWidget *main_toolbar = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_toolbar"));
    if (!main_toolbar)
        g_critical(_("Widget main_toolbar is missing in file csuper-gui.glade."));

    if (toolbar_preferences.new == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),0)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),0)));

    if (toolbar_preferences.open == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),1)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),1)));

    if (toolbar_preferences.save_as == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),2)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),2)));

    if (toolbar_preferences.separator_6 == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),3)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),3)));

    if (toolbar_preferences.delete_file == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),4)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),4)));

    if (toolbar_preferences.print == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),5)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),5)));

    if (toolbar_preferences.separator_1 == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),6)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),6)));

    if (toolbar_preferences.undo == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),7)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),7)));

    if (toolbar_preferences.redo == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),8)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),8)));

    if (toolbar_preferences.separator_2 == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),9)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),9)));

    if (toolbar_preferences.cut == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),10)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),10)));

    if (toolbar_preferences.copy == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),11)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),11)));

    if (toolbar_preferences.paste == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),12)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),12)));

    if (toolbar_preferences.delete == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),13)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),13)));

    if (toolbar_preferences.separator_3 == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),14)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),14)));

    if (toolbar_preferences.properties == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),15)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),15)));

    if (toolbar_preferences.separator_4 == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),16)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),16)));

    if (toolbar_preferences.preferences == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),17)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),17)));

    if (toolbar_preferences.game_configuration_preferences == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),18)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),18)));

    if (toolbar_preferences.toolbar_button_preferences == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),19)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),19)));

    if (toolbar_preferences.separator_5 == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),20)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),20)));

    if (toolbar_preferences.about == false)
        gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),21)));
    else
        gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),21)));
}

/*!
 * \fn G_MODULE_EXPORT void deleteFileButton(GtkWidget *widget, gpointer data)
 *  Delete the current file
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void deleteFileButton(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    if (deleteFile(user_data->csu_filename))
    {
        updateMainWindow(user_data,FALSE);
        closeCsuStruct(user_data->ptr_csu_struct);
        user_data->ptr_csu_struct = NULL;
        deleteAllLastCsuStruct(user_data);
        setButtonMainWindowSensitive(user_data);
    }
    else
        deleteFileError(user_data);
}

/*!
 * \fn void deleteFileError(globalData *data)
 *  Display a dialog box which said that there is a problem when deleting the file.
 * \param[in] data the globalData
 */
void deleteFileError(globalData *data)
{
    GtkWidget *window_error = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"file_not_deleted"));
    if (!window_error)
        g_critical(_("Widget file_not_deleted is missing in file csuper-gui.glade."));

    gtk_dialog_run (GTK_DIALOG (window_error));
    gtk_widget_hide (window_error);
}
