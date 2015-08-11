/*!
 * \file    command_line_option.cpp
 * \brief   Begin csuper
 * \author  Remi BERTHO
 * \date    14/06/15
 * \version 4.3.0
 */

/*
 * command_line_option.cpp
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

#include <glibmm/i18n.h>
#include "command_line_option.h"
#include <iostream>

using namespace Glib;
using namespace std;

CommandLineOption::CommandLineOption() : context_(""),
    filename_group_("filename",_("The input and output filename")),
    instruction_group_("instruction",_("The instruction")),
    open_(false), read_(false), pdf_(false), csv_(false),
     m_(false), png_(false), svg_(false), gnuplot_(false)
     , input_(""), output_("")
{
    open_entry_.set_long_name("open");
    open_entry_.set_short_name('e');
    open_entry_.set_flags(OptionEntry::FLAG_IN_MAIN);
    open_entry_.set_description(_("Open the input file"));

    read_entry_.set_long_name("read");
    read_entry_.set_short_name('r');
    read_entry_.set_flags(OptionEntry::FLAG_IN_MAIN);
    read_entry_.set_description(_("Read the input file"));

    pdf_entry_.set_long_name("to-pdf");
    pdf_entry_.set_short_name('p');
    pdf_entry_.set_flags(OptionEntry::FLAG_IN_MAIN);
    pdf_entry_.set_description(_("Export the input file into into a PDF output file"));

    csv_entry_.set_long_name("to-csv");
    csv_entry_.set_short_name('c');
    csv_entry_.set_flags(OptionEntry::FLAG_IN_MAIN);
    csv_entry_.set_description(_("Export the input file into into a CSV output file"));

    m_entry_.set_long_name("to-m");
    m_entry_.set_short_name('m');
    m_entry_.set_flags(OptionEntry::FLAG_IN_MAIN);
    m_entry_.set_description(_("Export the input file into into a m (Octave/Matlab) output file"));

    gnuplot_entry_.set_long_name("to-gnuplot");
    gnuplot_entry_.set_short_name('g');
    gnuplot_entry_.set_flags(OptionEntry::FLAG_IN_MAIN);
    gnuplot_entry_.set_description(_("Export the input file into into Gnuplot output files"));

    png_entry_.set_long_name("to-png");
    png_entry_.set_short_name('n');
    png_entry_.set_flags(OptionEntry::FLAG_IN_MAIN);
    png_entry_.set_description(_("Export the input file into into a PNG output file"));

    svg_entry_.set_long_name("to-svg");
    svg_entry_.set_short_name('s');
    svg_entry_.set_flags(OptionEntry::FLAG_IN_MAIN);
    svg_entry_.set_description(_("Export the input file into into a SVG output file"));

    instruction_group_.add_entry(open_entry_,open_);
    instruction_group_.add_entry(read_entry_,read_);
    instruction_group_.add_entry(pdf_entry_,pdf_);
    instruction_group_.add_entry(csv_entry_,csv_);
    instruction_group_.add_entry(m_entry_,m_);
    instruction_group_.add_entry(gnuplot_entry_,gnuplot_);
    instruction_group_.add_entry(png_entry_,png_);
    instruction_group_.add_entry(svg_entry_,svg_);

    context_.add_group(instruction_group_);


    input_entry_.set_long_name("input");
    input_entry_.set_short_name('i');
    input_entry_.set_flags(OptionEntry::FLAG_IN_MAIN);
    input_entry_.set_description(_("The input filename"));
    input_entry_.set_arg_description(_("filename"));

    output_entry_.set_long_name("output");
    output_entry_.set_short_name('o');
    output_entry_.set_flags(OptionEntry::FLAG_IN_MAIN);
    output_entry_.set_description(_("The output filename"));
    output_entry_.set_arg_description(_("filename"));

    filename_group_.add_entry_filename(input_entry_,input_);
    filename_group_.add_entry_filename(output_entry_,output_);

    context_.add_group(filename_group_);
    context_.set_help_enabled(true);

    context_.set_summary(_("If an instruction is set, a input filename is needed.\n"
                           "If a \"to\" instruction is set, an output filename is needed.\n"
                           "You can use only one instruction at once."));
}


CommandLineOption::Instruction CommandLineOption::parse(int& argc, char**& argv)
{
    Instruction ins = RUN;
    ustring error_msg;

    try
    {
        context_.parse(argc,argv);
    }
    catch (Glib::OptionError& e)
    {
        cerr << e.what() << endl;
        cerr << _("Use -h or --help for help.") << endl;
        exit(EXIT_FAILURE);
    }

    if (!open_ && !read_ && !pdf_ && !csv_ && !m_ && !gnuplot_ && !png_ && !svg_)
    {
        if (!(input_.empty()) || !(output_.empty()))
            error_msg += _("You need an instruction.\n");
        else
            ins = RUN;
    }
    else
    {
        if ((open_ && read_) || (open_ && pdf_) || (open_ && csv_) || (open_ && m_ )
            || (open_ && gnuplot_) || (read_ && pdf_) || (read_ && csv_)
            || (read_ && m_) || (read_ && gnuplot_) || (pdf_ && csv_)
            || (pdf_ && m_) || (pdf_ && gnuplot_) || (csv_ && m_)
            || (csv_ && gnuplot_) || (m_ && gnuplot_) || (png_ && open_)
            || (png_ && read_) || (png_ && pdf_) || (png_ && csv_)
            || (png_ && m_) || (png_ && gnuplot_) || (png_ && svg_)
            || (svg_ && open_) || (svg_ && read_) || (svg_ && pdf_)
            || (svg_ && csv_) || (svg_ && m_) || (svg_ && gnuplot_))
            error_msg += _("You have to use only one instruction.\n");

        if (open_ || read_)
        {
            if (input_.empty())
                error_msg += _("You need an input file to open or read a file.\n");
            else
            {
                if (open_)
                    ins = OPEN_FILE;
                else
                    ins = READ_FILE;
            }

            if (!(output_.empty()))
                error_msg += _("You don't need an output file to open or read a file.\n");
        }
        else
        {
            if (input_.empty())
                error_msg += _("You need an input file to export a file.\n");
            if (output_.empty())
                error_msg += _("You need an output file to export a file.\n");

            if (!(output_.empty()) && !(input_.empty()))
            {
                if (pdf_)
                    ins = EXPORT_TO_PDF;
                else if (csv_)
                    ins = EXPORT_TO_CSV;
                else if (gnuplot_)
                    ins = EXPORT_TO_GNUPLOT;
                else if (png_)
                    ins = EXPORT_TO_PNG;
                else if (svg_)
                    ins = EXPORT_TO_SVG;
                else
                    ins = EXPORT_TO_M;
            }

        }
    }


    if (!(error_msg.empty()))
    {
        cerr << error_msg;
        cerr << _("Use -h or --help for help.") << endl;
        exit(EXIT_FAILURE);
    }

    return ins;
}
