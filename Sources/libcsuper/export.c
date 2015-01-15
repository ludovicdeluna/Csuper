/*!
 * \file    export.c
 * \brief   Export function
 * \author  Remi BERTHO
 * \date    22/12/14
 * \version 4.1.0
 */

/*
* export.c
*
* Copyright 2014-2015 Remi BERTHO <remi.bertho@gmail.com>
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

#include "export.h"


/*!
 * \fn void errorHandler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
 *  Print an error message when an error occured on libhpdf
 * \param[in] error_no the error number
 * \param[in] detail_no the detail number
 * \param[in] user_data user data
 */
void errorHandler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no, (HPDF_UINT)detail_no);
}


/*!
 * \fn bool canUseUtf8Pdf(void)
 *  Say if you can use UTF-8 in a pdf file or not
 * \return true if you can use UF-8, false otherwise
 */
bool canUseUtf8Pdf(void)
{
#if HPDF_MAJOR_VERSION == 2 && HPDF_MINOR_VERSION < 3
    return false;
#else
    return true;
#endif // HPDF_MAJOR_VERSION
}

/*!
 * \fn void pdfShowText(HPDF_Page page, char *text, export_pdf *ptr_export_pdf)
 *  Print the text in the page
 * \param[in] page the page
 * \param[in] text the text to print
 * \param[in] ptr_export_pdf a pointer on a export_pdf
 */
void pdfShowText(HPDF_Page page, char *text, export_pdf *ptr_export_pdf)
{
    if (ptr_export_pdf->pref.charset == UTF8)
    {
#if HPDF_MAJOR_VERSION == 2 && HPDF_MINOR_VERSION < 3
        char *text_buffer = utf8ToLatin9(text);
        HPDF_Page_ShowText(page,text_buffer);
        free(text_buffer);
#else
        HPDF_Page_ShowText(page, text);
#endif // HPDF_MAJOR_VERSION
    }
    else
    {
        char *text_buffer = utf8ToLatin9(text);
        HPDF_Page_ShowText(page,text_buffer);
        free(text_buffer);
    }
}


/*!
 * \fn bool pdfTextOutTable(HPDF_Page page, float pos_min_x, float pos_y, const char *text, float max_width, int ranking, export_pdf *ptr_export_pdf)
 *  Print the text in the page center with a maximum width
 * \param[in] page the page
 * \param[in] pos_min_x the minimum position on the x axis
 * \param[in] pos_y the position on the y axis
 * \param[in] text the text to print
 * \param[in] max_width the maximum width of the text
 * \param[in] ranking the ranking of the player to determine the color of the text, put 0 to print in black
 * \param[in] ptr_export_pdf a pointer on a export_pdf
 * \return true if everything is OK, false otherwise
 */
bool pdfTextOutTable(HPDF_Page page, float pos_min_x, float pos_y, const char *text, float max_width, int ranking, export_pdf *ptr_export_pdf)
{
    float text_width;
    int nb_char;
    char *text_buffer;

    if (ptr_export_pdf->pref.charset == UTF8)
    {
#if HPDF_MAJOR_VERSION == 2 && HPDF_MINOR_VERSION < 3
        text_buffer = utf8ToLatin9(text);
#else
        text_buffer = myAlloc(TEXT_BUFFER_SIZE*sizeof(char));
        strncpy(text_buffer,text,TEXT_BUFFER_SIZE);
#endif // HPDF_MAJOR_VERSION
    }
    else
    {
        text_buffer = utf8ToLatin9(text);
    }
    text_width = HPDF_Page_TextWidth(page, text_buffer);
    nb_char = strlen(text_buffer);

    // Reduce the length of the text if needed
    while (text_width > max_width && nb_char > 1)
    {
        nb_char = strlen(text_buffer);
        text_buffer[nb_char-1] = '\0';
        text_width = HPDF_Page_TextWidth(page, text_buffer);
    }

    // Set the color
    switch (ranking)
    {
    case 0:
        HPDF_Page_SetRGBFill(page,0,0,0);
        break;
    case 1:
        HPDF_Page_SetRGBFill(page,0,0.4,0);
        break;
    case 2:
        HPDF_Page_SetRGBFill(page,0,0,0.25);
        break;
    case 3:
        HPDF_Page_SetRGBFill(page,0.75,0,0);
        break;
    default:
        HPDF_Page_SetRGBFill(page,0.35,0.2,0);
    }

    // Display the text center in the table
    if (HPDF_Page_TextOut (page, (max_width - text_width) / 2 + pos_min_x,pos_y, text_buffer) == HPDF_OK)
        return true;
    else
        return false;

    free(text_buffer);


    // Reset the color
    HPDF_Page_SetRGBFill(page,0,0,0);
}


