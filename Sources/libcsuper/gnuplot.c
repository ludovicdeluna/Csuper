/*!
 * \file    gnuplot.c
 * \author  Remi BERTHO
 * \date    14/05/15
 * \version 4.2.0
 */

/*
 * gnuplot.c
 *
 * Copyright 2014-2015 dalan <remi.bertho@openmailbox.org>
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

#include "gnuplot.h"

/*!
 * \fn bool exportToGnuplotFile(csuStruct *ptr_csu_struct, char *filename)
 *  Export the csu structure to gnuplot files
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \param[in] filename the filename
 * \return true if everything is OK, false otherwise
 */
bool exportToGnuplotFile(csuStruct *ptr_csu_struct, char *filename)
{
    if (!exportToGnuplotData(ptr_csu_struct,filename))
        return false;
    return exportToGnuplotScript(ptr_csu_struct,filename);
}

/*!
 * \fn bool exportToGnuplotData(csuStruct *ptr_csu_struct, char *filename)
 *  Export the csu structure to a gnuplot data file
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \param[in] filename the filename of the gnuplot data file
 * \return true if everything is OK, false otherwise
 */
bool exportToGnuplotData(csuStruct *ptr_csu_struct, char *filename)
{
    FILE *ptr_file;
    char dat_filename[SIZE_MAX_FILE_NAME];
    char buffer[128];
    int i,j;
    struct lconv *lc = localeconv();
    char *comma;

    strncpy(dat_filename,filename,SIZE_MAX_FILE_NAME);
    addFileDatExtension(dat_filename);
    ptr_file = openFile(dat_filename,"w");
    if (ptr_file == NULL)
        return false;

    fprintf(ptr_file,_("\"Players\""));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        fprintf(ptr_file,"\t\"%s\"",ptr_csu_struct->player_names[i]);

    for (i=0 ; i<maxNbTurn(ptr_csu_struct) ; i++)
    {
        fprintf(ptr_file,"\n%d",i);

        for (j=0 ; j<ptr_csu_struct->nb_player ; j++)
        {
            if (ptr_csu_struct->nb_turn[j] >= i+1)
            {
                convertFloatString(buffer,pointsAtTurn(ptr_csu_struct,j,i),ptr_csu_struct->config.decimal_place);
                if(*(lc->decimal_point) == ',')
                {
                    while ((comma = strchr(buffer, ',')) != NULL)
                        *comma='.';
                }
                fprintf(ptr_file,"\t%s",buffer);
            }
            else
                fprintf(ptr_file,"\t-");
        }
    }

    closeFile(ptr_file);
    return true;
}


/*!
 * \fn bool exportToGnuplotScript(csuStruct *ptr_csu_struct, char *filename)
 *  Export the csu structure to a gnuplot script file
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \param[in] filename the filename of the gnuplot script file
 * \return true if everything is OK, false otherwise
 */
bool exportToGnuplotScript(csuStruct *ptr_csu_struct, char *filename)
{
    FILE *ptr_file;
    char script_filename[SIZE_MAX_FILE_NAME];
    char dat_filename[SIZE_MAX_FILE_NAME];
    char simple_filename[SIZE_MAX_FILE_NAME];

    // Filenames
    getSimpleFilenameFromFullFilename(filename,simple_filename);

    strncpy(script_filename,filename,SIZE_MAX_FILE_NAME);
    addFileGnuplotExtension(script_filename);

    getSimpleFilenameFromFullFilename(filename,dat_filename);
    addFileDatExtension(dat_filename);

    ptr_file = openFile(script_filename,"w");
    if (ptr_file == NULL)
        return false;

    fprintf(ptr_file,_("set datafile missing '-'\n"
                    "set style data linespoints\n"
                    "set xlabel \"Number of turns\"\n"
                    "set ylabel \"Points\"\n"
                    "set title \"Points on %s\"\n"),simple_filename);

    fprintf(ptr_file,"plot '%s' using 2:xtic(1) title columnheader(2), for [i=3:%.0f"
                    "] '' using i title columnheader(i)\npause -1",dat_filename,ptr_csu_struct->nb_player+1);

    closeFile(ptr_file);
    return true;
}
