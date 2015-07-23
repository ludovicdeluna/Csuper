/*!
 * \file    interface.c
 * \brief   Graphical interface
 * \author  Remi BERTHO
 * \date    01/09/14
 * \version 4.2.0
 */

 /*
 * interface.c
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

 #include "interface.h"


/*!
 * \fn void displayFile()
 *  Ask a filename and display it.
 */
void displayFile()
{
    char file_name[SIZE_MAX_FILE_NAME];
    csuStruct *ptr_csu_struct;

    clearScreen();

    menuFileName(file_name);

    #ifndef PORTABLE
    if(readSystemPath(file_name)==false)
        return;
    #endif // PORTABLE

    ptr_csu_struct=readCsuFile(file_name);

    if (ptr_csu_struct != NULL)
    {
        printCsuStruct(ptr_csu_struct);

        if(exceedMaxNumber(ptr_csu_struct))
            printGameOver(ptr_csu_struct);

        closeCsuStruct(ptr_csu_struct);
    }

    systemPause();
}

/*!
 * \fn void deleteCsuFileNom()
 *  Ask a filename and deleted the file.
 */
void deleteCsuFileNom()
{
    char file_name[SIZE_MAX_FILE_NAME];

    clearScreen();
    menuFileName(file_name);
    addFileCsuExtension(file_name);

    #ifndef PORTABLE
    if(readSystemPath(file_name)==false)
        return;
    #endif // PORTABLE

    deleteFile(file_name);
    systemPause();
}

/*!
 * \fn void listCsuFiles()
 *  List all the files with csu extension
 */
void listCsuFiles()
{
    struct dirent *lecture;
    DIR *rep;
    char jeu[4]=FILE_EXTENSION_CSU;
    char ext[4]="abc";
    char folder[SIZE_MAX_FILE_NAME]=".";
    int i;

    clearScreen();

    #ifndef PORTABLE
    if(readSystemPath(folder)==false)
        return;
    #endif // PORTABLE

    rep = opendir(folder);

    printf(_("Here are all your csu files:\n"));

    while ((lecture = readdir(rep))) {
        for (i=0 ; i<3 ; i++)
            ext[i]='a';

        for (i=strlen(lecture->d_name)-3 ; i<strlen(lecture->d_name) ; i++)
            ext[-strlen(lecture->d_name)+i+3]=lecture->d_name[i];

        if (strcmp(jeu,ext)==0)
            printf("\t- %s\n", lecture->d_name);
    }

    closedir(rep);
    systemPause();
}

/*!
 * \fn void play(csuStruct *ptr_csu_struct, char *file_name)
 *  Count the points
 * \param[in,out] *ptr_csu_struct a pointer on a csu structure
 * \param[in] *file_name the filename
 */
void play(csuStruct *ptr_csu_struct, char *file_name)
{
    ContinueChangeDistributorOrQuit choice;
    bool continuer=true;

    clearScreen();
    printPoints(ptr_csu_struct);

    do
    {
        menuPlayersPoints(ptr_csu_struct);

        if (!writeFileNewTurn(file_name,ptr_csu_struct))
            systemPause();

        clearScreen();
        printPoints(ptr_csu_struct);

        if (exceedMaxNumber(ptr_csu_struct))
            continuer=false;

        else
        {
            choice=menuContinueChangeDistributorOrQuit();
            if (choice == Quit)
                continuer = false;
            if (choice == ChangeDistributor)
                menuChangeDistributor(ptr_csu_struct);
        }

    } while (continuer==true);

    printGameOver(ptr_csu_struct);

    if (menuDelete())
    {
        deleteFile(file_name);
        systemPause();
    }

    clearScreen();
    printCsuStruct(ptr_csu_struct);
    closeCsuStruct(ptr_csu_struct);
    systemPause();
}

/*!
 * \fn void newGame()
 *  Initialize a new game and run the play function.
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
    addFileCsuExtension(file_name);

    #ifndef PORTABLE
    if(readSystemPath(file_name)==false)
        return;
    #endif // PORTABLE

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
 *  Load a game from a file and run the play function.
 */
