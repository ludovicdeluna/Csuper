/*!
 * \file    exportation_preferences.c
 * \brief   The preferences of csuper
 * \author  Remi BERTHO
 * \date    10/01/15
 * \version 4.2.0
 */

 /*
 * exportation_preferences.c
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

 #include "exportation_preferences.h"


/*!
 * \fn void updateExportationPreferences(globalData *data)
 *  Update the exportation preferences window
 * \param[in] data the globalData
 */
void updateExportationPreferences(globalData *data)
{
    export_pdf_preferences pref;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFilePdfPreferences(home_path,&pref);

    GtkWidget *grid = getWidgetFromBuilder(data->ptr_builder,"grid_exportation_preferences");

    // Charset
    if (canUseUtf8Pdf())
    {
        if (pref.charset == UTF8)
            gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,1)),TRUE);
        else
            gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,1)),FALSE);
    } else
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),1,1)),FALSE);

    // Direction
    if (pref.direction == HPDF_PAGE_PORTRAIT)
        gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,1)),0);
    else
        gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,1)),1);

    // Size
    if (pref.size == HPDF_PAGE_SIZE_A3)
        gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,2)),2);
    else if (pref.size == HPDF_PAGE_SIZE_A4)
        gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,2)),1);
    else
        gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,2)),0);

    // Margin
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),3,2)),pref.margin);

    // Font size
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),1,3)),pref.font_size);

    // Total points by turn
    if (pref.total_points_turn == true)
        gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),3,3)),TRUE);
    else
        gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),3,3)),FALSE);

    // Ranking by turn
    if (pref.ranking_turn == true)
        gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,4)),TRUE);
    else
        gtk_switch_set_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,4)),FALSE);
}


/*!
 * \fn void readExportationPreferences(globalData *data, export_pdf_preferences *pref)
 *  Read the export_pdf_preferences with the exportation preferences window
 * \param[in] data the globalData
 * \param[in] pref the exportation preferences
 */
void readExportationPreferences(globalData *data, export_pdf_preferences *pref)
{
    GtkWidget *grid = getWidgetFromBuilder(data->ptr_builder,"grid_exportation_preferences");

    // Charset
    if (gtk_switch_get_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,1))))
        pref->charset = UTF8;
    else
        pref->charset = ISO885915;

    // Direction
    if (gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),3,1))) == 0)
        pref->direction = HPDF_PAGE_PORTRAIT;
    else
        pref->direction = HPDF_PAGE_LANDSCAPE;

    // Size
    if (gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,2))) == 0)
        pref->size = HPDF_PAGE_SIZE_A5;
    else if (gtk_combo_box_get_active(GTK_COMBO_BOX(gtk_grid_get_child_at(GTK_GRID(grid),1,2))) == 1)
        pref->size = HPDF_PAGE_SIZE_A4;
    else
        pref->size = HPDF_PAGE_SIZE_A3;

    // Margin
    pref->margin = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),3,2)));

    // Font size
    pref->font_size = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),1,3)));

    // Total points by turn
    if (gtk_switch_get_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),3,3))))
        pref->total_points_turn = true;
    else
        pref->total_points_turn = false;

    // Ranking by turn
    if (gtk_switch_get_active(GTK_SWITCH(gtk_grid_get_child_at(GTK_GRID(grid),1,4))))
        pref->ranking_turn = true;
    else
        pref->ranking_turn = false;
}


/*!
 * \fn G_MODULE_EXPORT void checkExportationPreferencesChanged(GtkWidget *widget,gpointer data)
 *  Check if the exportation preferences change relative to this save in the file
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void checkExportationPreferencesChanged(GtkWidget *widget,gpointer data)
{
    globalData *user_data = (globalData*) data;
    export_pdf_preferences pref_file;
    export_pdf_preferences pref_graph;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFilePdfPreferences(home_path,&pref_file);
    readExportationPreferences(user_data,&pref_graph);

    GtkWidget *apply_button = getWidgetFromBuilder(user_data->ptr_builder,"apply_button_exportation_preferences");

    gtk_widget_set_sensitive(apply_button,differentsTExportPdfPreferencesStruct(pref_file,pref_graph));
}


/*!
 * \fn G_MODULE_EXPORT void checkExportationPreferencesChangedSwitchButton(GObject *gobject,GParamSpec *pspec,gpointer user_data)
 *  Check if the exportation preferences change relative to this save in the file
 * Used with the GTKSwitchButton
 * \param[in] gobject the object which received the signal
 * \param[in] pspec the GParamSpec of the property which changed
 * \param[in] user_data user data set when the signal handler was connected
 */
G_MODULE_EXPORT void checkExportationPreferencesChangedSwitchButton(GObject *gobject,GParamSpec *pspec,gpointer user_data)
{
    checkExportationPreferencesChanged(NULL,user_data);
}


/*!
 * \fn G_MODULE_EXPORT void validExportationPreferences(GtkWidget *widget, gpointer data)
 *  Validate the exportation preferences
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void validExportationPreferences(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    export_pdf_preferences pref;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readExportationPreferences(user_data,&pref);

    createFilePdfPreferences(home_path,&pref);
    updateExportationPreferences(user_data);
    checkExportationPreferencesChanged(NULL,user_data);
}
