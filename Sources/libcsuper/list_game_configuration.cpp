/*!
 * \file    list_game_configuration.cpp
 * \author  Remi BERTHO
 * \date    25/05/15
 * \version 4.3.0
 */

/*
* list_game_configuration.cpp
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

#include "list_game_configuration.h"
#include "exceptions.h"
#include <iostream>
#include "config.h"

using namespace std;
using namespace Glib;
using namespace xmlpp;

namespace csuper
{
    double ListGameConfiguration::version_(1.0);

    ListGameConfiguration::ListGameConfiguration()
    {

    }

    ListGameConfiguration::ListGameConfiguration(const ustring& filename)
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
        if (node->get_name() != "csu_game_configuration")
            throw XmlError(ustring::compose(_("This file is not a CSU game configuration file, it's a %1 file."),node->get_name()));

        firstChildXmlElement(node);

        // Version
        double file_version = ustringToDouble(static_cast<Element*>(node)->get_child_text()->get_content());
        if (file_version > version_)
            throw XmlError(ustring::compose(_("This version of Csuper only support game configuration file version less than or equal to %1."),version_));

        // Number of game configurations
        nextXmlElement(node);
        int nb_game_config = ustringToDouble(static_cast<Element*>(node)->get_child_text()->get_content());

        // Get all game configuration
        for (int i=0 ; i< nb_game_config ; i++)
        {
            nextXmlElement(node);
            game_configuration_list_.push_back(new GameConfiguration(node));
        }
    }


    ListGameConfiguration::ListGameConfiguration(const ListGameConfiguration &list_game_config)
    {
        for (auto it = list_game_config.game_configuration_list_.cbegin() ; it != list_game_config.game_configuration_list_.cend() ; it++)
            game_configuration_list_.push_back(new GameConfiguration(**it));
    }


    ListGameConfiguration::~ListGameConfiguration()
    {
        for (auto it = game_configuration_list_.begin() ; it != game_configuration_list_.end() ; it++)
            delete *it;

        game_configuration_list_.clear();
    }



    const GameConfiguration &ListGameConfiguration::operator[](unsigned int i) const
    {
        if (i >= size())
            throw OutOfRange(ustring::compose(_("Cannot access to the %1th element, there is only %2 elements"),i+1,size()));
        return *game_configuration_list_[i];
    }

    GameConfiguration &ListGameConfiguration::operator[](unsigned int i)
    {
        if (i >= size())
            throw OutOfRange(ustring::compose(_("Cannot access to the %1th element, there is only %2 elements"),i+1,size()));
        return *game_configuration_list_[i];
    }

    unsigned int ListGameConfiguration::size() const
    {
        return game_configuration_list_.size();
    }


    ListGameConfiguration &ListGameConfiguration::operator=(const ListGameConfiguration &list_game_config)
    {
        if (this==&list_game_config)
            return *this;


        vector<GameConfiguration*>::const_iterator it;
        for (it = game_configuration_list_.cbegin() ; it != game_configuration_list_.cend() ; it++)
            delete *it;
        game_configuration_list_.clear();


        for (it = list_game_config.game_configuration_list_.cbegin() ; it != list_game_config.game_configuration_list_.cend() ; it++)
            game_configuration_list_.push_back(new GameConfiguration(**it));

        return *this;
    }


    void ListGameConfiguration::add(GameConfiguration* game_config)
    {
        for (auto it = game_configuration_list_.begin() ; it != game_configuration_list_.end() ; it++)
        {
            if (*game_config == **it)
                throw AlreadyExist(game_config->name());
        }
        game_configuration_list_.push_back(game_config);
    }

    void ListGameConfiguration::add(const GameConfiguration& game_config)
    {
        for (auto it = game_configuration_list_.begin() ; it != game_configuration_list_.end() ; it++)
        {
            if (game_config == **it)
                throw AlreadyExist(game_config.name());
        }
        game_configuration_list_.push_back(new GameConfiguration(game_config));
    }

    void ListGameConfiguration::add(const ListGameConfiguration& list_game_config)
    {
        for (auto it = list_game_config.game_configuration_list_.cbegin() ; it != list_game_config.game_configuration_list_.cend() ; it++)
        {
            GameConfiguration* tmp_game_config = new GameConfiguration(**it);
            try
            {
                add(tmp_game_config);
            }
            catch(AlreadyExist& e)
            {
                cerr << e.what() << endl;
                delete tmp_game_config;
            }
        }
    }

    void ListGameConfiguration::add(const ListGameConfiguration& list_game_config,const vector<unsigned int>& indexes)
    {
        unsigned int i=0;
        bool found;

        for (auto it = list_game_config.game_configuration_list_.cbegin() ; it != list_game_config.game_configuration_list_.cend() ; it++)
        {
            found = false;
            for (auto it_index=indexes.cbegin() ; it_index != indexes.cend() ; it_index++)
            {
                if (*it_index == i)
                {
                    found = true;
                    break;
                }
            }

            if (found)
            {
                GameConfiguration* tmp_game_config = new GameConfiguration(**it);
                try
                {
                    add(tmp_game_config);
                }
                catch(AlreadyExist& e)
                {
                    cerr << e.what() << endl;
                    delete tmp_game_config;
                }
            }

            i++;
        }
    }


    void ListGameConfiguration::remove(const unsigned int i)
    {
        if (i >= size())
            throw OutOfRange(ustring::compose(_("Cannot remove the %1th element, there is only %2 elements"),i+1,size()));

        delete game_configuration_list_[i];
        game_configuration_list_.erase(game_configuration_list_.begin()+i);
    }

    void ListGameConfiguration::remove(const GameConfiguration& game_config)
    {
        for (auto it = game_configuration_list_.begin() ; it != game_configuration_list_.end() ; it++)
        {
            if (**it == game_config)
            {
                delete *it;
                game_configuration_list_.erase(it);
                return;
            }
        }
        throw NotFound(ustring::compose(_("The game configuration %1 was not found in the list of game configuration"),game_config.name()));
    }

    ustring ListGameConfiguration::toUstring() const
    {
        ustring str("");

        for (auto it = game_configuration_list_.cbegin() ; it != game_configuration_list_.cend() ; it++)
            str += ((*it)->toUstring() + "\n\n");

        return str;
    }

    ustring ListGameConfiguration::toUstringName() const
    {
        ustring str("");
        unsigned int i=1;

        for (auto it = game_configuration_list_.cbegin() ; it != game_configuration_list_.cend() ; it++, i++)
            str += ustring::compose(" (%1) %2\n",i,(*it)->nameUstring()); //(" - " + (*it)->nameUstring() + "\n");

        return str;
    }

    ostream& operator<<(ostream& os, const ListGameConfiguration& list_game_config)
    {
        os << list_game_config.toUstring() << endl;
        return os;
    }


    void ListGameConfiguration::writeToFile(const ustring filename) const
    {
        Document doc;
        Element* root = doc.create_root_node("csu_game_configuration");

        // Version
        Element* node_version = root->add_child("version");
        node_version->add_child_text(Ascii::dtostr(version_));

        // Number of game configuration
        Element* node_nb = root->add_child("nb_game_config");
        node_nb->add_child_text(Ascii::dtostr(size()));

        for (auto it = game_configuration_list_.cbegin() ; it != game_configuration_list_.cend() ; it++)
            (*it)->createXmlNode(root);

        try
        {
            doc.write_to_file_formatted(filename,"UTF-8");
        }
        catch (xmlpp::exception& e)
        {
            cerr << e.what() << endl;
            throw FileError(ustring::compose(_("Error while writing the list of game configuration file %1"),filename));
        }
    }

    void ListGameConfiguration::writeToFile(const ustring filename, const std::vector<unsigned int>& indexes) const
    {
        Document doc;
        Element* root = doc.create_root_node("csu_game_configuration");

        // Version
        Element* node_version = root->add_child("version");
        node_version->add_child_text(Ascii::dtostr(version_));

        // Number of game configuration
        Element* node_nb = root->add_child("nb_game_config");
        node_nb->add_child_text(Ascii::dtostr(indexes.size()));

        unsigned int i=0;
        for (auto it = game_configuration_list_.cbegin() ; it != game_configuration_list_.cend() ; it++)
        {
            for (auto it_index=indexes.cbegin() ; it_index != indexes.cend() ; it_index++)
            {
                if (*it_index == i)
                {
                    (*it)->createXmlNode(root);
                    break;
                }
            }
            i++;
        }

        try
        {
            doc.write_to_file_formatted(filename,"UTF-8");
        }
        catch (xmlpp::exception& e)
        {
            cerr << e.what() << endl;
            throw FileError(ustring::compose(_("Error while writing the list of game configuration file %1"),filename));
        }
    }

    void ListGameConfiguration::writeToFile() const
    {
        ustring filename;
        if (Portable::getPortable())
            filename = build_filename(CSUPER_DIRECTORY_NAME,CSUPER_GAME_CONFIGURATIONS_FILENAME);
        else
            filename = build_filename(locale_to_utf8(get_home_dir()),CSUPER_DIRECTORY_NAME,CSUPER_GAME_CONFIGURATIONS_FILENAME);

        writeToFile(filename);
    }

    ListGameConfiguration *ListGameConfiguration::getMainList()
    {
        string filename;
        if (Portable::getPortable())
            filename = build_filename(CSUPER_DIRECTORY_NAME,CSUPER_GAME_CONFIGURATIONS_FILENAME);
        else
            filename = build_filename(get_home_dir(),CSUPER_DIRECTORY_NAME,CSUPER_GAME_CONFIGURATIONS_FILENAME);

        return new ListGameConfiguration(filename);
    }
}
