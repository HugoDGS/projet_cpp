#pragma once

#include <iostream>
#include <string>
#include <vector>

class Entreprise
{
private:
    int idEntreprise;                 // ID unique pour chaque entreprise
    std::string nom;
    std::string adresse;
    std::string contactNom;
    std::string contactTel;

    static int compteurID;            // Compteur global pour générer des IDs uniques

public:
    Entreprise(const std::string &nom, const std::string &adresse,
               const std::string &contactNom, const std::string &contactTel);

    // Getters
    int getIdEntreprise() const;
    std::string getNom() const;
    std::string getAdresse() const;
    std::string getContactNom() const;
    std::string getContactTel() const;

    // Setters
    void setNom(const std::string &nom);
    void setAdresse(const std::string &adresse);
    void setContactNom(const std::string &contactNom);
    void setContactTel(const std::string &contactTel);

    // Méthodes
    static Entreprise *creerEntreprise();
    static void supprimerEntreprise(std::vector<Entreprise *> &entreprises);
    static void modifierEntreprise(std::vector<Entreprise *> &entreprises);

    void afficher() const;
};
