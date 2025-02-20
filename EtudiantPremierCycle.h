#pragma once
#include "Etudiant.h"

class EtudiantPremierCycle : public Etudiant {
private:
    std::string serieBac;
    int anneeBac;
    std::string lieuBac;

public:
    // Constructeur
    EtudiantPremierCycle(int numeroEtudiant, const std::string& nom, const std::string& prenom,
                         const std::string& adresse, const std::string& telephone,
                         const std::string& serieBac, int anneeBac, const std::string& lieuBac);

    // Getters
    std::string getSerieBac() const;
    int getAnneeBac() const;
    std::string getLieuBac() const;

    // Méthodes
    void afficher() const override;
    void modifierCycle();

};
