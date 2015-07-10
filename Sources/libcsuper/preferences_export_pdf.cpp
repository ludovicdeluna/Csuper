/*!
 * \file    preferences_export_pdf.cpp
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_export_pdf.cpp
*
* Copyright 2014-2015
 Remi BERTHO <remi.bertho@openmailbox.org>
*
* This file is part of LibCsuper.
*
* LibCsuper is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* LibCsuper is distributed in the hope that it will be useful,
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

#include "preferences_export_pdf.h"
#include "config.h"

using namespace Glib;
using namespace std;
using namespace xmlpp;

namespace csuper
{
    //
    // Constructor
    //
    ExportPdfPreferences::ExportPdfPreferences() : font_size_(12), size_(A4), direction_(PORTRAIT),
        charset_(WINDOWS1252), margin_(40), total_points_(false), ranking_(false),
        pdf_size_for_chart_(true), embedded_font_(true), font_name_("Times-Roman")
    {

    }

    ExportPdfPreferences::ExportPdfPreferences(const unsigned int font_size, const PageSize size, const PageDirection direction,
                                               const CharacterSet charset, const unsigned int margin, const bool total_points,
                                               const bool ranking,const bool pdf_size_for_chart, const bool embedded_font,
                                               const ustring& font_name) : font_size_(font_size), size_(size), direction_(direction),
                                               charset_(charset), margin_(margin), total_points_(total_points), ranking_(ranking),
                                               pdf_size_for_chart_(pdf_size_for_chart) ,embedded_font_(embedded_font),
                                               font_name_(font_name)
   {

   }

    ExportPdfPreferences::ExportPdfPreferences(Node* xml_node, const double version)
    {
        Node* tmp_node = firstChildXmlElement(xml_node);
        font_size_ = ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        size_ = static_cast<PageSize>(ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content()));

        nextXmlElement(tmp_node);
        direction_ = static_cast<PageDirection>(ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content()));

        nextXmlElement(tmp_node);
        charset_ = static_cast<CharacterSet>(ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content()));

        nextXmlElement(tmp_node);
        margin_ = ustringToDouble(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        total_points_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        ranking_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        nextXmlElement(tmp_node);
        pdf_size_for_chart_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

        if (version > 1)
        {
            nextXmlElement(tmp_node);
            embedded_font_ = ustringToBool(static_cast<Element*>(tmp_node)->get_child_text()->get_content());

            nextXmlElement(tmp_node);
            font_name_ = static_cast<Element*>(tmp_node)->get_child_text()->get_content();
        }
        else
        {
            embedded_font_ = true;
            font_name_ = "Times-Roman";
        }

    }


    //
    // Function
    //
    bool ExportPdfPreferences::operator==(const ExportPdfPreferences& pdf) const
    {
        return (fontSize() == pdf.fontSize() && size() == pdf.size() && direction() == pdf.direction()
                && charset() == pdf.charset() && margin() == pdf.margin()
                && totalPoints() == pdf.totalPoints() && ranking() == pdf.ranking()
                && embeddedFont() == pdf.embeddedFont() && fontName() == pdf.fontName()
                && pdfSizeForChart() == pdf.pdfSizeForChart());
    }

    ustring ExportPdfPreferences::toUstring() const
    {
        return ustring::compose(_("Export pdf preferences preferences:\n - Font size: %1\n - Page size: %2\n - Page direction: %3"
                                  "\n - Character set: %4\n - Margin: %5\n - Total points: %6\n - Ranking: %7"
                                  "\n - Embedded font: %8\n - Font name: %9"),
                                fontSizeUstring(),sizeUstring(),directionUstring(),charsetUstring(),marginUstring(),
                                totalPointsUstring(),rankingUstring(),embeddedFontUstring(),fontNameUstring())
            + ustring::compose(_("\n - PDF size for chart: %10"),pdfSizeForChartUstring());
    }

    ostream& operator<<(ostream& os, const ExportPdfPreferences& pdf)
    {
        os << pdf.toUstring();
        return os;
    }

    void ExportPdfPreferences::createXmlNode(Element *parent_node) const
    {
        Element *node = parent_node->add_child("export_pdf_preferences");

        Element *node_font_size = node->add_child("font_size");
        node_font_size->add_child_text(Ascii::dtostr(fontSize()));

        Element *node_size = node->add_child("size");
        node_size->add_child_text(Ascii::dtostr(size()));

        Element *node_direction = node->add_child("direction");
        node_direction->add_child_text(Ascii::dtostr(direction()));

        Element *node_charset = node->add_child("charset");
        node_charset->add_child_text(Ascii::dtostr(charset()));

        Element *node_margin = node->add_child("margin");
        node_margin->add_child_text(Ascii::dtostr(margin()));

        Element *node_total_points = node->add_child("total_points");
        node_total_points->add_child_text(totalPointsUstring());

        Element *node_ranking = node->add_child("ranking");
        node_ranking->add_child_text(rankingUstring());

        Element *node_pdf_size_for_chart = node->add_child("pdf_size_for_chart");
        node_pdf_size_for_chart->add_child_text(pdfSizeForChartUstring());

        Element *node_embedded_font = node->add_child("embedded_font");
        node_embedded_font->add_child_text(embeddedFontUstring());

        Element *node_font_name = node->add_child("font_name");
        node_font_name->add_child_text(fontNameUstring());
    }
}
