/*!
 * \file    file_properties_dialog.h
 * \author  Remi BERTHO
 * \date    25/08/15
 * \version 4.3.0
 */

/*
 * file_properties_dialog.h
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

#ifndef FILE_PROPERTIES_DIALOG_H_INCLUDED
#define FILE_PROPERTIES_DIALOG_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class FilePropertiesDialog
*   \brief This class represent the file properties dialog
*/
class FilePropertiesDialog : public CsuWidget, public Gtk::Dialog
{
protected:
    Gtk::Button* ok_button_;    /*!< The OK button */
    Gtk::Grid* main_grid_;      /*!< The main grid */
    Gtk::Label* prop_label_;    /*!< The properties label */

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    FilePropertiesDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);



    /*!
     *  \brief Show the dialog properties
     */
    void launch();
};


#endif // FILE_PROPERTIES_DIALOG_H_INCLUDED