/*!
 * \fn bool exportToPdf(csuStruct *ptr_csu_struct, char *filename)
 *  Export the csu structure to a pdf
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \param[in] filename the filename of the pdf file
 * \return true if everything is OK, false otherwise
 */
bool exportToPdf(csuStruct *ptr_csu_struct, char *filename)
{
    export_pdf my_pdf;
    if (!initializePdfExport(&my_pdf,ptr_csu_struct))
        return false;

    if (createFirstPagePdf(&my_pdf,ptr_csu_struct,filename))
        while(createOtherPagePdf(&my_pdf,ptr_csu_struct));

    if (HPDF_SaveToFile(my_pdf.pdf, filename) == HPDF_OK)
        return true;
    else
        return false;

    closeExportPdf(&my_pdf);
}

/*!
 * \fn bool initializePdfExport(export_pdf *ptr_export_pdf,csuStruct *ptr_csu_struct)
 *  Initialize the exportation
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \param[in] ptr_export_pdf a pointer on a export_pdf
 * \return true if everything is OK, false otherwise
 */
bool initializePdfExport(export_pdf *ptr_export_pdf,csuStruct *ptr_csu_struct)
{
    char home_path[SIZE_MAX_FILE_NAME]="";
#ifndef PORTABLE
    readHomePathSlash(home_path);
#endif // PORTABLE

    // Create the pdf
    ptr_export_pdf->pdf = HPDF_New(errorHandler,NULL);
    if (!ptr_export_pdf->pdf)
    {
        printf (_("Error: cannot create PdfDoc object\n"));
        return false;
    }


    // Initialize the structure
    ptr_export_pdf->line = 0;
    ptr_export_pdf->num_page = 2;
    readFilePdfPreferences(home_path,&(ptr_export_pdf->pref));
    ptr_export_pdf->line_height = ptr_export_pdf->pref.font_size;
    ptr_export_pdf->table_line_height = 1.8*ptr_export_pdf->pref.font_size;
    ptr_export_pdf->total_points_ranking_print = false;


    // Initialize the font
    if (ptr_export_pdf->pref.charset == UTF8)
    {
#if HPDF_MAJOR_VERSION == 2 && HPDF_MINOR_VERSION < 3
        ptr_export_pdf->font = HPDF_GetFont(ptr_export_pdf->pdf,"Times-Roman", "ISO8859-15");
#else
        char font_name[SIZE_MAX_FILE_NAME];
        HPDF_UseUTFEncodings(ptr_export_pdf->pdf);
        strncpy(font_name,HPDF_LoadTTFontFromFile(ptr_export_pdf->pdf,"Fonts/DejaVuSans.ttf", HPDF_TRUE),SIZE_MAX_FILE_NAME);
        if (font_name == NULL)
        {
            printf(_("\nError:The font doesn't exsist\n"));
            return false;
        }
        ptr_export_pdf->font = HPDF_GetFont(ptr_export_pdf->pdf,font_name, "UTF-8");
#endif // HPDF_MAJOR_VERSION
    }
    else
        ptr_export_pdf->font = HPDF_GetFont(ptr_export_pdf->pdf,"Times-Roman", "ISO8859-15");

    // Set the attribute of the pdf
    #ifdef _WIN32
    HPDF_SetInfoAttr(ptr_export_pdf->pdf,HPDF_INFO_AUTHOR,getenv("USERNAME"));
    #else
    HPDF_SetInfoAttr(ptr_export_pdf->pdf,HPDF_INFO_AUTHOR,getenv("USER"));
    #endif
    HPDF_SetInfoAttr(ptr_export_pdf->pdf,HPDF_INFO_CREATOR,"Csuper");
    HPDF_SetCompressionMode(ptr_export_pdf->pdf,HPDF_COMP_ALL);
    time_t timestamp;
    struct tm *t;
    timestamp = time(NULL);
    t = localtime(&timestamp);
    HPDF_Date date = {t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec,'+',0,0};
    HPDF_SetInfoDateAttr(ptr_export_pdf->pdf,HPDF_INFO_CREATION_DATE,date);
    HPDF_SetInfoDateAttr(ptr_export_pdf->pdf,HPDF_INFO_MOD_DATE,date);


    return true;
}


