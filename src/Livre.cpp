#include "Livre.h"
#include "Exceptions.h"

// Constructeur
Livre::Livre(const std::string& code,
             const std::string& auteur,
             const std::string& titre,
             const std::string& editeur,
             const std::string& isbn,
             PublicCible publicCible)
    : code_(code),
      auteur_(auteur),
      titre_(titre),
      editeur_(editeur),
      isbn_(isbn),
      publicCible_(publicCible),
      etat_(EtatLivre::Libre),
      proprietaire_(nullptr),
      emprunteurActuel_(nullptr)
{
    // Vérification que les champs obligatoires sont remplis
    if (code_.empty())  throw InvalidArgumentException("code vide");
    if (isbn_.empty())  throw InvalidArgumentException("ISBN vide");
    if (titre_.empty()) throw InvalidArgumentException("titre vide");
}

// Getters
const std::string& Livre::getCode() const { return code_; }
const std::string& Livre::getAuteur() const { return auteur_; }
const std::string& Livre::getTitre() const { return titre_; }
const std::string& Livre::getEditeur() const { return editeur_; }
const std::string& Livre::getISBN() const { return isbn_; }
PublicCible Livre::getPublicCible() const { return publicCible_; }
EtatLivre Livre::getEtat() const { return etat_; }

// Indique si le livre est disponible
bool Livre::estLibre() const {
    return etat_ == EtatLivre::Libre;
}

// Retourne la bibliothèque propriétaire du livre
Bibliotheque* Livre::getProprietaire() const { return proprietaire_; }

// Retourne l'adhérent qui a emprunté le livre
Adherent* Livre::getEmprunteurActuel() const { return emprunteurActuel_; }

// Définit la bibliothèque propriétaire du livre
void Livre::setProprietaire(Bibliotheque* b) {
    proprietaire_ = b;
}

// Définit l'adhérent qui emprunte le livre
void Livre::setEmprunteur(Adherent* a) {
    emprunteurActuel_ = a;
}

// Change l'état du livre
void Livre::setEtat(EtatLivre e) {
    etat_ = e;
}

//l'opérateur << pour afficher un livre
std::ostream& operator<<(std::ostream& os, const Livre& l) {
    l.afficher(os);
    return os;
}
