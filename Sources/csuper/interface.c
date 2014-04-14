/*!
 * \file    interface.c
 * \brief   Fonctions qui gerent l'interface graphique du logiciel
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

 /*
 * interface.c
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

 #include "interface.h"


/*!
 * \fn void displayFile()
 *  Demande le name d'un fichier et l'affiche
 */
void displayFile()
{
    char file_name[SIZE_MAX_FILE_NAME];
    csuStruct *ptr_csu_struct;

    clearScreen();

    menuFileName(file_name);

    if(readSystemPath(file_name)==FALSE)
        return;

    ptr_csu_struct=readCsuFile(file_name);

    /*Si le fichier a bien ete lu affiche et ferme la structure*/
    if (ptr_csu_struct != NULL)
    {
        printCsuStruct(ptr_csu_struct);

        if(exceedMaxNumber(ptr_csu_struct))
        {
            printGameOver(ptr_csu_struct);
        }

        closeCsuStruct(ptr_csu_struct);
    }

    systemPause();
}

/*!
 * \fn void deleteCsuFileNom()
 *  Demande le name d'un fichier et le deleteime
 */
void deleteCsuFileNom()
{
    char file_name[SIZE_MAX_FILE_NAME];

    clearScreen();
    menuFileName(file_name);

    if(readSystemPath(file_name)==FALSE)
        return;

    deleteCsuFile(file_name);
    systemPause();
}

/*!
 * \fn void listCsuFiles()
 *  Liste tout les fichier du dossier courant contenant l'extension .jeu
 */
void listCsuFiles()
{
    struct dirent *lecture;
    DIR *rep;
    char jeu[4]=FILE_EXTENSION;
    char ext[4]="abc";
    char folder[SIZE_MAX_FILE_NAME]=".";
    int i;

    clearScreen();

    if(readSystemPath(folder)==FALSE)
        return;

    /*Lecture du folder*/
    rep = opendir(folder);

    printf("Voici tout vos fichiers de jeu :\n");

    /*Affichage du name de tout les fichiers du folder*/
    while ((lecture = readdir(rep))) {
        /*Initialisation de ext*/
        for (i=0 ; i<3 ; i++)
            ext[i]='a';

        /*Lecture de l'extension du fichier courant*/
        for (i=strlen(lecture->d_name)-3 ; i<strlen(lecture->d_name) ; i++)
            ext[-strlen(lecture->d_name)+i+3]=lecture->d_name[i];

        /*Si l'extension est celle d'un fichier jeu, on l'affiche*/
        if (strcmp(jeu,ext)==0)
            printf("\t- %s\n", lecture->d_name);
    }

    closedir(rep);
    systemPause();
}

/*!
 * \fn void play(csuStruct *ptr_csu_struct, char *file_name)
 *  Lance la partie de comptage jusqu'a la fin
 * \param[in,out] *ptr_csu_struct la structure csuStruct
 * \param[in] *file_name le name du fichier dans lequel on stocke les informations
 */
void play(csuStruct *ptr_csu_struct, char *file_name)
{
    int continuer=FALSE;

    clearScreen();
    printPoints(ptr_csu_struct);

    /*Fait compter les points*/
    do
    {
        menuPlayersPoints(ptr_csu_struct);

        /*Ecrit le nouveau score sur le fichier et verifie si l'ecriture du fichier s'est bien passe*/
        if (!writeFileNewTurn(file_name,ptr_csu_struct))
            systemPause();

        clearScreen();
        printPoints(ptr_csu_struct);

        if (exceedMaxNumber(ptr_csu_struct))
            continuer=FALSE;

        else
            continuer=menuContinue();

    } while (continuer==TRUE);

    printGameOver(ptr_csu_struct);

    if (menuDelete())
    {
        deleteCsuFile(file_name);
        systemPause();
    }

    clearScreen();
    printCsuStruct(ptr_csu_struct);
    closeCsuStruct(ptr_csu_struct);
    systemPause();
}

/*!
 * \fn void newGame()
 *  Initialise une nouvelle partie et lance la fonction de comptage des points
 */
void newGame()
{
    csuStruct *ptr_csu_struct;
    float nb_players;
    game_config config;
    int writting_file;
    char distributor_name[SIZE_MAX_NAME];
    char file_name[SIZE_MAX_FILE_NAME];

    clearScreen();
    menuFileName(file_name);

    if(readSystemPath(file_name)==FALSE)
        return;

    menuStartGame(&nb_players,&config);

    ptr_csu_struct=newCsuStruct(nb_players,config);
    menuPlayersName(ptr_csu_struct);

    if (config.use_distributor)
    {
        menuDistributor(distributor_name);
        addDistributorCsuStruct(ptr_csu_struct,distributor_name);
    }

    writting_file=writeCsuFile(file_name,ptr_csu_struct);

    systemPause();

    if (writting_file)
        play(ptr_csu_struct,file_name);
    else
        closeCsuStruct(ptr_csu_struct);
}

