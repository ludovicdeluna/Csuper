/*!
 * \file    share.c
 * \brief   Fonctions essentielles au fonctionnement du programme
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * share.c
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

#include "share.h"
#include "csu_files.h"

/*!
 * \fn void libcsuper_initialize()
 *  Initialize libcsuper with gettext.
 */
void libcsuper_initialize()
{
    static char initialized=FALSE;
    if (initialized == FALSE)
    {
        bindtextdomain("libcsuper","./Locales");
        initialized = TRUE;
    }
}

/*!
 * \fn void wrongChoice()
 *  Affiche un message d'erreur.
 */
void wrongChoice()
{
    libcsuper_initialize();
    printf(_("\nError: you didn't enter a good value.\n"));
}


/*!
 * \fn void clearScreen()
 *  Efface la console de l'utilisateur.
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
        printf("\nErreur lors de l'effacage de la console.\n");
}



/*!
 * \fn int compareFloatAscending(void const *a, void const *b)
 *  Compare 2 Flottant, renvoie 1 si a>b, 0 si a=b et -1 si a<b
 * \param[in] *a un pointeur sur un flottant
 * \param[in] *b un pointeur sur un flottant
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
 *  Compare 2 Flottant, renvoie 1 si a<b, 0 si a=b et -1 si a>b
 * \param[in] *a un pointeur sur un flottant
 * \param[in] *b un pointeur sur un flottant
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
 *  Ouvre un fichier a partir de son nom (nom[]) et du mode voulu (mode[])
 * \param[in] file_name[] le nom du fichier
 * \param[in] mode[] le mode voulu
 * \return un pointeur sur le fichier ouvert, NULL s'il y a eut un probleme
 */
FILE *openFile(char file_name[], char mode[])
{
    FILE *ptr_file;

    libcsuper_initialize();

    if ((ptr_file=fopen(file_name,mode)) == (FILE *) NULL )
    {
        printf("\nErreur lors de l'ouverture du fichier %s\n",file_name);
        perror("");
    }
    return ptr_file;
}

/*!
 * \fn int closeFile(FILE *ptr_file)
 *  Ferme le fichier
 * \param[in] *ptr_file le fichier
 * \return entier 0 si tout s'est bien passe, 1 sinon
 */
int closeFile(FILE *ptr_file)
{
    int i;

    libcsuper_initialize();

    i=fclose(ptr_file);
    if (i)
    {
        printf("Erreur lors de la fermeture du fichier");
        perror("");
    }

    return i;
}

/*!
 * \fn int readFileSize(FILE *ptr_file)
 *  Lis la size du fichier
 * \param[in] *ptr_file le fichier
 * \return entier ayant la size du fichier
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
 *  Alloue un bloc memoire et verifie que ca s'est bien alloue
 * \param[in] size_alloue la size à allouer
 * \return un pointeur sur la structure alloué
 */
void *myAlloc(int size_alloue)
{
    void *ptr;

    libcsuper_initialize();

    if ((ptr=malloc(size_alloue)) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }
    return ptr;
}

/*!
 * \fn void myRealloc(void *ptr,int size_alloue)
 *  Realloue un bloc memoire et verifie que ca s'est bien alloue
 * \param[in] size_alloue la size à allouer
 * \param[in] ptr le pointeur sur quoi ca doit etre realloue
 */
void myRealloc(void **ptr,int size_alloue)
{
    libcsuper_initialize();

    if ((*ptr=realloc(*ptr,size_alloue)) == NULL)
    {
        printf("\nProbleme reallocation memoire\n");
        perror("");
        exit(0);
    }
}

/*!
 * \fn void addFileCsuExtension(char *file_name)
 *  Ajoute l'extension du fichier si elle n'y est pas
 * \param[in] file_name le nom de fichier
 */
void addFileCsuExtension(char *file_name)
{
    char file_extension[4]=FILE_EXTENSION;
    char ext[4]="abc";
    int i;

    /*Lecture de l'extension du fichier*/
    for (i=strlen(file_name)-3 ; i<strlen(file_name) ; i++)
            ext[-strlen(file_name)+i+3]=file_name[i];

    /*Ajout de l'extension au nom de fichier si elle n'y est pas*/
    if (strcmp(file_extension,ext)!=0)
        sprintf(file_name,"%s.%s",file_name,FILE_EXTENSION);
}
