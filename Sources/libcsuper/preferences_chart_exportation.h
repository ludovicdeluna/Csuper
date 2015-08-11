/*!
 * \file    preferences_chart_exportation.h
 * \author  Remi BERTHO
 * \date    25/06/15
 * \version 4.3.0
 */

/*
* preferences_chart_exportation.h
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

#ifndef CHART_EXPORTATION_H_INCLUDED
#define CHART_EXPORTATION_H_INCLUDED

#include "share.h"

namespace csuper
{
    /*! \class ChartExportationPreferences
    *   \brief This class indicate the chart exportation preferences
    */
    class ChartExportationPreferences
    {
    private:
        int width_;         /*!< The width of the chart */
        int height_;        /*!< The height of the chart */
        bool total_points_; /*!< Total points or points */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        ChartExportationPreferences();

        /*!
         *  \brief Constructor with all intern component
         *  \param width
         *  \param height
         *  \param total_points
         */
        ChartExportationPreferences(const int width, const int height, const bool total_points);

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \exception csuper::XmlError if bad xmlpp node
         */
        ChartExportationPreferences(xmlpp::Node* xml_node);




        //
        // Function
        //
        /*!
         *  \brief Operator ==
         *  \param pref another ChartExportationPreferences
         */
        bool operator==(const ChartExportationPreferences& pref) const;

        /*!
         *  \brief Operator !=
         *  \param pref another ChartExportationPreferences
         */
        bool operator!=(const ChartExportationPreferences& pref) const;

        /*!
         *  \brief Convert to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param pref the ChartExportationPreferences
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const ChartExportationPreferences& pref);

        /*!
         *  \brief Add the ChartExportationPreferences into a xmlpp element
         *  \param parent_node the parent node
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node) const;





        //
        // Setter
        //
        /*!
         *  \brief Set the width
         *  \param the width
         */
         inline void setWidth(const int width)
         {
             width_ = width;
         }

        /*!
         *  \brief Set the height
         *  \param the height
         */
         inline void setHeight(const int height)
         {
             height_ = height;
         }

        /*!
         *  \brief Set the total_points
         *  \param the total_points
         */
         inline void setTotalPoints(const bool total_points)
         {
             total_points_ = total_points;
         }





        //
        // Getter
        //
        /*!
         *  \brief Return the width
         *  \return the width
         */
         inline int width() const
         {
             return width_;
         }

        /*!
         *  \brief Return the height
         *  \return the height
         */
         inline int height() const
         {
             return height_;
         }

        /*!
         *  \brief Return the total_points
         *  \return the total_points
         */
         inline bool totalPoints() const
         {
             return total_points_;
         }



        //
        // Getter ustring
        //
        /*!
         *  \brief Return the width in a ustring
         *  \return the ustring
         */
         inline Glib::ustring widthUstring() const
         {
             return intToUstring(width_);
         }

        /*!
         *  \brief Return the height in a ustring
         *  \return the ustring
         */
         inline Glib::ustring heightUstring() const
         {
             return intToUstring(height_);
         }

        /*!
         *  \brief Return the total_points in a ustring
         *  \return the ustring
         */
         inline Glib::ustring totalPointsUstring() const
         {
             return boolToUstring(total_points_);
         }
    };
}


#endif // CHART_EXPORTATION_H_INCLUDED
