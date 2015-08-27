/*!
 * \file    menu_edit.cpp
 * \author  Remi BERTHO
 * \date    06/08/15
 * \version 4.3.0
 */

/*
 * menu_edit.cpp
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

#include "menu_edit.h"

#include <glibmm/i18n.h>
#include "csu_application.h"

using namespace Gtk;
using namespace Glib;
using namespace csuper;
using namespace Gdk;

MenuEdit::MenuEdit(BaseObjectType* cobject, const RefPtr<Builder>& refGlade) :  CsuWidget(), Menu(cobject)
{
    set_accel_group(app()->mainAccelGroup());

    refGlade->get_widget("menu_undo", undo_);
    refGlade->get_widget("menu_redo", redo_);

    refGlade->get_widget("menuitem_separator_4", sep_);

    refGlade->get_widget("menu_copy", copy_);
    refGlade->get_widget("menu_cut", cut_);
    refGlade->get_widget("menu_paste", paste_);
    refGlade->get_widget("menu_delete", delete_);


    undo_->set_sensitive(false);
    redo_->set_sensitive(false);
    copy_->set_sensitive(false);
    cut_->set_sensitive(false);
    paste_->set_sensitive(false);
    delete_->set_sensitive(false);


    signal_show().connect(mem_fun(*this,&MenuEdit::setSensitive));


    undo_->signal_activate().connect(mem_fun(*this,&MenuEdit::undo));
    redo_->signal_activate().connect(mem_fun(*this,&MenuEdit::redo));

    copy_->signal_activate().connect(mem_fun(*this,&MenuEdit::copy));
    cut_->signal_activate().connect(mem_fun(*this,&MenuEdit::cut));
    paste_->signal_activate().connect(mem_fun(*this,&MenuEdit::paste));
    delete_->signal_activate().connect(mem_fun(*this,&MenuEdit::deleteText));


    undo_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_Z,CONTROL_MASK,ACCEL_VISIBLE);
    redo_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_Y,CONTROL_MASK,ACCEL_VISIBLE);

    copy_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_C,CONTROL_MASK,ACCEL_VISIBLE);
    cut_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_X,CONTROL_MASK,ACCEL_VISIBLE);
    paste_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_P,CONTROL_MASK,ACCEL_VISIBLE);
    delete_->add_accelerator("activate",app()->mainAccelGroup(),GDK_KEY_Delete,~MODIFIER_MASK,ACCEL_VISIBLE);
}


//
// Function
//
void MenuEdit::setSensitive()
{
    // Undo/redo
    if (app()->undoRedoManager().canUndo())
        undo_->set_sensitive(true);
    else
        undo_->set_sensitive(false);

    if (app()->undoRedoManager().canRedo())
        redo_->set_sensitive(true);
    else
        redo_->set_sensitive(false);

    // Clipboard
    Widget* focus_widget = app()->get_active_window()->get_focus();
    if (focus_widget == nullptr)
    {
        copy_->set_sensitive(false);
        cut_->set_sensitive(false);
        paste_->set_sensitive(false);
        delete_->set_sensitive(false);
        return;
    }

    Editable* focus_editable = dynamic_cast<Editable*>(focus_widget);
    if (focus_editable == nullptr)
    {
        copy_->set_sensitive(false);
        cut_->set_sensitive(false);
        paste_->set_sensitive(false);
        delete_->set_sensitive(false);
        return;
    }

    RefPtr<Clipboard> clipboard = Clipboard::get();
    RefPtr<Clipboard> clipboard_selected = Clipboard::get(gdk_atom_intern("PRIMARY",TRUE));

    bool text_selected = clipboard_selected->wait_is_text_available();

    copy_->set_sensitive(text_selected);
    cut_->set_sensitive(text_selected);
    delete_->set_sensitive(text_selected);
    paste_->set_sensitive(clipboard->wait_is_text_available());
}


void MenuEdit::copy()
{
    Widget* focus_widget = app()->get_active_window()->get_focus();
    if (focus_widget == nullptr)
        return;

    Editable* focus_editable = dynamic_cast<Editable*>(focus_widget);
    if (focus_editable == nullptr)
        return;

    focus_editable->copy_clipboard();
}


void MenuEdit::cut()
{
    Widget* focus_widget = app()->get_active_window()->get_focus();
    if (focus_widget == nullptr)
        return;

    Editable* focus_editable = dynamic_cast<Editable*>(focus_widget);
    if (focus_editable == nullptr)
        return;

    focus_editable->cut_clipboard();
}




void MenuEdit::paste()
{
    Widget* focus_widget = app()->get_active_window()->get_focus();
    if (focus_widget == nullptr)
        return;

    Editable* focus_editable = dynamic_cast<Editable*>(focus_widget);
    if (focus_editable == nullptr)
        return;

    focus_editable->paste_clipboard();
}




void MenuEdit::deleteText()
{
    Widget* focus_widget = app()->get_active_window()->get_focus();
    if (focus_widget == nullptr)
        return;

    Editable* focus_editable = dynamic_cast<Editable*>(focus_widget);
    if (focus_editable == nullptr)
        return;

    focus_editable->delete_selection();
}

void MenuEdit::undo()
{
    Game* game = app()->undoRedoManager().undo();
    app()->updateGame(game);
}


void MenuEdit::redo()
{
    Game* game = app()->undoRedoManager().redo();
    app()->updateGame(game);
}
