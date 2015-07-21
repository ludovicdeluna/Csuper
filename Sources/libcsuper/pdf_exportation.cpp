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
using namespace PoDoFo;

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
        pdf_ = new PdfMemDocument();
        painter_ = new PdfPainter();

        if (!(game->config().turnBased()))
            pref_.setRanking(false);

        const PdfEncoding* encoding;
        #if canUseUtf8
        if (pref.charset() == ExportPdfPreferences::UTF8)
            encoding = PdfEncodingFactory::GlobalIdentityEncodingInstance();
        else
        #endif
            encoding = PdfEncodingFactory::GlobalWinAnsiEncodingInstance();
        #if canUseUtf8
        font_ = pdf_->CreateFont(pref.fontName().c_str(),false,encoding,PdfFontCache::eFontCreationFlags_AutoSelectBase14 ,pref.embeddedFont());
        #else
        font_ = pdf_->CreateFont(pref.fontName().c_str(),encoding,PdfFontCache::eFontCreationFlags_AutoSelectBase14 ,pref.embeddedFont());
        #endif
        if( !font_ )
		{
			PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
		}

        PdfInfo* info = pdf_->GetInfo();

        info->SetAuthor(get_user_name());
        info->SetCreator("Csuper");
        info->SetProducer("PoDoFo");
    }


    //
    // Destuctor
    //
    PdfExportation::~PdfExportation()
    {
        delete pdf_;
        delete painter_;
    }



    //
    // Create page
    //
    bool PdfExportation::createFirstPage(const Glib::ustring& filename)
    {
        PdfPage* first_page;
        ustring simple_filename;
        ustring text_buffer;
        double text_pos_y;
        bool create_another_page = true;

        // Add a new page object.
        EPdfPageSize page_size;
        switch(pref_.size())
        {
        case ExportPdfPreferences::A3:
            page_size = ePdfPageSize_A3;
            break;
        case ExportPdfPreferences::A4:
            page_size = ePdfPageSize_A4;
            break;
        case ExportPdfPreferences::A5:
            page_size = ePdfPageSize_A5;
            break;
        }
        bool landscape=false;
        if (pref_.direction() == ExportPdfPreferences::LANDSCAPE)
            landscape = true;
        first_page = pdf_->CreatePage(PdfPage::CreateStandardPageSize(page_size,landscape));
        painter_->SetPage(first_page);
        painter_->SetFont(font_);

        // Get the height and the width
        height_ = first_page->GetPageSize().GetHeight();
        width_ = first_page->GetPageSize().GetWidth();

        // Print the filename
        font_->SetFontSize(2*pref_.fontSize());
        simple_filename = path_get_basename(filename);
        removeFileExtension(simple_filename);
        textOutTable(0,height_ - pref_.margin()*2/3 - line_height_,simple_filename,width_);
        pdf_->GetInfo()->SetTitle(ustringToPdfstring(simple_filename));


        // Print the header
        font_->SetFontSize(pref_.fontSize());
        painter_->BeginText(pref_.margin(), height_ - pref_.margin() - pref_.fontSize()*2);

        // File creation
        text_buffer = ustring::compose(_("File created on the %1"),game_->dateUstring());
        showText(text_buffer);

        // Number of player
        painter_->MoveTextPos(0, -line_height_);
        text_buffer = ustring::compose(_("Number of players: %1"),game_->nbPlayerUstring());
        showText(text_buffer);

        // Maximum number of turn
        painter_->MoveTextPos(0, -line_height_);
        text_buffer = ustring::compose(_("Maximum number of turns: %1"),game_->maxNbTurn());
        showText(text_buffer);

        // Name of the game configuration
        painter_->MoveTextPos(0, -line_height_);
        text_buffer = ustring::compose(_("Name of the game configuration: %1"),game_->config().nameUstring());
        showText(text_buffer);
        painter_->EndText();


        // Calculate the table width and the text position
        tableWidthCalculate();
        text_pos_y = height_ - pref_.margin() - 7*line_height_;


        // Names, legend, ponts
        printNames(text_pos_y);
        printLegend(text_pos_y);
        printPoints(text_pos_y);
        createGrid(pref_.margin(),height_ - pref_.margin() - 7*line_height_ - table_line_height_*1/3,
                  width_-pref_.margin(),text_pos_y+table_line_height_*2/3,table_line_height_,table_width_);

        // Page number
        textOutTable(0,pref_.margin()*2/3,_("Page 1"),width_);


        if ((text_pos_y - 3*table_line_height_ - pref_.fontSize()) > pref_.margin())
        {
            text_pos_y -= table_line_height_;
            addTotalPointsRanking(text_pos_y);
            total_points_ranking_print_ = true;

            if ((text_pos_y - 7* table_line_height_ - pref_.fontSize())  > pref_.margin())
            {
                text_pos_y -= table_line_height_;
                addStats(text_pos_y);
                stat_print_ = true;
                create_another_page = addPodium(text_pos_y);
            }
        }

        painter_->FinishPage();

        return create_another_page;
    }


    bool PdfExportation::createOtherPage()
    {
        PdfPage* page;
        ustring text_buffer;
        double text_pos_y;
        bool create_another_page;

        // Add a new page object.
        EPdfPageSize page_size;
        switch(pref_.size())
        {
        case ExportPdfPreferences::A3:
            page_size = ePdfPageSize_A3;
            break;
        case ExportPdfPreferences::A4:
            page_size = ePdfPageSize_A4;
            break;
        case ExportPdfPreferences::A5:
            page_size = ePdfPageSize_A5;
            break;
        }
        bool landscape=false;
        if (pref_.direction() == ExportPdfPreferences::LANDSCAPE)
            landscape = true;
        page = pdf_->CreatePage(PdfPage::CreateStandardPageSize(page_size,landscape));
        painter_->SetPage(page);
        painter_->SetFont(font_);

        text_pos_y = height_ - pref_.margin() - line_height_*2/3;
        font_->SetFontSize(pref_.fontSize());

        // Names and legend
        if ((! total_points_ranking_print_) && (line_ < game_->maxNbTurn()))
        {
            printNames(text_pos_y);
            printLegend(text_pos_y);
        }

        // Points
        printPoints(text_pos_y);

        // Print the page number
        text_buffer = ustring::compose(_("Page %1"),num_page_);
        num_page_++;
        textOutTable(0,pref_.margin()*2/3,text_buffer,width_);

        // Grid
        if (height_ - pref_.margin() - line_height_*2/3 != text_pos_y)
        {
            createGrid(pref_.margin(),height_ - pref_.margin() - table_line_height_*0.7,
                       width_ - pref_.margin(),text_pos_y + table_line_height_*2/3,
                       table_line_height_,table_width_);
            text_pos_y -= table_line_height_;
        }

        // Total points ranking
        if (((text_pos_y - 3* table_line_height_ - pref_.fontSize()) > pref_.margin()) && total_points_ranking_print_ == false)
        {
            addTotalPointsRanking(text_pos_y);
            total_points_ranking_print_ = true;
            text_pos_y -= table_line_height_;
        }

        // Stats
        if (((text_pos_y - 7* table_line_height_ - pref_.fontSize())  > pref_.margin()) && stat_print_ == false)
        {
            addStats(text_pos_y);
            stat_print_ = true;
        }

        create_another_page = addPodium(text_pos_y);

        painter_->FinishPage();

        return create_another_page;
    }



    //
    // Print elements
    //
    void PdfExportation::printNames(double& pos_y)
    {
        unsigned int i;
        unsigned int nb_column_per_player;

        textOutTable(pref_.margin(),pos_y,_("Name"),table_width_);

        if (pref_.totalPoints() && pref_.ranking())
            nb_column_per_player = 3;
        else if (pref_.totalPoints() || pref_.ranking())
            nb_column_per_player = 2;
        else
            nb_column_per_player=1;

        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(pref_.margin() + (nb_column_per_player*i+1)*table_width_,pos_y,
                game_->playerName(i),table_width_*nb_column_per_player,game_->ranking(i));
        }

        createGrid(pref_.margin(),pos_y + table_line_height_*2/3,
            pref_.margin() + table_width_,pos_y - table_line_height_*1/3,
            table_line_height_,table_width_);

        createGrid(pref_.margin() + table_width_,pos_y + table_line_height_*2/3,
            width_ - pref_.margin(),pos_y - table_line_height_*1/3,
            table_line_height_,nb_column_per_player*table_width_);


        pos_y = pos_y - table_line_height_;
    }

    void PdfExportation::printLegend(double& pos_y)
    {
        unsigned int i;

        //Test if it need a legend
        if (pref_.totalPoints() || pref_.ranking())
        {
            textOutTable(pref_.margin(),pos_y,_("Legend"),table_width_);

            // If that need total points and ranking
            if (pref_.totalPoints() && pref_.ranking())
            {
                for (i=0 ; i<game_->nbPlayer() ; i++)
                {
                    textOutTable(pref_.margin() + (3*i+1)*table_width_,pos_y,
                        _("Points"),table_width_,game_->ranking(i));
                    textOutTable(pref_.margin() + (3*i+2)*table_width_,pos_y,
                        _("Total"),table_width_,game_->ranking(i));
                    textOutTable(pref_.margin() + (3*i+3)*table_width_,pos_y,
                        _("Ranking"),table_width_,game_->ranking(i));
                }
            } else
            // If it need only the total points
            if (pref_.totalPoints())
            {
                for (i=0 ; i<game_->nbPlayer() ; i++)
                {
                    textOutTable(pref_.margin() + (2*i+1)*table_width_,pos_y,
                        _("Points"),table_width_,game_->ranking(i));
                    textOutTable(pref_.margin() + 2*(i+1)*table_width_,pos_y,
                        _("Total"),table_width_,game_->ranking(i));
                }
            }
            else
            // If it need only the ranking
            {
                for (i=0 ; i<game_->nbPlayer() ; i++)
                {
                    textOutTable(pref_.margin() + (2*i+1)*table_width_,pos_y,
                        _("Points"),table_width_,game_->ranking(i));
                    textOutTable(pref_.margin() + 2*(i+1)*table_width_,pos_y,
                        _("Ranking"),table_width_,game_->ranking(i));
                }
            }

            pos_y = pos_y - table_line_height_;
        }
    }


    void PdfExportation::printPoints(double& pos_y)
    {
        ustring text_buffer;
        unsigned int i;

        while ((pos_y > pref_.margin() + pref_.fontSize() ) && (line_ < game_->maxNbTurn()+1))
        {
            text_buffer = ustring::compose(_("Turn %1"),line_);
            textOutTable(pref_.margin(),pos_y,text_buffer,table_width_,0);

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
                        textOutTable(pref_.margin() + (3*i+1)*table_width_,pos_y,text_buffer,table_width_,game_->ranking(i));
                        text_buffer = game_->totalPointsUstring(i,line_);
                        textOutTable(pref_.margin() + (3*i+2)*table_width_,pos_y,text_buffer,table_width_,game_->ranking(i));
                        text_buffer = game_->rankingUstring(i,line_);
                        textOutTable(pref_.margin() + (3*i+3)*table_width_,pos_y,text_buffer,table_width_,game_->ranking(i));
                    } else
                    // If the total points needs to be display
                    if (pref_.totalPoints())
                    {
                        textOutTable(pref_.margin() + (2*i+1)*table_width_,pos_y,text_buffer,table_width_,game_->ranking(i));
                        text_buffer = game_->totalPointsUstring(i,line_);
                        textOutTable(pref_.margin() + 2*(i+1)*table_width_,pos_y,text_buffer,table_width_,game_->ranking(i));
                    }else
                    // If the ranking needs to be display
                    if (pref_.ranking())
                    {
                        textOutTable(pref_.margin() + (2*i+1)*table_width_,pos_y,text_buffer,table_width_,game_->ranking(i));
                        text_buffer = game_->rankingUstring(i,line_);
                        textOutTable(pref_.margin() + 2*(i+1)*table_width_,pos_y,text_buffer,table_width_,game_->ranking(i));
                    }
                    else
                        textOutTable(pref_.margin() + (i+1)*table_width_,pos_y,text_buffer,table_width_,game_->ranking(i));
                }
            }

            line_ ++;
            pos_y -= table_line_height_;
        }
    }

    void PdfExportation::addTotalPointsRanking(double& y)
    {
        ustring text_buffer;
        unsigned int i;

        double table_width = ((width_- 2*pref_.margin())/(game_->nbPlayer()+1));

        // Names
        textOutTable(pref_.margin(),y,_("Name"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
            textOutTable(pref_.margin() + (i+1)*table_width,y,game_->playerNameUstring(i),table_width,game_->ranking(i));

        // Print the finals points
        textOutTable(pref_.margin(),y- table_line_height_,_("Total points"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(pref_.margin() + (i+1)*table_width,y- table_line_height_,
                         game_->totalPointsUstring(i),table_width,game_->ranking(i));
        }

        // Print the ranking
        textOutTable(pref_.margin(),y-2* table_line_height_,_("Ranking"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(pref_.margin() + (i+1)*table_width,y- 2*table_line_height_,
                         game_->rankingUstring(i),table_width,game_->ranking(i));
        }

        createGrid(pref_.margin(),y+ table_line_height_*2/3,width_-pref_.margin(),
                   y - table_line_height_*7/3, table_line_height_,table_width);

        y = y - 3*table_line_height_;
    }

    void PdfExportation::addStats(double& y)
    {
        ustring text_buffer;
        unsigned int i;

        double table_width = ((width_ - 2*pref_.margin())/(game_->nbPlayer()+1));

        // Names
        textOutTable(pref_.margin(),y,_("Name"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(pref_.margin() + (i+1)*table_width,y,
                         game_->playerNameUstring(i),table_width,game_->ranking(i));
        }

        // Nb turn
        y -= table_line_height_;
        textOutTable(pref_.margin(),y,_("Nb turn"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(pref_.margin() + (i+1)*table_width,y,
                            game_->nbTurnUstring(i),table_width,game_->ranking(i));
        }

        // Mean
        y -= table_line_height_;
        textOutTable(pref_.margin(),y,_("Mean points"),table_width);
        for (i=0 ; i<game_->nbPlayer() ; i++)
        {
            textOutTable(pref_.margin() + (i+1)*table_width,y,
                            game_->meanPointsUstring(i),table_width,game_->ranking(i));
        }

        if (game_->config().turnBased())
        {
            // Nb turn best
            y -= table_line_height_;
            textOutTable(pref_.margin(),y,_("Nb turn best"),table_width);
            for (i=0 ; i<game_->nbPlayer() ; i++)
            {
                textOutTable(pref_.margin() + (i+1)*table_width,y,
                                game_->nbTurnBestUstring(i),table_width,game_->ranking(i));
            }

            // Nb turn worst
            y -= table_line_height_;
            textOutTable(pref_.margin(),y,_("Nb turn worst"),table_width);
            for (i=0 ; i<game_->nbPlayer() ; i++)
            {
                textOutTable(pref_.margin() + (i+1)*table_width,y,
                                game_->nbTurnWorstUstring(i),table_width,game_->ranking(i));
            }

            // Nb turn first
            y -= table_line_height_;
            textOutTable(pref_.margin(),y,_("Nb turn first"),table_width);
            for (i=0 ; i<game_->nbPlayer() ; i++)
            {
                textOutTable(pref_.margin() + (i+1)*table_width,y,
                                game_->nbTurnFirstUstring(i),table_width,game_->ranking(i));
            }

            // Nb turn last
            y -= table_line_height_;
            textOutTable(pref_.margin(),y,_("Nb turn last"),table_width);
            for (i=0 ; i<game_->nbPlayer() ; i++)
            {
                textOutTable(pref_.margin() + (i+1)*table_width,y,
                                game_->nbTurnLastUstring(i),table_width,game_->ranking(i));
            }

            createGrid(pref_.margin(),
                      y + table_line_height_*20/3,
                      width_ - pref_.margin(),
                      y - table_line_height_*1/3,
                      table_line_height_,
                      table_width);
        }
        else
        {
            createGrid(pref_.margin(),
                      y + table_line_height_*8/3,
                      width_ - pref_.margin(),
                      y - table_line_height_*1/3,
                      table_line_height_,
                      table_width);
        }
    }

    bool PdfExportation::addPodium(const double y)
    {
        PdfImage podium(pdf_);
        try
        {
            podium.LoadFromFile("Images/Podium.png");
        }
        catch (PoDoFo::PdfError& e)
        {
            painter_->FinishPage();
            throw e;
        }
        double podium_width = podium.GetWidth();
        double podium_height = podium.GetHeight();
        double ratio=1;

        if (podium_width > width_ - 2*pref_.margin())
            ratio = (width_ - 2 * pref_.margin()) / podium_width;


        if (y - podium_height*ratio - table_line_height_ > pref_.margin())
        {
            painter_->DrawImage((width_ - podium_width*ratio ) / 2 ,y - podium_height*ratio - table_line_height_,
                                &podium,ratio,ratio);

            vector<unsigned int> index = game_->playerIndexFromPosition();

            font_->SetFontSize(2*pref_.fontSize());

            // First
            textOutTable(pref_.margin(),y-podium_height*ratio /4,game_->playerNameUstring(index[0]),
                            width_-2*pref_.margin(),1);

            // Second
            if (game_->nbPlayer() >= 2)
            {
                textOutTable((width_-podium_width*ratio )/2,y-podium_height*ratio /2,
                             game_->playerNameUstring(index[1]),podium_width*ratio /3,2);
            }

            // Third
            if (game_->nbPlayer() >= 3)
            {
                textOutTable((width_-podium_width*ratio )/2 +2*podium_width*ratio /3,
                             y-13*podium_height*ratio /20,game_->playerNameUstring(index[2]),podium_width*ratio /3,3);
            }

            return false;
        }
        else
            return true;
    }


    //
    // Print function
    //
    void PdfExportation::showText(const Glib::ustring& text)
    {
        painter_->AddText(ustringToPdfstring(text));
    }

    void PdfExportation::textOutTable(const double pos_min_x, const double pos_y, const Glib::ustring& text, const double max_width, const int ranking)
    {
        double text_width;
        unsigned int nb_char;
        PdfString text_buffer = ustringToPdfstring(text);
        const PdfFontMetrics* font_metric = font_->GetFontMetrics();

        text_width = font_metric->StringWidth(text_buffer);
        nb_char = text_buffer.GetCharacterLength();

        // Reduce the length of the text if needed
        while (text_width > max_width && nb_char > 1)
        {
            nb_char--;
            text_width = font_metric->StringWidth(text_buffer.GetUnicode(),nb_char);
        }
        if (nb_char != text.length())
        {
            ustring tmp_str = text_buffer.GetStringUtf8();
            tmp_str.resize(nb_char);
            text_buffer = ustringToPdfstring(tmp_str);
        }

        // Set the color
        switch (ranking)
        {
        case 0:
            painter_->SetColor(0,0,0);
            break;
        case 1:
            painter_->SetColor(0,0.4,0);
            break;
        case 2:
            painter_->SetColor(0,0,0.25);
            break;
        case 3:
            painter_->SetColor(0.75,0,0);
            break;
        default:
            painter_->SetColor(0.35,0.2,0);
        }

        // Display the text center in the table
        painter_->DrawText((max_width - text_width) / 2 + pos_min_x,pos_y,text_buffer,nb_char);


        // Reset the color
        painter_->SetColor(0,0,0);
    }


    void PdfExportation::tableWidthCalculate()
    {
        if (pref_.totalPoints() && pref_.ranking())
            table_width_ = ((width_ - 2*pref_.margin())/(3*(game_->nbPlayer())+1));
        else if (pref_.totalPoints() || pref_.ranking())
            table_width_ = ((width_ - 2*pref_.margin())/(2*(game_->nbPlayer())+1));
        else
            table_width_ = ((width_ - 2*pref_.margin())/(game_->nbPlayer()+1));
    }

    void PdfExportation::createGrid(const double top_x, const double top_y, const double bottom_x, const double bottom_y,
                           const double length_row, const double length_column)
    {
        double x,y;

        painter_->SetStrokeWidth(1);

        // Vertical grid;
        for (y = top_y ; y >= bottom_y - 1 ; y -= length_row)
        {
            painter_->DrawLine(top_x,y,bottom_x,y);
        }

        // Horizontal grid;
        for (x = top_x ; x <= bottom_x + 1; x += length_column)
        {
            painter_->DrawLine(x,top_y,x,bottom_y);
        }
    }

    //
    // Fusion function
    //
    void PdfExportation::deleteTemporaryFiles(string& filename)
    {
        if (remove((filename + "1").c_str()) != 0)
            perror(ustring::compose(_("Error when deleting %1: "),filename + "1").c_str());
        if (remove((filename + "2").c_str()) != 0)
            perror(ustring::compose(_("Error when deleting %1: "),filename + "2").c_str());
    }



    //
    // Static function
    //


    PdfString PdfExportation::ustringToPdfstring(const ustring& str)
    {
        return PdfString((pdf_utf8*)(str.c_str()));
    }

    bool PdfExportation::canUseUtf8()
    {
        #if PODOFO_VERSION > 0x000900
        return true;
        #else
        return false;
        #endif // PODOFO_VERSION
    }

    void PdfExportation::exportToPdf(const Game* game, const ExportPdfPreferences& pdf_pref, const ChartExportationPreferences& chart_pref, const Glib::ustring& filename)
    {
        PoDoFo::PdfError::EnableLogging(false);
        PoDoFo::PdfError::EnableDebug(false);

        string locale_filename = locale_from_utf8(filename);

        PdfExportation* pdf_table;
        try
        {
            pdf_table = new PdfExportation(game,pdf_pref);
        }
        catch (PoDoFo::PdfError& e)
        {
            cerr << e.what() << endl;
            throw PdfError(_("The PDF document cannot be created"));
        }

        try
        {
            if(pdf_table->createFirstPage(filename))
                while(pdf_table->createOtherPage());
        }
        catch (PoDoFo::PdfError& e)
        {
            delete pdf_table;
            cerr << e.what() << endl;
            throw PdfError(_("The PDF table cannot be created"));
        }


        try
        {
            ExportPdfPreferences chart_pdf_pref(pdf_pref);
            chart_pdf_pref.setDirection(ExportPdfPreferences::LANDSCAPE);
            ChartExportationPreferences tmp_chart_pref(chart_pref);

            game->exportToChart(filename + "1",tmp_chart_pref,chart_pdf_pref,Game::PDF);
            tmp_chart_pref.setTotalPoints(false);
            game->exportToChart(filename + "2",tmp_chart_pref,chart_pdf_pref,Game::PDF);
        }
        catch(csuper::PdfError& e)
        {
            cerr << e.what() << endl;
            delete pdf_table;
            deleteTemporaryFiles(locale_filename);
            throw PdfError(_("The PDF charts cannot be save"));
        }

        try
        {
            PdfMemDocument pdf_chart_1((locale_filename+"1").c_str());
            PdfMemDocument pdf_chart_2((locale_filename+"2").c_str());
            pdf_table->pdf_->Append(pdf_chart_1);
            pdf_table->pdf_->Append(pdf_chart_2);
        }
        catch(PoDoFo::PdfError& e)
        {
            cerr << e.what() << endl;
            delete pdf_table;
            deleteTemporaryFiles(locale_filename);
            throw PdfError(_("The PDF charts cannot be merge to the table"));
        }


        try
        {
            pdf_table->pdf_->Write((locale_filename).c_str());
        }
        catch (PoDoFo::PdfError& e)
        {
            delete pdf_table;
            cerr << e.what() << endl;
            throw PdfError(_("The PDF table cannot be save"));
        }

        deleteTemporaryFiles(locale_filename);

        delete pdf_table;
    }

}
