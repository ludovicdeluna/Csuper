/*!
 * \file    keyboarding.c
 * \brief   Function of keyboarding
 * \author  Remi BERTHO
 * \date    26/04/14
 * \version 2.2.0
 */

 /*
 * keyboarding.c
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
 *
 * This file is part of Csuper-cli.
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
 *  Clean the buffer of stdin.
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
 *  Do a keyboarding of a string with nb-char_plus_one minus 1 characters
 * \param[in,out] *string a string
 * \param[in] nb_char_plus_one the number of characters that the function will read plus one
 */
char *stringKey(char *string, int nb_char_plus_one)
{
    char *p;

    string=fgets(string,nb_char_plus_one,stdin);

    p = strchr(string, '\n');

    /*If we found the newline, we deleted it*/
    if (p)
    {
        *p = 0;
    }

    /*Otherwise we clean the stdin*/
    else
    {
        clean_stdin();
    }

    return string;
}

/*!
 * \fn void *intKey(int *nb)
 *  Do a keyboarding of an int, put 0 if the keyboarding is not an int.
 * \param[in,out] *nb the number
 */
void intKey(int *nb)
{
    char string[NB_CARACT_INT];

    stringKey(string,NB_CARACT_INT);
    *nb=0;
    sscanf(string,"%d",nb);
}

/*!
 * \fn void floatKey(float *nb)
 *  Do a keyboarding of an float, put 0 if the keyboarding is not an float.
 * \param[in,out] *nb the number
 */
void floatKey(float *nb)
{
    char string[NB_CARACT_FLOAT];
    char *decimal;

    stringKey(string,NB_CARACT_FLOAT);

    /*Change the decimal to a comma*/
    decimal = strchr(string, '.');
    if (decimal)
        *decimal = ',';

    *nb=0;
    sscanf(string,"%f",nb);
}

/*!
 * \fn void floatKeyNoComma(float *nb)
 *  Do a keyboarding of an float with no comma, put 0 if the keyboarding is not an float.
 * \param[in,out] *nb the number
 */
void floatKeyNoComma(float *nb)
{
    char string[NB_CARACT_FLOAT];
    char *p;

    stringKey(string,NB_CARACT_FLOAT);

    /*Remove the comma*/
    p = strchr(string, ',');
    if (p)
    {
        *p = '\0';
    }

    *nb=0;
    sscanf(string,"%f",nb);
}

/*!
 * \fn char *charKey(char *c)
 *  Do a keyboarding of a character.
 * \param[in,out] *c the character
 */
char *charKey(char *c)
{
    char string[2];

    fgets(string,2,stdin);
    *c=string[0];

    if (*c != '\n')
    {
        clean_stdin();
    }

    return c;
}

/*!
 * \fn void systemPause()
 *  Ask the user do press enter to continue.
 */
void systemPause()
{
    char a;

    printf(_("\nPress enter to continue"));
    charKey(&a);
}
