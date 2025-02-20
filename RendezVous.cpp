#include "RendezVous.h"
#include <regex>
#include <iomanip>
RendezVous::RendezVous(const std::string &date, const std::string &heureDebut, const std::string &heureFin,
                       Entreprise *entreprise, Etudiant *etudiant)
    : date(date), heureDebut(heureDebut), heureFin(heureFin), entreprise(entreprise), etudiant(etudiant) {}

std::string RendezVous::getDate() const { return date; }
std::string RendezVous::getHeureDebut() const { return heureDebut; }
std::string RendezVous::getHeureFin() const { return heureFin; }
Entreprise *RendezVous::getEntreprise() const { return entreprise; }
Etudiant *RendezVous::getEtudiant() const { return etudiant; }

void RendezVous::setDate(const std::string &date) { this->date = date; }
void RendezVous::setHeureDebut(const std::string &heureDebut) { this->heureDebut = heureDebut; }
void RendezVous::setHeureFin(const std::string &heureFin) { this->heureFin = heureFin; }
void RendezVous::setEntreprise(Entreprise *entreprise) { this->entreprise = entreprise; }
void RendezVous::setEtudiant(Etudiant *etudiant) { this->etudiant = etudiant; }

void RendezVous::afficher() const
{
    std::cout << "Date: " << date << ", Heure: " << heureDebut << " - " << heureFin << "\n";
    std::cout << "Entreprise: " << entreprise->getNom() << ", Étudiant: " << etudiant->getNom() << "\n";
}

// Fonction pour vérifier les conflits
bool RendezVous::verifierConflit(const std::vector<RendezVous> &rendezVousListe,
                                 const std::string &date,
                                 const std::string &heureDebut,
                                 const std::string &heureFin,
                                 Entreprise *entreprise,
                                 Etudiant *etudiant)
{
    for (const auto &rendezVous : rendezVousListe)
    {
        if (rendezVous.getDate() == date &&
            ((heureDebut >= rendezVous.getHeureDebut() && heureDebut < rendezVous.getHeureFin()) ||
             (heureFin > rendezVous.getHeureDebut() && heureFin <= rendezVous.getHeureFin())))
        {
            if (rendezVous.getEntreprise() == entreprise || rendezVous.getEtudiant() == etudiant)
            {
                return true;
            }
        }
    }
    return false;
}

bool estDateValide(const std::string &date)
{
    struct tm tm;
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%Y-%m-%d");

    if (ss.fail())
    {
        return false; // Si l'analyse échoue, la date n'est pas valide
    }

    // Comparer l'année, le mois et le jour pour s'assurer que la date existe réellement
    time_t t = mktime(&tm);
    return t != -1;
}

