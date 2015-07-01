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

#include "main_window.h"



/*!
 * \fn void noCsuFileRanking(globalData *data)
 *  Fill the ranking with no ranking
 * \param[in] data the globalData
 */
void noCsuFileRanking(globalData *data)
{
    GtkWidget *viewport = getWidgetFromBuilder(data->ptr_builder,"viewport_ranking");

    GtkWidget *label = gtk_label_new(_("No csu file loaded"));

    gtk_widget_set_vexpand(label,TRUE);

    gtk_container_add(GTK_CONTAINER(viewport),label);
}

/*!
 * \fn void deleteRanking(globalData *data)
 *  Delete the ranking
 * \param[in] data the globalData
 */
void deleteRanking(globalData *data)
{
    GtkWidget *viewport = getWidgetFromBuilder(data->ptr_builder,"viewport_ranking");

    gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(viewport)));
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

    GtkWidget *viewport = getWidgetFromBuilder(data->ptr_builder,"viewport_ranking");

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

    gtk_container_add(GTK_CONTAINER(viewport),rank_grid);

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
    updateCalculatorMainWindow(NULL,data);
}

/*!
 * \fn void updateDistributorLabel(globalData *data)
 *  Update the distributor
 * \param[in] data the globalData
 */
void updateDistributorLabel(globalData *data)
{
    GtkWidget *label = getWidgetFromBuilder(data->ptr_builder,"main_window_label_distributor");

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
    GtkWidget *label = getWidgetFromBuilder(data->ptr_builder,"main_window_label_total_points_in_turn");

    if (updatable_points)
    {
        gint i;
        gfloat total_points=0;
        gint max_nb_turn = maxNbTurn(data->ptr_csu_struct);

        GtkWidget *viewport = getWidgetFromBuilder(data->ptr_builder,"main_window_viewport");

        for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
            total_points += gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),6*i+2,2*(max_nb_turn+1)+2)));

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
    GtkWidget *viewport = getWidgetFromBuilder(data->ptr_builder,"main_window_viewport");

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
    GtkWidget *viewport = getWidgetFromBuilder(data->ptr_builder,"main_window_viewport");

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
    gint points_grid_width;

    GtkWidget *viewport = getWidgetFromBuilder(data->ptr_builder,"main_window_viewport");

    // Read the preferences
    score_display score;
    gchar home_path[SIZE_MAX_FILE_NAME]="";
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFileScoreDisplay(home_path,&score);
    if (score.total_points || score.ranking)
        points_grid_width = 1;
    else
        points_grid_width = 5;

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


    /* Add separator */
    for (i=0 ; i<data->ptr_csu_struct->nb_player+3; i++)
    {
        if (i<=data->ptr_csu_struct->nb_player)
            gtk_grid_attach(GTK_GRID(points_grid),gtk_separator_new(GTK_ORIENTATION_VERTICAL),6*i+1,0,1,2*(max_nb_turn+7));
        else if (score.edit_suppr)
            gtk_grid_attach(GTK_GRID(points_grid),gtk_separator_new(GTK_ORIENTATION_VERTICAL),6*i+1,5,1,2*(max_nb_turn-1)+1);
    }
    for (i=0 ; i< max_nb_turn + 6 ; i++)
    {
        if ( i < max_nb_turn + 1 && score.edit_suppr && i > 0 && max_nb_turn != 1)
            gtk_grid_attach(GTK_GRID(points_grid),gtk_separator_new(GTK_ORIENTATION_HORIZONTAL),0,2*i+3,6*(data->ptr_csu_struct->nb_player+2)+2,1);
        else
            gtk_grid_attach(GTK_GRID(points_grid),gtk_separator_new(GTK_ORIENTATION_HORIZONTAL),0,2*i+3,6*data->ptr_csu_struct->nb_player+2,1);
    }


    /* Write the names of the players and set the expand*/
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Name")),0,0,1,1);
    gtk_widget_set_hexpand(gtk_grid_get_child_at(GTK_GRID(points_grid),0,0),TRUE);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
    {
        gtk_grid_attach(GTK_GRID(points_grid),GTK_WIDGET(createGtkLabelWithAttributes(g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[i]),15,FALSE,0,0,0,FALSE,0,0,0)),6*i+2,0,5,1);
        gtk_widget_set_hexpand(gtk_grid_get_child_at(GTK_GRID(points_grid),6*i+2,0),TRUE);
    }


    // Set the legend
    gtk_grid_attach(GTK_GRID(points_grid),gtk_separator_new(GTK_ORIENTATION_HORIZONTAL),0,1,6*data->ptr_csu_struct->nb_player+2,1);
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Legend")),0,2,1,1);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
    {
        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Points")),6*i+2,2,points_grid_width,1);
        gtk_widget_set_hexpand(gtk_grid_get_child_at(GTK_GRID(points_grid),6*i+2,2),TRUE);
    }
    if (score.total_points)
    {
        for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
        {
            gtk_grid_attach(GTK_GRID(points_grid),gtk_separator_new(GTK_ORIENTATION_VERTICAL),6*i+3,1,1,2*(max_nb_turn+1)+1);
            gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Total")),6*i+4,2,1,1);
            gtk_widget_set_hexpand(gtk_grid_get_child_at(GTK_GRID(points_grid),6*i+4,2),TRUE);
        }
    }
    if (score.ranking)
    {
        for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
        {
            gtk_grid_attach(GTK_GRID(points_grid),gtk_separator_new(GTK_ORIENTATION_VERTICAL),6*i+5,1,1,2*(max_nb_turn+1)+1);
            gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Ranking")),6*i+6,2,1,1);
            gtk_widget_set_hexpand(gtk_grid_get_child_at(GTK_GRID(points_grid),6*i+6,2),TRUE);
        }
    }

    // Set the button delete and edit
    if (score.edit_suppr)
    {
        GtkWidget *tmp_edit_button;
        GtkWidget *tmp_delete_button;
        #if GTK_MINOR_VERSION < 10
        GtkWidget *tmp_image_edit;
        GtkWidget *tmp_image_delete;
        #endif // GTK_MINOR_VERSION
        for (i=1 ; i< max_nb_turn ; i++)
        {
            #if GTK_MINOR_VERSION >= 10
            tmp_edit_button = GTK_WIDGET(gtk_button_new_from_icon_name("gtk-edit",GTK_ICON_SIZE_BUTTON));
            tmp_delete_button = GTK_WIDGET(gtk_button_new_from_icon_name("gtk-delete",GTK_ICON_SIZE_BUTTON));
            #else
            tmp_image_edit = gtk_image_new_from_stock(GTK_STOCK_EDIT,GTK_ICON_SIZE_BUTTON);
            tmp_edit_button = gtk_button_new();
            gtk_button_set_image(GTK_BUTTON(tmp_edit_button),tmp_image_edit);
            tmp_image_delete = gtk_image_new_from_stock(GTK_STOCK_DELETE,GTK_ICON_SIZE_BUTTON);
            tmp_delete_button = gtk_button_new();
            gtk_button_set_image(GTK_BUTTON(tmp_delete_button),tmp_image_delete);
            #endif
            gtk_grid_attach(GTK_GRID(points_grid),tmp_edit_button,6*data->ptr_csu_struct->nb_player+2,2*(i+1)+2,5,1);
            gtk_grid_attach(GTK_GRID(points_grid),tmp_delete_button,6*(data->ptr_csu_struct->nb_player+1)+2,2*(i+1)+2,5,1);
            g_signal_connect(tmp_delete_button,"clicked", G_CALLBACK(deleteTurnSignal),data);
            g_signal_connect(tmp_edit_button,"clicked", G_CALLBACK(changeTurnSignal),data);
        }
    }


    /* Write all the points, the total point and the ranking of the players */
    for (i=0 ; i<max_nb_turn ; i++)
    {
        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("Turn %d"),i)),0,2*(i+1)+2,1,1);

        for (k=0 ; k<data->ptr_csu_struct->nb_player ; k++)
        {
            // Points
            if (data->ptr_csu_struct->nb_turn[k] >= i+1)
            {
                switch (data->ptr_csu_struct->config.decimal_place)
                {
                case 0 :
                    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.0f"),data->ptr_csu_struct->point[k][i])),6*k+2,2*(i+1)+2,points_grid_width,1);
                    break;
                case 1 :
                    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.1f"),data->ptr_csu_struct->point[k][i])),6*k+2,2*(i+1)+2,points_grid_width,1);
                    break;
                case 2 :
                    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.2f"),data->ptr_csu_struct->point[k][i])),6*k+2,2*(i+1)+2,points_grid_width,1);
                    break;
                case 3 :
                    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.3f"),data->ptr_csu_struct->point[k][i])),6*k+2,2*(i+1)+2,points_grid_width,1);
                    break;
                }
                // Total points
                if (score.total_points)
                {
                    switch (data->ptr_csu_struct->config.decimal_place)
                    {
                    case 0 :
                        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.0f"),pointsAtTurn(data->ptr_csu_struct,k,i))),6*k+4,2*(i+1)+2,1,1);
                        break;
                    case 1 :
                        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.1f"),pointsAtTurn(data->ptr_csu_struct,k,i))),6*k+4,2*(i+1)+2,1,1);
                        break;
                    case 2 :
                        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.2f"),pointsAtTurn(data->ptr_csu_struct,k,i))),6*k+4,2*(i+1)+2,1,1);
                        break;
                    case 3 :
                        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.3f"),pointsAtTurn(data->ptr_csu_struct,k,i))),6*k+4,2*(i+1)+2,1,1);
                        break;
                    }
                }
                // Ranking
                if (score.ranking)
                    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%d"),rankAtTurn(data->ptr_csu_struct,k,i))),6*k+6,2*(i+1)+2,1,1);
            }
        }
    }

    /* Put the spin button for the new points */
    if (spin_button)
    {
        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("New points")),0,2*(max_nb_turn+1)+2,1,1);
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
            gtk_grid_attach(GTK_GRID(points_grid),new_points_button,6*i+2,2*(max_nb_turn+1)+2,5,1);
            g_signal_connect (new_points_button,"value-changed", G_CALLBACK(updateTotalPointsInTurnLabelSignal),data);


            /* g_signal_connect (new_points_button,"changed", G_CALLBACK(setButtonMainWindowClipboardSensitive),data);*/
        }

        /* Write a blank line */
        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(""),0,2*(max_nb_turn+2)+2,1,1);
    }

    /* Write the names of the players*/
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Name")),0,2*(max_nb_turn+3)+2,1,1);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
        gtk_grid_attach(GTK_GRID(points_grid),GTK_WIDGET(createGtkLabelWithAttributes(g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[i]),15,FALSE,0,0,0,FALSE,0,0,0)),6*i+2,2*(max_nb_turn+3)+2,5,1);

    /* Write the total points of the players */
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Total number of points")),0,2*(max_nb_turn+4)+2,1,1);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
    {
        switch (data->ptr_csu_struct->config.decimal_place)
        {
        case 0 :
            gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.0f"),data->ptr_csu_struct->total_points[i])),6*i+2,2*(max_nb_turn+4)+2,5,1);
            break;
        case 1 :
            gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.1f"),data->ptr_csu_struct->total_points[i])),6*i+2,2*(max_nb_turn+4)+2,5,1);
            break;
        case 2 :
            gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.2f"),data->ptr_csu_struct->total_points[i])),6*i+2,2*(max_nb_turn+4)+2,5,1);
            break;
        case 3 :
            gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%.3f"),data->ptr_csu_struct->total_points[i])),6*i+2,2*(max_nb_turn+4)+2,5,1);
            break;
        }
    }

    /* Write the ranking of the players */
    gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(_("Ranking")),0,2*(max_nb_turn+5)+2,1,1);
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
        gtk_grid_attach(GTK_GRID(points_grid),gtk_label_new(g_strdup_printf(_("%0.f"),data->ptr_csu_struct->rank[i])),6*i+2,2*(max_nb_turn+5)+2,5,1);

    gtk_container_add(GTK_CONTAINER(viewport),points_grid);

    gtk_widget_show_all(viewport);
}


