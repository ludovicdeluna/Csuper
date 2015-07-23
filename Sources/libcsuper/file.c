/*!
 * \file    file.c
 * \brief   Files function of libcsuper
 * \author  Remi BERTHO
 * \date    05/07/14
 * \version 4.0.1
 */

 /*
 * file.c
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

 #include "file.h"

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
 * \fn bool deleteFile(char *file_name)
 *  Delete a file
 * \param[in] *file_name the filename
 * \return true if everything is OK, false otherwise
 */
bool deleteFile(char *file_name)
{
    libcsuper_initialize();

    if(remove(file_name))
    {
        printf(_("\nThe file %s cannot be deleted.\n"),file_name);
        perror("");
        return false;
    }

    else
    {
        printf(_("\nThe file %s was deleted successfully.\n"),file_name);
        return true;
    }
}

/*!
 * \fn bool renameFile(char *old_name, char *new_name)
 *  Rename a file.
 * \param[in] *old_name the old name of the file
 * \param[in] *new_name the new name of the file
 * \return true if everything is OK, false otherwise
 */
bool renameFile(char *old_name, char *new_name)
{
    libcsuper_initialize();

    if(rename(old_name,new_name))
    {
        printf(_("\nThe file %s cannot be renamed.\n"),old_name);
        return false;
    }

    else
    {
        printf(_("\nThe file %s was well renamed in %s.\n"),old_name,new_name);
        return true;
    }
}
