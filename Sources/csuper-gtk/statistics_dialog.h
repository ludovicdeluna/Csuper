/*!
 * \file    statistics_dialog.h
 * \author  Remi BERTHO
 * \date    27/08/15
 * \version 4.3.0
 */

/*
 * statistics_dialog.h
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

#ifndef STATISTICS_DIALOG_H_INCLUDED
#define STATISTICS_DIALOG_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class StatisticsDialog
*   \brief This class represent the statistics dialog
*/
class StatisticsDialog : public CsuWidget, public Gtk::Dialog
{
protected:
    Gtk::Button* ok_button_;                /*!< The OK button */
    Gtk::Grid* main_grid_;                  /*!< The main fixed */
    Gtk::ScrolledWindow* scrolled_window_;  /*!< The scrolled window */
    Gtk::Viewport* viewport_;               /*!< The viewport */
    Gtk::Label* stat_label_;                /*!< The label */

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    StatisticsDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);



    /*!
     *  \brief Show the dialog properties
     */
    void launch();
};


#endif // STATISTICS_DIALOG_H_INCLUDED
