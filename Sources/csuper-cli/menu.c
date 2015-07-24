/*!
 * \file    menu.c
 * \brief   Menu functions
 * \author  Remi BERTHO
 * \date    01/09/14
 * \version 4.2.0
 */

 /*
 * menu.c
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
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

 #include "menu.h"

/*!
 * \fn char *menuFileName(char file_name[SIZE_MAX_FILE_NAME])
 *  Ask and save the filename.
 * \param[in,out] file_name the filename
 * \return the filename
 */
char *menuFileName(char file_name[SIZE_MAX_FILE_NAME])
{
    char test_filename[SIZE_MAX_FILE_NAME/8];

    do
    {
        printf(_("Give a name to the file with at most %d characters.\nYour choice: "),SIZE_MAX_FILE_NAME/8);
        stringKey(test_filename,SIZE_MAX_FILE_NAME/8);
        printf(_("You choose %s\n"),test_filename);
        strcpy(file_name,test_filename);
        #ifndef PORTABLE
        readSystemPath(test_filename);
        #endif // PORTABLE
    } while (checkFilename(test_filename,"") == false);

    return file_name;
}

/*!
 * \fn void menuStartGame(float *ptr_nb_player, game_config *ptr_config)
 *  Ask and save the number of player and all the informations of a game configuration.
 * \param[in,out] ptr_nb_player the number of player
 * \param[in,out] ptr_config the game configuration
 */
void menuStartGame(float *ptr_nb_player, game_config *ptr_config)
{
    int i;
    int game_config_choice;
    list_game_config *ptr_list_config;
    char home_path[SIZE_MAX_FILE_NAME]="";

    /*Number of player*/
    do
    {
        printf(_("\nGive the number of players in the game (>0).\nYour choice: "));
        floatKeyNoComma(ptr_nb_player);
        printf(_("You chose %.0f\n"),*ptr_nb_player);
    } while (*ptr_nb_player <= 0);

    /*Display the different game configurations*/
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);
    printf(_("\nWhich game configuration would you like to use?\n"));
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
        printf(_("(%d) %s\n"),i+1,ptr_list_config->name_game_config[i]);
    printf(_("(%d) Other\n"),i+1);

    /*Ask which one will be chose*/
    do
    {
        printf(_("\nYour choice: "));
        intKey(&game_config_choice);
        printf(_("You chose %d\n"),game_config_choice);
    } while (game_config_choice <1 || game_config_choice >i+1);

    /*Read a game configuration or create it*/
    if (game_config_choice <= i)
        readConfigFile(game_config_choice-1,ptr_list_config,ptr_config,home_path);
    else
    {
        menuGameConfig(ptr_config);
        strcpy(ptr_config->name,_("Unknown"));
    }

    closeListGameConfig(ptr_list_config);
}

/*!
 * \fn void menuGameConfig(game_config *ptr_config)
 *  Ask and save a game configuration.
 * \param[in,out] ptr_config a game configuration
 */
void menuGameConfig(game_config *ptr_config)
{
    char nbmax;
    char max;
    char first_max;
    char turn;
    char distrib;
    int comma;

    /*Maximum number*/
    printf(_("\nWould you like to use a maximum or a minimum score (Y/n): "));
    charKey(&nbmax);
    if (nbmax=='n' || nbmax=='N')
    {
        ptr_config->nb_max  =  INFINITY;
        ptr_config->max = 1;
    } else
    {
        /*Maximum or minimum*/
        printf(_("\nWould you like to use a maximum score (Y/n): "));
        charKey(&max);
        if (max=='n' || max == 'N')
            ptr_config->max=0;
        else
            ptr_config->max=1;

        /*Number maximum or minimum.*/
        printf(_("\nGive the maximal or minimal score which a player can reach in the game."
        "\nYour choice: "));
        floatKey(&(ptr_config->nb_max));
        printf(_("You chose %.3f\n"),ptr_config->nb_max);
    }

    /*Score at the beginning*/
    printf(_("\nGive the initial score of the players.\nYour choice: "));
    floatKey(&(ptr_config->begin_score));
    printf(_("You chose %.3f\n"),ptr_config->begin_score);

    /*First way*/
    printf(_("\nThe winner is the player who has the highest score (Y/n): "));
    charKey(&first_max);
    if (first_max=='n' || first_max == 'N')
        ptr_config->first_way=-1;
    else
        ptr_config->first_way=1;

    /*Turn by turn*/
    printf(_("\nThis is a turn-based game (Y/n): "));
    charKey(&turn);
    if (turn=='n' || turn == 'N')
        ptr_config->turn_based=0;
    else
        ptr_config->turn_based=1;

    /*Distributor*/
    printf(_("\nA distributor is used (Y/n): "));
    charKey(&distrib);
    if (distrib=='n' || distrib == 'N')
        ptr_config->use_distributor=0;
    else
        ptr_config->use_distributor=1;

    /*Number of decimal place.*/
    do
    {
        printf(_("\nGive the number of decimals displayed. This number must be between 0 and 3.\nYour choice: "));
        intKey(&comma);
        printf(_("You chose %.0d\n"),comma);
    } while (comma < 0 || comma > 3);
    ptr_config->decimal_place=comma;
}