/*!
 * \fn void closeExportPdf(export_pdf *ptr_export_pdf)
 *  Close the structure export_pdf
 * \param[in] ptr_export_pdf a pointer on a export_pdf
 */
void closeExportPdf(export_pdf *ptr_export_pdf)
{
    HPDF_Free(ptr_export_pdf->pdf);
}


/*!
 * \fn void printPointsPdf(HPDF_Page page, float *pos_y, csuStruct *ptr_csu_struct,export_pdf *ptr_export_pdf,float table_width)
 *  Print the points on a pdf page
 * \param[in] page the page
 * \param[in] pos_y a pointer to the first position on the y axis
 * \param[in] table_width the width of a table
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \param[in] ptr_export_pdf a pointer on a export_pdf
 * \return true if everything is OK, false otherwise
 */
void printPointsPdf(HPDF_Page page, float *pos_y, csuStruct *ptr_csu_struct,export_pdf *ptr_export_pdf,float table_width)
{
    char text_buffer[TEXT_BUFFER_SIZE]="";
    int i;

    while ((*pos_y > ptr_export_pdf->pref.margin + ptr_export_pdf->pref.font_size ) && (ptr_export_pdf->line < maxNbTurn(ptr_csu_struct)))
    {
        sprintf(text_buffer,_("Turn %d"),ptr_export_pdf->line);
        pdfTextOutTable(page,ptr_export_pdf->pref.margin,*pos_y,text_buffer,table_width,0,ptr_export_pdf);

        for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        {
            if (ptr_csu_struct->nb_turn[i] >= ptr_export_pdf->line+1)
            {
                switch (ptr_csu_struct->config.decimal_place)
                {
                case 0 :
                    sprintf(text_buffer,"%.0f",ptr_csu_struct->point[i][ptr_export_pdf->line]);
                    break;
                case 1 :
                    sprintf(text_buffer,"%.1f",ptr_csu_struct->point[i][ptr_export_pdf->line]);
                    break;
                case 2 :
                    sprintf(text_buffer,"%.2f",ptr_csu_struct->point[i][ptr_export_pdf->line]);
                    break;
                case 3 :
                    sprintf(text_buffer,"%.3f",ptr_csu_struct->point[i][ptr_export_pdf->line]);
                    break;
                }
                pdfTextOutTable(page,ptr_export_pdf->pref.margin + (i+1)*table_width,*pos_y,text_buffer,table_width,ptr_csu_struct->rank[i],ptr_export_pdf);
            }
        }

        (ptr_export_pdf->line) += 1;
        *pos_y -= ptr_export_pdf->table_line_height;
    }
}


