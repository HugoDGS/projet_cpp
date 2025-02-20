#include "EtudiantPremierCycle.h"
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
// Constructeur
EtudiantPremierCycle::EtudiantPremierCycle(int numeroEtudiant, const std::string& nom, const std::string& prenom,
                                           const std::string& adresse, const std::string& telephone,
                                           const std::string& serieBac, int anneeBac, const std::string& lieuBac)
    : Etudiant(numeroEtudiant, nom, prenom, adresse, telephone),
      serieBac(serieBac), anneeBac(anneeBac), lieuBac(lieuBac) {}

// Getters
std::string EtudiantPremierCycle::getSerieBac() const { return serieBac; }
int EtudiantPremierCycle::getAnneeBac() const { return anneeBac; }
std::string EtudiantPremierCycle::getLieuBac() const { return lieuBac; }

// Affichage
void EtudiantPremierCycle::afficher() const {
    Etudiant::afficher();
    std::cout << "Cycle: Premier Cycle\n"
              << "Serie du Bac: " << serieBac << "\n"
              << "Annee du Bac: " << anneeBac << "\n"
              << "Lieu du Bac: " << lieuBac << std::endl;
}
void EtudiantPremierCycle::modifierCycle()
{
    std::cout << "Modification des informations du Premier Cycle :\n";

    std::string nouvelleSerieBac, nouveauLieuBac;
    int nouvelleAnneeBac;

    std::cout << "Serie actuelle du Bac : " << serieBac << "\nNouvelle serie du Bac : ";
    std::getline(std::cin, nouvelleSerieBac);
    if (!nouvelleSerieBac.empty())
    {
        serieBac = nouvelleSerieBac;
    }

    std::cout << "Annee actuelle du Bac : " << anneeBac << "\nNouvelle annee du Bac : ";
    while (!(std::cin >> nouvelleAnneeBac) || nouvelleAnneeBac <= 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Annee invalide. Entrez une annee valide : ";
    }
    anneeBac = nouvelleAnneeBac;

    std::cin.ignore();
    std::cout << "Lieu actuel du Bac : " << lieuBac << "\nNouveau lieu du Bac : ";
    std::getline(std::cin, nouveauLieuBac);
    if (!nouveauLieuBac.empty())
    {
        lieuBac = nouveauLieuBac;
    }

    std::cout << "Premier Cycle modifie avec succes.\n";
}
