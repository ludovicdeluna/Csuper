/*!
 * \file    preferences.h
 * \author  Remi BERTHO
 * \date    11/06/15
 * \version 4.3.0
 */

/*
* preferences.h
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

#ifndef PREFERENCES_H_INCLUDED
#define PREFERENCES_H_INCLUDED

#include "preferences_difference_between_player.h"
#include "preferences_main_window_size.h"
#include "preferences_score_display.h"
#include "preferences_main_window_display.h"
#include "preferences_export_pdf.h"
#include "preferences_directory.h"
#include "preferences_chart_exportation.h"
#include "preferences_main_window_title_bar.h"
#include "preferences_version.h"

namespace csuper
{
    /*! \class Preferences
    *   \brief This class represent all the preferences
    */
    class Preferences
    {
    private:
        DifferenceBetweenPlayerPreferences* diff_;      /*!< The differences between player preferences */
        DirectoryPreferences* dir_;                     /*!< The directory preferences */
        ExportPdfPreferences* pdf_;                     /*!< The pdf exportation preferences */
        MainWindowDisplayPreferences* display_;         /*!< The main window display preferences */
        MainWindowSizePreferences* size_;               /*!< The main window size preferences */
        ScoreDisplayPreferences* score_;                /*!< The score display preferences */
        ChartExportationPreferences* chart_;            /*!< The chart exportation preferences */
        MainWindowTitleBarPreferences* title_bar_;      /*!< The main window title bar preferences */
        VersionPreferences* version_pref_;              /*!< The version preferences */
        static double version_;                         /*!< The version */



        //
        // Constructor
        //
        /*!
         *  \brief Constructor from a filename
         *  \exception csuper::XmlError if bad file
         */
        Preferences(const Glib::ustring& filename);

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        Preferences();

        /*!
         *  \brief Copy constructor
         */
        Preferences(const Preferences &pref);


        //
        // Destuctor
        //
        /*!
         *  \brief Destructor
         */
        ~Preferences();




        //
        // Function
        //
        /*!
         *  \brief operator =
         *  \param pref a Preferences
         *  \return a reference to the object
         */
        Preferences &operator=(const Preferences& pref);

        /*!
         *  \brief Convert to a ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param pref
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const Preferences &pref);

        /*!
         *  \brief Get the preferences
         *  \return the preferences
         */
        static Preferences *get();

        /*!
         *  \brief Write to the file
         *  \exception csuper::FileError
         */
        void writeToFile() const;





        //
        // Getter and setter
        //
        /*!
         *  \brief return the DifferenceBetweenPlayerPreferences
         *  \return the DifferenceBetweenPlayerPreferences
         */
        const DifferenceBetweenPlayerPreferences &differenceBetweenPlayer() const
        {
            return *diff_;
        }

        /*!
         *  \brief return the DifferenceBetweenPlayerPreferences
         *  \return the DifferenceBetweenPlayerPreferences
         */
        DifferenceBetweenPlayerPreferences &differenceBetweenPlayer()
        {
            return *diff_;
        }

        /*!
         *  \brief return the DirectoryPreferences
         *  \return the DirectoryPreferences
         */
        const DirectoryPreferences &directory() const
        {
            return *dir_;
        }

        /*!
         *  \brief return the DirectoryPreferences
         *  \return the DirectoryPreferences
         */
        DirectoryPreferences &directory()
        {
            return *dir_;
        }

        /*!
         *  \brief return the ExportPdfPreferences
         *  \return the ExportPdfPreferences
         */
        const ExportPdfPreferences &exportPdf() const
        {
            return *pdf_;
        }

        /*!
         *  \brief return the ExportPdfPreferences
         *  \return the ExportPdfPreferences
         */
        ExportPdfPreferences &exportPdf()
        {
            return *pdf_;
        }

        /*!
         *  \brief return the MainWindowDisplayPreferences
         *  \return the MainWindowDisplayPreferences
         */
        const MainWindowDisplayPreferences &mainWindowDisplay() const
        {
            return *display_;
        }

        /*!
         *  \brief return the MainWindowDisplayPreferences
         *  \return the MainWindowDisplayPreferences
         */
        MainWindowDisplayPreferences &mainWindowDisplay()
        {
            return *display_;
        }

        /*!
         *  \brief return the MainWindowSizePreferences
         *  \return the MainWindowSizePreferences
         */
        const MainWindowSizePreferences &mainWindowSize() const
        {
            return *size_;
        }

        /*!
         *  \brief return the MainWindowSizePreferences
         *  \return the MainWindowSizePreferences
         */
        MainWindowSizePreferences &mainWindowSize()
        {
            return *size_;
        }

        /*!
         *  \brief return the ScoreDisplayPreferences
         *  \return the ScoreDisplayPreferences
         */
        const ScoreDisplayPreferences &scoreDisplay() const
        {
            return *score_;
        }

        /*!
         *  \brief return the ScoreDisplayPreferences
         *  \return the ScoreDisplayPreferences
         */
        ScoreDisplayPreferences &scoreDisplay()
        {
            return *score_;
        }


        /*!
         *  \brief return the ChartExportationPreferences
         *  \return the ChartExportationPreferences
         */
        const ChartExportationPreferences &chartExportation() const
        {
            return *chart_;
        }

        /*!
         *  \brief return the ChartExportationPreferences
         *  \return the ChartExportationPreferences
         */
        ChartExportationPreferences &chartExportation()
        {
            return *chart_;
        }

        /*!
         *  \brief return the MainWindowTitleBarPreferences
         *  \return the MainWindowTitleBarPreferences
         */
        const MainWindowTitleBarPreferences &mainWindowTitleBar() const
        {
            return *title_bar_;
        }

        /*!
         *  \brief return the MainWindowTitleBarPreferences
         *  \return the MainWindowTitleBarPreferences
         */
        MainWindowTitleBarPreferences &mainWindowTitleBar()
        {
            return *title_bar_;
        }

        /*!
         *  \brief return the VersionPreferences
         *  \return the VersionPreferences
         */
        const VersionPreferences &version() const
        {
            return *version_pref_;
        }

        /*!
         *  \brief return the VersionPreferences
         *  \return the VersionPreferences
         */
        VersionPreferences &version()
        {
            return *version_pref_;
        }

    };
}



#endif // PREFERENCES_H_INCLUDED
