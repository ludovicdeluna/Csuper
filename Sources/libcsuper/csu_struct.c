/*!
 * \file    csu_struct.c
 * \brief   Fonction de gestion des fichiers de la struction contenant les informations
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

 /*
 * csu_struct.c
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

 #include "csu_struct.h"

/*!
 * \fn csuStruct *newCsuStruct(float nb_player , game_config config)
 *  Cree une structure Fichier_jeu a partir des donnees de la fonction.
 * \param[in] nb_player le nombre de joueur
 * \param[in] config la configuration de la partie
 */
csuStruct *newCsuStruct(float nb_player , game_config config)
{
    csuStruct *ptr_csu_struct;
    int i;
    time_t timestamp;
    struct tm *t;

    /*Allocation memoire de la structure*/
    ptr_csu_struct=(csuStruct *)myAlloc(sizeof(csuStruct));

    /*Copie de certaines variables dans la structure*/
    ptr_csu_struct->size_max_name=SIZE_MAX_NAME;
    ptr_csu_struct->version=VERSION;
    ptr_csu_struct->nb_player=nb_player;
    ptr_csu_struct->distributor=0;
    ptr_csu_struct->config=config;

    /*Allocation memoire des nombre de tours*/
    ptr_csu_struct->nb_turn=(float *)myAlloc(nb_player*sizeof(float*));

    /*Allocation memoire du tableau des nom des personnes*/
    ptr_csu_struct->player_names=(char **)myAlloc(nb_player*sizeof(char*));
    for (i=0 ; i<nb_player ; i++)
        ptr_csu_struct->player_names[i]=(char *)myAlloc(SIZE_MAX_NAME*sizeof(char));

    /*Allocation memoire des points totaux et des de ranks*/
    ptr_csu_struct->total_points=(float *)myAlloc(nb_player*sizeof(float));
    ptr_csu_struct->rank=(float *)myAlloc(nb_player*sizeof(float));

    /*Initialisation des points totaux,de la rank et du nombre de tour*/
    for (i=0 ; i<nb_player ; i++)
    {
        ptr_csu_struct->total_points[i]=ptr_csu_struct->config.begin_score;
        ptr_csu_struct->rank[i]=1;
        ptr_csu_struct->nb_turn[i]=0;
    }

    /*Allocation memoire du tableau de points*/
    ptr_csu_struct->point=(float **)myAlloc(ptr_csu_struct->nb_player*sizeof(float*));
    for (i=0 ; i<nb_player ; i++)
        ptr_csu_struct->point[i]=(float*)myAlloc(0*sizeof(float));

    /*Enregistrement de la date courante dans la structure*/
    timestamp = time(NULL);
    t = localtime(&timestamp);
    ptr_csu_struct->year=(t->tm_year+1900);
    ptr_csu_struct->month=(t->tm_mon+1);
    ptr_csu_struct->day=(t->tm_mday);

    return ptr_csu_struct;
}

/*!
 * \fn void closeCsuStruct(csuStruct *ptr_csu_struct)
 *  Desalloue la memoire attribuee a la structure csuStruct mis en parametre
 * \param[in,out] *ptr_csu_struct un pointeur sur la structure csuStruct a fermer
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
 * \fn void startNewTurn(csuStruct *ptr_csu_struct)
 *  Realloue l'espace memoire dedie au points sur la structure csuStruct mis en parametre pour un nouveau tour
 * \param[in,out] *ptr_csu_struct un pointeur sur la structure csuStruct
 * \param[in,out] index_player le numero du joueur qui va commencer un nouveau tour, vaut -1 si c'est tout le monde
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
 * \fn void endNewTurn(csuStruct *ptr_csu_struct)
 *  Met a day les points totaux, le nombre de tour, la personne qui doit distributorr et les ranks pour un nouveau tour
 * \param[in,out] *ptr_csu_struct un pointeur sur la structure csuStruct
 * \param[in,out] index_player le numero du joueur qui va commencer un nouveau tour, vaut -1 si c'est tout le monde
 */
