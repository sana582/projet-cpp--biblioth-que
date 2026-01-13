#ifndef PIECETHEATRE_H
#define PIECETHEATRE_H

#include "Livre.h"
#include <ostream>
class PieceTheatre : public Livre { 
private:
    int siecle_;  

public:
    // Constructeur avec initialisation de tous les attributs
    PieceTheatre(const std::string& code,
                 const std::string& auteur,
                 const std::string& titre,
                 const std::string& editeur,
                 const std::string& isbn,
                 PublicCible publicCible,
                 int siecle);

    ~PieceTheatre() override = default;  // Destructeur par défaut

    int getSiecle() const;  // Getter pour le siècle

    void afficher(std::ostream& os) const override;  // Affiche les informations de la pièce

    TypeLivre getType() const override { return TypeLivre::PieceTheatre; }  
    // Retourne le type de livre

};

#endif  