/*!
 * \fn bool createFirstPagePdf(export_pdf *ptr_export_pdf, csuStruct *ptr_csu_struct, char *filename)
 *  Create the first page of the pdf
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \param[in] ptr_export_pdf a pointer on a export_pdf
 * \param[in] filename the filename of the pdf file
 * \return true if it need another page, false otherwise
 */
bool createFirstPagePdf(export_pdf *ptr_export_pdf, csuStruct *ptr_csu_struct, char *filename)
{
    float height;
    float width;
    HPDF_Page first_page;
    char simple_filename[SIZE_MAX_FILE_NAME];
    char text_buffer[TEXT_BUFFER_SIZE]="";
    int i;
    float table_width;
    float text_pos_y;
    bool create_another_page = true;

    // Add a new page object.
    first_page = HPDF_AddPage(ptr_export_pdf->pdf);
    HPDF_Page_SetSize(first_page,ptr_export_pdf->pref.size,ptr_export_pdf->pref.direction);

    // Get the heoght and the width
    height = HPDF_Page_GetHeight (first_page);
    width = HPDF_Page_GetWidth (first_page);

    // Print the filename
    HPDF_Page_SetFontAndSize (first_page, ptr_export_pdf->font, 2*ptr_export_pdf->pref.font_size);
    getSimpleFilenameFromFullFilename(filename,simple_filename);
    removeFilenameExtension(simple_filename);
    HPDF_Page_BeginText (first_page);
    pdfTextOutTable(first_page,0,height - ptr_export_pdf->pref.margin*2/3 - ptr_export_pdf->line_height,simple_filename,width,0,ptr_export_pdf);
    HPDF_Page_EndText (first_page);
    HPDF_SetInfoAttr(ptr_export_pdf->pdf,HPDF_INFO_TITLE,simple_filename);


    // Print the header
    HPDF_Page_SetFontAndSize (first_page, ptr_export_pdf->font, ptr_export_pdf->pref.font_size);
    HPDF_Page_BeginText (first_page);
    HPDF_Page_MoveTextPos (first_page, ptr_export_pdf->pref.margin, height - ptr_export_pdf->pref.margin - ptr_export_pdf->pref.font_size*2);

    // File creation
    sprintf(text_buffer,_("File created on the %02.0f/%02.0f/%4.0f"),ptr_csu_struct->day,ptr_csu_struct->month,ptr_csu_struct->year);
    pdfShowText (first_page, text_buffer,ptr_export_pdf);

    // Number of player
    HPDF_Page_MoveTextPos (first_page, 0, - ptr_export_pdf->line_height);
    sprintf(text_buffer,_("Number of players: %.0f"),ptr_csu_struct->nb_player);
    pdfShowText (first_page, text_buffer,ptr_export_pdf);

    // Maximum number of turn
    HPDF_Page_MoveTextPos (first_page, 0, - ptr_export_pdf->line_height);
    sprintf(text_buffer,_("Maximum number of turns: %d"),maxNbTurn(ptr_csu_struct)-1);
    pdfShowText (first_page, text_buffer,ptr_export_pdf);

    // Name of the game configuration
    HPDF_Page_MoveTextPos (first_page, 0, - ptr_export_pdf->line_height);
    sprintf(text_buffer,_("Name of the game configuration: %s"),ptr_csu_struct->config.name);
    pdfShowText (first_page, text_buffer,ptr_export_pdf);


    // Calculate the table width
    table_width = ((width - 2*ptr_export_pdf->pref.margin)/(ptr_csu_struct->nb_player+1));

    // Names
    pdfTextOutTable(first_page,ptr_export_pdf->pref.margin,height - ptr_export_pdf->pref.margin - 7* ptr_export_pdf->line_height,_("Name"),table_width,0,ptr_export_pdf);
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        pdfTextOutTable(first_page,ptr_export_pdf->pref.margin + (i+1)*table_width,height - ptr_export_pdf->pref.margin - 7* ptr_export_pdf->line_height,
                        ptr_csu_struct->player_names[i],table_width,ptr_csu_struct->rank[i],ptr_export_pdf);

    // Points
    text_pos_y = height - ptr_export_pdf->pref.margin - 7* ptr_export_pdf->line_height - ptr_export_pdf->table_line_height;
    printPointsPdf(first_page,&text_pos_y,ptr_csu_struct,ptr_export_pdf,table_width);

    pdfTextOutTable(first_page,0,ptr_export_pdf->pref.margin*2/3,_("Page 1"),width,0,ptr_export_pdf);

    HPDF_Page_EndText (first_page);

    createPdfGrid(first_page,ptr_export_pdf->pref.margin,height - ptr_export_pdf->pref.margin - 7* ptr_export_pdf->line_height + ptr_export_pdf->table_line_height*2/3,
                  width-ptr_export_pdf->pref.margin,text_pos_y+ptr_export_pdf->table_line_height*2/3,ptr_export_pdf->table_line_height,table_width);

    if (text_pos_y-3*ptr_export_pdf->table_line_height-ptr_export_pdf->pref.font_size > ptr_export_pdf->pref.margin)
    {
        addTotalPointsRankingPdf(first_page,ptr_csu_struct,text_pos_y-ptr_export_pdf->table_line_height,ptr_export_pdf);
        create_another_page = addPodiumPdf(first_page,ptr_csu_struct,text_pos_y-3*ptr_export_pdf->table_line_height-ptr_export_pdf->pref.font_size,ptr_export_pdf);
    }

    return create_another_page;
}


