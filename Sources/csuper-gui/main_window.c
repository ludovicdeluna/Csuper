/*!
 * \file    main_window.c
 * \brief   Main window
 * \author  Remi BERTHO
 * \date    31/08/14
 * \version 4.2.0
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
    gfloat points,points_first,points_last,previous_points;;

    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_grid_game_config"));
    if (!grid)
        g_critical(_("Widget main_window_grid_game_config is missing in file csuper-gui.glade."));

    /* Set the grid*/
    GtkWidget *rank_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(rank_grid),20);
    gtk_grid_set_row_spacing(GTK_GRID(rank_grid),10);
    #if GTK_MINOR_VERSION >= 12
    gtk_widget_set_margin_end(rank_grid,10);
    gtk_widget_set_margin_start(rank_grid,10);
    #else
    gtk_widget_set_margin_right(rank_grid,10);
    gtk_widget_set_margin_left(rank_grid,10);
    #endif // GTK_MINOR_VERSION
    gtk_widget_set_margin_top(rank_grid,10);
    gtk_widget_set_margin_bottom(rank_grid,10);
    gtk_widget_set_vexpand(rank_grid,TRUE);

    /* Get the diff structure*/
    difference_between_player diff;
    gchar home_path[SIZE_MAX_FILE_NAME]="";
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFileDifferenceBetweenPlayer(home_path,&diff);

    /* Set the column name */
    gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Position")),0,0,1,1);
    gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Name")),1,0,1,1);
    gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Points")),2,0,1,1);
    if (diff.consecutive)
        gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Diff cons")),3,0,1,1);
    if (diff.first)
        gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Diff first")),4,0,1,1);
    if (diff.last)
        gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(_("Diff last")),5,0,1,1);

    nb=1;
    points_first = data->ptr_csu_struct->total_points[searchIndexFromPosition(data->ptr_csu_struct,1,&nb)];
    points_last = data->ptr_csu_struct->total_points[searchIndexFromPosition(data->ptr_csu_struct,data->ptr_csu_struct->nb_player,&nb)];

    /* Set all the information*/
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
    {
        nb=1;
        index=searchIndexFromPosition(data->ptr_csu_struct,i+1,&nb);
        points=data->ptr_csu_struct->total_points[index];

        gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%d"),i+2-nb)),0,i+1,1,1);

        gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[index])),1,i+1,1,1);

        switch (data->ptr_csu_struct->config.decimal_place)
        {
        case 0 :
            gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.0f"),points)),2,i+1,1,1);
            if (diff.first)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.0f"),fabs(points_first-points))),4,i+1,1,1);
            if (diff.last)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.0f"),fabs(points_last-points))),5,i+1,1,1);
            if (diff.consecutive && i>0)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.0f"),fabs(previous_points-points))),3,i+1,1,1);
            break;
        case 1 :
            gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.1f"),points)),2,i+1,1,1);
            if (diff.first)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.1f"),fabs(points_first-points))),4,i+1,1,1);
            if (diff.last)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.1f"),fabs(points_last-points))),5,i+1,1,1);
            if (diff.consecutive && i>0)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.1f"),fabs(previous_points-points))),3,i+1,1,1);
            break;
        case 2 :
            gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.2f"),points)),2,i+1,1,1);
            if (diff.first)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.2f"),fabs(points_first-points))),4,i+1,1,1);
            if (diff.last)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.2f"),fabs(points_last-points))),5,i+1,1,1);
            if (diff.consecutive && i>0)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.2f"),fabs(previous_points-points))),3,i+1,1,1);
            break;
        case 3 :
            gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.3f"),points)),2,i+1,1,1);
            if (diff.first)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.3f"),fabs(points_first-points))),4,i+1,1,1);
            if (diff.last)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.3f"),fabs(points_last-points))),5,i+1,1,1);
            if (diff.consecutive && i>0)
                gtk_grid_attach(GTK_GRID(rank_grid),gtk_label_new(g_strdup_printf(_("%.3f"),fabs(previous_points-points))),3,i+1,1,1);
            break;
        }

        previous_points=points;
    }

    gtk_grid_attach(GTK_GRID(grid),rank_grid,0,1,1,1);

    gtk_widget_show_all(rank_grid);
}

