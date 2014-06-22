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

    gtk_widget_set_vexpand(label,TRUE);

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
    //gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),0,0)),TRUE);
    gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Name")),1,0,1,1);
    //gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),1,0)),TRUE);
    gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Points")),2,0,1,1);
    //gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),2,0)),TRUE);

    /* Set all the information*/
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
    {
        nb=1;
        index=searchIndexFromPosition(data->ptr_csu_struct,i+1,&nb);

        gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%d"),i+2-nb)),0,i+1,1,1);
        //gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),0,i+1)),TRUE);

        gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[index])),1,i+1,1,1);
        //gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),1,i+1)),TRUE);

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
        //gtk_label_set_selectable(GTK_LABEL(gtk_grid_get_child_at(GTK_GRID(rank_grid),2,i+1)),TRUE);
    }

    gtk_widget_set_vexpand(rank_grid,TRUE);

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
    deletePoints(data);
    createPointsGrid(data);
    updateTotalPointsInTurnLabel(NULL,data);
    setButtonMainWindowSensitive(data);
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

/*!
 * \fn G_MODULE_EXPORT void updateTotalPointsInTurnLabel(globalData *data)
 *  Update the total points in the turn
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void updateTotalPointsInTurnLabel(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gint i;
    gfloat total_points=0;
    gint max_nb_turn = maxNbTurn(user_data->ptr_csu_struct);

    GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"main_window_label_total_points_in_turn"));
    if (!label)
        g_critical(_("Widget main_window_label_total_points_in_turn is missing in file csuper-gui.glade."));

    GtkWidget *viewport = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"main_window_viewport"));
    if (!viewport)
        g_critical(_("Widget main_window_viewport is missing in file csuper-gui.glade."));

    for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
        total_points += gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),2*(i+1),2*(max_nb_turn+1))));

    switch (user_data->ptr_csu_struct->config.decimal_place)
    {
    case 0 :
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("There is %.0f points in the turn"),total_points));
        break;
    case 1 :
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("There is %.1f points in the turn"),total_points));
        break;
    case 2 :
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("There is %.2f points in the turn"),total_points));
        break;
    case 3 :
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("There is %.3f points in the turn"),total_points));
        break;
    }
}

/*!
 * \fn void noCsuFilePoints(globalData *data)
 *  Fill the points with no csu file
 * \param[in] data the globalData
 */
void noCsuFilePoints(globalData *data)
{
    GtkWidget *viewport = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_viewport"));
    if (!viewport)
        g_critical(_("Widget main_window_viewport is missing in file csuper-gui.glade."));

    GtkWidget *label = gtk_label_new(_("No csu file loaded"));

    gtk_container_add(GTK_CONTAINER(viewport),label);
}

/*!
 * \fn void deletePoints(globalData *data)
 *  Delete the points window
 * \param[in] data the globalData
 */
void deletePoints(globalData *data)
{
    GtkWidget *viewport = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_viewport"));
    if (!viewport)
        g_critical(_("Widget main_window_viewport is missing in file csuper-gui.glade."));

    gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(viewport)));
}

/*!
 * \fn void createPointsGrid(globalData *data)
 *  Create the points grid
 * \param[in] data the globalData
 */
