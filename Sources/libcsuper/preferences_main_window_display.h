/*!
 * \file    preferences_main_window_display.h
 * \author  Remi BERTHO
 * \date    09/06/15
 * \version 4.3.0
 */

/*
* preferences_main_window_display.h
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

#ifndef MAIN_WINDOW_DISPLAY_H_INCLUDED
#define MAIN_WINDOW_DISPLAY_H_INCLUDED

#include "share.h"

namespace csuper
{
    /*! \class MainWindowDisplayPreferences
    *   \brief This class indicate what will be display in the main window
    */
    class MainWindowDisplayPreferences
    {
    private:
        bool ranking_;          /*!< Display the ranking in each turn */
        bool calculator_;       /*!< Display the calculator*/
        bool game_information_; /*!< Display the game informations */

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Default constructor
         */
        MainWindowDisplayPreferences();

        /*!
         *  \brief Constructor with all intern component
         *  \param calculator_
         *  \param ranking
         *  \param game_information
         */
        MainWindowDisplayPreferences(const bool ranking, const bool calculator, const bool game_information);

        /*!
         *  \brief Constructor with a xmlpp node
         *  \param xml_node the xml node
         *  \exception csuper::XmlError if bad xmlpp node
         */
        MainWindowDisplayPreferences(xmlpp::Node* xml_node);




        //
        // Function
        //
        /*!
         *  \brief Operator ==
         *  \param display another MainWindowDisplayPreferences
         */
        bool operator==(const MainWindowDisplayPreferences& display) const;

        /*!
         *  \brief Convert to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param display the MainWindowDisplayPreferences
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const MainWindowDisplayPreferences& display);

        /*!
         *  \brief Add the MainWindowDisplayPreferences into a xmlpp element
         *  \param parent_node the parent node
         *  \exception xmlpp::internal_error if bad xmlpp node
         */
        void createXmlNode(xmlpp::Element *parent_node) const;





        //
        // Setter
        //
        /*!
         *  \brief Set the calculator
         *  \param the calculator
         */
         inline void setCalculator(const bool calculator)
         {
             calculator_ = calculator;
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
         *  \brief Set the game_information
         *  \param the game_information
         */
         inline void setGameInformation(const bool game_information)
         {
             game_information_ = game_information;
         }





        //
        // Getter
        //
        /*!
         *  \brief Return the calculator
         *  \return the calculator
         */
         inline bool calculator() const
         {
             return calculator_;
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
         *  \brief Return the game_information
         *  \return the game_information
         */
         inline bool gameInformation() const
         {
             return game_information_;
         }



        //
        // Getter ustring
        //
        /*!
         *  \brief Return the calculator in a ustring
         *  \return the ustring
         */
         inline Glib::ustring calculatorUstring() const
         {
             return boolToUstring(calculator_);
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
         *  \brief Return the game_information in a ustring
         *  \return the ustring
         */
         inline Glib::ustring gameInformationUstring() const
         {
             return boolToUstring(game_information_);
         }
    };
}


#endif // MAIN_WINDOW_DISPLAY_H_INCLUDED
