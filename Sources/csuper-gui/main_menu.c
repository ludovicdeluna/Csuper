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

 #include "main_menu.h"
 #include "chart.h"

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
    GtkWidget *window_about = getWidgetFromBuilder(user_data->ptr_builder,"about_window");

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
        gtk_file_chooser_set_current_folder_file(GTK_FILE_CHOOSER(window_file_open),g_file_new_for_path(g_locale_to_utf8(system_path,-1,NULL,NULL,NULL)),NULL);
        #endif
    }
    else
    {
        gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(window_file_open),g_locale_to_utf8(user_data->csu_filename,-1,NULL,NULL,NULL));
    }

	switch (gtk_dialog_run (GTK_DIALOG (window_file_open)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
		    /* Get the filename*/
		    gchar *filename;
		    filename=g_locale_from_utf8(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_open)),-1,NULL,NULL,NULL);

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
                fillCalculatorNames(user_data);
                setButtonMainWindow(user_data);
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
 * \fn G_MODULE_EXPORT void recentCsuFileOpen(GtkRecentChooser *chooser, gpointer data)
 *  Open a recent csu file.
 * \param[in] chooser the GtkRecentChooser which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void recentCsuFileOpen(GtkRecentChooser *chooser, gpointer data)
{
    globalData *user_data = (globalData*) data;

    /* Get the filename*/
    gchar *uri,*filename;
    uri=gtk_recent_chooser_get_current_uri(GTK_RECENT_CHOOSER(chooser));
    filename=g_filename_from_uri(uri,NULL,NULL);

    if (user_data->ptr_csu_struct != NULL)
        closeCsuStruct(user_data->ptr_csu_struct);

    user_data->ptr_csu_struct=NULL;
    (user_data->ptr_csu_struct) = readCsuFile(filename);
    if((user_data->ptr_csu_struct) == NULL)
        openFileError(user_data);
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
        fillCalculatorNames(user_data);
        setButtonMainWindow(user_data);
    }
    g_free(uri);
    g_free(filename);
}

/*!
 * \fn void openFileError(globalData *data)
 *  Display a dialog box which said that there is a problem when loading the file.
 * \param[in] data the globalData
 */
