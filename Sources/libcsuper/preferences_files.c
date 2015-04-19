/*!
 * \file    preferences_files.c
 * \brief   Function which store preferences into files
 * \author  Remi BERTHO
 * \date    07/01/15
 * \version 4.2.0
 */

/*
* preferences_files.c
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

#include "preferences_files.h"
#include <libxml/tree.h>


/*!
 * \fn void createPreferencesFolder(char *home_path)
 *  Create the folder which contain all preferences
 * \param[in] home_path the path to the home directory
 */
void createPreferencesFolder(char *home_path)
{
    char folder[SIZE_MAX_FILE_NAME];

    sprintf(folder,"%s%s",home_path,PREFERENCES_FOLDER_NAME);

    #ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(folder);
    #endif
}

/*!
 * \fn bool createFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct toolbar)
 *  Create the file which contain the preferences for the toolbar button
 * \param[in] home_path the path to the home directory
 * \param[in] toolbar the toolbar button preferences for displaying
 * \return true if everything is OK, false otherwise
 */
bool createFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct toolbar)
{
    one_preferences one;
    one.toolbar = toolbar;
    return writeXmlPreferencesFileType(&one,home_path,toolbar_type);
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_TOOLBAR_BUTTON_PREFERENCES);

    createPreferencesFolder(home_path);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",toolbar.new,toolbar.open,
            toolbar.save_as,toolbar.export,toolbar.separator_6,toolbar.delete_file,
            toolbar.separator_1,toolbar.undo,toolbar.redo,toolbar.separator_2,toolbar.cut,
            toolbar.copy,toolbar.paste,toolbar.delete,toolbar.separator_3,toolbar.properties,
            toolbar.separator_4,toolbar.preferences,toolbar.game_configuration_preferences,
            toolbar.toolbar_button_preferences,toolbar.exportation_preferences,toolbar.separator_5,toolbar.about);

    closeFile(ptr_file);

    return true;*/
}

/*!
 * \fn bool readFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct *toolbar)
 *  Read the file which contain the preferences for the toolbar button
 * \param[in] home_path the path to the home directory
 * \param[in] toolbar the toolbar button preferences for displaying
 * \return true if everything is OK, false otherwise
 */
bool readFileToolbarButtonPreferences(char *home_path, toolbar_button_preferences_struct *toolbar)
{
    one_preferences one;
    readXmlPreferencesFileType(&one,home_path,toolbar_type);
    *toolbar=one.toolbar;
    return true;
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;
    toolbar->open=2;
    toolbar->new=2;
    toolbar->save_as=2;
    toolbar->export=1;
    toolbar->separator_6=2;
    toolbar->delete_file=1;
    toolbar->separator_1=2;
    toolbar->undo=2;
    toolbar->redo=2;
    toolbar->separator_2=2;
    toolbar->cut=1;
    toolbar->copy=1;
    toolbar->paste=1;
    toolbar->delete=1;
    toolbar->separator_3=2;
    toolbar->properties=1;
    toolbar->separator_4=2;
    toolbar->preferences=2;
    toolbar->game_configuration_preferences=0;
    toolbar->toolbar_button_preferences=0;
    toolbar->exportation_preferences=0;
    toolbar->separator_5=2;
    toolbar->about=1;

    createPreferencesFolder(home_path);

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_TOOLBAR_BUTTON_PREFERENCES);

    ptr_file=openFile(file_name,"r");

    if (ptr_file==NULL)
        return createFileToolbarButtonPreferences(home_path,*toolbar);

    fscanf(ptr_file,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",&(toolbar->new),&(toolbar->open),
           &(toolbar->save_as),&(toolbar->export),&(toolbar->separator_6),&(toolbar->delete_file),
           &(toolbar->separator_1),&(toolbar->undo),&(toolbar->redo),&(toolbar->separator_2),
           &(toolbar->cut),&(toolbar->copy),&(toolbar->paste),&(toolbar->delete),
           &(toolbar->separator_3),&(toolbar->properties),&(toolbar->separator_4),&(toolbar->preferences),
           &(toolbar->game_configuration_preferences),&(toolbar->toolbar_button_preferences),
           &(toolbar->exportation_preferences),&(toolbar->separator_5),&(toolbar->about));

    closeFile(ptr_file);

    return true;*/
}

