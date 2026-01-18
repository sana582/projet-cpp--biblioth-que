#include "Album.h"
#include "Enums.h"

// Convertit le type d'illustration en texte lisible
static std::string toString(TypeIllustration t) {
    switch (t) {
        case TypeIllustration::Photos: return "Photos";
        case TypeIllustration::Dessins: return "Dessins";
        case TypeIllustration::PhotosEtDessins: return "Photos et dessins";
    }
    return "Inconnu";
}

// Constructeur d'Album
Album::Album(const std::string& code,
             const std::string& auteur,
             const std::string& titre,
             const std::string& editeur,
             const std::string& isbn,
             PublicCible publicCible,
             TypeIllustration illustrations)
    : Livre(code, auteur, titre, editeur, isbn, publicCible), // Appel du constructeur de Livre
      illustrations_(illustrations) // Initialise le type d'illustration
{}

// Retourne le type d'illustration
TypeIllustration Album::getIllustrations() const {
    return illustrations_;
}

// Affiche les infos de l'album
void Album::afficher(std::ostream& os) const {
    os << "[Album] "
       << "code=" << code_
       << ", titre=\"" << titre_ << "\""
       << ", auteur=" << auteur_
       << ", isbn=" << isbn_
       << ", public=" << toString(publicCible_)
       << ", etat=" << toString(etat_)
       << ", illustrations=" << toString(illustrations_);
}