/*!
 * \fn G_MODULE_EXPORT deleteTurnSignal(GtkWidget *widget, gpointer data)
 *  Delete a turn
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void deleteTurnSignal(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    GtkWidget *viewport = getWidgetFromBuilder(user_data->ptr_builder,"main_window_viewport");

    gint turn;

    // Get the turn
    for (turn = 0 ; widget != gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),6*(user_data->ptr_csu_struct->nb_player+1)+2,2*(turn+1)+2) ; turn ++);

    if (user_data->ptr_csu_struct->config.turn_based == 1)
    {
        deleteTurn(user_data->ptr_csu_struct,0,turn);

        if (writeFileNewTurn(user_data->csu_filename,user_data->ptr_csu_struct) == false)
            saveFileError(user_data);
        addLastCsuStruct(user_data);
        updateMainWindow(user_data,!exceedMaxNumber(user_data->ptr_csu_struct));

        /* Test if the game is over */
        if (exceedMaxNumber(user_data->ptr_csu_struct) == true)
            gameOver(user_data);
    }
    else
    {
        GtkWidget *viewport_dialog = getWidgetFromBuilder(user_data->ptr_builder,"delete_turn_dialog_viewport");

        // Set the grid
        GtkWidget *grid = gtk_grid_new();
        gtk_grid_set_column_spacing(GTK_GRID(grid),5);
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

        int i,j;
        bool first_attach = false;

        // Set the radio button
        for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
        {
            if (user_data->ptr_csu_struct->nb_turn[i] > turn)
            {
                if (first_attach)
                    gtk_grid_attach(GTK_GRID(grid),gtk_radio_button_new_with_label_from_widget(
                        GTK_RADIO_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),0,0)),
                        user_data->ptr_csu_struct->player_names[i]),0,i,1,1);
                else
                {
                    first_attach = true;
                    gtk_grid_attach(GTK_GRID(grid),gtk_radio_button_new_with_label(NULL,user_data->ptr_csu_struct->player_names[i]),0,0,1,1);
                }
            }
        }

        // Add the grid
        gtk_container_add(GTK_CONTAINER(viewport_dialog),grid);
        GtkWidget *dialog = getWidgetFromBuilder(user_data->ptr_builder,"delete_turn_dialog");

        gtk_widget_show_all(grid);
        switch (gtk_dialog_run(GTK_DIALOG(dialog)))
        {
        case GTK_RESPONSE_CANCEL:
            break;
        case GTK_RESPONSE_APPLY:
            // Search the player selected
            for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
            {
                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),0,i))))
                {
                    for (j=0 ; j<user_data->ptr_csu_struct->nb_player ; j++ )
                        if (g_utf8_collate(gtk_button_get_label(GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),0,i))),user_data->ptr_csu_struct->player_names[j]) == 0)
                            break;
                    break;
                }
            }
            // Delete the turn
            deleteTurn(user_data->ptr_csu_struct,j,turn);
            if (writeFileNewTurn(user_data->csu_filename,user_data->ptr_csu_struct) == false)
                saveFileError(user_data);
            addLastCsuStruct(user_data);
            updateMainWindow(user_data,!exceedMaxNumber(user_data->ptr_csu_struct));

            // Test if the game is over
            if (exceedMaxNumber(user_data->ptr_csu_struct) == true)
                gameOver(user_data);
            break;
        default:
            break;
        }
        gtk_widget_hide(dialog);
        gtk_widget_destroy(grid);
    }
}