/*!
 * \fn bool differentsToolbarButtonPreferencesStruct(toolbar_button_preferences_struct toolbar1, toolbar_button_preferences_struct toolbar2)
 *  Test if the two toolbar button preferences are different
 * \param[in] toolbar1 the first toolbar button preferences
 * \param[in] toolbar2 the second toolbar button preferences
 * \return true if everything is OK, false otherwise
 */
bool differentsToolbarButtonPreferencesStruct(toolbar_button_preferences_struct toolbar1, toolbar_button_preferences_struct toolbar2)
{
    return (toolbar1.new != toolbar2.new || toolbar1.open != toolbar2.open || toolbar1.save_as != toolbar2.save_as || toolbar1.separator_1 != toolbar2.separator_1
            || toolbar1.separator_6 != toolbar2.separator_6 || toolbar1.delete_file != toolbar2.delete_file || toolbar1.export != toolbar2.export
            || toolbar1.undo != toolbar2.undo || toolbar1.redo != toolbar2.redo || toolbar1.separator_2 != toolbar2.separator_2 ||
            toolbar1.cut != toolbar2.cut || toolbar1.copy != toolbar2.copy || toolbar1.paste != toolbar2.paste || toolbar1.delete != toolbar2.delete
            || toolbar1.separator_3 != toolbar2.separator_3 || toolbar1.properties != toolbar2.properties || toolbar1.separator_4 != toolbar2.separator_4
            || toolbar1.preferences != toolbar2.preferences || toolbar1.game_configuration_preferences != toolbar2.game_configuration_preferences ||
            toolbar1.toolbar_button_preferences != toolbar2.toolbar_button_preferences || toolbar1.separator_5 != toolbar2.separator_5
            || toolbar1.about != toolbar2.about || toolbar1.exportation_preferences != toolbar2.exportation_preferences);
}

/*!
 * \fn bool createFileMainWidowSize(char *home_path, main_window_size size)
 *  Create the file which contain the main window size
 * \param[in] home_path the path to the home directory
 * \param[in] size the size of the main window
 * \return true if everything is OK, false otherwise
 */
bool createFileMainWidowSize(char *home_path, main_window_size size)
{
    one_preferences one;
    one.size = size;
    return writeXmlPreferencesFileType(&one,home_path,size_type);
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_MAIN_WINDOW_SIZE);

    createPreferencesFolder(home_path);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%d %d %d",size.width,size.height,size.is_maximize);

    closeFile(ptr_file);

    return true;*/
}

/*!
 * \fn bool readFileMainWidowSize(char *home_path, main_window_size *size)
 *  Read the file which contain the main window size
 * \param[in] home_path the path to the home directory
 * \param[in] size the size of the main window
 * \return true if everything is OK, false otherwise
 */
bool readFileMainWidowSize(char *home_path, main_window_size *size)
{
    one_preferences one;
    readXmlPreferencesFileType(&one,home_path,size_type);
    *size=one.size;
    return true;
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    size->height=422;
    size->width=851;
    size->is_maximize = false;

    createPreferencesFolder(home_path);

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_MAIN_WINDOW_SIZE);

    ptr_file=openFile(file_name,"r");

    if (ptr_file==NULL)
    {
        if (createFileMainWidowSize(home_path,*size) == false)
            return false;
        else
            return true;
    }

    fscanf(ptr_file,"%d %d %d",&(size->width),&(size->height),&(size->is_maximize));

    closeFile(ptr_file);

    return true;*/
}

/*!
 * \fn bool createFileSystemPath()
 *  Create the folder and the file which contain the system path
 * \return true if everything is OK, false otherwise
 */
bool createFileSystemPath()
{
    char folder[SIZE_MAX_FILE_NAME];
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    /*Read the home directory and create the folder*/
    readHomePath(folder);
    sprintf(folder,"%s/%s",folder,PREFERENCES_FOLDER_NAME);
#ifdef __unix__
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#elif _WIN32
    mkdir(folder);
#endif

    sprintf(file_name,"%s/%s",folder,FILENAME_SYSTEM_PATH);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%s",folder);

    closeFile(ptr_file);

    return true;
}

/*!
 * \fn bool readFileSystemPath(char *file_name)
 *  Read the system path and the path read to the filename
 * \param[in,out] *file_name the filename
 * \return true if everything is OK, false otherwise
 */
