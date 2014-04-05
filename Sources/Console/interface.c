/*!
 * \file    interface.c
 * \brief   Fonctions qui gerent l'interface graphique du logiciel
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

 /*
 * interface.c
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

 #include "interface.h"


/*!
 * \fn void afficheFichier()
 *  Demande le nom d'un fichier et l'affiche
 */
void afficheFichier()
{
    char nom_fichier[TAILLE_MAX_NOM_FICHIER];
    Fichier_Jeu *ptr_struct_fichier;

    systemEfface();

    menuNomFichier(nom_fichier);

    if(lectureCheminFichier(nom_fichier)==FAUX)
        return;

    ptr_struct_fichier=lireFichier(nom_fichier);

    /*Si le fichier a bien ete lu affiche et ferme la structure*/
    if (ptr_struct_fichier != NULL)
    {
        afficherStruct(ptr_struct_fichier);

        if(depScoreMax(ptr_struct_fichier))
        {
            afficherPartieFinie(ptr_struct_fichier);
        }

        fermeeFichierStruct(ptr_struct_fichier);
    }

    systemPause();
}

/*!
 * \fn void supprimerFichierNom()
 *  Demande le nom d'un fichier et le supprime
 */
void supprimerFichierNom()
{
    char nom_fichier[TAILLE_MAX_NOM_FICHIER];

    systemEfface();
    menuNomFichier(nom_fichier);

    if(lectureCheminFichier(nom_fichier)==FAUX)
        return;

    supprimerFichier(nom_fichier);
    systemPause();
}

/*!
 * \fn void listerFichier()
 *  Liste tout les fichier du dossier courant contenant l'extension .jeu
 */
void listerFichier()
{
    struct dirent *lecture;
    DIR *rep;
    char jeu[4]=EXTENSION_FICHIER;
    char ext[4]="abc";
    char repertoire[TAILLE_MAX_NOM_FICHIER]=".";
    int i;

    systemEfface();

    if(lectureCheminFichier(repertoire)==FAUX)
        return;

    /*Lecture du repertoire*/
    rep = opendir(repertoire);

    printf("Voici tout vos fichiers de jeu :\n");

    /*Affichage du nom de tout les fichiers du repertoire*/
    while ((lecture = readdir(rep))) {
        /*Initialisation de ext*/
        for (i=0 ; i<3 ; i++)
            ext[i]='a';

        /*Lecture de l'extension du fichier courant*/
        for (i=strlen(lecture->d_name)-3 ; i<strlen(lecture->d_name) ; i++)
            ext[-strlen(lecture->d_name)+i+3]=lecture->d_name[i];

        /*Si l'extension est celle d'un fichier jeu, on l'affiche*/
        if (strcmp(jeu,ext)==0)
            printf("\t- %s\n", lecture->d_name);
    }

    closedir(rep);
    systemPause();
}

/*!
 * \fn void jouer(Fichier_Jeu *ptr_struct_fichier, char *nom_fichier)
 *  Lance la partie de comptage jusqu'a la fin
 * \param[in,out] *ptr_struct_fichier la structure Fichier_Jeu
 * \param[in] *nom_fichier le nom du fichier dans lequel on stocke les informations
 */
void jouer(Fichier_Jeu *ptr_struct_fichier, char *nom_fichier)
{
    int continuer=FAUX;

    systemEfface();
    afficherScore(ptr_struct_fichier);

    /*Fait compter les points*/
    do
    {
        menuPointsJoueur(ptr_struct_fichier);

        /*Ecrit le nouveau score sur le fichier et verifie si l'ecriture du fichier s'est bien passe*/
        if (!nouveauScore(nom_fichier,ptr_struct_fichier))
        {
            systemPause();
        }

        systemEfface();
        afficherScore(ptr_struct_fichier);

        if (depScoreMax(ptr_struct_fichier))
            continuer=FAUX;

        else
            continuer=menuContinuer();

    } while (continuer==VRAI);

    afficherPartieFinie(ptr_struct_fichier);

    if (menuSupprimer())
    {
        supprimerFichier(nom_fichier);
        systemPause();
    }

    systemEfface();
    afficherStruct(ptr_struct_fichier);
    fermeeFichierStruct(ptr_struct_fichier);
    systemPause();
}

/*!
 * \fn void nouvellePartie()
 *  Initialise une nouvelle partie et lance la fonction de comptage des points
 */
void nouvellePartie()
{
    Fichier_Jeu *ptr_struct_fichier;
    float nb_joueurs;
    game_config config;
    int ecriture_fichier;
    char nom_distribue[TAILLE_MAX_NOM];
    char nom_fichier[TAILLE_MAX_NOM_FICHIER];

    systemEfface();
    menuNomFichier(nom_fichier);

    if(lectureCheminFichier(nom_fichier)==FAUX)
        return;

    menuDebutPartie(&nb_joueurs,&config);

    ptr_struct_fichier=creerFichierStruct(nb_joueurs,config);
    menuNomJoueur(ptr_struct_fichier);

    if (config.use_distributor)
    {
        menuDistribue(nom_distribue);
        ajoutDistribueStruct(ptr_struct_fichier,nom_distribue);
    }

    ecriture_fichier=ecrireFichier(nom_fichier,ptr_struct_fichier);

    systemPause();

    if (ecriture_fichier)
        jouer(ptr_struct_fichier,nom_fichier);
    else
        fermeeFichierStruct(ptr_struct_fichier);
}

