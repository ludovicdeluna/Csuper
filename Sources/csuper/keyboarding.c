/*!
 * \file    keyboarding.c
 * \brief   Fonctions de saisie clavier
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * keyboarding.c
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

 #include "keyboarding.h"

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
 * \fn char *stringKey(char *string, int nb_char_plus_one)
 *  Fait une saisie clavier de string de caractere au claver dans string sur nb-caract_plus_un moins 1 caractere
 * \param[in,out] *string une string de caractere
 * \param[in] nb_char_plus_one le nombre de caractere moins un que la fonction va lire
 */
char *stringKey(char *string, int nb_char_plus_one)
{
    char *p;

    /*Recuperation de la string de caractere au clavier*/
    string=fgets(string,nb_char_plus_one,stdin);

    /*Recerche du caractere de saut de ligne*/
    p = strchr(string, '\n');

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

    return string;
}

/*!
 * \fn void *intKey(int *nb)
 *  Fait une saisie clavier d'un entier, met 0 si l'entree n'est pas un chiffre.
 * \param[in,out] *nb le nombre que l'on veut saisir.
 */
void intKey(int *nb)
{
    char string[NB_CARACT_INT];

    /*On recupere la string de caractere contenant le nombre*/
    stringKey(string,NB_CARACT_INT);

    *nb=0;

    /*On convertit la string de caractere en entier*/
    sscanf(string,"%d",nb);
}

/*!
 * \fn void floatKey(float *nb)
 *  Fait une saisie clavier d'un flottant, met 0 si l'entree n'est pas un chiffre.
 * \param[in,out] *nb le nombre que l'on veut saisir.
 */
void floatKey(float *nb)
{
    char string[NB_CARACT_FLOAT];

    /*On recupere la string de caractere contenant le nombre*/
    stringKey(string,NB_CARACT_FLOAT);

    *nb=0;

    /*On convertit la string de caractere en flottant*/
    sscanf(string,"%f",nb);
}

/*!
 * \fn void floatKeyNoComma(float *nb)
 *  Fait une saisie clavier d'un flottant sans virgule, met 0 si l'entree n'est pas un chiffre.
 * \param[in,out] *nb le nombre que l'on veut saisir.
 */
void floatKeyNoComma(float *nb)
{
    char string[NB_CARACT_FLOAT];
    char *p;

    /*On recupere la string de caractere contenant le nombre*/
    stringKey(string,NB_CARACT_FLOAT);

    /*Recerche du caractere .*/
    p = strchr(string, '.');

    /*Si on a trouve le . , on l'enleve*/
    if (p)
    {
        *p = '\0';
    }

    *nb=0;

    /*On convertit la string de caractere en flottant*/
    sscanf(string,"%f",nb);
}

/*!
 * \fn void doubleKey(double *nb)
 *  Fait une saisie clavier d'un double, met 0 si l'entree n'est pas un chiffre.
 * \param[in,out] *nb le nombre que l'on veut saisir.
 */
void doubleKey(double *nb)
{
    char string[NB_CARACT_DOUB];

    /*On recupere la string de caractere contenant le nombre*/
    stringKey(string,NB_CARACT_DOUB);

    *nb=0;

    /*On convertit la string de caractere en flottant*/
    sscanf(string,"%lf",nb);
}

/*!
 * \fn char *charKey(char *c)
 *  Fait une saisie clavier d'un caractere.
 * \param[in,out] *c le caractere que l'on veut saisir
 */
char *charKey(char *c)
{
    char string[2];

    /*On recupere la string de caractere contenant le caractere suivi de \0*/
    fgets(string,2,stdin);

    /*On recupere le premier caractere de la string dans c*/
    *c=string[0];

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

    printf(_("\nPress enter to continue"));
    charKey(&a);
}
