/*!
 * \file    structure.c
 * \brief   Fonction de gestion des fichiers de la struction contenant les informations
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * structure.c
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

 #include "structure.h"

/*!
 * \fn Fichier_Jeu *creerFichierStruct(float nb_joueur , float nb_max, char sens_premier)
 *  Cree une structure Fichier_jeu a partir des donnees de la fonction.
 * \param[in] nb_joueur le nombre de joueur
 * \param[in] nb_max le nombre maximum de points
 * \param[in] sens_premier permet de savoir dans quelle sens est calculer le premier
 * \return un pointeur sur le structure Fichier_Jeu cree
 */
Fichier_Jeu *creerFichierStruct(float nb_joueur , float nb_max, char sens_premier)
{
    Fichier_Jeu *ptr_struct_fichier;
    int i;
    time_t timestamp;
    struct tm *t;

    /*Allocation memoire de la structure*/
    if ((ptr_struct_fichier=(Fichier_Jeu *)malloc(sizeof(Fichier_Jeu))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Copie de certaines variables dans la structure*/
    ptr_struct_fichier->taille_max_nom=TAILLE_MAX_NOM;
    ptr_struct_fichier->version=VERSION;
    ptr_struct_fichier->nb_joueur=nb_joueur;
    ptr_struct_fichier->nb_max=nb_max;
    ptr_struct_fichier->distribue=0;
    ptr_struct_fichier->nb_tour=0;
    ptr_struct_fichier->sens_premier=sens_premier;

    /*Allocation memoire du tableau de chaine de caractere pour le nom des personnes*/
    if ((ptr_struct_fichier->nom_joueur=(char **)malloc(nb_joueur*sizeof(char*))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Allocation memoire des noms des personnes*/
    for (i=0 ; i<nb_joueur ; i++)
    {
        if ((ptr_struct_fichier->nom_joueur[i]=(char *)malloc(TAILLE_MAX_NOM*sizeof(char))) == NULL)
        {
            printf("\nProbleme allocation memoire\n");
            perror("");
            exit(0);
        }
    }

    /*Allocation memoire des points totaux*/
    if ((ptr_struct_fichier->point_tot=(float *)malloc(nb_joueur*sizeof(float))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Allocation memoire de positions*/
    if ((ptr_struct_fichier->position=(float *)malloc(nb_joueur*sizeof(float))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Initialisation des points totaux et de la position a zero*/
    for (i=0 ; i<nb_joueur ; i++)
    {
        ptr_struct_fichier->point_tot[i]=0;
        ptr_struct_fichier->position[i]=1;
    }

    /*Allocation memoire des points*/
    if ((ptr_struct_fichier->point=(float *)malloc(0)) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Enregistrement de la date courante dans la structure*/
    timestamp = time(NULL);
    t = localtime(&timestamp);
    ptr_struct_fichier->annee=(t->tm_year+1900);
    ptr_struct_fichier->mois=(t->tm_mon+1);
    ptr_struct_fichier->jour=(t->tm_mday);

    return ptr_struct_fichier;
}

/*!
 * \fn void fermeeFichierStruct(Fichier_Jeu *ptr_struct_fichier)
 *  Desalloue la memoire attribuee a la structure Fichier_Jeu mis en parametre
 * \param[in,out] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu a fermer
 */
void fermeeFichierStruct(Fichier_Jeu *ptr_struct_fichier)
{
    int i;

    free(ptr_struct_fichier->point);
    free(ptr_struct_fichier->point_tot);
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
        free(ptr_struct_fichier->nom_joueur[i]);
    free(ptr_struct_fichier->nom_joueur);
    free(ptr_struct_fichier->position);
    free(ptr_struct_fichier);
}

/*!
 * \fn void debNouvTour(Fichier_Jeu *ptr_struct_fichier)
 *  Realloue l'espace memoire dedie au points sur la structure Fichier_Jeu mis en parametre
 * \param[in,out] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void debNouvTour(Fichier_Jeu *ptr_struct_fichier)
{
    if ((ptr_struct_fichier->point=(float *)realloc(ptr_struct_fichier->point,ptr_struct_fichier->nb_joueur*((ptr_struct_fichier->nb_tour)+1)*sizeof(float))) == NULL)
    {
        printf("\nProbleme reallocation memoire\n");
        perror("");
        exit(0);
    }
}

/*!
 * \fn void finNouvTour(Fichier_Jeu *ptr_struct_fichier)
 *  Met a jour les points totaux, le nombre de tour, la personne qui doit distribuer et les positions
 * \param[in,out] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void finNouvTour(Fichier_Jeu *ptr_struct_fichier)
{
    int i;

    /*Mise a jour des points totaux*/
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        ptr_struct_fichier->point_tot[i]+=ptr_struct_fichier->point[i+(int)((ptr_struct_fichier->nb_joueur)*(ptr_struct_fichier->nb_tour))];
    }

    (ptr_struct_fichier->nb_tour)++;

    /*Mise a jour de la personne qui doit distribue*/
    if (ptr_struct_fichier->distribue == ptr_struct_fichier->nb_joueur -1)
        ptr_struct_fichier->distribue=0;
    else
        (ptr_struct_fichier->distribue)++;

    calculPosition(ptr_struct_fichier);
}

/*!
 * \fn void calculPosition(Fichier_Jeu *ptr_struct_fichier)
 *  Calcule les positions des joueurs
 * \param[in,out] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 */
void calculPosition(Fichier_Jeu *ptr_struct_fichier)
{
    float *points_trie;
    int i;
    int j;

    /*Allocation memoire de points_trie*/
    if ((points_trie=(float *)malloc(sizeof(float)*ptr_struct_fichier->nb_joueur)) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Copie les pints totaux dans points_trie*/
    for(i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        points_trie[i]=ptr_struct_fichier->point_tot[i];
    }

    /*Trie points_trie en fonction du sens du premier*/
    if(ptr_struct_fichier->sens_premier == 1)
        qsort(points_trie,ptr_struct_fichier->nb_joueur,sizeof(float),compareFlottantDecroissant);
    else
        qsort(points_trie,ptr_struct_fichier->nb_joueur,sizeof(float),compareFlottantCroissant);


    /*Boucle sur les points tries a partir du plus petit*/
    for(i=ptr_struct_fichier->nb_joueur -1 ; i>=0 ; i--)
    {
        /*Boucle sur les points totaux des joueurs*/
        for(j=0 ; j<ptr_struct_fichier->nb_joueur ; j++)
        {
            /*Si les points totaux sont egaux aux points trie, on enregistre la position*/
            if (points_trie[i]==ptr_struct_fichier->point_tot[j])
            {
                ptr_struct_fichier->position[j]=i+1;
            }
        }
    }

    free(points_trie);
}

/*!
 * \fn void ajoutDistribueStruct(Fichier_Jeu *ptr_struct_fichier, char *nom_distribue)
 *  Ajoute la personne qui distribue dans la structure.
 * \param[in] *nom_distribue le nom de la personne qui distribue
 * \param[in] *ptr_struct_fichier la structure du fichier avec lequel on veut mettre la personne qui distribue
 */
void ajoutDistribueStruct(Fichier_Jeu *ptr_struct_fichier, char *nom_distribue)
{
    /*Declaration de la constante*/
    int i;

    /*Recherche du nom de la pesonne qui disribue dans le nom des joueurs*/
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        /*Si la personne est trouve, stocke le numero de la personne et arrete la fonction.*/
        if (strcmp(ptr_struct_fichier->nom_joueur[i],nom_distribue)==0)
        {
            ptr_struct_fichier->distribue=i;
            return;
        }
    }
    /*Message d'erreur si le nom n'est pas trouve*/
    printf("\nErreur le nom n'existe pas, la personne qui distribue a ete initialisee par defaut a %s\n",ptr_struct_fichier->nom_joueur[(int)ptr_struct_fichier->distribue]);
}

/*!
 * \fn int depScoreMax(Fichier_Jeu *ptr_struct_fichier)
 *  Verifie si quelqu'un a depasse le score maximum
 * \param[in] *ptr_struct_fichier la structure du fichier
 * \return VRAI s'il y a un depassement, FAUX sinon
 */
int depScoreMax(Fichier_Jeu *ptr_struct_fichier)
{
    int i;
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        if (ptr_struct_fichier->point_tot[i] >= ptr_struct_fichier->nb_max)
            return VRAI;
    }
    return FAUX;
}