/*!
 * \fn void menuDistributor(char *distributor_name)
 *  Ask and save the distributor.
 * \param[in,out] *distributor_name the name of the distributor.
 */
void menuDistributor(char *distributor_name)
{
    printf(_("\nGive the name (or the first letters of the name) of the person who will distribute first.\nYour choice: "));
    stringKey(distributor_name,SIZE_MAX_NAME);
    printf(_("You chose %s\n"),distributor_name);
}

/*!
 * \fn void menuPlayersName(csuStruct *ptr_csu_struct)
 *  Ask and save the name of the players.
 * \param[in,out] *ptr_csu_struct a pointer on a csu structure
 */
void menuPlayersName(csuStruct *ptr_csu_struct)
{
    int i;
    char name[SIZE_MAX_NAME];

    printf(_("\nThe players' names must have between 2 and %.0f characters and mustn't include any special character.\n"),ptr_csu_struct->size_max_name-1);

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        do
        {
            printf(_("\nGive the name of the %dth person: "),i+1);
            stringKey(name,SIZE_MAX_NAME);
            printf(_("You chose %s\n"),name);
        } while (strlen(name) <2 || strlen(name) > ptr_csu_struct->size_max_name);

        strncpy(ptr_csu_struct->player_names[i],name,SIZE_MAX_NAME-1);
    }
}

/*!
 * \fn void menuPlayersPoints(csuStruct *ptr_csu_struct)
 *  Begin a new turn, ask and save the new points and finish the turn
 * \param[in,out] *ptr_csu_struct a pointer on a csu structure
 */
void menuPlayersPoints(csuStruct *ptr_csu_struct)
{
    int i;
    int validation;
    char valid;
    int index_player;
    float total=0;

    if (ptr_csu_struct->config.turn_based == 1)
        index_player = -1;
    else
        index_player = menuPlayerIndex(ptr_csu_struct);

    startNewTurn(ptr_csu_struct,index_player);

    do
    {
        validation=true;

        if (ptr_csu_struct->config.turn_based == 1)
        {
            for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
            {
                printf(_("\nGive the points of %s : "),ptr_csu_struct->player_names[i]);
                floatKey(&(ptr_csu_struct->point[i][(int)ptr_csu_struct->nb_turn[i]]));
                printf(_("You chose %.3f\n"),ptr_csu_struct->point[i][(int)ptr_csu_struct->nb_turn[i]]);
                total += ptr_csu_struct->point[i][(int)ptr_csu_struct->nb_turn[i]];
                printf(_("\nTotal number of points distributed in that turn: %.3f\n"),total);
            }
        } else
        {
            printf(_("\nGive their points: "));
            floatKey(&(ptr_csu_struct->point[index_player][(int)ptr_csu_struct->nb_turn[index_player]]));
            printf(_("You chose %.3f\n"),ptr_csu_struct->point[index_player][(int)ptr_csu_struct->nb_turn[index_player]]);
        }

        printf(_("\nDo you confirm these scores (Y/n)? "));
        charKey(&valid);

        if (valid=='n' || valid=='N')
            validation = false;

    } while (!validation);

    endNewTurn(ptr_csu_struct,index_player);
}

/*!
 * \fn int menuPlayerIndex(csuStruct *ptr_csu_struct)
 *  Ask a player name and save his index
 * \param[in,out] *ptr_csu_struct a pointer on a csu structure
 */
int menuPlayerIndex(csuStruct *ptr_csu_struct)
{
    char name[SIZE_MAX_NAME];
    int index_player;

    do
    {
        printf(_("\nGive the name (or the first letters of the name) of the person who will earn points.\nYour choice: "));
        stringKey(name,SIZE_MAX_NAME);
        printf(_("You chose %s\n"),name);
    } while ((index_player = searchPlayerIndex(ptr_csu_struct,name)) == -1);

    return index_player;
}

/*!
 * \fn ContinueChangeDistributorOrQuit menuContinueChangeDistributorOrQuit()
 *  Ask if we want to continue
 * \return a ContinueChangeDistributorOrQuit
 */
