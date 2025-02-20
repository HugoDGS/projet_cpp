#include "Etudiant.h"
#include <unordered_set>
#include <iostream>
#include "EtudiantDeuxiemeCycle.h"
#include "EtudiantPremierCycle.h"
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <sstream>


using namespace std;

// Conteneur global pour stocker les numeros etudiants uniques
std::unordered_set<int> numerosEtudiants;


// Fonction pour valider un numéro de téléphone français
bool isValidePhone(const std::string &phone)
{
    std::regex pattern("^0[1-9][0-9]{8}$");
    return std::regex_match(phone, pattern);
}

// Fonction pour valider une date au format YYYY-MM-DD
bool isValidDate(const std::string &date)
{
    std::regex pattern(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$)");
    return std::regex_match(date, pattern);
}

// Fonction pour comparer deux dates au format YYYY-MM-DD
bool isDateBefore(const std::string &startDate, const std::string &endDate)
{
    return startDate < endDate;
}

// Fonction pour vérifier une année valide
bool isValidYear(int year)
{
    int currentYear = 2025; 
    return year > 0 && year < currentYear;
}

// Constructeur
Etudiant::Etudiant(int numeroEtudiant, const std::string &nom, const std::string &prenom,
                   const std::string &adresse, const std::string &telephone)
    : numeroEtudiant(numeroEtudiant), nom(nom), prenom(prenom), adresse(adresse), telephone(telephone) {}

// Getters
int Etudiant::getNumeroEtudiant() const { return numeroEtudiant; }
std::string Etudiant::getNom() const { return nom; }
std::string Etudiant::getPrenom() const { return prenom; }
std::string Etudiant::getAdresse() const { return adresse; }
std::string Etudiant::getTelephone() const { return telephone; }
const std::vector<Diplome> &Etudiant::getDiplomes() const { return diplomes; }

std::vector<ExperienceProfessionnelle> &Etudiant::getExperiences()
{
    return experiences;
}

// Setters
void Etudiant::setNumeroEtudiant(int numeroEtudiant) { this->numeroEtudiant = numeroEtudiant; }
void Etudiant::setNom(const std::string &nom) { this->nom = nom; }
void Etudiant::setPrenom(const std::string &prenom) { this->prenom = prenom; }
void Etudiant::setAdresse(const std::string &adresse) { this->adresse = adresse; }
void Etudiant::setTelephone(const std::string &telephone) { this->telephone = telephone; }

// Ajout de diplome
void Etudiant::addDiplome(const Diplome &diplome)
{
    diplomes.push_back(diplome);
}

// Ajout d'experience
void Etudiant::addExperience(const ExperienceProfessionnelle &experience)
{
    experiences.push_back(experience);
}

void Etudiant::afficher() const
{
    std::cout << "\n===============================" << std::endl;
    std::cout << "       FICHE DE L'ETUDIANT       " << std::endl;
    std::cout << "===============================\n"
              << std::endl;

    std::cout << "Nom complet : " << nom << " " << prenom << std::endl;
    std::cout << "Adresse     : " << adresse << std::endl;
    std::cout << "Telephone   : " << telephone << std::endl;
    std::cout << "Numero ID   : " << numeroEtudiant << std::endl;


    std::cout << "\n-------------------------------" << std::endl;
    std::cout << "Diplomes obtenus :" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    for (const auto &diplome : diplomes)
    {
        if (!diplome.isEnCours())
            diplome.afficherNonEnCours();
    }

    std::cout << "\n-------------------------------" << std::endl;
    std::cout << "Diplomes en cours :" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    for (const auto &diplome : diplomes)
    {
        if (diplome.isEnCours())
            diplome.afficherEnCours();
    }

    std::cout << "\n-------------------------------" << std::endl;
    std::cout << "Experiences professionnelles :" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    for (const auto &experience : experiences)
    {
        experience.afficher();
    }

    std::cout << "\n-------------------------------\n"
              << std::endl;
}

