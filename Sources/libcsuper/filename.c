/*!
 * \file    filename.c
 * \brief   Essential function of libcsuper
 * \author  Remi BERTHO
 * \date    22/12/14
 * \version 4.1.0
 */

 /*
 * filename.c
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
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

 #include "filename.h"

/*!
 * \fn void addFileCsuExtension(char *file_name)
 *  Add the csu file extension
 * \param[in] file_name the filename
 */
void addFileCsuExtension(char *file_name)
{
    char ext[4]="abc";
    unsigned int i;

    /*Read the extension of the file*/
    for (i=strlen(file_name)-3 ; i<strlen(file_name) ; i++)
            ext[-strlen(file_name)+i+3]=file_name[i];

    /*Add the csu extension if it is not there*/
    if (strcmp(FILE_EXTENSION_CSU,ext)!=0)
        sprintf(file_name,"%s.%s",file_name,FILE_EXTENSION_CSU);
}

/*!
 * \fn void addFilePdfExtension(char *file_name)
 *  Add the pdf file extension
 * \param[in] file_name the filename
 */
void addFilePdfExtension(char *file_name)
{
    char ext[4]="abc";
    unsigned int i;

    /*Read the extension of the file*/
    for (i=strlen(file_name)-3 ; i<strlen(file_name) ; i++)
            ext[-strlen(file_name)+i+3]=file_name[i];

    /*Add the csu extension if it is not there*/
    if (strcmp("pdf",ext)!=0)
        sprintf(file_name,"%s.%s",file_name,"pdf");
}


/*!
 * \fn void addFileCsvExtension(char *file_name)
 *  Add the csv file extension
 * \param[in] file_name the filename
 */
void addFileCsvExtension(char *file_name)
{
    char ext[4]="abc";
    unsigned int i;

    /*Read the extension of the file*/
    for (i=strlen(file_name)-3 ; i<strlen(file_name) ; i++)
            ext[-strlen(file_name)+i+3]=file_name[i];

    /*Add the csu extension if it is not there*/
    if (strcmp("csv",ext)!=0)
        sprintf(file_name,"%s.%s",file_name,"csv");
}

/*!
 * \fn void removeFileExtension(char *file_name)
 *  Remove the file extension file extension
 * \param[in] file_name the filename
 */
void removeFileExtension(char *file_name)
{
    if (file_name[strlen(file_name)-4] == '.')
        file_name[strlen(file_name)-4]='\0';
}


/*!
 * \fn bool getFolderFromFilename(char *file_name_to_folder)
 *  Transform a filename into his folder
 * \param[in] file_name_to_folder the filename
 * \return true if everything is OK, false otherwise
 */
bool getFolderFromFilename(char *file_name_to_folder)
{
    int i;
    bool ok = false;
    for (i=strlen(file_name_to_folder) ; i>=0 ; i--)
    {
        #ifdef _WIN32
        if (file_name_to_folder[i] == '\\' || file_name_to_folder[i] == '/')
        #else
        if (file_name_to_folder[i] == '/')
        #endif // _WIN32
        {
            ok = true;
            #ifdef _WIN32
            if (i==2 && strlen(file_name_to_folder) > i)
                file_name_to_folder[3] = '\0';
            else
                file_name_to_folder[i] = '\0';
            #else
            file_name_to_folder[i] = '\0';
            #endif // _WIN32
            break;
        }
    }

    return ok;
}

/*!
 * \fn bool getSimpleFilenameFromFullFilename(char *full_filename,char *simple_filename)
 *  Transform a full filename into his simple filename (without the folder)
 * \param[in] full_filename the full filename
 * \param[in] simple_filename the full filename
 * \return true if everything is OK, false otherwise
 */
bool getSimpleFilenameFromFullFilename(char *full_filename,char *simple_filename)
{
    int i;
    bool ok = false;
    strcpy(simple_filename,full_filename);
    for (i=strlen(full_filename) ; i>=0 ; i--)
    {
        #ifdef _WIN32
        if (full_filename[i] == '/' || full_filename[i] == '\\')
        #else
        if (full_filename[i] == '/')
        #endif // _WIN32
        {
            ok = true;
            strcpy(simple_filename,full_filename+i+1);
            break;
        }
    }

    return ok;
}

/*!
 * \fn bool checkPath(char *path)
 *  Test if the path is valid
 * \param[in,out] *path the path
 * \return true if the path is valid OK, false otherwise
 */
bool checkPath(char *path)
{
    FILE *ptr_file_test=NULL;
    char check_path[SIZE_MAX_FILE_NAME]="";

    if (path == NULL)
        return false;

    if(path[strlen(path)-1] == '\\')
        sprintf(check_path,"%stest-chemin_fichier_csuper",path);
    else
        sprintf(check_path,"%s/test-chemin_fichier_csuper",path);
    ptr_file_test=openFile(check_path,"w+");
    if (ptr_file_test != NULL)
    {
        closeFile(ptr_file_test);
        remove(check_path);
        return true;
    }
    else
    {
        printf(_("\nError: this folder is not valid.\n"));
        return false;
    }
}

/*!
 * \fn bool checkFilename(char *filename,char * folder)
 *  Test if the filename is valid
 * \param[in,out] *filename the filename
 * \param[in,out] *folder the folder where the filename will be tested, may be ""
 * \return true if the filename is valid OK, false otherwise
 */
bool checkFilename(char *filename,char *folder)
{
    FILE *ptr_file_test;
    char check_filename[SIZE_MAX_FILE_NAME+10]="";

    if (folder == NULL || strcmp(folder,"") == 0)
        sprintf(check_filename,"%s_test.csu",filename);
    else
    {
        if(folder[strlen(folder)-1] == '\\')
            sprintf(check_filename,"%s%s_test.csu",folder,filename);
        else
            sprintf(check_filename,"%s/%s_test.csu",folder,filename);
    }
    ptr_file_test=openFile(check_filename,"w+");
    if (ptr_file_test != NULL)
    {
        closeFile(ptr_file_test);
        remove(check_filename);
        return true;
    }
    else
    {
        printf(_("\nError : this filename is not valid.\n"));
        return false;
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

/*!
 * \fn bool removeFilenameExtension(char *filename)
 *  Remove the file extension of the filename
 * \param[in] filename the filename
 * \return true if everything is OK, false otherwise
 */
bool removeFilenameExtension(char *filename)
{
    int i;
    bool ok = false;
    for (i=strlen(filename) ; i>=0 ; i--)
    {
        if (filename[i] == '.')
        {
            ok = true;
            filename[i] = '\0';
            break;
        }
    }

    return ok;
}