void loadGame()
{
    csuStruct *ptr_csu_struct;
    char file_name[SIZE_MAX_FILE_NAME];

    clearScreen();
    menuFileName(file_name);

    #ifndef PORTABLE
    if(readSystemPath(file_name)==false)
        return;
    #endif // PORTABLE

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
 *  Main menu of csuper.
 */
void mainMenu()
{
    int choice;
    int stop = false;

    do
    {
        choice=-1;

        clearScreen();

        printf(_("Csuper - Universal points counter allowing a dispense with reflection v"));
        printf(_("%s"),CSUPER_VERSION);
        printf(_("\n\nWhat do you want to do?\n "
            "(%d) Play a new game\n (%d) Load an existing game\n (%d) Display the results of an existing game"
            "\n (%d) Delete a game\n (%d) Display all existing games\n (%d) Export a file\n"
            " (%d) Display the preferences menu\n (%d) Quit the program\n\nYour choice : ")
            ,newMatch,loadMatch,printFile,deleteFiles,listFile,export_file,pref,quit);

        intKey(&choice);

        switch (choice) {
            case newMatch  :    newGame();
                                break;
            case loadMatch  :   loadGame();
                                break;
            case printFile  :   displayFile();
                                break;
            case deleteFiles  : deleteCsuFileNom();
                                break;
            case listFile  :    listCsuFiles();
                                break;
            case export_file  : exportCsu();
                                break;
            case pref :         preferencesMenu();
                                break;
            case quit  :        printf(_("\nSee you.\n"));
                                systemPause();
                                stop=true;
                                break;
            case easterEggs :   printf(_("\nYes, it's the correct answer, but that doesn't help me to know what you want to do.\n"));
                                systemPause();
                                break;
            default :           wrongChoice();
                                systemPause();
        }

        clearScreen();

	} while (stop==false);
}

/*!
 * \fn void preferencesMenu()
 *  Preferences menu of csuper.
 */
void preferencesMenu()
{
    int choice;
    int stop = false;

    do
    {
        choice=-1;

        clearScreen();

        printf(_("\nWhat do you want to do?\n"));
        #ifndef PORTABLE
        printf(_("\n (%d) Change the folder where files will be saved\n (%d) Display the folder where files will be saved"),newPath,readPath);
        #endif
        printf(_("\n (%d) Make a new game configuration\n (%d) Delete an existing game configuration"
        "\n (%d) Display the list of game configurations\n (%d) Display a game configuration"
        "\n (%d) Export game configurations\n (%d) Import game configurations\n (%d) Change pdf export preferences"
        "\n (%d) Back to main menu\n\nYour choice : ")
               ,newGameConf,removeGameConf,printListGameConf,printGameConf,exportGameConf,importGameConf,pdfPreferences,backMainMenu);

        intKey(&choice);

        switch (choice) {
            #ifndef PORTABLE
            case newPath   :   changeFilePath();
                                break;
            case readPath :     readFilePath();
                                break;
            #endif
            case backMainMenu  :   stop=true;
                                break;
            case newGameConf :  newGameConfig();
                                break;
            case removeGameConf:removeGameConfig();
                                break;
            case printListGameConf:printListGameConfig();
                                break;
            case printGameConf: printGameConfigFile();
                                break;
            case easterEggs2 :  printf(_("\nYes, it's the correct answer, but that doesn't help me to know what you want to do.\n"));
                                systemPause();
                                break;
            case exportGameConf:exportListGameConfig();
                                break;
            case importGameConf:importListGameConfig();
                                break;
            case pdfPreferences:changePdfPreferences();
                                break;
            default :           wrongChoice();
                                systemPause();
        }

        clearScreen();

	} while (stop==false);
}

/*!
 * \fn void changeFilePath()
 *  Change the path which the file are saved.
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
 *  Read the file path and display it.
 */
void readFilePath()
{
    char path[SIZE_MAX_FILE_NAME]="";

    clearScreen();

    #ifndef PORTABLE
    readSystemPath(path);
    #endif // PORTABLE

    printf(_("Your files are saved in %s\n"),path);
    systemPause();
}

/*!
 * \fn void loadGameLocale(char *file_name)
 *  Load the file and run the play function
 * \param[in] file_name the filename
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
 *  Display the file.
 */
void displayFileLocale(char *file_name)
{
    csuStruct *ptr_csu_struct;

    clearScreen();

    ptr_csu_struct=readCsuFile(file_name);

    if (ptr_csu_struct != NULL)
    {
        printCsuStruct(ptr_csu_struct);

        if(exceedMaxNumber(ptr_csu_struct))
            printGameOver(ptr_csu_struct);

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
    char home_path[SIZE_MAX_FILE_NAME]="";

    clearScreen();
    menuFileName(config.name);
    menuGameConfig(&config);
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    if (newConfigFile(config,home_path) == false);
        systemPause();
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
    char home_path[SIZE_MAX_FILE_NAME]="";

    clearScreen();

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);
    if (ptr_list_config->nb_config > 0)
    {
        /*Affichage des diffrentes configurations*/
        printf(_("\nWhich game configuration would you like to use?\n"));
        for (i=0 ; i<ptr_list_config->nb_config ; i++)
            printf("(%d) %s\n",i+1,ptr_list_config->name_game_config[i]);

        /*Demande du choice*/
        do
        {
            printf(_("\nYour choice: "));
            intKey(&game_config_choice);
            printf(_("You chose %d\n"),game_config_choice);
        } while (game_config_choice <1 || game_config_choice >i);

        removeConfigListFile(game_config_choice-1,ptr_list_config,home_path);
    }

    else
        printf(_("\nYou do not have any game configuration file.\n"));

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
    char home_path[SIZE_MAX_FILE_NAME]="";

    clearScreen();

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);
    printf(_("\nHere are all your game configurations:\n"));
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
        printf("(%d) %s\n",i+1,ptr_list_config->name_game_config[i]);
    closeListGameConfig(ptr_list_config);
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
    char home_path[SIZE_MAX_FILE_NAME]="";

    clearScreen();

    /*Affichage des diffrentes configurations*/
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    ptr_list_config = readConfigListFile(home_path);
    if (ptr_list_config->nb_config > 0)
    {
        printf(_("\nWhich game configuration would you like to display?\n"));
        for (i=0 ; i<ptr_list_config->nb_config ; i++)
            printf("(%d) %s\n",i+1,ptr_list_config->name_game_config[i]);

        /*Demande du choice*/
        do
        {
            printf(_("\nYour choice: "));
            intKey(&game_config_choice);
            printf(_("You chose %d\n"),game_config_choice);
        } while (game_config_choice <1 || game_config_choice >i);

        readConfigFile(game_config_choice-1,ptr_list_config,&config,home_path);
        printGameConfig(config);
        closeListGameConfig(ptr_list_config);
    }

    else
        printf(_("\nYou do not have any game configuration file.\n"));

    systemPause();
}