/*!
 * \fn void chargerPartie()
 *  Charge une partie a partir d'un fichier et lance la fonction de comptage des points
 */
void chargerPartie()
{
    Fichier_Jeu *ptr_struct_fichier;
    char nom_fichier[TAILLE_MAX_NOM_FICHIER];

    systemEfface();
    menuNomFichier(nom_fichier);

    if(lectureCheminFichier(nom_fichier)==FAUX)
        return;

    ptr_struct_fichier=lireFichier(nom_fichier);

    if (ptr_struct_fichier == NULL)
    {
        systemPause();
        return;
    }

    afficherStruct(ptr_struct_fichier);

    if(depScoreMax(ptr_struct_fichier))
    {
        afficherPartieFinie(ptr_struct_fichier);
        systemPause();
    }

    else
    {
        systemPause();
        jouer(ptr_struct_fichier,nom_fichier);
    }
}

/*!
 * \fn void menuPrincipal()
 *  Lance un menu que redirige vers l'action que l'on veut effectuer
 */
void menuPrincipal()
{
    int choix;
    int arret = FAUX;

    do
    {
        choix=-1;

        systemEfface();

        printf("Csuper - Compteur de Score Universel Permettant l'Exemption de Reflexion v2.1.8\n\nQue voulez vous faire ?\n "
        "(%d) Faire une nouvelle partie \n (%d) Charger une partie existente \n (%d) Afficher les resultats d'une partie existante "
        "\n (%d) Supprimer une partie \n (%d) Afficher toutes les parties existantes",nouvPart,charPart,affFich,supprFich,listFich);
        printf("\n (%d) Afficher le menu des preferences \n (%d) Quitter le programme\n\nVotre choix : ",pref,quit);

        saisieClavierEntier(&choix);

        switch (choix) {
            case nouvPart  :    nouvellePartie();
                                break;
            case charPart  :    chargerPartie();
                                break;
            case affFich  :     afficheFichier();
                                break;
            case supprFich  :   supprimerFichierNom();
                                break;
            case listFich  :    listerFichier();
                                break;
            case pref :         menuPreferences();
                                break;
            case quit  :        printf("\nVous avez choisi de quitter le programme.\n\n");
                                arret=VRAI;
                                break;
            case easterEggs :   printf("\nEffectivement c'est la bonne reponse mais ca ne m'aide pas a savoir ce que vous voulez faire.\n");
                                systemPause();
                                break;
            default :           mauvais_choix();
                                systemPause();
        }

        systemEfface();

	} while (arret==FAUX);
}

void menuPreferences()
{
    int choix;
    int arret = FAUX;

    do
    {
        choix=-1;

        systemEfface();

        printf("\nQue voulez vous faire ?\n ");
        #ifndef PORTABLE
        printf(" \n (%d) Choisir un nouveau dossier d'enregistrement des fichiers \n (%d) Affiche le dossier d'enregistrement des fichiers",nouvChem,lireChem);
        #endif
        printf("\n (%d) Faire une nouvelle configuration de jeu\n (%d) Supprimer une configuration de jeu",newGameConf,removeGameConf);
        printf("\n (%d) Afficher la liste des configurations de jeu\n (%d) Afficher une configuration de jeu",printListGameConf,printGameConf);
        printf("\n (%d) Revenir au menu principal\n\nVotre choix : ",menuPrinc);

        saisieClavierEntier(&choix);

        switch (choix) {
            #ifndef PORTABLE
            case nouvChem   :   nouveauCheminFichier();
                                break;
            case lireChem :     lireCheminFichier();
                                break;
            #endif
            case menuPrinc  :   printf("\nVous avez choisi de quitter le programme.\n\n");
                                arret=VRAI;
                                break;
            case newGameConf :  newGameConfig();
                                break;
            case removeGameConf:removeGameConfig();
                                break;
            case printListGameConf:printListGameConfig();
                                break;
            case printGameConf: printGameConfigFile();
                                break;
            case easterEggs2 :  printf("\nEffectivement c'est la bonne reponse mais ca ne m'aide pas a savoir ce que vous voulez faire.\n");
                                systemPause();
                                break;
            default :           mauvais_choix();
                                systemPause();
        }

        systemEfface();

	} while (arret==FAUX);
}

/*!
 * \fn void nouveauCheminFichier()
 *  Charge un nouveau chemin que l'on demande a l'utilisateur
 */
