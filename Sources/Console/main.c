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
 * \param[in] argc le nombre d 'argument
 * \param[in] argv le tableau des arguments
 * \return 0 si tout s'est bien passe
 */
int main(int argc, char *argv[])
{
    int fonction;
    int emplacement_fichier;
    #ifdef PORTABLE
    afficherLicense();
    systemPause();
    #endif
    if (argc == 2)
        chargerPartieLocale(argv[1]);
    else
    {
        if (argc >= 3 && searchArgument(argc,argv,&fonction,&emplacement_fichier))
        {
            if (fonction == LECTURE_FICHIER)
                afficheFichierLocale(argv[emplacement_fichier]);
            else if (fonction == OUVERTURE_FICHIER)
                chargerPartieLocale(argv[emplacement_fichier]);
        }
        else
            menuPrincipal();
    }
    return 0;
}