// Création d'un rendez-vous
void RendezVous::creerRendezVous(std::vector<RendezVous> &rendezVousListe,
                                 std::vector<Entreprise *> &entreprises,
                                 std::vector<Etudiant *> &etudiants)
{
    std::string date, heureDebut, heureFin, nomEntreprise;
    int numeroEtudiant;

    std::cout << "===== Creation d'un rendez-vous =====\n";

    // Validation du format de la date
    std::regex dateRegex(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$)");
    do
    {
        std::cout << "Date (YYYY-MM-DD): ";
        std::cin >> date;
        if (!std::regex_match(date, dateRegex))
        {
            std::cout << "Erreur : La date doit être au format YYYY-MM-DD.\n";
        }
    } while (!std::regex_match(date, dateRegex));

    int heureDebutInt = std::stoi(heureDebut.substr(0, 2));
    int minuteDebutInt = std::stoi(heureDebut.substr(3, 2));

    int heureFinInt = std::stoi(heureFin.substr(0, 2));
    int minuteFinInt = std::stoi(heureFin.substr(3, 2));

    if (heureDebutInt < 0 || heureDebutInt >= 24 || minuteDebutInt < 0 || minuteDebutInt >= 60)
    {
        std::cout << "Erreur : L'heure de début n'est pas valide.\n";
        return;
    }

    if (heureFinInt < 0 || heureFinInt >= 24 || minuteFinInt < 0 || minuteFinInt >= 60)
    {
        std::cout << "Erreur : L'heure de fin n'est pas valide.\n";
        return;
    }
    if (heureDebut >= heureFin)
    {
        std::cout << "Erreur : L'heure de début doit être inférieure à l'heure de fin.\n";
        return;
    }

    // Choix de l'entreprise
    std::cout << "Entrez le nom de l'entreprise : ";
    std::cin.ignore();
    std::getline(std::cin, nomEntreprise);

    Entreprise *entreprise = nullptr;
    for (auto *e : entreprises)
    {
        if (e->getNom() == nomEntreprise)
        {
            entreprise = e;
            break;
        }
    }
    if (!entreprise)
    {
        std::cout << "Entreprise introuvable !\n";
        return;
    }

    // Choix de l'étudiant
    std::cout << "Entrez le numero de l'etudiant : ";
    std::cin >> numeroEtudiant;

    Etudiant *etudiant = nullptr;
    for (auto *e : etudiants)
    {
        if (e->getNumeroEtudiant() == numeroEtudiant)
        {
            etudiant = e;
            break;
        }
    }
    if (!etudiant)
    {
        std::cout << "Étudiant introuvable !\n";
        return;
    }

    // Vérifier les conflits
    if (verifierConflit(rendezVousListe, date, heureDebut, heureFin, entreprise, etudiant))
    {
        std::cout << "Conflit detecte ! L'entreprise ou l'etudiant est deja occupe a cette heure.\n";
        return;
    }

    // Ajouter le rendez-vous
    rendezVousListe.emplace_back(date, heureDebut, heureFin, entreprise, etudiant);
    std::cout << "Rendez-vous cree avec succes !\n";
}
void RendezVous::modifierRendezVous(std::vector<RendezVous> &rendezVousListe,
                                    std::vector<Entreprise *> &entreprises,
                                    std::vector<Etudiant *> &etudiants)
{
    int index;
    std::cout << "Entrez l'index du rendez-vous a modifier : ";
    std::cin >> index;

    if (index < 0 || index >= rendezVousListe.size())
    {
        std::cout << "Rendez-vous introuvable !\n";
        return;
    }

    RendezVous &rendezVous = rendezVousListe[index];

    // Proposer les modifications
    std::string nouvelleDate, nouvelleHeureDebut, nouvelleHeureFin, nouveauNomEntreprise;
    int nouveauNumeroEtudiant;

    std::cout << "Nouvelle date (YYYY-MM-DD, laissez vide pour conserver) : ";
    std::cin.ignore();
    std::getline(std::cin, nouvelleDate);
    if (!nouvelleDate.empty())
        rendezVous.setDate(nouvelleDate);

    std::cout << "Nouvelle heure de début (HH:MM, laissez vide pour conserver) : ";
    std::getline(std::cin, nouvelleHeureDebut);
    if (!nouvelleHeureDebut.empty())
        rendezVous.setHeureDebut(nouvelleHeureDebut);

    std::cout << "Nouvelle heure de fin (HH:MM, laissez vide pour conserver) : ";
    std::getline(std::cin, nouvelleHeureFin);
    if (!nouvelleHeureFin.empty())
        rendezVous.setHeureFin(nouvelleHeureFin);

    // Modifier l'entreprise
    std::cout << "Nom actuel de l'entreprise : " << rendezVous.getEntreprise()->getNom() << "\n";
    std::cout << "Nouveau nom de l'entreprise (laissez vide pour conserver) : ";
    std::getline(std::cin, nouveauNomEntreprise);
    if (!nouveauNomEntreprise.empty())
    {
        Entreprise *nouvelleEntreprise = nullptr;
        for (auto *e : entreprises)
        {
            if (e->getNom() == nouveauNomEntreprise)
            {
                nouvelleEntreprise = e;
                break;
            }
        }
        if (nouvelleEntreprise)
        {
            rendezVous.setEntreprise(nouvelleEntreprise);
        }
        else
        {
            std::cout << "Entreprise introuvable. Modification ignorée.\n";
        }
    }

    // Modifier l'étudiant
    std::cout << "Numéro actuel de l'étudiant : " << rendezVous.getEtudiant()->getNumeroEtudiant() << "\n";
    std::cout << "Nouveau numéro de l'étudiant (0 pour conserver) : ";
    std::cin >> nouveauNumeroEtudiant;
    if (nouveauNumeroEtudiant != 0)
    {
        Etudiant *nouvelEtudiant = nullptr;
        for (auto *e : etudiants)
        {
            if (e->getNumeroEtudiant() == nouveauNumeroEtudiant)
            {
                nouvelEtudiant = e;
                break;
            }
        }
        if (nouvelEtudiant)
        {
            rendezVous.setEtudiant(nouvelEtudiant);
        }
        else
        {
            std::cout << "Étudiant introuvable. Modification ignorée.\n";
        }
    }

    std::cout << "Rendez-vous modifié avec succès !\n";
}

void RendezVous::supprimerRendezVous(std::vector<RendezVous> &rendezVousListe)
{
    if (rendezVousListe.empty())
    {
        std::cout << "Aucun rendez-vous à supprimer.\n";
        return;
    }

    // Afficher tous les rendez-vous avec leurs indices
    std::cout << "\n===== Liste des Rendez-vous =====\n";
    for (size_t i = 0; i < rendezVousListe.size(); ++i)
    {
        std::cout << "ID #" << i + 1 << ":\n";
        rendezVousListe[i].afficher();
        std::cout << "--------------------------------\n";
    }

    int index;
    std::cout << "Entrez l'ID du rendez-vous à supprimer : ";
    std::cin >> index;

    // Valider l'index
    if (index <= 0 || static_cast<size_t>(index) > rendezVousListe.size())
    {
        std::cout << "Rendez-vous introuvable !\n";
        return;
    }

    // Supprimer le rendez-vous
    rendezVousListe.erase(rendezVousListe.begin() + (index - 1));
    std::cout << "Rendez-vous supprimé avec succès !\n";
}
