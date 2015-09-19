/*!
 * \file    ranking_view.h
 * \author  Remi BERTHO
 * \date    18/09/15
 * \version 4.3.0
 */

/*
 * ranking_view.h
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

#ifndef RANKING_VIEW_H_INCLUDED
#define RANKING_VIEW_H_INCLUDED

#include <gtkmm.h>

#include "csu_widget.h"

/*! \class RankingView
*   \brief This class represent the calculator view
*/
class RankingView : public CsuWidget, public Gtk::Box
{
protected:
    Gtk::Separator* sep_;           /*!< The separator */
    Gtk::Viewport* viewport_;       /*!< The viewport */
    Gtk::Label* rank_label_;        /*!< The ranking label */
    Gtk::ScrolledWindow* scroll_;   /*!< The scrolled window */

public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    RankingView(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);


    //
    // Function
    //
    /*!
     *  \brief Update the ranking
     */
    void update();


};

#endif // RANKING_VIEW_H_INCLUDED