/*!
 * \fn void updateMainWindow(globalData *data,bool editable)
 *  Update the main window
 * \param[in] data the globalData
 * \param[in] editable indicate if we can add points in the game
 */
void updateMainWindow(globalData *data,bool editable)
{
    deleteRanking(data);
    createRanking(data);
    updateDistributorLabel(data);
    deletePoints(data);
    createPointsGrid(data,editable);
    updateTotalPointsInTurnLabel(data,editable);
    setButtonMainWindow(data);
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
 * \fn G_MODULE_EXPORT void updateTotalPointsInTurnLabelSignal(GtkWidget *widget, gpointer data)
 *  Update the total points in the turn
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void updateTotalPointsInTurnLabelSignal(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    updateTotalPointsInTurnLabel(user_data,TRUE);
}

/*!
 * \fn void updateTotalPointsInTurnLabel(globalData data,bool updatable_points)
 *  Update the label which indicate the total points which will be add this turn
 * \param[in] data the globalData
 * \param[in] updatable_points indicate if we can add points in the game
 */
void updateTotalPointsInTurnLabel(globalData *data,bool updatable_points)
{
    GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_label_total_points_in_turn"));
    if (!label)
        g_critical(_("Widget main_window_label_total_points_in_turn is missing in file csuper-gui.glade."));

    if (updatable_points)
    {
        gint i;
        gfloat total_points=0;
        gint max_nb_turn = maxNbTurn(data->ptr_csu_struct);

        GtkWidget *viewport = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_viewport"));
        if (!viewport)
            g_critical(_("Widget main_window_viewport is missing in file csuper-gui.glade."));

        for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
            total_points += gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),2*(i+1),2*(max_nb_turn+1))));

        switch (data->ptr_csu_struct->config.decimal_place)
        {
        case 0 :
            gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("There are %.0f points given in the turn"),total_points));
            break;
        case 1 :
            gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("There are %.1f points given in the turn"),total_points));
            break;
        case 2 :
            gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("There are %.2f points given in the turn"),total_points));
            break;
        case 3 :
            gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("There are %.3f points given in the turn"),total_points));
            break;
        }
    }
    else
       gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("You cannot give points")));
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
 * \fn void createPointsGrid(globalData *data,bool spin_button)
 *  Create the points grid
 * \param[in] data the globalData
 * \param[in] spin_button indicate if we must add a spin button for the new points
 */
