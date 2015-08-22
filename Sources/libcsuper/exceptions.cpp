/*!
 * \file    exceptions.h
 * \brief   Exceptions of Csuper
 * \author  Remi BERTHO
 * \date    25/05/14
 * \version 4.3.0
 */

/*
* exceptions.h
*
* Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
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

#include "exceptions.h"
#include "config.h"

using namespace std;
using namespace Glib;

namespace csuper
{
    Exception::Exception(const ustring msg) : Glib::Exception(), msg_(msg)
    {

    }

    ustring Exception::what() const
    {
        return msg_;
    }



    XmlError::XmlError(const ustring& msg) : Exception(_("XML Error: ") + msg)
    {

    }



    AlreadyExist::AlreadyExist(const ustring& msg) : Exception(_("Already exist: ") + msg)
    {

    }



    NotFound::NotFound(const ustring& msg) : Exception(_("Not found: ") + msg)
    {

    }



    FileError::FileError(const ustring& msg) : Exception(_("File error: ") + msg)
    {

    }



    PdfError::PdfError(const ustring& msg) : Exception(_("PDF error: ") + msg)
    {

    }



    WrongUse::WrongUse(const ustring& msg) : Exception(_("Wrong use: ") + msg)
    {

    }



    CalculatorError::CalculatorError(const ustring& msg) : Exception(_("Calculator error: ") + msg)
    {

    }



    OutOfRange::OutOfRange(const ustring& msg) : Exception(_("Out of range: ") + msg)
    {

    }



    UndoRedoError::UndoRedoError(const ustring& msg) : Exception(_("Undo redo error: ") + msg)
    {

    }
}