ContinueChangeDistributorOrQuit menuContinueChangeDistributorOrQuit()
{
    char choice;

    printf(_("\nWhat do you want to do?\n (%d) Continue the game (default)\n (%d) Change the distributor and continue the game"
             "\n (%d) Stop the game\nYour choice: "),1,2,3);
    charKey(&choice);

    if (choice=='2' || choice=='2')
        return ChangeDistributor;

    if (choice=='3' || choice=='3')
        return Quit;

    return Continue;
}

/*!
 * \fn void menuChangeDistributor(csuStruct *ptr_csu_struct)
 *  Ask and validate the new distributor
 * \param[in,out] *ptr_csu_struct a pointer on a csu structure
 */
void menuChangeDistributor(csuStruct *ptr_csu_struct)
{
    int i;
    int choice;

    do
    {
        printf(_("\nChoose the new disributor\n"));
        for(i=0 ; i<ptr_csu_struct->nb_player ; i++)
            printf(_("(%d) %s\n"),i+1,ptr_csu_struct->player_names[i]);
        printf(_("Your choice: \n"));
        intKey(&choice);
    } while (choice < 1 || choice > ptr_csu_struct->nb_player);

    changeDistributor(ptr_csu_struct,choice-1);
}

/*!
 * \fn bool menuDelete()
 *  Ask if we want to delete a file.
 * \return true if we want to deleted the file, false otherwise
 */
bool menuDelete()
{
    char delete;

    printf(_("\nWould you like to delete the file (y/N)? "));
    charKey(&delete);

    if (delete=='o' || delete=='O' || delete == 'y' || delete == 'Y')
        return true;

    return false;
}

/*!
 * \fn void menuNewPath(char *new_path)
 *  Ask and save the new path
 * \param[in,out] *new_path the new path
 */
void menuNewPath(char *new_path)
{
    int verif=false;

    do
    {
        printf(_("\nGive the new folder in which you would like to save your files\nCheck "
                 "if the folder exists and if you have the read and write rights.\n\nYour choice: "));
        stringKey(new_path,SIZE_MAX_FILE_NAME);

        /*Check if the path is valid*/
        verif = checkPath(new_path);

    } while (verif == false);

    printf(_("You chose %s\n"),new_path);
}

/*!
 * \fn bool menuExportListGameConfig(int **id,int *nb_id)
 *  Choose the game configuration which will be exported
 * \param[in] id the id of the game configuration which will be exported
 * \param[in] nb_id the number of game configuration which will be exported
 * \return true if there is no problem, false otherwise
 */
bool menuExportListGameConfig(int **id,int *nb_id)
{
    int i;
    list_game_config *ptr_list_config;
    char home_path[SIZE_MAX_FILE_NAME]="";

    clearScreen();

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);
    if (ptr_list_config == NULL)
        return false;
    printf(_("\nHere are all your game configurations:\n"));
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
        printf("(%d) %s\n",i,ptr_list_config->name_game_config[i]);

    do
    {
        printf(_("\nGive the number of game configuration you want to export or -1 if you want to export all of them.\nYour choice: "));
        intKey(nb_id);
    } while (*nb_id < -1 || *nb_id > ptr_list_config->nb_config || *nb_id == 0);

    if (*nb_id != -1)
    {
        *id = (int*)myAlloc(*nb_id * sizeof(int));
        for (i=0 ; i<*nb_id ; i++)
        {
            do
            {
                printf(_("\nGive the id of the %dth configuration you want to export.\nYour choice: "),i);
                intKey(*id+i);
                printf(_("You chose %d\n"),(*id)[i]);
            } while ((*id)[i] <0 || (*id)[i] >= ptr_list_config->nb_config);
        }
    }
    else
    {
        *id = (int*)myAlloc(ptr_list_config->nb_config * sizeof(int));
        *nb_id = ptr_list_config->nb_config;
        for (i=0 ; i< ptr_list_config->nb_config ; i++)
            (*id)[i]=i;
    }

    closeListGameConfig(ptr_list_config);

    return true;
}

/*!
 * \fn bool menuImportListGameConfig(int **id,int *nb_id,char *filename)
 *  Choose the game configuration which will be imported
 * \param[in] filename the filename of the imported file.
 * \param[in] id the id of the game configuration which will be imported
 * \param[in] nb_id the number of game configuration which will be imported
 * \return true if there is no problem, false otherwise
 */
