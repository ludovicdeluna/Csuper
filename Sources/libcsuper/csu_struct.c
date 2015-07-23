
/*!
 * \file    csu_struct.c
 * \brief   Management of the csu files
 * \author  Remi BERTHO
 * \date    25/01/15
 * \version 4.1.0
 */

/*
* csu_struct.c
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
    if (index_player == -1)
    {
        for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
            ptr_csu_struct->total_points[i]+=ptr_csu_struct->point[i][(int)ptr_csu_struct->nb_turn[i]];
    }
    else
        ptr_csu_struct->total_points[index_player]+=ptr_csu_struct->point[index_player][(int)ptr_csu_struct->nb_turn[index_player]];

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
        sort_points[i]=ptr_csu_struct->total_points[i];

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
                ptr_csu_struct->rank[j]=i+1;
        }
    }

    free(sort_points);
}

/*!
 * \fn int searchIndexFromPosition(csuStruct *ptr_csu_struct, int position,int *nb)
 *  Search the index in the array of the person who is the 'position' position
 * \param[in,out] *ptr_csu_struct a pointer on a csuStruct
 * \param[in,out] position the position
 * \param[in,out] nb the nbth player who have the position will be selected
 * \return the index or NULL if the position doesn't exist
 */
int searchIndexFromPosition(csuStruct *ptr_csu_struct, int position,int *nb)
{
    int i;
    int nb_position=1;

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        if (ptr_csu_struct->rank[i] == position)
        {
            if (*nb == nb_position)
                return i;
            else
                nb_position++;
        }
    }
    if (position > 1)
    {
        *nb = *nb + 1;
        return searchIndexFromPosition(ptr_csu_struct,position-1,nb);
    }
    else
        return -1;
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
        printf(_("The distributor was initializes by default to %s.\n"),ptr_csu_struct->player_names[(int)ptr_csu_struct->distributor]);
}

/*!
 * \fn bool exceedMaxNumber(csuStruct *ptr_csu_struct)
 *  Check if someone exceed the maximum number
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \return true if someone exceed, false otherwise
 */
bool exceedMaxNumber(csuStruct *ptr_csu_struct)
{
    int i;
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        if (ptr_csu_struct->config.max == 1)
        {
            if (ptr_csu_struct->total_points[i] + FLT_EPSILON >= ptr_csu_struct->config.nb_max)
                return true;
        }
        else
        {
            if (ptr_csu_struct->total_points[i] - FLT_EPSILON <= ptr_csu_struct->config.nb_max)
                return true;
        }

    }
    return false;
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

    printf(_("\nError: this name doesn't exist.\n"));
    return -1;
}

/*!
 * \fn bool differentsPlayerName(csuStruct *ptr_csu_struct)
 *  Search if all the name are different
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \return true if all player names are different, false otherwise
 */
bool differentsPlayerName(csuStruct *ptr_csu_struct)
{
    int i;
    int j;

    for (i=0 ; i<ptr_csu_struct->nb_player -1 ; i++)
    {
        for (j=i+1 ; j<ptr_csu_struct->nb_player ; j++)
        {
            if (strcmp(ptr_csu_struct->player_names[i],ptr_csu_struct->player_names[j]) == 0)
                return false;
        }
    }

    return true;
}

/*!
 * \fn csuStruct *copyCsuStruct(csuStruct *ptr_csu_struct)
 *  Copy a csu structure
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \return a pointer on the new csu structure
 */
