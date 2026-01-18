#ifndef ALBUM_H
#define ALBUM_H

#include "Livre.h"    
#include "Enums.h"     
#include <ostream>     

// Classe Album dérivée de Livre
class Album : public Livre {
private:
    TypeIllustration illustrations_;  // Type d'illustrations de l'album

public:
    // Constructeur avec initialisation de tous les attributs
    Album(const std::string& code,
          const std::string& auteur,
          const std::string& titre,
          const std::string& editeur,
          const std::string& isbn,
          PublicCible publicCible,
          TypeIllustration illustrations);

    ~Album() override = default;  // Destructeur par défaut

    TypeIllustration getIllustrations() const;  // Getter pour le type d'illustration

    void afficher(std::ostream& os) const override;  // Affiche les informations de l'album

    TypeLivre getType() const override { return TypeLivre::Album; }  
    // Retourne le type de livre 
};

#endif 