// Fonction principale pour creer un etudiant complet
Etudiant *Etudiant::creerEtudiantComplet()
{
    std::string nom, prenom, adresse, telephone;
    int numeroEtudiant, choixCycle;

    // 1. Collecte des informations de base
    std::cout << "Creation d'un etudiant\n";

    // Verification de l'unicite du numero etudiant
    do
    {
        std::cout << "Numero etudiant : ";
        while (!(std::cin >> numeroEtudiant) || numeroEtudiant <= 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Numero invalide. Entrez un entier positif : ";
        }

        if (numerosEtudiants.find(numeroEtudiant) != numerosEtudiants.end())
        {
            std::cout << "Ce numero etudiant existe deja. Veuillez entrer un autre numero.\n";
        }
        else
        {
            break; // Numero unique
        }
    } while (true);

    numerosEtudiants.insert(numeroEtudiant);

    std::cin.ignore();
    std::cout << "Nom : ";
    std::getline(std::cin, nom);

    std::cout << "Prenom : ";
    std::getline(std::cin, prenom);

    std::cout << "Adresse : ";
    std::getline(std::cin, adresse);

    do
    {
        std::cout << "Telephone : ";
        std::getline(std::cin, telephone);
        if (!isValidePhone(telephone))
        {
            std::cout << "Telephone invalide. Format attendu : 0XXXXXXXXX (10 chiffres).\n";
        }
    } while (!isValidePhone(telephone));

    // 2. Determiner le cycle
    std::cout << "L'etudiant est-il :\n1. En premier cycle\n2. En deuxieme cycle\nVotre choix : ";
    while (!(std::cin >> choixCycle) || (choixCycle != 1 && choixCycle != 2))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Choix invalide. Veuillez entrer 1 pour Premier Cycle ou 2 pour Deuxieme Cycle : ";
    }

    std::cin.ignore();
    Etudiant *etudiant = nullptr;

    if (choixCycle == 1)
    {
        std::string serieBac, lieuBac;
        int anneeBac;

        std::cout << "Serie du Bac : ";
        std::getline(std::cin, serieBac);

        do
        {
            std::cout << "Annee du Bac : ";
            while (!(std::cin >> anneeBac) || !isValidYear(anneeBac))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Annee invalide. Veuillez entrer une annee valide avant 2025 : ";
            }
        } while (!isValidYear(anneeBac));

        std::cin.ignore();
        std::cout << "Lieu du Bac : ";
        std::getline(std::cin, lieuBac);

        etudiant = new EtudiantPremierCycle(numeroEtudiant, nom, prenom, adresse, telephone, serieBac, anneeBac, lieuBac);
    }
    else if (choixCycle == 2)
    {
        std::string disciplinePrincipale;
        std::cout << "Discipline principale : ";
        std::getline(std::cin, disciplinePrincipale);

        etudiant = new EtudiantDeuxiemeCycle(numeroEtudiant, nom, prenom, adresse, telephone, disciplinePrincipale);
    }

    // Ajout de diplomes
    int ajouterDiplome = 0;
    do
    {
        std::cout << "Souhaitez-vous ajouter un diplome pour cet etudiant ? (1: Oui, 0: Non) : ";
        std::cin >> ajouterDiplome;

        if (ajouterDiplome == 1)
        {
            std::string code, nomDiplome, dateObtention, lieuObtention, datePremiereInscription;
            int numeroAnnee;
            bool enCours;
            std::cin.ignore();

            std::cout << "Code du diplome : ";
            std::getline(std::cin, code);
            std::cout << "Nom du diplome : ";
            std::getline(std::cin, nomDiplome);

            std::cout << "Ce diplome est-il en cours ? (1: Oui, 0: Non) : ";
            while (!(std::cin >> enCours))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Valeur invalide. Entrez 1 pour Oui ou 0 pour Non : ";
            }

            if (!enCours)
            {
                std::cout << "Lieu d'obtention : ";
                std::cin.ignore();
                std::getline(std::cin, lieuObtention);

                do
                {
                    std::cout << "Date d'obtention (YYYY-MM-DD) : ";
                    std::getline(std::cin, dateObtention);
                    if (!isValidDate(dateObtention))
                    {
                        std::cout << "Format invalide. Utilisez YYYY-MM-DD.\n";
                    }
                } while (!isValidDate(dateObtention));
            }

            if (enCours)
            {
                do
                {
                    std::cout << "Date de premiere inscription (YYYY-MM-DD) : ";
                    std::cin.ignore();
                    std::getline(std::cin, datePremiereInscription);
                    if (!isValidDate(datePremiereInscription))
                    {
                        std::cout << "Format invalide. Utilisez YYYY-MM-DD.\n";
                    }
                } while (!isValidDate(datePremiereInscription));

                std::cout << "Numero d'annee (ex: 3 pour Licence 3) : ";
                while (!(std::cin >> numeroAnnee) || numeroAnnee <= 0)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Numero invalide. Entrez un entier positif : ";
                }
                std::cin.ignore();
            }

            Diplome diplome(code, nomDiplome, dateObtention, lieuObtention, datePremiereInscription, numeroAnnee, enCours);
            etudiant->addDiplome(diplome);
        }

    } while (ajouterDiplome != 0);

    int ajouterExperience = 0;
    do
    {
        std::cout << "Souhaitez-vous ajouter une experience professionnelle pour cet etudiant ? (1: Oui, 0: Non) : ";
        std::cin >> ajouterExperience;

        if (ajouterExperience == 1)
        {
            std::string intitule, entreprise, dateDebut, dateFin;
            std::cin.ignore();

            std::cout << "Intitule du poste : ";
            std::getline(std::cin, intitule);
            std::cout << "Entreprise : ";
            std::getline(std::cin, entreprise);

            do
            {
                std::cout << "Date de debut (YYYY-MM-DD) : ";
                std::getline(std::cin, dateDebut);
                if (!isValidDate(dateDebut))
                {
                    std::cout << "Format invalide. Utilisez YYYY-MM-DD.\n";
                }
            } while (!isValidDate(dateDebut));

            do
            {
                std::cout << "Date de fin (YYYY-MM-DD) : ";
                std::getline(std::cin, dateFin);
                if (!isValidDate(dateFin) || !isDateBefore(dateDebut, dateFin))
                {
                    std::cout << "Format invalide ou la date de fin est avant la date de debut.\n";
                }
            } while (!isValidDate(dateFin) || !isDateBefore(dateDebut, dateFin));

            ExperienceProfessionnelle experience(dateDebut, dateFin, entreprise, intitule);
            etudiant->addExperience(experience);
        }

    } while (ajouterExperience != 0);

    return etudiant;
}
//fonction pour supprimer un etudiant
void Etudiant::supprimerEtudiant(std::vector<Etudiant *> &listeEtudiants)
{
    int numero;
    std::cout << "Entrez le numero d'etudiant a supprimer : ";
    std::cin >> numero;

    auto it = std::find_if(listeEtudiants.begin(), listeEtudiants.end(),
                           [numero](Etudiant *e)
                           { return e->getNumeroEtudiant() == numero; });

    if (it != listeEtudiants.end())
    {
        delete *it; // Libérer la mémoire
        listeEtudiants.erase(it);
        std::cout << "Etudiant supprime avec succes.\n";
    }
    else
    {
        std::cout << "Etudiant introuvable.\n";
    }
}
//fonction pour modifier un etudiant
void Etudiant::modifierEtudiant(std::vector<Etudiant *> &listeEtudiants)
{
    int numero;
    std::cout << "Entrez le numero d'etudiant a modifier : ";
    std::cin >> numero;

    auto it = std::find_if(listeEtudiants.begin(), listeEtudiants.end(),
                           [numero](Etudiant *e)
                           { return e->getNumeroEtudiant() == numero; });

    if (it != listeEtudiants.end())
    {
        Etudiant *etudiant = *it;

        // Modification des informations personnelles de l'étudiant
        std::cout << "\nModification des informations personnelles de l'etudiant :\n";
        std::string nouveauNom, nouveauPrenom, nouvelleAdresse, nouveauTelephone;

        std::cout << "Nom actuel : " << etudiant->getNom() << "\nNouveau nom : ";
        std::cin.ignore();
        std::getline(std::cin, nouveauNom);
        if (!nouveauNom.empty())
            etudiant->setNom(nouveauNom);

        std::cout << "Prénom actuel : " << etudiant->getPrenom() << "\nNouveau prénom : ";
        std::getline(std::cin, nouveauPrenom);
        if (!nouveauPrenom.empty())
            etudiant->setPrenom(nouveauPrenom);

        std::cout << "Adresse actuelle : " << etudiant->getAdresse() << "\nNouvelle adresse : ";
        std::getline(std::cin, nouvelleAdresse);
        if (!nouvelleAdresse.empty())
            etudiant->setAdresse(nouvelleAdresse);

        std::cout << "Téléphone actuel : " << etudiant->getTelephone() << "\nNouveau téléphone : ";
        std::getline(std::cin, nouveauTelephone);
        if (!nouveauTelephone.empty())
            etudiant->setTelephone(nouveauTelephone);

        // Modification des diplômes de l'étudiant
        std::cout << "\nSouhaitez-vous modifier les diplômes de l'étudiant ? (1: Oui, 0: Non) : ";
        int choixDiplome;
        std::cin >> choixDiplome;
        if (choixDiplome == 1)
        {
            Diplome::modifierDiplome(etudiant->getDiplomes());
        }

        // Modification du cycle de l'étudiant
        std::cout << "\nSouhaitez-vous modifier le cycle de l'étudiant ? (1: Oui, 0: Non) : ";
        int choixCycle;
        std::cin >> choixCycle;
        if (choixCycle == 1)
        {
            if (auto *premierCycle = dynamic_cast<EtudiantPremierCycle *>(etudiant))
            {
                premierCycle->modifierCycle();
            }
            else if (auto *deuxiemeCycle = dynamic_cast<EtudiantDeuxiemeCycle *>(etudiant))
            {
                deuxiemeCycle->modifierCycle();
            }
        }
        std::cout << "\nSouhaitez-vous modifier les expériences professionnelles de l'étudiant ? (1: Oui, 0: Non) : ";
        int choixExperience;
        std::cin >> choixExperience;
        if (choixExperience == 1)
        {
            ExperienceProfessionnelle::modifierExperience(etudiant->getExperiences());
        }

        std::cout << "\nLes informations de l'étudiant ont été modifiées avec succès.\n";
    }
    else
    {
        std::cout << "Etudiant introuvable.\n";
    }
}