#include "Bibliotheque.h"
#include "Livre.h"
#include "Adherent.h"
#include "Exceptions.h"
#include <algorithm>//fnct find
#include <iostream>//cout,cin

// Constructeur de la bibliothèque
Bibliotheque::Bibliotheque(const std::string& nom,
                           const std::string& adresse,
                           const std::string& code)
    : nom_(nom), adresse_(adresse), code_(code)
{
    // Vérifications de base si ils sont vide ou non
    if (nom_.empty()) throw InvalidArgumentException("nom bibliotheque vide");
    if (adresse_.empty()) throw InvalidArgumentException("adresse bibliotheque vide");
    if (code_.empty()) throw InvalidArgumentException("code bibliotheque vide");
}

//geters
const std::string& Bibliotheque::getNom() const { return nom_; }
const std::string& Bibliotheque::getAdresse() const { return adresse_; }
const std::string& Bibliotheque::getCode() const { return code_; }

//ADHERENTS
// Chercher un adhérent par son numéro
Adherent* Bibliotheque::trouverAdherent(const std::string& numAdh) const {
    for (Adherent* a : adherents_) {
        if (a != nullptr) {          
            Adherent& adherent = *a;  // Transforme le pointeur en référence
            if (adherent.getNumeroAdherent() == numAdh) {
                return a;            
            }
        }
    }
    return nullptr; 
}


// Inscrire un nouvel adhérent
void Bibliotheque::inscrire(Adherent* a) {
    if (a == nullptr) 
        throw InvalidArgumentException("adherent null");

    Adherent& adherent = *a; // transforme le pointeur en référence

    // Si l’adhérent est déjà inscrit, on ne fait rien
    if (trouverAdherent(adherent.getNumeroAdherent()) != nullptr) 
        return;

    adherents_.push_back(a);

    // Associer l’adhérent à cette bibliothèque
    adherent.setBibliothequeInscription(this);
}


//LIVRES
// Chercher un livre par son code
Livre* Bibliotheque::trouverLivreParCode(const std::string& codeLivre) const {
    for (Livre* l : livres_) {
        if (l == nullptr) continue;      

        Livre& livre = *l;                // Transforme le pointeur en référence
        if (livre.getCode() == codeLivre) {
            return l;                     
        }
    }
    return nullptr;
}

// Chercher un livre par ISBN
Livre* Bibliotheque::trouverLivreParISBN(const std::string& isbn) const {
    for (Livre* l : livres_) {
        if (l == nullptr) continue;        

        Livre& livre = *l;                 // Transforme le pointeur en référence
        if (livre.getISBN() == isbn) {
            return l;                     
        }
    }
    return nullptr;
}


// Acheter un livre
void Bibliotheque::acheterLivre(Livre* l) {
    if (l == nullptr) 
        throw InvalidArgumentException("livre null");

    Livre& livre = *l;  // Transforme le pointeur en référence 

    // Éviter d’ajouter deux livres avec le même code
    if (trouverLivreParCode(livre.getCode()) != nullptr) 
        return;

    livres_.push_back(l);          // Ajoute le pointeur à la liste
    livre.setProprietaire(this);   // Met à jour la propriété de la bibliothèque
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

    // Liste des catégories à afficher
    TypeLivre categories[] = {
        TypeLivre::Roman,
        TypeLivre::BandeDessinee,
        TypeLivre::RecueilPoesie,
        TypeLivre::PieceTheatre,
        TypeLivre::Album
    };

    // Parcours chaque catégorie
    for (TypeLivre cat : categories) {
        os << "\n-- " << toString(cat) << " --\n";

        // Parcours tous les livres
        for (Livre* l : livres_) {
            if (l == nullptr) continue;       
            Livre& livre = *l;                
            if (livre.getType() == cat) {
                os << " - " << livre << "\n";
            }
        }
    }
}


//EMPRUNT / RETOUR

// Emprunter un livre
bool Bibliotheque::emprunterLivre(const std::string& numAdh, const std::string& codeLivre) {
    Adherent* x = trouverAdherent(numAdh);
    if (x == nullptr) return false;

    Adherent& a = *x; 

    // L’adhérent doit appartenir à cette bibliothèque
    if (a.getBibliothequeInscription() != this) return false;

    Livre* y= trouverLivreParCode(codeLivre);
    if (y == nullptr) return false;

    Livre& l = *y; 

    // Vérifications simples
    if (l.getEtat() != EtatLivre::Libre) return false;
    if (a.aAtteintLimite()) return false;

    // Mise à jour des informations
    if (!a.ajouterEmprunt(&l)) return false; 
    l.setEtat(EtatLivre::Emprunte);
    l.setEmprunteur(&a);

    return true;
}

