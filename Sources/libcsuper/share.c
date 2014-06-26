/*!
 * \file    share.c
 * \brief   Essential function of libcsuper
 * \author  Remi BERTHO
 * \date    15/06/14
 * \version 4.0.0
 */

 /*
 * share.c
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

#include "share.h"
#include "csu_files.h"

/*!
 * \fn void libcsuper_initialize()
 *  Initialize libcsuper with gettext.
 */
void libcsuper_initialize()
{
    static char initialized=MY_FALSE;
    if (initialized == MY_FALSE)
    {
        bindtextdomain("libcsuper","./Locales");
        initialized = MY_TRUE;
    }
}

/*!
 * \fn void wrongChoice()
 *  Display an error message.
 */
void wrongChoice()
{
    libcsuper_initialize();
    printf(_("\nError: you didn't enter a good value.\n"));
}


/*!
 * \fn void clearScreen()
 *  Clear the terminal.
 */
void clearScreen()
{
    int successful;

    libcsuper_initialize();

    /*Lancement de la fonction d'effacage de l'ecrn*/
    #ifdef __unix__
    successful=system("clear");
    #elif _WIN32
    successful=system("cls");
    #endif

    /*Verifie si l'ecran s'est bien effacer*/
    if (successful != 0)
        printf(_("\nError while clearing the screen.\n"));
}



/*!
 * \fn int compareFloatAscending(void const *a, void const *b)
 *  Compare 2 float
 * \param[in] *a a pointer on a float
 * \param[in] *b a pointer on a float
 * \return 1 if a>b, 0 if a=b and -1 if a<b
 */
int compareFloatAscending(void const *a, void const *b)
{
   int ret = 0;
   float const *pa = a;
   float const *pb = b;
   float diff = *pa - *pb;

   if (diff > 0)
   {
      ret = 1;
   }

   else if (diff < 0)
   {
      ret = -1;
   }

   else
   {
      ret = 0;
   }

   return ret;
}

/*!
 * \fn int int compareFloatDescending(void const *a, void const *b)
 *  Compare 2 float
 * \param[in] *a a pointer on a float
 * \param[in] *b a pointer on a float
 * \return 1 if a<b, 0 if a=b and -1 if a>b
 */
int compareFloatDescending(void const *a, void const *b)
{
   int ret = 0;
   float const *pa = a;
   float const *pb = b;
   float diff = *pa - *pb;

   if (diff > 0)
   {
      ret = -1;
   }

   else if (diff < 0)
   {
      ret = 1;
   }

   else
   {
      ret = 0;
   }

   return ret;
}

/*!
 * \fn FILE *openFile(char file_name[], char mode[])
 *  Open a file with his name and with a specific mode.
 * \param[in] file_name[] the filename
 * \param[in] mode[] the mode
 * \return a pointer to the open file, NULL if there was a problem
 */
FILE *openFile(char file_name[], char mode[])
{
    FILE *ptr_file;
    libcsuper_initialize();

    if ((ptr_file=fopen(file_name,mode)) == (FILE *) NULL )
    {
        printf(_("\nError while opening %s\n"),file_name);
        perror("");
    }
    return ptr_file;
}

/*!
 * \fn int closeFile(FILE *ptr_file)
 *  Close the file
 * \param[in] *ptr_file the file
 * \return 0 if everything is OK, 1 otherwise
 */
int closeFile(FILE *ptr_file)
{
    int i;

    libcsuper_initialize();

    i=fclose(ptr_file);
    if (i)
    {
        printf(_("Error while closing the file"));
        perror("");
    }

    return i;
}

/*!
 * \fn int readFileSize(FILE *ptr_file)
 *  Read the size of the file
 * \param[in] *ptr_file the file
 * \return the size of the file
 */
int readFileSize(FILE *ptr_file)
{
    int size;
    int rank=ftell(ptr_file);

    fseek(ptr_file,0,SEEK_END);
    size=ftell(ptr_file);
    fseek(ptr_file,rank,SEEK_SET);

    return size;
}

/*!
 * \fn void *myAlloc(int size_alloue)
 *  Allocate a memory block and check if everything is OK.
 * \param[in] size_alloue the size
 * \return a pointer on the allocate memory block
 */