void createPointsGrid(globalData *data,bool spin_button)
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
    #if GTK_MINOR_VERSION >= 12
    gtk_widget_set_margin_end(points_grid,10);
    gtk_widget_set_margin_start(points_grid,10);
    #else
    gtk_widget_set_margin_right(points_grid,10);
    gtk_widget_set_margin_left(points_grid,10);
    #endif // GTK_MINOR_VERSION
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
    if (spin_button)
    {
        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("New points")),0,2*(max_nb_turn+1),1,1);
        for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
        {
            GtkAdjustment *adju = gtk_adjustment_new(0,-G_MAXDOUBLE,G_MAXDOUBLE,1,0,0);
            GtkWidget *new_points_button = gtk_spin_button_new(adju,1,data->ptr_csu_struct->config.decimal_place);
            gtk_entry_set_alignment (GTK_ENTRY(new_points_button),0.5);
            gtk_entry_set_width_chars(GTK_ENTRY(new_points_button),3);
            if (data->ptr_csu_struct->config.turn_based == false)
                gtk_entry_set_activates_default(GTK_ENTRY(new_points_button),true);
            if (exceedMaxNumber(data->ptr_csu_struct) == true)
                gtk_editable_set_editable(GTK_EDITABLE(new_points_button),FALSE);
            gtk_grid_attach(GTK_GRID(points_grid),new_points_button,2*(i+1),2*(max_nb_turn+1),1,1);
            g_signal_connect (new_points_button,"value-changed", G_CALLBACK(updateTotalPointsInTurnLabelSignal),data);


            /* g_signal_connect (new_points_button,"changed", G_CALLBACK(setButtonMainWindowClipboardSensitive),data);*/
        }

        /* Write a blank line */
        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(""),0,2*(max_nb_turn+2),1,1);
    }

    /* Write the names of the players*/
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Name")),0,2*(max_nb_turn+3),1,1);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
        gtk_grid_attach(GTK_GRID(points_grid),GTK_WIDGET(createGtkLabelWithAttributes(g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[i]),15,FALSE,0,0,0,FALSE,0,0,0)),2*(i+1),2*(max_nb_turn+3),1,1);

    /* Write the total points of the players */
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Total number of points")),0,2*(max_nb_turn+4),1,1);
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
 * \param[in] widget the widget which send the signal
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

    GtkWidget *scrolled_window = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"main_window_scrolled_window"));
    if (!scrolled_window)
        g_critical(_("Widget main_window_scrolled_window is missing in file csuper-gui.glade."));

    /* Test if there is a csu file opened or if the game is not finished */
    if (user_data->ptr_csu_struct == NULL)
        return;

    gint max_nb_turn = maxNbTurn(user_data->ptr_csu_struct);

    /* Save the scores in the structure */
    if (user_data->ptr_csu_struct->config.turn_based == 0)
    {
        /* Save the scores in the structure */
        for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
        {
            tmp_score = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),2*(i+1),2*(max_nb_turn+1))));

            if (tmp_score != 0)
            {
                startNewTurn(user_data->ptr_csu_struct,i);
                user_data->ptr_csu_struct->point[i][(int)user_data->ptr_csu_struct->nb_turn[i]] = tmp_score;
                endNewTurn(user_data->ptr_csu_struct,i);
                has_changed = TRUE;
            }
        }
    }
    else
    {
        startNewTurn(user_data->ptr_csu_struct,-1);
        for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
            user_data->ptr_csu_struct->point[i][(int)user_data->ptr_csu_struct->nb_turn[i]] =
                gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),2*(i+1),2*(max_nb_turn+1))));
        endNewTurn(user_data->ptr_csu_struct,-1);

        has_changed = TRUE;

    }

    if (has_changed)
    {
        if (writeFileNewTurn(user_data->csu_filename,user_data->ptr_csu_struct) == false)
            saveFileError(user_data);
        addLastCsuStruct(user_data);
        updateMainWindow(user_data,!exceedMaxNumber(user_data->ptr_csu_struct));

        /* Scroll the window at the bottom */
        gtk_adjustment_set_upper(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrolled_window)),
            gtk_adjustment_get_upper(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrolled_window)))+
            gtk_adjustment_get_step_increment(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrolled_window))));

        gtk_adjustment_set_value(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrolled_window)),
            gtk_adjustment_get_upper(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrolled_window)))
            -gtk_adjustment_get_page_size(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrolled_window))));


        /* Test if the game is over */
        if (exceedMaxNumber(user_data->ptr_csu_struct) == true)
            gameOver(user_data);
    }
}


/*!
 * \fn void gameOver(globalData *data)
 *  Display the game over window
 * \param[in] data the globalData
 */
