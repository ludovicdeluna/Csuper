/*!
 * \file    preferences_files.c
 * \brief   Function which store preferences into files
 * \author  Remi BERTHO
 * \date    24/06/14
 * \version 4.0
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

    sprintf(folder,"%s/%s",home_path,PREFERENCES_FOLDER_NAME);

    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif
}

/*!
 * \fn int createFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct toolbar)
 *  Create the file which contain the preferences for the toolbar button
 * \param[in] home_path the path to the home directory
 * \param[in] toolbar the toolbar button preferences
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int createFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct toolbar)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    sprintf(file_name,"%s/%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILE_NAME_TOOLBAR_BUTTON_PREFERENCES);

    createPreferencesFolder(home_path);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return MY_FALSE;

    fprintf(ptr_file,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",toolbar.new,toolbar.open,toolbar.save_as,
            toolbar.separator_1,toolbar.undo,toolbar.redo,toolbar.separator_2,toolbar.cut,toolbar.copy,toolbar.paste,
            toolbar.delete,toolbar.separator_3,toolbar.properties,toolbar.separator_4,toolbar.preferences,
            toolbar.game_configuration_preferences,toolbar.toolbar_button_preferences,toolbar.separator_5,toolbar.about);

    closeFile(ptr_file);

    return MY_TRUE;
}

/*!
 * \fn int readFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct *toolbar)
 *  Read the file which contain the preferences for the toolbar button
 * \param[in] home_path the path to the home directory
 * \param[in] toolbar the toolbar button preferences
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int readFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct *toolbar)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;
    toolbar->open=MY_TRUE;
    toolbar->new=MY_TRUE;
    toolbar->save_as=MY_TRUE;
    toolbar->separator_1=MY_TRUE;
    toolbar->undo=MY_TRUE;
    toolbar->redo=MY_TRUE;
    toolbar->separator_2=MY_TRUE;
    toolbar->cut=MY_FALSE;
    toolbar->copy=MY_FALSE;
    toolbar->paste=MY_FALSE;
    toolbar->delete=MY_FALSE;
    toolbar->separator_3=MY_FALSE;
    toolbar->properties=MY_TRUE;
    toolbar->separator_4=MY_TRUE;
    toolbar->preferences=MY_TRUE;
    toolbar->game_configuration_preferences=MY_FALSE;
    toolbar->toolbar_button_preferences=MY_FALSE;
    toolbar->separator_5=MY_TRUE;
    toolbar->about=MY_TRUE;

    createPreferencesFolder(home_path);

    sprintf(file_name,"%s/%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILE_NAME_TOOLBAR_BUTTON_PREFERENCES);

    ptr_file=openFile(file_name,"r");

    if (ptr_file==NULL)
    {
        if (createFileToolbarButtonPreferences(home_path,*toolbar) == MY_FALSE)
            return MY_FALSE;
        else
            return MY_TRUE;
    }

    fscanf(ptr_file,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",&(toolbar->new),&(toolbar->open),&(toolbar->save_as),
        &(toolbar->separator_1),&(toolbar->undo),&(toolbar->redo),&(toolbar->separator_2),&(toolbar->cut),&(toolbar->copy),&(toolbar->paste),
        &(toolbar->delete),&(toolbar->separator_3),&(toolbar->properties),&(toolbar->separator_4),&(toolbar->preferences),
        &(toolbar->game_configuration_preferences),&(toolbar->toolbar_button_preferences),&(toolbar->separator_5),&(toolbar->about));

    closeFile(ptr_file);

    return MY_TRUE;
}

/*!
 * \fn int differentsToolbarButtonPreferencesStruct(toolbar_button_preferences_struct toolbar1, toolbar_button_preferences_struct toolbar2)
 *  Test if the two toolbar button preferences are different
 * \param[in] toolbar1 the first toolbar button preferences
 * \param[in] toolbar1 the second toolbar button preferences
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int differentsToolbarButtonPreferencesStruct(toolbar_button_preferences_struct toolbar1, toolbar_button_preferences_struct toolbar2)
{
    if (toolbar1.new != toolbar2.new || toolbar1.open != toolbar2.open || toolbar1.save_as != toolbar2.save_as || toolbar1.separator_1 != toolbar2.separator_1
            || toolbar1.undo != toolbar2.undo || toolbar1.redo != toolbar2.redo || toolbar1.separator_2 != toolbar2.separator_2 ||
            toolbar1.cut != toolbar2.cut || toolbar1.copy != toolbar2.copy || toolbar1.paste != toolbar2.paste || toolbar1.delete != toolbar2.delete
            || toolbar1.separator_3 != toolbar2.separator_3 || toolbar1.properties != toolbar2.properties || toolbar1.separator_4 != toolbar2.separator_4
            || toolbar1.preferences != toolbar2.preferences || toolbar1.game_configuration_preferences != toolbar2.game_configuration_preferences ||
            toolbar1.toolbar_button_preferences != toolbar2.toolbar_button_preferences || toolbar1.separator_5 != toolbar2.separator_5
            || toolbar1.about != toolbar2.about)
        return MY_TRUE;
    else
        return MY_FALSE;
}

/*!
 * \fn void createFileSystemPath()
 *  Create the folder and the file which contain the system path
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int createFileSystemPath()
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

    sprintf(file_name,"%s/%s",folder,FILE_NAME_SYSTEM_PATH);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return MY_FALSE;

    fprintf(ptr_file,"%s",folder);

    closeFile(ptr_file);

    return MY_TRUE;
}

/*!
 * \fn int readFileSystemPath(char *file_name)
 *  Read the system path and the path read to the filename
 * \param[in,out] *file_name the filename
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int readFileSystemPath(char *file_name)
{
    char file_name_preferences[SIZE_MAX_FILE_NAME];
    char folder[SIZE_MAX_FILE_NAME];
    int file_size;
    FILE *ptr_file;

    readHomePath(file_name_preferences);
    sprintf(file_name_preferences,"%s/%s/%s",file_name_preferences,PREFERENCES_FOLDER_NAME,FILE_NAME_SYSTEM_PATH);

    ptr_file=openFile(file_name_preferences,"r");

    if(ptr_file == NULL)
        return MY_FALSE;

    file_size=readFileSize(ptr_file);
    fgets(folder,file_size+1,ptr_file);
    closeFile(ptr_file);

    sprintf(folder,"%s/%s",folder,file_name);
    strcpy(file_name,folder);

    return MY_TRUE;
}

/*!
 * \fn int readSystemPath(char *file_name)
 *  Add the system path, if the file system path doesn't exist, it create it.
 * \param[in,out] *file_name the filename
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int readSystemPath(char *file_name)
{
    libcsuper_initialize();

    if (readFileSystemPath(file_name)==MY_FALSE)
    {
        if(createFileSystemPath()==MY_FALSE)
        {
            printf(_("\nError while reading the file containing the system path.\n"));
            return MY_FALSE;
        }
        if (readFileSystemPath(file_name)==MY_FALSE)
        {
            printf(_("\nError while reading the file containing the system path.\n"));
            return MY_FALSE;
        }
    }
    return MY_TRUE;
}

/*!
 * \fn int changeSystemPath(char *new_path)
 *  Change the system path
 * \param[in,out] *new_path the new path
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int changeSystemPath(char *new_path)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    if (checkPath(new_path) == MY_FALSE)
        return MY_FALSE;

    if (createFileSystemPath()==MY_FALSE)
        return MY_FALSE;

    readHomePath(file_name);

    sprintf(file_name,"%s/%s/%s",file_name,PREFERENCES_FOLDER_NAME,FILE_NAME_SYSTEM_PATH);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return MY_FALSE;

    fprintf(ptr_file,"%s",new_path);

    closeFile(ptr_file);

    return MY_TRUE;
}

/*!
 * \fn int checkPath(char *path)
 *  Test if the path is valid
 * \param[in,out] *new_path the path
 * \return MY_TRUE if the path is valid OK, MY_FALSE otherwise
 */
int checkPath(char *path)
{
    FILE *ptr_file_test;
    char check_path[SIZE_MAX_FILE_NAME];

    sprintf(check_path,"%s/test-chemin_fichier_csuper",path);
    ptr_file_test=openFile(check_path,"w+");
    if (ptr_file_test != NULL)
    {
        closeFile(ptr_file_test);
        remove(check_path);
        return MY_TRUE;
    }
    else
    {
        printf(_("\nError : this folder is not valid.\n"));
        return MY_FALSE;
    }
}

/*!
 * \fn void readHomePath(char *path)
 *  Read the home path
 * \param[in,out] path the path
 */
void readHomePath(char *path)
{
    #ifdef __unix__
    strcpy(path,getenv("HOME"));
    #elif _WIN32
    strcpy(path,getenv("USERPROFILE"));
    #endif
}

/*!
 * \fn void readHomePath(char *path)
 *  Read the home path with a slash at the end
 * \param[in,out] path the path
 */
void readHomePathSlash(char *path)
{
    #ifdef __unix__
    strcpy(path,getenv("HOME"));
    #elif _WIN32
    strcpy(path,getenv("USERPROFILE"));
    #endif
    sprintf(path,"%s/",path);
}
