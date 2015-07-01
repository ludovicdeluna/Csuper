/*!
 * \file    preferences_score_display.h
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_score_display.h
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

#ifndef SCORE_DISPLAY_H_INCLUDED
#define SCORE_DISPLAY_H_INCLUDED

#include "share.h"

namespace csuper
{
    /*! \class ScoreDisplayPreferences
    *   \brief This class indicate what will be display in the left side of the main window
    */
    class ScoreDisplayPreferences
    {
    private:
        bool total_points_;   /*!< Display the total points in each turn */
        bool ranking_;        /*!< Display the ranking in each turn */
        bool edit_suppr_;     /*!< Display the edit and delete turn in each turn */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        ScoreDisplayPreferences();

        /*!
         *  \brief Constructor with all intern component
         *  \param total_points
         *  \param ranking
         *  \param edit_suppr
         */
        ScoreDisplayPreferences(const bool total_points, const bool ranking, const bool edit_suppr);

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \exception csuper::XmlError if bad xmlpp node
         */
        ScoreDisplayPreferences(xmlpp::Node* xml_node);




        //
        // Function
        //
        /*!
         *  \brief Operator ==
         *  \param score another ScoreDisplayPreferences
         */
        bool operator==(const ScoreDisplayPreferences& score) const;

        /*!
         *  \brief Convert to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param score the ScoreDisplayPreferences
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const ScoreDisplayPreferences& score);

        /*!
         *  \brief Add the ScoreDisplayPreferences into a xmlpp element
         *  \param parent_node the parent node
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node) const;





        //
        // Setter
        //
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
         *  \brief Set the edit_suppr
         *  \param the edit_suppr
         */
         inline void setEditSuppr(const bool edit_suppr)
         {
             edit_suppr_ = edit_suppr;
         }





        //
        // Getter
        //
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
         *  \brief Return the edit_suppr
         *  \return the edit_suppr
         */
         inline bool editSuppr() const
         {
             return edit_suppr_;
         }



        //
        // Getter ustring
        //
        /*!
         *  \brief Return the total_points in a ustring
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
         *  \brief Return the edit_suppr in a ustring
         *  \return the ustring
         */
         inline Glib::ustring editSupprUstring() const
         {
             return boolToUstring(edit_suppr_);
         }
    };
}


#endif // SCORE_DISPLAY_H_INCLUDED
