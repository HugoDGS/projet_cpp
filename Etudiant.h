#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Diplome.h"
#include "ExperienceProfessionnelle.h"

class Etudiant
{
private:
    int numeroEtudiant;
    std::string nom;
    std::string prenom;
    std::string adresse;
    std::string telephone;
    std::vector<Diplome> diplomes;
    std::vector<ExperienceProfessionnelle> experiences;

public:
    virtual ~Etudiant() = default;

    // Constructeur
    Etudiant(int numeroEtudiant, const std::string &nom, const std::string &prenom,
             const std::string &adresse, const std::string &telephone);

    // Getters
    int getNumeroEtudiant() const;
    std::string getNom() const;
    std::string getPrenom() const;
    std::string getAdresse() const;
    std::string getTelephone() const;
    const std::vector<Diplome> &getDiplomes() const;
    std::vector<ExperienceProfessionnelle>& getExperiences();

    // Setters
    void setNumeroEtudiant(int numeroEtudiant);
    void setNom(const std::string &nom);
    void setPrenom(const std::string &prenom);
    void setAdresse(const std::string &adresse);
    void setTelephone(const std::string &telephone);

    // Méthodes
    void addDiplome(const Diplome &diplome);
    void addExperience(const ExperienceProfessionnelle &experience);
    static Etudiant *creerEtudiantComplet();
    static void supprimerEtudiant(std::vector<Etudiant *> &listeEtudiants);
    static void modifierEtudiant(std::vector<Etudiant *> &listeEtudiants);
    virtual void afficher() const;
};