csuStruct *copyCsuStruct(csuStruct *ptr_csu_struct)
{
    csuStruct *ptr_copy_csu_struct=(csuStruct *)myAlloc(sizeof(csuStruct));
    int i;

    ptr_copy_csu_struct->version = ptr_csu_struct->version;
    ptr_copy_csu_struct->size_max_name = ptr_csu_struct->size_max_name;
    ptr_copy_csu_struct->day = ptr_csu_struct->day;
    ptr_copy_csu_struct->month = ptr_csu_struct->month;
    ptr_copy_csu_struct->year = ptr_csu_struct->year;
    ptr_copy_csu_struct->nb_player = ptr_csu_struct->nb_player;
    ptr_copy_csu_struct->config = ptr_csu_struct->config;

    ptr_copy_csu_struct->player_names=(char **)myAlloc(ptr_csu_struct->nb_player*sizeof(char*));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        ptr_copy_csu_struct->player_names[i]=(char *)myAlloc(ptr_csu_struct->size_max_name*sizeof(char));
        memcpy(ptr_copy_csu_struct->player_names[i],ptr_csu_struct->player_names[i],sizeof(char)*ptr_copy_csu_struct->size_max_name);
    }

    ptr_copy_csu_struct->total_points=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    memcpy(ptr_copy_csu_struct->total_points,ptr_csu_struct->total_points,sizeof(float)*ptr_copy_csu_struct->nb_player);

    ptr_copy_csu_struct->rank=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    memcpy(ptr_copy_csu_struct->rank,ptr_csu_struct->rank,sizeof(float)*ptr_copy_csu_struct->nb_player);

    ptr_copy_csu_struct->nb_turn=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    memcpy(ptr_copy_csu_struct->nb_turn,ptr_csu_struct->nb_turn,sizeof(float)*ptr_copy_csu_struct->nb_player);

    ptr_copy_csu_struct->distributor = ptr_csu_struct->distributor;

    ptr_copy_csu_struct->point=(float **)myAlloc(ptr_csu_struct->nb_player*sizeof(float*));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        ptr_copy_csu_struct->point[i]=(float *)myAlloc(ptr_csu_struct->nb_turn[i]*sizeof(float));
        memcpy(ptr_copy_csu_struct->point[i],ptr_csu_struct->point[i],sizeof(float)*ptr_csu_struct->nb_turn[i]);
    }

    return ptr_copy_csu_struct;
}

/*!
 * \fn bool changeDistributor(csuStruct *ptr_csu_struct, int index)
 *  Change the distributor
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \param[in] index the index of the player
 * \return true if the distributor can be change, false otherwise
 */
bool changeDistributor(csuStruct *ptr_csu_struct, int index)
{
    if (index >= ptr_csu_struct->nb_player + 0.1)
    {
        printf(_("\nError: this index doesn't exist\n"));
        return false;
    }

    ptr_csu_struct->distributor = index;

    return true;
}


/*!
 * \fn float pointsAtTurn(csuStruct *ptr_csu_struct, int player_index, int turn)
 *  Return the number of points of a player at a specific turn
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \param[in] player_index the index of the player
 * \param[in] turn the turn
 * \return the total number of points
 */
float pointsAtTurn(csuStruct *ptr_csu_struct, int player_index, int turn)
{
    if (ptr_csu_struct->nb_turn[player_index] < turn)
    {
        printf(_("\nError: %s only have %.0f turn but you ask the %d turn\n"),ptr_csu_struct->player_names[player_index],ptr_csu_struct->nb_turn[player_index],turn);
        return 0;
    }
    if (turn < 0)
    {
        printf(_("\nError: negative turns doesn't exist\n"));
        return 0;
    }

    int i;
    float points=0;

    for (i=0 ; i<=turn ; i++)
        points += ptr_csu_struct->point[player_index][i];

    return points;
}


/*!
 * \fn float rankAtTurn(csuStruct *ptr_csu_struct, int player_index, int turn)
 *  Return the ranking of a player at a specific turn
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \param[in] player_index the index of the player
 * \param[in] turn she turn
 * \return the ranking or 0 if the game configuration is not turn based
 */
int rankAtTurn(csuStruct *ptr_csu_struct, int player_index, int turn)
{
    float *sort_points;
    int i;
    int ranking;

    if (ptr_csu_struct->config.turn_based == 0)
        return 0;

    sort_points=(float *)myAlloc(sizeof(float)*ptr_csu_struct->nb_player);

    for(i=0 ; i<ptr_csu_struct->nb_player ; i++)
        sort_points[i]=pointsAtTurn(ptr_csu_struct,i,turn);

    /*Sort the points base on the first way*/
    if(ptr_csu_struct->config.first_way == 1)
        qsort(sort_points,ptr_csu_struct->nb_player,sizeof(float),compareFloatDescending);
    else
        qsort(sort_points,ptr_csu_struct->nb_player,sizeof(float),compareFloatAscending);


    /*Loop on the sort points from the smallest*/
    for(i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        if (sort_points[i] == pointsAtTurn(ptr_csu_struct,player_index,turn))
        {
            ranking = i+1;
            break;
        }
    }

    free(sort_points);

    return ranking;
}

