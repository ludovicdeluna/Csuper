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

 static void increaseFmt(char* fmt);

/*!
 * \fn G_MODULE_EXPORT void displayTotalPointsChart(GtkWidget *widget, gpointer data)
 *  Display the chart window
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void displayTotalPointsChart(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    GtkWidget *dialog = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart");
    GtkWidget *main_grid = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_main_grid");
    int i,j;

    // Grid
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


    // Slope
    user_data->slope_chart = slope_chart_create(_("Total points chart"), _("Turn"), _("Total points"));
    int max_nb_turn = maxNbTurn(user_data->ptr_csu_struct);
    int nb_player = user_data->ptr_csu_struct->nb_player;
    char fmt[4] = "b+-";

    user_data->slope_turn = myAlloc(max_nb_turn*sizeof(double));
    user_data->slope_points = myAlloc(sizeof(double*)*nb_player);
    user_data->slope_items = myAlloc(sizeof(slope_item_t*)*nb_player);

    for (i=0 ; i<max_nb_turn ; i++)
        user_data->slope_turn[i]=i;

    for (i=0 ; i<nb_player ; i++)
    {
        user_data->slope_points[i] = myAlloc(user_data->ptr_csu_struct->nb_turn[i]*sizeof(double));
        for (j=0 ; j<user_data->ptr_csu_struct->nb_turn[i] ; j++)
            user_data->slope_points[i][j]= pointsAtTurn(user_data->ptr_csu_struct,i,j);
        user_data->slope_items[i] = slope_chart_add_plot(user_data->slope_chart,
                                                         user_data->slope_turn,
                                                         user_data->slope_points[i],
                                                         user_data->ptr_csu_struct->nb_turn[i],
                                                         user_data->ptr_csu_struct->player_names[i],
                                                         fmt);
        increaseFmt(fmt);
    }

    GtkWidget *slope_view = slope_view_new_for_figure(user_data->slope_chart);
    gtk_widget_set_vexpand(slope_view,TRUE);
    slope_view_toggle_mouse_zoom(slope_view,TRUE);


    gtk_grid_attach(GTK_GRID(main_grid),slope_view,0,0,1,1);



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


    gtk_widget_show_all(main_grid);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_hide(dialog);

    free(user_data->slope_turn);
    for (i=0 ; i<nb_player ; i++)
        free(user_data->slope_points[i]);
    free(user_data->slope_points);
    free(user_data->slope_items);
    slope_chart_destroy(user_data->slope_chart);

    gtk_widget_destroy(slope_view);
    gtk_widget_destroy(player_display_grid);
}


/*!
 * \fn G_MODULE_EXPORT void displayPointsChart(GtkWidget *widget, gpointer data)
 *  Display the chart window
 * \param[in] widget the widget which send the signal
 * \param[in] data the globalData
 */