bool readFileSystemPath(char *file_name)
{
    char file_name_preferences[SIZE_MAX_FILE_NAME];
    char folder[SIZE_MAX_FILE_NAME];
    int file_size;
    FILE *ptr_file;

    readHomePath(file_name_preferences);
    sprintf(file_name_preferences,"%s/%s/%s",file_name_preferences,PREFERENCES_FOLDER_NAME,FILENAME_SYSTEM_PATH);

    ptr_file=openFile(file_name_preferences,"r");

    if(ptr_file == NULL)
        return false;

    file_size=readFileSize(ptr_file);
    fgets(folder,file_size+1,ptr_file);
    closeFile(ptr_file);

    sprintf(folder,"%s/%s",folder,file_name);
    strcpy(file_name,folder);

    return true;
}

/*!
 * \fn bool readSystemPath(char *file_name)
 *  Add the system path, if the file system path doesn't exist, it create it.
 * \param[in,out] *file_name the filename
 * \return true if everything is OK, false otherwise
 */
bool readSystemPath(char *file_name)
{
    libcsuper_initialize();

    if (readFileSystemPath(file_name)==false)
    {
        if(createFileSystemPath()==false)
        {
            printf(_("\nError while reading the file containing the system path.\n"));
            return false;
        }
        if (readFileSystemPath(file_name)==false)
        {
            printf(_("\nError while reading the file containing the system path.\n"));
            return false;
        }
    }
    return true;
}

/*!
 * \fn bool changeSystemPath(char *new_path)
 *  Change the system path
 * \param[in,out] *new_path the new path
 * \return true if everything is OK, false otherwise
 */
bool changeSystemPath(char *new_path)
{
    char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    if (checkPath(new_path) == false)
        return false;

    if (createFileSystemPath()==false)
        return false;

    readHomePath(file_name);

    sprintf(file_name,"%s/%s/%s",file_name,PREFERENCES_FOLDER_NAME,FILENAME_SYSTEM_PATH);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%s",new_path);

    closeFile(ptr_file);

    return true;
}

/*!
 * \fn bool createFileDifferenceBetweenPlayer(char *home_path, difference_between_player diff)
 *  Create the file which contain the data which explain that we display the differences between players
 * \param[in] home_path the path to the home directory
 * \param[in] diff the difference structure
 * \return true if everything is OK, false otherwise
 */
bool createFileDifferenceBetweenPlayer(char *home_path, difference_between_player diff)
{
    one_preferences one;
    one.diff = diff;
    return writeXmlPreferencesFileType(&one,home_path,diff_type);
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_DIFFERENCE_BETWEEN_PLAYER);

    createPreferencesFolder(home_path);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%d %d %d",diff.consecutive,diff.first,diff.last);

    closeFile(ptr_file);

    return true;*/
}


/*!
 * \fn bool readFileDifferenceBetweenPlayer(char *home_path, difference_between_player *diff)
 *  Read the file which contain the data which explain that we display the differences between players
 * \param[in] home_path the path to the home directory
 * \param[in] diff the difference structure
 * \return true if everything is OK, false otherwise
 */
bool readFileDifferenceBetweenPlayer(char *home_path, difference_between_player *diff)
{
    one_preferences one;
    readXmlPreferencesFileType(&one,home_path,diff_type);
    *diff=one.diff;
    return true;
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    diff->consecutive=false;
    diff->first=false;
    diff->last=false;

    createPreferencesFolder(home_path);

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_DIFFERENCE_BETWEEN_PLAYER);

    ptr_file=openFile(file_name,"r");

    if (ptr_file==NULL)
        return createFileDifferenceBetweenPlayer(home_path,*diff);

    fscanf(ptr_file,"%d %d %d",(int*)&(diff->consecutive),(int*)&(diff->first),(int*)&(diff->last));

    closeFile(ptr_file);

    return true;*/
}


/*!
 * \fn bool createFilePdfPreferences(char *home_path, export_pdf_preferences *ptr_pref)
 *  Create the file which contain the preferences export into a pdf file
 * \param[in] home_path the path to the home directory
 * \param[in] ptr_pref a pointer on a export_pdf_preferences
 * \return true if everything is OK, false otherwise
 */
bool createFilePdfPreferences(char *home_path, export_pdf_preferences *ptr_pref)
{
    one_preferences one;
    one.pdf = *ptr_pref;
    return writeXmlPreferencesFileType(&one,home_path,pdf_type);
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_PDF_PREFERENCES);

    createPreferencesFolder(home_path);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%d %d %d %d %d %d %d",ptr_pref->charset,ptr_pref->font_size,
            ptr_pref->direction,ptr_pref->size,ptr_pref->margin,ptr_pref->total_points_turn,
            ptr_pref->ranking_turn);

    closeFile(ptr_file);

    return true;*/
}


