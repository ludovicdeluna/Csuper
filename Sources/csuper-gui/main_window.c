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
 * \fn void updateCsuInfo(globalData *data)
 *  Update the csu informations in the right panel.
 * \param[in] data the globalData
 */
void updateCsuInfo(globalData *data)
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_date_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%02.0f/%02.0f/%4.0f"),data->ptr_csu_struct->day,data->ptr_csu_struct->month,data->ptr_csu_struct->year));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_version_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%1.1f"),data->ptr_csu_struct->version));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_size_max_name_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%.0f"),data->ptr_csu_struct->size_max_name));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_number_player_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%.0f"),data->ptr_csu_struct->nb_player));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_turn_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%d"),maxNbTurn(data->ptr_csu_struct)-1));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_config_name_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%s"),data->ptr_csu_struct->config.name));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_use_max_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%d"),data->ptr_csu_struct->config.max));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_initial_score_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%.3f"),data->ptr_csu_struct->config.begin_score));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_digit_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%d"),data->ptr_csu_struct->config.decimal_place));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_first_way_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%d"),data->ptr_csu_struct->config.first_way));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_turn_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%d"),data->ptr_csu_struct->config.turn_by_turn));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_distributor_turn_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%d"),data->ptr_csu_struct->config.use_distributor));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_max_change"));
    #ifdef __unix__
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%.3f"),data->ptr_csu_struct->config.nb_max));
    #elif _WIN32
    if (data->ptr_csu_struct->config.nb_max == INFINITY)
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("inf")));
    else
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%.3f"),data->ptr_csu_struct->config.nb_max));
    #endif

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_distributor_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[(int)data->ptr_csu_struct->distributor]));
}

/*!
 * \fn void updateCsuInfoSameFile(globalData *data)
 *  Update the distributor informations in the right panel.
 * \param[in] data the globalData
 */
void updateCsuInfoSameFile(globalData *data)
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_distributor_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[(int)data->ptr_csu_struct->distributor]));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_turn_change"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%d"),maxNbTurn(data->ptr_csu_struct)-1));
}
