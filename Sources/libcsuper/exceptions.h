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

namespace csuper
{
    /*! \class xmlError
    *   \brief This class represent a xml error
    */
    class xmlError : public std::runtime_error
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param what_arg the string of the error
         */
        xmlError(const std::string& what_arg);
    };


    /*! \class alreadyExist
    *   \brief This class represent an already exist error
    */
    class alreadyExist : public std::runtime_error
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param what_arg the string of the error
         */
        alreadyExist(const std::string& what_arg);
    };

    /*! \class notFound
    *   \brief This class represent a not found error
    */
    class notFound : public std::runtime_error
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param what_arg the string of the error
         */
        notFound(const std::string& what_arg);
    };

    /*! \class fileError
    *   \brief This class represent a not file error
    */
    class fileError : public std::runtime_error
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param what_arg the string of the error
         */
        fileError(const std::string& what_arg);
    };

    /*! \class pdfError
    *   \brief This class represent a pdf error
    */
    class pdfError : public std::runtime_error
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param what_arg the string of the error
         */
        pdfError(const std::string& what_arg);
    };

    /*! \class wrongUse
    *   \brief This class represent a error when a function is called when it would'n be
    */
    class wrongUse : public std::logic_error
    {
    public:
        /*!
         *  \brief Constructor with the string parameter
         *  \param what_arg the string of the error
         */
        wrongUse(const std::string& what_arg);
    };
}


#endif // EXCEPTIONS_H_INCLUDED