G_MODULE_EXPORT void displayPointsChart(GtkWidget *widget, gpointer data)
{
    globalData *user_data = (globalData*) data;
    GtkWidget *dialog = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart");
    GtkWidget *main_grid = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_main_grid");
    int i,j;

    // Grid
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


    // Slope
    user_data->slope_chart = slope_chart_create(_("Points chart"), _("Turn"), _("Points"));
    int max_nb_turn = maxNbTurn(user_data->ptr_csu_struct);
    int nb_player = user_data->ptr_csu_struct->nb_player;
    char fmt[4] = "b+-";

    user_data->slope_turn = myAlloc(max_nb_turn*sizeof(double));
    user_data->slope_points = myAlloc(sizeof(double*)*nb_player);
    user_data->slope_items = myAlloc(sizeof(slope_item_t*)*nb_player);

    for (i=0 ; i<max_nb_turn ; i++)
        user_data->slope_turn[i]=i;

    for (i=0 ; i<nb_player ; i++)
    {
        user_data->slope_points[i] = myAlloc(user_data->ptr_csu_struct->nb_turn[i]*sizeof(double));
        for (j=0 ; j<user_data->ptr_csu_struct->nb_turn[i] ; j++)
            user_data->slope_points[i][j]= user_data->ptr_csu_struct->point[i][j];
        user_data->slope_items[i] = slope_chart_add_plot(user_data->slope_chart,
                                                         user_data->slope_turn,
                                                         user_data->slope_points[i],
                                                         user_data->ptr_csu_struct->nb_turn[i],
                                                         user_data->ptr_csu_struct->player_names[i],
                                                         fmt);
        increaseFmt(fmt);
    }

    GtkWidget *slope_view = slope_view_new_for_figure(user_data->slope_chart);
    gtk_widget_set_vexpand(slope_view,TRUE);
    slope_view_toggle_mouse_zoom(slope_view,TRUE);


    gtk_grid_attach(GTK_GRID(main_grid),slope_view,0,0,1,1);



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


    gtk_widget_show_all(main_grid);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_hide(dialog);

    free(user_data->slope_turn);
    for (i=0 ; i<nb_player ; i++)
        free(user_data->slope_points[i]);
    free(user_data->slope_points);
    free(user_data->slope_items);
    slope_chart_destroy(user_data->slope_chart);

    gtk_widget_destroy(slope_view);
    gtk_widget_destroy(player_display_grid);
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
    int nb_player = user_data->ptr_csu_struct->nb_player;
    int i;

    GtkWidget *main_grid = getWidgetFromBuilder(user_data->ptr_builder,"dialog_chart_main_grid");

    for (i=0 ; i<nb_player ; i++)
    {
        GtkWidget *tmp_button = gtk_grid_get_child_at(GTK_GRID(gtk_grid_get_child_at(GTK_GRID(main_grid),0,1)),i%5,i/5);
        slope_item_toggle_visible(user_data->slope_items[i],gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tmp_button)));
    }

    gtk_widget_queue_draw(gtk_grid_get_child_at(GTK_GRID(main_grid),0,0));
}


/*!
 * \fn  void increaseFmt(char* fmt)
 *  Increase fmt color
 * \param[in] fmt
 */
 void increaseFmt(char* fmt)
 {
    switch(fmt[0])
    {
    case 'b':
        fmt[0] = 'r';
        break;
    case 'r':
        fmt[0] = 'o';
        break;
    case 'o':
        fmt[0] = 'l';
        break;
    case 'l':
        fmt[0] = 'm';
        break;
    case 'm':
        fmt[0] = 'p';
        break;
    case 'p':
        fmt[0] = 'y';
        break;
    case 'y':
        fmt[0] = 'e';
        break;
    case 'e':
        fmt[0] = 'g';
        break;
    case 'g':
        fmt[0] = 'a';
        break;
    case 'a':
        fmt[0] = 't';
        break;
    case 't':
        fmt[0] = 'b';
        break;
    }
 }

/*!
 * \fn bool exportToChart(csuStruct *ptr_csu_struct, char *filename, ChartExportationType type)
 *  Export to a chart
 * \param[in] ptr_csu_struct tge csi struct
 * \param[in] filename the filename
 * \param[in] type the type of exportation
 * \return true is everything is fine, false otherwise
 */
