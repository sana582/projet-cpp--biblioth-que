#include "Bibliotheque.h"
#include "Livre.h"
#include "Adherent.h"
#include "Exceptions.h"

#include <algorithm>
#include <iostream>

// Constructeur de la bibliothèque
Bibliotheque::Bibliotheque(const std::string& nom,
                           const std::string& adresse,
                           const std::string& code)
    : nom_(nom), adresse_(adresse), code_(code)
{
    // Vérifications de base
    if (nom_.empty()) throw InvalidArgumentException("nom bibliotheque vide");
    if (adresse_.empty()) throw InvalidArgumentException("adresse bibliotheque vide");
    if (code_.empty()) throw InvalidArgumentException("code bibliotheque vide");
}

//INFOS
const std::string& Bibliotheque::getNom() const { return nom_; }
const std::string& Bibliotheque::getAdresse() const { return adresse_; }
const std::string& Bibliotheque::getCode() const { return code_; }

//ADHERENTS
// Chercher un adhérent par son numéro
Adherent* Bibliotheque::trouverAdherent(const std::string& numAdh) const {
    for (Adherent* a : adherents_) {
        if (a && a->getNumeroAdherent() == numAdh) return a;
    }
    return nullptr;
}

// Inscrire un nouvel adhérent
void Bibliotheque::inscrire(Adherent* a) {
    if (a == nullptr) throw InvalidArgumentException("adherent null");

    // Si l’adhérent est déjà inscrit, on ne fait rien
    if (trouverAdherent(a->getNumeroAdherent()) != nullptr) return;

    adherents_.push_back(a);
    a->setBibliothequeInscription(this);
}

// Désinscrire un adhérent
bool Bibliotheque::desinscrire(const std::string& numAdh) {
    auto it = std::find_if(adherents_.begin(), adherents_.end(),
                           [&](Adherent* a){ return a && a->getNumeroAdherent() == numAdh; });

    if (it == adherents_.end()) return false;

    // On refuse si l’adhérent a encore des livres empruntés
    if ((*it)->getNbLivresEmpruntes() > 0) return false;

    (*it)->setBibliothequeInscription(nullptr);
    adherents_.erase(it);
    return true;
}

//LIVRES
// Chercher un livre par son code
Livre* Bibliotheque::trouverLivreParCode(const std::string& codeLivre) const {
    for (Livre* l : livres_) {
        if (l && l->getCode() == codeLivre) return l;
    }
    return nullptr;
}

// Chercher un livre par ISBN
Livre* Bibliotheque::trouverLivreParISBN(const std::string& isbn) const {
    for (Livre* l : livres_) {
        if (l && l->getISBN() == isbn) return l;
    }
    return nullptr;
}

// Ajouter un livre à la bibliothèque
void Bibliotheque::ajouterLivre(Livre* l) {
    if (l == nullptr) throw InvalidArgumentException("livre null");

    // Éviter d’ajouter deux livres avec le même code
    if (trouverLivreParCode(l->getCode()) != nullptr) return;

    livres_.push_back(l);
    l->setProprietaire(this);
}

// Acheter un livre (même chose que ajouter)
void Bibliotheque::acheterLivre(Livre* l) {
    ajouterLivre(l);
}

// Retirer un livre de la bibliothèque
bool Bibliotheque::retirerLivre(Livre* l) {
    if (l == nullptr) return false;

    auto it = std::find(livres_.begin(), livres_.end(), l);
    if (it == livres_.end()) return false;

    livres_.erase(it);
    return true;
}

//AFFICHAGE

// Afficher tous les livres
void Bibliotheque::afficherLivres(std::ostream& os) const {
    os << "=== Bibliotheque " << nom_ << " (" << code_ << ") ===\n";
    for (Livre* l : livres_) {
        if (l) os << " - " << *l << "\n";
    }
}

// Afficher les livres par catégorie
void Bibliotheque::afficherLivresParCategorie(std::ostream& os) const {
    os << "=== Livres par categorie (" << nom_ << ") ===\n";

    auto afficherCategorie = [&](TypeLivre cat) {
        os << "\n-- " << toString(cat) << " --\n";
        for (Livre* l : livres_) {
            if (l && l->getType() == cat) {
                os << " - " << *l << "\n";
            }
        }
    };

    afficherCategorie(TypeLivre::Roman);
    afficherCategorie(TypeLivre::BandeDessinee);
    afficherCategorie(TypeLivre::RecueilPoesie);
    afficherCategorie(TypeLivre::PieceTheatre);
    afficherCategorie(TypeLivre::Album);
}