/*!
 * \fn int lastRankAtTurn(csuStruct *ptr_csu_struct, int turn)
 *  Return the last rank at a specific turn
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \param[in] turn she turn
 * \return the last rank or 0 if the game configuration is not turn based
 */
int lastRankAtTurn(csuStruct *ptr_csu_struct, int turn)
{
    float *sort_points;
    int i,j;
    int *rank;
    int last_rank=0;

    if (ptr_csu_struct->config.turn_based == 0)
        return 0;

    sort_points=(float *)myAlloc(sizeof(float)*ptr_csu_struct->nb_player);
    rank=(int *)myAlloc(sizeof(int)*ptr_csu_struct->nb_player);

    for(i=0 ; i<ptr_csu_struct->nb_player ; i++)
        sort_points[i]=pointsAtTurn(ptr_csu_struct,i,turn);

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
            if (sort_points[i]==pointsAtTurn(ptr_csu_struct,j,turn))
                rank[j]=i+1;
        }
    }

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        if (rank[i] > last_rank)
            last_rank = rank[i];
    }

    free(sort_points);
    free(rank);

    return last_rank;
}



/*!
 * \fn bool changeDeleteTurn(csuStruct *ptr_csu_struct, int player_index, int turn)
 *  Delete a turn of a player or all of them
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \param[in] player_index the index of the player
 * \param[in] turn the turn
 * \return true if everything is OK, false otherwise
 */
bool deleteTurn(csuStruct *ptr_csu_struct, int player_index, int turn)
{
    int i,j;

    // Test the turn
    if (ptr_csu_struct->nb_turn[player_index] < turn)
    {
        printf(_("\nError: %s only have %.0f turn but you ask the %d turn\n"),ptr_csu_struct->player_names[player_index],ptr_csu_struct->nb_turn[player_index],turn);
        return 0;
    }
    if (turn < 0)
    {
        printf(_("\nError: negative turns doesn't exist\n"));
        return 0;
    }

    // Turn based game
    if (ptr_csu_struct->config.turn_based)
    {
        // For all player delete the points and the turn
        for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        {
            (ptr_csu_struct->total_points[i]) -= ptr_csu_struct->point[i][turn];
            for (j=turn+1 ; j<ptr_csu_struct->nb_turn[i] ; j++)
            {
                ptr_csu_struct->point[i][j-1] = ptr_csu_struct->point[i][j];
            }
            myRealloc((void**)&(ptr_csu_struct->point[i]),((ptr_csu_struct->nb_turn[i])-1)*sizeof(float));
            (ptr_csu_struct->nb_turn[i]) -= 1;
        }

    }
    else
    {
        (ptr_csu_struct->total_points[player_index]) -= ptr_csu_struct->point[player_index][turn];
        for (j=turn+1 ; j<ptr_csu_struct->nb_turn[player_index] ; j++)
            ptr_csu_struct->point[player_index][j-1] = ptr_csu_struct->point[player_index][j];
        myRealloc((void**)&(ptr_csu_struct->point[player_index]),((ptr_csu_struct->nb_turn[player_index])-1)*sizeof(float));
        (ptr_csu_struct->nb_turn[player_index]) -= 1;
    }

    rankCalculation(ptr_csu_struct);

    return true;
}


/*!
 * \fn float meanPoints(csuStruct *ptr_csu_struct, int player_index)
 *  Calculate the mean points of a player
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \param[in] player_index the index of the player
 * \return the mean points
 */
