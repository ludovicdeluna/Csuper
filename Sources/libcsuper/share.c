/*!
 * \file    share.c
 * \brief   Essential function of libcsuper
 * \author  Remi BERTHO
 * \date    05/07/14
 * \version 4.0.1
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
    static char initialized=false;
    if (initialized == false)
    {
        bindtextdomain("libcsuper","./Locales");
        initialized = true;
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