void gameOver(globalData *data)
{
    GtkWidget *window_game_over = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"dialog_game_over"));
    if (!window_game_over)
        g_critical(_("Widget dialog_game_over is missing in file csuper-gui.glade."));

    GtkWidget *fixed = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"dialog_game_over_fixed"));
    if (!fixed)
        g_critical(_("Widget dialog_game_over_fixed is missing in file csuper-gui.glade."));

    GtkWidget *podium =gtk_image_new_from_file("Images/Podium.png");
    gtk_fixed_put(GTK_FIXED(fixed),podium,0,20);


    /*Initialization of the position array*/
    int pos[3]={0,1,2};
    int i;
    int un_pris=false;
    int deux_pris=false;
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
    {
        if (data->ptr_csu_struct->rank[i] == 3 || (un_pris && deux_pris && data->ptr_csu_struct->rank[i] == 1) || (deux_pris && data->ptr_csu_struct->rank[i] == 2))
            pos[2]=i;

        if ((data->ptr_csu_struct->rank[i] == 2 && !deux_pris ) || (un_pris && data->ptr_csu_struct->rank[i] == 1 && !deux_pris))
        {
            pos[1]=i;
            deux_pris=true;
        }
        if (data->ptr_csu_struct->rank[i] == 1 && !un_pris)
        {
            pos[0]=i;
            un_pris=true;
        }
    }


    /* Put the different names */
    GtkWidget *label_1 = GTK_WIDGET(createGtkLabelWithAttributes(data->ptr_csu_struct->player_names[pos[0]],15,TRUE,0,50,0,FALSE,0,0,0));
    gtk_fixed_put(GTK_FIXED(fixed),label_1,250-g_utf8_strlen(data->ptr_csu_struct->player_names[pos[0]],SIZE_MAX_NAME)*9/2,47);

    GtkWidget *label_2;
    if (data->ptr_csu_struct->nb_player >=2)
    {
        label_2 = GTK_WIDGET(createGtkLabelWithAttributes(data->ptr_csu_struct->player_names[pos[1]],15,TRUE,0,0,100,FALSE,0,0,0));
        gtk_fixed_put(GTK_FIXED(fixed),label_2,90-g_utf8_strlen(data->ptr_csu_struct->player_names[pos[1]],SIZE_MAX_NAME)*9/2,118);
    }

    GtkWidget *label_3;
    if (data->ptr_csu_struct->nb_player >=3)
    {
        label_3 = GTK_WIDGET(createGtkLabelWithAttributes(data->ptr_csu_struct->player_names[pos[2]],15,TRUE,100,0,0,FALSE,0,0,0));
        gtk_fixed_put(GTK_FIXED(fixed),label_3,410-g_utf8_strlen(data->ptr_csu_struct->player_names[pos[2]],SIZE_MAX_NAME)*9/2,158);
    }


    gtk_widget_show_all(window_game_over);
    gtk_dialog_run(GTK_DIALOG (window_game_over));
    gtk_widget_hide (window_game_over);

    gtk_widget_destroy(podium);
    gtk_widget_destroy(label_1);
    if (data->ptr_csu_struct->nb_player >=2)
        gtk_widget_destroy(label_2);
    if (data->ptr_csu_struct->nb_player >=3)
        gtk_widget_destroy(label_3);
}

/*!
 * \fn void setButtonMainWindow(globalData *data)
 *  Set the button of the main window sensitive or not
 * \param[in] data the globalData
 */