void endNewTurn(csuStruct *ptr_csu_struct, int index_player)
{
    int i;

    /*Mise a day des points totaux*/
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        ptr_csu_struct->total_points[i]+=ptr_csu_struct->point[i][(int)ptr_csu_struct->nb_turn[i]];
    }

    if (index_player == -1)
    {
        for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
            (ptr_csu_struct->nb_turn[i])++;
    }
    else
        (ptr_csu_struct->nb_turn[index_player])++;

    /*Mise a day de la personne qui doit distributor*/
    if (ptr_csu_struct->distributor == ptr_csu_struct->nb_player -1)
        ptr_csu_struct->distributor=0;
    else
        (ptr_csu_struct->distributor)++;

    rankCalculation(ptr_csu_struct);
}

/*!
 * \fn void rankCalculation(csuStruct *ptr_csu_struct)
 *  Calcule les ranks des joueurs
 * \param[in,out] *ptr_csu_struct un pointeur sur la structure csuStruct
 */
void rankCalculation(csuStruct *ptr_csu_struct)
{
    float *sort_points;
    int i;
    int j;

    /*Allocation memoire de sort_points*/
    sort_points=(float *)myAlloc(sizeof(float)*ptr_csu_struct->nb_player);

    /*Copie les pints totaux dans sort_points*/
    for(i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        sort_points[i]=ptr_csu_struct->total_points[i];
    }

    /*Trie sort_points en fonction du sens du premier*/
    if(ptr_csu_struct->config.first_way == 1)
        qsort(sort_points,ptr_csu_struct->nb_player,sizeof(float),compareFloatDescending);
    else
        qsort(sort_points,ptr_csu_struct->nb_player,sizeof(float),compareFloatAscending);


    /*Boucle sur les points tries a partir du plus petit*/
    for(i=ptr_csu_struct->nb_player -1 ; i>=0 ; i--)
    {
        /*Boucle sur les points totaux des joueurs*/
        for(j=0 ; j<ptr_csu_struct->nb_player ; j++)
        {
            /*Si les points totaux sont egaux aux points trie, on enregistre la rank*/
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
 *  Ajoute la personne qui distributor dans la structure.
 * \param[in] *distributor_name le nom de la personne qui distributor
 * \param[in] *ptr_csu_struct la structure du fichier avec lequel on veut mettre la personne qui distributor
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
 *  Verifie si quelqu'un a depasse le score maximum
 * \param[in] *ptr_csu_struct la structure du fichier
 * \return TRUE s'il y a un depassement, FALSE sinon
 */
int exceedMaxNumber(csuStruct *ptr_csu_struct)
{
    int i;
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        if (ptr_csu_struct->config.max == 1)
        {
            if (ptr_csu_struct->total_points[i] + FLT_EPSILON >= ptr_csu_struct->config.nb_max)
                return TRUE;
        }
        else
        {
            if (ptr_csu_struct->total_points[i] - FLT_EPSILON <= ptr_csu_struct->config.nb_max)
                return TRUE;
        }

    }
    return FALSE;
}

/*!
 * \fn int maxNbTurn(csuStruct *ptr_csu_struct)
 *  Cherche le maximum de nombre de tour
 * \param[in] *ptr_csu_struct la structure du fichier
 * \return le nombre maximum de nombre de tour
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
 *  Cherche l'indice du tableau dans lequel est stocke une personne.
 * \param[in] *distributor_name le nom de la personne
 * \param[in] *ptr_csu_struct la structure du fichier
 * \return l'indice du tableau, -1 si non trouve
 */
int searchPlayerIndex(csuStruct *ptr_csu_struct, char *player_name)
{
    int i;

    libcsuper_initialize();

    /*Recherche du nom de la personne dans le nom des joueurs*/
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        if (strncasecmp(ptr_csu_struct->player_names[i],player_name,strlen(player_name))==0)
            return i;
    }

    /*Message d'erreur si le nom n'est pas trouve*/
    printf(_("\nError this name doesn't exist.\n"));
    return -1;
}