// Rendre un livre
bool Bibliotheque::rendreLivre(const std::string& numAdh, const std::string& codeLivre) {
    Adherent* aPtr = trouverAdherent(numAdh);
    if (aPtr == nullptr) return false;

    Adherent& a = *aPtr; 

    Livre* lPtr = trouverLivreParCode(codeLivre);
    if (lPtr == nullptr) return false;

    Livre& l = *lPtr; 

    // Le livre doit être emprunté par cet adhérent
    if (l.getEtat() != EtatLivre::Emprunte) return false;
    if (l.getEmprunteurActuel() != aPtr) return false;

    if (!a.retirerEmprunt(lPtr)) return false;

    l.setEmprunteur(nullptr);

    // Si le livre vient d’une autre bibliothèque
    if (l.getProprietaire() != this)
        l.setEtat(EtatLivre::Prete);
    else
        l.setEtat(EtatLivre::Libre);

    return true;
}


//PRET / DEMANDE ISBN

// Prêter un livre à une autre bibliothèque
bool Bibliotheque::preterLivreVers(Bibliotheque& dest, const std::string& codeLivre) {
    Livre* lPtr = trouverLivreParCode(codeLivre);
    if (lPtr == nullptr) return false;

    Livre& l = *lPtr; 

    // On ne prête que les livres libres
    if (l.getEtat() != EtatLivre::Libre) return false;

    // Retirer le livre de cette bibliothèque
    if (!retirerLivre(lPtr)) return false;

    // Ajouter le livre à l’autre bibliothèque
    dest.livres_.push_back(lPtr);

    // Mettre à jour l’état et l’emprunteur
    l.setEtat(EtatLivre::Prete);
    l.setEmprunteur(nullptr);

    return true;
}


// Demander un livre à une autre bibliothèque par ISBN
bool Bibliotheque::demanderLivreParISBN(Bibliotheque& source, const std::string& isbn) {
    Livre* lPtr = source.trouverLivreParISBN(isbn);
    if (lPtr == nullptr) return false;

    Livre& l = *lPtr; 

    // Demande le livre à la bibliothèque source
    return source.preterLivreVers(*this, l.getCode());
}


//SUPPRESSION

// Supprimer un livre selon un motif
bool Bibliotheque::supprimerLivreParCode(const std::string& codeLivre, MotifSuppression motif) {
    Livre* lPtr = trouverLivreParCode(codeLivre);
    if (lPtr == nullptr) return false;

    Livre& l = *lPtr; 

    // On ne supprime pas un livre emprunté
    if (l.getEtat() == EtatLivre::Emprunte) return false;

    (void)motif;   // Le motif n’influence pas l’action 

    // Retire le livre de la bibliothèque
    return retirerLivre(lPtr);
}


//RETOUR DES LIVRES PRETES

// Renvoyer les livres prêtés et non empruntés à leur propriétaire
int Bibliotheque::rendreLivresPretesNonEmpruntes() {
    int compteur = 0;

    for (auto it = livres_.begin(); it != livres_.end(); ) {
        Livre* lPtr = *it;
        if (lPtr == nullptr) {
            ++it;
            continue; 
        }

        Livre& l = *lPtr; 

        // Vérifie si le livre est prêté et non emprunté
        if (l.getEtat() == EtatLivre::Prete && l.getEmprunteurActuel() == nullptr) {
            Bibliotheque* proprioPtr = l.getProprietaire();
            
            // Si le livre appartient à une autre bibliothèque
            if (proprioPtr != nullptr && proprioPtr != this) {
                it = livres_.erase(it);          // Retire le livre de cette bibliothèque
                proprioPtr->livres_.push_back(lPtr); // Ajoute à la bibliothèque propriétaire
                l.setEtat(EtatLivre::Libre);     // Met à jour l'état du livre
                compteur++;
                continue;                        // Passe au livre suivant
            }
        }

        ++it; // Livre non déplacé, passe au suivant
    }

    return compteur;
}


//ACCES AUX LISTES

const std::list<Livre*>& Bibliotheque::getLivres() const { return livres_; }
const std::list<Adherent*>& Bibliotheque::getAdherents() const { return adherents_; }