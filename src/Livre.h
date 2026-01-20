#ifndef LIVRE_H
#define LIVRE_H
#include <string>
#include <ostream>
#include "Enums.h"

class Bibliotheque;
class Adherent;

// Classe abstraite représentant un livre
class Livre {
protected:
    // Informations du livre
    std::string code_;
    std::string auteur_;
    std::string titre_;
    std::string editeur_;
    std::string isbn_;
    PublicCible publicCible_;
    EtatLivre etat_;

    Bibliotheque* proprietaire_;
    Adherent* emprunteurActuel_;

public:
    // Constructeur
    Livre(const std::string& code,
          const std::string& auteur,
          const std::string& titre,
          const std::string& editeur,
          const std::string& isbn,
          PublicCible publicCible);

    virtual ~Livre() = default;

    // Getters
    const std::string& getCode() const;
    const std::string& getAuteur() const;
    const std::string& getTitre() const;
    const std::string& getEditeur() const;
    const std::string& getISBN() const;
    PublicCible getPublicCible() const;
    EtatLivre getEtat() const;

    // Retourne le type du livre
    virtual TypeLivre getType() const = 0;

    // Indique si le livre est libre
    bool estLibre() const;

    Bibliotheque* getProprietaire() const;
    Adherent* getEmprunteurActuel() const;

    void setProprietaire(Bibliotheque* b);
    void setEmprunteur(Adherent* a);
    void setEtat(EtatLivre e);
   
    // Affichage du livre
    // Chaque classe dérivée,doit définir sa propre façon d’afficher ses informations.
    virtual void afficher(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Livre& l);
};

#endif
