#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include "Diplome.h"
using namespace std;

// Constructeur
Diplome::Diplome(const std::string &code, const std::string &nom,
                 const std::string &dateObtention, const std::string &lieuObtention,
                 const std::string &datePremiereInscription, int numeroAnnee, bool enCours)
    : code(code), nom(nom), dateObtention(dateObtention), lieuObtention(lieuObtention),
      datePremiereInscription(datePremiereInscription), numeroAnnee(numeroAnnee), enCours(enCours) {}

// Getters
std::string Diplome::getCode() const { return code; }
std::string Diplome::getNom() const { return nom; }
std::string Diplome::getDateObtention() const { return dateObtention; }
std::string Diplome::getLieuObtention() const { return lieuObtention; }
std::string Diplome::getDatePremiereInscription() const { return datePremiereInscription; }
int Diplome::getNumeroAnnee() const { return numeroAnnee; }
bool Diplome::isEnCours() const { return enCours; }

// Setters
void Diplome::setNom(const std::string &nom) { this->nom = nom; }

void Diplome::setLieuObtention(const std::string &lieuObtention) { this->lieuObtention = lieuObtention; }

void Diplome::setDateObtention(const std::string &dateObtention) { this->dateObtention = dateObtention; }

void Diplome::setDatePremiereInscription(const std::string &date) { datePremiereInscription = date; }

void Diplome::setNumeroAnnee(int annee) { numeroAnnee = annee; }

void Diplome::setEnCours(bool enCours) { this->enCours = enCours; }

// Affichage
void Diplome::afficherEnCours() const
{
    std::cout << "Diplome: " << nom << " (Code: " << code << ")\n"
              << "Statut: En cours\n"
              << "Date de premiere inscription: " << datePremiereInscription
              << ", Numero d'annee: " << numeroAnnee << std::endl;
}

void Diplome::afficherNonEnCours() const
{
    std::cout << "Diplome: " << nom << " (Code: " << code << ")\n"
              << "Date d'obtention: " << dateObtention << "\n"
              << "Lieu d'obtention: " << lieuObtention << std::endl;
}

void Diplome::modifierDiplome(const std::vector<Diplome> &diplomes)
{
    std::string code;
    std::cout << "Entrez le code du diplome a modifier : ";
    std::cin.ignore();
    std::getline(std::cin, code);

    auto it = std::find_if(diplomes.begin(), diplomes.end(),
                           [&code](const Diplome &d)
                           { return d.getCode() == code; });

    if (it != diplomes.end())
    {
        Diplome diplome = *it; // Create a copy for modification

        std::cout << "Modification des informations du diplome (laissez vide pour conserver l'ancienne valeur):\n";

        std::string nouveauNom, nouvelleDateObtention, nouveauLieuObtention, nouvelleDatePremiereInscription;
        int nouveauNumeroAnnee;
        bool nouveauEnCours;

        // Modifier le nom
        std::cout << "Nom actuel : " << diplome.getNom() << "\nNouveau nom : ";
        std::getline(std::cin, nouveauNom);
        if (!nouveauNom.empty())
        {
            diplome.setNom(nouveauNom);
        }

        // Modifier le lieu d'obtention
        std::cout << "Lieu d'obtention actuel : " << diplome.getLieuObtention() << "\nNouveau lieu d'obtention : ";
        std::getline(std::cin, nouveauLieuObtention);
        if (!nouveauLieuObtention.empty())
        {
            diplome.setLieuObtention(nouveauLieuObtention);
        }

        // Modifier la date d'obtention (si le diplôme est terminé)
        if (!diplome.isEnCours())
        {
            std::cout << "Date d'obtention actuelle : " << diplome.getDateObtention() << "\nNouvelle date d'obtention : ";
            std::getline(std::cin, nouvelleDateObtention);
            if (!nouvelleDateObtention.empty())
            {
                diplome.setDateObtention(nouvelleDateObtention);
            }
        }

        // Modifier la première inscription (si le diplôme est en cours)
        if (diplome.isEnCours())
        {
            std::cout << "Date de premiere inscription actuelle : " << diplome.getDatePremiereInscription()
                      << "\nNouvelle date de premiere inscription : ";
            std::getline(std::cin, nouvelleDatePremiereInscription);
            if (!nouvelleDatePremiereInscription.empty())
            {
                diplome.setDatePremiereInscription(nouvelleDatePremiereInscription);
            }

            std::cout << "Numero d'annee actuel : " << diplome.getNumeroAnnee() << "\nNouveau numero d'annee : ";
            while (!(std::cin >> nouveauNumeroAnnee) || nouveauNumeroAnnee <= 0)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Numero invalide. Entrez un entier positif : ";
            }
            diplome.setNumeroAnnee(nouveauNumeroAnnee);
        }

        // Modifier l'état "en cours"
        std::cout << "Ce diplome est-il toujours en cours ? (1: Oui, 0: Non) : ";
        while (!(std::cin >> nouveauEnCours))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Valeur invalide. Entrez 1 pour Oui ou 0 pour Non : ";
        }
        diplome.setEnCours(nouveauEnCours);

        std::cout << "Diplome modifie avec succes.\n";
    }
    else
    {
        std::cout << "Diplome introuvable.\n";
    }
}
