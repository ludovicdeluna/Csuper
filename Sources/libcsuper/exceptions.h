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

#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <exception>
#include <stdexcept>
#include <string>
#include <glibmm.h>

namespace csuper
{
    /*! \class Exception
    *   \brief This class represent a csuper Exception
    */
    class Exception : public Glib::Exception
    {
    private:
        Glib::ustring msg_;

    public:
        /*!
         *  \brief Constructor with the ustring parameter
         *  \param msg the message
         */
        Exception(const Glib::ustring msg);

        /*!
         *  \brief Return the message
         *  \return msg the message
         */
        virtual Glib::ustring what() const;
    };





    /*! \class XmlError
    *   \brief This class represent a xml error
    */
    class XmlError : public Exception
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param msg the string of the error
         */
        XmlError(const Glib::ustring& msg);
    };





    /*! \class AlreadyExist
    *   \brief This class represent an already exist error
    */
    class AlreadyExist : public Exception
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param msg the string of the error
         */
        AlreadyExist(const Glib::ustring& msg);
    };





    /*! \class NotFound
    *   \brief This class represent a not found error
    */
    class NotFound : public Exception
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param msg the string of the error
         */
        NotFound(const Glib::ustring& msg);
    };





    /*! \class FileError
    *   \brief This class represent a file error
    */
    class FileError : public Exception
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param msg the string of the error
         */
        FileError(const Glib::ustring& msg);
    };





    /*! \class PdfError
    *   \brief This class represent a pdf error
    */
    class PdfError : public Exception
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param msg the string of the error
         */
        PdfError(const Glib::ustring& msg);
    };





    /*! \class WrongUse
    *   \brief This class represent a error when a function is called when it would'n be
    */
    class WrongUse : public Exception
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param msg the string of the error
         */
        WrongUse(const Glib::ustring& msg);
    };





    /*! \class WrongUse
    *   \brief This class represent a error when calculating
    */
    class CalculatorError : public Exception
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param msg the string of the error
         */
        CalculatorError(const Glib::ustring& msg);
    };





    /*! \class OutOfRange
    *   \brief This class represent a error when the is an out of range
    */
    class OutOfRange : public Exception
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param msg the string of the error
         */
        OutOfRange(const Glib::ustring& msg);
    };





    /*! \class UndoRedoError
    *   \brief This class represent a error on the UndoRedoManager
    */
    class UndoRedoError : public Exception
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param msg the string of the error
         */
        UndoRedoError(const Glib::ustring& msg);
    };
}


#endif // EXCEPTIONS_H_INCLUDED
