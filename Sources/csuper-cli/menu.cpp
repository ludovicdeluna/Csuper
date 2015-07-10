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
 #include <glibmm/i18n.h>


 using namespace csuper;
 using namespace Glib;
 using namespace std;



//
// Constructor and destructor
//
 Menu::Menu()
 {
     pref_ = Preferences::get();
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
                                   "\n (%8) Quit the program"
                                   "\n\nYour choice : ")
                                 ,NEW,LOAD,PRINT,DELETE,LIST,EXPORT,PREF,QUIT);
        cin >> choice;
        cleanStdin();

        switch (choice) {
            case NEW:
                //newGame();
                break;
            case LOAD:
                //loadGame();
                break;
            case PRINT:
                //displayFile();
                break;
            case DELETE:
                //deleteCsuFileNom();
                break;
            case LIST:
                listFile();
                break;
            case EXPORT:
                //exportCsu();
                break;
            case PREF:
                //preferencesMenu();
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
        cerr << e.what() << endl;
    }
    systemPause();
}


void Menu::wrongChoice() const
{
    cout << ustring(_("Error: you didn't enter a good value.")) << endl;
}
