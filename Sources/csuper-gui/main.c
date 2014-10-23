/*!
 * \file    main.c
 * \brief   Main
 * \author  Remi BERTHO
 * \date    19/07/14
 * \version 4.0.2
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
int main (int argc, char *argv[])
{
    globalData data;
    GError *error = NULL;
    gchar *glade_filename = NULL;

    /* Change the directory to the directory of the executable */
    #ifdef _WIN32
    char directory[SIZE_MAX_FILE_NAME];
    strncpy(directory,argv[0],SIZE_MAX_FILE_NAME-1);
    if (getFolderFromFilename(directory) == true)
        chdir(directory);
    #endif // _WIN32

    /* Set locales */
    bindtextdomain("csuper-gui","./Locales");
    bind_textdomain_codeset("csuper-gui","UTF-8");
    textdomain("csuper-gui");
    setlocale(LC_ALL,"");

    gtk_init(&argc, &argv);

    /* Init the global data*/
    data.ptr_builder = gtk_builder_new();
    data.ptr_clipboard=gtk_clipboard_get(gdk_atom_intern("CLIPBOARD",TRUE));
    data.ptr_clipboard_selected=gtk_clipboard_get(gdk_atom_intern("PRIMARY",TRUE));
    data.ptr_csu_struct_tmp=NULL;
    data.indexLastCsuStruct=0;
    data.nbLastCsuStruct=0;
    data.ptr_csu_struct=NULL;
    strcpy(data.csu_filename,"");

    /* Load the glade file.*/
    glade_filename =  g_build_filename("csuper-gui.glade", NULL);
    gtk_builder_add_from_file (data.ptr_builder, glade_filename, &error);
    g_free (glade_filename);
    if (error)
    {
      gint code = error->code;
      g_printerr("%s\n", error->message);
      g_error_free (error);
      return code;
    }

    gtk_builder_connect_signals (data.ptr_builder, &data);

    data.ptr_main_window = GTK_WIDGET(gtk_builder_get_object(data.ptr_builder,"main_window"));

    /* Set csuper */
    noCsuFileRanking(&data);
    noCsuFilePoints(&data);
    setButtonMainWindow(&data);
    readMainWindowSize(&data);
    updateToolbarButton(&data);

    if (openFileWithMainArgument(&data,argc,argv) == FALSE)
        return EXIT_FAILURE;

    gtk_widget_show_all(data.ptr_main_window);

    g_timeout_add(50,&setButtonMainWindowClipboardSensitive,&data);

    gtk_main();

    g_object_unref(data.ptr_builder);

    return EXIT_SUCCESS;
}

/*!
 * \fn bool openFileWithMainArgument(globalData *data,int argc, char *argv[])
 *  Open directly a file if there is one in the main argument
 * \param[in] data the globalData
 * \param[in] argc the number of argument.
 * \param[in] argv the array of argument.
 * \return true if everything is OK, FALSE if there is an error while loading the file
 */
bool openFileWithMainArgument(globalData *data,int argc, char *argv[])
{
    /* Open the file which is on second argument id there is one*/
    if (argc < 2)
        return true;

    gchar filename[SIZE_MAX_FILE_NAME];

    #ifdef _WIN32
    strncpy(filename,g_convert(argv[1],-1,"ISO-8859-1","UTF-8",NULL,NULL,NULL),SIZE_MAX_FILE_NAME-1);
    #else
    strncpy(filename,argv[1],SIZE_MAX_FILE_NAME-1);
    #endif // _WIN32

    (data->ptr_csu_struct) = readCsuFile(filename);
    if((data->ptr_csu_struct) != NULL)
    {
        /* Save the folder */
        #ifndef PORTABLE
        gchar folder[SIZE_MAX_FILE_NAME];
        strcpy(folder,filename);
        if (getFolderFromFilename(folder) == true)
            changeSystemPath(folder);
        #endif // PORTABLE

        strcpy(data->csu_filename,filename);
        updateMainWindow(data,!exceedMaxNumber(data->ptr_csu_struct));
        deleteAllLastCsuStruct(data);
        addLastCsuStruct(data);
        setButtonMainWindow(data);
    }
    else
    {
        if (strcmp(argv[1],"") != 0)
        {
            openFileError(data);
            return false;
        }
    }
    return true;
}