void openFileError(globalData *data)
{
    GtkWidget *window_error = getWidgetFromBuilder(data->ptr_builder,"file_not_open");

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
    gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(window_file_save),g_locale_to_utf8(user_data->csu_filename,-1,NULL,NULL,NULL));


	switch (gtk_dialog_run (GTK_DIALOG (window_file_save)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
		    char *filename;
		    char true_filename[SIZE_MAX_FILE_NAME];
		    filename=g_locale_from_utf8(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_save)),-1,NULL,NULL,NULL);

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
 * \fn G_MODULE_EXPORT void chooseExportFile(GtkWidget *widget, gpointer data)
 *  Choose and export the current file file
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void chooseExportFile(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    int error=FALSE;
    gchar export_filename[SIZE_MAX_FILE_NAME];
    gchar folder[SIZE_MAX_FILE_NAME];

    if(user_data->ptr_csu_struct == NULL)
        return;

    /* Create the file chooser dialog*/
    GtkWidget *window_file_export = gtk_file_chooser_dialog_new (_("Export csu file"),GTK_WINDOW(user_data->ptr_main_window),
                GTK_FILE_CHOOSER_ACTION_SAVE,"gtk-cancel", GTK_RESPONSE_CANCEL,"gtk-save",GTK_RESPONSE_ACCEPT,NULL);

    /* Give filename to the old filename*/
    getSimpleFilenameFromFullFilename(user_data->csu_filename,export_filename);
    strcpy(folder,user_data->csu_filename);
    getFolderFromFilename(folder);
    removeFileExtension(export_filename);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(window_file_export),g_locale_to_utf8(folder,-1,NULL,NULL,NULL));
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(window_file_export),g_locale_to_utf8(export_filename,-1,NULL,NULL,NULL));


     /*Add filters*/
    GtkFileFilter *pdf_filter= GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefilterpdf"));
    GtkFileFilter *csv_filter= GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefiltercsv"));
    GtkFileFilter *gnuplot_filter= GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefiltergnuplot"));
    GtkFileFilter *octave_filter= GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefilteroctave"));
    GtkFileFilter *svg_filter= GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefiltersvg"));
    GtkFileFilter *png_filter= GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefilterpng"));
    GtkFileFilter *pdf_chart_filter= GTK_FILE_FILTER(gtk_builder_get_object(user_data->ptr_builder,"filefilterpdfchart"));
    gtk_file_filter_set_name(pdf_filter,_("PDF files"));
    gtk_file_filter_set_name(csv_filter,_("CSV files"));
    gtk_file_filter_set_name(gnuplot_filter,_("Gnuplot files"));
    gtk_file_filter_set_name(octave_filter,_("Octave/Matlab files"));
    gtk_file_filter_set_name(svg_filter,_("SVG files"));
    gtk_file_filter_set_name(png_filter,_("PNG files"));
    gtk_file_filter_set_name(pdf_chart_filter,_("PDF chart files"));
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_export),csv_filter);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_export),svg_filter);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_export),pdf_filter);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_export),gnuplot_filter);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_export),octave_filter);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_export),png_filter);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (window_file_export),pdf_chart_filter);
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER (window_file_export),pdf_filter);

	switch (gtk_dialog_run (GTK_DIALOG (window_file_export)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
		    char *filename;
		    char true_filename[SIZE_MAX_FILE_NAME];
		    filename=g_locale_from_utf8(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (window_file_export)),-1,NULL,NULL,NULL);

		    strcpy(true_filename,filename);

            /* Export */
            GtkFileFilter* filter = gtk_file_chooser_get_filter(GTK_FILE_CHOOSER(window_file_export));
			if(filter == pdf_filter)
            {
                addFilePdfExtension(true_filename);
                if (exportToPdf(user_data->ptr_csu_struct,true_filename) == false)
                    error=TRUE;
            }
            else if(filter == csv_filter)
            {
                addFileCsvExtension(true_filename);
                if (exportToCsv(user_data->ptr_csu_struct,true_filename) == false)
                    error=TRUE;
            }
            else if(filter == gnuplot_filter)
            {
                if (exportToGnuplotFile(user_data->ptr_csu_struct,true_filename) == false)
                    error=TRUE;
            }
            else if(filter == octave_filter)
            {
                addFileExtension(true_filename,"m");
                if (exportToM(user_data->ptr_csu_struct,true_filename) == false)
                    error=TRUE;
            }
            else if(filter == svg_filter)
            {
                addFileExtension(true_filename,"svg");
                if (exportToSvg(user_data->ptr_csu_struct,true_filename) == false)
                    error=TRUE;
            }
            else if(filter == png_filter)
            {
                addFileExtension(true_filename,"png");
                if (exportToPng(user_data->ptr_csu_struct,true_filename) == false)
                    error=TRUE;
            }
            else if(filter == pdf_chart_filter)
            {
                addFileExtension(true_filename,"pdf");
                if (exportToPdfChart(user_data->ptr_csu_struct,true_filename) == false)
                    error=TRUE;
            }

            g_free(filename);
			break;
		}
		default:
			break;
	}
	gtk_widget_destroy(window_file_export);
	if (error)
        exportFileError(user_data);
}

/*!
 * \fn void saveFileError(globalData *data)
 *  Display a dialog box which said that there is a problem when saving the file.
 * \param[in] data the globalData
 */
void saveFileError(globalData *data)
{
    GtkWidget *window_error = getWidgetFromBuilder(data->ptr_builder,"file_not_save");

    gtk_dialog_run (GTK_DIALOG (window_error));
    gtk_widget_hide (window_error);
}

/*!
 * \fn void exportFileError(globalData *data)
 *  Display a dialog box which said that there is a problem when exporting the file.
 * \param[in] data the globalData
 */
