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
}

/*!
 * \fn bool createFileChartExportation(char *home_path, chart_exportation pref)
 *  Create the file which contain the chart exportation preferences
 * \param[in] home_path the path to the home directory
 * \param[in] pref the chart_exportation structure
 * \return true if everything is OK, false otherwise
 */
bool createFileChartExportation(char *home_path, chart_exportation pref)
{
    one_preferences one;
    one.chart = pref;
    return writeXmlPreferencesFileType(&one,home_path,chart_type);
}


/*!
 * \fn bool readFileChartExportation(char *home_path, chart_exportation *pref);
 *  Read the file which contain the chart exportation preferences
 * \param[in] home_path the path to the home directory
 * \param[in] pref the chart_exportation structure
 * \return true if everything is OK, false otherwise
 */
bool readFileChartExportation(char *home_path, chart_exportation *pref)
{
    one_preferences one;
    readXmlPreferencesFileType(&one,home_path,chart_type);
    *pref=one.chart;
    return true;
}

/*!
 * \fn bool differentsChartExportationStruct(chart_exportation pref_1, chart_exportation pref_2)
 *  Test if the two chart exportation structure
 * \param[in] pref_1 the first chart_exportation
 * \param[in] pref_2 the second chart_exportation
 * \return true if everything is OK, false otherwise
 */
bool differentsChartExportationStruct(chart_exportation pref_1, chart_exportation pref_2)
{
    return (pref_1.width != pref_2.width || pref_1.height != pref_2.height
            || pref_1.total_points != pref_2.total_points);
}


/*!
 * \fn bool writeXmlPreferencesFile(preferences *pref, char *home_path)
 *  Write the preferences file
 * \param[in] home_path the path to the home directory
 * \param[in] pref the preferences structure
 * \return true if everything is OK, false otherwise
 */
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

    // Version
    addXmlFloatNode(racine,"version",PREFERENCES_FILE_XML_VERSION,1);

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

    // PDF export preferences
    tmp_node = xmlNewNode(NULL, BAD_CAST "chart_export_preferences");
    addXmlIntNode(tmp_node,"width",pref->chart.width);
    addXmlIntNode(tmp_node,"height",pref->chart.height);
    addXmlBoolNode(tmp_node,"total_points",pref->chart.total_points);
    xmlAddChild(racine, tmp_node);


    if(xmlSaveFormatFileEnc(filename,doc,"UTF-8",1) == -1)
        res = false;
    xmlFreeDoc(doc);

    return res;
}


/*!
 * \fn bool writeXmlPreferencesFileType(one_preferences *pref, char *home_path, preferences_type type)
 *  Write the preferences file withe the preferences selected
 * \param[in] home_path the path to the home directory
 * \param[in] pref a preferences
 * \param[in] type the type of preferences
 * \return true if everything is OK, false otherwise
 */
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
    case chart_type:
        pref_glob.chart = pref->chart;
        break;
    }

    return writeXmlPreferencesFile(&pref_glob,home_path);
}


/*!
 * \fn bool readXmlPreferencesFile(preferences *pref, char *home_path)
 *  Read the preferences file
 * \param[in] home_path the path to the home directory
 * \param[in] pref the preferences structure
 */
void readXmlPreferencesFile(preferences *pref, char *home_path)
{
    xmlDocPtr doc;
    xmlNodePtr root,tmp_node;
    char filename[SIZE_MAX_FILE_NAME];
    float version;

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

        pref->chart.height = 500;
        pref->chart.width = 800;
        pref->chart.total_points = true;

        return;
    }

    // Check root
    root = xmlDocGetRootElement(doc);
    if (!xmlStrEqual(root->name,xmlCharStrdup("csu_preferences")))
    {
        printf(_("Not a csu preferences file\n"));
        xmlFreeDoc(doc);
        return;
    }

    // Version
    tmp_node = xmlFirstElementChild(root);
    version = convertStringFloat((char *)xmlNodeGetContent(tmp_node));
    if (version > PREFERENCES_FILE_XML_VERSION)
    {
        printf(_("This version of Csuper only support preferences file version of %.1f.\n")
               ,PREFERENCES_FILE_XML_VERSION);
        xmlFreeDoc(doc);
        return;
    }

    // Toolbar button
    tmp_node = xmlFirstElementChild(xmlNextElementSibling(tmp_node));
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


    // Chart export preferences
    tmp_node = xmlFirstElementChild(xmlNextElementSibling(tmp_node->parent));
    pref->chart.width = convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->chart.height = convertStringInt((char *)xmlNodeGetContent(tmp_node));
    tmp_node = xmlNextElementSibling(tmp_node);
    pref->chart.total_points = convertStringBool((char *)xmlNodeGetContent(tmp_node));


    xmlFreeDoc(doc);
}


/*!
 * \fn bool readXmlPreferencesFileType(one_preferences *pref, char *home_path, preferences_type type)
 *  Read the preferences file withe the preferences selected
 * \param[in] home_path the path to the home directory
 * \param[in] pref a preferences
 * \param[in] type the type of preferences
 * \return true if everything is OK, false otherwise
 */
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
    case chart_type:
        pref->chart = pref_glob.chart;
        break;
    }
}