/*!
 * \fn bool readFilePdfPreferences(char *home_path, export_pdf_preferences *ptr_pref)
 *  Read the file which contain the preferences export into a pdf file
 * \param[in] home_path the path to the home directory
 * \param[in] ptr_pref a pointer on a export_pdf_preferences
 * \return true if everything is OK, false otherwise
 */
bool readFilePdfPreferences(char *home_path, export_pdf_preferences *ptr_pref)
{
    one_preferences one;
    readXmlPreferencesFileType(&one,home_path,pdf_type);
    *ptr_pref=one.pdf;
    return true;
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    ptr_pref->font_size = DEFAULT_FONT_SIZE;
    ptr_pref->charset = ISO885915;
    ptr_pref->size = HPDF_PAGE_SIZE_A4;
    ptr_pref->direction = HPDF_PAGE_PORTRAIT;
    ptr_pref->margin = DEFAULT_MARGIN;
    ptr_pref->total_points_turn = false;
    ptr_pref->ranking_turn = false;

    createPreferencesFolder(home_path);

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_PDF_PREFERENCES);

    ptr_file=openFile(file_name,"r");

    if (ptr_file==NULL)
        return createFilePdfPreferences(home_path,ptr_pref);

    fscanf(ptr_file,"%d %d %d %d %d %d %d",(int*)&(ptr_pref->charset),(int*)&(ptr_pref->font_size)
           ,(int*)&(ptr_pref->direction),(int*)&(ptr_pref->size),(int*)&(ptr_pref->margin),
           (int *)&(ptr_pref->total_points_turn),(int *)&(ptr_pref->ranking_turn));

    closeFile(ptr_file);

    return true;*/
}


/*!
 * \fn bool differentsTExportPdfPreferencesStruct(export_pdf_preferences pdf_1, export_pdf_preferences pdf_2)
 *  Test if the two pdf export preferences are different
 * \param[in] pdf_1 the first pdf export preferences
 * \param[in] pdf_2 the second pdf export preferences
 * \return true if everything is OK, false otherwise
 */
bool differentsTExportPdfPreferencesStruct(export_pdf_preferences pdf_1, export_pdf_preferences pdf_2)
{
    return (pdf_1.charset != pdf_2.charset || pdf_1.direction != pdf_2.direction
            || pdf_1.font_size != pdf_2.font_size || pdf_1.margin != pdf_2.margin
            || pdf_1.size != pdf_2.size || pdf_1.total_points_turn != pdf_2.total_points_turn
            || pdf_1.ranking_turn != pdf_2.ranking_turn );
}



/*!
 * \fn bool createFileScoreDisplay(char *home_path, score_display score)
 *  Create the file which contain the data which explain that we display on the score grid
 * \param[in] home_path the path to the home directory
 * \param[in] score the score_display structure
 * \return true if everything is OK, false otherwise
 */
bool createFileScoreDisplay(char *home_path, score_display score)
{
    one_preferences one;
    one.score = score;
    return writeXmlPreferencesFileType(&one,home_path,score_type);
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_SCORE_DISPLAY);

    createPreferencesFolder(home_path);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%d %d %d",score.total_points,score.ranking,score.edit_suppr);

    closeFile(ptr_file);

    return true;*/
}


/*!
 * \fn bool readFileScoreDisplay(char *home_path, score_display *score)
 *  Read the file which contain the data which explain that we display on the score grid
 * \param[in] home_path the path to the home directory
 * \param[in] score the score_display structure
 * \return true if everything is OK, false otherwise
 */
bool readFileScoreDisplay(char *home_path, score_display *score)
{
    one_preferences one;
    readXmlPreferencesFileType(&one,home_path,score_type);
    *score=one.score;
    return true;
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    score->total_points=false;
    score->ranking=false;
    score->edit_suppr=false;

    createPreferencesFolder(home_path);

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_SCORE_DISPLAY);

    ptr_file=openFile(file_name,"r");

    if (ptr_file==NULL)
        return createFileScoreDisplay(home_path,*score);

    fscanf(ptr_file,"%d %d %d",(int*)&(score->total_points),(int*)&(score->ranking),(int*)&(score->edit_suppr));

    closeFile(ptr_file);

    return true;*/
}


