/*!
 * \file    pdf_exportation.cpp
 * \brief   Exceptions of Csuper
 * \author  Remi BERTHO
 * \date    12/06/14
 * \version 4.3.0
 */

/*
* pdf_exportation.cpp
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

#include "pdf_exportation.h"
#include "config.h"
#include "exceptions.h"
#include "glibmm.h"
#include "share.h"
#include <iostream>
#include <glibmm/datetime.h>

using namespace Glib;
using namespace std;

namespace csuper
{
    //
    // Constructor
    //
    PdfExportation::PdfExportation(const Game* game,  const ExportPdfPreferences& pref) :
        line_(0), num_page_(2), line_height_(pref.fontSize()),
        table_line_height_(1.8*pref.fontSize()), pref_(pref),
        total_points_ranking_print_(false), stat_print_(false), game_(game)
    {
        pdf_ = HPDF_New(errorHandler,NULL);

        if (!(game->config().turnBased()))
            pref_.setRanking(false);

        // Initialize the font
        if (pref_.charset() == ExportPdfPreferences::UTF8)
        {
            #if HPDF_MAJOR_VERSION == 2 && HPDF_MINOR_VERSION < 3
            font_ = HPDF_GetFont(pdf_,"Times-Roman", "ISO8859-15");
            #else
            HPDF_UseUTFEncodings(pdf_);
            ustring font_name;
            try
            {
                font_name = HPDF_LoadTTFontFromFile(pdf_,"Fonts/DejaVuSans.ttf", HPDF_TRUE);
            }
            catch (PdfError& e)
            {
                HPDF_Free(pdf_);
                cerr << e.what() << endl;
                throw PdfError(_("The font doesn't exist"));
            }
            font_ = HPDF_GetFont(pdf_,font_name.c_str(), "UTF-8");
            #endif // HPDF_MAJOR_VERSION
        }
        else
            font_ = HPDF_GetFont(pdf_,"Times-Roman", "ISO8859-15");

        // Set the attribute of the pdf
        HPDF_SetInfoAttr(pdf_,HPDF_INFO_AUTHOR,get_user_name().c_str());
        HPDF_SetInfoAttr(pdf_,HPDF_INFO_CREATOR,"Csuper");
        HPDF_SetCompressionMode(pdf_,HPDF_COMP_ALL);
        DateTime gdate = DateTime::create_now_local();
        HPDF_Date date = {gdate.get_year(),gdate.get_month(),gdate.get_day_of_month(),
            gdate.get_hour(),gdate.get_minute(),gdate.get_second(),'+',0,0};
        HPDF_SetInfoDateAttr(pdf_,HPDF_INFO_CREATION_DATE,date);
        HPDF_SetInfoDateAttr(pdf_,HPDF_INFO_MOD_DATE,date);
    }


    //
    // Destuctor
    //
    PdfExportation::~PdfExportation()
    {
        HPDF_Free(pdf_);
    }



    //
    // Create page
    //
    bool PdfExportation::createFirstPage(const Glib::ustring& filename)
    {
        float height;
        float width;
        HPDF_Page first_page;
        ustring simple_filename;
        ustring text_buffer;
        float table_width;
        float text_pos_y;
        bool create_another_page = true;

        // Add a new page object.
        first_page = HPDF_AddPage(pdf_);
        HPDF_Page_SetSize(first_page,static_cast<HPDF_PageSizes>(pref_.size()),static_cast<HPDF_PageDirection>(pref_.direction()));

        // Get the heoght and the width
        height = HPDF_Page_GetHeight(first_page);
        width = HPDF_Page_GetWidth(first_page);

        // Print the filename
        HPDF_Page_SetFontAndSize (first_page,font_, 2*pref_.fontSize());
        simple_filename = path_get_basename(filename);
        removeFileExtension(simple_filename);
        HPDF_Page_BeginText(first_page);
        textOutTable(first_page,0,height - pref_.margin()*2/3 - line_height_,simple_filename,width,0);
        HPDF_Page_EndText(first_page);
        HPDF_SetInfoAttr(pdf_,HPDF_INFO_TITLE,convertCharsetPdf(simple_filename,pref_.charset()).c_str());


        // Print the header
        HPDF_Page_SetFontAndSize(first_page,font_, pref_.fontSize());
        HPDF_Page_BeginText(first_page);
        HPDF_Page_MoveTextPos(first_page, pref_.margin(), height - pref_.margin() - pref_.fontSize()*2);

        // File creation
        text_buffer = ustring::compose(_("File created on the %1"),game_->dateUstring());
        showText (first_page, text_buffer);

        // Number of player
        HPDF_Page_MoveTextPos(first_page, 0, -line_height_);
        text_buffer = ustring::compose(_("Number of players: %1"),game_->nbPlayerUstring());
        showText(first_page, text_buffer);

        // Maximum number of turn
        HPDF_Page_MoveTextPos (first_page, 0, -line_height_);
        text_buffer = ustring::compose(_("Maximum number of turns: %1"),game_->maxNbTurn());
        showText (first_page, text_buffer);

        // Name of the game configuration
        HPDF_Page_MoveTextPos (first_page, 0, -line_height_);
        text_buffer = ustring::compose(_("Name of the game configuration: %1"),game_->config().nameUstring());
        showText(first_page, text_buffer);
        HPDF_Page_EndText(first_page);


        // Calculate the table width and the text position
        table_width = tableWidthCalculate(first_page);
        text_pos_y = height - pref_.margin() - 7*line_height_;


        // Names, legend, ponts
        printNames(text_pos_y,table_width,first_page);
        printLegend(text_pos_y,table_width,first_page);
        printPoints(text_pos_y,table_width,first_page);
        createGrid(first_page,pref_.margin(),height - pref_.margin() - 7*line_height_ - table_line_height_*1/3,
                  width-pref_.margin(),text_pos_y+table_line_height_*2/3,table_line_height_,table_width);

        // Page number
        HPDF_Page_BeginText(first_page);
        textOutTable(first_page,0,pref_.margin()*2/3,_("Page 1"),width);
        HPDF_Page_EndText (first_page);


        if ((text_pos_y - 3*table_line_height_ - pref_.fontSize()) > pref_.margin())
        {
            text_pos_y -= table_line_height_;
            addTotalPointsRanking(first_page,text_pos_y);
            total_points_ranking_print_ = true;

            if ((text_pos_y - 7* table_line_height_ - pref_.fontSize())  > pref_.margin())
            {
                text_pos_y -= table_line_height_;
                addStats(first_page,text_pos_y);
                stat_print_ = true;
                create_another_page = addPodium(first_page,text_pos_y);
            }
        }

        return create_another_page;
    }


    bool PdfExportation::createOtherPage()
    {
        float height;
        float width;
        HPDF_Page page;
        ustring text_buffer;
        float table_width;
        float text_pos_y;

        // Add a new page object.
        page = HPDF_AddPage(pdf_);
        HPDF_Page_SetSize(page,static_cast<HPDF_PageSizes>(pref_.size()),static_cast<HPDF_PageDirection>(pref_.direction()));

        // Get the height and the width
        height = HPDF_Page_GetHeight (page);
        width = HPDF_Page_GetWidth (page);
        text_pos_y = height - pref_.margin() - line_height_*2/3;

        // Prepare the page
        HPDF_Page_SetFontAndSize(page, font_, pref_.fontSize());

        // Calculate the table width
        table_width = tableWidthCalculate(page);

        // Names and legend
        if ((! total_points_ranking_print_) && (line_ < game_->maxNbTurn()))
        {
            printNames(text_pos_y,table_width,page);
            printLegend(text_pos_y,table_width,page);
        }

        // Points
        printPoints(text_pos_y,table_width,page);

        // Print the page number
        HPDF_Page_BeginText(page);
        text_buffer = ustring::compose(_("Page %1"),num_page_);
        num_page_++;
        textOutTable(page,0,pref_.margin()*2/3,text_buffer,width);

        HPDF_Page_EndText(page);

        // Grid
        if (height - pref_.margin() - line_height_*2/3 != text_pos_y)
        {
            createGrid(page,pref_.margin(),height - pref_.margin() - table_line_height_*0.7,
                       width - pref_.margin(),text_pos_y + table_line_height_*2/3,
                       table_line_height_,table_width);
            text_pos_y -= table_line_height_;
        }

        // Total points ranking
        if (((text_pos_y - 3* table_line_height_ - pref_.fontSize()) > pref_.margin()) && total_points_ranking_print_ == false)
        {
            addTotalPointsRanking(page,text_pos_y);
            total_points_ranking_print_ = true;
            text_pos_y -= table_line_height_;
        }

        // Stats
        if (((text_pos_y - 7* table_line_height_ - pref_.fontSize())  > pref_.margin()) && stat_print_ == false)
        {
            addStats(page,text_pos_y);
            stat_print_ = true;
        }

        return addPodium(page,text_pos_y);
    }



    //
    // Print elements
    //
    void PdfExportation::printNames(float& pos_y, const float table_width, HPDF_Page& page)
    {
        unsigned int i;
        float width = HPDF_Page_GetWidth(page);
        unsigned int nb_column_per_player;

        HPDF_Page_BeginText(page);
        textOutTable(page,pref_.margin(),pos_y,_("Name"),table_width);

        if (pref_.totalPoints() && pref_.ranking())
            nb_column_per_player = 3;
        else if (pref_.totalPoints() || pref_.ranking())
            nb_column_per_player = 2;
        else
            nb_column_per_player=1;

        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(page,pref_.margin() + (nb_column_per_player*i+1)*table_width,pos_y,
                game_->playerName(i),table_width*nb_column_per_player,game_->ranking(i));
        }
        HPDF_Page_EndText(page);

        createGrid(page,pref_.margin(),pos_y + table_line_height_*2/3,
            pref_.margin() + table_width,pos_y - table_line_height_*1/3,
            table_line_height_,table_width);

        createGrid(page,pref_.margin() + table_width,pos_y + table_line_height_*2/3,
            width - pref_.margin(),pos_y - table_line_height_*1/3,
            table_line_height_,nb_column_per_player*table_width);


        pos_y = pos_y - table_line_height_;
    }

    void PdfExportation::printLegend(float& pos_y, const float table_width, HPDF_Page& page)
    {
        unsigned int i;

        //Test if it need a legend
        if (pref_.totalPoints() || pref_.ranking())
        {
            HPDF_Page_BeginText(page);
            textOutTable(page,pref_.margin(),pos_y,_("Legend"),table_width);

            // If that need total points and ranking
            if (pref_.totalPoints() && pref_.ranking())
            {
                for (i=0 ; i<game_->nbPlayer() ; i++)
                {
                    textOutTable(page,pref_.margin() + (3*i+1)*table_width,pos_y,
                        _("Points"),table_width,game_->ranking(i));
                    textOutTable(page,pref_.margin() + (3*i+2)*table_width,pos_y,
                        _("Total"),table_width,game_->ranking(i));
                    textOutTable(page,pref_.margin() + (3*i+3)*table_width,pos_y,
                        _("Ranking"),table_width,game_->ranking(i));
                }
            } else
            // If it need only the total points
            if (pref_.totalPoints())
            {
                for (i=0 ; i<game_->nbPlayer() ; i++)
                {
                    textOutTable(page,pref_.margin() + (2*i+1)*table_width,pos_y,
                        _("Points"),table_width,game_->ranking(i));
                    textOutTable(page,pref_.margin() + 2*(i+1)*table_width,pos_y,
                        _("Total"),table_width,game_->ranking(i));
                }
            }
            else
            // If it need only the ranking
            {
                for (i=0 ; i<game_->nbPlayer() ; i++)
                {
                    textOutTable(page,pref_.margin() + (2*i+1)*table_width,pos_y,
                        _("Points"),table_width,game_->ranking(i));
                    textOutTable(page,pref_.margin() + 2*(i+1)*table_width,pos_y,
                        _("Ranking"),table_width,game_->ranking(i));
                }
            }

            HPDF_Page_EndText(page);
            pos_y = pos_y - table_line_height_;
        }
    }


    void PdfExportation::printPoints(float& pos_y, const float table_width, HPDF_Page& page)
    {
        ustring text_buffer;
        unsigned int i;

        HPDF_Page_BeginText(page);

        while ((pos_y > pref_.margin() + pref_.fontSize() ) && (line_ < game_->maxNbTurn()))
        {
            text_buffer = ustring::compose(_("Turn %1"),line_);
            textOutTable(page,pref_.margin(),pos_y,text_buffer,table_width,0);

            // For each turn
            for (i=0 ; i<game_->nbPlayer() ; i++)
            {
                // Test if the player has points in this turn
                if (game_->hasTurn(i,line_))
                {
                    text_buffer = game_->pointsUstring(i,line_);
                    // If the total points and the ranking needs to be display
                    if (pref_.totalPoints() && pref_.ranking())
                    {
                        textOutTable(page,pref_.margin() + (3*i+1)*table_width,pos_y,text_buffer,table_width,game_->ranking(i));
                        text_buffer = game_->totalPointsUstring(i,line_);
                        textOutTable(page,pref_.margin() + (3*i+2)*table_width,pos_y,text_buffer,table_width,game_->ranking(i));
                        text_buffer = game_->rankingUstring(i,line_);
                        textOutTable(page,pref_.margin() + (3*i+3)*table_width,pos_y,text_buffer,table_width,game_->ranking(i));
                    } else
                    // If the total points needs to be display
                    if (pref_.totalPoints())
                    {
                        textOutTable(page,pref_.margin() + (2*i+1)*table_width,pos_y,text_buffer,table_width,game_->ranking(i));
                        text_buffer = game_->totalPointsUstring(i,line_);
                        textOutTable(page,pref_.margin() + 2*(i+1)*table_width,pos_y,text_buffer,table_width,game_->ranking(i));
                    }else
                    // If the ranking needs to be display
                    if (pref_.ranking())
                    {
                        textOutTable(page,pref_.margin() + (2*i+1)*table_width,pos_y,text_buffer,table_width,game_->ranking(i));
                        text_buffer = game_->rankingUstring(i,line_);
                        textOutTable(page,pref_.margin() + 2*(i+1)*table_width,pos_y,text_buffer,table_width,game_->ranking(i));
                    }
                    else
                        textOutTable(page,pref_.margin() + (i+1)*table_width,pos_y,text_buffer,table_width,game_->ranking(i));
                }
            }

            line_ ++;
            pos_y -= table_line_height_;
        }
        HPDF_Page_EndText(page);
    }

    void PdfExportation::addTotalPointsRanking(HPDF_Page& page, float& y)
    {
        ustring text_buffer;
        unsigned int i;
        float width = HPDF_Page_GetWidth(page);

        float table_width = ((width - 2*pref_.margin())/(game_->nbPlayer()+1));

        HPDF_Page_BeginText(page);

        // Names
        textOutTable(page,pref_.margin(),y,_("Name"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
            textOutTable(page,pref_.margin() + (i+1)*table_width,y,game_->playerNameUstring(i),table_width,game_->ranking(i));

        // Print the finals points
        textOutTable(page,pref_.margin(),y- table_line_height_,_("Total points"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(page,pref_.margin() + (i+1)*table_width,y- table_line_height_,
                         game_->totalPointsUstring(i),table_width,game_->ranking(i));
        }

        // Print the ranking
        textOutTable(page,pref_.margin(),y-2* table_line_height_,_("Ranking"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(page,pref_.margin() + (i+1)*table_width,y- 2*table_line_height_,
                         game_->rankingUstring(i),table_width,game_->ranking(i));
        }

        HPDF_Page_EndText(page);

        createGrid(page,pref_.margin(),y+ table_line_height_*2/3,width-pref_.margin(),
                   y - table_line_height_*7/3, table_line_height_,table_width);

        y = y - 3*table_line_height_;
    }

    void PdfExportation::addStats(HPDF_Page& page, float& y)
    {
        ustring text_buffer;
        unsigned int i;
        float width = HPDF_Page_GetWidth(page);

        float table_width = ((width - 2*pref_.margin())/(game_->nbPlayer()+1));

        HPDF_Page_BeginText(page);

        // Names
        textOutTable(page,pref_.margin(),y,_("Name"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(page,pref_.margin() + (i+1)*table_width,y,
                         game_->playerNameUstring(i),table_width,game_->ranking(i));
        }

        // Nb turn
        y -= table_line_height_;
        textOutTable(page,pref_.margin(),y,_("Nb turn"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(page,pref_.margin() + (i+1)*table_width,y,
                            game_->nbTurnUstring(i),table_width,game_->ranking(i));
        }

        // Mean
        y -= table_line_height_;
        textOutTable(page,pref_.margin(),y,_("Mean points"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(page,pref_.margin() + (i+1)*table_width,y,
                            game_->meanPointsUstring(i),table_width,game_->ranking(i));
        }

        if (game_->config().turnBased())
        {
            // Nb turn best
            y -= table_line_height_;
            textOutTable(page,pref_.margin(),y,_("Nb turn best"),table_width);
            for (i=0 ; i<game_->nbPlayer() ; i++)
            {
                textOutTable(page,pref_.margin() + (i+1)*table_width,y,
                                game_->nbTurnBestUstring(i),table_width,game_->ranking(i));
            }

            // Nb turn worst
            y -= table_line_height_;
            textOutTable(page,pref_.margin(),y,_("Nb turn worst"),table_width);
            for (i=0 ; i<game_->nbPlayer() ; i++)
            {
                textOutTable(page,pref_.margin() + (i+1)*table_width,y,
                                game_->nbTurnWorstUstring(i),table_width,game_->ranking(i));
            }

            // Nb turn first
            y -= table_line_height_;
            textOutTable(page,pref_.margin(),y,_("Nb turn first"),table_width);
            for (i=0 ; i<game_->nbPlayer() ; i++)
            {
                textOutTable(page,pref_.margin() + (i+1)*table_width,y,
                                game_->nbTurnFirstUstring(i),table_width,game_->ranking(i));
            }

            // Nb turn last
            y -= table_line_height_;
            textOutTable(page,pref_.margin(),y,_("Nb turn last"),table_width);
            for (i=0 ; i<game_->nbPlayer() ; i++)
            {
                textOutTable(page,pref_.margin() + (i+1)*table_width,y,
                                game_->nbTurnLastUstring(i),table_width,game_->ranking(i));
            }

            HPDF_Page_EndText(page);

            createGrid(page,
                      pref_.margin(),
                      y + table_line_height_*20/3,
                      width - pref_.margin(),
                      y - table_line_height_*1/3,
                      table_line_height_,
                      table_width);
        }
        else
        {
            HPDF_Page_EndText(page);

            createGrid(page,
                      pref_.margin(),
                      y + table_line_height_*8/3,
                      width - pref_.margin(),
                      y - table_line_height_*1/3,
                      table_line_height_,
                      table_width);
        }
    }

    bool PdfExportation::addPodium(HPDF_Page& page, const float y)
    {
        HPDF_Image podium = HPDF_LoadJpegImageFromFile(pdf_,"Images/Podium.jpg");
        int podium_width = HPDF_Image_GetWidth(podium);
        int podium_height = HPDF_Image_GetHeight(podium);
        float page_width = HPDF_Page_GetWidth(page);

        if (podium_width > page_width - 2*pref_.margin())
        {
            float ratio = (page_width - 2 * pref_.margin()) / podium_width;
            podium_height *= ratio;
            podium_width *= ratio;
        }


        if (y - podium_height - table_line_height_ > pref_.margin())
        {
            HPDF_Page_DrawImage(page,podium,(page_width - podium_width) / 2,
                                y - podium_height - table_line_height_,podium_width,podium_height);

            vector<unsigned int> index = game_->playerIndexFromPosition();

            HPDF_Page_SetFontAndSize(page, font_, pref_.fontSize() * 2);
            HPDF_Page_BeginText(page);

            // First
            textOutTable(page,pref_.margin(),y-podium_height/4,game_->playerNameUstring(index[0]),
                            page_width-2*pref_.margin(),1);

            // Second
            if (game_->nbPlayer() >= 2)
            {
                textOutTable(page,(page_width-podium_width)/2,y-podium_height/2,
                             game_->playerNameUstring(index[1]),podium_width/3,2);
            }

            // Third
            if (game_->nbPlayer() >= 3)
            {
                textOutTable(page,(page_width-podium_width)/2 +2*podium_width/3,
                             y-13*podium_height/20,game_->playerNameUstring(index[2]),podium_width/3,3);
            }

            HPDF_Page_EndText(page);
            return false;
        }
        else
            return true;
    }


    //
    // Print function
    //
    void PdfExportation::showText(HPDF_Page& page, const Glib::ustring& text)
    {
        HPDF_Page_ShowText(page,convertCharsetPdf(text,pref_.charset()).c_str());
    }

    void PdfExportation::textOutTable(HPDF_Page& page, const float pos_min_x, const float pos_y, const Glib::ustring& text, const float max_width, const int ranking)
    {
        float text_width;
        unsigned int nb_char;
        ustring text_buffer;

        text_buffer = convertCharsetPdf(text,pref_.charset());

        text_width = HPDF_Page_TextWidth(page, text_buffer.c_str());
        if (text_buffer.validate())
            nb_char = text_buffer.length();
        else
            nb_char = strlen(text_buffer.c_str());

        // Reduce the length of the text if needed
        while (text_width > max_width && nb_char > 1)
        {
            nb_char--;
            if (text_buffer.validate())
                text_buffer.resize(nb_char);
            else
            {
                string tmp_str = string(text_buffer);
                tmp_str.resize(nb_char);
                text_buffer = tmp_str;
            }
            text_width = HPDF_Page_TextWidth(page, text_buffer.c_str());
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
        HPDF_Page_TextOut (page, (max_width - text_width) / 2 + pos_min_x,pos_y, text_buffer.c_str());

        // Reset the color
        HPDF_Page_SetRGBFill(page,0,0,0);
    }


    float PdfExportation::tableWidthCalculate(HPDF_Page& page)
    {
        float width = HPDF_Page_GetWidth (page);

        if (pref_.totalPoints() && pref_.ranking())
            return ((width - 2*pref_.margin())/(3*(game_->nbPlayer())+1));
        else if (pref_.totalPoints() || pref_.ranking())
            return ((width - 2*pref_.margin())/(2*(game_->nbPlayer())+1));
        else
            return ((width - 2*pref_.margin())/(game_->nbPlayer()+1));
    }

    void PdfExportation::createGrid(HPDF_Page& page,const float top_x, const float top_y, const float bottom_x, const float bottom_y,
                           const float length_row, const float length_column)
    {
        float x,y;

        HPDF_Page_SetLineWidth(page, 1);

        // Vertical grid;
        for (y = top_y ; y >= bottom_y - 1 ; y -= length_row)
        {
            HPDF_Page_MoveTo(page,top_x,y);
            HPDF_Page_LineTo(page,bottom_x,y);
            HPDF_Page_Stroke(page);
        }

        // Horizontal grid;
        for (x = top_x ; x <= bottom_x + 1; x += length_column)
        {
            HPDF_Page_MoveTo(page,x,top_y);
            HPDF_Page_LineTo(page,x,bottom_y);
            HPDF_Page_Stroke(page);
        }
    }



    //
    // Static function
    //
    void PdfExportation::errorHandler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
    {
        //printf ("ERROR: error_no=%04X, detail_no=%d\n",(unsigned int) error_no, (int) detail_no);
        throw PdfError(ustring::compose("libharu: error_no=%1, detail_no=%2",ustring::format(hex,(unsigned int) error_no), (int) detail_no));
    }

    bool PdfExportation::canUseUtf8()
    {
        #if HPDF_MAJOR_VERSION == 2 && HPDF_MINOR_VERSION < 3
        return false;
        #else
        return true;
        #endif // HPDF_MAJOR_VERSION
    }



    string PdfExportation::convertCharsetPdf(const Glib::ustring& str, const ExportPdfPreferences::CharacterSet charset)
    {
        if (charset == ExportPdfPreferences::UTF8)
        {
            #if HPDF_MAJOR_VERSION == 2 && HPDF_MINOR_VERSION < 3
            try
            {
                return convert(str,"ISO8859-15","UTF-8");
            }
            catch (ConvertError& e)
            {
                cerr << e.what() << endl;
                throw PdfError(_("Conversion from UTF-8 to ISO8859-15 failed"));
            }
            #else
            return str;
            #endif // HPDF_MAJOR_VERSION
        }
        else
        {
            try
            {
                return convert(str,"ISO8859-15","UTF-8");
            }
            catch (ConvertError& e)
            {
                cerr << e.what() << endl;
                throw PdfError(_("Conversion from UTF-8 to ISO8859-15 failed"));
            }
        }
    }

    void PdfExportation::exportToPdf(const Game* game, const ExportPdfPreferences& pref, const Glib::ustring& filename)
    {
        PdfExportation* pdf = new PdfExportation(game,pref);

        try
        {
            if(pdf->createFirstPage(filename))
                while(pdf->createOtherPage());
        }
        catch (PdfError& e)
        {
            delete pdf;
            cerr << e.what() << endl;
            throw PdfError(_("The PDF table cannot be created"));
        }

        try
        {
            HPDF_SaveToFile(pdf->pdf_,locale_from_utf8(filename).c_str());
        }
        catch (PdfError& e)
        {
            delete pdf;
            cerr << e.what() << endl;
            throw PdfError(_("The PDF table cannot be save"));
        }
        delete pdf;
    }

}