G_MODULE_EXPORT void changeTurnSignal(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;

    GtkWidget *viewport = getWidgetFromBuilder(user_data->ptr_builder,"main_window_viewport");
    GtkWidget *viewport_dialog = getWidgetFromBuilder(user_data->ptr_builder,"edit_turn_dialog_viewport");
    GtkWidget *dialog = getWidgetFromBuilder(user_data->ptr_builder,"edit_turn_dialog");

    gint turn,i;

    // Set the grid
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid),5);
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
    gtk_widget_set_hexpand(grid,TRUE);

    // Get the turn
    for (turn = 0 ; widget != gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),6*(user_data->ptr_csu_struct->nb_player+1),2*(turn+1)+2) ; turn ++);

    for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
    {
        if (user_data->ptr_csu_struct->nb_turn[i] > turn)
        {
            GtkWidget *new_label = gtk_label_new(user_data->ptr_csu_struct->player_names[i]);
            gtk_grid_attach(GTK_GRID(grid),new_label,i,0,1,1);
            GtkAdjustment *adju = gtk_adjustment_new(0,-G_MAXDOUBLE,G_MAXDOUBLE,1,0,0);
            GtkWidget *new_points_button = gtk_spin_button_new(adju,1,user_data->ptr_csu_struct->config.decimal_place);
            gtk_entry_set_alignment (GTK_ENTRY(new_points_button),0.5);
            gtk_entry_set_width_chars(GTK_ENTRY(new_points_button),3);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(new_points_button),user_data->ptr_csu_struct->point[i][turn]);
            gtk_grid_attach(GTK_GRID(grid),new_points_button,i,1,1,1);
            gtk_widget_set_hexpand(new_points_button,TRUE);
            gtk_widget_set_halign(new_points_button,GTK_ALIGN_CENTER);
        }

    }

    gtk_container_add(GTK_CONTAINER(viewport_dialog),grid);
    gtk_widget_show_all(grid);

    switch (gtk_dialog_run(GTK_DIALOG(dialog)))
    {
    case GTK_RESPONSE_CANCEL:
        break;
    case GTK_RESPONSE_APPLY:
        // Edit the turn
        for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
        {
            if (user_data->ptr_csu_struct->nb_turn[i] > turn)
            {
                (user_data->ptr_csu_struct->total_points[i]) -= user_data->ptr_csu_struct->point[i][turn];
                user_data->ptr_csu_struct->point[i][turn]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(grid),i,1)));
                (user_data->ptr_csu_struct->total_points[i]) += user_data->ptr_csu_struct->point[i][turn];
            }
        }
        rankCalculation(user_data->ptr_csu_struct);
        addLastCsuStruct(user_data);
        if (writeFileNewTurn(user_data->csu_filename,user_data->ptr_csu_struct) == false)
            saveFileError(user_data);
        updateMainWindow(user_data,!exceedMaxNumber(user_data->ptr_csu_struct));

        // Test if the game is over
        if (exceedMaxNumber(user_data->ptr_csu_struct) == true)
            gameOver(user_data);
        break;
    default:
        break;
    }

    gtk_widget_hide(dialog);
    gtk_widget_destroy(grid);
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

    GtkWidget *viewport = getWidgetFromBuilder(user_data->ptr_builder,"main_window_viewport");
    GtkWidget *scrolled_window = getWidgetFromBuilder(user_data->ptr_builder,"main_window_scrolled_window");

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
            tmp_score = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),6*i+2,2*(max_nb_turn+1)+2)));

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
                gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),6*i+2,2*(max_nb_turn+1)+2)));
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
    GtkWidget *window_game_over = getWidgetFromBuilder(data->ptr_builder,"dialog_game_over");
    GtkWidget *fixed = getWidgetFromBuilder(data->ptr_builder,"dialog_game_over_fixed");

    GtkWidget *podium =gtk_image_new_from_file("Images/Podium.png");
    gtk_fixed_put(GTK_FIXED(fixed),podium,0,20);
    int nb=1;

    /* Put the different names */
    nb=1;
    int index = searchIndexFromPosition(data->ptr_csu_struct,1,&nb);
    GtkWidget *label_1 = GTK_WIDGET(createGtkLabelWithAttributes(data->ptr_csu_struct->player_names[index],15,TRUE,0,50,0,FALSE,0,0,0));
    gtk_fixed_put(GTK_FIXED(fixed),label_1,250-g_utf8_strlen(data->ptr_csu_struct->player_names[index],SIZE_MAX_NAME)*9/2,47);

    GtkWidget *label_2;
    if (data->ptr_csu_struct->nb_player >=2)
    {
        nb=1;
        index = searchIndexFromPosition(data->ptr_csu_struct,2,&nb);
        label_2 = GTK_WIDGET(createGtkLabelWithAttributes(data->ptr_csu_struct->player_names[index],15,TRUE,0,0,100,FALSE,0,0,0));
        gtk_fixed_put(GTK_FIXED(fixed),label_2,90-g_utf8_strlen(data->ptr_csu_struct->player_names[index],SIZE_MAX_NAME)*9/2,118);
    }

    GtkWidget *label_3;
    if (data->ptr_csu_struct->nb_player >=3)
    {
        nb=1;
        index = searchIndexFromPosition(data->ptr_csu_struct,3,&nb);
        label_3 = GTK_WIDGET(createGtkLabelWithAttributes(data->ptr_csu_struct->player_names[index],15,TRUE,100,0,0,FALSE,0,0,0));
        gtk_fixed_put(GTK_FIXED(fixed),label_3,410-g_utf8_strlen(data->ptr_csu_struct->player_names[index],SIZE_MAX_NAME)*9/2,158);
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
    GtkWidget *button_end_of_turn = getWidgetFromBuilder(data->ptr_builder,"button_end_of_turn");
    GtkWidget *button_calculator = getWidgetFromBuilder(data->ptr_builder,"main_window_label_calculator_validate");
    GtkWidget *combobox_calculator = getWidgetFromBuilder(data->ptr_builder,"main_window_label_calculator_select_person");
    GtkWidget *button_change_distributor = getWidgetFromBuilder(data->ptr_builder,"main_window_button_change_distributor");
    GtkWidget *main_toolbar = getWidgetFromBuilder(data->ptr_builder,"main_toolbar");
    GtkWidget *menu_save_as = getWidgetFromBuilder(data->ptr_builder,"menu_save_as");
    GtkWidget *menu_properties = getWidgetFromBuilder(data->ptr_builder,"menu_properties");
    GtkWidget *menu_delete_file = getWidgetFromBuilder(data->ptr_builder,"menu_delete_file");
    GtkWidget *menu_export = getWidgetFromBuilder(data->ptr_builder,"menu_export");
    GtkWidget *menu_podium = getWidgetFromBuilder(data->ptr_builder,"menu_display_podium");
    GtkWidget *menu_chart_total_points= getWidgetFromBuilder(data->ptr_builder,"menu_display_chart_total_points");
    GtkWidget *menu_chart_points= getWidgetFromBuilder(data->ptr_builder,"menu_display_chart_points");
    GtkWidget *menu_statistics= getWidgetFromBuilder(data->ptr_builder,"menu_display_statistics");


    // Set the recent csu file open
    GtkRecentFilter *recent_filter_csu = GTK_RECENT_FILTER(gtk_builder_get_object(data->ptr_builder,"recent_filter_csu"));
    GtkWidget *recent_chooser = gtk_recent_chooser_menu_new();
    gtk_recent_chooser_set_filter(GTK_RECENT_CHOOSER(recent_chooser),recent_filter_csu);
    gtk_recent_chooser_set_show_not_found(GTK_RECENT_CHOOSER(recent_chooser),FALSE);
    gtk_menu_tool_button_set_menu(GTK_MENU_TOOL_BUTTON(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),1)),recent_chooser);
    g_signal_connect(recent_chooser,"item-activated", G_CALLBACK(recentCsuFileOpen),data);


    // Set image menu
    #ifdef ENABLE_DEPRECIATE_FUNCTIONS
    GtkWidget *menu_preferences_game = getWidgetFromBuilder(data->ptr_builder,"menu_preference_game_config");
    GtkWidget *menu_preferences_toolbar = getWidgetFromBuilder(data->ptr_builder,"menu_preferences_toolbar_button");
    GtkWidget *menu_preferences_exportation = getWidgetFromBuilder(data->ptr_builder,"menu_preferences_exportation");

    // Set the image of the menu
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_podium),gtk_image_new_from_file("Images/Podium_icon.png"));
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_preferences_game),gtk_image_new_from_stock("gtk-preferences",GTK_ICON_SIZE_MENU));
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_preferences_toolbar),gtk_image_new_from_stock("gtk-preferences",GTK_ICON_SIZE_MENU));
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_preferences_exportation),gtk_image_new_from_stock("gtk-preferences",GTK_ICON_SIZE_MENU));
    #endif


    // If there is no csu file opened
    if (data->ptr_csu_struct == NULL)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),2)),FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),5)),FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),3)),FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),15)),FALSE);
        gtk_widget_set_sensitive(menu_properties,FALSE);
        gtk_widget_set_sensitive(menu_save_as,FALSE);
        gtk_widget_set_sensitive(menu_delete_file,FALSE);
        gtk_widget_set_sensitive(menu_export,FALSE);
        gtk_widget_set_sensitive(menu_podium,FALSE);
        gtk_widget_set_sensitive(menu_chart_total_points,FALSE);
        gtk_widget_set_sensitive(menu_chart_points,FALSE);
        gtk_widget_set_sensitive(menu_statistics,FALSE);
        gtk_widget_set_sensitive(button_end_of_turn,FALSE);
        gtk_widget_set_sensitive(button_calculator,FALSE);
        gtk_widget_set_sensitive(button_change_distributor,FALSE);
        gtk_widget_set_sensitive(combobox_calculator,FALSE);
    }
    else
    {
        if (exceedMaxNumber(data->ptr_csu_struct) == true)
        {
            gtk_widget_set_sensitive(button_calculator,FALSE);
            gtk_widget_set_sensitive(button_end_of_turn,FALSE);
            gtk_widget_set_sensitive(combobox_calculator,FALSE);
        }
        else
        {
            gtk_widget_set_sensitive(button_calculator,TRUE);
            gtk_widget_set_sensitive(button_end_of_turn,TRUE);
            gtk_widget_set_sensitive(combobox_calculator,TRUE);
        }

        if (data->ptr_csu_struct->config.use_distributor == 0)
            gtk_widget_set_sensitive(button_change_distributor,FALSE);
        else
            gtk_widget_set_sensitive(button_change_distributor,TRUE);

        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),2)),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),5)),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),3)),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(gtk_toolbar_get_nth_item(GTK_TOOLBAR(main_toolbar),15)),TRUE);
        gtk_widget_set_sensitive(menu_properties,TRUE);
        gtk_widget_set_sensitive(menu_save_as,TRUE);
        gtk_widget_set_sensitive(menu_delete_file,TRUE);
        gtk_widget_set_sensitive(menu_export,TRUE);
        gtk_widget_set_sensitive(menu_podium,TRUE);
        gtk_widget_set_sensitive(menu_chart_total_points,TRUE);
        gtk_widget_set_sensitive(menu_chart_points,TRUE);
        gtk_widget_set_sensitive(menu_statistics,TRUE);
    }


    // Set the toggle button of the display preferences
    difference_between_player diff;
    gchar home_path[SIZE_MAX_FILE_NAME]="";

    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    readFileDifferenceBetweenPlayer(home_path,&diff);

    GtkWidget *consecutive = getWidgetFromBuilder(data->ptr_builder,"menu_display_consecutive");
    GtkWidget *first = getWidgetFromBuilder(data->ptr_builder,"menu_display_first");
    GtkWidget *last = getWidgetFromBuilder(data->ptr_builder,"menu_display_last");

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(consecutive),diff.consecutive);
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(first),diff.first);
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(last),diff.last);



    // Set the toggle button of the points grid
    score_display score;
    readFileScoreDisplay(home_path,&score);

    GtkWidget *total_points = getWidgetFromBuilder(data->ptr_builder,"menu_display_totalpoints");
    GtkWidget *ranking = getWidgetFromBuilder(data->ptr_builder,"menu_display_ranking");
    GtkWidget *edit_suppr = getWidgetFromBuilder(data->ptr_builder,"menu_display_edit_suppr");

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(ranking),score.ranking);
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(total_points),score.total_points);
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(edit_suppr),score.edit_suppr);



    // Set the toggle button of main window side
    main_window_side pref;
    readFileMainWindowSide(home_path,&pref);

    GtkWidget *calculator = getWidgetFromBuilder(data->ptr_builder,"menu_display_calculator");
    GtkWidget *ranking_side = getWidgetFromBuilder(data->ptr_builder,"menu_display_ranking_side");
    GtkWidget *game_information = getWidgetFromBuilder(data->ptr_builder,"menu_display_game_information");

    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(calculator),pref.calculator);
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(ranking_side),pref.ranking);
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(game_information),pref.game_information);




    // The undo buttons
    GtkWidget *menu_undo = getWidgetFromBuilder(data->ptr_builder,"menu_undo");
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

    // The redo buttons
    GtkWidget *menu_redo = getWidgetFromBuilder(data->ptr_builder,"menu_redo");
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

    GtkWidget *main_toolbar = getWidgetFromBuilder(user_data->ptr_builder,"main_toolbar");

    GtkWidget *menu_cut = getWidgetFromBuilder(user_data->ptr_builder,"menu_cut");
    GtkWidget *menu_copy = getWidgetFromBuilder(user_data->ptr_builder,"menu_copy");
    GtkWidget *menu_paste = getWidgetFromBuilder(user_data->ptr_builder,"menu_paste");
    GtkWidget *menu_delete = getWidgetFromBuilder(user_data->ptr_builder,"menu_delete");

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

    GtkWidget *main_window = getWidgetFromBuilder(data->ptr_builder,"main_window");

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


    size.height = configure_event.height;
    size.width = configure_event.width;
    #if GTK_MINOR_VERSION >= 12
    GtkWidget *main_window = getWidgetFromBuilder(user_data->ptr_builder,"main_window");
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

    GtkWidget *dialog = getWidgetFromBuilder(user_data->ptr_builder,"change_distributor_dialog");
    GtkWidget *viewport = getWidgetFromBuilder(user_data->ptr_builder,"change_distributor_dialog_viewport");


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


    /* Set the radio button */
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


