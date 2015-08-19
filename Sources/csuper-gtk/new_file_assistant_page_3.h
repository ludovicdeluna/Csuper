/*!
 * \file    new_file_assistant_page_3.h
 * \author  Remi BERTHO
 * \date    18/08/15
 * \version 4.3.0
 */

/*
 * new_file_assistant_page_3.h
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

#ifndef NEW_FILE_ASSISTANT_PAGE_3_H_INCLUDED
#define NEW_FILE_ASSISTANT_PAGE_3_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class NewFileAssistantPage3
*   \brief This class represent the scrolled window of the third page of the new assistant
*/
class NewFileAssistantPage3 : public CsuWidget, public Gtk::Grid
{
protected:
    Gtk::Label* distributor_label_;             /*!< The distributor label */
    Gtk::ComboBoxText* distributor_combobox_;   /*!< The distributor combobox */

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor
     */
    NewFileAssistantPage3();

    friend class NewFileAssistant;
};


#endif // NEW_FILE_ASSISTANT_PAGE_3_H_INCLUDED
