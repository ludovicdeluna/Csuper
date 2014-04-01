/*!
 * \file    saisie_clavier.c
 * \brief   Fonctions de saisie clavier
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * saisie_clavier.c
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

 #include "saisie_clavier.h"

 /*!
 * \fn void clean_stdin(void)
 *  Vide la cache de stdin.
 */
void clean_stdin(void)
{
    int c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

/*!
 * \fn char *saisieClavierChaine(char *chaine, int nb_caract_plus_un)
 *  Fait une saisie clavier de chaine de caractere au claver dans chaine sur nb-caract_plus_un moins 1 caractere
 * \param[in,out] *chaine une chaine de caractere
 * \param[in] nb_caract_plus_un le nombre de caractere moins un que la fonction va lire
 */
char *saisieClavierChaine(char *chaine, int nb_caract_plus_un)
{
    char *p;

    /*Recuperation de la chaine de caractere au clavier*/
    chaine=fgets(chaine,nb_caract_plus_un,stdin);

    /*Recerche du caractere de saut de ligne*/
    p = strchr(chaine, '\n');

    /*Si on a trouve le saut de ligne, on l'enleve*/
    if (p)
    {
        *p = 0;
    }

    /*Sinon on vide la cache de stdin*/
    else
    {
        clean_stdin();
    }

    return chaine;
}

/*!
 * \fn void *saisieClavierEntier(int *nb)
 *  Fait une saisie clavier d'un entier, met 0 si l'entree n'est pas un chiffre.
 * \param[in,out] *nb le nombre que l'on veut saisir.
 */
void saisieClavierEntier(int *nb)
{
    char chaine[NB_CARACT_INT];

    /*On recupere la chaine de caractere contenant le nombre*/
    saisieClavierChaine(chaine,NB_CARACT_INT);

    *nb=0;

    /*On convertit la chaine de caractere en entier*/
    sscanf(chaine,"%d",nb);
}

/*!
 * \fn void saisieClavierFlottant(float *nb)
 *  Fait une saisie clavier d'un flottant, met 0 si l'entree n'est pas un chiffre.
 * \param[in,out] *nb le nombre que l'on veut saisir.
 */
void saisieClavierFlottant(float *nb)
{
    char chaine[NB_CARACT_FLOT];

    /*On recupere la chaine de caractere contenant le nombre*/
    saisieClavierChaine(chaine,NB_CARACT_FLOT);

    *nb=0;

    /*On convertit la chaine de caractere en flottant*/
    sscanf(chaine,"%f",nb);
}

/*!
 * \fn void saisieClavierFlottantSansVirgule(float *nb)
 *  Fait une saisie clavier d'un flottant sans virgule, met 0 si l'entree n'est pas un chiffre.
 * \param[in,out] *nb le nombre que l'on veut saisir.
 */
void saisieClavierFlottantSansVirgule(float *nb)
{
    char chaine[NB_CARACT_FLOT];
    char *p;

    /*On recupere la chaine de caractere contenant le nombre*/
    saisieClavierChaine(chaine,NB_CARACT_FLOT);

    /*Recerche du caractere .*/
    p = strchr(chaine, '.');

    /*Si on a trouve le . , on l'enleve*/
    if (p)
    {
        *p = '\0';
    }

    *nb=0;

    /*On convertit la chaine de caractere en flottant*/
    sscanf(chaine,"%f",nb);
}

/*!
 * \fn void saisieClavierDouble(double *nb)
 *  Fait une saisie clavier d'un double, met 0 si l'entree n'est pas un chiffre.
 * \param[in,out] *nb le nombre que l'on veut saisir.
 */
void saisieClavierDouble(double *nb)
{
    char chaine[NB_CARACT_DOUB];

    /*On recupere la chaine de caractere contenant le nombre*/
    saisieClavierChaine(chaine,NB_CARACT_DOUB);

    *nb=0;

    /*On convertit la chaine de caractere en flottant*/
    sscanf(chaine,"%lf",nb);
}

/*!
 * \fn char *saisieClavierCaractere(char *c)
 *  Fait une saisie clavier d'un caractere.
 * \param[in,out] *c le caractere que l'on veut saisir
 */
char *saisieClavierCaractere(char *c)
{
    char chaine[2];

    /*On recupere la chaine de caractere contenant le caractere suivi de \0*/
    fgets(chaine,2,stdin);

    /*On recupere le premier caractere de la chaine dans c*/
    *c=chaine[0];

    /*Vide le tampon de stdin s'il n'est pas vide, c'est a dire si le caractere lu n'est pas un saut a la ligne*/
    if (*c != '\n')
    {
        clean_stdin();
    }

    return c;
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