bool menuImportListGameConfig(int **id,int *nb_id,char *filename)
{
    int i;
    list_game_config *ptr_list_config;

    clearScreen();

    ptr_list_config = newListGameConfigFromImport(filename);
    if (ptr_list_config == NULL)
        return false;
    printf(_("\nHere are all the game configurations in this file:\n"));
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
        printf("(%d) %s\n",i,ptr_list_config->name_game_config[i]);

    do
    {
        printf(_("\nGive the number of game configuration you want to import or -1 if you want to import all of them.\nYour choice: "));
        intKey(nb_id);
    } while (*nb_id < -1 || *nb_id > ptr_list_config->nb_config);

    if (*nb_id != -1)
    {
        *id = (int*) myAlloc(*nb_id * sizeof(int));
        for (i=0 ; i<*nb_id ; i++)
        {
            do
            {
                printf(_("\nGive the id of the %dth configuration you want to import.\nYour choice: "),i);
                intKey(*id+i);
                printf(_("You chose %d\n"),(*id)[i]);
            } while ((*id)[i] <0 || (*id)[i] >= ptr_list_config->nb_config);
        }
    }
    else
    {
        *id = (int*) myAlloc(ptr_list_config->nb_config * sizeof(int));
        *nb_id = ptr_list_config->nb_config;
        for (i=0 ; i< ptr_list_config->nb_config ; i++)
            (*id)[i]=i;
    }

    closeListGameConfig(ptr_list_config);

    return true;
}


/*!
 * \fn void menuPdfPreferences(export_pdf_preferences *pref)
 *  Fill a export pdf preferences structure
 * \param[in] pref a pointer on a export_pdf_preferences
 */
void menuPdfPreferences(export_pdf_preferences *pref)
{
    clearScreen();

    char choice;
    int nb;

    // Charset
    if (canUseUtf8Pdf())
    {
        printf(_("The UTF-8 character set permit to display all the character with the cost of bigger pdf file.\n\nWould you like to use the UTF-8 character set (y/N)? "));
        charKey(&choice);
        if (choice=='Y' || choice == 'y')
            pref->charset = UTF8;
        else
            pref->charset = ISO885915;
    }

    // Direction
    printf(_("\n\nWhat page direction of the page do you want?\n (1) Portrait (default)\n (2) Landscape\nYour choice: "));
    charKey(&choice);
    if (choice=='2' || choice=='2')
        pref->direction = HPDF_PAGE_LANDSCAPE;
    else
        pref->direction = HPDF_PAGE_PORTRAIT;

    // Size
    printf(_("\n\nWhat size of page do you want?\n (1) A3\n (2) A4 (default)\n (3) A5 \nYour choice: "));
    charKey(&choice);
    if (choice=='1')
        pref->size = HPDF_PAGE_SIZE_A3 ;
    else if (choice=='3')
        pref->size = HPDF_PAGE_SIZE_A5;
    else
        pref->size = HPDF_PAGE_SIZE_A4;

    // Margin
    do
    {
        printf(_("\nGive the margin you want or -1 if want to keep the old one (%d). It will be between 0 and 200.\nYour choice: "),pref->margin);
        intKey(&nb);
    } while (nb < -1 || nb > 200);
    if (nb != -1)
        pref->margin = nb;

    // Font size
    do
    {
        printf(_("\nGive the font size you want or -1 if want to keep the old one (%d). It will be between 4 and 40.\nYour choice: "),pref->font_size);
        intKey(&nb);
    } while ((nb < 4 || nb > 40) && nb != -1);
    if (nb != -1)
        pref->font_size = nb;

    // Total points by turn
    printf(_("\nWould you like to display the total points in each turn (y/N)? "));
    charKey(&choice);
    if (choice=='Y' || choice == 'y')
        pref->total_points_turn = true;
    else
        pref->total_points_turn = false;

    // Ranking by turn
    printf(_("\nWould you like to display the ranking in each turn (y/N)? "));
    charKey(&choice);
    if (choice=='Y' || choice == 'y')
        pref->ranking_turn = true;
    else
        pref->ranking_turn = false;

    // Pdf size for chart
    printf(_("\nWould you like to use the pdf size for the pdf chart (y/N)? "));
    charKey(&choice);
    if (choice=='Y' || choice == 'y')
        pref->pdf_size_for_chart = true;
    else
        pref->pdf_size_for_chart = false;
}


/*!
 * \fn FileType menuChooseExportFileType()
 *  Choose the file type which will be exported
 */
FileType menuChooseExportFileType()
{
    char choice;

    printf(_("\nIn what file type would you like to export?\n "
             "(1) PDF file (default)\n (2) CSV file\n (3) Gnuplot files\n"
             " (4) m files (octave/matlab file)\nYour choice: "));
    charKey(&choice);
    if (choice=='2')
        return csv_file;
    else if (choice=='3')
        return gnuplot_file;
    else if (choice=='4')
        return m_file;
    else
        return pdf_file;
}
