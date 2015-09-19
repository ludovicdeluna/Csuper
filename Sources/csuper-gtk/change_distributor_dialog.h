/*!
 * \file    change_distributor_dialog.h
 * \author  Remi BERTHO
 * \date    18/09/15
 * \version 4.3.0
 */

/*
 * change_distributor_dialog.h
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


#ifndef CHANGE_DISTRIBUTOR_DIALOG_H_INCLUDED
#define CHANGE_DISTRIBUTOR_DIALOG_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class ChangeDistributorDialog
*   \brief This class represent the change distributor dialog
*/
class ChangeDistributorDialog : public CsuWidget, public Gtk::Dialog
{
protected:
    Gtk::Button* ok_button_;        /*!< The OK button */
    Gtk::Button* cancel_button_;    /*!< The cancel button */
    Gtk::Grid* main_grid_;          /*!< The main grid */
    Gtk::Label* title_;             /*!< The title label */
    Gtk::ScrolledWindow* window_;   /*!< The scrolled window */
    Gtk::Viewport* viewport_;       /*!< The viewport */

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    ChangeDistributorDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);



    /*!
     *  \brief Show the dialog properties
     *  \return true if the distributor change, false otherwise
     */
    bool launch();
};

#endif // CHANGE_DISTRIBUTOR_DIALOG_H_INCLUDED
