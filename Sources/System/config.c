/*!
 * \file    config.c
 * \brief   Fonction des fichiers lies a la config
 * \author  Remi BERTHO
 * \date    27/03/14
 * \version 2.2.0
 */

 /*
 * config.c
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

 #include "config.h"

/*!
 * \fn list_game_config *makeListGameConfig(int nb_config)
 *  Cree une structure list_game_config
 * \parma[in] nb_config le nombre de configuration disponible
 * \return une list_game_config
 */
list_game_config *makeListGameConfig(int nb_config)
 {
     int i;
     list_game_config *config=(list_game_config *)myAlloc(sizeof(list_game_config));
     config->nb_config=nb_config;
     config->name_game_config = (char **)myAlloc(nb_config*sizeof(char*));
     for (i=0 ; i< nb_config ; i++)
        config->name_game_config[i]=(char *)myAlloc(sizeof(char)*TAILLE_MAX_NOM_FICHIER);
    return config;
 }

/*!
 * \fn void freeListGameConfig(list_game_config *ptr_list_config)
 *  Desalloue une structure list_game_config
 * \parma[in] ptr_list_config un pointeur sur un list_game_config
 */
void freeListGameConfig(list_game_config *ptr_list_config)
 {
     int i;
     for (i=0 ; i<ptr_list_config->nb_config ; i++)
        free(ptr_list_config->name_game_config[i]);
     free(ptr_list_config->name_game_config);
     free(ptr_list_config);
 }

 /*!
 * \fn int makeConfigListFile()
 *  Cree les dossier et le fichier qui va contenir les configs
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int makeConfigListFile()
{
    char repertoire[TAILLE_MAX_NOM_FICHIER]="";
    char nom_fichier[TAILLE_MAX_NOM_FICHIER]="";
    FILE *ptr_fichier;

    /*Lecture du chemin Document et creation du dossier au bonne endroit et de la chaine qui va contenir le fichier*/
    #ifndef PORTABLE
    #ifdef __unix__
    strcpy(repertoire,getenv("HOME"));
    #elif _WIN32
    strcpy(repertoire,getenv("USERPROFILE"));
    #endif
    sprintf(repertoire,"%s/",repertoire);
    #endif // PORTABLE

    sprintf(repertoire,"%s%s",repertoire,NOM_DOSSIER_CSUPER);

    #ifdef __unix__
    mkdir(repertoire, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(repertoire);
    #endif

    sprintf(nom_fichier,"%s/%s",repertoire,NOM_FICHIER_CONFIG);

    sprintf(repertoire,"%s/%s",repertoire,NOM_DOSSIER_CONFIG);
    #ifdef __unix__
    mkdir(repertoire, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(repertoire);
    #endif


    ptr_fichier=ouvrirFichier(nom_fichier,"w+");

    if (ptr_fichier==NULL)
        return FAUX;

    fprintf(ptr_fichier,"%d",0);

    fermerFichier(ptr_fichier);

    return VRAI;
}

/*!
 * \fn list_game_config *readConfigListFile()
 *  Cree une structure list_game_config a partir du fichier de configuration
 * \return une list_game_config
 */
list_game_config *readConfigListFile()
{
    char nom_fichier_config[TAILLE_MAX_NOM_FICHIER]="";
    FILE *ptr_fichier;
    list_game_config *ptr_config;
    int nb_config;
    int i;

    /*Lecture du chemin Document et creation du nom de fichier du fichier config*/
    #ifndef PORTABLE
    #ifdef __unix__
    strcpy(nom_fichier_config,getenv("HOME"));
    #elif _WIN32
    strcpy(nom_fichier_config,getenv("USERPROFILE"));
    #endif
    sprintf(nom_fichier_config,"%s/",nom_fichier_config);
    #endif // PORTABLE
    sprintf(nom_fichier_config,"%s%s/%s",nom_fichier_config,NOM_DOSSIER_CSUPER,NOM_FICHIER_CONFIG);

    ptr_fichier=ouvrirFichier(nom_fichier_config,"r");

    if(ptr_fichier == NULL)
    {
        makeConfigListFile();
        ptr_fichier=ouvrirFichier(nom_fichier_config,"r");
    }

    /*Lis le nombre de config*/
    fscanf(ptr_fichier,"%d",&nb_config);

    ptr_config=makeListGameConfig(nb_config);

    for (i=0 ; i< nb_config ; i++)
        fscanf(ptr_fichier,"%s",ptr_config->name_game_config[i]);

    fermerFichier(ptr_fichier);

    return ptr_config;
}

/*!
 * \fn int addConfigListFile(list_game_config *ptr_list_config, char *new_config_name)
 *  Ajoute une nouvelle configuration dans le fichier qui les liste
 * \param[in] new_config_game le nom de la nouvelle configuration
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int addConfigListFile(char *new_config_name)
{
    char nom_fichier_config[TAILLE_MAX_NOM_FICHIER]="";
    FILE *ptr_fichier;
    int i;
    list_game_config *ptr_list_config =readConfigListFile();

    /*Lecture du chemin Document et creation du nom de fichier du fichier config*/
    #ifndef PORTABLE
    #ifdef __unix__
    strcpy(nom_fichier_config,getenv("HOME"));
    #elif _WIN32
    strcpy(nom_fichier_config,getenv("USERPROFILE"));
    #endif
    sprintf(nom_fichier_config,"%s/",nom_fichier_config);
    #endif // PORTABLE
    sprintf(nom_fichier_config,"%s%s/%s",nom_fichier_config,NOM_DOSSIER_CSUPER,NOM_FICHIER_CONFIG);


    ptr_fichier=ouvrirFichier(nom_fichier_config,"w");

    if(ptr_fichier == NULL)
        return FAUX;

    fprintf(ptr_fichier,"%d\n",ptr_list_config->nb_config+1);

    for (i=0 ; i< ptr_list_config->nb_config ; i++)
        fprintf(ptr_fichier,"%s\n",ptr_list_config->name_game_config[i]);

    fprintf(ptr_fichier,"%s",new_config_name);

    fermerFichier(ptr_fichier);
    freeListGameConfig(ptr_list_config);

    return VRAI;
}

