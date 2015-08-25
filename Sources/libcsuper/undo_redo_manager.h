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

#ifndef UNDO_REDO_MANAGER_H_INCLUDED
#define UNDO_REDO_MANAGER_H_INCLUDED

#include <deque>
#include "game.h"


namespace csuper
{
   /*! \class UndoRedoManager
    *   \brief This class is a undo redo manager
    */
    class UndoRedoManager
    {
    private:
        std::deque<Game*> last_game_;  /*!< The last games */
        unsigned int index_ = 0;        /*!< The index of the last game used */

    public:
        //
        // Constructor and destructor
        //
        /*!
         *  \brief Default constructor
         */
        UndoRedoManager();

        /*!
         *  \brief Copy constructor
         */
        UndoRedoManager(const UndoRedoManager &undo_redo_manager);

        /*!
         *  \brief Destructor
         */
        ~UndoRedoManager();


        //
        // Function
        //
        /*!
         *  \brief operator =
         *  \param undo_redo_manager a UndoRedoManager
         *  \return a reference to the object
         */
        UndoRedoManager &operator=(const UndoRedoManager &undo_redo_manager);


        /*!
         *  \brief Test if the user can do an undo or not
         *  \return true if the user can undo, false otherwise
         */
        bool canUndo() const;


        /*!
         *  \brief Test if the user can do an redo or not
         *  \return true if the user can redo, false otherwise
         */
        bool canRedo() const;


        /*!
         *  \brief Clear all the Games
         */
        void clear();


        /*!
         *  \brief Add a game
         *  \param true if the user can redo, false otherwise
         */
        void add(const Game* const game);


        /*!
         *  \brief Retrieve the last game used
         *  \param The last game, must be free by the user
         *  \exception csuper::UndoRedoError if you cannot undo
         */
        Game *undo();


        /*!
         *  \brief Retrieve the last game used
         *  \param The game, must be free by the user
         *  \exception csuper::UndoRedoError if you cannot redo
         */
        Game *redo();

    };
}

#endif // UNDO_REDO_MANAGER_H_INCLUDED
