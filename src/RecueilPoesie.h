#ifndef RECUEILPOESIE_H
#define RECUEILPOESIE_H

#include "Livre.h"

#include <ostream>

class RecueilPoesie : public Livre {
private:
    TypePoesie type_;

public:
    // Constructeur 
    RecueilPoesie(const std::string& code,
                  const std::string& auteur,
                  const std::string& titre,
                  const std::string& editeur,
                  const std::string& isbn,
                  PublicCible publicCible,
                  TypePoesie type);


    // Destructeur
    ~RecueilPoesie() override = default;


    // Affiche les informations du recueil de poésie
    void afficher(std::ostream& os) const override;

    // Retourne le type du livre
    TypeLivre getType() const override { return TypeLivre::RecueilPoesie; }

    // Retourne le type de poésie du recueil
    TypePoesie getTypePoesie() const;

};

#endif
