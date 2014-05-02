/*!
 * \file    csu_struct.c
 * \brief   Management of the csu files
 * \author  Remi BERTHO
 * \date    15/04/14
 * \version 2.2.0
 */

 /*
 * csu_struct.c
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
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

 #include "csu_struct.h"

/*!
 * \fn csuStruct *newCsuStruct(float nb_player , game_config config)
 *  Create a new csuStruct from a game configuration and the number of player.
 * \param[in] nb_player the number of player
 * \param[in] config the game configuration
 */
csuStruct *newCsuStruct(float nb_player , game_config config)
{
    csuStruct *ptr_csu_struct;
    int i;
    time_t timestamp;
    struct tm *t;

    /*Memory allocation of the structure*/
    ptr_csu_struct=(csuStruct *)myAlloc(sizeof(csuStruct));

    /*Copy the a few variable on the structure*/
    ptr_csu_struct->size_max_name=SIZE_MAX_NAME;
    ptr_csu_struct->version=VERSION;
    ptr_csu_struct->nb_player=nb_player;
    ptr_csu_struct->distributor=0;
    ptr_csu_struct->config=config;

    /*Memory allocation of the number of turn*/
    ptr_csu_struct->nb_turn=(float *)myAlloc(nb_player*sizeof(float*));

    /*Memory allocation of the player's names*/
    ptr_csu_struct->player_names=(char **)myAlloc(nb_player*sizeof(char*));
    for (i=0 ; i<nb_player ; i++)
        ptr_csu_struct->player_names[i]=(char *)myAlloc(SIZE_MAX_NAME*sizeof(char));

    /*Memory allocation of the total points and the ranking*/
    ptr_csu_struct->total_points=(float *)myAlloc(nb_player*sizeof(float));
    ptr_csu_struct->rank=(float *)myAlloc(nb_player*sizeof(float));

    /*Memory allocation of the points*/
    ptr_csu_struct->point=(float **)myAlloc(ptr_csu_struct->nb_player*sizeof(float*));
    for (i=0 ; i<nb_player ; i++)
        ptr_csu_struct->point[i]=(float*)myAlloc(1*sizeof(float));

    /*Initialization of the total points,the rank and the number of turns*/
    for (i=0 ; i<nb_player ; i++)
    {
        ptr_csu_struct->total_points[i]=ptr_csu_struct->config.begin_score;
        ptr_csu_struct->rank[i]=1;
        ptr_csu_struct->nb_turn[i]=1;
        ptr_csu_struct->point[i][0]=ptr_csu_struct->config.begin_score;
    }

    /*Save the current date*/
    timestamp = time(NULL);
    t = localtime(&timestamp);
    ptr_csu_struct->year=(t->tm_year+1900);
    ptr_csu_struct->month=(t->tm_mon+1);
    ptr_csu_struct->day=(t->tm_mday);

    return ptr_csu_struct;
}

/*!
 * \fn void closeCsuStruct(csuStruct *ptr_csu_struct)
 *  Free a csuStruct
 * \param[in,out] *ptr_csu_struct a pointer to the csuStruct
 */
void closeCsuStruct(csuStruct *ptr_csu_struct)
{
    int i;

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        free(ptr_csu_struct->point[i]);
    free(ptr_csu_struct->point);
    free(ptr_csu_struct->total_points);
    free(ptr_csu_struct->nb_turn);
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        free(ptr_csu_struct->player_names[i]);
    free(ptr_csu_struct->player_names);
    free(ptr_csu_struct->rank);
    free(ptr_csu_struct);
}

/*!
 * \fn void startNewTurn(csuStruct *ptr_csu_struct,int index_player)
 *  Reallocate the memory for the point to begin a new turn.
 * \param[in,out] *ptr_csu_struct a pointer on a csuStruct
 * \param[in,out] index_player the index of the player who begin a new turn, -1 if everybody begin a new turn
 */
void startNewTurn(csuStruct *ptr_csu_struct,int index_player)
{
    int i;

    if (index_player == -1)
    {
         for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
            myRealloc((void**)&(ptr_csu_struct->point[i]),ptr_csu_struct->nb_player*((ptr_csu_struct->nb_turn[0])+1)*sizeof(float));
    }
    else
        myRealloc((void **)&(ptr_csu_struct->point[index_player]),ptr_csu_struct->nb_player*((ptr_csu_struct->nb_turn[index_player])+1)*sizeof(float));
}

/*!
 * \fn void endNewTurn(csuStruct *ptr_csu_struct, int index_player)
 *  Update the total points, the number of turn, the distributor and the rank for a new turn
 * \param[in,out] *ptr_csu_struct a pointer on a csuStruct
 * \param[in,out] index_player index_player the index of the player who begin a new turn, -1 if everybody begin a new turn
 */