/*!
 * \fn void createPdfGrid(HPDF_Page page,float top_x, float top_y, float bottom_x, float bottom_y, float length_row, float length_column)
 *  Print a grid to a pdf page
 * \param[in] page the pdf page
 * \param[in] top_x the x coordinate of the top left corn
 * \param[in] top_y the y coordinate of the top left corn
 * \param[in] bottom_x the x coordinate of the bottom right corn
 * \param[in] bottom_y the y coordinate of the bottom right corn
 * \param[in] length_row the length of the row
 * \param[in] length_column the length of the column
 */
void createPdfGrid(HPDF_Page page,float top_x, float top_y, float bottom_x, float bottom_y, float length_row, float length_column)
{
    float x,y;

    HPDF_Page_SetLineWidth(page, 1);

    // Vertical grid;
    for (y = top_y ; y >= bottom_y ; y -= length_row)
    {
        HPDF_Page_MoveTo(page,top_x,y);
        HPDF_Page_LineTo(page,bottom_x,y);
        HPDF_Page_Stroke(page);
    }

    // Horizontal grid;
    for (x = top_x ; x <= bottom_x ; x += length_column)
    {
        HPDF_Page_MoveTo(page,x,top_y);
        HPDF_Page_LineTo(page,x,bottom_y);
        HPDF_Page_Stroke(page);
    }
}


/*!
 * \fn void addTotalPointsRankingPdf(HPDF_Page page, csuStruct *ptr_csu_struct, float y,export_pdf *ptr_export_pdf)
 *  Print the total points and the ranking on a pdf page
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \param[in] page the pdf page
 * \param[in] y the top y coordinate
 * \param[in] ptr_export_pdf a pointer on a export_pdf
 */
