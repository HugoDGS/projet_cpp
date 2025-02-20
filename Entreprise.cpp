#include "Entreprise.h"
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <regex>


// Initialisation du compteur global
int Entreprise::compteurID = 1;

// Constructeur avec ID automatique
Entreprise::Entreprise(const std::string &nom, const std::string &adresse,
                       const std::string &contactNom, const std::string &contactTel)
    : idEntreprise(compteurID++), nom(nom), adresse(adresse), contactNom(contactNom), contactTel(contactTel) {}

// Getters
int Entreprise::getIdEntreprise() const { return idEntreprise; }
std::string Entreprise::getNom() const { return nom; }
std::string Entreprise::getAdresse() const { return adresse; }
std::string Entreprise::getContactNom() const { return contactNom; }
std::string Entreprise::getContactTel() const { return contactTel; }

// Setters
void Entreprise::setNom(const std::string &nom) { this->nom = nom; }
void Entreprise::setAdresse(const std::string &adresse) { this->adresse = adresse; }
void Entreprise::setContactNom(const std::string &contactNom) { this->contactNom = contactNom; }
void Entreprise::setContactTel(const std::string &contactTel) { this->contactTel = contactTel; }

bool isValidPhone(const std::string &phone)
{
    std::regex pattern("^0[1-9][0-9]{8}$");
    return std::regex_match(phone, pattern);
}

// Méthode interactive pour créer une entreprise
Entreprise *Entreprise::creerEntreprise()
{
    std::string nom, adresse, contactNom, contactTel;

    std::cout << "===== Creation d'une entreprise =====\n";

    // Entrer le nom de l'entreprise
    do
    {
        std::cout << "Nom de l'entreprise : ";
        std::cin.ignore();
        std::getline(std::cin, nom);
        if (nom.empty())
        {
            std::cout << "Le nom ne peut pas être vide.\n";
        }
    } while (nom.empty());

    // Entrer l'adresse
    do
    {
        std::cout << "Adresse de l'entreprise : ";
        std::getline(std::cin, adresse);
        if (adresse.empty())
        {
            std::cout << "L'adresse ne peut pas être vide.\n";
        }
    } while (adresse.empty());

    // Entrer le nom du contact
    do
    {
        std::cout << "Nom du contact : ";
        std::getline(std::cin, contactNom);
        if (contactNom.empty())
        {
            std::cout << "Le nom du contact ne peut pas être vide.\n";
        }
    } while (contactNom.empty());

    // Entrer le téléphone du contact
    do
    {
        std::cout << "Telephone du contact : ";
        std::getline(std::cin, contactTel);
        if (!isValidPhone(contactTel))
        {
            std::cout << "Telephone invalide. Format attendu : 0XXXXXXXXX (10 chiffres).\n";
        }
    } while (!isValidPhone(contactTel));

    std::cout << "Entreprise creee avec succes.\n";

    return new Entreprise(nom, adresse, contactNom, contactTel);
}

// Méthode pour afficher les informations de l'entreprise
void Entreprise::afficher() const
{
    std::cout << "\n=====================================" << std::endl;
    std::cout << "         FICHE DE L'ENTREPRISE       " << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "ID                  : " << idEntreprise << std::endl;
    std::cout << "Nom                 : " << nom << std::endl;
    std::cout << "Adresse             : " << adresse << std::endl;
    std::cout << "Contact             : " << contactNom << std::endl;
    std::cout << "Telephone du contact: " << contactTel << std::endl;
    std::cout << "=====================================\n" << std::endl;
}


void Entreprise::modifierEntreprise(std::vector<Entreprise *> &entreprises)
{
    int id;
    std::cout << "Entrez l'ID de l'entreprise a modifier : ";
    std::cin >> id;

    auto it = std::find_if(entreprises.begin(), entreprises.end(),
                           [id](Entreprise *e) { return e->getIdEntreprise() == id; });

    if (it != entreprises.end())
    {
        Entreprise *entreprise = *it;

        std::string nouveauNom, nouvelleAdresse, nouveauContactNom, nouveauContactTel;

        std::cout << "Modifiez les informations de l'entreprise (laissez vide pour conserver l'ancienne valeur):\n";

        std::cin.ignore(); // Ignorer les caractères résiduels

        // Modifier le nom
        std::cout << "Nom actuel : " << entreprise->getNom() << "\nNouveau nom : ";
        std::getline(std::cin, nouveauNom);
        if (!nouveauNom.empty())
        {
            entreprise->setNom(nouveauNom);
        }

        // Modifier l'adresse
        std::cout << "Adresse actuelle : " << entreprise->getAdresse() << "\nNouvelle adresse : ";
        std::getline(std::cin, nouvelleAdresse);
        if (!nouvelleAdresse.empty())
        {
            entreprise->setAdresse(nouvelleAdresse);
        }

        // Modifier le contact
        std::cout << "Nom du contact actuel : " << entreprise->getContactNom() << "\nNouveau nom du contact : ";
        std::getline(std::cin, nouveauContactNom);
        if (!nouveauContactNom.empty())
        {
            entreprise->setContactNom(nouveauContactNom);
        }

        // Modifier le téléphone du contact
        std::cout << "Téléphone actuel : " << entreprise->getContactTel() << "\nNouveau téléphone : ";
        std::getline(std::cin, nouveauContactTel);
        if (!nouveauContactTel.empty())
        {
            entreprise->setContactTel(nouveauContactTel);
        }

        std::cout << "Entreprise modifiée avec succès.\n";
    }
    else
    {
        std::cout << "Entreprise introuvable.\n";
    }
}

void Entreprise::supprimerEntreprise(std::vector<Entreprise *> &entreprises)
{
    int id;
    std::cout << "Entrez l'ID de l'entreprise a supprimer : ";
    std::cin >> id;

    auto it = std::find_if(entreprises.begin(), entreprises.end(),
                           [id](Entreprise *e) { return e->getIdEntreprise() == id; });

    if (it != entreprises.end())
    {
        delete *it; // Libérer la mémoire
        entreprises.erase(it);
        std::cout << "Entreprise supprimee avec succes.\n";
    }
    else
    {
        std::cout << "Entreprise introuvable.\n";
    }
}