/*!
 * \fn void exportListGameConfig()
 *  Export all game configuration in one file.
 */
void exportListGameConfig()
{
    char home_path[SIZE_MAX_FILE_NAME]="";
    char file_name[SIZE_MAX_FILE_NAME]="";
    int *id;
    int nb_id;

    clearScreen();

    menuFileName(file_name);

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    if(readSystemPath(file_name)==false)
        return;
    #endif // PORTABLE

    if (!menuExportListGameConfig(&id,&nb_id))
        return;

    if(exportConfigFile(home_path,file_name,id,nb_id) == true)
        printf(_("\nGame configurations were exported successfully in %s\n"),file_name);

    free(id);
    systemPause();
}

/*!
 * \fn void importListGameConfig()
 *  Import all game configuration in one file.
 */
void importListGameConfig()
{
    char home_path[SIZE_MAX_FILE_NAME]="";
    char filename[SIZE_MAX_FILE_NAME]="";
    int *id;
    int nb_id=0;

    clearScreen();

    menuFileName(filename);

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    if(readSystemPath(filename)==false)
        return;
    #endif // PORTABLE

    if (!menuImportListGameConfig(&id,&nb_id,filename))
        return;

    if(importConfigFile(home_path,filename,id,nb_id) == true)
        printf(_("\nGame configurations were successfully imported from %s\n"),filename);

    free(id);
    systemPause();
}


/*!
 * \fn void exportToPdfLocale(char *filename, char *export_filename)
 *  Export the csu file named filename into a pdf file named export_filename
 * \param[in] filename the csu filename
 * \param[in] export_filename the pdf filename
 */
void exportToPdfLocale(char *filename, char *export_filename)
{
    csuStruct *ptr_csu_struct;

    ptr_csu_struct=readCsuFile(filename);

    if (ptr_csu_struct == NULL)
    {
        systemPause();
        return;
    }

    if (exportToPdf(ptr_csu_struct,export_filename))
        printf(_("The file was well export to %s\n"),export_filename);
    else
        printf(_("There is an error when exporting the file %s into a pdf file.\n"),filename);
}


/*!
 * \fn void changePdfPreferences()
 *  Change the export to pdf preferences
 */