/*!
 * \fn G_MODULE_EXPORT void updateCalculatorMainWindow(GtkWidget *widget, gpointer data)
 *  Update the result of the calculator of the main window
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void updateCalculatorMainWindow(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    double res;
    gchar string[SIZE_MAX_FILE_NAME];
    struct lconv *lc;
    char *comma;

    GtkWidget *text = getWidgetFromBuilder(user_data->ptr_builder,"main_window_label_calculator_result");
    GtkWidget *entry = getWidgetFromBuilder(user_data->ptr_builder,"main_window_label_calculator_entry");
    GtkWidget *calculator_button = getWidgetFromBuilder(user_data->ptr_builder,"main_window_label_calculator_validate");
    //GtkWidget *combobox_calculator = getWidgetFromBuilder(user_data->ptr_builder,"main_window_label_calculator_select_person");

    // Get the string and convert the . to , if needed
    strncpy(string,gtk_entry_get_text(GTK_ENTRY(entry)),SIZE_MAX_FILE_NAME);
    lc=localeconv();
    if(*(lc->decimal_point) == ',')
    {
        while ((comma = strchr(string, '.')) != NULL)
            *comma=',';
    }

    res = calculateFromString(string);

    // Print the result
    if (fabs(res) < 1000000 && fabs(res) > 0.001)
        gtk_label_set_text(GTK_LABEL(text),g_strdup_printf(_("Result : %.3lf"),res));
    else
        gtk_label_set_text(GTK_LABEL(text),g_strdup_printf(_("Result : %.3e"),res));

    // Update the button validate
    if (user_data->ptr_csu_struct != NULL)
        gtk_widget_set_sensitive(calculator_button,!isnan(res));
}


/*!
 * \fn G_MODULE_EXPORT void validateCalculatorPoints(GtkWidget *widget, gpointer data)
 *  Change the points of the person selected to the result of the calculator.
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void validateCalculatorPoints(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    double res;
    gchar string[SIZE_MAX_FILE_NAME];
    struct lconv *lc;
    char *comma;
    int pos_player;
    gint max_nb_turn = maxNbTurn(user_data->ptr_csu_struct);

    GtkWidget *combobox_calculator = getWidgetFromBuilder(user_data->ptr_builder,"main_window_label_calculator_select_person");
    GtkWidget *entry = getWidgetFromBuilder(user_data->ptr_builder,"main_window_label_calculator_entry");
    GtkWidget *viewport = getWidgetFromBuilder(user_data->ptr_builder,"main_window_viewport");

    // Get the string and convert the . to , if needed
    strncpy(string,gtk_entry_get_text(GTK_ENTRY(entry)),SIZE_MAX_FILE_NAME);
    lc=localeconv();
    if(*(lc->decimal_point) == ',')
    {
        while ((comma = strchr(string, '.')) != NULL)
            *comma=',';
    }

    res = calculateFromString(string);

    pos_player = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox_calculator));

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtk_grid_get_child_at(GTK_GRID(gtk_bin_get_child(GTK_BIN(viewport))),6*pos_player+2,2*(max_nb_turn+1)+2)),res);
    if (user_data->ptr_csu_struct->config.turn_based == 0)
        endOfTurn(NULL,user_data);
}


/*!
 * \fn void fillCalculatorNames(globalData *data)
 *  Fill the combobox of the calculator with the names of the players
 * \param[in] data the globalData
 */
