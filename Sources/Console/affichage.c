/*!
 * \file    affichage.c
 * \brief   Fonctions qui gerent l'affichage des scores du logiciel
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * affichage.c
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

 #include "affichage.h"

/*!
 * \fn void afficherNom(Fichier_Jeu *ptr_struct_fichier, int *ptr_taille_ligne)
 *  Affiche les noms des joueurs et calcule la taille de la ligne
 * \param[in] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 * \param[in,out] *ptr_taille_ligne un pointeur sur la taille de la ligne a modifier
 */
void afficherNom(Fichier_Jeu *ptr_struct_fichier, int *ptr_taille_ligne)
{
    int i;
    int j;

    /*Affichage du nom des joueurs*/
    printf("\n\t| ");
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        /*Affiche du nom du joueur*/
        printf("%s",ptr_struct_fichier->nom_joueur[i]);
        for (j=strlen(ptr_struct_fichier->nom_joueur[i]) ; j < 4 ; j++)
        {
            printf(" ");
            *ptr_taille_ligne+=1;
        }

        printf(" | ");

        /*Calcule de la taille de la ligne*/
        *ptr_taille_ligne+=(strlen(ptr_struct_fichier->nom_joueur[i])+3);
    }
}

 /*!
 * \fn void afficherLigne(int taille_ligne)
 *  Affiche taille_ligne - apres une tabulation
 * \param[in] taille_ligne la taille de la ligne
 */
void afficherLigne(int taille_ligne)
{
    int i;

    printf("\n\t");

    for (i=0 ; i<taille_ligne ; i++)
    {
        printf("-");
    }
}

/*!
 * \fn void afficherScoreTotal(Fichier_Jeu *ptr_struct_fichier)
 *  Affiche le score total des joueurs
 * \param[in] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void afficherScoreTotal(Fichier_Jeu *ptr_struct_fichier)
{
    int i;
    int j;

    printf("\nTotal   |");

    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        /*Affiche le score de la personne*/
        switch (ptr_struct_fichier->config.number_after_comma)
        {
        case 0 :
            printf("%6.0f",ptr_struct_fichier->point_tot[i]);
            break;
        case 1 :
            printf("%6.1f",ptr_struct_fichier->point_tot[i]);
            break;
        case 2 :
            printf("%6.2f",ptr_struct_fichier->point_tot[i]);
            break;
        case 3 :
            printf("%6.3f",ptr_struct_fichier->point_tot[i]);
            break;
        }

        /*Ajoute des espaces a la fin du score pour garder la mise en forme*/
        for (j=4 ; j<strlen(ptr_struct_fichier->nom_joueur[i]); j++)
        {
            printf(" ");
        }

        printf("|");
    }
}

/*!
 * \fn void afficherDistribue(Fichier_Jeu *ptr_struct_fichier)
 *  Affiche la personne devant distribuer si l'on utilise un distributeur
 * \param[in] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void afficherDistribue(Fichier_Jeu *ptr_struct_fichier)
{
    if (ptr_struct_fichier->config.use_distributor)
        printf("\nC'est a %s de distribuer.",ptr_struct_fichier->nom_joueur[(int)ptr_struct_fichier->distribue]);
    printf("\n");
}

/*!
 * \fn void afficherEnTete(Fichier_Jeu *ptr_struct_fichier)
 *  Affiche l'en tete de la structure
 * \param[in] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void afficherEnTete(Fichier_Jeu *ptr_struct_fichier)
{
    printf("\nFichier jeu\nCreer le %02.0f/%02.0f/%4.0f",ptr_struct_fichier->jour,ptr_struct_fichier->mois,ptr_struct_fichier->annee);
    printf("\nVersion du fichier : %1.1f",ptr_struct_fichier->version);
    printf("\nTaille maximum du nom : %.0f",ptr_struct_fichier->taille_max_nom);
    printf("\nNombre de joueur : %.0f",ptr_struct_fichier->nb_joueur);
    printGameConfig(ptr_struct_fichier->config);
    printf("Nombre de tours maximum : %d",maxNbTour(ptr_struct_fichier));
}

/*!
 * \fn void afficherScoreEntier(Fichier_Jeu *ptr_struct_fichier)
 *  Affiche tout les scores de touts les joueurs a chaque tour.
 * \param[in] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void afficherScoreEntier(Fichier_Jeu *ptr_struct_fichier)
{
    int i;
    int j;
    int k;

    int max_nb_tour = maxNbTour(ptr_struct_fichier);

    for (i=0 ; i<max_nb_tour ; i++)
    {
        /*Affiche le numero du tour quand on passe a un nouveau tour*/
        printf("\nTour %2.0f |",(float)i + 1);

        for (k=0 ; k<ptr_struct_fichier->nb_joueur ; k++)
        {
            /*Affiche le score de la personne a un tour*/
            if (ptr_struct_fichier->nb_tour[k] >= i+1)
            {
                switch (ptr_struct_fichier->config.number_after_comma)
                {
                case 0 :
                    printf("%6.0f",ptr_struct_fichier->point[k][i]);
                    break;
                case 1 :
                    printf("%6.1f",ptr_struct_fichier->point[k][i]);
                    break;
                case 2 :
                    printf("%6.2f",ptr_struct_fichier->point[k][i]);
                    break;
                case 3 :
                    printf("%6.3f",ptr_struct_fichier->point[k][i]);
                    break;
                }
            }
            else
                printf("      ");

            /*Ajoute des espaces a la fin du score pour garder la mise en forme*/
            for (j=4 ; j<(strlen(ptr_struct_fichier->nom_joueur[k])); j++)
            printf(" ");

            printf("|");
        }
    }
}

