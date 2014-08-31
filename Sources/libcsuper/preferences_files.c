/*!
 * \file    preferences_files.c
 * \brief   Function which store preferences into files
 * \author  Remi BERTHO
 * \date    31/08/14
 * \version 4.2.0
 */

 /*
 * preferences_files.c
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
 *
 * This file is part of LibCsuper.
 *
 * LibCsuper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibCsuper is distributed in the hope that it will be useful,
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

 #include "preferences_files.h"

/*!
 * \fn void createPreferencesFolder(char *home_path)
 *  Create the folder which contain all preferences
 * \param[in] home_path the path to the home directory
 */
void createPreferencesFolder(char *home_path)
{
    char folder[SIZE_MAX_FILE_NAME];

    sprintf(folder,"%s%s",home_path,PREFERENCES_FOLDER_NAME);

    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif
}

/*!
 * \fn bool createFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct toolbar)
 *  Create the file which contain the preferences for the toolbar button
 * \param[in] home_path the path to the home directory
 * \param[in] toolbar the toolbar button preferences
 * \return true if everything is OK, false otherwise
 */
bool createFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct toolbar)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_TOOLBAR_BUTTON_PREFERENCES);

    createPreferencesFolder(home_path);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",toolbar.new,toolbar.open,toolbar.save_as,
            toolbar.separator_6,toolbar.delete_file,toolbar.print,
            toolbar.separator_1,toolbar.undo,toolbar.redo,toolbar.separator_2,toolbar.cut,toolbar.copy,toolbar.paste,
            toolbar.delete,toolbar.separator_3,toolbar.properties,toolbar.separator_4,toolbar.preferences,
            toolbar.game_configuration_preferences,toolbar.toolbar_button_preferences,toolbar.separator_5,toolbar.about);

    closeFile(ptr_file);

    return true;
}

/*!
 * \fn bool readFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct *toolbar)
 *  Read the file which contain the preferences for the toolbar button
 * \param[in] home_path the path to the home directory
 * \param[in] toolbar the toolbar button preferences
 * \return true if everything is OK, false otherwise
 */
bool readFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct *toolbar)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;
    toolbar->open=true;
    toolbar->new=true;
    toolbar->save_as=true;
    toolbar->separator_6=true;
    toolbar->delete_file=false;
    toolbar->print=true;
    toolbar->separator_1=true;
    toolbar->undo=true;
    toolbar->redo=true;
    toolbar->separator_2=true;
    toolbar->cut=false;
    toolbar->copy=false;
    toolbar->paste=false;
    toolbar->delete=false;
    toolbar->separator_3=false;
    toolbar->properties=true;
    toolbar->separator_4=true;
    toolbar->preferences=true;
    toolbar->game_configuration_preferences=false;
    toolbar->toolbar_button_preferences=false;
    toolbar->separator_5=true;
    toolbar->about=true;

    createPreferencesFolder(home_path);

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_TOOLBAR_BUTTON_PREFERENCES);

    ptr_file=openFile(file_name,"r");

    if (ptr_file==NULL)
    {
        if (createFileToolbarButtonPreferences(home_path,*toolbar) == false)
            return false;
        else
            return true;
    }

    fscanf(ptr_file,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",&(toolbar->new),&(toolbar->open),&(toolbar->save_as),
           &(toolbar->separator_6),&(toolbar->delete_file),&(toolbar->print),
        &(toolbar->separator_1),&(toolbar->undo),&(toolbar->redo),&(toolbar->separator_2),&(toolbar->cut),&(toolbar->copy),&(toolbar->paste),
        &(toolbar->delete),&(toolbar->separator_3),&(toolbar->properties),&(toolbar->separator_4),&(toolbar->preferences),
        &(toolbar->game_configuration_preferences),&(toolbar->toolbar_button_preferences),&(toolbar->separator_5),&(toolbar->about));

    closeFile(ptr_file);

    return true;
}

/*!
 * \fn bool differentsToolbarButtonPreferencesStruct(toolbar_button_preferences_struct toolbar1, toolbar_button_preferences_struct toolbar2)
 *  Test if the two toolbar button preferences are different
 * \param[in] toolbar1 the first toolbar button preferences
 * \param[in] toolbar2 the second toolbar button preferences
 * \return true if everything is OK, false otherwise
 */