void changePdfPreferences()
{
    export_pdf_preferences pref;
    char home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE

    readFilePdfPreferences(home_path,&pref);
    menuPdfPreferences(&pref);
    createFilePdfPreferences(home_path,&pref);
}


/*!
 * \fn void exportToCsvLocale(char *filename, char *export_filename)
 *  Export the csu file named filename into a csv file named export_filename
 * \param[in] filename the csu filename
 * \param[in] export_filename the csv filename
 */
void exportToCsvLocale(char *filename, char *export_filename)
{
    csuStruct *ptr_csu_struct;

    ptr_csu_struct=readCsuFile(filename);

    if (ptr_csu_struct == NULL)
    {
        systemPause();
        return;
    }

    if (exportToCsv(ptr_csu_struct,export_filename))
        printf(_("The file was well export to %s\n"),export_filename);
    else
        printf(_("There is an error when exporting the file %s into a csv file.\n"),filename);

    closeCsuStruct(ptr_csu_struct);
}

/*!
 * \fn void exportToGnuplotLocale(char *filename, char *export_filename)
 *  Export the csu file named filename into gnuplot files named export_filename
 * \param[in] filename the csu filename
 * \param[in] export_filename the filename
 */
void exportToGnuplotLocale(char *filename, char *export_filename)
{
    csuStruct *ptr_csu_struct;

    ptr_csu_struct=readCsuFile(filename);

    if (ptr_csu_struct == NULL)
    {
        systemPause();
        return;
    }

    if (exportToGnuplotFile(ptr_csu_struct,export_filename))
        printf(_("The file was well export to %s\n"),export_filename);
    else
        printf(_("There is an error when exporting the file %s into a csv file.\n"),filename);

    closeCsuStruct(ptr_csu_struct);
}


/*!
 * \fn void exportToMLocale(char *filename, char *export_filename)
 *  Export the csu file named filename into a m file (octave/matlab)
 * \param[in] filename the csu filename
 * \param[in] export_filename
 */
void exportToMLocale(char *filename, char *export_filename)
{
    csuStruct *ptr_csu_struct;

    ptr_csu_struct=readCsuFile(filename);

    if (ptr_csu_struct == NULL)
    {
        systemPause();
        return;
    }

    if (exportToM(ptr_csu_struct,export_filename))
        printf(_("The file was well export to %s\n"),export_filename);
    else
        printf(_("There is an error when exporting the file %s into a m file.\n"),filename);

    closeCsuStruct(ptr_csu_struct);
}

/*!
 * \fn void exportCsu()
 *  Export a csu file into a csv or pdf file
 */
void exportCsu()
{
    csuStruct *ptr_csu_struct;
    char filename[SIZE_MAX_FILE_NAME];
    char export_filename[SIZE_MAX_FILE_NAME];
    FileType type;

    clearScreen();

    // Get the filename
    menuFileName(filename);
    #ifndef PORTABLE
    if(readSystemPath(filename)==false)
        return;
    #endif // PORTABLE
    ptr_csu_struct=readCsuFile(filename);

    // Read the file
    if (ptr_csu_struct == NULL)
    {
        systemPause();
        return;
    }

    // Prepare the exportation
    strcpy(export_filename,filename);
    removeFileExtension(export_filename);
    type = menuChooseExportFileType();

    if (type == pdf_file)
    {
        addFilePdfExtension(export_filename);
        if (exportToPdf(ptr_csu_struct,export_filename))
            printf(_("The file was well export to %s\n"),export_filename);
        else
            printf(_("There is an error when exporting the file %s into a pdf file.\n"),filename);
    }
    else if (type == gnuplot_file)
    {
        if (exportToGnuplotFile(ptr_csu_struct,export_filename))
            printf(_("The file was well export to %s\n"),export_filename);
        else
            printf(_("There is an error when exporting the file %s into gnuplot files.\n"),filename);
    }
    else if (type == csv_file)
    {
        addFileCsvExtension(export_filename);
        if (exportToCsv(ptr_csu_struct,export_filename))
            printf(_("The file was well export to %s\n"),export_filename);
        else
        printf(_("There is an error when exporting the file %s into a csv file.\n"),filename);
    }
    else
    {
        addFileExtension(export_filename,"m");
        if (exportToM(ptr_csu_struct,export_filename))
            printf(_("The file was well export to %s\n"),export_filename);
        else
        printf(_("There is an error when exporting the file %s into a m file.\n"),filename);
    }

    closeCsuStruct(ptr_csu_struct);
    systemPause();
}
