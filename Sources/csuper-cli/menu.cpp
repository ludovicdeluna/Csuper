/*!
 * \file    menu.cpp
 * \author  Remi BERTHO
 * \date    10/07/15
 * \version 4.3.0
 */

/*
 * menu.cpp
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-cli.
 *
 * Csuper-cli is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-cli is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

 #include "menu.h"
 #include "share.h"
 #include "game_cli.h"
 #include "cin.h"
 #include <glibmm/i18n.h>


 using namespace csuper;
 using namespace Glib;
 using namespace std;



//
// Constructor and destructor
//
 Menu::Menu()
 {
     pref_ = csuper::Preferences::get();
     list_game_config_ = ListGameConfiguration::getMainList();
 }


 Menu::~Menu()
 {
     delete pref_;
     delete list_game_config_;
 }



 //
 // Menu function
 //

void Menu::main()
{
    int choice;
    int stop = false;

    do
    {
        choice=-1;

        clearScreen();

        cout << ustring(_("Csuper - Universal points counter allowing a dispense with reflection v"));
        cout << CSUPER_VERSION << endl << endl;
        cout << ustring::compose(_("What do you want to do?"
                                   "\n (%1) Play a new game"
                                   "\n (%2) Load an existing game"
                                   "\n (%3) Display the results of an existing game"
                                   "\n (%4) Delete a game"
                                   "\n (%5) Display all existing games"
                                   "\n (%6) Export a file"
                                   "\n (%7) Display the preferences menu"
                                   "\n (%8) About"
                                   "\n (%9) Quit the program"
                                   "\n\nYour choice : ")
                                 ,NEW,LOAD,PRINT,DELETE,LIST,EXPORT,PREF,ABOUT,QUIT);

        choice = Cin::getInt();

        switch (choice)
        {
        case NEW:
            //newGame();
            break;
        case LOAD:
            //loadGame();
            break;
        case PRINT:
            displayFile();
            break;
        case DELETE:
            deleteCsuFile();
            break;
        case LIST:
            listFile();
            break;
        case EXPORT:
            exportCsu();
            break;
        case PREF:
            preferencesMenu();
            break;
        case ABOUT:
            about();
            break;
        case QUIT:
            cout << ustring(_("\nSee you.")) << endl;
            systemPause();
            stop=true;
            break;
        default:
            wrongChoice();
            systemPause();
        }

        clearScreen();

	} while (stop==false);
}

void Menu::preferencesMenu() const
{
    int choice;
    int stop = false;

    do
    {
        clearScreen();

        cout << ustring(_("What do you want to do?")) << endl;
        cout << ustring::compose(_("\n (%1) Make a new game configuration"
                                   "\n (%2) Delete an existing game configuration"
                                   "\n (%3) Display the list of game configurations"
                                   "\n (%4) Display a game configuration"
                                   "\n (%5) Export game configurations"
                                   "\n (%6) Import game configurations"
                                   "\n (%7) Change PDF export preferences"
                                   "\n (%8) Change the folder where files will be read and saved"
                                   "\n (%9) Display the folder where files will be read and saved")
                                 ,NEW_GAME_CONF,REMOVE_GAME_CONF,PRINT_LIST_GAME_CONF,
                                 PRINT_GAME_CONF,EXPORT_GAME_CONF,IMPORT_GAME_CONF,
                                 PDF_PREFERENCES,CHANGE_OPEN_PATH,READ_OPEN_PATH);

        cout << ustring::compose(_("\n (%1) Back to main menu"
                                   "\n\nYour choice: "), BACK_MAIN_MENU);

        choice = Cin::getInt();

        switch (choice)
        {
        case CHANGE_OPEN_PATH :
            changeOpenPath();
            break;
        case READ_OPEN_PATH :
            readOpenPath();
            break;
        case BACK_MAIN_MENU :
            stop=true;
            break;
        case NEW_GAME_CONF :
            newGameConfig();
            break;
        case REMOVE_GAME_CONF :
            removeGameConfig();
            break;
        case PRINT_LIST_GAME_CONF :
            printListGameConfig();
            break;
        case PRINT_GAME_CONF :
            printGameConfig();
            break;
        case EXPORT_GAME_CONF :
            exportListGameConfig();
            break;
        case IMPORT_GAME_CONF :
            importListGameConfig();
            break;
        case PDF_PREFERENCES :
            changePdfPreferences();
            break;
        default :
            wrongChoice();
            systemPause();
        }

        clearScreen();
    } while (!stop);
}

void Menu::listFile() const
{
    clearScreen();
    cout << ustring(_("Here are all your csu files:")) << endl;

    try
    {
        Dir dir(filename_from_utf8(pref_->directory().open()));

        DirIterator it;
        for (it = dir.begin() ; it != dir.end() ; it++)
        {
            ustring filename = filename_to_utf8(*it);
            if (filename.compare(filename.length()-3,3,"csu") == 0)
                cout << " - " << filename << endl;
        }
    }
    catch(Glib::Error& e)
    {
        cout << e.what() << endl;
    }
    systemPause();
}

void Menu::about() const
{
    clearScreen();
    cout << ustring(_("Csuper - Universal points counter allowing a dispense with reflection v"))
         << CSUPER_VERSION << endl;
    cout << _("Csuper website: ") << ustring("http://www.dalan.rd-h.fr/wordpress") << endl;
    cout << ustring("Copyright © 2014-2015 Rémi BERTHO <remi.bertho@openmailbox.org>") << endl;
    cout << ustring(_("This program comes with ABSOLUTELY NO WARRANTY. \nThis is free software,"
                     "and you are welcome to redistribute it under certain conditions. \n"
                     "Fore more details : http://www.gnu.org/licenses/gpl.html\n")) << endl << endl;
    systemPause();
}

void Menu::deleteCsuFile() const
{
    clearScreen();

    ustring filename = build_filename(pref_->directory().open(),askFilename());
    if (remove((filename).c_str()) != 0)
        perror(ustring::compose(_("Error when deleting %1: "),filename).c_str());
    else
        cout << ustring::compose(_("The file %1 was successfully deleted."),filename) << endl;

    systemPause();
}

void Menu::displayFile() const
{
    clearScreen();

    ustring filename = build_filename(pref_->directory().open(),askFilename());

    try
    {
        GameCli* game = new GameCli(filename);
        cout << *game << endl;
        delete game;
    }
    catch (Glib::Exception& e)
    {
        cout << e.what() << endl;
    }


    systemPause();
}

void Menu::exportCsu() const
{
    GameCli* game;
    int choice;

    clearScreen();

    ustring filename = build_filename(pref_->directory().open(),askFilename());

    try
    {
        game = new GameCli(filename);
    }
    catch (Glib::Exception& e)
    {
        cout << e.what() << endl;
        systemPause();
        return;
    }

    cout << ustring(_("In what file type would you like to export?"
                      "\n (1) PDF file (default)"
                      "\n (2) CSV file"
                      "\n (3) Gnuplot files\n"
                      " (4) m files (Octave/Matlab file)"
                      "\nYour choice: "));

    choice = Cin::getInt();

    removeFileExtension(filename);
    try
    {
        switch(choice)
        {
        case 2:
            game->exportToCsv(filename + ".csv");
            break;
        case 3:
            game->exportToGnuplot(filename);
            break;
        case 4:
            game->exportToM(filename + ".m");
            break;
        default:
            game->exportToPdf(filename + ".pdf",pref_->exportPdf(),pref_->chartExportation());
            break;
        }
        cout << _("The file was well exported.") << endl;
    }
    catch(Glib::Exception& e)
    {
        cout << e.what() << endl;
        cout << ustring(_("There is an error when exporting the file.")) << endl;
    }

    systemPause();

    delete game;
}

void Menu::changeOpenPath() const
{
    clearScreen();

    ustring new_path;

    do
    {
        cout << ustring(_("Give the new folder in which you would like to save and read your files.\n"
                          "Check if the folder exists and if you have the read and write rights.\n\n"
                          "Your choice: "));

        new_path = Cin::getUstring();
    } while (! file_test(new_path,FILE_TEST_IS_DIR));

    pref_->directory().setOpen(new_path);
    pref_->writeToFile();

    systemPause();
}


void Menu::readOpenPath() const
{
    clearScreen();

    cout << ustring::compose(_("Your files are saved and read in %1"),pref_->directory().open()) << endl;

    systemPause();
}

void Menu::printListGameConfig() const
{
    clearScreen();

    cout << ustring(_("Here are all your game configurations:")) << endl;
    cout << list_game_config_->toUstringName() << endl;

    systemPause();
}

void Menu::printGameConfig() const
{
    clearScreen();

    if (list_game_config_->size() > 0)
    {
        cout << ustring(_("Which game configuration would you like to display?")) << endl;
        cout << list_game_config_->toUstringName() << endl;

        unsigned int choice = 0;

        do
        {
            cout << ustring(_("Your choice: "));
            choice = Cin::getUnsignedInt();
            cout << ustring::compose(_("You chose %1"),choice) << endl;
        } while (choice < 1 || choice > list_game_config_->size());

        cout << endl << (*list_game_config_)[choice-1] << endl;
    }
    else
        cout << ustring(_("You do not have any game configuration file.")) << endl;

    systemPause();
}

void Menu::removeGameConfig() const
{
    clearScreen();

    if (list_game_config_->size() > 0)
    {
        cout << ustring(_("Which game configuration would you like to delete?")) << endl;
        cout << list_game_config_->toUstringName() << endl;

        unsigned int choice = 0;

        do
        {
            cout <<  ustring(_("Your choice: "));
            choice = Cin::getUnsignedInt();
            cout << ustring::compose(_("You chose %1"),choice) << endl;
        } while (choice < 1 || choice > list_game_config_->size());

        list_game_config_->remove(choice-1);
        list_game_config_->writeToFile();

        cout << ustring(_("The game configuration was well deleted.")) << endl;
    }
    else
        cout << ustring(_("You do not have any game configuration file.")) << endl;

    systemPause();
}

void Menu::changePdfPreferences() const
{
    clearScreen();

    char choice;
    int nb;

    // Charset
    cout << ustring(_("The UTF-8 character set permit to display all character but can have problem with some fonts."
                      "\n\nWould you use the UTF-8 character set (y/N)? "));
    choice = Cin::getChar();
    if (choice == 'Y' || choice == 'y')
        pref_->exportPdf().setCharset(ExportPdfPreferences::UTF8);
    else
        pref_->exportPdf().setCharset(ExportPdfPreferences::WINDOWS1252);

    // Font
    cout << endl << endl;
    cout << ustring(_("Please type the font name which will be use in the PDF\n"
                      "Be careful, if the font does'nt exist the PDF file will be unreadable."
                      "\nYour choice: ")) << endl;
    pref_->exportPdf().setFontName(Cin::getUstring());


    // Embedded font
    cout << endl << endl;
    cout << ustring(_("If the font is embedded in the PDF file, any user will can read the file "
                      "even if he has not the font installed. But the file will be bigger."
                      "\n\nWould you embed the font in the PDF file (Y/n)? "));
    choice = Cin::getChar();
    if (choice == 'N' || choice == 'n')
        pref_->exportPdf().setEmbeddedFont(false);
    else
        pref_->exportPdf().setEmbeddedFont(true);

    // Direction
    cout << endl << endl;
    cout << ustring(_("What page direction of the page do you want?"
                      "\n (1) Portrait (default)"
                      "\n (2) Landscape"
                      "\nYour choice: "));
    choice = Cin::getChar();
    if (choice == '2' || choice =='2')
        pref_->exportPdf().setDirection(ExportPdfPreferences::LANDSCAPE);
    else
        pref_->exportPdf().setDirection(ExportPdfPreferences::PORTRAIT);

    // Size
    cout << endl << endl;
    cout << ustring(_("What size of page do you want?"
                      "\n (1) A3"
                      "\n (2) A4 (default)"
                      "\nYour choice: "));
    choice = Cin::getChar();
    if (choice == '1')
        pref_->exportPdf().setSize(ExportPdfPreferences::A3);
    else if (choice == '3')
        pref_->exportPdf().setSize(ExportPdfPreferences::A5);
    else
        pref_->exportPdf().setSize(ExportPdfPreferences::A4);

    // Margin
    do
    {
        cout << endl << endl;
        cout << ustring::compose(_("Give the margin you want or -1 if want to keep the old one (%1)."
                                   " It will be between 0 and 200."
                                   "\nYour choice: ")
                                 ,pref_->exportPdf().margin());
        nb = Cin::getInt();
    } while (nb < -1 || nb > 200);
    if (nb != -1)
        pref_->exportPdf().setMargin(nb);

    // Font size
    do
    {
        cout << endl << endl;
        cout << ustring::compose(_("Give the font size you want or -1 if want to keep the old one (%1)."
                                   " It will be between 4 and 40."
                                   "\nYour choice: ")
                                 ,pref_->exportPdf().fontSize());
        nb = Cin::getInt();
    } while ((nb < 4 || nb > 40) && nb != -1);
    if (nb != -1)
        pref_->exportPdf().setFontSize(nb);

    // Total points by turn
    cout << endl << endl;
    cout << ustring(_("Would you like to display the total points in each turn (y/N)? "));
    choice = Cin::getChar();
    if (choice == 'Y' || choice == 'y')
        pref_->exportPdf().setTotalPoints(true);
    else
        pref_->exportPdf().setTotalPoints(false);

    // Ranking by turn
    cout << endl << endl;
    cout << ustring(_("Would you like to display the ranking in each turn (y/N)? "));
    choice = Cin::getChar();
    if (choice == 'Y' || choice == 'y')
        pref_->exportPdf().setRanking(true);
    else
        pref_->exportPdf().setRanking(false);

    // Pdf size for chart
    cout << endl << endl;
    cout << ustring(_("Would you like to use the pdf size for the pdf chart (y/N)? "));
    choice = Cin::getChar();
    if (choice == 'Y' || choice == 'y')
        pref_->exportPdf().setPdfSizeForChart(true);
    else
        pref_->exportPdf().setPdfSizeForChart(false);


    pref_->writeToFile();

    cout << endl << ustring(_("The PDF preferences was well changed.")) << endl;

    systemPause();
}

void Menu::newGameConfig() const
{
    char tmp_char;

    clearScreen();
    GameConfiguration* game_config = new GameConfiguration();

    // Name
    cout << ustring(_("What is the name of the new game configuration?\n"
                       "Your choice: "));
    game_config->setName(Cin::getUstring());

    // Maximum number
    cout << endl << ustring(_("Would you like to use a maximum or a minimum score (Y/n): "));
    tmp_char = Cin::getChar();
    if (tmp_char == 'n' || tmp_char=='N')
    {
        game_config->setNbMaxMin(INFINITY);
        game_config->setUseMaximum(true);
    } else
    {
        // Maximum or minimum
        cout << endl << ustring(_("Would you like to use a maximum score (Y/n): "));
        tmp_char = Cin::getChar();
        if (tmp_char == 'n' || tmp_char == 'N')
            game_config->setUseMaximum(false);
        else
            game_config->setUseMaximum(true);

        // Number maximum or minimum.
        cout << endl;
        cout << ustring(_("Give the maximal or minimal score which a player can reach in the game."
                          "\nYour choice: "));
        game_config->setNbMaxMin(Cin::getDouble());
        cout << ustring::compose(_("You chose %1\n"),game_config->nbMaxMin());
    }

    // Score at the beginning
    cout << endl;
    cout << ustring(_("Give the initial score of the players.\nYour choice: "));
    game_config->setInitialScore(Cin::getDouble());
    cout << ustring::compose(_("You chose %1\n"),game_config->initialScore());

    // First way
    cout << endl;
    cout << ustring(_("The winner is the player who has the highest score (Y/n): "));
    tmp_char = Cin::getChar();
    if (tmp_char == 'n' || tmp_char == 'N')
        game_config->setMaxWinner(false);
    else
        game_config->setMaxWinner(true);

    // Turn by turn
    cout << endl;
    cout << ustring(_("This is a turn-based game (Y/n): "));
    tmp_char = Cin::getChar();
    if (tmp_char == 'n' || tmp_char == 'N')
        game_config->setTurnBased(false);
    else
        game_config->setTurnBased(true);

    // Distributor
    cout << endl;
    cout << ustring(_("A distributor is used (Y/n): "));
    tmp_char = Cin::getChar();
    if (tmp_char == 'n' || tmp_char == 'N')
        game_config->setUseDistributor(false);
    else
        game_config->setUseDistributor(true);

    // Number of decimal place
    do
    {
        cout << endl;
        cout << ustring(_("Give the number of decimals displayed. This number must be between 0 and 10."
                          "\nYour choice: "));
        game_config->setDecimalPlace(Cin::getInt());
        cout << ustring::compose(_("You chose %1"),game_config->decimalPlace()) << endl;
    } while (game_config->decimalPlace() < 0 || game_config->decimalPlace() > 10);

    try
    {
        list_game_config_->add(game_config);
        list_game_config_->writeToFile();
        cout << endl << ustring(_("The game configuration was well created.")) << endl;
    }
    catch (Glib::Exception& e)
    {
        cout << e.what() << endl;
    }
    systemPause();
}

void Menu::exportListGameConfig() const
{
    clearScreen();

    vector<unsigned int> indexes;
    ustring filename = build_filename(pref_->directory().open(),askFilename());

    if (list_game_config_->size() > 0)
    {
        cout << ustring(_("Here are all your game configurations:")) << endl;
        cout << list_game_config_->toUstringName() << endl;


        char tmp_char;
        cout << ustring(_("Export all your game configuration (Y/n): "));
        tmp_char = Cin::getChar();

        // Chose the export game configuration
        if (tmp_char == 'n' || tmp_char == 'N')
        {
            unsigned int choice;
            while (true)
            {
                cout << ustring(_("Give the id of the game configuration you want to export. Use 0 if you don't want another."
                                  "\nYour choice: "));
                choice = Cin::getUnsignedInt();
                cout << ustring::compose(_("You chose %1"),choice) << endl;
                if (choice > list_game_config_->size())
                    cout << ustring::compose(_("There is only %1 game configuration."),list_game_config_->size()) << endl;
                else if (choice == 0)
                    break;
                else
                    indexes.push_back(choice-1);
            }
        }
        // Export all
        else
        {
            for (unsigned int i=0; i<list_game_config_->size() ; i++)
                indexes.push_back(i);
        }


        // Save
        try
        {
            list_game_config_->writeToFile(filename,indexes);
            cout << ustring(_("The game configuration was well exported.")) << endl;
        }
        catch (Glib::Exception& e)
        {
            cout << e.what() << endl;
        }
    }
    else
        cout << ustring(_("You do not have any game configuration file.")) << endl;


    systemPause();
}

void Menu::importListGameConfig() const
{
    clearScreen();

    vector<unsigned int> indexes;
    ustring filename = build_filename(pref_->directory().open(),askFilename());

    ListGameConfiguration* import_game_config;
    try
    {
        import_game_config = new ListGameConfiguration(filename);
    }
    catch (Glib::Exception& e)
    {
        cout << e.what() << endl;
        systemPause();
        return;
    }

    cout << ustring(_("Here are all the game configurations in the file:")) << endl;
    cout << import_game_config->toUstringName() << endl;

    char tmp_char;
    cout << ustring(_("Import all the game configuration (Y/n): "));
    tmp_char = Cin::getChar();

    // Chose the import game configuration
    if (tmp_char == 'n' || tmp_char == 'N')
    {
        unsigned int choice;
        while (true)
        {
            cout << ustring(_("Give the id of the game configuration you want to import. Use 0 if you don't want another."
                              "\nYour choice: "));
            choice = Cin::getUnsignedInt();
            cout << ustring::compose(_("You chose %1"),choice) << endl;
            if (choice > import_game_config->size())
                cout << ustring::compose(_("There is only %1 game configuration."),import_game_config->size()) << endl;
            else if (choice == 0)
                break;
            else
                indexes.push_back(choice-1);
        }
    }
    // Import all
    else
    {
        for (unsigned int i=0; i<import_game_config->size() ; i++)
            indexes.push_back(i);
    }

    list_game_config_->add(*import_game_config,indexes);
    list_game_config_->writeToFile();
    cout << ustring(_("The game configuration was well imported.")) << endl;
    delete import_game_config;

    systemPause();
}

//
// Ask function
//
ustring Menu::askFilename() const
{
    ustring res;
    cout << ustring(_("Give a name to the file.\nYour choice: "));
    res = Cin::getUstring();
    cout << ustring(_("You choose ")) << res << endl;
    return res;
}




void Menu::wrongChoice() const
{
    cout << ustring(_("Error: you didn't enter a good value.")) << endl;
}