bool exportToChart(csuStruct *ptr_csu_struct, char *filename, ChartExportationType type)
{
    int i,j;
    double** slope_points;
    double* slope_turn;
    slope_figure_t* slope_chart;

    // Preferences
    gchar home_path[SIZE_MAX_FILE_NAME]="";
    #ifndef PORTABLE
    readHomePathSlash(home_path);
    #endif // PORTABLE
    chart_exportation chart_pref;
    export_pdf_preferences pdf_pref;
    readFileChartExportation(home_path,&chart_pref);
    readFilePdfPreferences(home_path,&pdf_pref);


    // Title
    char simple_filename[SIZE_MAX_FILE_NAME];
    getSimpleFilenameFromFullFilename(filename,simple_filename);
    removeFileExtension(simple_filename);
    char title[SIZE_MAX_FILE_NAME];
    if (chart_pref.total_points)
        sprintf(title,_("Total points on %s"),simple_filename);
    else
        sprintf(title,_("Points on %s"),simple_filename);


    // Slope
    slope_chart = slope_chart_create(title, _("Turn"), _("Points"));
    int max_nb_turn = maxNbTurn(ptr_csu_struct);
    int nb_player = ptr_csu_struct->nb_player;
    char fmt[4] = "b+-";

    slope_turn = myAlloc(max_nb_turn*sizeof(double));
    slope_points = myAlloc(sizeof(double*)*nb_player);

    for (i=0 ; i<max_nb_turn ; i++)
        slope_turn[i]=i;

    for (i=0 ; i<nb_player ; i++)
    {
        slope_points[i] = myAlloc(ptr_csu_struct->nb_turn[i]*sizeof(double));
        for (j=0 ; j<ptr_csu_struct->nb_turn[i] ; j++)
        {
            if (chart_pref.total_points)
                slope_points[i][j]= pointsAtTurn(ptr_csu_struct,i,j);
            else
                slope_points[i][j]= ptr_csu_struct->point[i][j];
        }
        slope_chart_add_plot(slope_chart,
                             slope_turn,
                             slope_points[i],
                             ptr_csu_struct->nb_turn[i],
                             ptr_csu_struct->player_names[i],
                             fmt);
        increaseFmt(fmt);
    }

    int res = SLOPE_SUCCESS;
    int width;
    int height;
    switch (type)
    {
    case svg:
        res = slope_figure_write_to_svg(slope_chart,filename,chart_pref.width,chart_pref.height);
        break;
    case png:
        res = slope_figure_write_to_png(slope_chart,filename,chart_pref.width,chart_pref.height);
        break;
    case pdf:
        if (pdf_pref.pdf_size_for_chart)
        {
            switch (pdf_pref.size)
            {
            case HPDF_PAGE_SIZE_A3:
                width = 842;
                height = 1190;
                break;
            case HPDF_PAGE_SIZE_A4:
                width = 595;
                height = 842;
                break;
            case HPDF_PAGE_SIZE_A5:
                width = 420;
                height = 595;
                break;
            default:
                break;
            }
            if (pdf_pref.direction == HPDF_PAGE_LANDSCAPE)
            {
                int tmp = width;
                width = height;
                height = tmp;
            }
        }
        else
        {
            width = chart_pref.width;
            height = chart_pref.height;
        }
        res = slope_figure_write_to_pdf(slope_chart,filename,width,height);
        break;
    }


    free(slope_turn);
    for (i=0 ; i<nb_player ; i++)
        free(slope_points[i]);
    free(slope_points);
    slope_chart_destroy(slope_chart);

    if (res == SLOPE_SUCCESS)
        return true;
    else
        return false;
}


/*!
 * \fn bool exportToSvg(csuStruct *ptr_csu_struct, char *filename)
 *  Export to a SVG chart
 * \param[in] ptr_csu_struct tge csi struct
 * \param[in] filename the filename
 * \return true is everything is fine, false otherwise
 */
bool exportToSvg(csuStruct *ptr_csu_struct, char *filename)
{
    return exportToChart(ptr_csu_struct,filename,svg);
}

/*!
 * \fn bool exportToPng(csuStruct *ptr_csu_struct, char *filename)
 *  Export to a PNG chart
 * \param[in] ptr_csu_struct tge csi struct
 * \param[in] filename the filename
 * \return true is everything is fine, false otherwise
 */
bool exportToPng(csuStruct *ptr_csu_struct, char *filename)
{
    return exportToChart(ptr_csu_struct,filename,png);
}


/*!
 * \fn bool exportToPdfChart(csuStruct *ptr_csu_struct, char *filename)
 *  Export to a PDF chart
 * \param[in] ptr_csu_struct tge csi struct
 * \param[in] filename the filename
 * \return true is everything is fine, false otherwise
 */
bool exportToPdfChart(csuStruct *ptr_csu_struct, char *filename)
{
    return exportToChart(ptr_csu_struct,filename,pdf);
}
