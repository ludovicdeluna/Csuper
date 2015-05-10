/*!
 * \file    chart.h
 * \brief   Chart
 * \author  Remi BERTHO
 * \date    08/05/15
 * \version 4.2.0
 */

 /*
 * chart.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-gui.
 *
 * Csuper-gui is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-gui is distributed in the hope that it will be useful,
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

#ifndef CHART_H_INCLUDED
#define CHART_H_INCLUDED

#include "slope/slope.h"
#include "csuper-gui.h"
#include "utils.h"

G_MODULE_EXPORT void displayChart(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void drawChart(GtkWidget *widget, cairo_t *cr, gpointer *data);
G_MODULE_EXPORT void changeChartZoom(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void changeChartScrollbar(GtkWidget *widget, gpointer data);
G_MODULE_EXPORT void changeChartPlayersDisplay(GtkWidget *widget, gpointer data);

#endif // CHART_H_INCLUDED