void fillCalculatorNames(globalData *data)
{
    GtkWidget *combobox_calculator = getWidgetFromBuilder(data->ptr_builder,"main_window_label_calculator_select_person");

    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(combobox_calculator));

    int i;
    for (i=0 ; i<data->ptr_csu_struct->nb_player ; i++)
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(combobox_calculator),"",data->ptr_csu_struct->player_names[i]);

    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_calculator),0);
}


/*!
 * \fn void fillCalculatorNames(globalData *data)
 *  Update the display of the main window left side
 * \param[in] data the globalData
 */
void updateMainWindowSide(globalData *data)
{
    gchar home_path[SIZE_MAX_FILE_NAME]="";
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    main_window_side pref;
    readFileMainWindowSide(home_path,&pref);

    GtkWidget *grid = getWidgetFromBuilder(data->ptr_builder,"main_window_grid_game_config");

    if (pref.ranking)
    {
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,0)));
        gtk_widget_show(GTK_WIDGET(gtk_bin_get_child(GTK_BIN(gtk_grid_get_child_at(GTK_GRID(grid),0,1)))));
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,2)));
    } else
    {
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,0)));
        gtk_widget_hide(GTK_WIDGET(gtk_bin_get_child(GTK_BIN(gtk_grid_get_child_at(GTK_GRID(grid),0,1)))));
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,2)));
    }

    if (pref.calculator)
    {
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,3)));
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,4)));
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,5)));
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,6)));
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,7)));
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,8)));
    } else
    {
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,3)));
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,4)));
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,5)));
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,6)));
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,7)));
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,8)));
    }

    if (pref.game_information)
        {
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,9)));
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,10)));
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,11)));
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,12)));
        gtk_widget_show(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,13)));
    } else
    {
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,9)));
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,10)));
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,11)));
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,12)));
        gtk_widget_hide(GTK_WIDGET(gtk_grid_get_child_at(GTK_GRID(grid),0,13)));
    }
}
