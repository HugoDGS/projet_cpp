#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Entreprise.h"
#include "Etudiant.h"

class RendezVous {
private:
    std::string date;      // Date du rendez-vous (format: "YYYY-MM-DD")
    std::string heureDebut; // Heure de début (format: "HH:MM")
    std::string heureFin;   // Heure de fin (format: "HH:MM")
    Entreprise* entreprise; // Entreprise associée
    Etudiant* etudiant;     // Étudiant associé

public:
    RendezVous(const std::string& date, const std::string& heureDebut, const std::string& heureFin,
               Entreprise* entreprise, Etudiant* etudiant);

    // Getters
    std::string getDate() const;
    std::string getHeureDebut() const;
    std::string getHeureFin() const;
    Entreprise* getEntreprise() const;
    Etudiant* getEtudiant() const;

    // Setters
    void setDate(const std::string& date);
    void setHeureDebut(const std::string& heureDebut);
    void setHeureFin(const std::string& heureFin);
    void setEntreprise(Entreprise* entreprise);
    void setEtudiant(Etudiant* etudiant);

    // Gestion des rendez-vous
    static void creerRendezVous(std::vector<RendezVous>& rendezVousListe,
                                std::vector<Entreprise*>& entreprises,
                                std::vector<Etudiant*>& etudiants);

    static void modifierRendezVous(std::vector<RendezVous>& rendezVousListe,
                                   std::vector<Entreprise*>& entreprises,
                                   std::vector<Etudiant*>& etudiants);

    static void supprimerRendezVous(std::vector<RendezVous>& rendezVousListe);

    static bool verifierConflit(const std::vector<RendezVous>& rendezVousListe, 
                                const std::string& date, 
                                const std::string& heureDebut, 
                                const std::string& heureFin, 
                                Entreprise* entreprise, 
                                Etudiant* etudiant);

    void afficher() const;
};