void exportFileError(globalData *data)
{
    GtkWidget *window_error = getWidgetFromBuilder(data->ptr_builder,"file_not_export");

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

    GtkLabel *label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_filename"));
    gchar filename[SIZE_MAX_FILE_NAME];
    getSimpleFilenameFromFullFilename(data->csu_filename,filename);
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Filename: %s"),filename));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_date"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Created on the: %02.0f/%02.0f/%4.0f"),data->ptr_csu_struct->day,data->ptr_csu_struct->month,data->ptr_csu_struct->year));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_version"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("File's version: %1.1f"),data->ptr_csu_struct->version));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_size_max_name"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Maximum size of the names: %.0f"),data->ptr_csu_struct->size_max_name));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_number_player"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of players: %.0f"),data->ptr_csu_struct->nb_player));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_nb_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Maximum number of turns: %d"),maxNbTurn(data->ptr_csu_struct)-1));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_config_name"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Name of the game configuration: %s"),data->ptr_csu_struct->config.name));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_use_max"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Use a maximum score: %s"),integerToYesNo(data->ptr_csu_struct->config.max,yes,no)));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_initial_score"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Initial score: %.3f"),data->ptr_csu_struct->config.begin_score));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_nb_digit"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of decimals displayed: %d"),data->ptr_csu_struct->config.decimal_place));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_first_way"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("The winner is the player who has the highest score: %s"),integerToYesNo(data->ptr_csu_struct->config.first_way,yes,no)));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Turn-based game: %s"),integerToYesNo(data->ptr_csu_struct->config.turn_based,yes,no)));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_distributor_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Use a distributor: %s"),integerToYesNo(data->ptr_csu_struct->config.use_distributor,yes,no)));

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_nb_max"));
    #ifdef __unix__
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Maximum/minimum number of points: %.3f"),data->ptr_csu_struct->config.nb_max));
    #elif _WIN32
    if (data->ptr_csu_struct->config.nb_max == INFINITY)
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Maximum/minimum number of points: inf")));
    else
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Maximum/minimum number of points: %.3f"),data->ptr_csu_struct->config.nb_max));
    #endif

    label = GTK_LABEL(getWidgetFromBuilder(data->ptr_builder,"label_distributor"));
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
    GtkWidget *dialog = getWidgetFromBuilder(user_data->ptr_builder,"csu_file_properties_dialog_box");

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
    toolbar_button_preferences_struct toolbar;
    gchar home_path[SIZE_MAX_FILE_NAME]="";
    gint i;

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFileToolbarButtonPreferences(home_path,&toolbar);

    GtkWidget *main_toolbar = getWidgetFromBuilder(data->ptr_builder,"main_toolbar");

    for (i=0 ; i<= 22 ; i++)
    {
        switch (*(&toolbar.new+i))
        {
        case 0:
            gtk_widget_hide(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),i)));
            break;
        case 1:
            gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),i)));
            gtk_tool_item_set_is_important(GTK_TOOL_ITEM(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),i)),FALSE);
            break;
        case 2:
            gtk_widget_show(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),i)));
            gtk_tool_item_set_is_important(GTK_TOOL_ITEM(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),i)),TRUE);
            break;
        }
    }
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

    GtkWidget *window = getWidgetFromBuilder(user_data->ptr_builder,"message_dialog_delete_file");

    switch (gtk_dialog_run (GTK_DIALOG (window)))
	{
		case GTK_RESPONSE_YES:
            if (deleteFile(user_data->csu_filename))
            {
                updateMainWindow(user_data,FALSE);
                closeCsuStruct(user_data->ptr_csu_struct);
                user_data->ptr_csu_struct = NULL;
                deleteAllLastCsuStruct(user_data);
                setButtonMainWindow(user_data);
            }
            else
                deleteFileError(user_data);
            break;
        case GTK_RESPONSE_NO:
            break;
	}
	gtk_widget_hide (window);
}

/*!
 * \fn void deleteFileError(globalData *data)
 *  Display a dialog box which said that there is a problem when deleting the file.
 * \param[in] data the globalData
 */
void deleteFileError(globalData *data)
{
    GtkWidget *window_error = getWidgetFromBuilder(data->ptr_builder,"file_not_deleted");

    gtk_dialog_run (GTK_DIALOG (window_error));
    gtk_widget_hide (window_error);
}