/*!
 * \fn int removeConfigListFile(int num_suppr, list_game_config *ptr_list_config)
 *  Enleve une configuration du fichier qui les liste
 * \param[in] num_sppr le numero de la config a supprimer
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int removeConfigListFile(int num_suppr, list_game_config *ptr_list_config)
{
    char nom_fichier_config[TAILLE_MAX_NOM_FICHIER]="";
    FILE *ptr_fichier;
    int i;
    ptr_list_config=readConfigListFile();

    /*Lecture du chemin Document et creation du nom de fichier du fichier config*/
    #ifndef PORTABLE
    #ifdef __unix__
    strcpy(nom_fichier_config,getenv("HOME"));
    #elif _WIN32
    strcpy(nom_fichier_config,getenv("USERPROFILE"));
    #endif
    sprintf(nom_fichier_config,"%s/",nom_fichier_config);
    #endif // PORTABLE
    sprintf(nom_fichier_config,"%s%s/%s",nom_fichier_config,NOM_DOSSIER_CSUPER,NOM_FICHIER_CONFIG);


    ptr_fichier=ouvrirFichier(nom_fichier_config,"w+");

    if(ptr_fichier == NULL)
        return FAUX;

    fprintf(ptr_fichier,"%d\n",ptr_list_config->nb_config-1);

    for (i=0 ; i< ptr_list_config->nb_config ; i++)
    {
        if (i!=num_suppr)
            fprintf(ptr_fichier,"%s\n",ptr_list_config->name_game_config[i]);
        else
            removeConfigFile(ptr_list_config->name_game_config[i]);
    }

    fermerFichier(ptr_fichier);
    freeListGameConfig(ptr_list_config);

    return VRAI;
}

 /*!
 * \fn int makeConfigFile(game_config config, char *config_name)
 *  Cree un fichier de configs de jeu
 * \param[in] config la config du jeu
 * \param[in] config_name le nom de la config
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int makeConfigFile(game_config config, char *config_name)
{
    char repertoire[TAILLE_MAX_NOM_FICHIER]="";
    char nom_fichier[TAILLE_MAX_NOM_FICHIER]="";
    FILE *ptr_fichier;

    /*Lecture du chemin Document et creation du dossier au bonne endroit et de la chaine qui va contenir le fichier*/
    #ifndef PORTABLE
    #ifdef __unix__
    strcpy(repertoire,getenv("HOME"));
    #elif _WIN32
    strcpy(repertoire,getenv("USERPROFILE"));
    #endif
    sprintf(repertoire,"%s/",repertoire);
    #endif // PORTABLE

    sprintf(repertoire,"%s%s",repertoire,NOM_DOSSIER_CSUPER);

    #ifdef __unix__
    mkdir(repertoire, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(repertoire);
    #endif

    sprintf(repertoire,"%s/%s",repertoire,NOM_DOSSIER_CONFIG);
    #ifdef __unix__
    mkdir(repertoire, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(repertoire);
    #endif

    sprintf(nom_fichier,"%s/%s",repertoire,config_name);

    ptr_fichier=ouvrirFichier(nom_fichier,"w+");

    if (ptr_fichier==NULL)
        return FAUX;

    fprintf(ptr_fichier,"%f %d %d %d %d",config.nb_max,config.sens_premier,config.tour_par_tour,config.use_distributor,config.number_after_comma);

    fermerFichier(ptr_fichier);

    addConfigListFile(config_name);

    return VRAI;
}

 /*!
 * \fn int removeConfigFile(char *config_name)
 *  Supprime un fichier de configs de jeu
 * \param[in] config_name le nom de la configuration de jeu
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int removeConfigFile(char *config_name)
{
    char repertoire[TAILLE_MAX_NOM_FICHIER]="";
    char nom_fichier[TAILLE_MAX_NOM_FICHIER]="";

    /*Lecture du chemin Document et creation du dossier au bonne endroit et de la chaine qui va contenir le fichier*/
    #ifndef PORTABLE
    #ifdef __unix__
    strcpy(repertoire,getenv("HOME"));
    #elif _WIN32
    strcpy(repertoire,getenv("USERPROFILE"));
    #endif
    sprintf(repertoire,"%s/",repertoire);
    #endif // PORTABLE

    sprintf(repertoire,"%s%s",repertoire,NOM_DOSSIER_CSUPER);

    #ifdef __unix__
    mkdir(repertoire, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(repertoire);
    #endif

    sprintf(repertoire,"%s/%s",repertoire,NOM_DOSSIER_CONFIG);
    #ifdef __unix__
    mkdir(repertoire, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #elif _WIN32
    mkdir(repertoire);
    #endif

    sprintf(nom_fichier,"%s/%s",repertoire,config_name);

    if(remove(nom_fichier))
    {
        printf("\nLe fichier %s n'a pas pu etre supprime.\n",nom_fichier);
        perror("");
        return FAUX;
    }
    else
    {
        printf("\nLe fichier %s a bien ete supprime.\n",nom_fichier);
        return VRAI;
    }

    return VRAI;
}

/*!
 * \fn int readConfigFile(int num_read, list_game_config *ptr_list_config, game_config *ptr_config)
 *  Lis un fichier de configuration de jeu
 * \param[in] num_read le numero de la liste de config a lire
 * \param[in] ptr_list_config un pointeur sur une liste de configuration  de jeu
 * \param[in] ptr_config un pointeur sur une configuration de jeu
 * \return une list_game_config
 */
int readConfigFile(int num_read, list_game_config *ptr_list_config, game_config *ptr_config)
{
    char nom_fichier_config[TAILLE_MAX_NOM_FICHIER]="";
    FILE *ptr_fichier;

    /*Lecture du chemin Document et creation du nom de fichier du fichier config*/
    #ifndef PORTABLE
    #ifdef __unix__
    strcpy(nom_fichier_config,getenv("HOME"));
    #elif _WIN32
    strcpy(nom_fichier_config,getenv("USERPROFILE"));
    #endif
    sprintf(nom_fichier_config,"%s/",nom_fichier_config);
    #endif // PORTABLE
    sprintf(nom_fichier_config,"%s%s/%s/%s",nom_fichier_config,NOM_DOSSIER_CSUPER,NOM_DOSSIER_CONFIG,ptr_list_config->name_game_config[num_read]);

    ptr_fichier=ouvrirFichier(nom_fichier_config,"r");

    if(ptr_fichier == NULL)
        return FAUX;

    /*Lis le nombre de config*/
    fscanf(ptr_fichier,"%f%d%d%d%d",&(ptr_config->nb_max),(int *)&(ptr_config->sens_premier),(int *)&(ptr_config->tour_par_tour),(int *)&(ptr_config->use_distributor),(int *)&(ptr_config->number_after_comma));

    fermerFichier(ptr_fichier);

    freeListGameConfig(ptr_list_config);

    return VRAI;
}
