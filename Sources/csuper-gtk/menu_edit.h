/*!
 * \file    menu_edit.h
 * \author  Remi BERTHO
 * \date    06/08/15
 * \version 4.3.0
 */

/*
 * menu_edit.h
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

#ifndef MENU_EDIT_H_INCLUDED
#define MENU_EDIT_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class MenuEdit
*   \brief This class represent the menu edit
*/
class MenuEdit : public CsuWidget, public Gtk::Menu
{
protected:
    Gtk::MenuItem* undo_;           /*!< The undo button */
    Gtk::MenuItem* redo_;           /*!< The redo button */
    Gtk::SeparatorMenuItem* sep_;   /*!< The separator */
    Gtk::MenuItem* cut_;            /*!< The cut button */
    Gtk::MenuItem* copy_;           /*!< The copy button */
    Gtk::MenuItem* paste_;          /*!< The paste button */
    Gtk::MenuItem* delete_;         /*!< The delete button */



    //
    // Function
    //
    /*!
     *  \brief Copy the current text in the clipboard
     */
    void copy();

    /*!
     *  \brief Cut the current text in the clipboard
     */
    void cut();

    /*!
     *  \brief Paste the current text in the clipboard
     */
    void paste();

    /*!
     *  \brief Delete the current text in the clipboard
     */
    void deleteText();

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    MenuEdit(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
};


#endif // MENU_EDIT_H_INCLUDED
