/*!
 * \file    preferences_difference_between_player.h
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_difference_between_player.h
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

#ifndef DIFFERENCES_BETWEEN_PLAYER_H_INCLUDED
#define DIFFERENCES_BETWEEN_PLAYER_H_INCLUDED

#include "share.h"

namespace csuper
{
    /*! \class DifferenceBetweenPlayerPreferences
    *   \brief This class indicate which difference between player will be displayed in the ranking
    */
    class DifferenceBetweenPlayerPreferences
    {
    private:
        bool consecutive_;   /*!< Between two player consecutive */
        bool first_;         /*!< Between the player and the first */
        bool last_;          /*!< Between the player and the last one */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        DifferenceBetweenPlayerPreferences();

        /*!
         *  \brief Constructor with all intern component
         *  \param width
         *  \param height
         *  \param is_maximize
         */
        DifferenceBetweenPlayerPreferences(const bool consecutive, const bool first, const bool last);

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \exception csuper::xmlError if bad xmlpp node
         */
        DifferenceBetweenPlayerPreferences(xmlpp::Node* xml_node);




        //
        // Function
        //
        /*!
         *  \brief Operator ==
         *  \param diff another DifferenceBetweenPlayerPreferences
         */
        bool operator==(const DifferenceBetweenPlayerPreferences& diff) const;

        /*!
         *  \brief Convert to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param diff the DifferenceBetweenPlayerPreferences
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const DifferenceBetweenPlayerPreferences& diff);

        /*!
         *  \brief Add the DifferenceBetweenPlayerPreferences into a xmlpp element
         *  \param parent_node the parent node
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node) const;





        //
        // Setter
        //
        /*!
         *  \brief Set the consecutive
         *  \param the consecutive
         */
         inline void setConsecutive(const bool consecutive)
         {
             consecutive_ = consecutive;
         }

        /*!
         *  \brief Set the first
         *  \param the first
         */
         inline void setFirst(const bool first)
         {
             first_ = first;
         }

        /*!
         *  \brief Set the last
         *  \param the last
         */
         inline void setLast(const bool last)
         {
             last_ = last;
         }





        //
        // Getter
        //
        /*!
         *  \brief Return the consecutive
         *  \return the consecutive
         */
         inline unsigned int consecutive() const
         {
             return consecutive_;
         }

        /*!
         *  \brief Return the first
         *  \return the first
         */
         inline unsigned int first() const
         {
             return first_;
         }

        /*!
         *  \brief Return the last
         *  \return the last
         */
         inline bool last() const
         {
             return last_;
         }



        //
        // Getter ustring
        //
        /*!
         *  \brief Return the consecutive in a ustring
         *  \return the ustring
         */
         inline Glib::ustring consecutiveUstring() const
         {
             return boolToUstring(consecutive_);
         }

        /*!
         *  \brief Return the first in a ustring
         *  \return the ustring
         */
         inline Glib::ustring firstUstring() const
         {
             return boolToUstring(first_);
         }

        /*!
         *  \brief Return the last in a ustring
         *  \return the ustring
         */
         inline Glib::ustring lastUstring() const
         {
             return boolToUstring(last_);
         }
    };
}


#endif // DIFFERENCES_BETWEEN_PLAYER_H_INCLUDED
