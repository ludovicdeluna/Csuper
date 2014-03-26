/*!
 * \file    structure.c
 * \brief   Fonction de gestion des fichiers de la struction contenant les informations
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
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
 * \fn Fichier_Jeu *creerFichierStruct(float nb_joueur , float nb_max, char sens_premier, char tour_par_tour, char use_distributor,char number_after_comma)
 *  Cree une structure Fichier_jeu a partir des donnees de la fonction.
 * \param[in] nb_joueur le nombre de joueur
 * \param[in] nb_max le nombre maximum de points
 * \param[in] sens_premier permet de savoir dans quelle sens est calculer le premier
 * \param[in] use_distributor permet de savoir si l'on utilise un distributeur ou pas
 * \param[in] number_after_comma nombre de chiffres apres la virgule
 * \return un pointeur sur le structure Fichier_Jeu cree
 */
Fichier_Jeu *creerFichierStruct(float nb_joueur , float nb_max, char sens_premier, char tour_par_tour, char use_distributor,char number_after_comma)
{
    Fichier_Jeu *ptr_struct_fichier;
    int i;
    time_t timestamp;
    struct tm *t;

    /*Allocation memoire de la structure*/
    ptr_struct_fichier=(Fichier_Jeu *)myAlloc(sizeof(Fichier_Jeu));

    /*Copie de certaines variables dans la structure*/
    ptr_struct_fichier->taille_max_nom=TAILLE_MAX_NOM;
    ptr_struct_fichier->version=VERSION;
    ptr_struct_fichier->nb_joueur=nb_joueur;
    ptr_struct_fichier->nb_max=nb_max;
    ptr_struct_fichier->distribue=0;
    ptr_struct_fichier->sens_premier=sens_premier;
    ptr_struct_fichier->tour_par_tour=tour_par_tour;
    ptr_struct_fichier->use_distributor=use_distributor;
    ptr_struct_fichier->number_after_comma=number_after_comma;

    /*Allocation memoire des nombre de tours*/
    ptr_struct_fichier->nb_tour=(float *)myAlloc(nb_joueur*sizeof(float*));

    /*Allocation memoire du tableau des nom des personnes*/
    ptr_struct_fichier->nom_joueur=(char **)myAlloc(nb_joueur*sizeof(char*));
    for (i=0 ; i<nb_joueur ; i++)
        ptr_struct_fichier->nom_joueur[i]=(char *)myAlloc(TAILLE_MAX_NOM*sizeof(char));

    /*Allocation memoire des points totaux et des de positions*/
    ptr_struct_fichier->point_tot=(float *)myAlloc(nb_joueur*sizeof(float));
    ptr_struct_fichier->position=(float *)myAlloc(nb_joueur*sizeof(float));

    /*Initialisation des points totaux,de la position a zero et du nombre de tour*/
    for (i=0 ; i<nb_joueur ; i++)
    {
        ptr_struct_fichier->point_tot[i]=0;
        ptr_struct_fichier->position[i]=1;
        ptr_struct_fichier->nb_tour[i]=0;
    }

    /*Allocation memoire du tableau de points*/
    ptr_struct_fichier->point=(float **)myAlloc(ptr_struct_fichier->nb_joueur*sizeof(float*));
    for (i=0 ; i<nb_joueur ; i++)
        ptr_struct_fichier->point[i]=(float*)myAlloc(0*sizeof(float));

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

    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
        free(ptr_struct_fichier->point[i]);
    free(ptr_struct_fichier->point);
    free(ptr_struct_fichier->point_tot);
    free(ptr_struct_fichier->nb_tour);
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
        free(ptr_struct_fichier->nom_joueur[i]);
    free(ptr_struct_fichier->nom_joueur);
    free(ptr_struct_fichier->position);
    free(ptr_struct_fichier);
}

/*!
 * \fn void debNouvTour(Fichier_Jeu *ptr_struct_fichier)
 *  Realloue l'espace memoire dedie au points sur la structure Fichier_Jeu mis en parametre pour un nouveau tour
 * \param[in,out] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 * \param[in,out] num_joueur le numero du joueur qui va commencer un nouveau tour, vaut -1 si c'est tout le monde
 */
void debNouvTour(Fichier_Jeu *ptr_struct_fichier,int num_joueur)
{
    int i;

    if (num_joueur == -1)
    {
         for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
            myRealloc((void**)&(ptr_struct_fichier->point[i]),ptr_struct_fichier->nb_joueur*((ptr_struct_fichier->nb_tour[0])+1)*sizeof(float));
    }
    else
        myRealloc((void **)&(ptr_struct_fichier->point[num_joueur]),ptr_struct_fichier->nb_joueur*((ptr_struct_fichier->nb_tour[num_joueur])+1)*sizeof(float));
}

/*!
 * \fn void finNouvTour(Fichier_Jeu *ptr_struct_fichier)
 *  Met a jour les points totaux, le nombre de tour, la personne qui doit distribuer et les positions pour un nouveau tour
 * \param[in,out] *ptr_struct_fichier un pointeur sur la structure Fichier_Jeu
 * \param[in,out] num_joueur le numero du joueur qui va commencer un nouveau tour, vaut -1 si c'est tout le monde
 */
void finNouvTour(Fichier_Jeu *ptr_struct_fichier, int num_joueur)
{
    int i;

    /*Mise a jour des points totaux*/
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        ptr_struct_fichier->point_tot[i]+=ptr_struct_fichier->point[i][(int)ptr_struct_fichier->nb_tour[i]];
    }

    if (num_joueur == -1)
    {
        for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
            (ptr_struct_fichier->nb_tour[i])++;
    }
    else
        (ptr_struct_fichier->nb_tour[num_joueur])++;

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
    points_trie=(float *)myAlloc(sizeof(float)*ptr_struct_fichier->nb_joueur);

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
    int num_joueur=rechercheNumJoueur(ptr_struct_fichier,nom_distribue);
    if(num_joueur != -1)
    {
        ptr_struct_fichier->distribue = num_joueur;
        return;
    }
    else
        printf("La personne qui distribue a ete initialisee par defaut a %s\n",ptr_struct_fichier->nom_joueur[(int)ptr_struct_fichier->distribue]);
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

/*!
 * \fn int maxNbTour(Fichier_Jeu *ptr_struct_fichier)
 *  Cherche le maximum de nombre de tour
 * \param[in] *ptr_struct_fichier la structure du fichier
 * \return le nombre maximum de nombre de tour
 */
int maxNbTour(Fichier_Jeu *ptr_struct_fichier)
{
    int max = ptr_struct_fichier->nb_tour[0];
    int i;

    for (i=1 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        if (ptr_struct_fichier->nb_tour[i] > max)
            max = ptr_struct_fichier->nb_tour[i];
    }
    return max;
}

/*!
 * \fn int rechercheNumJoueur(Fichier_Jeu *ptr_struct_fichier, char *nom_personne)
 *  Cherche l'indice du tableau dans lequel est stocke une personne.
 * \param[in] *nom_distribue le nom de la personne
 * \param[in] *ptr_struct_fichier la structure du fichier
 * \return l'indice du tableau, -1 si non trouve
 */
int rechercheNumJoueur(Fichier_Jeu *ptr_struct_fichier, char *nom_personne)
{
    int i;

    /*Recherche du nom de la personne dans le nom des joueurs*/
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        if (strncasecmp(ptr_struct_fichier->nom_joueur[i],nom_personne,strlen(nom_personne))==0)
            return i;
    }

    /*Message d'erreur si le nom n'est pas trouve*/
    printf("\nErreur le nom n'existe pas.\n");
    return -1;
}