void addTotalPointsRankingPdf(HPDF_Page page, csuStruct *ptr_csu_struct, float y,export_pdf *ptr_export_pdf)
{
    char text_buffer[TEXT_BUFFER_SIZE]="";
    int i;
    float width = HPDF_Page_GetWidth (page);

    // Calculate the table width
    float table_width = ((width - 2*ptr_export_pdf->pref.margin)/(ptr_csu_struct->nb_player+1));

    HPDF_Page_BeginText(page);

    // Names
    pdfTextOutTable(page,ptr_export_pdf->pref.margin,y,_("Name"),table_width,0,ptr_export_pdf);
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        pdfTextOutTable(page,ptr_export_pdf->pref.margin + (i+1)*table_width,y,ptr_csu_struct->player_names[i],table_width,ptr_csu_struct->rank[i],ptr_export_pdf);

    // Print the finals points
    pdfTextOutTable(page,ptr_export_pdf->pref.margin,y- ptr_export_pdf->table_line_height,_("Total points"),table_width,0,ptr_export_pdf);
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        switch (ptr_csu_struct->config.decimal_place)
        {
        case 0 :
            sprintf(text_buffer,"%.0f",ptr_csu_struct->total_points[i]);
            break;
        case 1 :
            sprintf(text_buffer,"%.1f",ptr_csu_struct->total_points[i]);
            break;
        case 2 :
            sprintf(text_buffer,"%.2f",ptr_csu_struct->total_points[i]);
            break;
        case 3 :
            sprintf(text_buffer,"%.3f",ptr_csu_struct->total_points[i]);
            break;
        }
        pdfTextOutTable(page,ptr_export_pdf->pref.margin + (i+1)*table_width,y- ptr_export_pdf->table_line_height,text_buffer,table_width,ptr_csu_struct->rank[i],ptr_export_pdf);
    }

    // Print the ranking
    pdfTextOutTable(page,ptr_export_pdf->pref.margin,y-2* ptr_export_pdf->table_line_height,_("Ranking"),table_width,0,ptr_export_pdf);
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        sprintf(text_buffer,"%.0f",ptr_csu_struct->rank[i]);
        pdfTextOutTable(page,ptr_export_pdf->pref.margin + (i+1)*table_width,y-2* ptr_export_pdf->table_line_height,text_buffer,table_width,ptr_csu_struct->rank[i],ptr_export_pdf);
    }

    HPDF_Page_EndText(page);

    createPdfGrid(page,ptr_export_pdf->pref.margin,y+ ptr_export_pdf->table_line_height*2/3,width-ptr_export_pdf->pref.margin,y+ ptr_export_pdf->table_line_height*2/3-3* ptr_export_pdf->table_line_height, ptr_export_pdf->table_line_height,table_width);
}


/*!
 * \fn bool createOtherPagePdf(export_pdf *ptr_export_pdf, csuStruct *ptr_csu_struct)
 *  Create the other page of the pdf
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \param[in] ptr_export_pdf a pointer on a export_pdf
 * \return true if it need another page, false otherwise
 */
