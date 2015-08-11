/*!
 * \file    exportation_preferences.h
 * \author  Remi BERTHO
 * \date    10/08/15
 * \version 4.3.0
 */

/*
 * exportation_preferences.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-gtk.
 *
 * Csuper-gtk is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-gtk is distributed in the hope that it will be useful,
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

#ifndef EXPORTATION_PREFERENCES_H_INCLUDED
#define EXPORTATION_PREFERENCES_H_INCLUDED

#include <gtkmm.h>
#include "../libcsuper/libcsuper.h"

#include "csu_widget.h"

/*! \class ExportationPreferences
*   \brief This class represent the exportation preferences scrolled window
*/
class ExportationPreferences : public CsuWidget, public Gtk::ScrolledWindow
{
protected:
    Gtk::Grid* main_grid_;                  /*!< The main grid */
    Gtk::Viewport* viewport_;               /*!< The viewport */

    Gtk::Label* pdf_label_;                     /*!< The pdf label */
    Gtk::Label* pdf_utf8_label_;                /*!< The pdf UTF-8 label */
    Gtk::Switch* pdf_utf8_switch_;              /*!< The pdf UTF-8 switch */
    Gtk::Label* pdf_fontname_label_;            /*!< The pdf font name label */
    Gtk::Entry* pdf_font_name_entry_;           /*!< The pdf font name entry */
    Gtk::Label* pdf_embedded_font_label_;       /*!< The pdf embedded font label */
    Gtk::Switch* pdf_embedded_font_switch_;     /*!< The pdf embedded font */
    Gtk::Label* pdf_direction_label_;           /*!< The pdf direction label */
    Gtk::ComboBoxText* pdf_direction_combobox_; /*!< The pdf direction combobox */
    Gtk::Label* pdf_size_label_;                /*!< The pdf size label */
    Gtk::ComboBoxText* pdf_size_combobox_;      /*!< The pdf size combobox */
    Gtk::Label* pdf_margin_label_;              /*!< The pdf margin label */
    Gtk::SpinButton* pdf_margin_spinbutton_;    /*!< The pdf margin spinbutton */
    Glib::RefPtr<Gtk::Adjustment> pdf_margin_adjustement_;    /*!< The pdf margin adjustement */
    Gtk::Label* pdf_font_size_label_;           /*!< The pdf font size label */
    Gtk::SpinButton* pdf_font_size_spinbutton_; /*!< The pdf font size spinbutton */
    Glib::RefPtr<Gtk::Adjustment>pdf_font_size_adjustement_; /*!< The pdf font size adjustement */
    Gtk::Label* pdf_total_points_label_;        /*!< The pdf total points label */
    Gtk::Switch* pdf_total_points_switch_;      /*!< The pdf total points switch */
    Gtk::Label* pdf_ranking_label_;             /*!< The pdf ranking label */
    Gtk::Switch* pdf_ranking_switch_;           /*!< The pdf ranking switch */
    Gtk::Label* pdf_size_chart_label_;          /*!< The pdf size_chart label */
    Gtk::Switch* pdf_size_chart_switch_;        /*!< The pdf size_chart switch */

    Gtk::Label* chart_label_;                   /*!< The chart label */
    Gtk::Label* chart_width_label_;             /*!< The chart width label */
    Gtk::SpinButton* chart_width_spinbutton_;   /*!< The chart width spinbutton */
    Glib::RefPtr<Gtk::Adjustment> chart_width_adjustement_;   /*!< The chart width adjustement */
    Gtk::Label* chart_height_label_;            /*!< The chart height label */
    Gtk::SpinButton* chart_height_spinbutton_;  /*!< The chart height spinbutton */
    Glib::RefPtr<Gtk::Adjustment> chart_height_adjustement_;  /*!< The chart height adjustement */
    Gtk::Label* chart_total_points_label_;      /*!< The chart total_points label */
    Gtk::Switch* chart_total_points_switch_;    /*!< The chart total_points switch */




public:
    //
    // Constructor and Destructor
    //
    /*!
     *  \brief Constructor with builder
     *  \param cobject the C object
     *  \param refGlade the builder
     */
    ExportationPreferences(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);


    //
    // Function
    //
    /*!
     *  \brief Update the view
     */
    void update();


    /*!
     *  \brief Read the PDF preferences
     */
    csuper::ExportPdfPreferences readPdf();


    /*!
     *  \brief Read the chart preferences
     */
    csuper::ChartExportationPreferences readChart();
};



#endif // EXPORTATION_PREFERENCES_H_INCLUDED