/*!
 * \fn void loadGame()
 *  Charge une partie a partir d'un fichier et lance la fonction de comptage des points
 */
void loadGame()
{
    csuStruct *ptr_csu_struct;
    char file_name[SIZE_MAX_FILE_NAME];

    clearScreen();
    menuFileName(file_name);

    if(readSystemPath(file_name)==FALSE)
        return;

    ptr_csu_struct=readCsuFile(file_name);

    if (ptr_csu_struct == NULL)
    {
        systemPause();
        return;
    }

    printCsuStruct(ptr_csu_struct);

    if(exceedMaxNumber(ptr_csu_struct))
    {
        printGameOver(ptr_csu_struct);
        systemPause();
    }

    else
    {
        systemPause();
        play(ptr_csu_struct,file_name);
    }
}

/*!
 * \fn void mainMenu()
 *  Lance un menu que redirige vers l'action que l'on veut effectuer
 */
void mainMenu()
{
    int choice;
    int stop = FALSE;

    do
    {
        choice=-1;

        clearScreen();

        printf("Csuper - Compteur de Score Universel Permettant l'Exemption de Reflexion v2.1.8\n\nQue voulez vous faire ?\n "
        "(%d) Faire une nouvelle partie \n (%d) Charger une partie existente \n (%d) Afficher les resultats d'une partie existante "
        "\n (%d) Supprimer une partie \n (%d) Afficher toutes les parties existantes",nouvPart,charPart,affFich,deleteFich,listFich);
        printf("\n (%d) Afficher le menu des preferences \n (%d) Quitter le programme\n\nVotre choice : ",pref,quit);

        intKey(&choice);

        switch (choice) {
            case nouvPart  :    newGame();
                                break;
            case charPart  :    loadGame();
                                break;
            case affFich  :     displayFile();
                                break;
            case deleteFich  :   deleteCsuFileNom();
                                break;
            case listFich  :    listCsuFiles();
                                break;
            case pref :         preferencesMenu();
                                break;
            case quit  :        printf("\nVous avez choisi de quitter le programme.\n\n");
                                stop=TRUE;
                                break;
            case easterEggs :   printf("\nEffectivement c'est la bonne reponse mais ca ne m'aide pas a savoir ce que vous voulez faire.\n");
                                systemPause();
                                break;
            default :           wrongChoice();
                                systemPause();
        }

        clearScreen();

	} while (stop==FALSE);
}

void preferencesMenu()
{
    int choice;
    int stop = FALSE;

    do
    {
        choice=-1;

        clearScreen();

        printf(_("\nWhat do you want to do ?\n"));
        #ifndef PORTABLE
        printf(" \n (%d) Choisir un nouveau dossier d'enregistrement des fichiers \n (%d) Affiche le dossier d'enregistrement des fichiers",nouvChem,lireChem);
        #endif
        printf("\n (%d) Faire une nouvelle configuration de jeu\n (%d) Supprimer une configuration de jeu",newGameConf,removeGameConf);
        printf("\n (%d) Afficher la liste des configurations de jeu\n (%d) Afficher une configuration de jeu",printListGameConf,printGameConf);
        printf("\n (%d) Revenir au menu principal\n\nVotre choice : ",menuPrinc);

        intKey(&choice);

        switch (choice) {
            #ifndef PORTABLE
            case nouvChem   :   changeFilePath();
                                break;
            case lireChem :     readFilePath();
                                break;
            #endif
            case menuPrinc  :   printf("\nVous avez choisi de quitter le programme.\n\n");
                                stop=TRUE;
                                break;
            case newGameConf :  newGameConfig();
                                break;
            case removeGameConf:removeGameConfig();
                                break;
            case printListGameConf:printListGameConfig();
                                break;
            case printGameConf: printGameConfigFile();
                                break;
            case easterEggs2 :  printf("\nEffectivement c'est la bonne reponse mais ca ne m'aide pas a savoir ce que vous voulez faire.\n");
                                systemPause();
                                break;
            default :           wrongChoice();
                                systemPause();
        }

        clearScreen();

	} while (stop==FALSE);
}

/*!
 * \fn void changeFilePath()
 *  Charge un nouveau path que l'on demande a l'utilisateur
 */
void changeFilePath()
{
    char new_path[SIZE_MAX_FILE_NAME];

    clearScreen();

    menuNewPath(new_path);
    changeSystemPath(new_path);

    systemPause();
}

