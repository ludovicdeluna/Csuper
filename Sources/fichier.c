/*!
 * \file    fichier.c
 * \brief   Fonction de gestion des fichiers
 * \author  Remi BERTHO
 * \date    13/02/14
 * \version 2.0
 */

 /*
 * fichier.c
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

 #include "fichier.h"



/*!
 * \fn FILE *ouvrirFichierExtension(char nom[], char mode[])
 *  Ouvre un fichier a partir de son nom (nom[]) et du mod voulu (mode[]) en y ajouter l'extension du fichier
 * \param[in] nom[] le nom du fichier
 * \param[in] mode[] le mode voulu
 * \return un pointeur sur le fichier ouvert, NULL s'il y a eut un probleme
 */
FILE *ouvrirFichierExtension(char nom[], char mode[])
{
    /*Decalaration des variables*/
    char nom_2[TAILLE_MAX_NOM_FICHIER];

    /*Ajout de l'extension au nom de fichier*/
    sprintf(nom_2,"%s.%s",nom,EXTENSION_FICHIER);

    return ouvrirFichier(nom_2,mode);
}


/*!
 * \fn Fichier_Jeu *lireFichier(char *nom)
 *  Lis ce qu'il y a dans le fichier avec le nom donne en parametre et le met dans une structure
 *  Fichier_Jeu rendu par la fonction
 * \param[in] nom[] le nom du fichier
 * \return un pointeur sur la structure Fichier_Jeu cree, NULL s'il y a un probleme d'ouverture du fichier
 */
