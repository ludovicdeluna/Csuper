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

namespace csuper
{
    /*! \class Game
    *   \brief This class is used to export a game into PDF
    */
    class PdfExportation
    {
    private:
        HPDF_Doc pdf_;                   /*!< The pdf document */
        HPDF_Font font_;                 /*!< The font */
        unsigned int line_;                       /*!< The number of the line to be display */
        int num_page_;                   /*!< The number of the page to be display */
        int line_height_;                /*!< The line height */
        int table_line_height_;          /*!< The line height of a table */
        ExportPdfPreferences pref_;      /*!< The user preferences */
        bool total_points_ranking_print_;/*!< Indicate if the total points and the ranking is printed */
        bool stat_print_;                /*!< Indicate if the stats are printed */
        const Game* game_;               /*!< The game */





        //
        // Constructor
        //
        /*!
         *  \brief Constructor
         *  \param game the game
         *  \exception csuper::pdfError if bad file
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
         * \exception csuper::pdfError
         */
        bool createFirstPage(const Glib::ustring& filename);

        /*!
         *  Create the the others page
         * \return true if it need another page, false otherwise
         * \exception csuper::pdfError
         */
        bool createOtherPage();




        //
        // Print elements
        //
        /*!
         *  Print the names on a pdf page
         * \param[in] page the page
         * \param[in] pos_y the first position on the y axis
         * \param[in] table_width the width of a table
         * \exception csuper::pdfError
         */
        void printNames(float& pos_y, const float table_width, HPDF_Page& page);

        /*!
         *  Print the legend on a pdf page if needed
         * \param[in] page the page
         * \param[in] pos_y the first position on the y axis
         * \param[in] table_width the width of a table
         * \exception csuper::pdfError
         */
        void printLegend(float& pos_y, const float table_width, HPDF_Page& page);

        /*!
         *  Print the points on a pdf page
         * \param[in] page the page
         * \param[in] pos_y the first position on the y axis
         * \param[in] table_width the width of a table
         * \exception csuper::pdfError
         */
        void printPoints(float& pos_y, const float table_width, HPDF_Page& page);

        /*!
         *  Print the total points and the ranking
         * \param[in] page the pdf page
         * \param[in] y the top y coordinate
         */
        void addTotalPointsRanking(HPDF_Page& page, float& y);

        /*!
         *  Print the statistics
         * \param[in] page the pdf page
         * \param[in] y the top y coordinate
         */
        void addStats(HPDF_Page& page, float& y);

        /*!
         *  Print the podium
         * \param[in] page the pdf page
         * \param[in] y the top y coordinate
         * \return true if it need another page, false otherwise
         */
        bool addPodium(HPDF_Page& page, const float y);




        //
        // Print function
        //
        /*!
         *  Print the text in the page
         * \param[in] page the page
         * \param[in] text the text to print
         * \exception csuper::pdfError if conversion failed
         */
        void showText(HPDF_Page& page, const Glib::ustring& text);

        /*!
         *  Print the text in the page center with a maximum width
         * \param[in] page the page
         * \param[in] pos_min_x the minimum position on the x axis
         * \param[in] pos_y the position on the y axis
         * \param[in] text the text to print
         * \param[in] max_width the maximum width of the text
         * \param[in] ranking the ranking of the player to determine the color of the text, put 0 to print in black
         * \return true if everything is OK, false otherwise
         */
        void textOutTable(HPDF_Page& page, const float pos_min_x, const float pos_y, const Glib::ustring& text,
                             const float max_width, const int ranking=0);

        /*!
         *  Calculate the table width
         * \param[in] page the page
         * \return the table width
         */
        float tableWidthCalculate(HPDF_Page& page);

        /*!
         *  Print a grid to a pdf page
         * \param[in] page the pdf page
         * \param[in] top_x the x coordinate of the top left corn
         * \param[in] top_y the y coordinate of the top left corn
         * \param[in] bottom_x the x coordinate of the bottom right corn
         * \param[in] bottom_y the y coordinate of the bottom right corn
         * \param[in] length_row the length of the row
         * \param[in] length_column the length of the column
         */
        void createGrid(HPDF_Page& page,const float top_x, const float top_y, const float bottom_x, const float bottom_y,
                           const float length_row, const float length_column);



        //
        // Static function
        //
        /*!
         *  Throw an exception when an error occured on libhpdf
         * \param[in] error_no the error number
         * \param[in] detail_no the detail number
         * \param[in] user_data user data
         */
        static void errorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);

        /*!
         * \fn bool canUseUtf8Pdf(void)
         *  Say if you can use UTF-8 in a pdf file or not
         * \return true if you can use UF-8, false otherwise
         */
        static bool canUseUtf8();

    public:
        /*!
         *  Export a csu structure to a pdf file
         * \param[in] game the game to be exported
         * \param[in] pref the preferences
         * \param[in] filename the filename of the pdf file
         * \exception csuper::pdfError
         */
        static void exportToPdf(const Game* game, const ExportPdfPreferences& pref, const Glib::ustring& filename);
    };
}

#endif // PDF_EXPORTATION_H_INCLUDED
