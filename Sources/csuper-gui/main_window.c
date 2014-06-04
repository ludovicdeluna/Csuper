/*!
 * \file    main_window.c
 * \brief   Main window
 * \author  Remi BERTHO
 * \date    03/05/14
 * \version 3.0.0
 */

 /*
 * main_window.c
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
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

#include "main_window.h"



/*!
 * \fn void noCsuFileRanking(globalData *data)
 *  Fill the ranking with no ranking
 * \param[in] data the globalData
 */
void noCsuFileRanking(globalData *data)
{
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_grid_game_config"));
    if (!grid)
        g_critical(_("Widget main_window_grid_game_config is missing in file csuper-gui.glade."));

    GtkWidget *label = gtk_label_new(_("No csu file loaded"));

    gtk_grid_attach(GTK_GRID(grid),label,0,1,1,1);
}

/*!
 * \fn void deleteRanking(globalData *data)
 *  Delete the ranking
 * \param[in] data the globalData
 */
void deleteRanking(globalData *data)
{
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_grid_game_config"));
    if (!grid)
        g_critical(_("Widget main_window_grid_game_config is missing in file csuper-gui.glade."));

    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(grid),0,1));
}

/*!
 * \fn void createRanking(globalData *data)
 *  Create the ranking
 * \param[in] data the globalData
 */
void createRanking(globalData *data)
{
    gint i;
    gint index;
    gint nb;

    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_grid_game_config"));
    if (!grid)
        g_critical(_("Widget main_window_grid_game_config is missing in file csuper-gui.glade."));

    /* Set the grid*/
    GtkWidget *rank_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(rank_grid),20);
    gtk_grid_set_row_spacing(GTK_GRID(rank_grid),10);
    gtk_widget_set_margin_right(rank_grid,10);
    gtk_widget_set_margin_left(rank_grid,10);
    gtk_widget_set_margin_top(rank_grid,10);
    gtk_widget_set_margin_bottom(rank_grid,10);
    gtk_grid_set_column_homogeneous(GTK_GRID(rank_grid),TRUE);

    /* Set the column name */
    gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Position")),0,0,1,1);
    gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),0,0)),TRUE);
    gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Name")),1,0,1,1);
    gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),1,0)),TRUE);
    gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Points")),2,0,1,1);
    gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),2,0)),TRUE);

    /* Set all the information*/
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
    {
        nb=1;
        index=searchIndexFromPosition(data->ptr_csu_struct,i+1,&nb);

        gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%d"),i+2-nb)),0,i+1,1,1);
        //gtk_label_set_markup(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),0,i+1)),"<span foreground=\"blue\"></span>");
        gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),0,i+1)),TRUE);

        gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[index])),1,i+1,1,1);
        gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),1,i+1)),TRUE);

        switch (data->ptr_csu_struct->config.decimal_place)
        {
        case 0 :
            gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.0f"),data->ptr_csu_struct->total_points[index])),2,i+1,1,1);
            break;
        case 1 :
            gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.1f"),data->ptr_csu_struct->total_points[index])),2,i+1,1,1);
            break;
        case 2 :
            gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.2f"),data->ptr_csu_struct->total_points[index])),2,i+1,1,1);
            break;
        case 3 :
            gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.3f"),data->ptr_csu_struct->total_points[index])),2,i+1,1,1);
            break;
        }
        gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),2,i+1)),TRUE);
    }

    gtk_grid_attach(GTK_GRID(grid),rank_grid,0,1,1,1);

    gtk_widget_show_all(rank_grid);
}

/*!
 * \fn void updateMainWindow(globalData *data)
 *  Update the main window
 * \param[in] data the globalData
 */
void updateMainWindow(globalData *data)
{
    deleteRanking(data);
    createRanking(data);
    updateDistributorLabel(data);
}

/*!
 * \fn void updateDistributorLabel(globalData *data)
 *  Update the distributor
 * \param[in] data the globalData
 */
void updateDistributorLabel(globalData *data)
{
    GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_label_distributor"));
    if (!label)
        g_critical(_("Widget main_window_label_distributor is missing in file csuper-gui.glade."));

    if (data->ptr_csu_struct->config.use_distributor == 1)
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%s is the distributor"),data->ptr_csu_struct->player_names[(gint)data->ptr_csu_struct->distributor]));
    else
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("There is no distributor")));
}
