#include "RecueilPoesie.h"
#include "Enums.h"


// Constructeur
RecueilPoesie::RecueilPoesie(const std::string& code,
                             const std::string& auteur,
                             const std::string& titre,
                             const std::string& editeur,
                             const std::string& isbn,
                             PublicCible publicCible,
                             TypePoesie type)
    : Livre(code, auteur, titre, editeur, isbn, publicCible),
      type_(type)
{}


// Retourne le type de poésie du recueil
TypePoesie RecueilPoesie::getTypePoesie() const {
    return type_;
}

// Affiche toutes les informations du recueil de poésie
void RecueilPoesie::afficher(std::ostream& os) const {
    os << "[Poesie] "
       << "code=" << code_
       << ", titre=\"" << titre_ << "\""
       << ", auteur=" << auteur_
       << ", isbn=" << isbn_
       << ", public=" << toString(publicCible_)
       << ", etat=" << toString(etat_)
       << ", type=" << toString(type_);
}
