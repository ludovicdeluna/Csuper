/*!
 * \file    menu_file.cpp
 * \author  Remi BERTHO
 * \date    06/08/15
 * \version 4.3.0
 */

/*
 * menu_file.cpp
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


#include "menu_file.h"

#include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace Gdk;
using namespace std;
using namespace csuper;

MenuFile::MenuFile(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Menu(cobject)
{
    set_accel_group(app()->mainAccelGroup());

    refGlade->get_widget("menu_save_as", save_as_);
    refGlade->get_widget("menu_export", export_);
    refGlade->get_widget("menuitem_separator5", sep_1_);
    refGlade->get_widget("menu_properties", prop_);
    refGlade->get_widget("menuitem_separator6", sep_2_);
    refGlade->get_widget("menu_delete_file", delete_);

    save_as_->set_sensitive(false);
    export_->set_sensitive(false);
    prop_->set_sensitive(false);
    delete_->set_sensitive(false);

    delete_->signal_activate().connect(mem_fun(*this,&MenuFile::deleteFile));
    prop_->signal_activate().connect(mem_fun(*this,&MenuFile::showProperties));
    save_as_->signal_activate().connect(mem_fun(*this,&MenuFile::saveAs));
    export_->signal_activate().connect(mem_fun(*this,&MenuFile::exportFile));

    delete_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_Delete,CONTROL_MASK,ACCEL_VISIBLE);
    prop_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_R,CONTROL_MASK,ACCEL_VISIBLE);
    save_as_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_S,CONTROL_MASK,ACCEL_VISIBLE);
    export_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_E,CONTROL_MASK,ACCEL_VISIBLE);
}


//
// Function
//
void MenuFile::setSensitive()
{
    save_as_->set_sensitive(true);
    export_->set_sensitive(true);
    prop_->set_sensitive(true);
    delete_->set_sensitive(true);
}


void MenuFile::showProperties()
{
    app()->filePropertiesDialog()->launch();
}

void MenuFile::deleteFile()
{
    MessageDialog* verif = new MessageDialog(*(app()->mainWindow()),_("Do you really want to delete the current file?"),false,MESSAGE_QUESTION,BUTTONS_YES_NO,true);
    switch(verif->run())
    {
    case RESPONSE_YES:
        verif->hide();
        try
        {
            trashFile(app()->filename());
        }
        catch (Glib::Exception& e)
        {
            cerr << e.what() << endl;
            MessageDialog* error = new MessageDialog(*(app()->mainWindow()),e.what(),false,MESSAGE_ERROR,BUTTONS_OK,true);
            error->run();
            error->hide();
            delete error;
        }
        break;
    default:
        verif->hide();
    }
    delete verif;
}

void MenuFile::saveAs()
{
    // File chooser dialog
    FileChooserDialog* file_chooser = new FileChooserDialog(*(app()->mainWindow()),_("Save as"),FILE_CHOOSER_ACTION_SAVE);
    file_chooser->add_button(_("Save"),RESPONSE_ACCEPT);
    file_chooser->add_button(_("Cancel"),RESPONSE_CANCEL);
    file_chooser->set_current_folder(filename_from_utf8(app()->pref()->directory().open()));
    file_chooser->set_current_name(removeFileExtension(path_get_basename(filename_from_utf8(app()->filename()))));


    // File filter
    RefPtr<FileFilter> csu_file_filter = FileFilter::create();
    csu_file_filter->add_mime_type("application/csu");
    csu_file_filter->add_pattern("*.csu");
    csu_file_filter->set_name(_("CSU file"));
    RefPtr<FileFilter> all_file_filter = FileFilter::create();
    all_file_filter->add_pattern("*");
    all_file_filter->set_name(_("All file"));
    file_chooser->add_filter(csu_file_filter);
    file_chooser->add_filter(all_file_filter);

    // Run
    ustring new_filename;

    switch (file_chooser->run())
    {
    case RESPONSE_ACCEPT:
        file_chooser->hide();

        new_filename = filename_to_utf8(file_chooser->get_filename());
        if (file_chooser->get_filter() == csu_file_filter)
            addFileExtension(new_filename,"csu");

        try
        {
            app()->game()->writeToFile(new_filename);
            app()->setFilename(new_filename);
        }
        catch(Glib::Exception& e)
        {
            cerr << e.what() << endl;
            MessageDialog* error = new MessageDialog(*(app()->mainWindow()),e.what(),false,MESSAGE_ERROR,BUTTONS_OK,true);
            error->run();
            error->hide();
            delete error;
        }
        break;
    default:
        file_chooser->hide();
        break;
    }

    delete file_chooser;
}


void MenuFile::exportFile()
{
    // File chooser dialog
    FileChooserDialog* file_chooser = new FileChooserDialog(*(app()->mainWindow()),_("Export"),FILE_CHOOSER_ACTION_SAVE);
    file_chooser->add_button(_("Export"),RESPONSE_ACCEPT);
    file_chooser->add_button(_("Cancel"),RESPONSE_CANCEL);
    file_chooser->set_current_folder(filename_from_utf8(app()->pref()->directory().open()));
    file_chooser->set_current_name(removeFileExtension(path_get_basename(filename_from_utf8(app()->filename()))));


    // File filter
    RefPtr<FileFilter> pdf_file_filter = FileFilter::create();
    pdf_file_filter->add_mime_type("application/pdf");
    pdf_file_filter->set_name(_("PDF file"));
    file_chooser->add_filter(pdf_file_filter);

    RefPtr<FileFilter> csv_file_filter = FileFilter::create();
    csv_file_filter->add_mime_type("text/csv");
    csv_file_filter->set_name(_("CSV file"));
    file_chooser->add_filter(csv_file_filter);

    RefPtr<FileFilter> gnuplot_file_filter = FileFilter::create();
    gnuplot_file_filter->add_mime_type("application/x-gnuplot");
    gnuplot_file_filter->add_pattern("*.dat");
    gnuplot_file_filter->add_pattern("*.plt");
    gnuplot_file_filter->set_name(_("Gnuplot file"));
    file_chooser->add_filter(gnuplot_file_filter);

    RefPtr<FileFilter> octave_file_filter = FileFilter::create();
    octave_file_filter->add_mime_type("text/x-matlab");
    octave_file_filter->add_mime_type("text/x-octave");
    octave_file_filter->add_pattern("*.m");
    octave_file_filter->set_name(_("Octave/Matlab file"));
    file_chooser->add_filter(octave_file_filter);

    RefPtr<FileFilter> svg_file_filter = FileFilter::create();
    svg_file_filter->add_mime_type("image/svg+xml");
    svg_file_filter->set_name(_("SVG file"));
    file_chooser->add_filter(svg_file_filter);

    RefPtr<FileFilter> png_file_filter = FileFilter::create();
    png_file_filter->add_mime_type("image/png");
    png_file_filter->set_name(_("PNG file"));
    file_chooser->add_filter(png_file_filter);


    // Run
    ustring new_filename;
    RefPtr<FileFilter> selected_filter;

    switch (file_chooser->run())
    {
    case RESPONSE_ACCEPT:
        file_chooser->hide();

        new_filename = filename_to_utf8(file_chooser->get_filename());
        selected_filter = file_chooser->get_filter();

        try
        {
            if (selected_filter == pdf_file_filter)
            {
                addFileExtension(new_filename,"pdf");
                app()->game()->exportToPdf(new_filename,app()->pref()->exportPdf(),app()->pref()->chartExportation());
            }
            else if (selected_filter == csv_file_filter)
            {
                addFileExtension(new_filename,"csv");
                app()->game()->exportToCsv(new_filename);
            }
            else if (selected_filter == octave_file_filter)
            {
                addFileExtension(new_filename,"m");
                app()->game()->exportToM(new_filename);
            }
            else if (selected_filter == svg_file_filter)
            {
                addFileExtension(new_filename,"svg");
                app()->game()->exportToSvg(new_filename,app()->pref()->chartExportation());
            }
            else if (selected_filter == png_file_filter)
            {
                addFileExtension(new_filename,"png");
                app()->game()->exportToPng(new_filename,app()->pref()->chartExportation());
            }
            else if (selected_filter == gnuplot_file_filter)
            {
                app()->game()->exportToGnuplot(new_filename);
            }
        }
        catch(Glib::Exception& e)
        {
            cerr << e.what() << endl;
            MessageDialog* error = new MessageDialog(*(app()->mainWindow()),e.what(),false,MESSAGE_ERROR,BUTTONS_OK,true);
            error->run();
            error->hide();
            delete error;
        }
        break;
    default:
        file_chooser->hide();
        break;
    }

    delete file_chooser;
}