//EMPRUNT / RETOUR

// Emprunter un livre
bool Bibliotheque::emprunterLivre(const std::string& numAdh, const std::string& codeLivre) {
    Adherent* a = trouverAdherent(numAdh);
    if (a == nullptr) return false;

    // L’adhérent doit appartenir à cette bibliothèque
    if (a->getBibliothequeInscription() != this) return false;

    Livre* l = trouverLivreParCode(codeLivre);
    if (l == nullptr) return false;

    // Vérifications simples
    if (l->getEtat() != EtatLivre::Libre) return false;
    if (a->aAtteintLimite()) return false;

    // Mise à jour des informations
    if (!a->ajouterEmprunt(l)) return false;
    l->setEtat(EtatLivre::Emprunte);
    l->setEmprunteur(a);

    return true;
}

// Rendre un livre
bool Bibliotheque::rendreLivre(const std::string& numAdh, const std::string& codeLivre) {
    Adherent* a = trouverAdherent(numAdh);
    if (a == nullptr) return false;

    Livre* l = trouverLivreParCode(codeLivre);
    if (l == nullptr) return false;

    // Le livre doit être emprunté par cet adhérent
    if (l->getEtat() != EtatLivre::Emprunte) return false;
    if (l->getEmprunteurActuel() != a) return false;

    if (!a->retirerEmprunt(l)) return false;

    l->setEmprunteur(nullptr);

    // Si le livre vient d’une autre bibliothèque
    if (l->getProprietaire() != this)
        l->setEtat(EtatLivre::Prete);
    else
        l->setEtat(EtatLivre::Libre);

    return true;
}

//PRET / DEMANDE ISBN

// Prêter un livre à une autre bibliothèque
bool Bibliotheque::preterLivreVers(Bibliotheque& dest, const std::string& codeLivre) {
    Livre* l = trouverLivreParCode(codeLivre);
    if (l == nullptr) return false;

    // On ne prête que les livres libres
    if (l->getEtat() != EtatLivre::Libre) return false;

    // Retirer le livre de cette bibliothèque
    if (!retirerLivre(l)) return false;

    // Ajouter le livre à l’autre bibliothèque
    dest.livres_.push_back(l);

    l->setEtat(EtatLivre::Prete);
    l->setEmprunteur(nullptr);
    return true;
}

// Demander un livre à une autre bibliothèque par ISBN
bool Bibliotheque::demanderLivreParISBN(Bibliotheque& source, const std::string& isbn) {
    Livre* l = source.trouverLivreParISBN(isbn);
    if (l == nullptr) return false;

    return source.preterLivreVers(*this, l->getCode());
}

//SUPPRESSION

// Supprimer un livre selon un motif
bool Bibliotheque::supprimerLivreParCode(const std::string& codeLivre, MotifSuppression motif) {
    Livre* l = trouverLivreParCode(codeLivre);
    if (l == nullptr) return false;

    // On ne supprime pas un livre emprunté
    if (l->getEtat() == EtatLivre::Emprunte) return false;

    // Le motif n’influence pas l’action ici
    (void)motif;
    return retirerLivre(l);
}

//RETOUR DES LIVRES PRETES

// Renvoyer les livres prêtés et non empruntés à leur propriétaire
int Bibliotheque::rendreLivresPretesNonEmpruntes() {
    int compteur = 0;

    for (auto it = livres_.begin(); it != livres_.end(); ) {
        Livre* l = *it;

        if (l && l->getEtat() == EtatLivre::Prete && l->getEmprunteurActuel() == nullptr) {
            Bibliotheque* proprio = l->getProprietaire();

            if (proprio && proprio != this) {
                it = livres_.erase(it);
                proprio->livres_.push_back(l);
                l->setEtat(EtatLivre::Libre);

                compteur++;
                continue;
            }
        }
        ++it;
    }

    return compteur;
}

//ACCES AUX LISTES

const std::list<Livre*>& Bibliotheque::getLivres() const { return livres_; }
const std::list<Adherent*>& Bibliotheque::getAdherents() const { return adherents_; }
