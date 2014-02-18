/*!
 * \file    emplacement_fichier.c
 * \brief   Fonctions qui l'emplacement des fichiers sauvegardes
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * emplacement_fichier.c
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

 #include "emplacement_fichier.h"

/*!
 * \fn void creationPreferences()
 *  Cree le dossier et le fichier qui va contenir les preferences
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int creationPreferences()
{
    char repertoire[TAILLE_MAX_NOM_FICHIER];
    char nom_fichier[TAILLE_MAX_NOM_FICHIER];
    FILE *ptr_fichier;

    /*Lecture du chemin Document et creation du dossier au bonne endroit et de la chaine qui va contenir le fichier*/
    #ifdef __unix__
    strcpy(repertoire,getenv("HOME"));
    sprintf(repertoire,"%s/%s",repertoire,NOM_DOSSIER);
    mkdir(repertoire, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    sprintf(nom_fichier,"%s/%s",repertoire,NOM_FICHIER);
    #elif _WIN32
    strcpy(repertoire,getenv("USERPROFILE"));
    sprintf(repertoire,"%s\\%s",repertoire,NOM_DOSSIER);
    mkdir(repertoire);
    sprintf(nom_fichier,"%s\\%s",repertoire,NOM_FICHIER);
    #endif

    ptr_fichier=ouvrirFichier(nom_fichier,"w+");

    if (ptr_fichier==NULL)
        return FAUX;

    /*Ecrit le repertoire courant comme repertoire par defaut*/
    fprintf(ptr_fichier,"%s",repertoire);

    fermerFichier(ptr_fichier);

    return VRAI;
}

/*!
 * \fn int lecturePreferences(char *nom_fichier)
 *  lis les preferences du fichier et ajoute le chemin lu dans le nom de fichier passe en parametre
 * \param[in,out] *nom_fichier le nom du fichier a qui on va ajouter son chemin
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int lecturePreferences(char *nom_fichier)
{
    char nom_fichier_preferences[TAILLE_MAX_NOM_FICHIER];
    char repertoire[TAILLE_MAX_NOM_FICHIER];
    int taille_fichier_preferences;
    FILE *ptr_fichier;

    /*Lecture du chemin Document et creation du nom de fichier du fichier preferences*/
    #ifdef __unix__
    strcpy(nom_fichier_preferences,getenv("HOME"));
    sprintf(nom_fichier_preferences,"%s/%s/%s",nom_fichier_preferences,NOM_DOSSIER,NOM_FICHIER);
    #elif _WIN32
    strcpy(nom_fichier_preferences,getenv("USERPROFILE"));
    sprintf(nom_fichier_preferences,"%s\\%s\\%s",nom_fichier_preferences,NOM_DOSSIER,NOM_FICHIER);
    #endif

    ptr_fichier=ouvrirFichier(nom_fichier_preferences,"r");

    if(ptr_fichier == NULL)
        return FAUX;

    /*Lis le repertoire contenue dans le fichier*/
    taille_fichier_preferences=lireTailleFichier(ptr_fichier);
    fgets(repertoire,taille_fichier_preferences+1,ptr_fichier);

    /*Ajoute le repertoire lu au nom de fichier*/
    #ifdef __unix__
    sprintf(repertoire,"%s/%s",repertoire,nom_fichier);
    #elif _WIN32
    sprintf(repertoire,"%s\\%s",repertoire,nom_fichier);
    #endif

    strcpy(nom_fichier,repertoire);

    fermerFichier(ptr_fichier);

    return VRAI;
}

/*!
 * \fn int lectureCheminFichier(char *nom_fichier)
 *  Ajoute le chemin du fichier dans le nom du fichier a partir des preferences, si le fichier de preference n'existe
 *  pas il le cree
 *  Attention ne fait quelque chose uniquement si la constant PORTABLE n'est pas defini
 * \param[in,out] *nom_fichier le nom du fichier a qui on va ajouter son chemin
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int lectureCheminFichier(char *nom_fichier)
{
    #ifndef PORTABLE
    if (lecturePreferences(nom_fichier)==FAUX)
    {
        if(creationPreferences()==FAUX)
        {
            printf("\nErreur lors de la lecture du fichier de preferences.\n");
            return FAUX;
        }
        if (lecturePreferences(nom_fichier)==FAUX)
        {
            printf("\nErreur lors de la lecture du fichier de preferences.\n");
            return FAUX;
        }
    }
    #endif
    return VRAI;
}

/*!
 * \fn int changerCheminFichier(char *nouveauChemin)
 *  Changer le chemin de sauvegarde des fichier par nouveauChemin
 * \param[in,out] *nouveauChemin le nomveau chemin
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int changerCheminFichier(char *nouveauChemin)
{
    char nom_fichier[TAILLE_MAX_NOM_FICHIER];
    FILE *ptr_fichier;

    if (creationPreferences()==FAUX)
        return FAUX;


    /*Lecture du chemin Document et cree la chaine qui va contenir le nom du fichier*/
    #ifdef __unix__
    strcpy(nom_fichier,getenv("HOME"));
    sprintf(nom_fichier,"%s/%s/%s",nom_fichier,NOM_DOSSIER,NOM_FICHIER);
    #elif _WIN32
    strcpy(nom_fichier,getenv("USERPROFILE"));
    sprintf(nom_fichier,"%s\\%s\\%s",nom_fichier,NOM_DOSSIER,NOM_FICHIER);
    #endif

    ptr_fichier=ouvrirFichier(nom_fichier,"w+");

    if (ptr_fichier==NULL)
        return FAUX;

    fprintf(ptr_fichier,"%s",nouveauChemin);

    fermerFichier(ptr_fichier);

    return VRAI;
}
