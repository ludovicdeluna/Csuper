/*!
 * \file    display.c
 * \brief   Display the games
 * \author  Remi BERTHO
 * \date    17/04/14
 * \version 2.2.0
 */

 /*
 * display.c
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

 #include "display.h"

/*!
 * \fn void printNames(csuStruct *ptr_csu_struct, int *ptr_size_line)
 *  Print the payers names and calculate the size of a line.
 * \param[in] *ptr_csu_struct a pointer on a csu structure
 * \param[in,out] *ptr_size_line a pointer to the size of the line, NULL if you doesn't need it
 */
void printNames(csuStruct *ptr_csu_struct, int *ptr_size_line)
{
    int i;
    int j;

    printf("\nNoms    | ");
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        /*Display the player name*/
        printf("%s",ptr_csu_struct->player_names[i]);
        for (j=strlen(ptr_csu_struct->player_names[i]) ; j < 4 ; j++)
        {
            printf(" ");
            if (ptr_size_line != NULL)
                *ptr_size_line+=1;
        }

        printf(" | ");

        /*Calculate the size of the line*/
        if (ptr_size_line != NULL)
            *ptr_size_line+=(strlen(ptr_csu_struct->player_names[i])+3);
    }
}

 /*!
 * \fn void printLigne(int size_line)
 *  Print a line of - after a tabulation.
 * \param[in] size_line the size of the line
 */
void printLigne(int size_line)
{
    int i;

    printf("\n\t");

    for (i=0 ; i<size_line ; i++)
    {
        printf("-");
    }
}

/*!
 * \fn void printTotalPoints(csuStruct *ptr_csu_struct)
 *  Print the total score of the players.
 * \param[in] *ptr_csu_struct a pointer on a csu structure
 */
void printTotalPoints(csuStruct *ptr_csu_struct)
{
    int i;
    int j;

    /*TRANSLATORS:The number of characters before the | must be eight*/
    printf(_("\nTotal   |"));

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        /*Print the score of the player*/
        switch (ptr_csu_struct->config.number_after_comma)
        {
        case 0 :
            printf("%6.0f",ptr_csu_struct->total_points[i]);
            break;
        case 1 :
            printf("%6.1f",ptr_csu_struct->total_points[i]);
            break;
        case 2 :
            printf("%6.2f",ptr_csu_struct->total_points[i]);
            break;
        case 3 :
            printf("%6.3f",ptr_csu_struct->total_points[i]);
            break;
        }

        /*Add space at the end to keep the form*/
        for (j=4 ; j<strlen(ptr_csu_struct->player_names[i]); j++)
        {
            printf(" ");
        }

        printf("|");
    }
}

/*!
 * \fn void printDistributor(csuStruct *ptr_csu_struct)
 *  Display the distributor.
 * \param[in] *ptr_csu_struct a pointer on a csu structure
 */
void printDistributor(csuStruct *ptr_csu_struct)
{
    if (ptr_csu_struct->config.use_distributor)
        printf(_("\n%s is the distributor."),ptr_csu_struct->player_names[(int)ptr_csu_struct->distributor]);
    printf("\n");
}

/*!
 * \fn void printHeader(csuStruct *ptr_csu_struct)
 *  Print the header of the structure
 * \param[in] *ptr_csu_struct a pointer on a csu structure
 */
void printHeader(csuStruct *ptr_csu_struct)
{
    printf(_("\nCsu file\nCreated the %02.0f/%02.0f/%4.0f\nFile's version : %1.1f\nSize max of the names : %.0f"
    "\nNumber of players : %.0f\nNumbers maximum of turns : %d")
    ,ptr_csu_struct->day,ptr_csu_struct->month,ptr_csu_struct->year,ptr_csu_struct->version,ptr_csu_struct->size_max_name
    ,ptr_csu_struct->nb_player,maxNbTurn(ptr_csu_struct));
    printGameConfig(ptr_csu_struct->config);
}

/*!
 * \fn void printAllPoints(csuStruct *ptr_csu_struct)
 *  Print the scores of all player in each turn.
 * \param[in] *ptr_csu_struct a pointer on a csu structure
 */
void printAllPoints(csuStruct *ptr_csu_struct)
{
    int i;
    int j;
    int k;

    int max_nb_turn = maxNbTurn(ptr_csu_struct);

    for (i=0 ; i<max_nb_turn ; i++)
    {
        /*TRANSLATORS:The number of characters before the | and without the %2.0f must be six*/
        printf(_("\nTurn %2.0f |"),(float)i + 1);

        for (k=0 ; k<ptr_csu_struct->nb_player ; k++)
        {
            if (ptr_csu_struct->nb_turn[k] >= i+1)
            {
                switch (ptr_csu_struct->config.number_after_comma)
                {
                case 0 :
                    printf("%6.0f",ptr_csu_struct->point[k][i]);
                    break;
                case 1 :
                    printf("%6.1f",ptr_csu_struct->point[k][i]);
                    break;
                case 2 :
                    printf("%6.2f",ptr_csu_struct->point[k][i]);
                    break;
                case 3 :
                    printf("%6.3f",ptr_csu_struct->point[k][i]);
                    break;
                }
            }
            else
                printf("      ");

            /*Add space at the end to keep the form*/
            for (j=4 ; j<(strlen(ptr_csu_struct->player_names[k])); j++)
            printf(" ");

            printf("|");
        }
    }
}

/*!
 * \fn void printRanking(csuStruct *ptr_csu_struct)
 *  Print the rank of each player
 * \param[in] *ptr_csu_struct a pointer on a csu structure
 */
