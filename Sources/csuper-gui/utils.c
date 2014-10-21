/*!
 * \file    utils.c
 * \brief   The new file assistant function
 * \author  Remi BERTHO
 * \date    26/06/14
 * \version 4.0.0
 */

 /*
 * utils.c
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

 #include "utils.h"

 /*!
 * \fn void setGtkLabelAttributes(GtkLabel *label, int text_size, gboolean use_foreground,guint16 foreground_red, guint16 foreground_green, guint16 foreground_blue, gboolean use_background,guint16 background_red, guint16 background_green, guint16 background_blue)
 *  Set the foreground color, the background color and the size of a gtklabel
 * \param[in] label the label
 * \param[in] text_size the size of the text, -1 if not used
 * \param[in] use_foreground indicate if it use the foreground color, if FALSE use the default color
 * \param[in] foreground_red the red value of the foreground (ranging from 0 to 100)
 * \param[in] foreground_green the green value of the foreground (ranging from 0 to 100)
 * \param[in] foreground_blue the blue value of the foreground (ranging from 0 to 100)
 * \param[in] use_background indicate if it use the background color, if FALSE use the default color
 * \param[in] background_red the red value of the background (ranging from 0 to 100)
 * \param[in] background_green the green value of the background (ranging from 0 to 100)
 * \param[in] background_blue the blue value of the background (ranging from 0 to 100)
 */
void setGtkLabelAttributes(GtkLabel *label, int text_size, gboolean use_foreground,guint16 foreground_red, guint16 foreground_green, guint16 foreground_blue, gboolean use_background,guint16 background_red, guint16 background_green, guint16 background_blue)
{
    PangoAttrList *attribut_list = pango_attr_list_new();
    PangoAttribute *size = pango_attr_size_new(text_size*PANGO_SCALE);
    PangoAttribute *foreground = pango_attr_foreground_new(foreground_red*655.35,foreground_green*655.35,foreground_blue*655.35);
    PangoAttribute *background = pango_attr_background_new(background_red*655.35,background_green*655.35,background_blue*655.35);

    if (text_size > 0)
    {
        pango_attr_list_ref(attribut_list);
        pango_attr_list_insert(attribut_list,size);
    }

    if (use_foreground)
    {
        pango_attr_list_ref(attribut_list);
        pango_attr_list_insert(attribut_list,foreground);
    }


    if (use_background)
    {
        pango_attr_list_ref(attribut_list);
        pango_attr_list_insert(attribut_list,background);
    }

    gtk_label_set_attributes(label,attribut_list);

    if (text_size > 0)
        pango_attr_list_unref(attribut_list);
    if (use_background)
        pango_attr_list_unref(attribut_list);
    if (use_foreground)
        pango_attr_list_unref(attribut_list);
    pango_attr_list_unref(attribut_list);
}

 /*!
 * \fn GtkLabel *createGtkLabelWithAttributes(gchar *text, int text_size, gboolean use_foreground,guint16 foreground_red, guint16 foreground_green, guint16 foreground_blue, gboolean use_background,guint16 background_red, guint16 background_green, guint16 background_blue)
 *  Set the foreground color, the background color and the size of a gtklabel
 * \param[in] text the text for the new gtklabel
 * \param[in] text_size the size of the text, -1 if not used
 * \param[in] use_foreground indicate if it use the foreground color, if FALSE use the default color
 * \param[in] foreground_red the red value of the foreground (ranging from 0 to 100)
 * \param[in] foreground_green the green value of the foreground (ranging from 0 to 100)
 * \param[in] foreground_blue the blue value of the foreground (ranging from 0 to 100)
 * \param[in] use_background indicate if it use the background color, if FALSE use the default color
 * \param[in] background_red the red value of the background (ranging from 0 to 100)
 * \param[in] background_green the green value of the background (ranging from 0 to 100)
 * \param[in] background_blue the blue value of the background (ranging from 0 to 100)
 * \return a new allocate gtklabel with attributes
 */
GtkLabel *createGtkLabelWithAttributes(gchar *text, int text_size, gboolean use_foreground,guint16 foreground_red, guint16 foreground_green, guint16 foreground_blue, gboolean use_background,guint16 background_red, guint16 background_green, guint16 background_blue)
{
    GtkWidget *label = gtk_label_new(text);
    setGtkLabelAttributes(GTK_LABEL(label),text_size,use_foreground,foreground_red,foreground_green,foreground_blue,use_background,background_red,background_green,background_blue);
    return GTK_LABEL(label);
}
