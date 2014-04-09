/*!
 * \file    csu_files.c
 * \brief   Fonction de gestion des fichiers
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

 /*
 * csu_files.c
 *
 * Copyright 2014 Remi BERTHO <remi.bertho@gmail.com>
 *
 * This file is part of Csuper.
 *
 * Csuper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper is distributed in the hope that it will be useful,
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

 #include "csu_files.h"



/*!
 * \fn FILE *openFileCsuExtension(char file_name[], char mode[])
 *  Ouvre un fichier a partir de son nom et du mode voulu en y ajouter l'extension du fichier si necessaire
 * \param[in] file_name[] le nom du fichier
 * \param[in] mode[] le mode voulu
 * \return un pointeur sur le fichier ouvert, NULL s'il y a eut un probleme
 */
FILE *openFileCsuExtension(char file_name[], char mode[])
{
    addFileCsuExtension(file_name);

    return openFile(file_name,mode);
}


/*!
 * \fn csuStruct *readCsuFile(char *file_name)
 *  Lis ce qu'il y a dans le fichier avec le nom donne en parametre et le met dans une structure
 *  csuStruct rendu par la fonction
 * \param[in] file_name[] le nom du fichier
 * \return un pointeur sur la structure csuStruct cree, NULL s'il y a un probleme d'ouverture du fichier
 */
csuStruct *readCsuFile(char *file_name)
{
    csuStruct *ptr_csu_struct=NULL;
    int i;
    char *player_name_temp;
    FILE *ptr_file;
    char check_file[sizeof(STRING_CHECK_CSU_FILE)];
    int file_size;
    int check_file_size=0;

    libcsuper_initialize();

    ptr_file=openFileCsuExtension(file_name,"rb");

    if (ptr_file == NULL)
    {
        printf(_("\nError: The file could not be read.\n"));
        return ptr_csu_struct;
    }

    fseek(ptr_file,0,SEEK_SET);

    file_size=readFileSize(ptr_file);

    check_file_size+=fread(check_file,sizeof(char),sizeof(STRING_CHECK_CSU_FILE),ptr_file);

    /*Si la chaine de verification ne correspond pas, on ferme le fichier et on retourne une structure vide*/
    if (strcmp(STRING_CHECK_CSU_FILE,check_file) != 0)
    {
        printf(_("\nError: File not compatible.\n"));
        closeFile(ptr_file);
        return ptr_csu_struct;
    }

    /*Allocation memoire de la structure*/
    ptr_csu_struct=(csuStruct *)myAlloc(sizeof(csuStruct));

    /*Lecture et verification de l version du fichier*/
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->version),sizeof(float),1,ptr_file));
    if (ptr_csu_struct->version + 0.01 < VERSION)
    {
        printf(_("\nError the file's version is the %1.1f while the software only support files with versions"
               " higher than the %1.1f.\n"),ptr_csu_struct->version,VERSION);
        closeFile(ptr_file);
        return NULL;
    }

    /*Lecture des differentes variables du fichier dans la structure*/
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->size_max_name),sizeof(float),1,ptr_file));
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->day),sizeof(float),1,ptr_file));
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->month),sizeof(float),1,ptr_file));
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->year),sizeof(float),1,ptr_file));
    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->nb_player),sizeof(float),1,ptr_file));
    check_file_size+=(sizeof(game_config)*fread(&(ptr_csu_struct->config),sizeof(game_config),1,ptr_file));

    /*Allocation memoire du tableau de chaine de caractere pour le nom des personnes*/
    ptr_csu_struct->player_names=(char **)myAlloc(ptr_csu_struct->nb_player*sizeof(char*));

    /*Allocation memoire des noms des personnes*/
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        ptr_csu_struct->player_names[i]=(char *)myAlloc(ptr_csu_struct->size_max_name*sizeof(char));

    /*Allocation du tableau de caractere player_name_temp ou vas etre stocke le nom des personnes en tant que tampon*/
    player_name_temp=(char *)myAlloc(sizeof(char)*ptr_csu_struct->size_max_name);

    /*Lecture du nom des personnes dans la structure*/
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
    {
        check_file_size+=fread(player_name_temp,sizeof(char),ptr_csu_struct->size_max_name,ptr_file);
        strcpy(ptr_csu_struct->player_names[i],player_name_temp);
    }

    free(player_name_temp);

    /*Allocation memoire et lecture des points totaux*/
    ptr_csu_struct->total_points=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    check_file_size+=(sizeof(float)*fread(ptr_csu_struct->total_points,sizeof(float),ptr_csu_struct->nb_player,ptr_file));

    /*Allocation memoire et lecture des ranks*/
    ptr_csu_struct->rank=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    check_file_size+=(sizeof(float)*fread(ptr_csu_struct->rank,sizeof(float),ptr_csu_struct->nb_player,ptr_file));

    /*Allocation memoire et lecture du nombre de tours*/
    ptr_csu_struct->nb_turn=(float *)myAlloc(ptr_csu_struct->nb_player*sizeof(float));
    check_file_size+=(sizeof(float)*fread(ptr_csu_struct->nb_turn,sizeof(float),ptr_csu_struct->nb_player,ptr_file));

    check_file_size+=(sizeof(float)*fread(&(ptr_csu_struct->distributor),sizeof(float),1,ptr_file));

    /*Allocation memoire du tableau de points points*/
    ptr_csu_struct->point=(float **)malloc(ptr_csu_struct->nb_player*sizeof(float*));
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        ptr_csu_struct->point[i]=(float *)myAlloc(ptr_csu_struct->nb_turn[i]*sizeof(float));

    /*Lecture des points*/
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        check_file_size+=(sizeof(float)*fread(ptr_csu_struct->point[i],sizeof(float),ptr_csu_struct->nb_turn[i],ptr_file));

    closeFile(ptr_file);

    /*Verifie si la lecture s'est bien passee*/
    if (file_size != check_file_size)
    {
        printf(_("\nError while reading file.\n"));
        return NULL;
    }

    return ptr_csu_struct;
}