void nouveauCheminFichier()
{
    char nouveauChemin[TAILLE_MAX_NOM_FICHIER];

    systemEfface();

    menuNouveauChemin(nouveauChemin);
    changerCheminFichier(nouveauChemin);

    systemPause();
}

/*!
 * \fn void lireCheminFichier()
 *  Lis le chemin de fichier et l'affiche
 */
void lireCheminFichier()
{
    char chemin[TAILLE_MAX_NOM_FICHIER]="";

    systemEfface();

    lectureCheminFichier(chemin);

    printf("Vos fichiers sont sauvegardes dans %s\n",chemin);
    systemPause();
}

/*!
 * \fn void chargerPartieLocale(char *nom_fichier)
 *  Charge une partie a partir d'un fichier dont le nom a ete donne et lance la fonction de comptage des points
 * \param[in] nom_fichier, le nom du fichier
 */
void chargerPartieLocale(char *nom_fichier)
{
    Fichier_Jeu *ptr_struct_fichier;

    systemEfface();

    ptr_struct_fichier=lireFichier(nom_fichier);

    if (ptr_struct_fichier == NULL)
    {
        systemPause();
        return;
    }

    afficherStruct(ptr_struct_fichier);

    if(depScoreMax(ptr_struct_fichier))
    {
        afficherPartieFinie(ptr_struct_fichier);
        systemPause();
    }

    else
    {
        systemPause();
        jouer(ptr_struct_fichier,nom_fichier);
    }
}

/*!
 * \fn void afficheFichierLocale(char *nom_fichier)
 *  Affiche le fichier dont le nom a ete donne en parametre
 */
void afficheFichierLocale(char *nom_fichier)
{
    Fichier_Jeu *ptr_struct_fichier;

    systemEfface();

    ptr_struct_fichier=lireFichier(nom_fichier);

    /*Si le fichier a bien ete lu affiche et ferme la structure*/
    if (ptr_struct_fichier != NULL)
    {
        afficherStruct(ptr_struct_fichier);

        if(depScoreMax(ptr_struct_fichier))
        {
            afficherPartieFinie(ptr_struct_fichier);
        }

        fermeeFichierStruct(ptr_struct_fichier);
    }

    systemPause();
}

/*!
 * \fn void newGameConfig()
 *  Add a new game configuration
 */
void newGameConfig()
{
    game_config config;

    systemEfface();
    menuNomFichier(config.name);
    menuGameConfig(&config);
    makeConfigFile(config);
}

/*!
 * \fn void removeGameConfig()
 *  Ask and remove a game configuration
 */
void removeGameConfig()
{
    int i;
    int choix_config;
    list_game_config *ptr_list_config;

    systemEfface();


    ptr_list_config = readConfigListFile();
    if (ptr_list_config->nb_config > 0)
    {
        /*Affichage des diffrentes configurations*/
        printf("\nQuelle configuration voulez vous utilisez ?\n");
        for (i=0 ; i<ptr_list_config->nb_config ; i++)
            printf("(%d) %s\n",i+1,ptr_list_config->name_game_config[i]);

        /*Demande du choix*/
        do
        {
            printf("\nVotre choix : ");
            saisieClavierEntier(&choix_config);
            printf("Vous avez choisi %d\n",choix_config);
        } while (choix_config <1 || choix_config >i);

        removeConfigListFile(choix_config-1,ptr_list_config);
    }

    else
        printf("\nVous n'avez pas encore de fichiers de configurations de jeu.\n");

    systemPause();
}

/*!
 * \fn void printListGameConfig()
 *  Print the list of game configuration
 */
void printListGameConfig()
{
    int i;
    list_game_config *ptr_list_config;

    systemEfface();

    ptr_list_config = readConfigListFile();
    printf("\nVoici la liste des configurations de jeu :\n");
    for (i=0 ; i<ptr_list_config->nb_config ; i++)
        printf("(%d) %s\n",i+1,ptr_list_config->name_game_config[i]);
    systemPause();
}

/*!
 * \fn void printGameConfig()
 *  Ask and print a game configuration
 */
void printGameConfigFile()
{
    int i;
    int choix_config;
    list_game_config *ptr_list_config;
    game_config config;

    systemEfface();

    /*Affichage des diffrentes configurations*/
    ptr_list_config = readConfigListFile();
    if (ptr_list_config->nb_config > 0)
    {
        printf("\nQuelle configuration voulez vous utilisez ?\n");
        for (i=0 ; i<ptr_list_config->nb_config ; i++)
            printf("(%d) %s\n",i+1,ptr_list_config->name_game_config[i]);

        /*Demande du choix*/
        do
        {
            printf("\nVotre choix : ");
            saisieClavierEntier(&choix_config);
            printf("Vous avez choisi %d\n",choix_config);
        } while (choix_config <1 || choix_config >i);

        readConfigFile(choix_config-1,ptr_list_config,&config);
        printGameConfig(config);
    }

    else
        printf("\nVous n'avez pas encore de fichiers de configurations de jeu.\n");

    systemPause();
}