void setButtonMainWindow(globalData *data)
{
    GtkWidget *button_end_of_turn = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"button_end_of_turn"));
    if (!button_end_of_turn)
        g_critical(_("Widget button_end_of_turn is missing in file csuper-gui.glade."));

    GtkWidget *button_change_distributor = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window_button_change_distributor"));
    if (!button_change_distributor)
        g_critical(_("Widget main_window_button_change_distributor is missing in file csuper-gui.glade."));

    GtkWidget *main_toolbar = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_toolbar"));
    if (!main_toolbar)
        g_critical(_("Widget main_toolbar is missing in file csuper-gui.glade."));

    GtkWidget *menu_save_as = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_save_as"));
    if (!menu_save_as)
        g_critical(_("Widget menu_save_as is missing in file csuper-gui.glade."));

    GtkWidget *menu_properties = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_properties"));
    if (!menu_properties)
        g_critical(_("Widget menu_properties is missing in file csuper-gui.glade."));

    GtkWidget *menu_delete_file = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_delete_file"));
    if (!menu_properties)
        g_critical(_("Widget menu_delete_file is missing in file csuper-gui.glade."));

    GtkWidget *menu_print = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_print"));
    if (!menu_properties)
        g_critical(_("Widget menu_print is missing in file csuper-gui.glade."));

    GtkWidget *menu_podium = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_display_podium"));
    if (!menu_podium)
        g_critical(_("Widget menu_display_podium is missing in file csuper-gui.glade."));


    /* Set the recent csu file open */
    GtkRecentFilter *recent_filter_csu = GTK_RECENT_FILTER(gtk_builder_get_object(data->ptr_builder,"recent_filter_csu"));
    if (!recent_filter_csu)
        g_critical(_("Widget recent_filter_csu is missing in file csuper-gui.glade."));

    GtkWidget *recent_chooser = gtk_recent_chooser_menu_new();
    gtk_recent_chooser_set_filter(GTK_RECENT_CHOOSER(recent_chooser),recent_filter_csu);
    gtk_recent_chooser_set_show_not_found(GTK_RECENT_CHOOSER(recent_chooser),FALSE);
    gtk_menu_tool_button_set_menu(GTK_MENU_TOOL_BUTTON(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),1)),recent_chooser);
    g_signal_connect(recent_chooser,"item-activated", G_CALLBACK(recentCsuFileOpen),data);

    #ifdef ENABLE_DEPRECIATE_FUNCTIONS
    GtkWidget *menu_preferences_game = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_preference_game_config"));
    if (!menu_preferences_game)
        g_critical(_("Widget menu_preference_game_config is missing in file csuper-gui.glade."));

    GtkWidget *menu_preferences_toolbar = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_preferences_toolbar_button"));
    if (!menu_preferences_toolbar)
        g_critical(_("Widget menu_preferences_toolbar_button is missing in file csuper-gui.glade."));

    /* Set the image of the menu */
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_podium),gtk_image_new_from_file("Images/Podium_icon.png"));
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_preferences_game),gtk_image_new_from_stock("gtk-preferences",GTK_ICON_SIZE_MENU));
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_preferences_toolbar),gtk_image_new_from_stock("gtk-preferences",GTK_ICON_SIZE_MENU));
    #endif


    /* Set the toggle button of the display preferences */
    difference_between_player diff;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFileDifferenceBetweenPlayer(home_path,&diff);

    GtkWidget *consecutive = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_display_consecutive"));
    if (!consecutive)
        g_critical(_("Widget menu_display_consecutive is missing in file csuper-gui.glade."));

    GtkWidget *first = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_display_first"));
    if (!first)
        g_critical(_("Widget menu_display_consecutive is missing in file csuper-gui.glade."));

    GtkWidget *last = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_display_last"));
    if (!last)
        g_critical(_("Widget menu_display_last is missing in file csuper-gui.glade."));

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(consecutive),diff.consecutive);
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(first),diff.first);
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(last),diff.last);


    /* If there is no csu file opened */
    if (data->ptr_csu_struct == NULL)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),2)),FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),4)),FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),5)),FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),15)),FALSE);
        gtk_widget_set_sensitive(menu_properties,FALSE);
        gtk_widget_set_sensitive(menu_save_as,FALSE);
        gtk_widget_set_sensitive(menu_delete_file,FALSE);
        gtk_widget_set_sensitive(menu_print,FALSE);
        gtk_widget_set_sensitive(menu_podium,FALSE);
        gtk_widget_set_sensitive(button_end_of_turn,FALSE);
        gtk_widget_set_sensitive(button_change_distributor,FALSE);
    }
    else
    {
        if (exceedMaxNumber(data->ptr_csu_struct) == true)
            gtk_widget_set_sensitive(button_end_of_turn,FALSE);
        else
            gtk_widget_set_sensitive(button_end_of_turn,TRUE);

        if (data->ptr_csu_struct->config.use_distributor == 0)
            gtk_widget_set_sensitive(button_change_distributor,FALSE);
        else
            gtk_widget_set_sensitive(button_change_distributor,TRUE);

        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),2)),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),4)),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),5)),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),15)),TRUE);
        gtk_widget_set_sensitive(menu_properties,TRUE);
        gtk_widget_set_sensitive(menu_save_as,TRUE);
        gtk_widget_set_sensitive(menu_delete_file,TRUE);
        gtk_widget_set_sensitive(menu_print,TRUE);
        gtk_widget_set_sensitive(menu_podium,TRUE);
    }

    /* The undo buttons */
    GtkWidget *menu_undo = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_undo"));
    if (!menu_undo)
        g_critical(_("Widget menu_undo is missing in file csuper-gui.glade."));
    if (data->indexLastCsuStruct < data->nbLastCsuStruct-1)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),7)),TRUE);
        gtk_widget_set_sensitive(menu_undo,TRUE);
    }
    else
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),7)),FALSE);
        gtk_widget_set_sensitive(menu_undo,FALSE);
    }

    /* The redo buttons */
    GtkWidget *menu_redo = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"menu_redo"));
    if (!menu_redo)
        g_critical(_("Widget menu_redo is missing in file csuper-gui.glade."));
    if (data->indexLastCsuStruct > 0)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),8)),TRUE);
        gtk_widget_set_sensitive(menu_redo,TRUE);
    }
    else
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),8)),FALSE);
        gtk_widget_set_sensitive(menu_redo,FALSE);
    }
}

