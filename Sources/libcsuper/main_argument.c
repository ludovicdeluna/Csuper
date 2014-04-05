/*!
 * \file    main_argument.c
 * \brief   Lancement du programme
 * \author  Remi BERTHO
 * \date    21/03/14
 * \version 2.1.0
 */

/*
 * main_argument.c
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
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include "main_argument.h"

/*!
 * \fn int searchArgument(int argc, char *argv[], int *fonction, int *emplacement_fichier)
 *  Lance le programme
 * \param[in] argc le nombre d 'argument
 * \param[in] argv le tableau des arguments
 * \param[in] fonction entier determinant quelle fonction lancer
 * \param[in] emplacement_fichier entier donnant l'emplacment du fichier a ouvrir
 * \return VRAI si la fonction a trouve un argument, FAUX sinon
 */
int searchArgument(int argc, char *argv[], int *fonction, int *emplacement_fichier)
{
    int i;

    for (i=1 ; i< argc ; i++)
    {
        if (strcmp(argv[i],CHAINE_LECTURE_FICHIER)==0 || strcmp(argv[i],CHAINE_LECTURE_FICHIER_RED)==0)
        {
            *fonction = LECTURE_FICHIER;
            *emplacement_fichier = 1+i;
            break;
        }
        if (strcmp(argv[i],CHAINE_OUVERTURE_FICHIER)==0 || strcmp(argv[i],CHAINE_OUVERTURE_FICHIER_RED)==0)
        {
            *fonction = OUVERTURE_FICHIER;
            *emplacement_fichier = 1+i;
            break;
        }
        if (strcmp(argv[i],STRING_HELP)==0 || strcmp(argv[i],STRING_HELP_RED)==0)
        {
            displayHelp();
            *fonction=HELP;
            *emplacement_fichier = i;
            break;
        }
    }

    if (i == argc || *emplacement_fichier >= argc)
        return FAUX;
    else
        return VRAI;
}

void displayHelp()
{
    printf("\nCsuper - Compteur de Score Universel Permettant l'Exemption de Reflexion\nVoici la syntaxe pour l'utiliser.\n");
    printf("\t- N'utiliser pas d'argument pour lancer le programme sur le menu.\n");
    printf("\t- Utiliser l'option '%s' ou '%s' suivi du nom de fichier pour lancer le jeu directement sur ce fichier.\n",CHAINE_OUVERTURE_FICHIER,CHAINE_OUVERTURE_FICHIER_RED);
    printf("\t- Utiliser l'option '%s' ou '%s' suivi du nom de fichier pour afficher directement le contenu du fichier.\n",CHAINE_LECTURE_FICHIER,CHAINE_LECTURE_FICHIER_RED);
}
