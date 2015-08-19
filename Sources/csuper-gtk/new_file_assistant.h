/*!
 * \file    new_file_assistant.h
 * \author  Remi BERTHO
 * \date    12/08/15
 * \version 4.3.0
 */

/*
 * new_file_assistant.h
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef NEW_FILE_ASSISTANT_H_INCLUDED
#define NEW_FILE_ASSISTANT_H_INCLUDED


#include <gtkmm.h>

#include "../libcsuper/libcsuper.h"

#include "csu_widget.h"
#include "new_file_assistant_page_1.h"
#include "new_file_assistant_page_2.h"
#include "new_file_assistant_page_3.h"

/*! \class NewFileAssistant
*   \brief This class represent the new file assistant
*/
class NewFileAssistant : public CsuWidget, public Gtk::Assistant
{
protected:
    csuper::GameConfiguration game_config_; /*!< The game configuration */
    bool save_game_config_;                 /*!< Indicate if at the end the game configuration will be saved */

    NewFileAssistantPage1* page_1_; /*!< The new file assistant page 1 */
    NewFileAssistantPage2* page_2_; /*!< The new file assistant page 2 */
    NewFileAssistantPage3* page_3_; /*!< The new file assistant page 3 */

    unsigned int nb_player_;            /*!< The number of player */
    std::vector<Glib::ustring> names_;  /*!< The player names */



    friend class NewFileAssistantPage1;
    friend class NewFileAssistantPage2;
    friend class NewFileAssistantPage3;

    //
    // Function
    //
    /*!
     *  \brief Delete the assistant
     */
    bool deleteAssistant(GdkEventAny* event);

    /*!
     *  \brief Cancel
     */
    void cancel();

    /*!
     *  \brief Validate page 1
     */
    void validatePageOne();

    /*!
     *  \brief Validate page 2
     */
    void validatePageTwo();

    /*!
     *  \brief Validate page 3
     */
    void validatePageThree();

    /*!
     *  \brief Choose a game configuration
     */
    void chooseGameConfig();

    /*!
     *  \brief Prepare the page
     */
    void preparePage(Gtk::Widget* page);

    /*!
     *  \brief Validate the new file
     */
    void validate();

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param refGlade the builder
     */
    NewFileAssistant(const Glib::RefPtr<Gtk::Builder>& refGlade);


    /*!
     *  \brief Destructor
     */
    ~NewFileAssistant();



    //
    // Function
    //
    /*!
     *  \brief Show the new file assistant
     */
    void launch();
};


#endif // NEW_FILE_ASSISTANT_H_INCLUDED
