/*!
 * \file    file_system_path.c
 * \brief   Fonctions qui l'emrankment des fichiers sauvegardes
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * file_system_path.c
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
 *
 * This file is part of Csuper.
 *
 * Csuper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper is distributed in the hope that it will be useful,
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

 #include "file_system_path.h"

/*!
 * \fn void createFileSystemPath()
 *  Cree le dossier et le fichier qui va contenir les preferences
 * \return TRUE si tout s'est bien passe, FALSE sinon
 */
int createFileSystemPath()
{
    char folder[SIZE_MAX_FILE_NAME];
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    /*Lecture du chemin Document et creation du dossier au bonne endroit et de la chaine qui va contenir le fichier*/
    #ifdef __unix__
    strcpy(folder,getenv("HOME"));
    #elif _WIN32
    strcpy(folder,getenv("USERPROFILE"));
    #endif
    sprintf(folder,"%s/%s",folder,MAIN_FOLDER_NAME);
    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif

    sprintf(file_name,"%s/%s",folder,FILE_NAME_SYSTEM_PATH);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return FALSE;

    /*Ecrit le folder courant comme folder par defaut*/
    fprintf(ptr_file,"%s",folder);

    closeFile(ptr_file);

    return TRUE;
}

/*!
 * \fn int readFileSystemPath(char *file_name)
 *  lis les preferences du fichier et ajoute le chemin lu dans le nom de fichier passe en parametre
 * \param[in,out] *file_name le nom du fichier a qui on va ajouter son chemin
 * \return TRUE si tout s'est bien passe, FALSE sinon
 */
int readFileSystemPath(char *file_name)
{
    char file_name_preferences[SIZE_MAX_FILE_NAME];
    char folder[SIZE_MAX_FILE_NAME];
    int file_size;
    FILE *ptr_file;

    /*Lecture du chemin Document et creation du nom de fichier du fichier preferences*/
    #ifdef __unix__
    strcpy(file_name_preferences,getenv("HOME"));
    #elif _WIN32
    strcpy(file_name_preferences,getenv("USERPROFILE"));
    #endif
    sprintf(file_name_preferences,"%s/%s/%s",file_name_preferences,MAIN_FOLDER_NAME,FILE_NAME_SYSTEM_PATH);

    ptr_file=openFile(file_name_preferences,"r");

    if(ptr_file == NULL)
        return FALSE;

    /*Lis le folder contenue dans le fichier*/
    file_size=readFileSize(ptr_file);
    fgets(folder,file_size+1,ptr_file);

    /*Ajoute le folder lu au nom de fichier*/
    #ifdef __unix__
    sprintf(folder,"%s/%s",folder,file_name);
    #elif _WIN32
    sprintf(folder,"%s\\%s",folder,file_name);
    #endif

    strcpy(file_name,folder);

    closeFile(ptr_file);

    return TRUE;
}

/*!
 * \fn int readSystemPath(char *file_name)
 *  Ajoute le chemin du fichier dans le nom du fichier a partir des preferences, si le fichier de preference n'existe
 *  pas il le cree
 *  Attention ne fait quelque chose uniquement si la constant PORTABLE n'est pas defini
 * \param[in,out] *file_name le nom du fichier a qui on va ajouter son chemin
 * \return TRUE si tout s'est bien passe, FALSE sinon
 */
int readSystemPath(char *file_name)
{
    #ifndef PORTABLE
    libcsuper_initialize();

    if (readFileSystemPath(file_name)==FALSE)
    {
        if(createFileSystemPath()==FALSE)
        {
            printf("\nErreur lors de la lecture du fichier de preferences.\n");
            return FALSE;
        }
        if (readFileSystemPath(file_name)==FALSE)
        {
            printf("\nErreur lors de la lecture du fichier de preferences.\n");
            return FALSE;
        }
    }
    #endif
    return TRUE;
}

/*!
 * \fn int changeSystemPath(char *new_path)
 *  Changer le chemin de sauvegarde des fichier par new_path
 * \param[in,out] *new_path le nomveau chemin
 * \return TRUE si tout s'est bien passe, FALSE sinon
 */
int changeSystemPath(char *new_path)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    if (createFileSystemPath()==FALSE)
        return FALSE;


    /*Lecture du chemin Document et cree la chaine qui va contenir le nom du fichier*/
    #ifdef __unix__
    strcpy(file_name,getenv("HOME"));
    #elif _WIN32
    strcpy(file_name,getenv("USERPROFILE"));
    #endif

    sprintf(file_name,"%s/%s/%s",file_name,MAIN_FOLDER_NAME,FILE_NAME_SYSTEM_PATH);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return FALSE;

    fprintf(ptr_file,"%s",new_path);

    closeFile(ptr_file);

    return TRUE;
}
