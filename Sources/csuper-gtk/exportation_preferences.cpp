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

#include "exportation_preferences.h"

#include <glibmm/i18n.h>
#include "csu_application.h"


using namespace Gtk;
using namespace Glib;
using namespace csuper;

ExportationPreferences::ExportationPreferences(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), ScrolledWindow(cobject)
{
    refGlade->get_widget("preferences_exportation_grid", main_grid_);
    refGlade->get_widget("preferences_exportation_viewport", viewport_);

    refGlade->get_widget("preferences_exportation_pdf_label", pdf_label_);
    refGlade->get_widget("preferences_exportation_pdf_utf8_label", pdf_utf8_label_);
    refGlade->get_widget("preferences_exportation_pdf_utf8_switch", pdf_utf8_switch_);
    refGlade->get_widget("preferences_exportation_pdf_font_name_label", pdf_fontname_label_);
    refGlade->get_widget("preferences_exportation_pdf_font_name_entry", pdf_font_name_entry_);
    refGlade->get_widget("preferences_exportation_pdf_embedded_font_label", pdf_embedded_font_label_);
    refGlade->get_widget("preferences_exportation_pdf_embedded_font_switch", pdf_embedded_font_switch_);
    refGlade->get_widget("preferences_exportation_pdf_direction_label", pdf_direction_label_);
    refGlade->get_widget("preferences_exportation_pdf_direction_comboboxtext", pdf_direction_combobox_);
    refGlade->get_widget("preferences_exportation_pdf_size_label", pdf_size_label_);
    refGlade->get_widget("preferences_exportation_pdf_size_comboboxtext", pdf_size_combobox_);
    refGlade->get_widget("preferences_exportation_pdf_margin_label", pdf_margin_label_);
    refGlade->get_widget("preferences_exportation_pdf_margin_spinbutton", pdf_margin_spinbutton_);
    pdf_margin_adjustement_ = RefPtr<Adjustment>::cast_dynamic(refGlade->get_object("preferences_exportation_pdf_margin_adjustment"));
    refGlade->get_widget("preferences_exportation_pdf_fontsize_label", pdf_font_size_label_);
    refGlade->get_widget("preferences_exportation_pdf_fontsize_spinbutton", pdf_font_size_spinbutton_);
    pdf_font_size_adjustement_ = RefPtr<Adjustment>::cast_dynamic(refGlade->get_object("preferences_exportation_pdf_fontsize_adjustment"));
    refGlade->get_widget("preferences_exportation_pdf_total_points_label", pdf_total_points_label_);
    refGlade->get_widget("preferences_exportation_pdf_total_points_switch", pdf_total_points_switch_);
    refGlade->get_widget("preferences_exportation_pdf_ranking_label", pdf_ranking_label_);
    refGlade->get_widget("preferences_exportation_pdf_ranking_switch", pdf_ranking_switch_);
    refGlade->get_widget("preferences_exportation_pdf_chart_size_label", pdf_size_chart_label_);
    refGlade->get_widget("preferences_exportation_pdf_chart_size_switch", pdf_size_chart_switch_);

    refGlade->get_widget("preferences_exportation_chart_label", chart_label_);
    refGlade->get_widget("preferences_exportation_chart_width_label", chart_width_label_);
    refGlade->get_widget("preferences_exportation_chart_width_spinbutton", chart_width_spinbutton_);
    chart_width_adjustement_ = RefPtr<Adjustment>::cast_dynamic(refGlade->get_object("preferences_exportation_chart_width_adjustment"));
    refGlade->get_widget("preferences_exportation_chart_height_label", chart_height_label_);
    refGlade->get_widget("preferences_exportation_chart_height_spinbutton", chart_height_spinbutton_);
    chart_height_adjustement_ = RefPtr<Adjustment>::cast_dynamic(refGlade->get_object("preferences_exportation_chart_height_adjustment"));
    refGlade->get_widget("preferences_exportation_chart_total_points_label", chart_total_points_label_);
    refGlade->get_widget("preferences_exportation_chart_total_points_switch", chart_total_points_switch_);

    if (!(PdfExportation::canUseUtf8()))
        pdf_utf8_switch_->set_sensitive(false);

    pdf_utf8_switch_->property_active().signal_changed().connect(
                                    mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    pdf_font_name_entry_->signal_changed().connect( mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    pdf_embedded_font_switch_->property_active().signal_changed().connect(
                                    mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    pdf_direction_combobox_->signal_changed().connect( mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    pdf_size_combobox_->signal_changed().connect( mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    pdf_margin_spinbutton_->signal_value_changed().connect( mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    pdf_font_size_spinbutton_->signal_value_changed().connect( mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    pdf_total_points_switch_->property_active().signal_changed().connect(
                                    mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    pdf_ranking_switch_->property_active().signal_changed().connect(
                                    mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    pdf_size_chart_switch_->property_active().signal_changed().connect(
                                    mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));

    chart_width_spinbutton_->signal_value_changed().connect( mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    chart_height_spinbutton_->signal_value_changed().connect( mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
    chart_total_points_switch_->property_active().signal_changed().connect(
                                    mem_fun(*(app()->preferencesWindow()),&PreferencesWindow::hasChange));
}


//
// Function
//
void ExportationPreferences::update()
{
    if (app()->pref()->exportPdf().charset() == ExportPdfPreferences::UTF8)
        pdf_utf8_switch_->set_active(true);
    else
        pdf_utf8_switch_->set_active(false);

    pdf_font_name_entry_->set_text(app()->pref()->exportPdf().fontName());
    pdf_embedded_font_switch_->set_active(app()->pref()->exportPdf().embeddedFont());
    pdf_direction_combobox_->set_active(app()->pref()->exportPdf().direction());
    pdf_size_combobox_->set_active(app()->pref()->exportPdf().size()-2);
    pdf_font_size_spinbutton_->set_value(app()->pref()->exportPdf().fontSize());
    pdf_margin_spinbutton_->set_value(app()->pref()->exportPdf().margin());
    pdf_total_points_switch_->set_active(app()->pref()->exportPdf().totalPoints());
    pdf_ranking_switch_->set_active(app()->pref()->exportPdf().ranking());
    pdf_size_chart_switch_->set_active(app()->pref()->exportPdf().pdfSizeForChart());

    chart_height_spinbutton_->set_value(app()->pref()->chartExportation().height());
    chart_width_spinbutton_->set_value(app()->pref()->chartExportation().width());
    chart_total_points_switch_->set_active(app()->pref()->chartExportation().totalPoints());
}

ExportPdfPreferences ExportationPreferences::readPdf()
{
    ExportPdfPreferences pref;

    if (pdf_utf8_switch_->get_active())
        pref.setCharset(ExportPdfPreferences::UTF8);
    else
        pref.setCharset(ExportPdfPreferences::WINDOWS1252);

    pref.setFontName(pdf_font_name_entry_->get_text());
    pref.setEmbeddedFont(pdf_embedded_font_switch_->get_active());

    if (pdf_direction_combobox_->get_active_id() == "portrait")
        pref.setDirection(ExportPdfPreferences::PORTRAIT);
    else
        pref.setDirection(ExportPdfPreferences::LANDSCAPE);

    if (pdf_size_combobox_->get_active_id() == "A5")
        pref.setSize(ExportPdfPreferences::A5);
    else if (pdf_size_combobox_->get_active_id() == "A4")
        pref.setSize(ExportPdfPreferences::A4);
    else
        pref.setSize(ExportPdfPreferences::A3);

    pref.setFontSize(pdf_font_size_spinbutton_->get_value_as_int());
    pref.setMargin(pdf_margin_spinbutton_->get_value_as_int());

    pref.setTotalPoints(pdf_total_points_switch_->get_active());
    pref.setRanking(pdf_ranking_switch_->get_active());
    pref.setPdfSizeForChart(pdf_size_chart_switch_->get_active());

    return pref;
}



ChartExportationPreferences ExportationPreferences::readChart()
{
    ChartExportationPreferences pref;

    pref.setHeight(chart_height_spinbutton_->get_value_as_int());
    pref.setWidth(chart_width_spinbutton_->get_value_as_int());
    pref.setTotalPoints(chart_total_points_switch_->get_active());

    return pref;
}
