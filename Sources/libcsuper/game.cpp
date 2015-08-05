/*!
 * \file    game.cpp
 * \author  Remi BERTHO
 * \date    04/06/15
 * \version 4.3.0
 */

/*
* game.cpp
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

#include "game.h"
#include "exceptions.h"
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "config.h"
#include "pdf_exportation.h"
#include "slope/slope.h"



namespace csuper
{
    using namespace std;
    using namespace Glib;
    using namespace xmlpp;

    double Game::version_(1.4);

    //
    // Constructor
    //

    Game::Game(const unsigned int nb_player,const GameConfiguration& game_config) : nb_player_(nb_player)
    {
        size_max_name_ = 100;
        date_.set_time_current();
        config_ = new GameConfiguration(game_config);
        distributor_ = 0;

        for (unsigned int i = 0; i<nb_player ; i++)
            players_.push_back(new Player(game_config));
    }


    Game::Game(const Game &game)
    {
        size_max_name_ = game.size_max_name_;
        date_ = game.date_;
        nb_player_ = game.nb_player_;
        distributor_ = game.distributor_;
        config_ = new GameConfiguration(*(game.config_));

        vector<Player*>::const_iterator it;
        for (it = game.players_.cbegin(); it != game.players_.cend() ; it++)
            players_.push_back(new Player(**it));
    }


    Game::Game(const Glib::ustring filename) : date_(1,Date::JANUARY,2015)
    {
        DomParser parser;
        try
        {
            parser.parse_file(filename);
        }
        catch (xmlpp::exception &e)
        {
        	cerr << e.what() << endl;
            throw XmlError(ustring::compose(_("Cannot open the file %1"),filename));
        }

        Node *node = parser.get_document()->get_root_node();
        if (node->get_name() != "csu")
            throw XmlError(ustring::compose(_("This file is not a CSU file, it's a %1 file."),node->get_name()));

        firstChildXmlElement(node);

        // Version
        double file_version = ustringToDouble(static_cast<Element*>(node)->get_child_text()->get_content());
        if (file_version > version_)
            throw XmlError(ustring::compose(_("This version of Csuper only support game file version of %1"),version_));

        // Size max of a name
        nextXmlElement(node);
        size_max_name_ = ustringToInt(static_cast<Element*>(node)->get_child_text()->get_content());

        // Date
        nextXmlElement(node);
        firstChildXmlElement(node);
        date_.set_year(ustringToInt(static_cast<Element*>(node)->get_child_text()->get_content()));
        nextXmlElement(node);
        date_.add_months(ustringToInt(static_cast<Element*>(node)->get_child_text()->get_content())-1);
        nextXmlElement(node);
        date_.set_day(ustringToInt(static_cast<Element*>(node)->get_child_text()->get_content()));

        // Nb player
        node = node->get_parent();
        nextXmlElement(node);
        nb_player_ = ustringToInt(static_cast<Element*>(node)->get_child_text()->get_content());

        // Distributor
        nextXmlElement(node);
        distributor_ = ustringToInt(static_cast<Element*>(node)->get_child_text()->get_content());

        // Game configuration
        nextXmlElement(node);
        config_ = new GameConfiguration(node);

        for (unsigned int i=0 ; i<nb_player_ ; i++)
        {
            nextXmlElement(node);
            players_.push_back(new Player(node));
        }

    }


    //
    // Destuctor
    //
    Game::~Game()
    {
        delete config_;

        vector<Player*>::iterator it;
        for (it = players_.begin(); it != players_.end() ; it++)
            delete *it;

        players_.clear();
    }


    //
    // Operator
    //
    Game &Game::operator=(const Game &game)
    {
        if (this==&game)
            return *this;


        delete config_;

        vector<Player*>::const_iterator it;
        for (it = players_.cbegin(); it != players_.cend() ; it++)
            delete *it;

        players_.clear();


        size_max_name_ = game.size_max_name_;
        date_ = game.date_;
        nb_player_ = game.nb_player_;
        distributor_ = game.distributor_;
        config_ = new GameConfiguration(*(game.config_));

        for (it = game.players_.cbegin(); it != game.players_.cend() ; it++)
            players_.push_back(new Player(**it));

        return *this;
    }

    ostream& operator<<(ostream& os, const Game& game)
    {
        os << game.toUstring();
        return os;
    }


    //
    // Getter
    //
    unsigned int Game::ranking(const unsigned int player_index, const int turn) const
    {
        if (turn == -1)
            return player(player_index).ranking();

        if (!(config().turnBased()))
            throw WrongUse(_("The ranking function should only be used in a turn based game when a specific turn is specify"));

        if (!(player(player_index).hasTurn(turn)))
            throw OutOfRange(ustring::compose(_("Cannot access to the %1th turn, there is only %2 turn"),turn,player(player_index).nbTurn()));

        vector<double> sort_points;
        vector<Player*>::const_iterator it_player;

        for (it_player=players_.cbegin() ; it_player != players_.cend() ; it_player++)
            sort_points.push_back((*it_player)->totalPoints(turn));

        // Sort the points base on the first way
        if (config().maxWinner())
            sort(sort_points.begin(),sort_points.end(),&compareDoubleDescending);
        else
            sort(sort_points.begin(),sort_points.end(),&compareDoubleAscending);

        vector<double>::iterator it_sort = sort_points.begin();
        double points_player = totalPoints(player_index,turn);
        for (unsigned int i = 0; i<nbPlayer() ; i++,it_sort++)
        {
            if (*it_sort == points_player)
                return i+1;
        }
        return 0;
    }

    Player &Game::player(const unsigned int index)
    {
        if (index >= nbPlayer())
            throw OutOfRange(ustring::compose(_("Cannot access to the %1th player, there is only %2 player"),index+1,nbPlayer()));
        return *players_[index];
    }


    const Player &Game::player(const unsigned int index) const
    {
        if (index >= nbPlayer())
            throw OutOfRange(ustring::compose(_("Cannot access to the %1th player, there is only %2 player"),index+1,nbPlayer()));
        return *players_[index];
    }




    //
    // To ustring
    //
    ustring Game::toUstring() const
    {
        ustring str;
        unsigned int line_size=1;

        str = toUstringHeader();
        str += config_->toUstring() + "\n";
        str += toUstringDistributor() + "\n";
        str += toUstringNames(line_size,true);
        str += toUstringLine(line_size);
        str += toUstringAllPoints();
        str += toUstringLine(line_size);
        str += toUstringTotalPoints();
        str += toUstringLine(line_size);
        str += toUstringRanking();



        return str;
    }

    ustring Game::toUstringPoints() const
    {
        ustring str;
        unsigned int line_size=1;

        str = toUstringNames(line_size,true);
        str += toUstringLine(line_size);
        str += toUstringAllPoints();
        str += toUstringLine(line_size);
        str += toUstringNames(line_size);
        str += toUstringLine(line_size);
        str += toUstringTotalPoints();
        str += toUstringLine(line_size);
        str += toUstringRanking();
        str += toUstringDistributor();


        return str;
    }

    ustring Game::toUstringHeader() const
    {
        ustring str = _("Csu file\nCreated on the ") + dateUstring()
                    + _("\nFile's version: ") + versionUstring()
                    + _("\nMaximum size of the names: ") + sizeMaxNameUstring()
                    + _("\nNumber of players: ") + nbPlayerUstring()
                    + _("\nMaximum number of turns: ") + intToUstring(maxNbTurn()) + "\n";
        return str;
    }

    ustring Game::toUstringDistributor() const
    {
        ustring str;
        if (config_->useDistributor())
            str = distributorNameUstring() + _(" is the distributor\n");
        return str;
    }

    ustring Game::toUstringNames(unsigned int& line_size, const bool change_line_size) const
    {
        ustring str;
        int i;
        vector<Player*>::const_iterator it;

        //TRANSLATORS:The number of characters before the | must be eight
        str = _("Names   | ");

        for (it = players_.cbegin() ; it != players_.cend() ; it++)
        {
            ustring name((*it)->name());
            str += name;

            for (i=name.size() ; i < 4 ; i++)
            {
                str += " ";
                if (change_line_size)
                    line_size+=1;
            }

            str += " | ";

            if (change_line_size)
                line_size += name.size() + 3;
        }


        return str + "\n";
    }

    ustring Game::toUstringLine(const unsigned int line_size) const
    {
        ustring str = "\t";

        for (unsigned i=0 ; i<line_size ; i++)
            str+="-";

        return str + "\n";
    }

    ustring Game::toUstringAllPoints() const
    {
        ustring str;
        unsigned int i,j;
        vector<Player*>::const_iterator it;

        for (i=0 ; i<=maxNbTurn() ; i++)
        {
            //TRANSLATORS:The number of characters before the | and without the %1 must be six
            str += ustring::compose(_("Turn %1 |"),ustring::format(setw(2),i));

            for (it=players_.cbegin() ; it != players_.cend() ; it++)
            {
                if ((*it)->hasTurn(i))
                    str += (*it)->pointsUstring(*config_,i,6);
                else
                    str += "      ";

                for (j=4 ; j<(*it)->name().size(); j++)
                    str += " ";

                str += "|";
            }
            str += "\n";
        }

        return str;
    }

    ustring Game::toUstringTotalPoints() const
    {
        ustring str;
        unsigned int i;
        vector<Player*>::const_iterator it;


        //TRANSLATORS:The number of characters before the | must be eight
        str += _("Total   |");

        for (it = players_.cbegin() ; it != players_.cend() ; it++)
        {
            str += (*it)->totalPointsUstring(*config_,-1,6);

            for (i=4 ; i<(*it)->name().size(); i++)
                str += " ";

            str += "|";
        }

        return str + "\n";
    }

    ustring Game::toUstringRanking() const
    {
        ustring str;
        unsigned int i;
        vector<Player*>::const_iterator it;


        //TRANSLATORS:The number of characters before the | must be eight
        str += _("Ranking |");

        for (it = players_.cbegin() ; it != players_.cend() ; it++)
        {
            str += (*it)->rankingUstring(6);

            for (i=4 ; i<(*it)->name().size(); i++)
                str += " ";

            str += "|";
        }

        return str + "\n";
    }



    //
    // Function
    //
    unsigned int Game::maxNbTurn() const
    {
        unsigned int max_turn = 0;

        vector<Player*>::const_iterator it;
        for (it = players_.cbegin(); it != players_.cend() ; it++)
            max_turn = max(max_turn,(*it)->nbTurn());

        return max_turn;
    }

    unsigned int Game::getPlayerIndex(const ustring& player_name) const
    {
        for (unsigned int i=0 ; i<nb_player_ ; i++)
        {
            if (players_[i]->name().compare(0,player_name.size(),player_name) == 0)
                return i;
        }
        throw NotFound(ustring::compose(_("Player %1 is not found in the game."),player_name));
    }

    unsigned int Game::getPlayerIndex(const Player& player) const
    {
        for (unsigned int i=0 ; i<nb_player_ ; i++)
        {
            if (*players_[i] == player)
                return i;
        }
        throw NotFound(ustring::compose(_("Player %1 is not found in the game."),player.name()));
    }

    void Game::rankingCalculation()
    {
        vector<double> sort_points;
        vector<Player*>::iterator it_player;

        for (it_player=players_.begin() ; it_player != players_.end() ; it_player++)
            sort_points.push_back((*it_player)->totalPoints());

        // Sort the points base on the first way
        if (config().maxWinner())
            sort(sort_points.begin(),sort_points.end(),&compareDoubleDescending);
        else
            sort(sort_points.begin(),sort_points.end(),&compareDoubleAscending);

        vector<double>::reverse_iterator it_sort = sort_points.rbegin() ;
        // Loop on the sort points from the smallest
        for (int i = nbPlayer()-1 ; i>=0 ; i--,it_sort++)
        {
            // Loop on the total points
            for (it_player=players_.begin() ; it_player != players_.end() ; it_player++)
            {
                if (*it_sort == (*it_player)->totalPoints())
                    (*it_player)->setRanking(i+1);
            }
        }

    }

    bool Game::exceedMaxNumber() const
    {
        vector<Player*>::const_iterator it;
        for (it = players_.cbegin() ; it!=players_.cend() ; it++)
        {
            if (config().useMaximum())
            {
                if ((*it)->totalPoints() + DBL_EPSILON >= config().nbMaxMin())
                    return true;
            } else
            {
                if ((*it)->totalPoints() - DBL_EPSILON <= config().nbMaxMin())
                    return true;
            }
        }
        return false;
    }


    bool Game::newTurn(const unsigned int player_index, const double points)
    {
        if (config().turnBased())
            throw WrongUse(_("This new turn function should only be used in a non turn based game"));

        player(player_index).addPoints(points);

        rankingCalculation();
        increaseDistributor();
        return exceedMaxNumber();
    }


    bool Game::newTurn(const vector<double>& points)
    {
        if (!(config().turnBased()))
            throw WrongUse(_("The new turn function should only be used in a turn based game when a vector of points is given"));

        if (points.size() != nbPlayer())
            throw OutOfRange(ustring::compose(_("There is %1 points and %2 player in the game"),intToUstring(points.size()),nbPlayer()));

        vector<double>::const_iterator it_points = points.cbegin();
        vector<Player*>::iterator it_player = players_.begin();
        for (;it_points != points.cend() ; it_player++, it_points++)
            (*it_player)->addPoints(*it_points);

        rankingCalculation();
        increaseDistributor();
        return exceedMaxNumber();
    }


    bool Game::differentsPlayerNames() const
    {
        vector<Player*>::const_iterator it1,it2;
        unsigned int i=0;
        for (it1 = players_.cbegin() ; it1 != players_.cend() ; it1++, i++)
        {
            for (it2 = players_.cbegin() + i + 1 ; it2 != players_.cend() ; it2++)
            {
                if ((*it1)->name() == (*it2)->name())
                    return false;
            }
        }
        return true;
    }


    unsigned int Game::lastRanking(const unsigned int turn) const
    {
        if (!(config().turnBased()))
            throw WrongUse(_("The last ranking function should only be used in a turn based game when a specific turn is specified"));

        if (!(player(0).hasTurn(turn)))
            throw OutOfRange(ustring::compose(_("Cannot access to the %1th turn, there is only %2 turn"),turn,player(0).nbTurn()));


        vector<double> sort_points;
        vector<Player*>::const_iterator it_player;

        for (it_player=players_.cbegin() ; it_player != players_.cend() ; it_player++)
            sort_points.push_back((*it_player)->totalPoints(turn));


        // Sort the points base on the first way
        if (config().maxWinner())
            sort(sort_points.begin(),sort_points.end(),&compareDoubleDescending);
        else
            sort(sort_points.begin(),sort_points.end(),&compareDoubleAscending);


        vector<double>::reverse_iterator it_sort = sort_points.rbegin();
        vector<unsigned int> ranking(nbPlayer());
        vector<unsigned int>::iterator it_rank;
        // Loop on the sort points from the smallest
        for (int i = nbPlayer()-1 ; i>=0 ; i--,it_sort++)
        {
            // Loop on the total points
            for (it_player=players_.begin(), it_rank = ranking.begin() ; it_player != players_.end() ; it_player++, it_rank++)
            {
                if (*it_sort == (*it_player)->totalPoints(turn))
                    *it_rank = i+1;
            }
        }

        return *max_element(ranking.begin(),ranking.end());
    }


    bool Game::deleteTurn(const unsigned int turn)
    {
        if (!(config().turnBased()))
            throw WrongUse(_("The delete turn function should only be used in a turn based game when a player is specified"));

        if (!(player(0).hasTurn(turn)))
            throw OutOfRange(ustring::compose(_("Cannot access to the %1th turn, there is only %2 turn"),turn,player(0).nbTurn()));

        vector<Player*>::iterator it;
        for (it=players_.begin() ; it != players_.end() ; it++)
            (*it)->deleteTurn(turn);

        rankingCalculation();
        decreaseDistributor();
        return exceedMaxNumber();
    }



    bool Game::deleteTurn(const unsigned int turn, const unsigned int player_index)
    {
        if (config().turnBased())
            throw WrongUse(_("The delete turn function should only be used in a non turn based game when a player is specified"));

        if (!(player(player_index).hasTurn(turn)))
            throw OutOfRange(ustring::compose(_("Cannot access to the %1th turn, there is only %2 turn"),turn,player(player_index).nbTurn()));

        player(player_index).deleteTurn(turn);

        rankingCalculation();
        decreaseDistributor();
        return exceedMaxNumber();
    }

    bool Game::editTurn(const unsigned int turn, const std::vector<double>& points)
    {
        if (points.size() != nbPlayer())
            throw OutOfRange(ustring::compose(_("There is %1 points and %2 player in the game"),intToUstring(points.size()),nbPlayer()));

        vector<double>::const_iterator it_points = points.cbegin();
        vector<Player*>::iterator it_player = players_.begin();
        for (;it_points != points.cend() ; it_player++, it_points++)
        {
            if ((*it_player)->hasTurn(turn))
                (*it_player)->setPoints(turn,*it_points);
        }

        rankingCalculation();
        return exceedMaxNumber();
    }

    bool Game::editTurn(const unsigned int turn, const unsigned int player_index, const double points)
    {
        player(player_index).setPoints(turn,points);

        rankingCalculation();
        return exceedMaxNumber();
    }


    void Game::increaseDistributor()
    {
        if (distributor() == nbPlayer()-1)
            distributor_ = 0;
        else
            distributor_++;
    }


    void Game::decreaseDistributor()
    {
        if (distributor() == 0)
            distributor_ = nbPlayer()-1;
        else
            distributor_--;
    }

    vector<unsigned int> Game::playerIndexFromPosition() const
    {
        vector<unsigned int> index;

        vector<Player*>::const_iterator it;
        unsigned int j;
        for (unsigned int i=1 ; i<=nbPlayer() ; i++)
        {
            for (it = players_.cbegin(), j=0 ; it !=  players_.cend() ; it++,j++)
            {
                if (i == (*it)->ranking())
                    index.push_back(j);
            }
        }

        return index;
    }

    void Game::writeToFile(const Glib::ustring& filename) const
    {
        Document doc;
        Element* root = doc.create_root_node("csu");


        // Version
        Element* node_version = root->add_child("version");
        node_version->add_child_text(Ascii::dtostr(version_));

        // Size max of a name
        Element* node_size_max_name = root->add_child("size_max_name");
        node_size_max_name->add_child_text(Ascii::dtostr(sizeMaxName()));

        // Date
        Element *node_date = root->add_child("date");
        Element *node_year = node_date->add_child("year");
        node_year->add_child_text(date().format_string("%Y"));
        Element *node_month = node_date->add_child("month");
        node_month->add_child_text(date().format_string("%m"));
        Element *node_day = node_date->add_child("day");
        node_day->add_child_text(date().format_string("%d"));

        // Nb player
        Element* node_nb_player = root->add_child("nb_player");
        node_nb_player->add_child_text(Ascii::dtostr(nbPlayer()));

        // Distributor
        Element* node_distributor = root->add_child("distributor");
        node_distributor->add_child_text(Ascii::dtostr(distributor()));

        // Game config
        config().createXmlNode(root);

        // Players
        vector<Player*>::const_iterator it;
        for (it = players_.cbegin() ; it != players_.cend() ; it++)
            (*it)->createXmlNode(root,config());

        try
        {
            doc.write_to_file_formatted(filename,"UTF-8");
        }
        catch (xmlpp::exception& e)
        {
            cerr << e.what() << endl;
            throw FileError(ustring::compose(_("Error while writing the CSU file %1"),filename));
        }
    }

    void Game::reWriteToFile(const Glib::ustring& filename) const
    {
        ustring tmp_filename = filename + ".tmp";
        string locale_filename = locale_from_utf8(filename);
        string tmp_locale_filename = locale_from_utf8(tmp_filename);

        writeToFile(tmp_locale_filename);

        if (remove(locale_filename.c_str()) == -1)
            perror(locale_filename.c_str());

        if (rename(tmp_locale_filename.c_str(),locale_filename.c_str()) == -1)
        {
            if (remove(tmp_locale_filename.c_str()) == -1)
                perror("");

            throw FileError(_("Error while rewriting the file ") + locale_filename);
        }
    }


    //
    // Statistics
    //
    unsigned int Game::nbTurnBestWorst(const unsigned int player_index, const bool best) const
    {
        if (!(config().turnBased()))
            throw WrongUse(_("The nbTurnBestWorst function should only be used in a turn based game"));

        unsigned int nb=0;
        double points;

        unsigned int i;
        for (i=1 ; i<=nbTurn(0) ; i++)
        {
            if ((config().maxWinner() && best) || (!(config().maxWinner() || best)))
                points = -DBL_MAX;
            else
                points = DBL_MAX;

            vector<Player*>::const_iterator it;
            for (it = players_.cbegin() ; it != players_.cend() ; it++)
            {
                if ((config().maxWinner() && best) || (!(config().maxWinner() || best)))
                    points = max(points,(*it)->points(i));
                else
                    points = min(points,(*it)->points(i));
            }
            if (points == player(player_index).points(i))
                nb++;
        }

        return nb;
    }

    unsigned int Game::nbTurnFirstLast(const unsigned int player_index, const bool first) const
    {
        if (!(config().turnBased()))
            throw WrongUse(_("The nbTurnFirstLast function should only be used in a turn based game"));

        unsigned int nb=0,i;

        for (i=1 ; i<=nbTurn(0) ; i++)
        {
            unsigned int compare_rank;
            if (first)
                compare_rank = 1;
            else
                compare_rank = lastRanking(i);

            if (compare_rank == ranking(player_index,i))
                nb++;
        }

        return nb;
    }



    //
    // Export
    //
    void Game::exportToCsv(const Glib::ustring& filename) const
    {
        ofstream file;
        file.exceptions(ofstream::failbit | ofstream::badbit );
        try
        {
            file.open(locale_from_utf8(filename),ofstream::out);
        }
        catch (ios_base::failure& e)
        {
            throw FileError(_("Error while exporting the game into a csv file, bad filename: ") + filename);
        }

        vector<Player*>::const_iterator it;
        unsigned int i,j;

        // Header
        file << _("Csu file;") << endl
            << _("Created on the;") << dateUstring().raw() << ";" << endl
            << _("File's version;") << version() << ";" << endl
            << _("Maximum size of the names;") << sizeMaxName() << ";" << endl
            << _("Number of players;") << nbPlayer() << ";" << endl
            << _("Maximum number of turns;") << maxNbTurn() << ";" << endl;

        // Game configuration
        file << _("Name of the game configuration;") << config().name().raw() << ";" << endl
            << _("Use of a maximum score;") << config().useMaximumUstring().raw() << ";" << endl
            << _("Initial score;") << config().initialScore() << ";" << endl
            << _("Number of decimals displayed;") << config().decimalPlace() << ";" << endl
            << _("The first has the highest score;") << config().maxWinnerUstring().raw() << ";" << endl
            << _("Turn-based game;") << config().turnBasedUstring().raw() << ";" << endl
            << _("Use of a distributor;") << config().useDistributorUstring().raw() << ";" << endl
            << _("Maximum/minimum number of points;") << config().nbMaxMin() << ";" << endl << endl;


        // Statistics

        file << _("Names;");
        for (it = players_.cbegin() ; it != players_.cend() ; it++)
            file << (*it)->name().raw() << ";";

        file << endl << _("Mean points;");
        for (it = players_.cbegin() ; it != players_.cend() ; it++)
            file << (*it)->meanPoints() << ";";

        file << endl << _("Number of turn;");
        for (it = players_.cbegin() ; it != players_.cend() ; it++)
            file << (*it)->nbTurn() << ";";
        if (config().turnBased())
        {
            file << endl << _("Number of turn with the best score;");
            for (i=0 ; i < nbPlayer() ; i++)
                file << nbTurnBest(i) << ";";

            file << endl << _("Number of turn with the worst score;");
            for (i=0 ; i < nbPlayer() ; i++)
                file << nbTurnWorst(i) << ";";

            file << endl << _("Number of turn first;");
            for (i=0 ; i < nbPlayer() ; i++)
                file << nbTurnFirst(i) << ";";

            file << endl << _("Number of turn last;");
            for (i=0 ; i < nbPlayer() ; i++)
                file << nbTurnLast(i) << ";";
        }

        // Points
        file << endl << endl << _("Names");
        for (it = players_.cbegin() ; it != players_.cend() ; it++)
            file << ";;" << (*it)->name().raw() << ";";

        file << endl << _("Legend;");
        for (i=0 ; i < nbPlayer() ; i++)
            file << _("Points in the turn;Points;Ranking;");

        for (i=0 ; i <= maxNbTurn() ; i++)
        {
            file << endl << _("Turn ") << i << ";";
            for (j=0 ; j<nbPlayer() ; j++)
            {
                if (player(j).hasTurn(i))
                {
                    file << points(j,i) << ";" << totalPoints(j,i) << ";";
                    if (config().turnBased())
                        file << ranking(j,i);
                    file << ";";
                }
                else
                    file << ";;;";
            }
        }


        // Conclusion


        file << endl << endl << _("Names;");
        for (it = players_.cbegin() ; it != players_.cend() ; it++)
            file << (*it)->name().raw() << ";";

        file << endl << _("Total points;");
        for (it = players_.cbegin() ; it != players_.cend() ; it++)
            file << (*it)->totalPoints() << ";";

        file << endl << _("Ranking;");
        for (it = players_.cbegin() ; it != players_.cend() ; it++)
            file << (*it)->ranking() << ";";


        file.close();
    }

    void Game::exportToM(const Glib::ustring& filename) const
    {
        ofstream file;
        file.exceptions(ofstream::failbit | ofstream::badbit );
        try
        {
            file.open(locale_from_utf8(filename),ofstream::out);
        }
        catch (ios_base::failure& e)
        {
            throw FileError(_("Error while exporting the game into a m file, bad filename: ") + filename);
        }

        vector<Player*>::const_iterator it;
        unsigned int i, tabs_name;

        file << "clear all;" << endl << "close all;" << endl ;


        // x for players
        for (it = players_.cbegin(), tabs_name=0 ; it != players_.cend() ; it++, tabs_name++)
            file << endl << "turn_" << tabs_name << "=0:1:" << (*it)->nbTurn() << ";";
        file << endl;


        // Tabs of total points
        for (it = players_.cbegin(), tabs_name=0 ; it != players_.cend() ; it++, tabs_name++)
        {
            file << endl << "total_points_" << tabs_name << "=[";
            for (i=0 ; i<=maxNbTurn() ; i++)
            {
                if ((*it)->hasTurn(i))
                    file << replaceCharacterInUstring((*it)->totalPointsUstring(config(),i),',','.').raw() << ",";
                else
                    break;
            }
            file << "];";
        }


        // Plot total points
        file << endl << "plot(";
        for (tabs_name=0 ; tabs_name<nbPlayer() ; tabs_name++)
        {
            file << "turn_" << tabs_name << ",total_points_" << tabs_name;
            if (tabs_name != nbPlayer()-1)
                file << ",";
        }
        file << ");" << endl
            << "title('" << _("Total points") << "');" << endl
            << "xlabel('" << _("Turn") << "');" << endl
            << "ylabel('" << _("Points") << "');" << endl;


        file << "legend(";
        for (it=players_.cbegin(), tabs_name=0 ; tabs_name<nbPlayer() ; tabs_name++, it++)
        {
            file << "'" << (*it)->nameUstring().raw() << "'";
            if (tabs_name != nbPlayer()-1)
                file << ",";
        }
        file << ");" << endl;


        // Tabs of points and mean points
        for (it = players_.cbegin(), tabs_name=0 ; it != players_.cend() ; it++, tabs_name++)
        {
            file << endl << "points_" << tabs_name << "=[";
            for (i=0 ; i<=maxNbTurn() ; i++)
            {
                if ((*it)->hasTurn(i))
                    file << replaceCharacterInUstring((*it)->pointsUstring(config(),i),',','.').raw() << ",";
                else
                    break;
            }
            file << "];" << endl
                << "fprintf('" << ustring::compose(_("Mean score of %1: "),(*it)->name()).raw()
                << "%f\\n',mean(points_" << tabs_name << "));";

        }


        // Plot points
        file << endl << endl << "figure;" << endl << "plot(";
        for (tabs_name=0 ; tabs_name<nbPlayer() ; tabs_name++)
        {
            file << "turn_" << tabs_name << ",points_" << tabs_name;
            if (tabs_name != nbPlayer()-1)
                file << ",";
        }
        file << ");" << endl
            << "title('" << _("Points") << "');" << endl
            << "xlabel('" << _("Turn") << "');" << endl
            << "ylabel('" << _("Points") << "');" << endl;


        file << "legend(";
        for (it=players_.cbegin(), tabs_name=0 ; tabs_name<nbPlayer() ; tabs_name++, it++)
        {
            file << "'" << (*it)->nameUstring().raw() << "'";
            if (tabs_name != nbPlayer()-1)
                file << ",";
        }
        file << ");" << endl;


        file.close();
    }

    void Game::exportToGnuplotData(const Glib::ustring& filename) const
    {
        ofstream file;
        file.exceptions(ofstream::failbit | ofstream::badbit );
        try
        {
            file.open(locale_from_utf8(filename+".dat"),ofstream::out);
        }
        catch (ios_base::failure& e)
        {
            throw FileError(_("Error while exporting the game into a m file, bad filename: ") + filename);
        }

        vector<Player*>::const_iterator it;
        unsigned int i;

        file << "\"" << _("Players") << "\"";
        for (it=players_.cbegin() ; it != players_.cend() ; it++)
            file << "\t\"" << (*it)->name().raw() << "\"";

        for (i=0; i<= maxNbTurn() ; i++)
        {
            file << endl << i;
            for (it=players_.cbegin() ; it != players_.cend() ; it++)
            {
                if ((*it)->hasTurn(i))
                    file << "\t" << replaceCharacterInUstring((*it)->totalPointsUstring(config(),i),',','.').raw();
                else
                    file << "\t-";
            }
        }


        file.close();
    }

    void Game::exportToGnuplotScript(const Glib::ustring& filename) const
    {
        ofstream file;
        file.exceptions(ofstream::failbit | ofstream::badbit );
        try
        {
            file.open(locale_from_utf8(filename+".plt"),ofstream::out);
        }
        catch (ios_base::failure& e)
        {
            throw FileError(_("Error while exporting the game into a m file, bad filename: ") + filename);
        }

        file << "set datafile missing '-'" << endl
            << "set style data linespoints" << endl
            << "set xlabel \"" << _("Number of turns") << "\"" << endl
            << "set ylabel \"" << _("Points") << "\"" << endl
            << "set title \"" << _("Points on ") << Glib::path_get_basename(filename) << "\"" << endl;

        file << "plot '" << Glib::path_get_basename(filename) << ".dat" << "' using 2:xtic(1) title columnheader(2),"
            << " for [i=3:" << (nbPlayer() + 1)
            << "] '' using i title columnheader(i)" << endl << "pause -1";


        file.close();
    }

    void Game::exportToGnuplot(const Glib::ustring& filename) const
    {
        exportToGnuplotData(filename);
        exportToGnuplotScript(filename);
    }

    void Game::exportToPdf(const Glib::ustring& filename, const ExportPdfPreferences& pdf_pref, const ChartExportationPreferences& chart_pref) const
    {
        // Save the temporary file
        try
        {
            PdfExportation::exportToPdf(this,pdf_pref,chart_pref,filename);
        }
        catch (Glib::Exception& e)
        {
            cerr << e.what() << endl;

            throw PdfError(ustring::compose(_("The file %1 cannot be created"),filename));
        }
    }

    void Game::exportToChart(const Glib::ustring& filename, const ChartExportationPreferences& chart_pref, const ExportPdfPreferences pdf_pref, const ChartExportationType type)  const
    {
        ustring title = path_get_basename(filename);
        removeFileExtension(title);
        if (chart_pref.totalPoints())
            title = _("Total points on ") + title;
        else
            title = _("Points on ") + title;

        char fmt[4] = "b+-";
        unsigned int i,j;

        slope_figure_t* slope_chart = slope_chart_create(title.c_str(), _("Turn"), _("Points"));

        double* slope_turn = new double[maxNbTurn()];
        double** slope_points = new double*[nbPlayer()];

        for (i=0 ; i<maxNbTurn() ; i++)
            slope_turn[i]=i;

        // Create the slope chart
        vector<Player*>::const_iterator it;
        for (i=0, it = players_.cbegin(); it != players_.cend() ; it++, i++)
        {
            if (!(chart_pref.totalPoints()))
            {
                slope_points[i] = (*it)->points_.data();
            }
            else
            {
                slope_points[i] = new double[(*it)->nbTurn()+1];
                for (j=0 ; j != nbTurn(i); j++)
                    slope_points[i][j] = (*it)->totalPoints(j);
            }
            slope_chart_add_plot(slope_chart,
                                 slope_turn,
                                 slope_points[i],
                                 (*it)->nbTurn(),
                                 (*it)->name().c_str(),
                                 fmt);
            // Change the color
            switch(fmt[0])
            {
            case 'b':
                fmt[0] = 'r';
                break;
            case 'r':
                fmt[0] = 'o';
                break;
            case 'o':
                fmt[0] = 'l';
                break;
            case 'l':
                fmt[0] = 'm';
                break;
            case 'm':
                fmt[0] = 'p';
                break;
            case 'p':
                fmt[0] = 'y';
                break;
            case 'y':
                fmt[0] = 'e';
                break;
            case 'e':
                fmt[0] = 'g';
                break;
            case 'g':
                fmt[0] = 'a';
                break;
            case 'a':
                fmt[0] = 't';
                break;
            case 't':
                fmt[0] = 'b';
                break;
            }
        }


        // Save the chart
        int res = SLOPE_SUCCESS;
        int width;
        int height;
        string locale_filename = locale_from_utf8(filename);
        switch (static_cast<int>(type))
        {
        case SVG:
            res = slope_figure_write_to_svg(slope_chart,locale_filename.c_str(),chart_pref.width(),chart_pref.height());
            break;
        case PNG:
            res = slope_figure_write_to_png(slope_chart,locale_filename.c_str(),chart_pref.width(),chart_pref.height());
            break;
        case PDF:
            if (pdf_pref.pdfSizeForChart())
            {
                switch (static_cast<int>(pdf_pref.size()))
                {
                case ExportPdfPreferences::A3:
                    width = 842;
                    height = 1190;
                    break;
                case ExportPdfPreferences::A4:
                    width = 595;
                    height = 842;
                    break;
                case ExportPdfPreferences::A5:
                    width = 420;
                    height = 595;
                    break;
                default:
                    width = 0;
                    height = 0;
                    break;
                }
                if (pdf_pref.direction() == ExportPdfPreferences::LANDSCAPE)
                {
                    int tmp = width;
                    width = height;
                    height = tmp;
                }
            }
            else
            {
                width = chart_pref.width();
                height = chart_pref.height();
            }
            res = slope_figure_write_to_pdf(slope_chart,locale_filename.c_str(),width,height);
            break;
        }

        // Delete
        delete[] slope_turn;
        if (chart_pref.totalPoints())
        {
            for (i=0 ; i<nbPlayer(); i++)
                delete[] slope_points[i];
        }
        delete[] slope_points;
        slope_chart_destroy(slope_chart);

        if (res != SLOPE_SUCCESS)
            throw PdfError(_("Error while exporting the game into chart file, bad filename"));
    }

}
