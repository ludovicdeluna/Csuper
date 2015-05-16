/*!
 * \file    chart.c
 * \brief   Chart
 * \author  Remi BERTHO
 * \date    08/05/15
 * \version 4.2.0
 */

 /*
 * chart.c
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

 #include "chart.h"

/*!
 * \fn G_MODULE_EXPORT void displayChart(GtkWidget *widget, gpointer data)
 *  Display the chart window
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void displayChart(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    GtkWidget *dialog = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart");
    GtkWidget *main_grid = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_main_grid");
    int i;


    GtkWidget *player_display_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(player_display_grid),5);
    gtk_grid_set_row_spacing(GTK_GRID(player_display_grid),5);
    #if GTK_MINOR_VERSION >= 12
    gtk_widget_set_margin_end(player_display_grid,10);
    gtk_widget_set_margin_start(player_display_grid,10);
    #else
    gtk_widget_set_margin_right(player_display_grid,10);
    gtk_widget_set_margin_left(player_display_grid,10);
    #endif // GTK_MINOR_VERSION
    gtk_widget_set_margin_top(player_display_grid,10);
    gtk_widget_set_margin_bottom(player_display_grid,10);

    for (i=0 ; i<user_data->ptr_csu_struct->nb_player ; i++)
    {
        GtkWidget *tmp_button = gtk_check_button_new_with_label(user_data->ptr_csu_struct->player_names[i]);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tmp_button),TRUE);
        gtk_widget_set_hexpand(tmp_button,TRUE);
        gtk_widget_set_halign(tmp_button,GTK_ALIGN_CENTER);
        g_signal_connect (tmp_button,"toggled", G_CALLBACK(changeChartPlayersDisplay),data);
        gtk_grid_attach(GTK_GRID(player_display_grid),tmp_button,i%5,i/5,1,1);
    }

    gtk_grid_attach(GTK_GRID(main_grid),player_display_grid,0,1,1,1);
    gtk_widget_show_all(player_display_grid);


    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_hide(dialog);
    gtk_widget_destroy(player_display_grid);
}

/*!
 * \fn G_MODULE_EXPORT void drawChart(GtkWidget *widget, cairo_t *cr, gpointer *data)
 *  Draw the cahrt in the GtkDrawing
 * \param[in] widget the widget which send the signal
 * \param[in] cr the cairo_t surface
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void drawChart(GtkWidget *widget, cairo_t *cr, gpointer *data)
{
    slope_rect_t rect;
    globalData *user_data = (globalData*) data;
    slope_scene_t *chart = slope_chart_create(_("Chart"), _("Turn"), _("Points"));
    int i,j;
    int max_nb_turn = maxNbTurn(user_data->ptr_csu_struct);
    int nb_player = user_data->ptr_csu_struct->nb_player;
    double *turn = myAlloc(max_nb_turn*sizeof(double));
    double **tmp_points = myAlloc(sizeof(double)*nb_player);
    double x_scroll, y_scroll,x_zoom,y_zoom,chart_width,chart_height;

    GtkWidget *chart_drawing = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_drawingarea");
    GtkWidget *chart_scale_x = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_scale_x");
    GtkWidget *chart_scale_y = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_scale_y");
    GtkWidget *chart_scrollbar_x = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_scrollbar_x");
    GtkWidget *chart_scrollbar_y = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_scrollbar_y");
    GtkWidget *main_grid = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_main_grid");

    x_scroll = gtk_range_get_value(GTK_RANGE(chart_scrollbar_x));
    y_scroll = gtk_range_get_value(GTK_RANGE(chart_scrollbar_y));
    x_zoom = gtk_range_get_value(GTK_RANGE(chart_scale_x));
    y_zoom = gtk_range_get_value(GTK_RANGE(chart_scale_y));
    chart_width = (double) gtk_widget_get_allocated_width(chart_drawing);
    chart_height = (double) gtk_widget_get_allocated_height(chart_drawing);

    rect.x = -(x_scroll-1)*chart_width;
    rect.y = -(y_scroll-1)*chart_height;
    rect.width = chart_width * x_zoom;
    rect.height = chart_height * y_zoom;

    for (i=0 ; i<max_nb_turn ; i++)
        turn[i]=i;

    for (i=0 ; i<nb_player ; i++)
    {
        tmp_points[i] = myAlloc(user_data->ptr_csu_struct->nb_turn[i]*sizeof(double));
        GtkWidget *tmp_button = gtk_grid_get_child_at(GTK_GRID(gtk_grid_get_child_at(GTK_GRID(main_grid),0,1)),i%5,i/5);
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tmp_button)))
        {
            for (j=0 ; j<user_data->ptr_csu_struct->nb_turn[i] ; j++)
                tmp_points[i][j]= pointsAtTurn(user_data->ptr_csu_struct,i,j);
            slope_chart_add_plot(chart, turn, tmp_points[i], user_data->ptr_csu_struct->nb_turn[i], user_data->ptr_csu_struct->player_names[i], "r-");
        }
    }

    slope_scene_draw(chart, cr, &rect);

    free(turn);
    for (i=0 ; i<nb_player ; i++)
        free(tmp_points[i]);
    free(tmp_points);
}


/*!
 * \fn G_MODULE_EXPORT void changeChartZoom(GtkWidget *widget, gpointer data)
 *  Call the change chart scrollbar
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void changeChartZoom(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    changeChartScrollbar(NULL,user_data);
}


/*!
 * \fn G_MODULE_EXPORT void changeChartScrollbar(GtkWidget *widget, gpointer data)
 *  Change the zoom and scrollbar
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void changeChartScrollbar(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    GtkWidget *chart_drawing = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_drawingarea");
    GtkWidget *chart_scale_x = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_scale_x");
    GtkWidget *chart_scale_y = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_scale_y");
    GtkWidget *chart_scrollbar_x = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_scrollbar_x");
    GtkWidget *chart_scrollbar_y = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_scrollbar_y");

    double zoom_x = gtk_range_get_value(GTK_RANGE(chart_scale_x));
    double zoom_y = gtk_range_get_value(GTK_RANGE(chart_scale_y));

    if (zoom_x == 1)
        gtk_widget_hide(chart_scrollbar_x);
    else
        gtk_widget_show(chart_scrollbar_x);

    gtk_range_set_range(GTK_RANGE(chart_scrollbar_x),1,zoom_x+1);

    if (zoom_y == 1)
        gtk_widget_hide(chart_scrollbar_y);
    else
        gtk_widget_show(chart_scrollbar_y);

    gtk_range_set_range(GTK_RANGE(chart_scrollbar_y),1,zoom_y+1);


    gtk_widget_queue_draw(chart_drawing);
}

/*!
 * \fn G_MODULE_EXPORT void changeChartPlayersDisplay(GtkWidget *widget, gpointer data)
 *  Change the players displayed
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void changeChartPlayersDisplay(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    GtkWidget *chart_drawing = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_drawingarea");
    gtk_widget_queue_draw(chart_drawing);
}
