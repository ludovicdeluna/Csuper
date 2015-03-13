/*!
 * \file    preferences.c
 * \brief   The preferences of csuper
 * \author  Remi BERTHO
 * \date    10/01/15
 * \version 4.2.0
 */

 /*
 * preferences.c
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


#include "preferences.h"

/*!
 * \fn G_MODULE_EXPORT void openPreferences(GtkWidget *widget, gpointer data)
 *  Open the preferences
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void openPreferences(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    GtkWidget *window_game = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"preferences_window"));
    if (!window_game)
        g_critical(_("Widget preferences_window is missing in file csuper-gui.glade."));

    displayGameConfiguration(user_data);
    updateToolbarButtonPreferencesSwitch(user_data);
    updateExportationPreferences(user_data);
    checkToolbarButtonPreferencesChanged(NULL,user_data);
    checkExportationPreferencesChanged(NULL,user_data);

    gtk_widget_show_all(window_game);
}

/*!
 * \fn G_MODULE_EXPORT void openGameConfigurationPreferences(GtkWidget *widget, gpointer data)
 *  Open the game configuration preferences
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void openGameConfigurationPreferences(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    GtkWidget *notebook_preferences = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"notebook_preferences"));
    if (!notebook_preferences)
        g_critical(_("Widget notebook_preferences is missing in file csuper-gui.glade."));

    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_preferences),0);

    openPreferences(NULL,user_data);
}

/*!
 * \fn G_MODULE_EXPORT void openToolbarButtonPreferences(GtkWidget *widget, gpointer data)
 *  Open the toolbar button preferences
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void openToolbarButtonPreferences(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    GtkWidget *notebook_preferences = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"notebook_preferences"));
    if (!notebook_preferences)
        g_critical(_("Widget notebook_preferences is missing in file csuper-gui.glade."));

    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_preferences),1);

    openPreferences(NULL,user_data);
}

/*!
 * \fn G_MODULE_EXPORT void openExporationPreferences(GtkWidget *widget, gpointer data)
 *  Open the exportation preferences
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void openExporationPreferences(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    GtkWidget *notebook_preferences = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"notebook_preferences"));
    if (!notebook_preferences)
        g_critical(_("Widget notebook_preferences is missing in file csuper-gui.glade."));

    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_preferences),2);

    openPreferences(NULL,user_data);
}

/*!
 * \fn G_MODULE_EXPORT void closePreferences(GtkWidget *widget, gpointer data)
 *  Close the preferences
 * \param[in] widget the button which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void closePreferences(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    GtkWidget *window_game = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"preferences_window"));
    if (!window_game)
        g_critical(_("Widget preferences_window is missing in file csuper-gui.glade."));

    deleteDisplayGameConfiguration(user_data);

    gtk_widget_hide(window_game);
}

/*!
 * \fn G_MODULE_EXPORT gboolean closePreferencesQuit(GtkWidget *widget, GdkEvent *event, gpointer user_data)
 *  Close the preferences
 * \param[in] widget the widget which send the signal
 * \param[in] event the event which triggered this signal
 * \param[in] user_data the globalData
 */
G_MODULE_EXPORT gboolean closePreferencesQuit(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    closePreferences(widget,user_data);
    return TRUE;
}

