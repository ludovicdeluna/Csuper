/*!
 * \file    export.h
 * \brief   Header for the export function
 * \author  Remi BERTHO
 * \date    22/12/14
 * \version 4.1.0
 */

/*
* export.h
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

#ifndef EXPORT_H_INCLUDED
#define EXPORT_H_INCLUDED

#include "share.h"

typedef enum
{
    UTF8,
    ISO885915
} CharacterSetPdf;

/*!
 * \struct export_pdf_preferences
 * Define the user preferences of the pdf
 */
typedef struct
{
    int font_size;                  /*!< The classical font size */
    HPDF_PageSizes size;            /*!< The size of the pdf document */
    HPDF_PageDirection direction;   /*!< The direction of the pdf document */
    CharacterSetPdf charset;        /*!< The character set of the pdf document */
    int margin;                     /*!< The margin of the pdf document */
    bool total_points_turn;         /*!< Indicate if we show the total points in each turn */
    bool ranking_turn;              /*!< Indicate if we show the ranking in each turn */
    bool pdf_size_for_chart;        /*!< Indicate if we use the pdf size for the chart*/
} export_pdf_preferences;

/*!
 * \struct export_pdf
 * Use to export a csu file to a pdf file
 */
typedef struct
{
    HPDF_Doc pdf;                   /*!< The pdf document */
    HPDF_Font font;                 /*!< The font */
    int line;                       /*!< The number of the line to be display */
    int num_page;                   /*!< The number of the page to be display */
    int line_height;                /*!< The line height */
    int table_line_height;          /*!< The line height of a table */
    export_pdf_preferences pref;    /*!< The user preferences */
    bool total_points_ranking_print;/*!< Indicate if the total points and the ranking is printed */
    bool stat_print;                /*!< Indicate if the stats are printed */
} export_pdf;


#include "preferences_files.h"
#include "csu_struct.h"
#include "csu_files.h"

/*!
 * \def DEFAULT_MARGIN
 * Define the default margin
 */
#define DEFAULT_MARGIN 40

/*!
 * \def DEFAULT_FONT_SIZE
 * Define the default font size
 */
#define DEFAULT_FONT_SIZE 12

/*!
 * \def TEXT_BUFFER_SIZE
 * Define the size of the text buffer
 */
#define TEXT_BUFFER_SIZE 1024

void errorHandler(HPDF_STATUS   error_no, HPDF_STATUS   detail_no, void *user_data);
bool canUseUtf8Pdf(void);
void pdfShowText(HPDF_Page page, char *text, export_pdf *ptr_export_pdf);
bool pdfTextOutTable(HPDF_Page page, float pos_min_x, float pos_y, const char *text, float max_width, int ranking, export_pdf *ptr_export_pdf);
bool exportToPdf(csuStruct *ptr_csu_struct, char *filename);
bool initializePdfExport(export_pdf *ptr_export_pdf,csuStruct *ptr_csu_struct);
void closeExportPdf(export_pdf *ptr_export_pdf);
void printPointsPdf(HPDF_Page page, float *pos_y, csuStruct *ptr_csu_struct,export_pdf *ptr_export_pdf,float table_width);
void printNamesPdf(export_pdf *ptr_export_pdf, csuStruct *ptr_csu_struct,float *pos_y, float table_width, HPDF_Page page);
void printLegendPdf(export_pdf *ptr_export_pdf, csuStruct *ptr_csu_struct,float *pos_y, float table_width, HPDF_Page page);
bool createFirstPagePdf(export_pdf *ptr_export_pdf, csuStruct *ptr_csu_struct, char *filename);
float tableWidthCalculatePdf(export_pdf *ptr_export_pdf, csuStruct *ptr_csu_struct,HPDF_Page page);
void createPdfGrid(HPDF_Page page,float top_x, float top_y, float bottom_x, float bottom_y, float length_row, float length_column);
void addTotalPointsRankingPdf(HPDF_Page page, csuStruct *ptr_csu_struct, float y,export_pdf *ptr_export_pdf);
void addStatsPdf(HPDF_Page page, csuStruct *ptr_csu_struct, float y,export_pdf *ptr_export_pdf);
bool createOtherPagePdf(export_pdf *ptr_export_pdf, csuStruct *ptr_csu_struct);
bool addPodiumPdf(HPDF_Page page, csuStruct *ptr_csu_struct, float y,export_pdf *ptr_export_pdf);

bool exportToCsv(csuStruct *ptr_csu_struct, char *filename);
bool exportToM(csuStruct *ptr_csu_struct, char *filename);

#endif // EXPORT_H_INCLUDED
