/*!
 * \file    main.c
 * \brief   Main
 * \author  Remi BERTHO
 * \date    02/05/14
 * \version 3.0.0
 */

 /*
 * main.c
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

 #include "main.h"

/*!
 * \fn int main(int argc, char *argv[])
 *  Begin csuper-gui.
 * \param[in] argc the number of argument.
 * \param[in] argv the array of argument.
 * \return EXIT_SUCCESS if everything is OK
 */
int main (int   argc, char *argv[])
{
    globalData data;
    GError *error = NULL;
    gchar *filename = NULL;

    data.ptr_csu_struct=NULL;
    strcpy(data.csu_filename,"");

    bindtextdomain("csuper-gui","./Locales");
    bind_textdomain_codeset("csuper-gui","UTF-8");
    textdomain("csuper-gui");

    gtk_init(&argc, &argv);

    data.ptr_builder = gtk_builder_new();
    data.ptr_clipboard=gtk_clipboard_get(gdk_atom_intern("CLIPBOARD",TRUE));
    data.ptr_clipboard_selected=gtk_clipboard_get(gdk_atom_intern("PRIMARY",TRUE));

    filename =  g_build_filename ("csuper-gui.glade", NULL);

    /* Load the glade file. */
    gtk_builder_add_from_file (data.ptr_builder, filename, &error);
    g_free (filename);
    if (error)
    {
      gint code = error->code;
      g_printerr("%s\n", error->message);
      g_error_free (error);
      return code;
    }

    gtk_builder_connect_signals (data.ptr_builder, &data);

    data.ptr_main_window = GTK_WIDGET(gtk_builder_get_object (data.ptr_builder, "main_window"));

    gtk_widget_show_all (data.ptr_main_window);

    gtk_main();

    g_object_unref(data.ptr_builder);

    return 0;
}
