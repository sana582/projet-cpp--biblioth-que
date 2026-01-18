#ifndef ENUMS_H
#define ENUMS_H

#include <string>

//Public cible et état
enum class PublicCible { Adulte, Ados, Jeunesse, ToutPublic };
enum class EtatLivre   { Libre, Emprunte, Prete };

//Poesie et Illustration
enum class TypePoesie { Vers, Prose, VersEtProse };
enum class TypeIllustration { Photos, Dessins, PhotosEtDessins };

//Motif suppression
enum class MotifSuppression { Perdu, Pilon };

//Types de livres
enum class TypeLivre {
    Roman,
    BandeDessinee,
    RecueilPoesie,
    PieceTheatre,
    Album
};

//Genre Roman
enum class GenreRoman {
    Litterature,
    RomanNoir,
    RomanPolicier,
    RomanAnimalier,
    RomanAmour,
    RomanMoeurs,
    RomanGothique,
    RomanCourtois,
    RomanEpistolaire,
    RomanFeuilleton,
    RomanGraphique,
    RomanHistorique,
    RomanPhoto,
    RomanPicaresque,
    RomanMemoires,
    RomanPopulaire,
    RomanAventures,
    RomanAnticipation,
    RomanEspionnage,
    RomanApprentissage,
    RomanChevalerie,
    RomanAutobiographique,
    NouveauRoman,
    RomanChevaleresque,
    Conte,
    Nouvelle
};
// Convertit le public cible en texte lisible
inline std::string toString(PublicCible p) {
    switch (p) {
        case PublicCible::Adulte: return "Adulte";
        case PublicCible::Ados: return "Ados";
        case PublicCible::Jeunesse: return "Jeunesse";
        case PublicCible::ToutPublic: return "Tout public";
    }
    // Cas de sécurité (ne devrait pas arriver)
    return "Inconnu";
}

// Convertit l’état d’un livre en texte
inline std::string toString(EtatLivre e) {
    switch (e) {
        case EtatLivre::Libre: return "Libre";
        case EtatLivre::Emprunte: return "Emprunte";
        case EtatLivre::Prete: return "Prete";
    }
    return "Inconnu";
}

// Convertit le type de livre en texte
inline std::string toString(TypeLivre t) {
    switch (t) {
        case TypeLivre::Roman: return "Roman";
        case TypeLivre::BandeDessinee: return "Bande dessinee";
        case TypeLivre::RecueilPoesie: return "Recueil de poesie";
        case TypeLivre::PieceTheatre: return "Piece de theatre";
        case TypeLivre::Album: return "Album";
    }
    return "Inconnu";
}

// Convertit le type de poésie en texte
inline std::string toString(TypePoesie t) {
    switch (t) {
        case TypePoesie::Vers: return "Vers";
        case TypePoesie::Prose: return "Prose";
        case TypePoesie::VersEtProse: return "Vers et prose";
    }
    return "Inconnu";
}

#endif