#include "Roman.h"

// Fonction utilitaire qui transforme un genre de roman en texte lisible
static std::string toString(GenreRoman g) {
    switch (g) {
        case GenreRoman::Litterature: return "Litterature";
        case GenreRoman::RomanNoir: return "Roman noir";
        case GenreRoman::RomanPolicier: return "Roman policier";
        case GenreRoman::RomanAnimalier: return "Roman animalier";
        case GenreRoman::RomanAmour: return "Roman d'amour";
        case GenreRoman::RomanMoeurs: return "Roman de moeurs";
        case GenreRoman::RomanGothique: return "Roman gothique";
        case GenreRoman::RomanCourtois: return "Roman courtois";
        case GenreRoman::RomanEpistolaire: return "Roman epistolaire";
        case GenreRoman::RomanFeuilleton: return "Roman-feuilleton";
        case GenreRoman::RomanGraphique: return "Roman graphique";
        case GenreRoman::RomanHistorique: return "Roman historique";
        case GenreRoman::RomanPhoto: return "Roman-photo";
        case GenreRoman::RomanPicaresque: return "Roman picaresque";
        case GenreRoman::RomanMemoires: return "Roman-memoires";
        case GenreRoman::RomanPopulaire: return "Roman populaire";
        case GenreRoman::RomanAventures: return "Roman d'aventures";
        case GenreRoman::RomanAnticipation: return "Roman d'anticipation";
        case GenreRoman::RomanEspionnage: return "Roman d'espionnage";
        case GenreRoman::RomanApprentissage: return "Roman d'apprentissage";
        case GenreRoman::RomanChevalerie: return "Roman de chevalerie";
        case GenreRoman::RomanAutobiographique: return "Roman autobiographique";
        case GenreRoman::NouveauRoman: return "Nouveau roman";
        case GenreRoman::RomanChevaleresque: return "Roman chevaleresque";
        case GenreRoman::Conte: return "Conte";
        case GenreRoman::Nouvelle: return "Nouvelle";
    }

    // Cas de sécurité si jamais on tombe sur une valeur inconnue
    return "Inconnu";
}

// Retourne le genre du roman
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