/*!
 * \fn void afficherPosition(Fichier_Jeu *ptr_struct_fichier)
 *  Affiche les positions des joueurs
 * \param[in] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void afficherPosition(Fichier_Jeu *ptr_struct_fichier)
{
    int i;
    int j;

    printf("\nPosition|");

    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        /*Affiche la position de la personne*/

        printf("%6.0f",ptr_struct_fichier->position[i]);

        /*Ajoute des espaces a la fin du score pour garder la mise en forme*/
        for (j=4 ; j<strlen(ptr_struct_fichier->nom_joueur[i]) ; j++)
        {
            printf(" ");
        }

        printf("|");
    }
}

/*!
 * \fn void afficherScore(Fichier_Jeu *ptr_struct_fichier)
 *  Affiche les noms des personnes aves leurs scores totaux ainsi que la personne devant distribuer
 *  a partir d'une structure Fichier_Jeu
 * \param[in] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void afficherScore(Fichier_Jeu *ptr_struct_fichier)
{
    int taille_ligne=1;

    afficherNom(ptr_struct_fichier,&taille_ligne);
    afficherLigne(taille_ligne);
    afficherScoreTotal(ptr_struct_fichier);
    afficherLigne(taille_ligne);
    afficherPosition(ptr_struct_fichier);
    if (ptr_struct_fichier->config.use_distributor)
        printf("\n");
    afficherDistribue(ptr_struct_fichier);
}

/*!
 * \fn void afficherStruct(Fichier_Jeu *ptr_struct_fichier)
 *  Affiche toutes les donnes d'une structure Fichier_Jeu
 * \param[in] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void afficherStruct(Fichier_Jeu *ptr_struct_fichier)
{
    int taille_ligne=1;

    afficherEnTete(ptr_struct_fichier);
    afficherDistribue(ptr_struct_fichier);
    afficherNom(ptr_struct_fichier,&taille_ligne);
    afficherLigne(taille_ligne);
    afficherScoreEntier(ptr_struct_fichier);
    afficherLigne(taille_ligne);
    afficherScoreTotal(ptr_struct_fichier);
    afficherLigne(taille_ligne);
    afficherPosition(ptr_struct_fichier);
    printf("\n");
}

/*!
 * \fn void afficherPartieFinie(Fichier_Jeu *ptr_struct_fichier)
 *  Affiche un podium des resultats
 * \param[in] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void afficherPartieFinie(Fichier_Jeu *ptr_struct_fichier)
{
    int pos[3]={0,1,2};
    int i;
    int un_pris=FAUX;
    int deux_pris=FAUX;

    printf("\nLa partie est terminee\n");

    /*Initialisation des positions des personnes dans le tableau*/
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        if (ptr_struct_fichier->position[i] == 3 || (un_pris && deux_pris && ptr_struct_fichier->position[i] == 1) || (deux_pris && ptr_struct_fichier->position[i] == 2))
            pos[2]=i;

        if ((ptr_struct_fichier->position[i] == 2 && !deux_pris ) || (un_pris && ptr_struct_fichier->position[i] == 1 && !deux_pris))
        {
            pos[1]=i;
            deux_pris=VRAI;
        }
        if (ptr_struct_fichier->position[i] == 1 && !un_pris)
        {
            pos[0]=i;
            un_pris=VRAI;
        }
    }

    printf("\n\t\t\t");

    /*Affiche le nom du premier*/
    afficherChaineTroisTab(ptr_struct_fichier->nom_joueur[pos[0]]);

    printf("\n");

    if(ptr_struct_fichier->nb_joueur >=2)
    {
        afficherChaineTroisTab(ptr_struct_fichier->nom_joueur[pos[1]]);
    }

    else
    {
        printf("\t\t\t");
    }

    /*On affiche le bas du podium pour le premier*/
    for (i=0 ; i<24 ; i++)
    {
        printf("-");
    }

    printf("\n");

    /*S'il y a plus de deux joueurs, on affiche le bas du podium pou le deuxieme*/
    if(ptr_struct_fichier->nb_joueur >=2)
    {
        for (i=0 ; i<24 ; i++)
        {
            printf("-");
        }
    }

    /*S'il y a plus de trois joueurs, on insere le troisime sur le podium*/
    if (ptr_struct_fichier->nb_joueur >= 3)
    {
        /*Laisse la place sous le nom du premier*/
        printf("\t\t\t");

        /*Affiche le nom du troisiemeejoueur*/
        afficherChaineTroisTab(ptr_struct_fichier->nom_joueur[pos[2]]);

        /*Passe a la ligne et passe la place des premiers et deuxieme*/
        printf("\n\t\t\t\t\t\t");

        /*Affiche le bas du podium pour le troisieme*/
        for (i=0 ; i<24 ; i++)
        {
            printf("-");
        }
    }

}