float meanPoints(csuStruct *ptr_csu_struct, int player_index)
{
    return ptr_csu_struct->total_points[player_index] / (ptr_csu_struct->nb_turn[player_index]-1);
}


/*!
 * \fn int nbTurnBest(csuStruct *ptr_csu_struct, int player_index)
 *  Calculate the number of turn where the player do the best score
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \param[in] player_index the index of the player
 * \return the  number of turn where the player do the best score
 */
int nbTurnBest(csuStruct *ptr_csu_struct, int player_index)
{
    int i,j;
    int nb_best=0;
    float best;

    if (ptr_csu_struct->config.turn_based == 0)
        return -1;


    for (i=1 ; i<ptr_csu_struct->nb_turn[player_index] ; i++)
    {
        if (ptr_csu_struct->config.first_way == 1)
            best=-FLT_MAX;
        else
            best=FLT_MAX;

        for (j=0 ; j<ptr_csu_struct->nb_player ; j++)
        {
            if ((ptr_csu_struct->config.first_way == 1) && (ptr_csu_struct->point[j][i] > best) )
                best = ptr_csu_struct->point[j][i];
            else if ((ptr_csu_struct->config.first_way == -1) && (ptr_csu_struct->point[j][i] < best) )
                best = ptr_csu_struct->point[j][i];
        }

        if (best == ptr_csu_struct->point[player_index][i])
            nb_best++;
    }


    return nb_best;
}

/*!
 * \fn int nbTurnWorst(csuStruct *ptr_csu_struct, int player_index)
 *  Calculate the number of turn where the player do the worst score
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \param[in] player_index the index of the player
 * \return the  number of turn where the player do the worst score
 */
int nbTurnWorst(csuStruct *ptr_csu_struct, int player_index)
{
    int i,j;
    int nb_worst=0;
    float worst;

    if (ptr_csu_struct->config.turn_based == 0)
        return -1;


    for (i=1 ; i<ptr_csu_struct->nb_turn[player_index] ; i++)
    {
        if (ptr_csu_struct->config.first_way == 1)
            worst=FLT_MAX;
        else
            worst=-FLT_MAX;

        for (j=0 ; j<ptr_csu_struct->nb_player ; j++)
        {
            if ((ptr_csu_struct->config.first_way == 1) && (ptr_csu_struct->point[j][i] < worst) )
                worst = ptr_csu_struct->point[j][i];
            else if ((ptr_csu_struct->config.first_way == -1) && (ptr_csu_struct->point[j][i] > worst) )
                worst = ptr_csu_struct->point[j][i];
        }

        if (worst == ptr_csu_struct->point[player_index][i])
            nb_worst++;
    }


    return nb_worst;
}


/*!
 * \fn int nbTurnFirst(csuStruct *ptr_csu_struct, int player_index)
 *  Calculate the number of turn where the player is the first place
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \param[in] player_index the index of the player
 * \return the  number of turn where the player is the first
 */
int nbTurnFirst(csuStruct *ptr_csu_struct, int player_index)
{
    int i;
    int nb_first=0;

    if (ptr_csu_struct->config.turn_based == 0)
        return -1;


    for (i=1 ; i<ptr_csu_struct->nb_turn[player_index] ; i++)
    {
        if (1 == rankAtTurn(ptr_csu_struct,player_index,i))
            nb_first++;
    }

    return nb_first;
}


/*!
 * \fn int nbTurnLast(csuStruct *ptr_csu_struct, int player_index)
 *  Calculate the number of turn where the player is the last place
 * \param[in] *ptr_csu_struct a pointer on a csuStruct
 * \param[in] player_index the index of the player
 * \return the  number of turn where the player is the last
 */
int nbTurnLast(csuStruct *ptr_csu_struct, int player_index)
{
    int i;
    int nb_last=0;
    if (ptr_csu_struct->config.turn_based == 0)
        return -1;


    for (i=1 ; i<ptr_csu_struct->nb_turn[player_index] ; i++)
    {
        if (lastRankAtTurn(ptr_csu_struct,i) == rankAtTurn(ptr_csu_struct,player_index,i))
            nb_last++;
    }

    return nb_last;
}
