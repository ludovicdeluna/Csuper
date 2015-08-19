/*!
 * \file    new_file_assistant_page_2.h
 * \author  Remi BERTHO
 * \date    17/08/15
 * \version 4.3.0
 */

/*
 * new_file_assistant_page_2.h
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

#ifndef NEW_FILE_ASSISTANT_PAGE_2_H_INCLUDED
#define NEW_FILE_ASSISTANT_PAGE_2_H_INCLUDED


#include <gtkmm.h>

#include "csu_widget.h"

/*! \class NewFileAssistantPage2
*   \brief This class represent the scrolled window of the second page of the new assistant
*/
class NewFileAssistantPage2 : public CsuWidget, public Gtk::ScrolledWindow
{
protected:
    Gtk::Viewport* viewport_;   /*!< The viewport */
    Gtk::Grid* grid_;           /*!< The grid */

    unsigned int nb_ligne_ = 0; /*!< The number of line */



public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor
     */
    NewFileAssistantPage2();

    friend class NewFileAssistant;

    /*!
     *  \brief Create the lines
     */
    void createLines(const unsigned int nb_player);

    /*!
     *  \brief Delete the lines
     */
    void deleteLines();
};


#endif // NEW_FILE_ASSISTANT_PAGE_2_H_INCLUDED
