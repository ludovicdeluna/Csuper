/*!
 * \file    csu_widget.h
 * \author  Remi BERTHO
 * \date    28/07/15
 * \version 4.3.0
 */

/*
 * csu_widget.h
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


#ifndef CSU_WIDGET_H_INCLUDED
#define CSU_WIDGET_H_INCLUDED

class CsuApplication;

/*! \class CsuWidget
*   \brief This class is a CsuWidget
*/
class CsuWidget
{
private:
    static CsuApplication* app_; /*!< The CsuApplication */

protected:
    /*!
     *  \brief return the application
     *  \return the application
     */
    inline CsuApplication* app() const
    {
        return app_;
    }

public:
    /*!
     *  \brief Set the application
     *  \param app the application
     */
    static void setApp(CsuApplication* app);
};


#endif // CSU_WIDGET_H_INCLUDED
