#include "EtudiantDeuxiemeCycle.h"
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
// Constructeur
EtudiantDeuxiemeCycle::EtudiantDeuxiemeCycle(int numeroEtudiant, const std::string& nom, const std::string& prenom,
                                             const std::string& adresse, const std::string& telephone,
                                             const std::string& disciplinePrincipale)
    : Etudiant(numeroEtudiant, nom, prenom, adresse, telephone), disciplinePrincipale(disciplinePrincipale) {}

// Getter
std::string EtudiantDeuxiemeCycle::getDisciplinePrincipale() const { return disciplinePrincipale; }

// Affichage
void EtudiantDeuxiemeCycle::afficher() const {
    Etudiant::afficher();
    std::cout << "Cycle: Deuxieme Cycle\n"
    << "Discipline principale: " << disciplinePrincipale << std::endl;
}
void EtudiantDeuxiemeCycle::modifierCycle()
{
    std::cout << "Modification des informations du Deuxieme Cycle :\n";

    std::string nouvelleDisciplinePrincipale;

    std::cout << "Discipline actuelle : " << disciplinePrincipale << "\nNouvelle discipline principale : ";
    std::getline(std::cin, nouvelleDisciplinePrincipale);
    if (!nouvelleDisciplinePrincipale.empty())
    {
        disciplinePrincipale = nouvelleDisciplinePrincipale;
    }

    std::cout << "Deuxieme Cycle modifie avec succes.\n";
}