/*!
 * \fn bool createFileMainWindowSide(char *home_path, main_window_side pref)
 *  Create the file which contain the data which explain what will be display in the left side of the main window
 * \param[in] home_path the path to the home directory
 * \param[in] pref the main_window_side structure
 * \return true if everything is OK, false otherwise
 */
bool createFileMainWindowSide(char *home_path, main_window_side pref)
{
    one_preferences one;
    one.side = pref;
    return writeXmlPreferencesFileType(&one,home_path,side_type);
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_MAIN_WINDOW_SIDE);

    createPreferencesFolder(home_path);

    ptr_file=openFile(file_name,"w+");

    if (ptr_file==NULL)
        return false;

    fprintf(ptr_file,"%d %d %d",pref.ranking,pref.calculator,pref.game_information);

    closeFile(ptr_file);

    return true;*/
}


/*!
 * \fn bool readFileMainWindowSide(char *home_path, main_window_side *pref)
 *  Read the file which contain the data which explain what will be display in the left side of the main window
 * \param[in] home_path the path to the home directory
 * \param[in] pref the main_window_side structure
 * \return true if everything is OK, false otherwise
 */
bool readFileMainWindowSide(char *home_path, main_window_side *pref)
{
    one_preferences one;
    readXmlPreferencesFileType(&one,home_path,side_type);
    *pref=one.side;
    return true;
    /*char file_name[SIZE_MAX_FILE_NAME];
    FILE *ptr_file;

    pref->ranking=true;
    pref->calculator=false;
    pref->game_information=true;

    createPreferencesFolder(home_path);

    sprintf(file_name,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_MAIN_WINDOW_SIDE);

    ptr_file=openFile(file_name,"r");

    if (ptr_file==NULL)
        return createFileMainWindowSide(home_path,*pref);

    fscanf(ptr_file,"%d %d %d",(int*)&(pref->ranking),(int*)&(pref->calculator),(int*)&(pref->game_information));

    closeFile(ptr_file);

    return true;*/
}