/*!
 * \fn G_MODULE_EXPORT void displayPodium(GtkWidget *widget, gpointer data)
 *  Display the podium
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void displayPodium(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    if (user_data->ptr_csu_struct != NULL)
        gameOver(user_data);
}

/*!
 * \fn G_MODULE_EXPORT void changeDisplayDifferencePoints(GtkWidget *widget, gpointer data)
 *  Update the preference of the differences of the points in the ranking
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void changeDisplayDifferencePoints(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    difference_between_player diff;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE

    GtkWidget *consecutive = getWidgetFromBuilder(user_data->ptr_builder,"menu_display_consecutive");
    GtkWidget *first = getWidgetFromBuilder(user_data->ptr_builder,"menu_display_first");
    GtkWidget *last = getWidgetFromBuilder(user_data->ptr_builder,"menu_display_last");

    diff.consecutive=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(consecutive));
    diff.first=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(first));
    diff.last=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(last));

    createFileDifferenceBetweenPlayer(home_path,diff);

    if (user_data->ptr_csu_struct != NULL)
    {
        deleteRanking(user_data);
        createRanking(user_data);
    }
}


/*!
 * \fn G_MODULE_EXPORT void changeDisplayDifferencePoints(GtkWidget *widget, gpointer data)
 *  Update the preference of the the main points grid
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void changeDisplayPointsGrid(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    score_display score;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE

    GtkWidget *total_points = getWidgetFromBuilder(user_data->ptr_builder,"menu_display_totalpoints");
    GtkWidget *ranking = getWidgetFromBuilder(user_data->ptr_builder,"menu_display_ranking");
    GtkWidget *edit_suppr = getWidgetFromBuilder(user_data->ptr_builder,"menu_display_edit_suppr");

    score.ranking=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(ranking));
    score.total_points=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(total_points));
    score.edit_suppr=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(edit_suppr));

    createFileScoreDisplay(home_path,score);

    if (user_data->ptr_csu_struct != NULL)
        updateMainWindow(user_data,!exceedMaxNumber(user_data->ptr_csu_struct));
}



/*!
 * \fn G_MODULE_EXPORT void changeDisplayMainWindowSide(GtkWidget *widget, gpointer data)
 *  Update the preference of what will be display in the left side of the main window
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void changeDisplayMainWindowSide(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    main_window_side pref;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE

    GtkWidget *calculator = getWidgetFromBuilder(user_data->ptr_builder,"menu_display_calculator");
    GtkWidget *ranking_side = getWidgetFromBuilder(user_data->ptr_builder,"menu_display_ranking_side");
    GtkWidget *game_information = getWidgetFromBuilder(user_data->ptr_builder,"menu_display_game_information");

    pref.ranking=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(ranking_side));
    pref.calculator=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(calculator));
    pref.game_information=gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(game_information));

    createFileMainWindowSide(home_path,pref);

    updateMainWindowSide(user_data);
}


/*!
 * \fn G_MODULE_EXPORT void displayStatistics(GtkWidget *widget, gpointer data)
 *  Display the statistics window
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void displayStatistics(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    GtkWidget *dialog = getWidgetFromBuilder(user_data->ptr_builder,"dialog_statistics");
    GtkWidget *viewport = getWidgetFromBuilder(user_data->ptr_builder,"dialog_statistics_viewport");
    int i;


    GtkWidget *player_display_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(player_display_grid),5);
    gtk_grid_set_row_spacing(GTK_GRID(player_display_grid),5);
    #if GTK_MINOR_VERSION >= 12
    gtk_widget_set_margin_end(player_display_grid,10);
    gtk_widget_set_margin_start(player_display_grid,10);
    #else
    gtk_widget_set_margin_right(player_display_grid,10);
    gtk_widget_set_margin_left(player_display_grid,10);
    #endif // GTK_MINOR_VERSION
    gtk_widget_set_margin_top(player_display_grid,10);
    gtk_widget_set_margin_bottom(player_display_grid,10);
    gtk_widget_set_hexpand(player_display_grid,TRUE);
    gtk_widget_set_vexpand(player_display_grid,TRUE);

    for (i=0 ; i<8 ; i++)
        gtk_grid_attach(GTK_GRID(player_display_grid),gtk_separator_new(GTK_ORIENTATION_VERTICAL),2*i,0,1,2*user_data->ptr_csu_struct->nb_player+3);

    gtk_grid_attach(GTK_GRID(player_display_grid),gtk_label_new(_("Name")),1,1,1,1);
    gtk_grid_attach(GTK_GRID(player_display_grid),gtk_label_new(_("Mean points")),3,1,1,1);
    gtk_grid_attach(GTK_GRID(player_display_grid),gtk_label_new(_("Number of turn")),5,1,1,1);
    gtk_grid_attach(GTK_GRID(player_display_grid),gtk_label_new(_("Number of turn with the best score")),7,1,1,1);
    gtk_grid_attach(GTK_GRID(player_display_grid),gtk_label_new(_("Number of turn with the worst score")),9,1,1,1);
    gtk_grid_attach(GTK_GRID(player_display_grid),gtk_label_new(_("Number of turn first")),11,1,1,1);
    gtk_grid_attach(GTK_GRID(player_display_grid),gtk_label_new(_("Number of turn last")),13,1,1,1);
    gtk_grid_attach(GTK_GRID(player_display_grid),gtk_separator_new(GTK_ORIENTATION_HORIZONTAL),0,0,15,1);
    gtk_grid_attach(GTK_GRID(player_display_grid),gtk_separator_new(GTK_ORIENTATION_HORIZONTAL),0,2,15,1);

    for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
    {
        GtkWidget *tmp_label = gtk_label_new(user_data->ptr_csu_struct->player_names[i]);
        gtk_widget_set_hexpand(tmp_label,TRUE);
        gtk_widget_set_vexpand(tmp_label,TRUE);
        gtk_grid_attach(GTK_GRID(player_display_grid),tmp_label,1,2*(1+i)+1,1,1);

        tmp_label = gtk_label_new(g_strdup_printf("%f",meanPoints(user_data->ptr_csu_struct,i)));
        gtk_widget_set_hexpand(tmp_label,TRUE);
        gtk_widget_set_vexpand(tmp_label,TRUE);
        gtk_grid_attach(GTK_GRID(player_display_grid),tmp_label,3,2*(1+i)+1,1,1);

        tmp_label = gtk_label_new(g_strdup_printf("%.0f",user_data->ptr_csu_struct->nb_turn[i]-1));
        gtk_widget_set_hexpand(tmp_label,TRUE);
        gtk_widget_set_vexpand(tmp_label,TRUE);
        gtk_grid_attach(GTK_GRID(player_display_grid),tmp_label,5,2*(1+i)+1,1,1);

        tmp_label = gtk_label_new(g_strdup_printf("%d",nbTurnBest(user_data->ptr_csu_struct,i)));
        gtk_widget_set_hexpand(tmp_label,TRUE);
        gtk_widget_set_vexpand(tmp_label,TRUE);
        gtk_grid_attach(GTK_GRID(player_display_grid),tmp_label,7,2*(1+i)+1,1,1);

        tmp_label = gtk_label_new(g_strdup_printf("%d",nbTurnWorst(user_data->ptr_csu_struct,i)));
        gtk_widget_set_hexpand(tmp_label,TRUE);
        gtk_widget_set_vexpand(tmp_label,TRUE);
        gtk_grid_attach(GTK_GRID(player_display_grid),tmp_label,9,2*(1+i)+1,1,1);

        tmp_label = gtk_label_new(g_strdup_printf("%d",nbTurnFirst(user_data->ptr_csu_struct,i)));
        gtk_widget_set_hexpand(tmp_label,TRUE);
        gtk_widget_set_vexpand(tmp_label,TRUE);
        gtk_grid_attach(GTK_GRID(player_display_grid),tmp_label,11,2*(1+i)+1,1,1);

        tmp_label = gtk_label_new(g_strdup_printf("%d",nbTurnLast(user_data->ptr_csu_struct,i)));
        gtk_widget_set_hexpand(tmp_label,TRUE);
        gtk_widget_set_vexpand(tmp_label,TRUE);
        gtk_grid_attach(GTK_GRID(player_display_grid),tmp_label,13,2*(1+i)+1,1,1);

        gtk_grid_attach(GTK_GRID(player_display_grid),gtk_separator_new(GTK_ORIENTATION_HORIZONTAL),0,2*(2+i),15,1);
    }

    gtk_container_add(GTK_CONTAINER(viewport),player_display_grid);
    gtk_widget_show_all(viewport);


    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_hide(dialog);
    gtk_widget_destroy(player_display_grid);
}