/*!
 * \fn G_MODULE_EXPORT gboolean setButtonMainWindowClipboardSensitive(gpointer data)
 *  Delete the selected text
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT gboolean setButtonMainWindowClipboardSensitive(gpointer data)
{
    globalData *user_data = (globalData*) data;

    GtkWidget *main_toolbar = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"main_toolbar"));
    if (!main_toolbar)
        g_critical(_("Widget main_toolbar is missing in file csuper-gui.glade."));

    GtkWidget *menu_cut = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"menu_cut"));
    if (!menu_cut)
        g_critical(_("Widget menu_cut is missing in file csuper-gui.glade."));
    GtkWidget *menu_copy = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"menu_copy"));
    if (!menu_copy)
        g_critical(_("Widget menu_copy is missing in file csuper-gui.glade."));
    GtkWidget *menu_paste = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"menu_paste"));
    if (!menu_paste)
        g_critical(_("Widget menu_paste is missing in file csuper-gui.glade."));
    GtkWidget *menu_delete = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"menu_delete"));
    if (!menu_delete)
        g_critical(_("Widget menu_delete is missing in file csuper-gui.glade."));

    if(GTK_IS_EDITABLE(gtk_window_get_focus(GTK_WINDOW(user_data->ptr_main_window))))
    {
        if (gtk_clipboard_wait_for_text(user_data->ptr_clipboard_selected) == NULL)
        {
            gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),10)),FALSE);
            gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),11)),FALSE);
            gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),13)),FALSE);
            gtk_widget_set_sensitive(menu_cut,FALSE);
            gtk_widget_set_sensitive(menu_copy,FALSE);
            gtk_widget_set_sensitive(menu_delete,FALSE);
        }
        else
        {
            gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),10)),TRUE);
            gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),11)),TRUE);
            gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),13)),TRUE);
            gtk_widget_set_sensitive(menu_cut,TRUE);
            gtk_widget_set_sensitive(menu_copy,TRUE);
            gtk_widget_set_sensitive(menu_delete,TRUE);
        }

        if (gtk_clipboard_wait_for_text(user_data->ptr_clipboard) == NULL)
        {
            gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),12)),FALSE);
            gtk_widget_set_sensitive(menu_paste,FALSE);
        }
        else
        {
            gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),12)),TRUE);
            gtk_widget_set_sensitive(menu_paste,TRUE);
        }
    }
    else
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),10)),FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),11)),FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),12)),FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),13)),FALSE);
        gtk_widget_set_sensitive(menu_cut,FALSE);
        gtk_widget_set_sensitive(menu_copy,FALSE);
        gtk_widget_set_sensitive(menu_paste,FALSE);
        gtk_widget_set_sensitive(menu_delete,FALSE);
    }

    return G_SOURCE_CONTINUE;
}

/*!
 * \fn void readMainWindowSize(globalData *data)
 *  Read and apply the main window size store is the file
 * \param[in] data the globalData
 */
