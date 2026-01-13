#ifndef ROMAN_H
#define ROMAN_H

#include "Livre.h"
#include "Enums.h"
#include <string>
#include <ostream>

/**
 * @brief Roman = Livre avec un genre.
 */
class Roman : public Livre {
private:
    GenreRoman genre_;

public:
    // Constructeur 
    Roman(const std::string& code,
          const std::string& auteur,
          const std::string& titre,
          const std::string& editeur,
          const std::string& isbn,
          PublicCible publicCible,
          GenreRoman genre);

    // Destructeur
    ~Roman() override = default;

    // Retourne le genre du roman
    GenreRoman getGenre() const;

    // Affiche les informations du roman 
    void afficher(std::ostream& os) const override;

    // Retourne le type du livre 
    TypeLivre getType() const override { return TypeLivre::Roman; }

};

#endif
