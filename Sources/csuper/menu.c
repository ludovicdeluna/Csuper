/*!
 * \file    menu.c
 * \brief   Fonctions qui gerent les menus demandant de rentrer des valeurs du logiciel
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

 /*
 * menu.c
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

 #include "menu.h"

/*!
 * \fn char *menuFileName(char file_name[SIZE_MAX_FILE_NAME])
 *  Demande et enregistre le name du fichier
 * \param[in,out] file_name la string de caractere contenant le name du fichier
 * \return la string de caractere contenant le name du fichier
 */
char *menuFileName(char file_name[SIZE_MAX_FILE_NAME])
{
    printf(_("Give the name of the file with at the most %d characters.\nYour choice : "),SIZE_MAX_FILE_NAME-1);
    stringKey(file_name,SIZE_MAX_FILE_NAME);
    printf("Vous avez choisi %s\n",file_name);

    return file_name;
}

/*!
 * \fn void menuStartGame(float *ptr_nb_player, game_config *ptr_config)
 *  Demande et enregistre le namebre de joueur, le namebre maximum et le name de la personne qui comme a distributorr
 * \param[in,out] ptr_nb_player le namebre de joueur
 * \param[in,out] ptr_config la configuration de la partie
 */
void menuStartGame(float *ptr_nb_player, game_config *ptr_config)
{
    int i;
    int game_config_choice;
    list_game_config *ptr_list_config;
    char home_path[SIZE_MAX_FILE_NAME]="";

    /*Nombre de joueur*/
    do
    {
        printf(_("\nGive the number of player in the game (>0).\nYour choice : "));
        floatKeyNoComma(ptr_nb_player);
        printf(_("You chose %.0f\n"),*ptr_nb_player);
    } while (*ptr_nb_player <= 0);

    /*Affichage des diffrentes configurations*/
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);
    printf(_("\nWhich game configuration would you want to use ?\n"));
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
        printf("(%d) %s\n",i+1,ptr_list_config->name_game_config[i]);
    printf(_("(%d) Other\n"),i+1);

    /*Demande du choix*/
    do
    {
        printf(_("\nYour choice : "));
        intKey(&game_config_choice);
        printf(_("You chose %d\n"),game_config_choice);
    } while (game_config_choice <1 || game_config_choice >i+1);

    /*Soit on lit une config, soit on en cree une*/
    if (game_config_choice <= i)
        readConfigFile(game_config_choice-1,ptr_list_config,ptr_config,home_path);
    else
    {
        closeListGameConfig(ptr_list_config);
        menuGameConfig(ptr_config);
        strcpy(ptr_config->name,_("Unknown"));
    }
}

/*!
 * \fn void menuGameConfig(game_config *ptr_config)
 *  Demande et enregistre la configuration de jeu
 * \param[in,out] ptr_config la configuration de la partie
 */
void menuGameConfig(game_config *ptr_config)
{
    char nbmax;
    char max;
    char first_max;
    char turn;
    char distrib;
    int comma;

    /*Nombre maximum*/
    printf(_("\nWould you want to use a maximum or minimum score (Y/n) : "));
    charKey(&nbmax);
    if (nbmax=='n' || nbmax=='N')
    {
        ptr_config->nb_max  =  INFINITY;
        ptr_config->max = 1;
    } else
    {
        /*Maximum or minimum*/
        printf(_("\nWould you want to use a maximum score (Y/n) : "));
        charKey(&max);
        if (max=='n' || max == 'N')
            ptr_config->max=0;
        else
            ptr_config->max=1;

        /*Recuperation du namebre maximale.*/
        printf(_("\nGive the maximal or minimal score which a player can reach in the game."
        "\nYour choice : "));
        floatKey(&(ptr_config->nb_max));
        printf(_("You chose %.3f\n"),ptr_config->nb_max);
    }

    /*Score au debut de la partie*/
    printf(_("\nGive the initial score of the players .\nYour choice: "));
    floatKey(&(ptr_config->begin_score));
    printf(_("You chose %.3f\n"),ptr_config->begin_score);

    /*Sens du premier*/
    printf(_("\nThe first is the player who have the higher score (Y/n) : "));
    charKey(&first_max);
    if (first_max=='n' || first_max == 'N')
        ptr_config->first_way=-1;
    else
        ptr_config->first_way=1;

    /*Tour par turn ou pas*/
    printf(_("\nThe points will be attribute in turn by turn (Y/n) : "));
    charKey(&turn);
    if (turn=='n' || turn == 'N')
        ptr_config->turn_by_turn=0;
    else
        ptr_config->turn_by_turn=1;

    /*Distributeur ou pas*/
    printf(_("\nWe use a distributor (Y/n) : "));
    charKey(&distrib);
    if (distrib=='n' || distrib == 'N')
        ptr_config->use_distributor=0;
    else
        ptr_config->use_distributor=1;

    /*Recuperation du namebre de chiffres apres la virgule.*/
    do
    {
        printf(_("\nGive the number of digit display after the comma. This number must be"
        " between 0 and 3\nYour choice : "));
        intKey(&comma);
        printf(_("You chose %.0d\n"),comma);
    } while (comma < 0 || comma > 3);
    ptr_config->number_after_comma=comma;
}

/*!
 * \fn void menuDistributor(char *distributor_name)
 *  Demande et enregistre le name de la personne qui comme a distributorr
 * \param[in,out] *distributor_name le name de la personne qui commence a distributorr
 */
void menuDistributor(char *distributor_name)
{
    printf(_("\nGive the name (or the firsts letters of the name) of the person who begin to distribute.\nYour choice : "));
    stringKey(distributor_name,SIZE_MAX_NAME);
    printf("Vous avez choisi %s\n",distributor_name);
}