Fichier_Jeu *lireFichier(char *nom)
{
    Fichier_Jeu *ptr_struct_fichier=NULL;
    int i;
    char *nom_pers;
    FILE *ptr_fichier;
    char verif_fichier[sizeof(TYPE_FICHIER)];
    int taille_fichier;
    int verif_lecture_fichier=0;

    ptr_fichier=ouvrirFichierExtension(nom,"rb");

    if (ptr_fichier == NULL)
    {
        printf("\nErreur : Le fichier n'a pas pu etre lu.\n");
        return ptr_struct_fichier;
    }

    fseek(ptr_fichier,0,SEEK_SET);

    taille_fichier=lireTailleFichier(ptr_fichier);

    verif_lecture_fichier+=fread(verif_fichier,sizeof(char),sizeof(TYPE_FICHIER),ptr_fichier);

    /*Si la chaine de verification ne correspond pas, on ferme le fichier et on retourne une structure vide*/
    if (strcmp(TYPE_FICHIER,verif_fichier) != 0)
    {
        printf("\nErreur : Fichier non compatible.\n");
        fermerFichier(ptr_fichier);
        return ptr_struct_fichier;
    }

    /*Allocation memoire de la structure*/
    if ((ptr_struct_fichier=(Fichier_Jeu *)malloc(sizeof(Fichier_Jeu))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Lecture des differentes variables du fichier dans la structure*/
    verif_lecture_fichier+=(sizeof(float)*fread(&(ptr_struct_fichier->version),sizeof(float),1,ptr_fichier));
    verif_lecture_fichier+=(sizeof(float)*fread(&(ptr_struct_fichier->taille_max_nom),sizeof(float),1,ptr_fichier));
    verif_lecture_fichier+=(sizeof(float)*fread(&(ptr_struct_fichier->jour),sizeof(float),1,ptr_fichier));
    verif_lecture_fichier+=(sizeof(float)*fread(&(ptr_struct_fichier->mois),sizeof(float),1,ptr_fichier));
    verif_lecture_fichier+=(sizeof(float)*fread(&(ptr_struct_fichier->annee),sizeof(float),1,ptr_fichier));
    verif_lecture_fichier+=(sizeof(float)*fread(&(ptr_struct_fichier->nb_joueur),sizeof(float),1,ptr_fichier));
    verif_lecture_fichier+=(sizeof(float)*fread(&(ptr_struct_fichier->nb_max),sizeof(float),1,ptr_fichier));
    verif_lecture_fichier+=fread(&(ptr_struct_fichier->sens_premier),sizeof(char),1,ptr_fichier);

    /*Allocation memoire du tableau de chaine de caractere pour le nom des personnes*/
    if ((ptr_struct_fichier->nom_joueur=(char **)malloc(ptr_struct_fichier->nb_joueur*sizeof(char*))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Allocation memoire des noms des personnes*/
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        if ((ptr_struct_fichier->nom_joueur[i]=(char *)malloc(ptr_struct_fichier->taille_max_nom*sizeof(char))) == NULL)
        {
            printf("\nProbleme allocation memoire\n");
            perror("");
            exit(0);
        }
    }

    /*Allocation du tableau de caractere nom_pers ou vas etre stocke le nom des personnes en tant que tampon*/
    if ((nom_pers=(char *)malloc(sizeof(char)*ptr_struct_fichier->taille_max_nom)) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Lecture du nom des personnes dans la structure*/
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        verif_lecture_fichier+=fread(nom_pers,sizeof(char),ptr_struct_fichier->taille_max_nom,ptr_fichier);
        strcpy(ptr_struct_fichier->nom_joueur[i],nom_pers);
    }

    free(nom_pers);

    /*Allocation memoire des points totaux*/
    if ((ptr_struct_fichier->point_tot=(float *)malloc(ptr_struct_fichier->nb_joueur*sizeof(float))) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Lecture des points totaux*/
    verif_lecture_fichier+=(sizeof(float)*fread(ptr_struct_fichier->point_tot,sizeof(float),ptr_struct_fichier->nb_joueur,ptr_fichier));

    /*Allocation memoire des positions*/
    if ((ptr_struct_fichier->position=(float *)malloc(ptr_struct_fichier->nb_joueur*sizeof(float))) == NULL)
    {
        printf("Probleme allocation memoire");
        exit(0);
    }

    /*Lecture des positions, du nombre de tour et de distribue*/
    verif_lecture_fichier+=(sizeof(float)*fread(ptr_struct_fichier->position,sizeof(float),ptr_struct_fichier->nb_joueur,ptr_fichier));
    verif_lecture_fichier+=(sizeof(float)*fread(&(ptr_struct_fichier->nb_tour),sizeof(float),1,ptr_fichier));
    verif_lecture_fichier+=(sizeof(float)*fread(&(ptr_struct_fichier->distribue),sizeof(float),1,ptr_fichier));

    /*Allocation memoire des points*/
    if ((ptr_struct_fichier->point=(float *)malloc(ptr_struct_fichier->nb_joueur*sizeof(float)*ptr_struct_fichier->nb_tour)) == NULL)
    {
        printf("\nProbleme allocation memoire\n");
        perror("");
        exit(0);
    }

    /*Lecture des points*/
    verif_lecture_fichier+=(sizeof(float)*fread(ptr_struct_fichier->point,sizeof(float),ptr_struct_fichier->nb_joueur*ptr_struct_fichier->nb_tour,ptr_fichier));

    fermerFichier(ptr_fichier);

    /*Verifie si la lecture s'est bien passee*/
    if (taille_fichier != verif_lecture_fichier)
    {
        printf("\nErreur lors de la lecture du fichier\n");
        return NULL;
    }

    return ptr_struct_fichier;
}

/*!
 * \fn int ecrireFichier(char *nom, Fichier_Jeu *ptr_struct_fichier)
 *  Cree un fichier .jeu qui contient toutes les informations de la structure Fichier_Jeu mis en parametre
 * \param[in] *nom le nom du fichier
 * \param[in] *ptr_struct_fichier la structure du fichier avec lequel on veut cree le fichier
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int ecrireFichier(char *nom, Fichier_Jeu *ptr_struct_fichier)
{
    int i;
    FILE *ptr_fichier;

    ptr_fichier=ouvrirFichierExtension(nom,"w+");

    if (ptr_fichier == NULL)
    {
        printf("\nErreur lors de l'ecriture du fichier.\n");
        return FAUX;
    }

    fseek(ptr_fichier,0,SEEK_SET);

    fwrite(TYPE_FICHIER,sizeof(char),sizeof(TYPE_FICHIER),ptr_fichier);
    fwrite(&(ptr_struct_fichier->version),sizeof(float),1,ptr_fichier);
    fwrite(&(ptr_struct_fichier->taille_max_nom),sizeof(float),1,ptr_fichier);
    fwrite(&(ptr_struct_fichier->jour),sizeof(float),1,ptr_fichier);
    fwrite(&(ptr_struct_fichier->mois),sizeof(float),1,ptr_fichier);
    fwrite(&(ptr_struct_fichier->annee),sizeof(float),1,ptr_fichier);
    fwrite(&(ptr_struct_fichier->nb_joueur),sizeof(float),1,ptr_fichier);
    fwrite(&(ptr_struct_fichier->nb_max),sizeof(float),1,ptr_fichier);
    fwrite(&(ptr_struct_fichier->sens_premier),sizeof(char),1,ptr_fichier);

    /*Ecriture des noms des personnes*/
    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
        fwrite(ptr_struct_fichier->nom_joueur[i],sizeof(char),ptr_struct_fichier->taille_max_nom,ptr_fichier);

    fwrite(ptr_struct_fichier->point_tot,sizeof(float),ptr_struct_fichier->nb_joueur,ptr_fichier);
    fwrite(ptr_struct_fichier->position,sizeof(float),ptr_struct_fichier->nb_joueur,ptr_fichier);
    fwrite(&(ptr_struct_fichier->nb_tour),sizeof(float),1,ptr_fichier);
    fwrite(&(ptr_struct_fichier->distribue),sizeof(float),1,ptr_fichier);
    fwrite(ptr_struct_fichier->point,sizeof(float),ptr_struct_fichier->nb_joueur*ptr_struct_fichier->nb_tour,ptr_fichier);

    fermerFichier(ptr_fichier);

    return VRAI;
}

/*!
 * \fn void nouveauScore(char *nom, Fichier_Jeu *ptr_struct_fichier)
 *  Mets a jour le fichier avec les nouveaux scores
 * \param[in] *nom le nom du fichier
 * \param[in] *ptr_struct_fichier la structure du fichier avec lequel on veut mettre un nouveau score
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int nouveauScore(char *nom, Fichier_Jeu *ptr_struct_fichier)
{
    char nom_fichier_2[TAILLE_MAX_NOM_FICHIER+4];
    int reussi;

    sprintf(nom_fichier_2,"%s_tmp",nom);

    reussi=ecrireFichier(nom_fichier_2,ptr_struct_fichier);

    if (reussi)
    {
        if(supprimerFichier(nom))
        {
            if(renommerFichier(nom_fichier_2,nom))
                return VRAI;
        }
    }

    return FAUX;
}

/*!
 * \fn int supprimerFichier(char *nom)
 *  Supprime le fichier dont le nom est en parametre
 * \param[in] *nom le nom du fichier
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int supprimerFichier(char *nom)
{
    char nom_2[TAILLE_MAX_NOM+4];

    sprintf(nom_2,"%s.%s",nom,EXTENSION_FICHIER);

    if(remove(nom_2))
    {
        printf("\nLe fichier %s n'a pas pu etre supprime.\n",nom_2);
        perror("");
        return FAUX;
    }

    else
    {
        printf("\nLe fichier %s a bien ete supprime.\n",nom_2);
        return VRAI;
    }
}

/*!
 * \fn int renommerFichier(char *nom_ancien, char *nom_nouveau)
 *  Renomme le fichier dont le nom est en parametre
 * \param[in] *nom_ancien l'ancien nom du fichier
 * \param[in] *nom_nouveau le nouveau nom du fichier
 * \return VRAI si tout s'est bien passe, FAUX sinon
 */
int renommerFichier(char *nom_ancien, char *nom_nouveau)
{
    char nom_ancien_2[TAILLE_MAX_NOM+8];
    char nom_nouveau_2[TAILLE_MAX_NOM+4];

    sprintf(nom_ancien_2,"%s.%s",nom_ancien,EXTENSION_FICHIER);
    sprintf(nom_nouveau_2,"%s.%s",nom_nouveau,EXTENSION_FICHIER);

    if(rename(nom_ancien_2,nom_nouveau_2))
    {
        printf("\nLe fichier %s n'a pas pu etre renomme.\n",nom_ancien_2);
        return FAUX;
    }

    else
    {
        printf("\nLe fichier %s a bien ete renome en %s.\n",nom_ancien_2,nom_nouveau_2);
        return VRAI;
    }
}

