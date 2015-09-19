/*!
 * \file    calculator_view.h
 * \author  Remi BERTHO
 * \date    18/09/15
 * \version 4.3.0
 */

/*
 * calculator_view.h
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

#ifndef CALCULATOR_VIEW_H_INCLUDED
#define CALCULATOR_VIEW_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"
#include "../libcsuper/libcsuper.h"

/*! \class CalculatorView
*   \brief This class represent the calculator view
*/
class CalculatorView : public CsuWidget, public Gtk::Box
{
protected:
    Gtk::Separator* sep_;           /*!< The separator */
    Gtk::Entry* entry_;             /*!< The entry */
    Gtk::Label* calc_label_;        /*!< The calculator label */
    Gtk::Label* result_label_;      /*!< The result label */
    Gtk::ComboBoxText* player_;     /*!< The player combobox text */
    Gtk::Button* validate_;         /*!< The validate button */

    csuper::Calculator calc_;       /*!< The calculator */



    //
    // Function
    //
    /*!
     *  \brief Calculate
     */
    void calculate();

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    CalculatorView(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);


    //
    // Function
    //
    /*!
     *  \brief Fill names
     */
    void fillNames();


};

#endif // CALCULATOR_VIEW_H_INCLUDED
