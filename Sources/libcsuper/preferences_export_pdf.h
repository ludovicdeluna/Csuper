/*!
 * \file    preferences_export_pdf.h
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_export_pdf.h
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

#ifndef PREFERENCES_EXPORT_PDF_H_INCLUDED
#define PREFERENCES_EXPORT_PDF_H_INCLUDED

#include "share.h"

namespace csuper
{
    /*! \class ExportPdfPreferences
    *   \brief This class indicate the preferences for the pdf exportation
    */
    class ExportPdfPreferences
    {
    public:
        //
        // Enum
        //
        enum CharacterSet
        {
            UTF8=0,
            WINDOWS1252=1
        };

        enum PageSize
        {
            A3=2,
            A4=3,
            A5=4
        };

        enum PageDirection
        {
            PORTRAIT=0,
            LANDSCAPE=1
        };

    private:
        unsigned int font_size_;   /*!< The classical font size */
        PageSize size_;            /*!< The size of the pdf document */
        PageDirection direction_;  /*!< The direction of the pdf document */
        CharacterSet charset_;     /*!< The character set of the pdf document */
        unsigned int margin_;      /*!< The margin of the pdf document */
        bool total_points_;        /*!< Indicate if we show the total points in each turn */
        bool ranking_;             /*!< Indicate if we show the ranking in each turn */
        bool embedded_font_;       /*!< Indicate if the font will be embedded */
        Glib::ustring font_name_;  /*!< The font name*/

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        ExportPdfPreferences();

        /*!
         *  \brief Constructor with all intern component
         *  \param font_size
         *  \param size
         *  \param direction
         *  \param charset
         *  \param margin
         *  \param total_points
         *  \param ranking
         *  \param embedded_font
         *  \param font_name
         */
        ExportPdfPreferences(const unsigned int font_size,
                             const PageSize size,
                             const PageDirection direction,
                             const CharacterSet charset,
                             const unsigned int margin,
                             const bool total_points,
                             const bool ranking,
                             const bool embedded_font,
                             const Glib::ustring& font_name);

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \param version the version of the preferences
         *  \exception csuper::XmlError if bad xmlpp node
         */
        ExportPdfPreferences(xmlpp::Node* xml_node, const double version);




        //
        // Function
        //
        /*!
         *  \brief Operator ==
         *  \param pdf another ExportPdfPreferences
         */
        bool operator==(const ExportPdfPreferences& pdf) const;

        /*!
         *  \brief Convert to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param pdf the ExportPdfPreferences
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const ExportPdfPreferences& pdf);

        /*!
         *  \brief Add the ExportPdfPreferences into a xmlpp element
         *  \param parent_node the parent node
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node) const;





        //
        // Setter
        //
        /*!
         *  \brief Set the font_size
         *  \param the font_size
         */
         inline void setFontSize(const unsigned int font_size)
         {
             font_size_ = font_size;
         }

        /*!
         *  \brief Set the size
         *  \param the size
         */
         inline void setSize(const PageSize size)
         {
             size_ = size;
         }

        /*!
         *  \brief Set the direction
         *  \param the direction
         */
         inline void setDirection(const PageDirection direction)
         {
             direction_ = direction;
         }

        /*!
         *  \brief Set the charset
         *  \param the charset
         */
         inline void setCharset(const CharacterSet charset)
         {
             charset_ = charset;
         }

        /*!
         *  \brief Set the margin
         *  \param the margin
         */
         inline void setMargin(const unsigned int margin)
         {
             margin_ = margin;
         }

        /*!
         *  \brief Set the total_points
         *  \param the total_points
         */
         inline void setTotalPoints(const bool total_points)
         {
             total_points_ = total_points;
         }

        /*!
         *  \brief Set the ranking
         *  \param the ranking
         */
         inline void setRanking(const bool ranking)
         {
             ranking_ = ranking;
         }

        /*!
         *  \brief Set the font name
         *  \param the font name
         */
         inline void setFontName(const Glib::ustring& font_name)
         {
             font_name_ = font_name;
         }

        /*!
         *  \brief Set the embedded_font
         *  \param the embedded_font
         */
         inline void setEmbeddedFont(const bool embedded_font)
         {
             embedded_font_ = embedded_font;
         }


        //
        // Getter
        //
        /*!
         *  \brief Return the font_size
         *  \return the font_size
         */
         inline unsigned int fontSize() const
         {
             return font_size_;
         }

        /*!
         *  \brief Return the size
         *  \return the size
         */
         inline PageSize size() const
         {
             return size_;
         }

        /*!
         *  \brief Return the direction
         *  \return the direction
         */
         inline PageDirection direction() const
         {
             return direction_;
         }

        /*!
         *  \brief Return the charset
         *  \return the charset
         */
         inline CharacterSet charset() const
         {
             return charset_;
         }

        /*!
         *  \brief Return the margin
         *  \return the margin
         */
         inline unsigned int margin() const
         {
             return margin_;
         }

        /*!
         *  \brief Return the total_points
         *  \return the total_points
         */
         inline bool totalPoints() const
         {
             return total_points_;
         }

        /*!
         *  \brief Return the ranking
         *  \return the ranking
         */
         inline bool ranking() const
         {
             return ranking_;
         }

        /*!
         *  \brief Return the font name
         *  \return the font name
         */
         inline Glib::ustring fontName() const
         {
             return font_name_;
         }

        /*!
         *  \brief Return the embedded_font
         *  \return the embedded_font
         */
         inline bool embeddedFont() const
         {
             return embedded_font_ ;
         }






        //
        // Getter ustring
        //
        /*!
         *  \brief Return the font_size in a ustring
         *  \return the ustring
         */
         inline Glib::ustring fontSizeUstring() const
         {
             return intToUstring(font_size_);
         }

        /*!
         *  \brief Return the size in a ustring
         *  \return the ustring
         */
         inline Glib::ustring sizeUstring() const
         {
             return intToUstring(size_);
         }

        /*!
         *  \brief Return the direction in a ustring
         *  \return the ustring
         */
         inline Glib::ustring directionUstring() const
         {
             return intToUstring(direction_);
         }

        /*!
         *  \brief Return the charset in a ustring
         *  \return the ustring
         */
         inline Glib::ustring charsetUstring() const
         {
             return intToUstring(charset_);
         }

        /*!
         *  \brief Return the margin in a ustring
         *  \return the ustring
         */
         inline Glib::ustring marginUstring() const
         {
             return intToUstring(margin_);
         }

        /*!
         *  \brief Return the total_oints in a ustring
         *  \return the ustring
         */
         inline Glib::ustring totalPointsUstring() const
         {
             return boolToUstring(total_points_);
         }

        /*!
         *  \brief Return the ranking in a ustring
         *  \return the ustring
         */
         inline Glib::ustring rankingUstring() const
         {
             return boolToUstring(ranking_);
         }

        /*!
         *  \brief Return the embedded_font in a ustring
         *  \return the ustring
         */
         inline Glib::ustring embeddedFontUstring() const
         {
             return boolToUstring(embedded_font_);
         }


        /*!
         *  \brief Return the font name in a ustring
         *  \return the ustring
         */
         inline Glib::ustring fontNameUstring() const
         {
             return font_name_;
         }




    };
}



#endif // PREFERENCES_EXPORT_PDF_H_INCLUDED