bool createOtherPagePdf(export_pdf *ptr_export_pdf, csuStruct *ptr_csu_struct)
{
    float height;
    float width;
    HPDF_Page page;
    char text_buffer[TEXT_BUFFER_SIZE]="";
    int i;
    float table_width;
    float text_pos_y;
    bool create_another_page = true;

    // Add a new page object.
    page = HPDF_AddPage(ptr_export_pdf->pdf);
    HPDF_Page_SetSize(page,ptr_export_pdf->pref.size,ptr_export_pdf->pref.direction);

    // Get the height and the width
    height = HPDF_Page_GetHeight (page);
    width = HPDF_Page_GetWidth (page);
    text_pos_y = height - ptr_export_pdf->pref.margin;

    // Prepare the page
    HPDF_Page_SetFontAndSize (page, ptr_export_pdf->font, ptr_export_pdf->pref.font_size);
    HPDF_Page_BeginText (page);

    // Calculate the table width
    table_width = ((width - 2*ptr_export_pdf->pref.margin)/(ptr_csu_struct->nb_player+1));

    // Names
    if (! ptr_export_pdf->total_points_ranking_print)
    {
        pdfTextOutTable(page,ptr_export_pdf->pref.margin,text_pos_y,_("Name"),table_width,0,ptr_export_pdf);
        for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
            pdfTextOutTable(page,ptr_export_pdf->pref.margin + (i+1)*table_width,text_pos_y,ptr_csu_struct->player_names[i],table_width,ptr_csu_struct->rank[i],ptr_export_pdf);
        text_pos_y -=  ptr_export_pdf->table_line_height;
    }

    // Points
    printPointsPdf(page,&text_pos_y,ptr_csu_struct,ptr_export_pdf,table_width);

    // Print the page number
    sprintf(text_buffer,_("Page %d"),ptr_export_pdf->num_page);
    (ptr_export_pdf->num_page) +=1;
    pdfTextOutTable(page,0,ptr_export_pdf->pref.margin*2/3,text_buffer,width,0,ptr_export_pdf);

    HPDF_Page_EndText(page);

    if (height - ptr_export_pdf->pref.margin != text_pos_y)
        createPdfGrid(page,ptr_export_pdf->pref.margin,height - ptr_export_pdf->pref.margin + ptr_export_pdf->table_line_height*2/3,width-ptr_export_pdf->pref.margin,text_pos_y+ ptr_export_pdf->table_line_height*2/3, ptr_export_pdf->table_line_height,table_width);

    if ((text_pos_y-3* ptr_export_pdf->table_line_height -ptr_export_pdf->pref.font_size  > ptr_export_pdf->pref.margin) && ptr_export_pdf->total_points_ranking_print == false)
    {
        addTotalPointsRankingPdf(page,ptr_csu_struct,text_pos_y- ptr_export_pdf->table_line_height,ptr_export_pdf);
        ptr_export_pdf->total_points_ranking_print = true;
        text_pos_y -= 3* ptr_export_pdf->table_line_height -ptr_export_pdf->pref.font_size;
    }
    create_another_page = addPodiumPdf(page,ptr_csu_struct,text_pos_y,ptr_export_pdf);


    return create_another_page;
}


bool addPodiumPdf(HPDF_Page page, csuStruct *ptr_csu_struct, float y,export_pdf *ptr_export_pdf)
{
    HPDF_Image podium = HPDF_LoadJpegImageFromFile(ptr_export_pdf->pdf,"Images/Podium.jpg");
    int podium_width = HPDF_Image_GetWidth(podium);
    int podium_height = HPDF_Image_GetHeight(podium);
    float page_width = HPDF_Page_GetWidth(page);

    if (podium_width > page_width - 2*ptr_export_pdf->pref.margin)
    {
        float ratio = (page_width - 2*ptr_export_pdf->pref.margin) / podium_width;
        podium_height *= ratio;
        podium_width *= ratio;
    }


    if (y - podium_height - ptr_export_pdf->table_line_height > ptr_export_pdf->pref.margin)
    {
        HPDF_Page_DrawImage(page,podium,(page_width - podium_width) / 2,y - podium_height - ptr_export_pdf->table_line_height,podium_width,podium_height);

        int nb;
        int index;
        HPDF_Page_SetFontAndSize (page, ptr_export_pdf->font, ptr_export_pdf->pref.font_size *2);
        HPDF_Page_BeginText (page);

        // First
        nb=1;
        index = searchIndexFromPosition(ptr_csu_struct,1,&nb);
        pdfTextOutTable(page,ptr_export_pdf->pref.margin,y-podium_height/4,ptr_csu_struct->player_names[index],page_width-2*ptr_export_pdf->pref.margin,1,ptr_export_pdf);

        // Second
        if (ptr_csu_struct->nb_player >= 2)
        {
            nb=1;
            index = searchIndexFromPosition(ptr_csu_struct,2,&nb);
            pdfTextOutTable(page,(page_width-podium_width)/2,y-podium_height/2,ptr_csu_struct->player_names[index],podium_width/3,2,ptr_export_pdf);
        }

        // Third
        if (ptr_csu_struct->nb_player >= 3)
        {
            nb=1;
            index = searchIndexFromPosition(ptr_csu_struct,3,&nb);
            pdfTextOutTable(page,(page_width-podium_width)/2 +2*podium_width/3,y-13*podium_height/20,ptr_csu_struct->player_names[index],podium_width/3,3,ptr_export_pdf);
        }

        HPDF_Page_EndText(page);
        return false;
    }
    else
        return true;
}


