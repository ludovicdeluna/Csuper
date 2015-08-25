/*!
 * \file    undo_redo_manager.h
 * \author  Remi BERTHO
 * \date    21/08/15
 * \version 4.3.0
 */

/*
 * undo_redo_manager.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-gtk.
 *
 * Csuper-gtk is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-gtk is distributed in the hope that it will be useful,
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

#include "undo_redo_manager.h"
#include "exceptions.h"
#include "config.h"

using namespace std;


namespace csuper
{
    //
    // Constructor and destructor
    //
    UndoRedoManager::UndoRedoManager()
    {

    }

    UndoRedoManager::UndoRedoManager(const UndoRedoManager& undo_redo_manager)
    {
        for (auto& it : last_game_)
            last_game_.push_back(new Game(*it));

        index_ = undo_redo_manager.index_;
    }


    UndoRedoManager::~UndoRedoManager()
    {
        for (auto& it : last_game_)
            delete it;
    }


    //
    // Function
    //
    UndoRedoManager &UndoRedoManager::operator=(const UndoRedoManager &undo_redo_manager)
    {
        for (auto& it : last_game_)
            delete it;

        last_game_.clear();

        for (auto& it : last_game_)
            last_game_.push_back(new Game(*it));

        index_ = undo_redo_manager.index_;

        return *this;
    }


    bool UndoRedoManager::canUndo() const
    {
        return ((index_ + 1) < last_game_.size());
    }


    bool UndoRedoManager::canRedo() const
    {
        return (index_ > 0);
    }

    void UndoRedoManager::clear()
    {
        for (auto& it : last_game_)
            delete it;

        last_game_.clear();

        index_ = 0;
    }

    void UndoRedoManager::add(const Game* const game)
    {
        // Delete the last redo available
        for (unsigned int i=0 ; i < index_ ; i++)
        {
            delete last_game_[0];
            last_game_.pop_front();
        }
        index_ = 0;

        last_game_.push_front(new Game(*game));
    }

    Game *UndoRedoManager::undo()
    {
        if (!(canUndo()))
            throw UndoRedoError(_("You cannot undo, there is no previous game."));

        index_++;
        return (new Game (*last_game_[index_]));
    }

    Game *UndoRedoManager::redo()
    {
        if (!(canRedo()))
            throw UndoRedoError(_("You cannot redo, there is no previous game."));

        index_--;
        return (new Game (*last_game_[index_]));
    }
}

