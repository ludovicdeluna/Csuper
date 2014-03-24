/*!
 * \file    menu.c
 * \brief   Fonctions qui gerent les menus demandant de rentrer des valeurs du logiciel
 * \author  Remi BERTHO
 * \date    09/03/14
 * \version 2.1.0
 */

 /*
 * menu.c
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

 #include "menu.h"

/*!
 * \fn char *menuNomFichier(char nom_fichier[TAILLE_MAX_NOM_FICHIER])
 *  Demande et enregistre le nom du fichier
 * \param[in,out] nom_fichier la chaine de caractere contenant le nom du fichier
 * \return la chaine de caractere contenant le nom du fichier
 */
char *menuNomFichier(char nom_fichier[TAILLE_MAX_NOM_FICHIER])
{
    printf("Donnez le nom du fichier avec ou sans l'extension avec au maximum %d caracteres.\nVotre choix : ",TAILLE_MAX_NOM_FICHIER-1);
    saisieClavierChaine(nom_fichier,TAILLE_MAX_NOM_FICHIER);
    printf("Vous avez choisi %s\n",nom_fichier);

    return nom_fichier;
}

/*!
 * \fn void menuDebutPartie(float *ptr_nb_joueur, float *ptr_nb_max , char *ptr_sens_premier, char *ptr_tour_par_tour)
 *  Demande et enregistre le nombre de joueur, le nombre maximum et le nom de la personne qui comme a distribuer
 * \param[in,out] *ptr_nb_joueur le nombre de joueur
 * \param[in,out] *ptr_nb_max le nombre maximum
 * \param[in,out] *ptr_sens_premier definit le sens du premier
 */
void menuDebutPartie(float *ptr_nb_joueur, float *ptr_nb_max, char *ptr_sens_premier, char *ptr_tour_par_tour)
{
    char nbmax;
    char premier_max;
    char tour;

    /*Nombre de joueur*/
    do
    {
        printf("\nDonnez le nombre de joueur dans votre jeu (>0).\nVotre choix : ");
        saisieClavierFlottantSansVirgule(ptr_nb_joueur);
        printf("Vous avez choisi %.0f\n",*ptr_nb_joueur);
    } while (*ptr_nb_joueur <= 0);

    /*Nombre maximum*/
    printf("\nVoulez-vous utiliser un nombre maximum (O/n) : ");
    saisieClavierCaractere(&nbmax);
    if (nbmax=='n' || nbmax=='N')
    {
        *ptr_nb_max =  INFINITY;
    } else
    {
        /*Recuperation du nombre maximale.*/
        do
        {
            printf("\nDonnez le nombre maximal pouvant etre atteint par un joueur dans votre jeu (>0)."
            "\nVotre choix : ");
            saisieClavierFlottant(ptr_nb_max);
            printf("Vous avez choisi %.0f\n",*ptr_nb_max);
        } while (*ptr_nb_max <= 0);
    }

    printf("\nLe premier est-il celui qui a le plus de points (O/n) : ");
    saisieClavierCaractere(&premier_max);

    /*Sens du premier*/
    if (premier_max=='n' || premier_max == 'N')
        *ptr_sens_premier=-1;
    else
        *ptr_sens_premier=1;

    /*Tour par tour ou pas*/
    printf("\nLes points se feront en tour par tour (O/n) : ");
    saisieClavierCaractere(&tour);
    if (tour=='n' || tour == 'N')
        *ptr_tour_par_tour=0;
    else
        *ptr_tour_par_tour=1;
}

/*!
 * \fn void menuDistribue(char *nom_distribue)
 *  Demande et enregistre le nom de la personne qui comme a distribuer
 * \param[in,out] *nom_distribue le nom de la personne qui commence a distribuer
 */
void menuDistribue(char *nom_distribue)
{
    printf("\nDonnez le nom de la personne qui commence a distribuer.\nVotre choix : ");
    saisieClavierChaine(nom_distribue,TAILLE_MAX_NOM);
    printf("Vous avez choisi %s\n",nom_distribue);
}

/*!
 * \fn void menuNomJoueur(Fichier_Jeu *ptr_struct_fichier)
 *  Demande et enregistre le nom des joueurs
 * \param[in,out] *ptr_struct_fichier la structure Fichier_Jeu ou l'on veut enregistrer le nom des joueurs
 */
void menuNomJoueur(Fichier_Jeu *ptr_struct_fichier)
{
    int i;
    char nom[TAILLE_MAX_NOM];

    printf("\nLes noms des personnes doivent etre comprises entre 2 et %.0f caracteres sans accent.\n",ptr_struct_fichier->taille_max_nom);

    for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
    {
        do
        {
            printf("\nDonnez le nom de la %deme personne : ",i+1);
            saisieClavierChaine(nom,TAILLE_MAX_NOM);
            printf("Vous avez choisi %s\n",nom);
        } while (strlen(nom) <2 || strlen(nom) > ptr_struct_fichier->taille_max_nom);

        strcpy(ptr_struct_fichier->nom_joueur[i],nom);
    }
}