void printRanking(csuStruct *ptr_csu_struct)
{
    int i;
    int j;

    /*TRANSLATORS:The number of characters before the | must be eight*/
    printf(_("\nRanking |"));

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        printf("%6.0f",ptr_csu_struct->rank[i]);

        /*Add space at the end to keep the form*/
        for (j=4 ; j<strlen(ptr_csu_struct->player_names[i]) ; j++)
        {
            printf(" ");
        }

        printf("|");
    }
}

/*!
 * \fn void printPoints(csuStruct *ptr_csu_struct)
 *  Print the names, the points, the total points and the rank of each player.
 * \param[in] *ptr_csu_struct a pointer on a csu structure
 */
void printPoints(csuStruct *ptr_csu_struct)
{
    int size_ligne=1;

    printNames(ptr_csu_struct,&size_ligne);
    printLigne(size_ligne);
    printAllPoints(ptr_csu_struct);
    printLigne(size_ligne);
    printNames(ptr_csu_struct,NULL);
    printLigne(size_ligne);
    printTotalPoints(ptr_csu_struct);
    printLigne(size_ligne);
    printRanking(ptr_csu_struct);
    if (ptr_csu_struct->config.use_distributor)
        printf("\n");
    printDistributor(ptr_csu_struct);
}

/*!
 * \fn void printCsuStruct(csuStruct *ptr_csu_struct)
 *  Print all data of the csu structure.
 * \param[in] *ptr_csu_struct a pointer on a csu structure
 */
void printCsuStruct(csuStruct *ptr_csu_struct)
{
    int size_ligne=1;

    printHeader(ptr_csu_struct);
    printDistributor(ptr_csu_struct);
    printNames(ptr_csu_struct,&size_ligne);
    printLigne(size_ligne);
    printAllPoints(ptr_csu_struct);
    printLigne(size_ligne);
    printTotalPoints(ptr_csu_struct);
    printLigne(size_ligne);
    printRanking(ptr_csu_struct);
    printf("\n");
}

/*!
 * \fn void printGameOver(csuStruct *ptr_csu_struct)
 *  Display that the game is over and a podium.
 * \param[in] *ptr_csu_struct a pointer on a csu structure
 */
void printGameOver(csuStruct *ptr_csu_struct)
{
    int pos[3]={0,1,2};
    int i;
    int un_pris=FALSE;
    int deux_pris=FALSE;

    printf(_("\nThe game is over.\n"));

    /*Initialization of the position array*/
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        if (ptr_csu_struct->rank[i] == 3 || (un_pris && deux_pris && ptr_csu_struct->rank[i] == 1) || (deux_pris && ptr_csu_struct->rank[i] == 2))
            pos[2]=i;

        if ((ptr_csu_struct->rank[i] == 2 && !deux_pris ) || (un_pris && ptr_csu_struct->rank[i] == 1 && !deux_pris))
        {
            pos[1]=i;
            deux_pris=TRUE;
        }
        if (ptr_csu_struct->rank[i] == 1 && !un_pris)
        {
            pos[0]=i;
            un_pris=TRUE;
        }
    }

    /*Print the first line*/
    printf("\n\t\t\t");
    printStringThreeTabs(ptr_csu_struct->player_names[pos[0]]);
    printf("\n");

    /*Print the second line*/
    if(ptr_csu_struct->nb_player >=2)
        printStringThreeTabs(ptr_csu_struct->player_names[pos[1]]);
    else
        printf("\t\t\t");
    for (i=0 ; i<24 ; i++)
        printf("-");
    printf("\n");

    /*Print the bottom of the second podium*/
    if(ptr_csu_struct->nb_player >=2)
    {
        for (i=0 ; i<24 ; i++)
            printf("-");
    }

    /*Print the third podium*/
    if (ptr_csu_struct->nb_player >= 3)
    {
        printf("\t\t\t");
        printStringThreeTabs(ptr_csu_struct->player_names[pos[2]]);
        printf("\n\t\t\t\t\t\t");
        for (i=0 ; i<24 ; i++)
            printf("-");
    }

}

/*!
 * \fn void printStringThreeTabs(char *string)
 *  Print a string center into a space of three tabulations.
 * \param[in] *string a string
 */
void printStringThreeTabs(char *string)
{
    int i;
    int size=strlen(string);

    for (i=0 ; i<(24-size)/2 ; i++)
    {
        printf(" ");
    }

    printf("%s",string);

    for (i=0 ; i<(24-size)/2 ; i++)
    {
        printf(" ");
    }
}

/*!
 * \fn void printLicense()
 *  Print the license.
 */
void printLicense()
{
    printf(_("\nCsuper Copyright (C) 2014 Remi BERTHO <remi.bertho@gmail.com>\n"
    "This program comes with ABSOLUTELY NO WARRANTY. \nThis is free software, and you are welcome to redistribute it"
    " under certain conditions. \nFore more details : http://www.gnu.org/licenses/gpl.html\n"));
}

/*!
 * \fn void printGameConfig(game_config config)
 *  Print the game config
 * \param[in] config a game config
 */
void printGameConfig(game_config config)
{
    printf(_("\nName of the game configuration : %s\nUse a maximum score : %d\nInitial score : %.3f\n"
    "Number of digit display after the comma : %d\nFirst way : %d\n"
    "Game in turn by turn : %d\nUse a distributor : %d\n")
    ,config.name,config.max,config.begin_score,config.number_after_comma,config.first_way,config.turn_by_turn,config.use_distributor);
    #ifdef __unix__
    printf(_("Number of points maximum/minimum : %.3f\n"),config.nb_max);
    #elif _WIN32
    if (config.nb_max == INFINITY)
        printf(_("Number of points maximum/minimum : inf\n"));
    else
        printf(_("Number of points maximum/minimum : %.3f\n"),config.nb_max);
    #endif
}