/*!
 * \fn void readFilePath()
 *  Lis le path de fichier et l'affiche
 */
void readFilePath()
{
    char path[SIZE_MAX_FILE_NAME]="";

    clearScreen();

    readSystemPath(path);

    printf("Vos fichiers sont sauvegardes dans %s\n",path);
    systemPause();
}

/*!
 * \fn void loadGameLocale(char *file_name)
 *  Charge une partie a partir d'un fichier dont le name a ete donne et lance la fonction de comptage des points
 * \param[in] file_name, le name du fichier
 */
void loadGameLocale(char *file_name)
{
    csuStruct *ptr_csu_struct;

    clearScreen();

    ptr_csu_struct=readCsuFile(file_name);

    if (ptr_csu_struct == NULL)
    {
        systemPause();
        return;
    }

    printCsuStruct(ptr_csu_struct);

    if(exceedMaxNumber(ptr_csu_struct))
    {
        printGameOver(ptr_csu_struct);
        systemPause();
    }

    else
    {
        systemPause();
        play(ptr_csu_struct,file_name);
    }
}

/*!
 * \fn void displayFileLocale(char *file_name)
 *  Affiche le fichier dont le name a ete donne en parametre
 */
void displayFileLocale(char *file_name)
{
    csuStruct *ptr_csu_struct;

    clearScreen();

    ptr_csu_struct=readCsuFile(file_name);

    /*Si le fichier a bien ete lu affiche et ferme la structure*/
    if (ptr_csu_struct != NULL)
    {
        printCsuStruct(ptr_csu_struct);

        if(exceedMaxNumber(ptr_csu_struct))
        {
            printGameOver(ptr_csu_struct);
        }

        closeCsuStruct(ptr_csu_struct);
    }

    systemPause();
}

/*!
 * \fn void newGameConfig()
 *  Add a new game configuration
 */
void newGameConfig()
{
    game_config config;

    clearScreen();
    menuFileName(config.name);
    menuGameConfig(&config);
    newConfigFile(config);
}

/*!
 * \fn void removeGameConfig()
 *  Ask and remove a game configuration
 */
void removeGameConfig()
{
    int i;
    int game_config_choice;
    list_game_config *ptr_list_config;

    clearScreen();


    ptr_list_config = readConfigListFile();
    if (ptr_list_config->nb_config > 0)
    {
        /*Affichage des diffrentes configurations*/
        printf("\nQuelle configuration voulez vous utilisez ?\n");
        for (i=0 ; i<ptr_list_config->nb_config ; i++)
            printf("(%d) %s\n",i+1,ptr_list_config->name_game_config[i]);

        /*Demande du choice*/
        do
        {
            printf("\nVotre choice : ");
            intKey(&game_config_choice);
            printf("Vous avez choisi %d\n",game_config_choice);
        } while (game_config_choice <1 || game_config_choice >i);

        removeConfigListFile(game_config_choice-1,ptr_list_config);
    }

    else
        printf("\nVous n'avez pas encore de fichiers de configurations de jeu.\n");

    systemPause();
}

/*!
 * \fn void printListGameConfig()
 *  Print the list of game configuration
 */
void printListGameConfig()
{
    int i;
    list_game_config *ptr_list_config;

    clearScreen();

    ptr_list_config = readConfigListFile();
    printf("\nVoici la liste des configurations de jeu :\n");
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
        printf("(%d) %s\n",i+1,ptr_list_config->name_game_config[i]);
    systemPause();
}

/*!
 * \fn void printGameConfig()
 *  Ask and print a game configuration
 */
void printGameConfigFile()
{
    int i;
    int game_config_choice;
    list_game_config *ptr_list_config;
    game_config config;

    clearScreen();

    /*Affichage des diffrentes configurations*/
    ptr_list_config = readConfigListFile();
    if (ptr_list_config->nb_config > 0)
    {
        printf("\nQuelle configuration voulez vous utilisez ?\n");
        for (i=0 ; i<ptr_list_config->nb_config ; i++)
            printf("(%d) %s\n",i+1,ptr_list_config->name_game_config[i]);

        /*Demande du choice*/
        do
        {
            printf("\nVotre choice : ");
            intKey(&game_config_choice);
            printf("Vous avez choisi %d\n",game_config_choice);
        } while (game_config_choice <1 || game_config_choice >i);

        readConfigFile(game_config_choice-1,ptr_list_config,&config);
        printGameConfig(config);
    }

    else
        printf("\nVous n'avez pas encore de fichiers de configurations de jeu.\n");

    systemPause();
}
