#pragma once
#include "Etudiant.h"

class EtudiantDeuxiemeCycle : public Etudiant {
private:
    std::string disciplinePrincipale;

public:
    // Constructeur
    EtudiantDeuxiemeCycle(int numeroEtudiant, const std::string& nom, const std::string& prenom,
                          const std::string& adresse, const std::string& telephone,
                          const std::string& disciplinePrincipale);

    // Getter
    std::string getDisciplinePrincipale() const;

    // Méthodes
    void afficher() const override;
    void modifierCycle();

};