void createPointsGrid(globalData *data)
{
    gint i,k;
    gint max_nb_turn = maxNbTurn(data->ptr_csu_struct);

    GtkWidget *viewport = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_viewport"));
    if (!viewport)
        g_critical(_("Widget main_window_viewport is missing in file csuper-gui.glade."));

    /* Set the grid*/
    GtkWidget *points_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(points_grid),5);
    gtk_grid_set_row_spacing(GTK_GRID(points_grid),5);
    gtk_widget_set_margin_right(points_grid,10);
    gtk_widget_set_margin_left(points_grid,10);
    gtk_widget_set_margin_top(points_grid,10);
    gtk_widget_set_margin_bottom(points_grid,10);
    gtk_widget_set_valign(GTK_WIDGET(points_grid),GTK_ALIGN_START);

    for (i=0 ; i<data->ptr_csu_struct->nb_player; i++)
        gtk_grid_attach(GTK_GRID(points_grid),gtk_separator_new(GTK_ORIENTATION_VERTICAL),2*i+1,0,1,2*(max_nb_turn+6));
    for (i=0 ; i< max_nb_turn + 5 ; i++)
        gtk_grid_attach(GTK_GRID(points_grid),gtk_separator_new(GTK_ORIENTATION_HORIZONTAL),0,2*i+1,2*(data->ptr_csu_struct->nb_player+1),1);

    /* Write the names of the players and set the expand*/
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Name")),0,0,1,1);
    gtk_widget_set_hexpand(gtk_grid_get_child_at(GTK_GRID(points_grid),0,0),TRUE);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
    {
        gtk_grid_attach(GTK_GRID(points_grid),GTK_WIDGET(createGtkLabelWithAttributes(g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[i]),15,FALSE,0,0,0,FALSE,0,0,0)),2*(i+1),0,1,1);
        gtk_widget_set_hexpand(gtk_grid_get_child_at(GTK_GRID(points_grid),2*(i+1),0),TRUE);
    }


    /* Write all the points of the players */
    for (i=0 ; i<max_nb_turn ; i++)
    {
        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("Turn %d"),i)),0,2*(i+1),1,1);

        for (k=0 ; k<data->ptr_csu_struct->nb_player ; k++)
        {
            if (data->ptr_csu_struct->nb_turn[k] >= i+1)
            {
                switch (data->ptr_csu_struct->config.decimal_place)
                {
                case 0 :
                    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.0f"),data->ptr_csu_struct->point[k][i])),2*(k+1),2*(i+1),1,1);
                    break;
                case 1 :
                    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.1f"),data->ptr_csu_struct->point[k][i])),2*(k+1),2*(i+1),1,1);
                    break;
                case 2 :
                    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.2f"),data->ptr_csu_struct->point[k][i])),2*(k+1),2*(i+1),1,1);
                    break;
                case 3 :
                    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.3f"),data->ptr_csu_struct->point[k][i])),2*(k+1),2*(i+1),1,1);
                    break;
                }
            }
        }
    }

    /* Put the spin button for the new points */
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("New points")),0,2*(max_nb_turn+1),1,1);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
    {
        GtkAdjustment *adju = gtk_adjustment_new(0,-G_MAXDOUBLE,G_MAXDOUBLE,1,0,0);
        GtkWidget *new_points_button = gtk_spin_button_new(adju,1,data->ptr_csu_struct->config.decimal_place);
        gtk_entry_set_alignment (GTK_ENTRY(new_points_button),0.5);
        gtk_entry_set_width_chars(GTK_ENTRY(new_points_button),3);
        if (data->ptr_csu_struct->config.turn_by_turn == MY_FALSE)
            gtk_entry_set_activates_default(GTK_ENTRY(new_points_button),TRUE);
        if (exceedMaxNumber(data->ptr_csu_struct) == MY_TRUE)
            gtk_editable_set_editable(GTK_EDITABLE(new_points_button),FALSE);
        gtk_grid_attach(GTK_GRID(points_grid),new_points_button,2*(i+1),2*(max_nb_turn+1),1,1);
        g_signal_connect (new_points_button,"changed", G_CALLBACK(updateTotalPointsInTurnLabel),data);
    }

    /* Write a blank line */
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(""),0,2*(max_nb_turn+2),1,1);

    /* Write the names of the players*/
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Name")),0,2*(max_nb_turn+3),1,1);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
        gtk_grid_attach(GTK_GRID(points_grid),GTK_WIDGET(createGtkLabelWithAttributes(g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[i]),15,FALSE,0,0,0,FALSE,0,0,0)),2*(i+1),2*(max_nb_turn+3),1,1);

    /* Write the total points of the players */
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Total points")),0,2*(max_nb_turn+4),1,1);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
    {
        switch (data->ptr_csu_struct->config.decimal_place)
        {
        case 0 :
            gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%0.f"),data->ptr_csu_struct->total_points[i])),2*(i+1),2*(max_nb_turn+4),1,1);
            break;
        case 1 :
            gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%1.f"),data->ptr_csu_struct->total_points[i])),2*(i+1),2*(max_nb_turn+4),1,1);
            break;
        case 2 :
            gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%2.f"),data->ptr_csu_struct->total_points[i])),2*(i+1),2*(max_nb_turn+4),1,1);
            break;
        case 3 :
            gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%3.f"),data->ptr_csu_struct->total_points[i])),2*(i+1),2*(max_nb_turn+4),1,1);
            break;
        }
    }

    /* Write the ranking of the players */
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Ranking")),0,2*(max_nb_turn+5),1,1);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%0.f"),data->ptr_csu_struct->rank[i])),2*(i+1),2*(max_nb_turn+5),1,1);

    gtk_container_add(GTK_CONTAINER(viewport),points_grid);

    gtk_widget_show_all(viewport);
}

