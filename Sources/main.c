/*!
 * \file    main.c
 * \brief   Lancement du programme
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

/*
 * main.c
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

#include "main.h"

/*!
 * \fn int main(int argc, char *argv[])
 *  Lance le programme
 * \return 0 si tout s'est bien passe
 */
int main(int argc, char *argv[])
{
    #ifdef PORTABLE
    afficherLicense();
    systemPause();
    #endif
    if (argc == 2)
        chargerPartieLocale(argv[1]);
    else
    {
        if (argc >= 3)
        {
            if (strcmp(argv[1],LECTURE_FICHIER)==0)
                afficheFichierLocale(argv[2]);
            else if (strcmp(argv[2],LECTURE_FICHIER)==0)
                afficheFichierLocale(argv[1]);
            else if (strcmp(argv[1],OUVERTURE_FICHIER)==0)
                chargerPartieLocale(argv[2]);
            else if (strcmp(argv[2],OUVERTURE_FICHIER)==0)
                chargerPartieLocale(argv[1]);
            else
                printf("Vous n'avez pas entre une bonne commande.\nLes options sont %s et %s avec le nom du fichier.\n",LECTURE_FICHIER,OUVERTURE_FICHIER);
        }
        else
            menuPrincipal();
    }
    return 0;
}

