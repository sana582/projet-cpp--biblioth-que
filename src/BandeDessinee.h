
#ifndef BANDEDESSINEE_H
#define BANDEDESSINEE_H

#include "Livre.h"
#include <string>
#include <ostream>

class BandeDessinee : public Livre {
private:
    std::string dessinateur_;

public:
    // Constructeur
    BandeDessinee(const std::string& code,
                  const std::string& auteur,
                  const std::string& titre,
                  const std::string& editeur,
                  const std::string& isbn,
                  PublicCible publicCible,
                  const std::string& dessinateur);

    // Destructeur
    ~BandeDessinee() override = default;

    // Retourne le nom du dessinateur
    const std::string& getDessinateur() const;

    // Affiche les informations de la bande dessinée
    void afficher(std::ostream& os) const override;

    // Retourne le type du livre 
    TypeLivre getType() const override { return TypeLivre::BandeDessinee; }

};

#endif