void *myAlloc(int size_alloue)
{
    void *ptr;

    libcsuper_initialize();

    if ((ptr=malloc(size_alloue)) == NULL)
    {
        printf(_("\nMemory allocation problem\n"));
        perror("");
        exit(0);
    }
    return ptr;
}

/*!
 * \fn void myRealloc(void *ptr,int size_alloue)
 *  Reallocate a memory block and check if everything is OK.
 * \param[in] size_alloue the size
 * \param[in] a pointer on the reallocate memory block
 */
void myRealloc(void **ptr,int size_alloue)
{
    libcsuper_initialize();

    if ((*ptr=realloc(*ptr,size_alloue)) == NULL)
    {
        printf(_("\nMemory allocation problem\n"));
        perror("");
        exit(0);
    }
}

/*!
 * \fn void addFileCsuExtension(char *file_name)
 *  Add the csu file extension
 * \param[in] file_name the filename
 */
void addFileCsuExtension(char *file_name)
{
    char file_extension[4]=FILE_EXTENSION;
    char ext[4]="abc";
    int i;

    /*Read the extension of the file*/
    for (i=strlen(file_name)-3 ; i<strlen(file_name) ; i++)
            ext[-strlen(file_name)+i+3]=file_name[i];

    /*Add the csu extension if it is not there*/
    if (strcmp(file_extension,ext)!=0)
        sprintf(file_name,"%s.%s",file_name,FILE_EXTENSION);
}

/*!
 * \fn int deleteFile(char *file_name)
 *  Delete a file
 * \param[in] *file_name the filename
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int deleteFile(char *file_name)
{
    libcsuper_initialize();

    if(remove(file_name))
    {
        printf(_("\nThe file %s cannot be deleted.\n"),file_name);
        perror("");
        return MY_FALSE;
    }

    else
    {
        printf(_("\nThe file %s was well deleted.\n"),file_name);
        return MY_TRUE;
    }
}

/*!
 * \fn int renameFile(char *old_name, char *new_name)
 *  Rename a file.
 * \param[in] *old_name the old name of the file
 * \param[in] *new_name the new name of the file
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int renameFile(char *old_name, char *new_name)
{
    libcsuper_initialize();

    if(rename(old_name,new_name))
    {
        printf(_("\nThe file %s cannot be renamed.\n"),old_name);
        return MY_FALSE;
    }

    else
    {
        printf(_("\nThe file %s was well renamed in %s.\n"),old_name,new_name);
        return MY_TRUE;
    }
}

/*!
 * \fn char *integerToYesNo(int i, char *yes, char *no)
 *  Transform an integer to yes or no
 * \param[in] i the integer
 * \param[in] yes the yes string
 * \param[in] no the no string
 * \return yes if i > 0, no otherwise
 */
char *integerToYesNo(int i, char *yes, char *no)
{
    if (i > 0)
        return yes;
    else
        return no;
}

/*!
 * \fn int getFolderFromFilename(char *file_name_to_folder)
 *  Transform a filename into his folder
 * \param[in] file_name_to_folder the filename
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int getFolderFromFilename(char *file_name_to_folder)
{
    int i;
    int ok = MY_FALSE;
    for (i=strlen(file_name_to_folder) ; i>=0 ; i--)
    {
        #ifdef _WIN32
        if (file_name_to_folder[i] == '\\')
        #else
        if (file_name_to_folder[i] == '/')
        #endif // _WIN32
        {
            ok = MY_TRUE;
            file_name_to_folder[i] = '\0';
            break;
        }
    }

    return ok;
}

/*!
 * \fn int getSimpleFilenameFromFullFilename(char *full_filename,char *simple_filename)
 *  Transform a full filename into his simple filename (without the folder)
 * \param[in] full_filename the full filename
 * \param[in] simple_filename the full filename
 * \return MY_TRUE if everything is OK, MY_FALSE otherwise
 */
int getSimpleFilenameFromFullFilename(char *full_filename,char *simple_filename)
{
    int i;
    int ok = MY_FALSE;
    for (i=strlen(full_filename) ; i>=0 ; i--)
    {
        if (full_filename[i] == '/')
        {
            ok = MY_TRUE;
            strcpy(simple_filename,full_filename+i+1);
            break;
        }
    }

    return ok;
}