/*!
 * \fn void afficherChaineTroisTab(char *chaine)
 *  Affiche la chaine de caractere passe en parametre centrer sur un espace de trois tabulations
 * \param[in] *chaine une chaine de caractere
 */
void afficherChaineTroisTab(char *chaine)
{
    int i;
    int taille=strlen(chaine);

    for (i=0 ; i<(24-taille)/2 ; i++)
    {
        printf(" ");
    }

    printf("%s",chaine);

    for (i=0 ; i<(24-taille)/2 ; i++)
    {
        printf(" ");
    }
}

/*!
 * \fn void afficherLicense()
 *  Affiche la license
 */
void afficherLicense()
{
    printf("\nCsuper Copyright (C) 2014 Remi BERTHO <remi.bertho@gmail.com>\n"
    "Ce programme vient SANS ABSOLUMENT AUCUNE GARANTIE. \nCeci est un logiciel libre et vous etes invite a le redistribuer"
    " suivant certaines conditions. \nPour plus de detail : http://www.gnu.org/licenses/gpl.html\n");
}

/*!
 * \fn void printGameConfig(game_config config)
 *  Print the game config
 * \param[in] config a game config
 */
void printGameConfig(game_config config)
{
    printf("\nNom de la configuration de jeu : %s\n",config.name);
    printf("Utilise un nombre maximum : %d\n",config.max);
    #ifdef __unix__
    printf("Nombre de points maximum/minimum : %.3f\n",config.nb_max);
    #elif _WIN32
    if (config.nb_max == INFINITY)
        printf("Nombre de points maximum/minimum : inf\n");
    else
        printf("Nombre de points maximum/minimum : %.3f\n",config.nb_max);
    #endif
    printf("Score initial : %.3f\n",config.begin_score);
    printf("Nombre de chiffres apres la virgule utilise a l'affichage des points : %d\n",config.number_after_comma);
    printf("Sens du premier : %d\n",config.sens_premier);
    printf("Jeu en tour par tour : %d\n",config.tour_par_tour);
    printf("Utilise un distributeur tournant : %d\n",config.use_distributor);

}
