
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <unordered_set>
#include <stdexcept>

#include "Etudiant.h"
#include "EtudiantPremierCycle.h"
#include "EtudiantDeuxiemeCycle.h"
#include "Entreprise.h"
#include "RendezVous.h"
#include "Diplome.h"
#include "ExperienceProfessionnelle.h"

using namespace std;

// Affiche le menu principal
static void afficherMenuPrincipal()
{
    cout << "========== MENU PRINCIPAL ==========\n";
    cout << "1. Gestion des etudiants\n";
    cout << "2. Gestion des entreprises\n";
    cout << "3. Gestion des rendez-vous\n";
    cout << "4. Quitter\n";
    cout << "====================================\n";
    cout << "Votre choix : ";
}

// Sous-menu pour la gestion des étudiants
static void afficherMenuEtudiant()
{
    cout << "\n===== Gestion des Etudiants =====\n";
    cout << "1. Ajouter un etudiant\n";
    cout << "2. Afficher les cv etudiants\n";
    cout << "3. Modifier un etudiant\n";
    cout << "4. Supprimer un etudiant\n";
    cout << "5. Retour au menu principal\n";
    cout << "Votre choix : ";
}

// Sous-menu pour la gestion des entreprises
static void afficherMenuEntreprise()
{
    cout << "\n===== Gestion des Entreprises =====\n";
    cout << "1. Ajouter une entreprise\n";
    cout << "2. Afficher toutes les entreprises\n";
    cout << "3. Modifier une entreprise\n";
    cout << "4. Supprimer une entreprise\n";
    cout << "5. Retour au menu principal\n";
    cout << "Votre choix : ";
}

// Sous-menu pour la gestion des rendez-vous
static void afficherMenuRendezVous()
{
    cout << "\n===== Gestion des Rendez-vous =====\n";
    cout << "1. Ajouter un rendez-vous\n";
    cout << "2. Afficher tous les rendez-vous\n";
    cout << "3. Modifier un rendez-vous\n";
    cout << "4. Supprimer un rendez-vous\n";
    cout << "5. Retour au menu principal\n";
    cout << "Votre choix : ";
}

// Fonction utilitaire pour lire un choix utilisateur valide
int lireChoix(int min, int max)
{
    string input;
    int choix;
    while (true)
    {
        cin >> input;
        try
        {
            choix = stoi(input); // Conversion de l'entrée en entier
            if (choix >= min && choix <= max)
            {
                return choix;
            }
            else
            {
                cout << "Choix invalide. Veuillez entrer un nombre entre " << min << " et " << max << ".\n";
            }
        }
        catch (const invalid_argument &)
        {
            cout << "Entrée invalide. Veuillez entrer un nombre entre " << min << " et " << max << ".\n";
        }
        catch (const out_of_range &)
        {
            cout << "Nombre hors plage. Veuillez entrer un nombre entre " << min << " et " << max << ".\n";
        }
    }
}

