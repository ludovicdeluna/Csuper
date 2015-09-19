/*!
 * \file    calculator_view.cpp
 * \author  Remi BERTHO
 * \date    18/09/15
 * \version 4.3.0
 */

/*
 * calculator_view.cpp
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

#include "calculator_view.h"

#include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace csuper;
using namespace std;


//
// Constructor and destructor
//
CalculatorView::CalculatorView(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Box(cobject)
{
    refGlade->get_widget("main_window_side_calculator_label", calc_label_);
    refGlade->get_widget("main_window_side_calculator_entry", entry_);
    refGlade->get_widget("main_window_side_calculator_result", result_label_);
    refGlade->get_widget("main_window_side_separator2", sep_);
    refGlade->get_widget("main_window_side_calculator_select_person", player_);
    refGlade->get_widget("main_window_side_calculator_validate", validate_);

    entry_->signal_changed().connect(mem_fun(*this,&CalculatorView::calculate));
    player_->signal_changed().connect(mem_fun(*this,&CalculatorView::calculate));

    validate_->set_sensitive(false);
}


//
// Function
//
void CalculatorView::calculate()
{
    ustring expr = entry_->get_text();

    if (expr.empty())
    {
        result_label_->set_text(_("No calculation"));
        return;
    }

    calc_.changeExpression(expr);
    try
    {
        result_label_->set_text(ustring::compose((_("The result is %1")),calc_.calculate()));
        if (app()->game() != nullptr && player_->get_active_row_number() != -1)
            validate_->set_sensitive(true);
    }
    catch (Glib::Exception& e)
    {
        cerr << e.what() << endl;
        result_label_->set_text(_("The expression is not correct"));
        validate_->set_sensitive(false);
    }
}


void CalculatorView::fillNames()
{
    player_->remove_all();

    for (unsigned int i=0 ; i<app()->game()->nbPlayer() ; i++)
        player_->append(app()->game()->playerName(i));
}