/*!
 * \fn int writeCsuFile(char *file_name, csuStruct *ptr_csu_struct)
 *  Cree un fichier .jeu qui contient toutes les informations de la structure csuStruct mis en parametre
 * \param[in] *file_name le nom du fichier
 * \param[in] *ptr_csu_struct la structure du fichier avec lequel on veut cree le fichier
 * \return TRUE si tout s'est bien passe, FALSE sinon
 */
int writeCsuFile(char *file_name, csuStruct *ptr_csu_struct)
{
    int i;
    FILE *ptr_file;

    libcsuper_initialize();

    ptr_file=openFileCsuExtension(file_name,"w+");

    if (ptr_file == NULL)
    {
        printf(_("\nError while writing file.\n"));
        return FALSE;
    }

    fseek(ptr_file,0,SEEK_SET);

    fwrite(STRING_CHECK_CSU_FILE,sizeof(char),sizeof(STRING_CHECK_CSU_FILE),ptr_file);
    fwrite(&(ptr_csu_struct->version),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->size_max_name),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->day),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->month),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->year),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->nb_player),sizeof(float),1,ptr_file);
    fwrite(&(ptr_csu_struct->config),sizeof(game_config),1,ptr_file);

    /*Ecriture des noms des personnes*/
    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        fwrite(ptr_csu_struct->player_names[i],sizeof(char),ptr_csu_struct->size_max_name,ptr_file);

    fwrite(ptr_csu_struct->total_points,sizeof(float),ptr_csu_struct->nb_player,ptr_file);
    fwrite(ptr_csu_struct->rank,sizeof(float),ptr_csu_struct->nb_player,ptr_file);
    fwrite(ptr_csu_struct->nb_turn,sizeof(float),ptr_csu_struct->nb_player,ptr_file);
    fwrite(&(ptr_csu_struct->distributor),sizeof(float),1,ptr_file);

    for (i=0 ; i<ptr_csu_struct->nb_player ; i++)
        fwrite(ptr_csu_struct->point[i],sizeof(float),ptr_csu_struct->nb_turn[i],ptr_file);

    closeFile(ptr_file);

    return TRUE;
}

/*!
 * \fn void writeFileNewTurn(char *file_name, csuStruct *ptr_csu_struct)
 *  Mets a day le fichier avec les nouveaux scores
 * \param[in] *file_name le nom du fichier
 * \param[in] *ptr_csu_struct la structure du fichier avec lequel on veut mettre un nouveau score
 * \return TRUE si tout s'est bien passe, FALSE sinon
 */
int writeFileNewTurn(char *file_name, csuStruct *ptr_csu_struct)
{
    char file_name_2[SIZE_MAX_FILE_NAME+4];
    int successful;

    sprintf(file_name_2,"%s_tmp",file_name);

    successful=writeCsuFile(file_name_2,ptr_csu_struct);

    if (successful)
    {
        if(deleteCsuFile(file_name))
        {
            if(renameCsuFile(file_name_2,file_name))
                return TRUE;
        }
    }

    return FALSE;
}

/*!
 * \fn int deleteCsuFile(char *file_name)
 *  Supprime le fichier dont le nom est en parametre
 * \param[in] *file_name le nom du fichier
 * \return TRUE si tout s'est bien passe, FALSE sinon
 */
int deleteCsuFile(char *file_name)
{
    addFileCsuExtension(file_name);

    libcsuper_initialize();

    if(remove(file_name))
    {
        printf(_("\nThe file %s cannot be deleted.\n"),file_name);
        perror("");
        return FALSE;
    }

    else
    {
        printf(_("\nThe file %s was well deleted.\n"),file_name);
        return TRUE;
    }
}

/*!
 * \fn int renameCsuFile(char *old_name, char *new_name)
 *  Renomme le fichier dont le nom est en parametre
 * \param[in] *old_name l'ancien nom du fichier
 * \param[in] *new_name le nouveau nom du fichier
 * \return TRUE si tout s'est bien passe, FALSE sinon
 */
int renameCsuFile(char *old_name, char *new_name)
{
    char old_name_2[SIZE_MAX_NAME+8];
    char new_name_2[SIZE_MAX_NAME+4];

    libcsuper_initialize();

    sprintf(old_name_2,"%s",old_name);
    addFileCsuExtension(old_name_2);
    sprintf(new_name_2,"%s",new_name);
    addFileCsuExtension(new_name_2);

    if(rename(old_name_2,new_name_2))
    {
        printf(_("\nThe file %s cannot be renamed.\n"),old_name_2);
        return FALSE;
    }

    else
    {
        printf(_("\nThe file %s was well renamed in %s.\n"),old_name_2,new_name_2);
        return TRUE;
    }
}

