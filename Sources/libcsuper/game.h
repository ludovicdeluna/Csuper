/*!
 * \file    game.h
 * \author  Remi BERTHO
 * \date    04/06/15
 * \version 4.3.0
 */

/*
* game.h
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

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "game_configuration.h"
#include "player.h"


namespace csuper
{
    /*! \class Game
    *   \brief This class represent a game
    */
    class Game
    {
    private:
        static double version_;
        unsigned int size_max_name_;
        Glib::Date date_;
        unsigned int nb_player_;
        GameConfiguration *config_;
        std::vector<Player*> players_;
        unsigned int distributor_;


        //
        // Getter
        //
        /*!
         *  \brief return the game configuration
         *  \param index the index of the player
         *  \return the player
         *  \exception std::length_error if index is greater the the number of player
         */
        Player &player(const unsigned int index);

        /*!
         *  \brief return the game configuration
         *  \param index the index of the player
         *  \return the player
         *  \exception std::length_error if index is greater the the number of player
         */
        const Player &player(const unsigned int index) const;

        /*!
         *  \brief return the game configuration
         *  \param index the index of the player
         *  \return the player
         *  \exception csuper::notFound if the plyer name doesn't exist
         */
        Player &player(const Glib::ustring& player_name)
        {
            return player(getPlayerIndex(player_name));
        }

        /*!
         *  \brief return the game configuration
         *  \param index the index of the player
         *  \return the player
         *  \exception csuper::notFound if the plyer name doesn't exist
         */
        Player const &player(const Glib::ustring& player_name) const
        {
            return player(getPlayerIndex(player_name));
        }



        //
        // Function
        //
        /*!
         *  \brief Get the index of a player
         *  \param player_name
         *  \exception csuper::notFound if the player name doesn't exist
         */
        unsigned int getPlayerIndex(const Glib::ustring& player_name) const;

        /*!
         *  \brief Get the index of a player
         *  \param player
         *  \exception csuper::notFound if the player name doesn't exist
         */
        unsigned int getPlayerIndex(const Player&) const;

        /*!
         *  \brief Calculate the new ranking
         */
        void rankingCalculation();

        /*!
         *  \brief Check if someone exceed the maximum number
         *  \return true if someone exceed, false otherwise
         */
        bool exceedMaxNumber() const;

        /*!
         *  \brief Return the last ranking in a turn
         *  \param turn thu turn
         *  \return the last ranking in a turn
         *  \exception std::length_error if turn is greater than the number of turn
         */
        unsigned int lastRanking(const unsigned int turn) const;

        /*!
         *  \brief Increase the distributor
         */
        void increaseDistributor();

        /*!
         *  \brief Decrease the distributor
         */
        void decreaseDistributor();




        //
        // Statistical
        //
        /*!
         *  \brief Calculate the number of time where the player got the best or the worst score in a turn
         *  \param player_index the player index
         *  \param best if true calculate the number of best and otherwise the number of worst
         *  \return the number of time where the player got the best or the worst score in a turn
         *  \exception std::length_error if index is greater than the number of player
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        unsigned int nbTurnBestWorst(const unsigned int player_index, const bool best) const;

        /*!
         *  \brief Calculate the number of time where the player was in the first or the last place
         *  \param player_index the player index
         *  \param first if true calculate the number of first place and otherwise the number of last place
         *  \return the number of time where the player was in the first or the last place
         *  \exception std::length_error if index is greater than the number of player
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        unsigned int nbTurnFirstLast(const unsigned int player_index, const bool first) const;


        //
        // Export
        //
        /*!
         *  \brief Export to a gnuplot data file (octave/matlab)
         *  \param filename the filename
         *  \exception std::ios_base::failure if intern error
         *  \exception csuper::fileError if bad filename
         */
        void exportToGnuplotData(const Glib::ustring& filename) const;

        /*!
         *  \brief Export to a gnuplot script file (octave/matlab)
         *  \param filename the filename
         *  \exception std::ios_base::failure if intern error
         *  \exception csuper::fileError if bad filename
         */
        void exportToGnuplotScript(const Glib::ustring& filename) const;



    protected:
        //
        // To Ustring
        //
        /*!
         *  \brief Convert the header to a ustring
         *  \return the ustring
         */
        virtual Glib::ustring toUstringHeader() const;

        /*!
         *  \brief Convert the distributor to a ustring
         *  \return the ustring
         */
        virtual Glib::ustring toUstringDistributor() const;

        /*!
         *  \brief Convert the names to a ustring and calculate the line size
         *  \param line_size the size of the line
         *  \param change_line_size indicate if the function must change the line size
         *  \return the ustring
         */
        virtual Glib::ustring toUstringNames(unsigned int& line_size, const bool change_line_size = false) const;

        /*!
         *  \brief Create a line to a ustring
         *  \param line_size the size of the line
         *  \return the ustring
         */
        virtual Glib::ustring toUstringLine(const unsigned int line_size) const;

        /*!
         *  \brief Convert all the points to a ustring
         *  \return the ustring
         */
        virtual Glib::ustring toUstringAllPoints() const;

        /*!
         *  \brief Convert the total points to a ustring
         *  \return the ustring
         */
        virtual Glib::ustring toUstringTotalPoints() const;

        /*!
         *  \brief Convert the ranking to a ustring
         *  \return the ustring
         */
        virtual Glib::ustring toUstringRanking() const;

    public:
        //
        // Constructor
        //
        /*!
         *  \brief Constructor
         *  \param nb_player the number of player
         *  \param game_config the game configuration used
         */
        Game(const unsigned int nb_player,const GameConfiguration& game_config);

        /*!
         *  \brief Copy constructor
         */
        Game(const Game &game);

        /*!
         *  \brief Constructor from a filename
         *  \exception csuper::xmlError if bad file
         */
        Game(const Glib::ustring filename);




        //
        // Destuctor
        //
        /*!
         *  \brief Destructor
         */
        virtual ~Game();





        //
        // Operator
        //
        /*!
         *  \brief operator =
         *  \param game a game
         *  \return a reference to the object
         */
        Game &operator=(const Game &game);

        /*!
         *  \brief Operator <<
         *  \param os the ostream
         *  \param Game the game
         *  \return the ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const Game& game);





        //
        // Function
        //
        /*!
         *  \brief Convert to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstring() const;

        /*!
         *  \brief Convert the points of the game to a ustring
         *  \return the ustring
         */
        Glib::ustring toUstringPoints() const;

        /*!
         *  \brief Calculate the maximal number of turn
         *  \return the maximal number of turn
         */
        unsigned int maxNbTurn() const;

        /*!
         *  \brief Begin a new turn in a non turn based game
         *  \param player_index the index of the player
         *  \param points the new points
         *  \return true if the game is over, false otherwise
         *  \exception csuper::wrongUse if function is used in a turn based game
         *  \exception std::length_error if index is greater the the number of player
         */
        bool newTurn(const unsigned int player_index, const double points);

        /*!
         *  \brief Begin a new turn in a non turn based game
         *  \param player_name the name of the player
         *  \param points the new points
         *  \return true if the game is over, false otherwise
         *  \exception csuper::wrongUse if function is used in a turn based game
         *  \exception csuper::notFound if the player name doesn't exist
         */
        inline bool newTurn(const Glib::ustring& player_name, const double points)
        {
            return newTurn(getPlayerIndex(player_name),points);
        }

        /*!
         *  \brief Begin a new turn in a turn based game
         *  \param points the new points for all player
         *  \return true if the game is over, false otherwise
         *  \exception csuper::wrongUse if function is used in a turn based game
         *  \exception std::length_error if the number of points don't correspond to the number of player
         */
        bool newTurn(const std::vector<double>& points);

        /*!
         *  \brief Indicate if all the names are different
         *  \return true if all the names are different, false otherwise
         */
        bool differentsPlayerNames() const;

        /*!
         *  \brief Delete a turn
         *  \param turn the turn
         *  \return true if the game is over, false otherwise
         *  \exception std::length_error if turn is greater than the number of turn
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        bool deleteTurn(const unsigned int turn);

        /*!
         *  \brief Delete a turn
         *  \param turn the turn
         *  \param player_index the player index
         *  \return true if the game is over, false otherwise
         *  \exception std::length_error if index is greater than the number of player
         *  \exception std::length_error if turn is greater than the number of turn
         *  \exception csuper::wrongUse if function is used in a turn based game
         */
        bool deleteTurn(const unsigned int turn, const unsigned int player_index);

        /*!
         *  \brief Delete a turn
         *  \param turn the turn
         *  \param player_name the player name
         *  \return true if the game is over, false otherwise
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception csuper::wrongUse if function is used in a turn based game
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline bool deleteTurn(const unsigned int turn, const Glib::ustring& player_name)
        {
            return deleteTurn(turn,getPlayerIndex(player_name));
        }

        /*!
         *  \brief Edit a turn
         *  \param turn the turn
         *  \param points the new points for all player
         *  \return true if the game is over, false otherwise
         *  \exception std::length_error if turn is greater than the number of turn
         *  \exception std::length_error if the number of points don't correspond to the number of player
         */
        bool editTurn(const unsigned int turn, const std::vector<double>& points);

        /*!
         *  \brief Edit a turn
         *  \param turn the turn
         *  \param player_index the player index
         *  \param points the new points
         *  \return true if the game is over, false otherwise
         *  \exception std::length_error if index is greater than the number of player
         *  \exception std::length_error if turn is greater than the number of turn
         */
        bool editTurn(const unsigned int turn, const unsigned int player_index, const double points);

        /*!
         *  \brief Edit a turn
         *  \param turn the turn
         *  \param player_name the player name
         *  \param points the new points
         *  \return true if the game is over, false otherwise
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline bool editTurn(const unsigned int turn, const Glib::ustring& player_name, const double points)
        {
            return editTurn(turn,getPlayerIndex(player_name),points);
        }

        /*!
         *  \brief Get the player index of all the player sorted by the ranking
         *  \return a vector containing in the first element contain the player index of the first...
         */
        std::vector<unsigned int> playerIndexFromPosition() const;

        /*!
         *  \brief Write to a file
         *  \param filename the filename
         *  \exception xmlpp::internal_error if bad filename
         */
        void writeToFile(const Glib::ustring& filename) const;

        /*!
         *  \brief Rewrite to a file
         *  \param filename the filename
         *  \exception xmlpp::internal_error if bad filename
         *  \exception csuper::fileError
         */
        void reWriteToFile(const Glib::ustring& filename) const;







        //
        // Statistics
        //
        /*!
         *  \brief Calculate the number of time where the player got the best score in a turn
         *  \param player_index the player index
         *  \return the number of time where the player got the best score in a turn
         *  \exception std::length_error if index is greater than the number of player
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        inline unsigned int nbTurnBest(const unsigned int player_index) const
        {
            return nbTurnBestWorst(player_index,true);
        }

        /*!
         *  \brief Calculate the number of time where the player got the best score in a turn
         *  \param player_name the player name
         *  \return the number of time where the player got the best score in a turn
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        inline unsigned int nbTurnBest(const Glib::ustring& player_name) const
        {
            return nbTurnBest(getPlayerIndex(player_name));
        }

        /*!
         *  \brief Calculate the number of time where the player got the worst score in a turn
         *  \param player_index the player index
         *  \return the number of time where the player got the worst score in a turn
         *  \exception std::length_error if index is greater than the number of player
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        inline unsigned int nbTurnWorst(const unsigned int player_index) const
        {
            return nbTurnBestWorst(player_index,false);
        }


        /*!
         *  \brief Calculate the number of time where the player got the worst score in a turn
         *  \param player_name the player name
         *  \return the number of time where the player got the worst score in a turn
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        inline unsigned int nbTurnWorst(const Glib::ustring& player_name) const
        {
            return nbTurnWorst(getPlayerIndex(player_name));
        }

        /*!
         *  \brief Calculate the number of time where the player was in the first place
         *  \param player_index the player index
         *  \return the number of time where the player was in the first place
         *  \exception std::length_error if index is greater than the number of player
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        inline unsigned int nbTurnFirst(const unsigned int player_index) const
        {
            return nbTurnFirstLast(player_index,true);
        }

        /*!
         *  \brief Calculate the number of time where the player was in the first place
         *  \param player_name the player name
         *  \return the number of time where the player was in the first place
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        inline unsigned int nbTurnFirst(const Glib::ustring& player_name) const
        {
            return nbTurnFirst(getPlayerIndex(player_name));
        }

        /*!
         *  \brief Calculate the number of time where the player was in the first place
         *  \param player_index the player index
         *  \return the number of time where the player was in the first place
         *  \exception std::length_error if index is greater than the number of player
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        inline unsigned int nbTurnLast(const unsigned int player_index) const
        {
            return nbTurnFirstLast(player_index,false);
        }

        /*!
         *  \brief Calculate the number of time where the player was in the last place
         *  \param player_name the player name
         *  \return the number of time where the player was in the last place
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception csuper::wrongUse if function is used in a non turn based game
         */
        inline unsigned int nbTurnLast(const Glib::ustring& player_name) const
        {
            return nbTurnLast(getPlayerIndex(player_name));
        }







        //
        // Export
        //
        /*!
         *  \brief Export to a csv file
         *  \param filename the filename
         *  \exception std::ios_base::failure if intern error
         *  \exception csuper::fileError if bad filename
         */
        void exportToCsv(const Glib::ustring& filename) const;

        /*!
         *  \brief Export to a m file (octave/matlab)
         *  \param filename the filename
         *  \exception std::ios_base::failure if intern error
         *  \exception csuper::fileError if bad filename
         */
        void exportToM(const Glib::ustring& filename) const;

        /*!
         *  \brief Export to a gnuplot file (octave/matlab)
         *  \param filename the filename
         *  \exception std::ios_base::failure if intern error
         *  \exception csuper::fileError if bad filename
         */
        void exportToGnuplot(const Glib::ustring& filename) const;





        //
        // Setter
        //
        /*!
         *  \brief Set the size maximum of a name
         *  \param size_max_name
         */
        inline void setSizeMaxName(const unsigned int size_max_name)
        {
            size_max_name_ = size_max_name;
        }

        /*!
         *  \brief Set the date
         *  \param date
         */
        inline void setDate(const Glib::Date& date)
        {
            date_ = date;
        }

        /*!
         *  \brief Set the number of player
         *  \param nb_player
         */
        inline void setNbPlayer(const unsigned int nb_player)
        {
            nb_player_ = nb_player;
        }

        /*!
         *  \brief Set the distributor
         *  \param distributor
         */
        inline void setDistributor(const unsigned int distributor)
        {
            distributor_ = distributor;
        }

        /*!
         *  \brief Set the distributor
         *  \param distributor_name
         *  \exception csuper::notFound if the player name doesn't exist
         */
        inline void setDistributor(const Glib::ustring& distributor_name)
        {
            distributor_ = getPlayerIndex(distributor_name);
        }

        /*!
         *  \brief Set a player name
         *  \param index the index of the player
         *  \param name the name
         *  \exception std::length_error if index is greater the than number of player
         */
        inline void setPlayerName(const unsigned int index, const Glib::ustring& name)
        {
            players_[index]->setName(name);
        }




        //
        // Getter
        //
        /*!
         *  \brief return the version
         *  \return the version
         */
        inline double version() const
        {
            return version_;
        }

        /*!
         *  \brief return the size maximum of a name
         *  \return the size_max_name_
         */
        inline unsigned int sizeMaxName() const
        {
            return size_max_name_;
        }

        /*!
         *  \brief return the date
         *  \return the date
         */
        inline Glib::Date date() const
        {
            return date_;
        }

        /*!
         *  \brief return the version
         *  \return the version
         */
        inline unsigned int nbPlayer() const
        {
            return nb_player_;
        }

        /*!
         *  \brief return the game configuration
         *  \return the game configuration
         */
        inline const GameConfiguration &config() const
        {
            return *config_;
        }

        /*!
         *  \brief return the distributor
         *  \return the distributor
         */
        inline unsigned int distributor() const
        {
            return distributor_;
        }

        /*!
         *  \brief return the distributor name
         *  \return the distributor name
         */
        inline Glib::ustring distributorName() const
        {
            return players_[distributor_]->name();
        }

        /*!
         *  \brief return the number of turn of a player
         *  \param player_index the player index
         *  \return the number of turn
         *  \exception std::length_error if index is greater than the number of player
         */
        inline unsigned int nbTurn(const unsigned int player_index) const
        {
            return player(player_index).nbTurn();
        }

        /*!
         *  \brief return the number of turn of a player
         *  \param player_name the player name
         *  \return the number of turn
         *  \exception csuper::notFound if the player name doesn't exist
         */
        inline unsigned int nbTurn(const Glib::ustring& player_name) const
        {
            return player(player_name).nbTurn();
        }

        /*!
         *  \brief return the points of a player
         *  \param player_index the player index
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the points
         *  \exception std::length_error if index is greater than the number of player
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline double points(const unsigned int player_index, const int turn=-1) const
        {
            return player(player_index).points(turn);
        }

        /*!
         *  \brief return the points of a player
         *  \param player_name the player name
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the points
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline double points(const Glib::ustring& player_name, const int turn=-1) const
        {
            return player(player_name).points(turn);
        }

        /*!
         *  \brief return the total points of a player
         *  \param player_index the player index
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the total points
         *  \exception std::length_error if index is greater than the number of player
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline double totalPoints(const unsigned int player_index, const int turn=-1) const
        {
            return player(player_index).totalPoints(turn);
        }

        /*!
         *  \brief return the total points of a player
         *  \param player_name the player name
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the total points
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline double totalPoints(const Glib::ustring& player_name, const int turn=-1) const
        {
            return player(player_name).totalPoints(turn);
        }

        /*!
         *  \brief return the ranking of a player
         *  \param player_index the player index
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the ranking
         *  \exception std::length_error if index is greater than the number of player
         *  \exception csuper::wrongUse if this function is used in a non turn game with a specific turn
         *  \exception std::length_error if turn is greater than the number of turn
         */
        unsigned int ranking(const unsigned int player_index, const int turn=-1) const;

        /*!
         *  \brief return the ranking of a player
         *  \param player_name the player name
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the total points
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception csuper::wrongUse if this function is used in a non turn game with a specific turn
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline unsigned int ranking(const Glib::ustring& player_name, const int turn=-1) const
        {
            return ranking(getPlayerIndex(player_name),turn);
        }





        //
        // Getter ustring
        //

        /*!
         *  \brief return the version in a ustring
         *  \return the ustring
         */
        inline Glib::ustring versionUstring() const
        {
            return intToUstring(version_);
        }

        /*!
         *  \brief return the size maximum of a name in a ustring
         *  \return the ustring
         */
        inline Glib::ustring sizeMaxNameUstring() const
        {
            return intToUstring(size_max_name_);
        }

        /*!
         *  \brief return the date in a ustring
         *  \return the ustring
         */
        inline Glib::ustring dateUstring() const
        {
            return date_.format_string("%x");
        }

        /*!
         *  \brief return the version in a ustring
         *  \return the ustring
         */
        inline Glib::ustring nbPlayerUstring() const
        {
            return intToUstring(nb_player_);
        }

        /*!
         *  \brief return the game configuration in a ustring
         *  \return the ustring
         */
        inline Glib::ustring configUstring() const
        {
            return config_->toUstring();
        }

        /*!
         *  \brief return the distributor in a ustring
         *  \return the ustring
         */
        inline Glib::ustring distributorUstring() const
        {
            return intToUstring(distributor_);
        }

        /*!
         *  \brief return the distributor name in a ustring
         *  \return the ustring
         */
        inline Glib::ustring distributorNameUstring() const
        {
            return players_[distributor_]->name();
        }

        /*!
         *  \brief return the game configuration in a ustring
         *  \param index the index of the player
         *  \return the ustring
         *  \exception std::length_error if index is greater the the number of player
         */
        inline Glib::ustring playerUstring(unsigned int index) const
        {
            return players_[index]->toUstring();
        }

        /*!
         *  \brief return the number of turn of a player in a ustring
         *  \param player_index the player index
         *  \return the ustring
         *  \exception std::length_error if index is greater than the number of player
         */
        inline Glib::ustring nbTurnUstring(const unsigned int player_index) const
        {
            return player(player_index).nbTurnUstring();
        }

        /*!
         *  \brief return the number of turn of a player in a ustring
         *  \param player_name the player name
         *  \return the ustring
         *  \exception csuper::notFound if the player name doesn't exist
         */
        inline Glib::ustring nbTurnUstring(const Glib::ustring& player_name) const
        {
            return player(player_name).nbTurnUstring();
        }

        /*!
         *  \brief return the points of a player in a ustring
         *  \param player_index the player index
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the ustring
         *  \exception std::length_error if index is greater than the number of player
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline Glib::ustring pointsUstring(const unsigned int player_index, const int turn=-1) const
        {
            return player(player_index).pointsUstring(config(),turn);
        }

        /*!
         *  \brief return the points of a player in a ustring
         *  \param player_name the player name
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the ustring
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline Glib::ustring pointsUstring(const Glib::ustring& player_name, const int turn=-1) const
        {
            return player(player_name).pointsUstring(config(),turn);
        }

        /*!
         *  \brief return the total points of a player in a ustring
         *  \param player_index the player index
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the ustring
         *  \exception std::length_error if index is greater than the number of player
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline Glib::ustring totalPointsUstring(const unsigned int player_index, const int turn=-1) const
        {
            return player(player_index).totalPointsUstring(config(),turn);
        }

        /*!
         *  \brief return the total points of a player in a ustring
         *  \param player_name the player name
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the ustring
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline Glib::ustring totalPointsUstring(const Glib::ustring& player_name, const int turn=-1) const
        {
            return player(player_name).totalPointsUstring(config(),turn);
        }

        /*!
         *  \brief return the ranking of a player in a ustring
         *  \param player_index the player index
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the ustring
         *  \exception std::length_error if index is greater than the number of player
         *  \exception csuper::wrongUse if this function is used in a non turn game with a specific turn
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline Glib::ustring rankingUstring(const unsigned int player_index, const int turn=-1) const
        {
            return intToUstring(ranking(player_index,turn));
        }

        /*!
         *  \brief return the ranking of a player in a ustring
         *  \param player_name the player name
         *  \param turn the turn, if not set the turn is set to the last turn
         *  \return the ustring
         *  \exception csuper::notFound if the player name doesn't exist
         *  \exception csuper::wrongUse if this function is used in a non turn game with a specific turn
         *  \exception std::length_error if turn is greater than the number of turn
         */
        inline Glib::ustring rankingUstring(const Glib::ustring& player_name, const int turn=-1) const
        {
            return intToUstring(ranking(player_name,turn));
        }

    };
}

#endif // GAME_H_INCLUDED