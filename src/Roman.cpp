#include "Roman.h"
#include "Enums.h"
//constructeur
Roman::Roman(const std::string& code,
             const std::string& auteur,
             const std::string& titre,
             const std::string& editeur,
             const std::string& isbn,
             PublicCible publicCible,
             GenreRoman genre)
    : Livre(code, auteur, titre, editeur, isbn, publicCible),
      genre_(genre)
{}

GenreRoman Roman::getGenre() const {
    return genre_;
}

// Affiche toutes les informations du roman
void Roman::afficher(std::ostream& os) const {
    os << "[Roman] "
       << "code=" << code_
       << ", titre=\"" << titre_ << "\""
       << ", auteur=" << auteur_
       << ", editeur=" << editeur_
       << ", isbn=" << isbn_
       << ", public=" << toString(publicCible_)
       << ", etat=" << toString(etat_)
       << ", genre=" << toString(genre_);
}
