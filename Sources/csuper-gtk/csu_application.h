/*!
 * \file    csu_application.h
 * \author  Remi BERTHO
 * \date    28/07/15
 * \version 4.3.0
 */

/*
 * csu_application.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-gtk.
 *
 * Csuper-gtk is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-gtk is distributed in the hope that it will be useful,
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

#ifndef CSU_APPLICATION_H_INCLUDED
#define CSU_APPLICATION_H_INCLUDED

#include <gtkmm.h>

#include "main_window.h"
#include "about.h"

#include "../libcsuper/libcsuper.h"


/*! \class CsuApplication
*   \brief This class represent the Application
*/
class CsuApplication : public Gtk::Application
{
private:
    Glib::RefPtr<Gtk::Builder> builder_;    /*!< The Gtk::Builder */

    csuper::Preferences* pref_;                         /*!< The preferences */
    csuper::ListGameConfiguration* list_game_config_;   /*!< The list of game configuration */

    MainWindow* main_window_;               /*!< The main window */
    About* about_;                          /*!< The about dialog */



    //
    // Signal
    //
    /*!
     *  \brief Function used on the startup signal. It create the menu
     */
    void onStartup();

    /*!
     *  \brief Quit Csuper
     */
    void onQuit();

public:
    //
    // Constructor and destructor
    //
    /*!
     *  \brief Constructor
     *  \param argc The parameter received by your main() function.
     *  \param argv The parameter received by your main() function.
     */
    CsuApplication(int& argc, char**& argv);


    /*!
     *  \brief Destructor
     */
    ~CsuApplication();



    //
    // Function
    //
    /*!
     *  \brief Initialize the CsuApplication with the builder
     *  \param builder the GTK::Builder
     */
    void init(Glib::RefPtr<Gtk::Builder>& builder);

    /*!
     *  \brief Launch the application
     */
    int launch();
};

#endif // CSU_APPLICATION_H_INCLUDED
