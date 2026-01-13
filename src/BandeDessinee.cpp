#include "BandeDessinee.h"
#include "Exceptions.h"
#include "Enums.h"


// Constructeur
BandeDessinee::BandeDessinee(const std::string& code,
                             const std::string& auteur,
                             const std::string& titre,
                             const std::string& editeur,
                             const std::string& isbn,
                             PublicCible publicCible,
                             const std::string& dessinateur)
    : Livre(code, auteur, titre, editeur, isbn, publicCible),
      dessinateur_(dessinateur)
{
    // On vérifie que le nom du dessinateur n'est pas vide
    if (dessinateur_.empty()) throw InvalidArgumentException("dessinateur vide");
}

// Retourne le nom du dessinateur
const std::string& BandeDessinee::getDessinateur() const {
    return dessinateur_;
}

// Affiche toutes les informations de la bande dessinée
void BandeDessinee::afficher(std::ostream& os) const {
    os << "[BD] "
       << "code=" << code_
       << ", titre=\"" << titre_ << "\""
       << ", auteur=" << auteur_
       << ", dessinateur=" << dessinateur_
       << ", isbn=" << isbn_
       << ", public=" << toString(publicCible_)
       << ", etat=" << toString(etat_);
}