/*!
 * \fn G_MODULE_EXPORT endOfTurn(GtkWidget *widget, gpointer data)
 *  End of a turn
 * \param[in] widget the widget which send the interrupt
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void endOfTurn(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gint i;
    float tmp_score;
    gboolean has_changed = FALSE;

    GtkWidget *viewport = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"main_window_viewport"));
    if (!viewport)
        g_critical(_("Widget main_window_viewport is missing in file csuper-gui.glade."));

    /* Test if there is a csu file opened or if the game is not finished */
    if (user_data->ptr_csu_struct == NULL)
        return;
    if (exceedMaxNumber(user_data->ptr_csu_struct) == MY_TRUE)
        return;

    gint max_nb_turn = maxNbTurn(user_data->ptr_csu_struct);

    /* Save the scores in the structure */
    for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
    {
        tmp_score = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),2*(i+1),2*(max_nb_turn+1))));

        if (user_data->ptr_csu_struct->config.turn_by_turn == 1 || tmp_score != 0)
        {
            startNewTurn(user_data->ptr_csu_struct,i);
            user_data->ptr_csu_struct->point[i][(int)user_data->ptr_csu_struct->nb_turn[i]] = tmp_score;
            endNewTurn(user_data->ptr_csu_struct,i);
            has_changed = TRUE;
        }
    }

    if (has_changed)
    {
        writeFileNewTurn(user_data->csu_filename,user_data->ptr_csu_struct);
        addLastCsuStruct(user_data);
        updateMainWindow(user_data);
    }
}

void setButtonMainWindowSensitive(globalData *data)
{
    GtkWidget *button_end_of_turn = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"button_end_of_turn"));
    if (!button_end_of_turn)
        g_critical(_("Widget button_end_of_turn is missing in file csuper-gui.glade."));

    GtkWidget *main_toolbar = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_toolbar"));
    if (!main_toolbar)
        g_critical(_("Widget main_toolbar is missing in file csuper-gui.glade."));

    GtkWidget *menu_save_as = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_save_as"));
    if (!menu_save_as)
        g_critical(_("Widget menu_save_as is missing in file csuper-gui.glade."));

    GtkWidget *menu_properties = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_properties"));
    if (!menu_properties)
        g_critical(_("Widget menu_properties is missing in file csuper-gui.glade."));

    if (data->ptr_csu_struct == NULL)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),2)),FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),12)),FALSE);
        gtk_widget_set_sensitive(menu_properties,FALSE);
        gtk_widget_set_sensitive(menu_save_as,FALSE);
        gtk_widget_set_sensitive(button_end_of_turn,FALSE);
    }
    else
    {
        if (exceedMaxNumber(data->ptr_csu_struct) == MY_TRUE)
            gtk_widget_set_sensitive(button_end_of_turn,FALSE);
        else
            gtk_widget_set_sensitive(button_end_of_turn,TRUE);

        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),2)),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),12)),TRUE);
        gtk_widget_set_sensitive(menu_properties,TRUE);
        gtk_widget_set_sensitive(menu_save_as,TRUE);
    }

    /* The undo buttons */
    GtkWidget *menu_undo = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_undo"));
    if (!menu_undo)
        g_critical(_("Widget menu_undo is missing in file csuper-gui.glade."));
    if (data->indexLastCsuStruct < data->nbLastCsuStruct-1)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),4)),TRUE);
        gtk_widget_set_sensitive(menu_undo,TRUE);
    }
    else
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),4)),FALSE);
        gtk_widget_set_sensitive(menu_undo,FALSE);
    }

    /* The redo buttons */
    GtkWidget *menu_redo = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_redo"));
    if (!menu_redo)
        g_critical(_("Widget menu_redo is missing in file csuper-gui.glade."));
    if (data->indexLastCsuStruct > 0)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),5)),TRUE);
        gtk_widget_set_sensitive(menu_redo,TRUE);
    }
    else
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),5)),FALSE);
        gtk_widget_set_sensitive(menu_redo,FALSE);
    }
}
