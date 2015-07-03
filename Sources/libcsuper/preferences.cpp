/*!
 * \file    preferences.cpp
 * \author  Remi BERTHO
 * \date    11/06/15
 * \version 4.3.0
 */

/*
* preferences.cpp
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

#include "preferences.h"
#include "config.h"
#include "exceptions.h"
#include <iostream>

using namespace std;
using namespace Glib;
using namespace xmlpp;

namespace csuper
{
    double Preferences::version_(1.1);

    //
    // Constructor
    //
    Preferences::Preferences()
    {
        diff_ = new DifferenceBetweenPlayerPreferences();
        dir_ = new DirectoryPreferences();
        pdf_ = new ExportPdfPreferences();
        display_ = new MainWindowDisplayPreferences();
        size_ = new MainWindowSizePreferences();
        score_ = new ScoreDisplayPreferences();
        chart_ = new ChartExportationPreferences();
    }


    Preferences::Preferences(const Preferences &pref)
    {
        diff_ = new DifferenceBetweenPlayerPreferences(*(pref.diff_));
        dir_ = new DirectoryPreferences(*(pref.dir_));
        pdf_ = new ExportPdfPreferences(*(pref.pdf_));
        display_ = new MainWindowDisplayPreferences(*(pref.display_));
        size_ = new MainWindowSizePreferences(*(pref.size_));
        score_ = new ScoreDisplayPreferences(*(pref.score_));
        chart_ = new ChartExportationPreferences(*(pref.chart_));
    }


    Preferences::Preferences(const ustring& filename)
    {
        DomParser parser;
        try
        {
            parser.parse_file(filename);
        }
        catch (xmlpp::exception &e)
        {
        	cerr << e.what() << endl;
            throw XmlError(ustring::compose(_("Cannot open the file %1"),filename));
        }

        Node *node = parser.get_document()->get_root_node();
        firstChildXmlElement(node);

        // Version
        double file_version = ustringToDouble(static_cast<Element*>(node)->get_child_text()->get_content());
        if (file_version > version_)
            throw XmlError(ustring::compose(_("This version of Csuper only support preferences file version less than or equal to %1"),version_));

        // toolbar_button
        if (file_version == 1)
            nextXmlElement(node);

        // main_window_size
        nextXmlElement(node);
        size_ = new MainWindowSizePreferences(node);

        // difference_between_player
        nextXmlElement(node);
        diff_ = new DifferenceBetweenPlayerPreferences(node);

        // score_display
        nextXmlElement(node);
        score_ = new ScoreDisplayPreferences(node);

        // main_window_display
        nextXmlElement(node);
        display_ = new MainWindowDisplayPreferences(node);

        // export_pdf
        nextXmlElement(node);
        pdf_ = new ExportPdfPreferences(node,file_version);

        // chart
        nextXmlElement(node);
        chart_ = new ChartExportationPreferences(node);

        // directory
        if (file_version > 1)
        {
            nextXmlElement(node);
            dir_ = new DirectoryPreferences(node);
        } else
            dir_ = new DirectoryPreferences();

    }


    //
    // Destructor
    //
    Preferences::~Preferences()
    {
        delete diff_;
        delete dir_;
        delete pdf_;
        delete display_;
        delete size_;
        delete score_;
        delete chart_;
    }

    //
    // Function
    //
    Preferences &Preferences::operator=(const Preferences& pref)
    {
        if (this==&pref)
            return *this;

        delete diff_;
        delete dir_;
        delete pdf_;
        delete display_;
        delete size_;
        delete score_;
        delete chart_;

        diff_ = new DifferenceBetweenPlayerPreferences(*(pref.diff_));
        dir_ = new DirectoryPreferences(*(pref.dir_));
        pdf_ = new ExportPdfPreferences(*(pref.pdf_));
        display_ = new MainWindowDisplayPreferences(*(pref.display_));
        size_ = new MainWindowSizePreferences(*(pref.size_));
        score_ = new ScoreDisplayPreferences(*(pref.score_));
        chart_ = new ChartExportationPreferences(*(pref.chart_));

        return *this;
    }

    ustring Preferences::toUstring() const
    {
        return mainWindowSize().toUstring() + "\n"
            + differenceBetweenPlayer().toUstring() + "\n"
            + scoreDisplay().toUstring() + "\n"
            + mainWindowDisplay().toUstring() + "\n"
            + exportPdf().toUstring() + "\n"
            + chartExportation().toUstring() + "\n"
            + directory().toUstring();
    }

    ostream& operator<<(ostream& os, const Preferences& pref)
    {
        os << pref.toUstring() << endl;
        return os;
    }


    Preferences *Preferences::get()
    {
        string filename;
        if (Portable::getPortable())
            filename = build_filename(CSUPER_DIRECTORY_NAME,CSUPER_PREFERENCES_FILENAME);
        else
            filename = build_filename(get_home_dir(),CSUPER_DIRECTORY_NAME,CSUPER_PREFERENCES_FILENAME);

        return new Preferences(filename);
    }

    void Preferences::writeToFile() const
    {
        string filename;
        if (Portable::getPortable())
            filename = build_filename(CSUPER_DIRECTORY_NAME,CSUPER_PREFERENCES_FILENAME);
        else
            filename = build_filename(get_home_dir(),CSUPER_DIRECTORY_NAME,CSUPER_PREFERENCES_FILENAME);

        Document doc;
        Element* root = doc.create_root_node("csu_preferences");

        // Version
        Element* node_version = root->add_child("version");
        node_version->add_child_text(Ascii::dtostr(version_));

        mainWindowSize().createXmlNode(root);
        differenceBetweenPlayer().createXmlNode(root);
        scoreDisplay().createXmlNode(root);
        mainWindowDisplay().createXmlNode(root);
        exportPdf().createXmlNode(root);
        chartExportation().createXmlNode(root);
        directory().createXmlNode(root);


        try
        {
            doc.write_to_file_formatted(filename,"UTF-8");
        }
        catch (xmlpp::exception& e)
        {
            cerr << e.what() << endl;
            throw FileError(ustring::compose(_("Error while writing the CSU preferences file %1"),filename));
        }
    }
}