bool differentsToolbarButtonPreferencesStruct(toolbar_button_preferences_struct toolbar1, toolbar_button_preferences_struct toolbar2)
{
    if (toolbar1.new != toolbar2.new || toolbar1.open != toolbar2.open || toolbar1.save_as != toolbar2.save_as || toolbar1.separator_1 != toolbar2.separator_1
            || toolbar1.separator_6 != toolbar2.separator_6 || toolbar1.delete_file != toolbar2.delete_file || toolbar1.print != toolbar2.print
            || toolbar1.undo != toolbar2.undo || toolbar1.redo != toolbar2.redo || toolbar1.separator_2 != toolbar2.separator_2 ||
            toolbar1.cut != toolbar2.cut || toolbar1.copy != toolbar2.copy || toolbar1.paste != toolbar2.paste || toolbar1.delete != toolbar2.delete
            || toolbar1.separator_3 != toolbar2.separator_3 || toolbar1.properties != toolbar2.properties || toolbar1.separator_4 != toolbar2.separator_4
            || toolbar1.preferences != toolbar2.preferences || toolbar1.game_configuration_preferences != toolbar2.game_configuration_preferences ||
            toolbar1.toolbar_button_preferences != toolbar2.toolbar_button_preferences || toolbar1.separator_5 != toolbar2.separator_5
            || toolbar1.about != toolbar2.about)
        return true;
    else
        return false;
}

/*!
 * \fn bool createFileMainWidowSize(char *home_path, main_window_size size)
 *  Create the file which contain the main window size
 * \param[in] home_path the path to the home directory
 * \param[in] size the size of the main window
 * \return true if everything is OK, false otherwise
 */
bool createFileMainWidowSize(char *home_path, main_window_size size)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_MAIN_WINDOW_SIZE);

    createPreferencesFolder(home_path);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%d %d %d",size.width,size.height,size.is_maximize);

    closeFile(ptr_file);

    return true;
}

/*!
 * \fn bool readFileMainWidowSize(char *home_path, main_window_size *size)
 *  Read the file which contain the main window size
 * \param[in] home_path the path to the home directory
 * \param[in] size the size of the main window
 * \return true if everything is OK, false otherwise
 */
bool readFileMainWidowSize(char *home_path, main_window_size *size)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    size->height=422;
    size->width=851;
    size->is_maximize = false;

    createPreferencesFolder(home_path);

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_MAIN_WINDOW_SIZE);

    ptr_file=openFile(file_name,"r");

    if (ptr_file==NULL)
    {
        if (createFileMainWidowSize(home_path,*size) == false)
            return false;
        else
            return true;
    }

    fscanf(ptr_file,"%d %d %d",&(size->width),&(size->height),&(size->is_maximize));

    closeFile(ptr_file);

    return true;
}

/*!
 * \fn bool createFileSystemPath()
 *  Create the folder and the file which contain the system path
 * \return true if everything is OK, false otherwise
 */
bool createFileSystemPath()
{
    char folder[SIZE_MAX_FILE_NAME];
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    /*Read the home directory and create the folder*/
    readHomePath(folder);
    sprintf(folder,"%s/%s",folder,PREFERENCES_FOLDER_NAME);
    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif

    sprintf(file_name,"%s/%s",folder,FILENAME_SYSTEM_PATH);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%s",folder);

    closeFile(ptr_file);

    return true;
}

/*!
 * \fn bool readFileSystemPath(char *file_name)
 *  Read the system path and the path read to the filename
 * \param[in,out] *file_name the filename
 * \return true if everything is OK, false otherwise
 */
bool readFileSystemPath(char *file_name)
{
    char file_name_preferences[SIZE_MAX_FILE_NAME];
    char folder[SIZE_MAX_FILE_NAME];
    int file_size;
    FILE *ptr_file;

    readHomePath(file_name_preferences);
    sprintf(file_name_preferences,"%s/%s/%s",file_name_preferences,PREFERENCES_FOLDER_NAME,FILENAME_SYSTEM_PATH);

    ptr_file=openFile(file_name_preferences,"r");

    if(ptr_file == NULL)
        return false;

    file_size=readFileSize(ptr_file);
    fgets(folder,file_size+1,ptr_file);
    closeFile(ptr_file);

    sprintf(folder,"%s/%s",folder,file_name);
    strcpy(file_name,folder);

    return true;
}

/*!
 * \fn bool readSystemPath(char *file_name)
 *  Add the system path, if the file system path doesn't exist, it create it.
 * \param[in,out] *file_name the filename
 * \return true if everything is OK, false otherwise
 */
bool readSystemPath(char *file_name)
{
    libcsuper_initialize();

    if (readFileSystemPath(file_name)==false)
    {
        if(createFileSystemPath()==false)
        {
            printf(_("\nError while reading the file containing the system path.\n"));
            return false;
        }
        if (readFileSystemPath(file_name)==false)
        {
            printf(_("\nError while reading the file containing the system path.\n"));
            return false;
        }
    }
    return true;
}

/*!
 * \fn bool changeSystemPath(char *new_path)
 *  Change the system path
 * \param[in,out] *new_path the new path
 * \return true if everything is OK, false otherwise
 */
bool changeSystemPath(char *new_path)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    if (checkPath(new_path) == false)
        return false;

    if (createFileSystemPath()==false)
        return false;

    readHomePath(file_name);

    sprintf(file_name,"%s/%s/%s",file_name,PREFERENCES_FOLDER_NAME,FILENAME_SYSTEM_PATH);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%s",new_path);

    closeFile(ptr_file);

    return true;
}