bool writeXmlPreferencesFile(preferences *pref, char *home_path)
{
    bool res=true;
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr racine,tmp_node;
    char filename[SIZE_MAX_FILE_NAME];

    sprintf(filename,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_PREFERENCES_XML);

    // Set root
    racine = xmlNewNode(NULL, BAD_CAST "csu_preferences");
    xmlDocSetRootElement(doc,racine);

    //toolbar
    tmp_node = xmlNewNode(NULL, BAD_CAST "toolbar_button");
    addXmlIntNode(tmp_node,"new",pref->toolbar.new);
    addXmlIntNode(tmp_node,"open",pref->toolbar.open);
    addXmlIntNode(tmp_node,"save_as",pref->toolbar.save_as);
    addXmlIntNode(tmp_node,"export",pref->toolbar.export);
    addXmlIntNode(tmp_node,"separator_6",pref->toolbar.separator_6);
    addXmlIntNode(tmp_node,"delete_file",pref->toolbar.delete_file);
    addXmlIntNode(tmp_node,"separator_1",pref->toolbar.separator_1);
    addXmlIntNode(tmp_node,"undo",pref->toolbar.undo);
    addXmlIntNode(tmp_node,"redo",pref->toolbar.redo);
    addXmlIntNode(tmp_node,"separator_2",pref->toolbar.separator_2);
    addXmlIntNode(tmp_node,"cut",pref->toolbar.cut);
    addXmlIntNode(tmp_node,"copy",pref->toolbar.copy);
    addXmlIntNode(tmp_node,"paste",pref->toolbar.paste);
    addXmlIntNode(tmp_node,"delete",pref->toolbar.delete);
    addXmlIntNode(tmp_node,"separator_3",pref->toolbar.separator_3);
    addXmlIntNode(tmp_node,"properties",pref->toolbar.properties);
    addXmlIntNode(tmp_node,"separator_4",pref->toolbar.separator_4);
    addXmlIntNode(tmp_node,"preferences",pref->toolbar.preferences);
    addXmlIntNode(tmp_node,"game_configuration_preferences",pref->toolbar.game_configuration_preferences);
    addXmlIntNode(tmp_node,"toolbar_button_preferences",pref->toolbar.toolbar_button_preferences);
    addXmlIntNode(tmp_node,"exportation_preferences",pref->toolbar.exportation_preferences);
    addXmlIntNode(tmp_node,"separator_5",pref->toolbar.separator_5);
    addXmlIntNode(tmp_node,"about",pref->toolbar.about);
    xmlAddChild(racine, tmp_node);

    // main window size
    tmp_node = xmlNewNode(NULL, BAD_CAST "main_window_size");
    addXmlIntNode(tmp_node,"width",pref->size.width);
    addXmlIntNode(tmp_node,"height",pref->size.height);
    addXmlBoolNode(tmp_node,"is_maximize",pref->size.is_maximize);
    xmlAddChild(racine, tmp_node);

    // Differences between players
    tmp_node = xmlNewNode(NULL, BAD_CAST "difference_between_player");
    addXmlBoolNode(tmp_node,"consecutive",pref->diff.consecutive);
    addXmlBoolNode(tmp_node,"first",pref->diff.first);
    addXmlBoolNode(tmp_node,"last",pref->diff.last);
    xmlAddChild(racine, tmp_node);

    // Score display
    tmp_node = xmlNewNode(NULL, BAD_CAST "score_display");
    addXmlBoolNode(tmp_node,"total_points",pref->score.total_points);
    addXmlBoolNode(tmp_node,"ranking",pref->score.ranking);
    addXmlBoolNode(tmp_node,"edit_suppr",pref->score.edit_suppr);
    xmlAddChild(racine, tmp_node);

    // Main window side
    tmp_node = xmlNewNode(NULL, BAD_CAST "main_window_side");
    addXmlBoolNode(tmp_node,"ranking",pref->side.ranking);
    addXmlBoolNode(tmp_node,"calculator",pref->side.calculator);
    addXmlBoolNode(tmp_node,"game_information",pref->side.game_information);
    xmlAddChild(racine, tmp_node);

    // PDF export preferences
    tmp_node = xmlNewNode(NULL, BAD_CAST "export_pdf_preferences");
    addXmlIntNode(tmp_node,"font_size",pref->pdf.font_size);
    addXmlIntNode(tmp_node,"size",pref->pdf.size);
    addXmlIntNode(tmp_node,"direction",pref->pdf.direction);
    addXmlIntNode(tmp_node,"charset",pref->pdf.charset);
    addXmlIntNode(tmp_node,"margin",pref->pdf.margin);
    addXmlBoolNode(tmp_node,"total_points_turn",pref->pdf.total_points_turn);
    addXmlBoolNode(tmp_node,"ranking_turn",pref->pdf.ranking_turn);
    xmlAddChild(racine, tmp_node);


    if(xmlSaveFormatFileEnc(filename,doc,"UTF-8",1) == -1)
        res = false;
    xmlFreeDoc(doc);

    return res;
}


bool writeXmlPreferencesFileType(one_preferences *pref, char *home_path, preferences_type type)
{
    preferences pref_glob;

    readXmlPreferencesFile(&pref_glob,home_path);
    switch(type)
    {
    case toolbar_type:
        pref_glob.toolbar = pref->toolbar;
        break;
    case size_type:
        pref_glob.size = pref->size;
        break;
    case diff_type:
        pref_glob.diff = pref->diff;
        break;
    case score_type:
        pref_glob.score = pref->score;
        break;
    case side_type:
        pref_glob.side = pref->side;
        break;
    case pdf_type:
        pref_glob.pdf = pref->pdf;
        break;
    }

    return writeXmlPreferencesFile(&pref_glob,home_path);
}


