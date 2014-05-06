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
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_date"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Created the : %02.0f/%02.0f/%4.0f"),data->ptr_csu_struct->day,data->ptr_csu_struct->month,data->ptr_csu_struct->year));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_version"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("File's version : %1.1f"),data->ptr_csu_struct->version));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_size_max_name"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Size max of the names : %.0f"),data->ptr_csu_struct->size_max_name));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_number_player"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of players : %.0f"),data->ptr_csu_struct->nb_player));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Numbers maximum of turns : %d"),maxNbTurn(data->ptr_csu_struct)-1));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_config_name"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Name of the game configuration : %s"),data->ptr_csu_struct->config.name));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_use_max"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Use a maximum score : %d"),data->ptr_csu_struct->config.max));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_initial_score"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Initial score : %.3f"),data->ptr_csu_struct->config.begin_score));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_digit"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of decimal place : %d"),data->ptr_csu_struct->config.decimal_place));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_first_way"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("First way : %d"),data->ptr_csu_struct->config.first_way));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Game in turn by turn : %d"),data->ptr_csu_struct->config.turn_by_turn));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_distributor_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Use a distributor : %d"),data->ptr_csu_struct->config.use_distributor));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_nb_max"));
    #ifdef __unix__
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of points maximum/minimum : %.3f"),data->ptr_csu_struct->config.nb_max));
    #elif _WIN32
    if (data->ptr_csu_struct->config.nb_max == INFINITY)
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of points maximum/minimum : inf")));
    else
        gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Number of points maximum/minimum : %.3f"),data->ptr_csu_struct->config.nb_max));
    #endif

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"label_distributor"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("Distributor : %s"),data->ptr_csu_struct->player_names[(int)data->ptr_csu_struct->distributor]));
}

/*!
 * \fn void updateCsuInfoSameFile(globalData *data)
 *  Update the distributor informations in the right panel.
 * \param[in] data the globalData
 */
void updateCsuInfoSameFile(globalData *data)
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"Distributor : label_distributor"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%s"),data->ptr_csu_struct->player_names[(int)data->ptr_csu_struct->distributor]));

    label = GTK_LABEL(gtk_builder_get_object(data->ptr_builder,"Numbers maximum of turns : label_nb_turn"));
    gtk_label_set_text(GTK_LABEL(label),g_strdup_printf(_("%d"),maxNbTurn(data->ptr_csu_struct)-1));
}
