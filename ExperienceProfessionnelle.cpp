#include "ExperienceProfessionnelle.h"
#include <algorithm>
#include <iostream>
#include <limits>

// Constructeur
ExperienceProfessionnelle::ExperienceProfessionnelle(const std::string &dateDebut, const std::string &dateFin,
                                                     const std::string &entreprise, const std::string &fonction)
    : dateDebut(dateDebut), dateFin(dateFin), entreprise(entreprise), fonction(fonction) {}

// Getters
std::string ExperienceProfessionnelle::getDateDebut() const { return dateDebut; }
std::string ExperienceProfessionnelle::getDateFin() const { return dateFin; }
std::string ExperienceProfessionnelle::getEntreprise() const { return entreprise; }
std::string ExperienceProfessionnelle::getFonction() const { return fonction; }

// Setters
void ExperienceProfessionnelle::setDateDebut(const std::string &dateDebut) { this->dateDebut = dateDebut; }
void ExperienceProfessionnelle::setDateFin(const std::string &dateFin) { this->dateFin = dateFin; }
void ExperienceProfessionnelle::setEntreprise(const std::string &entreprise) { this->entreprise = entreprise; }
void ExperienceProfessionnelle::setFonction(const std::string &fonction) { this->fonction = fonction; }

// Affichage
void ExperienceProfessionnelle::afficher() const
{
    std::cout << "Date Debut: " << dateDebut << ", Date Fin: " << dateFin
              << "\nEntreprise: " << entreprise << ", Fonction: " << fonction << "\n";
}

// Modifier une expérience
void ExperienceProfessionnelle::modifierExperience(std::vector<ExperienceProfessionnelle> &experiences)
{
    std::string entrepriseCherchee;
    std::cout << "Entrez le nom de l'entreprise de l'experience a modifier : ";
    std::cin.ignore();
    std::getline(std::cin, entrepriseCherchee);

    auto it = std::find_if(experiences.begin(), experiences.end(),
                           [&entrepriseCherchee](const ExperienceProfessionnelle &e)
                           { return e.getEntreprise() == entrepriseCherchee; });

    if (it != experiences.end())
    {
        ExperienceProfessionnelle &experience = *it;

        std::cout << "Modification des informations de l'experience professionnelle :\n";

        std::string nouvelleDateDebut, nouvelleDateFin, nouvelleEntreprise, nouvelleFonction;

        // Modifier date de début
        std::cout << "Date de debut actuelle : " << experience.getDateDebut() << "\nNouvelle date de debut : ";
        std::getline(std::cin, nouvelleDateDebut);
        if (!nouvelleDateDebut.empty())
        {
            experience.setDateDebut(nouvelleDateDebut);
        }

        // Modifier date de fin
        std::cout << "Date de fin actuelle : " << experience.getDateFin() << "\nNouvelle date de fin : ";
        std::getline(std::cin, nouvelleDateFin);
        if (!nouvelleDateFin.empty())
        {
            experience.setDateFin(nouvelleDateFin);
        }

        // Modifier entreprise
        std::cout << "Entreprise actuelle : " << experience.getEntreprise() << "\nNouvelle entreprise : ";
        std::getline(std::cin, nouvelleEntreprise);
        if (!nouvelleEntreprise.empty())
        {
            experience.setEntreprise(nouvelleEntreprise);
        }

        // Modifier fonction
        std::cout << "Fonction actuelle : " << experience.getFonction() << "\nNouvelle fonction : ";
        std::getline(std::cin, nouvelleFonction);
        if (!nouvelleFonction.empty())
        {
            experience.setFonction(nouvelleFonction);
        }

        std::cout << "Experience professionnelle modifiee avec succes.\n";
    }
    else
    {
        std::cout << "Experience introuvable.\n";
    }
}