void readMainWindowSize(globalData *data)
{
    main_window_size size;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFileMainWidowSize(home_path,&size);

    GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(data->ptr_builder,"main_window"));
    if (!main_window)
        g_critical(_("Widget main_window is missing in file csuper-gui.glade."));

    gtk_window_resize(GTK_WINDOW(main_window),size.width,size.height);

    if (size.is_maximize == true)
        gtk_window_maximize(GTK_WINDOW(main_window));
    else
        gtk_window_unmaximize(GTK_WINDOW(main_window));
}

/*!
 * \fn G_MODULE_EXPORT gboolean saveMainWindowSize(GtkWidget *widget,GdkEvent *event,gpointer data)
 *  Save the main window size in a file
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 * \param[in] event the GdkEventConfigure which triggered this signal
 */
G_MODULE_EXPORT gboolean saveMainWindowSize(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    globalData *user_data = (globalData*) data;
    main_window_size size;
    gchar home_path[SIZE_MAX_FILE_NAME]="";
    GdkEventConfigure configure_event = event->configure;

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE

    GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"main_window"));
    if (!main_window)
        g_critical(_("Widget main_window is missing in file csuper-gui.glade."));

    size.height = configure_event.height;
    size.width = configure_event.width;
    #if GTK_MINOR_VERSION >= 12
    size.is_maximize=gtk_window_is_maximized(GTK_WINDOW(main_window));
    #else
    size.is_maximize=false;
    #endif

    createFileMainWidowSize(home_path,size);

    return FALSE;
}

/*!
 * \fn G_MODULE_EXPORT changeDistributorButton(GtkWidget *widget, gpointer data)
 *  Change distributor
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void changeDistributorButton(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    gint i;

    GtkWidget *dialog = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"change_distributor_dialog"));
    if (!dialog)
        g_critical(_("Widget change_distributor_dialog is missing in file csuper-gui.glade."));

    GtkWidget *viewport = GTK_WIDGET(gtk_builder_get_object(user_data->ptr_builder,"change_distributor_dialog_viewport"));
    if (!viewport)
        g_critical(_("Widget change_distributor_dialog_viewport is missing in file csuper-gui.glade."));


    /* Set the grid */
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid),5);
    #if GTK_MINOR_VERSION >= 12
    gtk_widget_set_margin_end(grid,10);
    gtk_widget_set_margin_start(grid,10);
    #else
    gtk_widget_set_margin_right(grid,10);
    gtk_widget_set_margin_left(grid,10);
    #endif // GTK_MINOR_VERSION
    gtk_widget_set_margin_top(grid,10);
    gtk_widget_set_margin_bottom(grid,10);
    gtk_widget_set_vexpand(grid,TRUE);


    /* Set the rbdio button */
    gtk_grid_attach(GTK_GRID(grid),gtk_radio_button_new_with_label(NULL,user_data->ptr_csu_struct->player_names[0]),0,0,1,1);

    for (i=1 ; i<user_data->ptr_csu_struct->nb_player ; i++)
        gtk_grid_attach(GTK_GRID(grid),gtk_radio_button_new_with_label_from_widget(
            GTK_RADIO_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),0,0)),
            user_data->ptr_csu_struct->player_names[i]),0,i,1,1);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),0,user_data->ptr_csu_struct->distributor)),TRUE);

    gtk_container_add(GTK_CONTAINER(viewport),grid);

    gtk_widget_show_all(dialog);

    switch (gtk_dialog_run(GTK_DIALOG(dialog)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
            for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
            {
                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),0,i))))
                    break;
            }
            changeDistributor(user_data->ptr_csu_struct,i);
            updateDistributorLabel(user_data);
			break;
		}
		case GTK_RESPONSE_CANCEL:
        {
            break;
        }
	}

	gtk_widget_hide(dialog);
	gtk_widget_destroy(grid);
}
