#pragma once
#include <string>
#include <iostream>
#include <vector>

class Diplome {
private:
    std::string code;
    std::string nom;
    std::string dateObtention;
    std::string lieuObtention;

    // Informations d'inscription
    std::string datePremiereInscription;
    int numeroAnnee;

    // Indicateur si le diplôme est en cours
    bool enCours;

public:
    // Constructeur
    Diplome(const std::string& code, const std::string& nom,
            const std::string& dateObtention, const std::string& lieuObtention,
            const std::string& datePremiereInscription, int numeroAnnee, bool enCours);

    // Getters
    std::string getDatePremiereInscription() const;
    std::string getCode() const;
    std::string getNom() const;
    std::string getDateObtention() const;
    std::string getLieuObtention() const;
    int getNumeroAnnee() const;
    bool isEnCours() const;

    // Setters
    void setNom(const std::string& nom);
    void setLieuObtention(const std::string& lieuObtention);
    void setDateObtention(const std::string& dateObtention);
    void setDatePremiereInscription(const std::string& date);
    void setNumeroAnnee(int annee);
    void setEnCours(bool enCours);

    // Méthode d'affichage
    void afficherNonEnCours() const;
    void afficherEnCours() const;

    // Fonction statique pour modifier un diplôme
    static void modifierDiplome(const std::vector<Diplome> &diplomes);
};