/*!
 * \fn void menuPlayersName(csuStruct *ptr_csu_struct)
 *  Demande et enregistre le name des joueurs
 * \param[in,out] *ptr_csu_struct la structure csuStruct ou l'on veut enregistrer le name des joueurs
 */
void menuPlayersName(csuStruct *ptr_csu_struct)
{
    int i;
    char name[SIZE_MAX_NAME];

    printf(_("\nThe players's names must have between 2 and %.0f characters with no special characters.\n"),ptr_csu_struct->size_max_name);

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        do
        {
            printf(_("\nGive the name of the %dth person : "),i+1);
            stringKey(name,SIZE_MAX_NAME);
            printf(_("You chose %s\n"),name);
        } while (strlen(name) <2 || strlen(name) > ptr_csu_struct->size_max_name);

        strcpy(ptr_csu_struct->player_names[i],name);
    }
}

/*!
 * \fn void menuPlayersPoints(csuStruct *ptr_csu_struct)
 *  Debute un nouveau turn, demande et enregistre les points et fini le turn
 * \param[in,out] *ptr_csu_struct la structure csuStruct ou l'on veut faire un nouveau turn
 */
void menuPlayersPoints(csuStruct *ptr_csu_struct)
{
    int i;
    int validation;
    char valid;
    int index_player;

    if (ptr_csu_struct->config.turn_by_turn == 1)
        index_player = -1;
    else
        index_player = menuPlayerIndex(ptr_csu_struct);

    startNewTurn(ptr_csu_struct,index_player);

    do
    {
        validation=TRUE;

        /*Demande les points de tout les joueurs si l'on est en turn par turn*/
        if (ptr_csu_struct->config.turn_by_turn == 1)
        {
            for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
            {
                printf(_("\nGive the points of %s : "),ptr_csu_struct->player_names[i]);
                floatKey(&(ptr_csu_struct->point[i][(int)ptr_csu_struct->nb_turn[i]]));
                printf(_("You chose %.3f\n"),ptr_csu_struct->point[i][(int)ptr_csu_struct->nb_turn[i]]);
            }
        } else
        {
            printf(_("\nGive their points : "));
            floatKey(&(ptr_csu_struct->point[index_player][(int)ptr_csu_struct->nb_turn[index_player]]));
            printf(_("You chose %.3f\n"),ptr_csu_struct->point[index_player][(int)ptr_csu_struct->nb_turn[index_player]]);
        }

        printf(_("\nYou confirm these scores (Y/n) : "));
        charKey(&valid);

        if (valid=='n' || valid=='N')
            validation = FALSE;

    } while (!validation);

    endNewTurn(ptr_csu_struct,index_player);
}

/*!
 * \fn int menuPlayerIndex(csuStruct *ptr_csu_struct)
 *  Demande et enregistre le numero du joueur
 * \param[in,out] *ptr_csu_struct la structure csuStruct
 */
int menuPlayerIndex(csuStruct *ptr_csu_struct)
{
    char name[SIZE_MAX_NAME];
    int index_player;

    do
    {
        printf(_("\nGive the name (or the firsts letters of the name) of the person who will earn points.\nYour choice: "));
        stringKey(name,SIZE_MAX_NAME);
        printf(_("You chose %s\n"),name);
    } while ((index_player = searchPlayerIndex(ptr_csu_struct,name)) == -1);

    return index_player;
}

/*!
 * \fn int menuContinue()
 *  Demande si l'on veut continuer ou pas et l'enregistre dans la variable arret
 * \return TRUE si l'on veut continuer, FALSE sinon
 */
int menuContinue()
{
    char continuer;

    printf(_("\nWould you like to continue the game (Y/n) : "));
    charKey(&continuer);

    if (continuer=='n' || continuer=='N')
        return FALSE;

    return TRUE;
}

/*!
 * \fn int menuDelete()
 *  Demande si l'on veut deleteimer le fichier ou pas et l'enregistre dans la variable delete
 * \return TRUE si l'on veut deleteimer le fichier, FALSE sinon
 */
int menuDelete()
{
    char delete;

    printf(_("\nWould ou like to delete the file (y/N) : "));
    charKey(&delete);

    if (delete=='o' || delete=='O' || delete == 'y' || delete == 'Y')
        return TRUE;

    return FALSE;
}

/*!
 * \fn void menuNewPath(char *new_path)
 *  Demande et enregistre le nouveau chemin
 * \param[in,out] *new_path le nouveau chemin
 */
void menuNewPath(char *new_path)
{
    int verif=FALSE;
    FILE *ptr_file_test;
    char check_path[SIZE_MAX_FILE_NAME];

    do
    {
        /*Saisie clavier du nouveau chemin*/
        printf(_("\nGive the new folder which you would like to save your files.\nChech if the folder exist"
        " and that you have the read and write rights.\n\nYour choice: "));
        stringKey(new_path,SIZE_MAX_FILE_NAME);

        /*Creation d'un fichier test pour voir si le chemin est valide*/
        sprintf(check_path,"%s/test-chemin_fichier_csuper",new_path);
        ptr_file_test=openFile(check_path,"w+");

        /*Si le chemin est valide on deleteime le fichier creer et on valide la saisie*/
        if (ptr_file_test != NULL)
        {
            closeFile(ptr_file_test);
            remove(check_path);
            verif=TRUE;
        }

        else
            printf(_("\nError : this folder is not valid.\n"));

    } while (verif == FALSE);

    printf(_("You chose %s\n"),new_path);
}
