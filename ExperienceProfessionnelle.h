#pragma once
#include <string>
#include <iostream>
#include <vector>

class ExperienceProfessionnelle
{
private:
    std::string dateDebut;
    std::string dateFin;
    std::string entreprise;
    std::string fonction;

public:
    // Constructeur
    ExperienceProfessionnelle(const std::string &dateDebut, const std::string &dateFin,
                              const std::string &entreprise, const std::string &fonction);

    // Getters et Setters
    std::string getDateDebut() const;
    std::string getDateFin() const;
    std::string getEntreprise() const;
    std::string getFonction() const;
    void setDateDebut(const std::string &dateDebut);
    void setDateFin(const std::string &dateFin);
    void setEntreprise(const std::string &entreprise);
    void setFonction(const std::string &fonction);

    // Méthode d'affichage
    void afficher() const;

    // Méthode statique pour modifier une expérience
    static void modifierExperience(std::vector<ExperienceProfessionnelle> &experiences);
};