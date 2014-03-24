/*!
 * \file    fonction.c
 * \brief   Fonctions essentielles au fonctionnement du programme
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * fonction.c
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

 #include "fonction.h"
 #include "fichier.h"


/*!
 * \fn void mauvais_choix()
 *  Affiche un message d'erreur.
 */
void mauvais_choix()
{
    printf("\nErreur : vous n'avez pas entre une bonne valeur.\n");
}


/*!
 * \fn void systemPause()
 *  Demande a l'utilisateur d'appuyer sur entrer pour continuer le programme.
 */
void systemPause()
{
    char a;

    printf("\nAppuyer sur entrer pour continuer");
    saisieClavierCaractere(&a);
}

/*!
 * \fn void systemEfface()
 *  Efface la console de l'utilisateur.
 */
void systemEfface()
{
    int reussi;

    /*Lancement de la fonction d'effacage de l'ecrn*/
    #ifdef __unix__
    reussi=system("clear");
    #elif _WIN32
    reussi=system("cls");
    #endif

    /*Verifie si l'ecran s'est bien effacer*/
    if (reussi != 0)
        printf("\nErreur lors de l'effacage de la console.\n");
}



/*!
 * \fn int compareFlottantCroissant(void const *a, void const *b)
 *  Compare 2 Flottant, renvoie 1 si a>b, 0 si a=b et -1 si a<b
 * \param[in] *a un pointeur sur un flottant
 * \param[in] *b un pointeur sur un flottant
 */
int compareFlottantCroissant(void const *a, void const *b)
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
 * \fn int int compareFlottantDecroissant(void const *a, void const *b)
 *  Compare 2 Flottant, renvoie 1 si a<b, 0 si a=b et -1 si a>b
 * \param[in] *a un pointeur sur un flottant
 * \param[in] *b un pointeur sur un flottant
 */
int compareFlottantDecroissant(void const *a, void const *b)
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
 * \fn FILE *ouvrirFichier(char nom[], char mode[])
 *  Ouvre un fichier a partir de son nom (nom[]) et du mode voulu (mode[])
 * \param[in] nom[] le nom du fichier
 * \param[in] mode[] le mode voulu
 * \return un pointeur sur le fichier ouvert, NULL s'il y a eut un probleme
 */
FILE *ouvrirFichier(char nom[], char mode[])
{
    FILE *ptr_fichier;

    if ((ptr_fichier=fopen(nom,mode)) == (FILE *) NULL )
    {
        printf("\nErreur lors de l'ouverture du fichier %s\n",nom);
        perror("");
    }
    return ptr_fichier;
}

/*!
 * \fn int fermerFichier(FILE *ptr_fichier)
 *  Ferme le fichier
 * \param[in] *ptr_fichier le fichier
 * \return entier 0 si tout s'est bien passe, 1 sinon
 */
int fermerFichier(FILE *ptr_fichier)
{
    int i;

    i=fclose(ptr_fichier);
    if (i)
    {
        printf("Erreur lors de la fermeture du fichier");
        perror("");
    }

    return i;
}

/*!
 * \fn int lireTailleFichier(FILE *ptr_fichier)
 *  Lis la taille du fichier
 * \param[in] *ptr_fichier le fichier
 * \return entier ayant la taille du fichier
 */
int lireTailleFichier(FILE *ptr_fichier)
{
    int taille;
    int position=ftell(ptr_fichier);

    fseek(ptr_fichier,0,SEEK_END);
    taille=ftell(ptr_fichier);
    fseek(ptr_fichier,position,SEEK_SET);

    return taille;
}

/*!
 * \fn void *myAlloc(int taille_alloue)
 *  Alloue un bloc memoire et verifie que ca s'est bien alloue
 * \param[in] taille_alloue la taille à allouer
 * \return un pointeur sur la structure alloué
 */
void *myAlloc(int taille_alloue)
{
    void *ptr;
    if ((ptr=malloc(taille_alloue)) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }
    return ptr;
}

/*!
 * \fn void myRealloc(void *ptr,int taille_alloue)
 *  Realloue un bloc memoire et verifie que ca s'est bien alloue
 * \param[in] taille_alloue la taille à allouer
 * \param[in] ptr le pointeur sur quoi ca doit etre realloue
 */
void myRealloc(void **ptr,int taille_alloue)
{
    if ((*ptr=realloc(*ptr,taille_alloue)) == NULL)
    {
        printf("\nProbleme reallocation memoire\n");
        perror("");
        exit(0);
    }
}

/*!
 * \fn void ajoutExtension(char *nom_fichier)
 *  Ajoute l'extension du fichier si elle n'y est pas
 * \param[in] nom_fichier le nom de fichier
 */
void ajoutExtension(char *nom_fichier)
{
    char jeu[4]=EXTENSION_FICHIER;
    char ext[4]="abc";
    int i;

    /*Lecture de l'extension du fichier*/
    for (i=strlen(nom_fichier)-3 ; i<strlen(nom_fichier) ; i++)
            ext[-strlen(nom_fichier)+i+3]=nom_fichier[i];

    /*Ajout de l'extension au nom de fichier si elle n'y est pas*/
    if (strcmp(jeu,ext)!=0)
        sprintf(nom_fichier,"%s.%s",nom_fichier,EXTENSION_FICHIER);
}