/*!
 * \fn bool exportToCsv(csuStruct *ptr_csu_struct, char *filename)
 *  Export the csu structure to a csv file
 * \param[in] ptr_csu_struct a pointer on a csuStruct
 * \param[in] filename the filename of the pdf file
 * \return true if everything is OK, false otherwise
 */
bool exportToCsv(csuStruct *ptr_csu_struct, char *filename)
{
    FILE *ptr_file;
    int i,j;

    ptr_file = openFile(filename,"w");
    if (ptr_file == NULL)
        return false;

    // Print the header
    fprintf(ptr_file,_("Csu file;\nCreated on the;%02.0f/%02.0f/%4.0f;\nFile's version;%1.1f;\nMaximum size of the names;%.0f;"
                       "\nNumber of players;%.0f;\nMaximum number of turns;%d;\n")
            ,ptr_csu_struct->day,ptr_csu_struct->month,ptr_csu_struct->year,ptr_csu_struct->version,ptr_csu_struct->size_max_name
            ,ptr_csu_struct->nb_player,maxNbTurn(ptr_csu_struct)-1);

    // Print the game configuration
    char *yes=_("yes");
    char *no=_("no");
    fprintf(ptr_file,_("Name of the game configuration;%s;\nUse of a maximum score;%s;\nInitial score;%.3f;\n"
                       "Number of decimals displayed;%d;\nThe first has the highest score;%s;\n"
                       "Turn-based game;%s;\nUse of a distributor;%s;\n")
            ,ptr_csu_struct->config.name,integerToYesNo(ptr_csu_struct->config.max,yes,no),ptr_csu_struct->config.begin_score,
            ptr_csu_struct->config.decimal_place,integerToYesNo(ptr_csu_struct->config.first_way,yes,no),
            integerToYesNo(ptr_csu_struct->config.turn_based,yes,no),integerToYesNo(ptr_csu_struct->config.use_distributor,yes,no));
    #ifdef __unix__
    fprintf(ptr_file,_("Maximum/minimum number of points;%.3f;\n"),ptr_csu_struct->config.nb_max);
    #elif _WIN32
    if (ptr_csu_struct->config.nb_max == INFINITY)
        fprintf(ptr_file,_("Maximum/minimum number of points;inf;\n"));
    else
        fprintf(ptr_file,_("Maximum/minimum number of points;%.3f;\n"),ptr_csu_struct->config.nb_max);
    #endif

    // Names
    fprintf(ptr_file,_("\nNames"));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        fprintf(ptr_file,_(";%s;"),ptr_csu_struct->player_names[i]);

    //Legend
    fprintf(ptr_file,_("\nLegend;"));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        fprintf(ptr_file,_("Points in the turn;Points;"));

    // Points
    for (i=0 ; i<maxNbTurn(ptr_csu_struct) ; i++)
    {
        fprintf(ptr_file,_("\nTurn %d;"),i);

        for (j=0 ; j<ptr_csu_struct->nb_player ; j++)
        {
            if (ptr_csu_struct->nb_turn[j] >= i+1)
                fprintf(ptr_file,"%f;%f;",ptr_csu_struct->point[j][i],pointsAtTurn(ptr_csu_struct,j,i));
            else
                fprintf(ptr_file,";;");
        }
    }

    // Names
    fprintf(ptr_file,_("\n\nNames;"));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        fprintf(ptr_file,_(";%s;"),ptr_csu_struct->player_names[i]);

    // Total points
    fprintf(ptr_file,_("\nTotal points;"));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        fprintf(ptr_file,_(";%f;"),ptr_csu_struct->total_points[i]);

    // Ranking
    fprintf(ptr_file,_("\nRanking;"));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        fprintf(ptr_file,_(";%.0f;"),ptr_csu_struct->rank[i]);

    closeFile(ptr_file);

    return true;
}