void readXmlPreferencesFile(preferences *pref, char *home_path)
{
    xmlDocPtr doc;
    xmlNodePtr root,tmp_node;
    char filename[SIZE_MAX_FILE_NAME];

    sprintf(filename,"%s%s/%s",home_path,PREFERENCES_FOLDER_NAME,FILENAME_PREFERENCES_XML);

        // Parse file
    doc = xmlParseFile(filename);
    if (doc == NULL)
    {
        printf(_("Invalid XML Document\n"));

        pref->toolbar.open=2;
        pref->toolbar.new=2;
        pref->toolbar.save_as=2;
        pref->toolbar.export=1;
        pref->toolbar.separator_6=2;
        pref->toolbar.delete_file=1;
        pref->toolbar.separator_1=2;
        pref->toolbar.undo=2;
        pref->toolbar.redo=2;
        pref->toolbar.separator_2=2;
        pref->toolbar.cut=1;
        pref->toolbar.copy=1;
        pref->toolbar.paste=1;
        pref->toolbar.delete=1;
        pref->toolbar.separator_3=2;
        pref->toolbar.properties=1;
        pref->toolbar.separator_4=2;
        pref->toolbar.preferences=2;
        pref->toolbar.game_configuration_preferences=0;
        pref->toolbar.toolbar_button_preferences=0;
        pref->toolbar.exportation_preferences=0;
        pref->toolbar.separator_5=2;
        pref->toolbar.about=1;

        pref->size.height=422;
        pref->size.width=851;
        pref->size.is_maximize = false;

        pref->diff.consecutive=false;
        pref->diff.first=false;
        pref->diff.last=false;

        pref->score.total_points=false;
        pref->score.ranking=false;
        pref->score.edit_suppr=false;

        pref->side.ranking=true;
        pref->side.calculator=false;
        pref->side.game_information=true;

        pref->pdf.font_size = DEFAULT_FONT_SIZE;
        pref->pdf.charset = ISO885915;
        pref->pdf.size = HPDF_PAGE_SIZE_A4;
        pref->pdf.direction = HPDF_PAGE_PORTRAIT;
        pref->pdf.margin = DEFAULT_MARGIN;
        pref->pdf.total_points_turn = false;
        pref->pdf.ranking_turn = false;

        return;
    }

    // Check root
    root = xmlDocGetRootElement(doc);
    if (!xmlStrEqual(root->name,xmlCharStrdup("csu_preferences")))
    {
        printf(_("Not a csu preferences file\n"));
        xmlFreeDoc(doc);
    }

    // Toolbar button
    tmp_node = xmlFirstElementChild(xmlFirstElementChild(root));
    pref->toolbar.new=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.open=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.save_as=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.export=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.separator_6=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.delete_file=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.separator_1=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.undo=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.redo=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.separator_2=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.cut=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.copy=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.paste=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.delete=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.separator_3=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.properties=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.separator_4=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.preferences=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.game_configuration_preferences=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.toolbar_button_preferences=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.exportation_preferences=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.separator_5=convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->toolbar.about=convertStringInt((char *)xmlNodeGetContent(tmp_node));

    // Main window size
    tmp_node = xmlFirstElementChild(xmlNextElementSibling(tmp_node->parent));
    pref->size.width = convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->size.height = convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->size.is_maximize = convertStringBool((char *)xmlNodeGetContent(tmp_node));

    // Differences between player
    tmp_node = xmlFirstElementChild(xmlNextElementSibling(tmp_node->parent));
    pref->diff.consecutive = convertStringBool((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->diff.first = convertStringBool((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->diff.last= convertStringBool((char *)xmlNodeGetContent(tmp_node));

    // Score display
    tmp_node = xmlFirstElementChild(xmlNextElementSibling(tmp_node->parent));
    pref->score.total_points = convertStringBool((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->score.ranking = convertStringBool((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->score.edit_suppr= convertStringBool((char *)xmlNodeGetContent(tmp_node));

    // Main window side
    tmp_node = xmlFirstElementChild(xmlNextElementSibling(tmp_node->parent));
    pref->side.ranking = convertStringBool((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->side.calculator = convertStringBool((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->side.game_information = convertStringBool((char *)xmlNodeGetContent(tmp_node));

    // PDF export preferences
    tmp_node = xmlFirstElementChild(xmlNextElementSibling(tmp_node->parent));
    pref->pdf.font_size = convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->pdf.size = convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->pdf.direction = convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->pdf.charset = convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->pdf.margin = convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->pdf.total_points_turn = convertStringBool((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->pdf.ranking_turn = convertStringBool((char *)xmlNodeGetContent(tmp_node));


    xmlFreeDoc(doc);
}

void readXmlPreferencesFileType(one_preferences *pref, char *home_path, preferences_type type)
{
    preferences pref_glob;

    readXmlPreferencesFile(&pref_glob,home_path);

    switch(type)
    {
    case toolbar_type:
        pref->toolbar = pref_glob.toolbar;
        break;
    case size_type:
        pref->size = pref_glob.size;
        break;
    case diff_type:
        pref->diff = pref_glob.diff;
        break;
    case score_type:
        pref->score = pref_glob.score;
        break;
    case side_type:
        pref->side = pref_glob.side;
        break;
    case pdf_type:
        pref->pdf = pref_glob.pdf;
        break;
    }
}
