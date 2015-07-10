/*!
 * \file    pdf_exportation.h
 * \brief   Exceptions of Csuper
 * \author  Remi BERTHO
 * \date    12/06/14
 * \version 4.3.0
 */

/*
* pdf_exportation.h
*
* Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
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

#ifndef PDF_EXPORTATION_H_INCLUDED
#define PDF_EXPORTATION_H_INCLUDED


#include <hpdf.h>
#include "game.h"
#include "preferences_export_pdf.h"

#include <podofo/podofo.h>

namespace csuper
{
    /*! \class Game
    *   \brief This class is used to export a game into PDF
    */
    class PdfExportation
    {
    private:
        PoDoFo::PdfMemDocument* pdf_;                   /*!< The pdf document */
        PoDoFo::PdfFont* font_;                 /*!< The font */
        PoDoFo::PdfPainter* painter_;
        unsigned int line_;                       /*!< The number of the line to be display */
        int num_page_;                   /*!< The number of the page to be display */
        int line_height_;                /*!< The line height */
        int table_line_height_;          /*!< The line height of a table */
        ExportPdfPreferences pref_;      /*!< The user preferences */
        bool total_points_ranking_print_;/*!< Indicate if the total points and the ranking is printed */
        bool stat_print_;                /*!< Indicate if the stats are printed */
        const Game* game_;               /*!< The game */
        double height_;
        double width_;
        double table_width_;





        //
        // Constructor
        //
        /*!
         *  \brief Constructor
         *  \param game the game
         *  \exception csuper::PdfError if bad file
         */
        PdfExportation(const Game* game,  const ExportPdfPreferences& pref);




        //
        // Destuctor
        //
        /*!
         *  \brief Destructor
         */
        ~PdfExportation();



        //
        // Create page
        //
        /*!
         *  Create the first page of the pdf
         * \param[in] filename the filename of the pdf file
         * \return true if it need another page, false otherwise
         * \exception PoDoFo::PdfError
         */
        bool createFirstPage(const Glib::ustring& filename);

        /*!
         *  Create the the others page
         * \return true if it need another page, false otherwise
         * \exception PoDoFo::PdfError
         */
        bool createOtherPage();




        //
        // Print elements
        //
        /*!
         *  Print the names on a pdf page
         * \param[in] pos_y the first position on the y axis
         * \exception PoDoFo::PdfError
         */
        void printNames(double& pos_y);

        /*!
         *  Print the legend on a pdf page if needed
         * \param[in] pos_y the first position on the y axis
         * \exception PoDoFo::PdfError
         */
        void printLegend(double& pos_y);

        /*!
         *  Print the points on a pdf page
         * \param[in] pos_y the first position on the y axis
         * \exception PoDoFo::PdfError
         */
        void printPoints(double& pos_y);

        /*!
         *  Print the total points and the ranking
         * \param[in] y the top y coordinate
         */
        void addTotalPointsRanking(double& y);

        /*!
         *  Print the statistics
         * \param[in] y the top y coordinate
         */
        void addStats(double& y);

        /*!
         *  Print the podium
         * \param[in] y the top y coordinate
         * \return true if it need another page, false otherwise
         */
        bool addPodium(const double y);




        //
        // Print function
        //
        /*!
         *  Print the text
         * \param[in] text the text to print
         * \exception PoDoFo::PdfError if conversion failed
         */
        void showText(const Glib::ustring& text);

        /*!
         *  Print the text in the page center with a maximum width
         * \param[in] pos_min_x the minimum position on the x axis
         * \param[in] pos_y the position on the y axis
         * \param[in] text the text to print
         * \param[in] max_width the maximum width of the text
         * \param[in] ranking the ranking of the player to determine the color of the text, put 0 to print in black
         * \return true if everything is OK, false otherwise
         */
        void textOutTable(const double pos_min_x, const double pos_y, const Glib::ustring& text,
                             const double max_width, const int ranking=0);

        /*!
         *  Calculate the table width
         * \return the table width
         */
        void tableWidthCalculate();

        /*!
         *  Print a grid to a pdf page
         * \param[in] top_x the x coordinate of the top left corn
         * \param[in] top_y the y coordinate of the top left corn
         * \param[in] bottom_x the x coordinate of the bottom right corn
         * \param[in] bottom_y the y coordinate of the bottom right corn
         * \param[in] length_row the length of the row
         * \param[in] length_column the length of the column
         */
        void createGrid(const double top_x, const double top_y, const double bottom_x, const double bottom_y,
                           const double length_row, const double length_column);



        //
        // Fusion function
        //

        /*!
         *  Delete the temporary files
         * \param[in] filename the filenames
         */
        static void deleteTemporaryFiles(std::string& filename);



        //
        // Static function
        //
        static std::string convertCharsetPdf(const Glib::ustring& str, const ExportPdfPreferences::CharacterSet charset);


        static PoDoFo::PdfString ustringToPdfstring(const Glib::ustring& str);


    public:
        /*!
         *  Export a csu structure to a pdf file
         * \param[in] game the game to be exported
         * \param[in] pdf_pref the pdf preferences
         * \param[in] chart_pref the chart preferences
         * \param[in] filename the filename of the pdf file
         * \exception csuper::PdfError
         */
        static void exportToPdf(const Game* game, const ExportPdfPreferences& pdf_pref, const ChartExportationPreferences& chart_pref, const Glib::ustring& filename);
    };
}

#endif // PDF_EXPORTATION_H_INCLUDED
