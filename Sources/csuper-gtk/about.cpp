/*!
 * \file    about.cpp
 * \author  Remi BERTHO
 * \date    29/07/15
 * \version 4.3.0
 */

/*
 * about.cpp
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

#include "about.h"

#include "../libcsuper/libcsuper.h"


using namespace Gtk;
using namespace Glib;
using namespace csuper;

About::About(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), AboutDialog(cobject)
{
    //Version
    set_version(Version().toUstring());
}



void About::launch()
{
    show();
    run();
    hide();
}