void endNewTurn(csuStruct *ptr_csu_struct, int index_player)
{
    int i;

    /*Update the total points*/
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        ptr_csu_struct->total_points[i]+=ptr_csu_struct->point[i][(int)ptr_csu_struct->nb_turn[i]];
    }

    /*Update the number of turn*/
    if (index_player == -1)
    {
        for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
            (ptr_csu_struct->nb_turn[i])++;
    }
    else
        (ptr_csu_struct->nb_turn[index_player])++;

    /*Update the distributor*/
    if (ptr_csu_struct->distributor == ptr_csu_struct->nb_player -1)
        ptr_csu_struct->distributor=0;
    else
        (ptr_csu_struct->distributor)++;

    rankCalculation(ptr_csu_struct);
}

/*!
 * \fn void rankCalculation(csuStruct *ptr_csu_struct)
 *  Calculate the rank
 * \param[in,out] *ptr_csu_struct a pointer on a csuStruct
 */
void rankCalculation(csuStruct *ptr_csu_struct)
{
    float *sort_points;
    int i;
    int j;

    sort_points=(float *)myAlloc(sizeof(float)*ptr_csu_struct->nb_player);

    for(i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        sort_points[i]=ptr_csu_struct->total_points[i];
    }

    /*Sort the points base on the first way*/
    if(ptr_csu_struct->config.first_way == 1)
        qsort(sort_points,ptr_csu_struct->nb_player,sizeof(float),compareFloatDescending);
    else
        qsort(sort_points,ptr_csu_struct->nb_player,sizeof(float),compareFloatAscending);


    /*Loop on the sort points from the smallest*/
    for(i=ptr_csu_struct->nb_player -1 ; i>=0 ; i--)
    {
        /*Loop on the total points*/
        for(j=0 ; j<ptr_csu_struct->nb_player ; j++)
        {
            if (sort_points[i]==ptr_csu_struct->total_points[j])
            {
                ptr_csu_struct->rank[j]=i+1;
            }
        }
    }

    free(sort_points);
}

/*!
 * \fn void addDistributorCsuStruct(csuStruct *ptr_csu_struct, char *distributor_name)
 *  Add the distributor on the structure
 * \param[in] *distributor_name the name of the distributor
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 */
void addDistributorCsuStruct(csuStruct *ptr_csu_struct, char *distributor_name)
{
    int index_player=searchPlayerIndex(ptr_csu_struct,distributor_name);

    libcsuper_initialize();

    if(index_player != -1)
    {
        ptr_csu_struct->distributor = index_player;
        return;
    }
    else
        printf(_("The distributor was initialize by default to %s.\n"),ptr_csu_struct->player_names[(int)ptr_csu_struct->distributor]);
}

/*!
 * \fn int exceedMaxNumber(csuStruct *ptr_csu_struct)
 *  Check if someone exceed the maximum number
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \return MY_TRUE if someone exceed, MY_FALSE otherwise
 */
int exceedMaxNumber(csuStruct *ptr_csu_struct)
{
    int i;
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        if (ptr_csu_struct->config.max == 1)
        {
            if (ptr_csu_struct->total_points[i] + FLT_EPSILON >= ptr_csu_struct->config.nb_max)
                return MY_TRUE;
        }
        else
        {
            if (ptr_csu_struct->total_points[i] - FLT_EPSILON <= ptr_csu_struct->config.nb_max)
                return MY_TRUE;
        }

    }
    return MY_FALSE;
}

/*!
 * \fn int maxNbTurn(csuStruct *ptr_csu_struct)
 *  Search the maximal number of turn
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \return the maximal number of turn
 */
int maxNbTurn(csuStruct *ptr_csu_struct)
{
    int max = ptr_csu_struct->nb_turn[0];
    int i;

    for (i=1 ; i<ptr_csu_struct->nb_player ; i++)
    {
        if (ptr_csu_struct->nb_turn[i] > max)
            max = ptr_csu_struct->nb_turn[i];
    }
    return max;
}

/*!
 * \fn int searchPlayerIndex(csuStruct *ptr_csu_struct, char *player_name)
 *  Search the index of a person
 * \param[in] *player_name the name of the player
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \return the index, -1 if there is not found
 */
int searchPlayerIndex(csuStruct *ptr_csu_struct, char *player_name)
{
    int i;

    libcsuper_initialize();

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        if (strncasecmp(ptr_csu_struct->player_names[i],player_name,strlen(player_name))==0)
            return i;
    }

    printf(_("\nError this name doesn't exist.\n"));
    return -1;
}
