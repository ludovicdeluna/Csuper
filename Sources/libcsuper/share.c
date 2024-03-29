/*!
 * \file    share.c
 * \brief   Essential function of libcsuper
 * \author  Remi BERTHO
 * \date    25/01/15
 * \version 4.1.0
 */

 /*
 * share.c
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
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

    if (size_alloue == 0)
    {
        free(*ptr);
        return;
    }

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


/*!
 * \fn char *utf8ToLatin9(const char *const string)
 * Create a dynamically allocated copy of string,
 * changing the encoding from UTF-8 to ISO-8859-15.
 * Unsupported code points are ignored.
 * \param[in] string the input string in UTF-8
 * \return a newly allocated string in ISO-8859-15
 */
char *utf8ToLatin9(const char *const string)
{
    size_t         size = 0;
    size_t         used = 0;
    unsigned char *result = NULL;

    if (string) {
        const unsigned char  *s = (const unsigned char *)string;

        while (*s) {

            if (used >= size) {
                void *const old = result;

                size = (used | 255) + 257;
                result = realloc(result, size);
                if (!result) {
                    if (old)
                        free(old);
                    errno = ENOMEM;
                    return NULL;
                }
            }

            if (*s < 128) {
                result[used++] = *(s++);
                continue;

            } else
            if (s[0] == 226 && s[1] == 130 && s[2] == 172) {
                result[used++] = 164;
                s += 3;
                continue;

            } else
            if (s[0] == 194 && s[1] >= 128 && s[1] <= 191) {
                result[used++] = s[1];
                s += 2;
                continue;

            } else
            if (s[0] == 195 && s[1] >= 128 && s[1] <= 191) {
                result[used++] = s[1] + 64;
                s += 2;
                continue;

            } else
            if (s[0] == 197 && s[1] == 160) {
                result[used++] = 166;
                s += 2;
                continue;

            } else
            if (s[0] == 197 && s[1] == 161) {
                result[used++] = 168;
                s += 2;
                continue;

            } else
            if (s[0] == 197 && s[1] == 189) {
                result[used++] = 180;
                s += 2;
                continue;

            } else
            if (s[0] == 197 && s[1] == 190) {
                result[used++] = 184;
                s += 2;
                continue;

            } else
            if (s[0] == 197 && s[1] == 146) {
                result[used++] = 188;
                s += 2;
                continue;

            } else
            if (s[0] == 197 && s[1] == 147) {
                result[used++] = 189;
                s += 2;
                continue;

            } else
            if (s[0] == 197 && s[1] == 184) {
                result[used++] = 190;
                s += 2;
                continue;

            }

            if (s[0] >= 192 && s[0] < 224 &&
                s[1] >= 128 && s[1] < 192) {
                s += 2;
                continue;
            } else
            if (s[0] >= 224 && s[0] < 240 &&
                s[1] >= 128 && s[1] < 192 &&
                s[2] >= 128 && s[2] < 192) {
                s += 3;
                continue;
            } else
            if (s[0] >= 240 && s[0] < 248 &&
                s[1] >= 128 && s[1] < 192 &&
                s[2] >= 128 && s[2] < 192 &&
                s[3] >= 128 && s[3] < 192) {
                s += 4;
                continue;
            } else
            if (s[0] >= 248 && s[0] < 252 &&
                s[1] >= 128 && s[1] < 192 &&
                s[2] >= 128 && s[2] < 192 &&
                s[3] >= 128 && s[3] < 192 &&
                s[4] >= 128 && s[4] < 192) {
                s += 5;
                continue;
            } else
            if (s[0] >= 252 && s[0] < 254 &&
                s[1] >= 128 && s[1] < 192 &&
                s[2] >= 128 && s[2] < 192 &&
                s[3] >= 128 && s[3] < 192 &&
                s[4] >= 128 && s[4] < 192 &&
                s[5] >= 128 && s[5] < 192) {
                s += 6;
                continue;
            }

            s++;
        }
    }
    {
        void *const old = result;

        size = (used | 7) + 1;

        result = realloc(result, size);
        if (!result) {
            if (old)
                free(old);
            errno = ENOMEM;
            return NULL;
        }

        memset(result + used, 0, size - used);
    }

    return (char *)result;
}

/*!
 * \fn void convertFloatString(char *output, float input,int decimal_place)
 *  Convert a float into the output string with a specific number of decimal place
 * \param[in] output the output sting
 * \param[in] input the input float
 * \param[in] decimal_place the number of decimal, must be between 0 and 3
 * \return the ranking
 */
void convertFloatString(char *output, float input,int decimal_place)
{
    #ifdef _WIN32
    if isinf(input)
    {
        strcpy(output,"inf");
        return;
    }
    #endif // _WIN32
    switch (decimal_place)
    {
    case 0 :
        sprintf(output,"%.0f",input);
        break;
    case 1 :
        sprintf(output,"%.1f",input);
        break;
    case 2 :
        sprintf(output,"%.2f",input);
        break;
    case 3 :
        sprintf(output,"%.3f",input);
        break;
    }
}


/*!
 * \fn float convertStringFloat(char *str)
 *  Convert a string into a float
 * \param[in] str the string
 * \return the float
 */
float convertStringFloat(char *str)
{
    float ret;
    struct lconv *lc;
    char *comma;

    /*Change the decimals to a comma if needed*/
    lc=localeconv();
    if(*(lc->decimal_point) == ',')
    {
        while ((comma = strchr(str, '.')) != NULL)
            *comma=',';
    }
    else if(*(lc->decimal_point) == '.')
    {
        while ((comma = strchr(str, ',')) != NULL)
            *comma='.';
    }
    #ifdef _WIN32
    if (strncmp("inf",str,4) == 0)
        ret = INFINITY;
    else
    #endif // _WIN32
    sscanf(str,"%f",&ret);
    return ret;
}


/*!
 * \fn int convertStringInt(char *str)
 *  Convert a string into a int
 * \param[in] str the string
 * \return the int
 */
int convertStringInt(char *str)
{
    int ret;
    sscanf(str,"%d",&ret);
    return ret;
}


/*!
 * \fn bool convertStringBool(char *str)
 *  Convert a string into a bool
 * \param[in] str the string
 * \return the bool
 */
bool convertStringBool(char *str)
{
    return strcmp("no",str);
}
