/*!
 * \file    command_line_option.h
 * \brief   Begin csuper
 * \author  Remi BERTHO
 * \date    14/06/15
 * \version 4.3.0
 */

/*
 * command_line_option.h
 *
 * Copyright 2014-2015 Remi BERTHO <remi.bertho@openmailbox.org>
 *
 * This file is part of Csuper-cli.
 *
 * Csuper-cli is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper-cli is distributed in the hope that it will be useful,
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

#ifndef COMMAND_LINE_OPTION_H_INCLUDED
#define COMMAND_LINE_OPTION_H_INCLUDED

#include <glibmm.h>

/*! \class CommandLineOption
*   \brief This class is used to retrieve the command line option
*/
class CommandLineOption
{
private:
    Glib::OptionContext context_;           /*!< The context */

    Glib::OptionGroup filename_group_;      /*!< The filename group */
    Glib::OptionGroup instruction_group_;   /*!< The instruction group */

    Glib::OptionEntry open_entry_;          /*!< The open entry */
    Glib::OptionEntry read_entry_;          /*!< The read entry */
    Glib::OptionEntry pdf_entry_;           /*!< The export to pdf entry */
    Glib::OptionEntry csv_entry_;           /*!< The export to csv entry */
    Glib::OptionEntry m_entry_;             /*!< The export to m entry */
    Glib::OptionEntry gnuplot_entry_;       /*!< The export to gnuplot entry */
    Glib::OptionEntry png_entry_;           /*!< The export to png entry */
    Glib::OptionEntry svg_entry_;           /*!< The export to svg entry */

    Glib::OptionEntry input_entry_;         /*!< The input filename entry */
    Glib::OptionEntry output_entry_;        /*!< The output filename entry */

    bool open_ = false;                     /*!< Check if the open option is used */
    bool read_ = false;                     /*!< Check if the read option is used */
    bool pdf_ = false;                      /*!< Check if the pdf option is used */
    bool csv_ = false;                      /*!< Check if the csv option is used */
    bool m_ = false;                        /*!< Check if the m option is used */
    bool png_ = false;                      /*!< Check if the png option is used */
    bool svg_ = false;                      /*!< Check if the svg option is used */
    bool gnuplot_ = false;                  /*!< Check if the gnuplot option is used */
    std::string input_ = "";                /*!< The input filename */
    std::string output_ = "";               /*!< The output filename */

public:
    /*!
     *  \brief Constructor
     */
    CommandLineOption();


    enum Instruction
    {
        READ_FILE,
        OPEN_FILE,
        EXPORT_TO_PDF,
        EXPORT_TO_M,
        EXPORT_TO_CSV,
        EXPORT_TO_GNUPLOT,
        EXPORT_TO_PNG,
        EXPORT_TO_SVG,
        RUN
    };


    /*!
     *  \brief Parses the command line arguments.
        Call exit(1) if error.
        Print the help and do exit(0) if ask in the arguments
     *  \param argc A pointer to the number of command line arguments
     *  \param argv A pointer to the array of command line arguments
     *  \return the instruction
     */
    Instruction parse(int& argc, char**& argv);


    /*!
     *  \brief Get the input filename
     *  \return the input filename
     */
    inline Glib::ustring input() const
    {
        return Glib::filename_to_utf8(input_);
    }

    /*!
     *  \brief Get the output filename
     *  \return the output filename
     */
    inline Glib::ustring output() const
    {
        return Glib::filename_to_utf8(output_);
    }
};


#endif // COMMAND_LINE_OPTION_H_INCLUDED