/*!
 * \fn void menuPointsJoueur(Fichier_Jeu *ptr_struct_fichier)
 *  Debute un nouveau tour, demande et enregistre les points et fini le tour
 * \param[in,out] *ptr_struct_fichier la structure Fichier_Jeu ou l'on veut faire un nouveau tour
 */
void menuPointsJoueur(Fichier_Jeu *ptr_struct_fichier)
{
    int i;
    int validation;
    char valid;
    int indice_joueur;

    if (ptr_struct_fichier->tour_par_tour == 1)
        indice_joueur = -1;
    else
        indice_joueur = menuNumJoueur(ptr_struct_fichier);

    debNouvTour(ptr_struct_fichier,indice_joueur);

    do
    {
        validation=VRAI;

        /*Demande les points de tout les joueurs si l'on est en tour par tour*/
        if (ptr_struct_fichier->tour_par_tour == 1)
        {
            for (i=0 ; i<ptr_struct_fichier->nb_joueur ; i++)
            {
                printf("\nDonnez les points de %s : ",ptr_struct_fichier->nom_joueur[i]);
                saisieClavierFlottant(&(ptr_struct_fichier->point[i][(int)ptr_struct_fichier->nb_tour[i]]));
                printf("Vous avez choisi %.0f\n",ptr_struct_fichier->point[i][(int)ptr_struct_fichier->nb_tour[i]]);
            }
        } else
        {
            printf("\nDonnez ses points : ");
            saisieClavierFlottant(&(ptr_struct_fichier->point[indice_joueur][(int)ptr_struct_fichier->nb_tour[indice_joueur]]));
            printf("Vous avez choisi %.0f\n",ptr_struct_fichier->point[indice_joueur][(int)ptr_struct_fichier->nb_tour[indice_joueur]]);
        }

        printf("\nValidez vous ces scores (O/n) : ");
        saisieClavierCaractere(&valid);

        if (valid=='n' || valid=='N')
            validation = FAUX;

    } while (!validation);

    finNouvTour(ptr_struct_fichier,indice_joueur);
}

/*!
 * \fn int menuNumJoueur(Fichier_Jeu *ptr_struct_fichier)
 *  Demande et enregistre le numero du joueur
 * \param[in,out] *ptr_struct_fichier la structure Fichier_Jeu
 */
int menuNumJoueur(Fichier_Jeu *ptr_struct_fichier)
{
    char nom[TAILLE_MAX_NOM];
    int indice_joueur;

    do
    {
        printf("\nDonner le nom de la personne qui va recevoir des points : ");
        saisieClavierChaine(nom,TAILLE_MAX_NOM);
        printf("Vous avez choisi %s\n",nom);
    } while ((indice_joueur = rechercheNumJoueur(ptr_struct_fichier,nom)) == -1);

    return indice_joueur;
}

/*!
 * \fn int menuContinuer()
 *  Demande si l'on veut continuer ou pas et l'enregistre dans la variable arret
 * \return VRAI si l'on veut continuer, FAUX sinon
 */
int menuContinuer()
{
    char continuer;

    printf("\nVoulez-vous continuer la partie (O/n) : ");
    saisieClavierCaractere(&continuer);

    if (continuer=='n' || continuer=='N')
        return FAUX;

    return VRAI;
}

/*!
 * \fn int menuSupprimer()
 *  Demande si l'on veut supprimer le fichier ou pas et l'enregistre dans la variable suppr
 * \return VRAI si l'on veut supprimer le fichier, FAUX sinon
 */
int menuSupprimer()
{
    char suppr;

    printf("\nVoulez-vous supprimer le fichier (o/N) : ");
    saisieClavierCaractere(&suppr);

    if (suppr=='o' || suppr=='O')
        return VRAI;

    return FAUX;
}

/*!
 * \fn void menuNouveauChemin(char *nouveauChemin)
 *  Demande et enregistre le nouveau chemin
 * \param[in,out] *nouveauChemin le nouveau chemin
 */
void menuNouveauChemin(char *nouveauChemin)
{
    int verif=FAUX;
    FILE *ptr_fichier_test;
    char testChemin[TAILLE_MAX_NOM_FICHIER];

    do
    {
        /*Saisie clavier du nouveau chemin*/
        printf("\nDonnez le nouveau dossier d'enregistrement des fichiers que vous voulez utiliser.\nVerifiez bien que le dossier existe"
        " et que vous y avez les droits en lecture et ecriture.\n\nVotre choix : ");
        saisieClavierChaine(nouveauChemin,TAILLE_MAX_NOM_FICHIER);

        /*Creation d'un fichier test pour voir si le chemin est valide*/
        sprintf(testChemin,"%s/test-chemin_fichier_csuper",nouveauChemin);
        ptr_fichier_test=ouvrirFichier(testChemin,"w+");

        /*Si le chemin est valide on supprime le fichier creer et on valide la saisie*/
        if (ptr_fichier_test != NULL)
        {
            fermerFichier(ptr_fichier_test);
            remove(testChemin);
            verif=VRAI;
        }

        else
            printf("\nErreur le chemin de fichier donnee n'est pas valide.\n");

    } while (verif == FAUX);

    printf("Vous avez choisi %s\n",nouveauChemin);
}
