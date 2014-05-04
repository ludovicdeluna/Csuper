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
 *  Begin csuper.
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