int main()
{
    vector<Etudiant *> listeEtudiants;  // Liste globale pour stocker les étudiants
    vector<Entreprise *> entreprises;   // Liste globale pour stocker les entreprises
    vector<RendezVous> rendezVousListe; // Liste globale pour stocker les rendez-vous
    bool continuer = true;

    while (continuer)
    {
        afficherMenuPrincipal();
        int choixPrincipal = lireChoix(1, 4); // Lire un choix valide pour le menu principal

        switch (choixPrincipal)
        {
        case 1: // Gestion des étudiants
        {
            bool retourMenuPrincipalEtudiant = false;
            while (!retourMenuPrincipalEtudiant)
            {
                afficherMenuEtudiant();
                int choixEtudiant;
                cin >> choixEtudiant;

                switch (choixEtudiant)
                {
                case 1: // Ajouter un étudiant
                {
                    Etudiant *nouvelEtudiant = Etudiant::creerEtudiantComplet();
                    if (nouvelEtudiant)
                    {
                        listeEtudiants.push_back(nouvelEtudiant);
                        cout << "Etudiant ajoute avec succes !\n";
                    }
                    break;
                }
                case 2: // Afficher tous les étudiants
                {
                    cout << "\n===== Liste des Etudiants =====\n";
                    for (const auto &etudiant : listeEtudiants)
                    {
                        etudiant->afficher();
                        cout << "--------------------------------\n";
                    }
                    break;
                }
                case 3: // Modifier un étudiant
                    cout << "Modification d'un étudiant.\n";
                    Etudiant::modifierEtudiant(listeEtudiants);
                    break;
                case 4: // Supprimer un étudiant
                    Etudiant::supprimerEtudiant(listeEtudiants);
                    break;
                case 5: // Retour au menu principal
                    retourMenuPrincipalEtudiant = true;
                    break;
                default:
                    cout << "Choix invalide. Veuillez reessayer.\n";
                }
            }
            break;
        }
        case 2: // Gestion des entreprises
        {
            bool retourMenuPrincipalEntreprise = false;
            while (!retourMenuPrincipalEntreprise)
            {
                afficherMenuEntreprise();
                int choixEntreprise;
                cin >> choixEntreprise;

                switch (choixEntreprise)
                {
                case 1: // Ajouter une entreprise
                {
                    Entreprise *nouvelleEntreprise = Entreprise::creerEntreprise();
                    if (nouvelleEntreprise)
                    {
                        entreprises.push_back(nouvelleEntreprise);
                        cout << "Entreprise ajoutee avec succes !\n";
                    }
                    break;
                }
                case 2: // Afficher toutes les entreprises
                {
                    cout << "\n===== Liste des Entreprises =====\n";
                    for (const auto &entreprise : entreprises)
                    {
                        entreprise->afficher();
                        cout << "--------------------------------\n";
                    }
                    break;
                }
                case 3: // Modifier une entreprise
                    cout << "Modification d'une entreprise.\n";
                    Entreprise::modifierEntreprise(entreprises);
                    break;
                case 4: // Supprimer une entreprise
                    Entreprise::supprimerEntreprise(entreprises);
                    break;
                case 5: // Retour au menu principal
                    retourMenuPrincipalEntreprise = true;
                    break;
                default:
                    cout << "Choix invalide. Veuillez reessayer.\n";
                }
            }
            break;
        }
        case 3: // Gestion des rendez-vous
        {
            bool retourMenuPrincipalRendezVous = false;
            while (!retourMenuPrincipalRendezVous)
            {
                afficherMenuRendezVous();
                int choixRendezVous;
                cin >> choixRendezVous;

                switch (choixRendezVous)
                {
                case 1: // Ajouter un rendez-vous
                {
                    // Vérifier si les listes d'entreprises et d'étudiants ne sont pas vides
                    if (entreprises.empty())
                    {
                        cout << "Erreur : Aucun entreprise disponible pour un rendez-vous.\n";
                        break;
                    }
                    if (listeEtudiants.empty())
                    {
                        cout << "Erreur : Aucun étudiant disponible pour un rendez-vous.\n";
                        break;
                    }

                    RendezVous::creerRendezVous(rendezVousListe, entreprises, listeEtudiants);
                    break;
                }
                case 2: // Afficher tous les rendez-vous
                {
                    cout << "\n===== Liste des Rendez-vous =====\n";
                    for (size_t i = 0; i < rendezVousListe.size(); ++i)
                    {
                        cout << "Rendez-vous #" << i + 1 << ":\n";
                        rendezVousListe[i].afficher();
                        cout << "--------------------------------\n";
                    }
                    break;
                }
                case 3: // Modifier un rendez-vous
                    RendezVous::modifierRendezVous(rendezVousListe, entreprises, listeEtudiants);
                    break;
                case 4: // Supprimer un rendez-vous
                    RendezVous::supprimerRendezVous(rendezVousListe);
                    break;
                case 5: // Retour au menu principal
                    retourMenuPrincipalRendezVous = true;
                    break;
                default:
                    cout << "Choix invalide. Veuillez reessayer.\n";
                }
            }
            break;
        }
        case 4: // Quitter
            continuer = false;
            break;
        }
    }

    cout << "Merci d'avoir utilisé le programme. Au revoir !\n";
    return 0;
}
