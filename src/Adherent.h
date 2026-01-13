#ifndef ADHERENT_H
#define ADHERENT_H

#include <string>
#include <list>

class Livre;
class Bibliotheque;
//Représente un adhérent inscrit dans une bibliothèque.
//Un adhérent a :
//un nom, prénom, adresse, numéro d'adhérent
//un nombre maximum de livres qu'il peut emprunter
//une liste de livres actuellement empruntés
//une bibliothèque où il est inscrit
 
class Adherent {
private:
    std::string nom_;
    std::string prenom_;
    std::string adresse_;
    std::string numeroAdherent_;
    int nbLivresAutorise_;

    std::list<Livre*> livresEmpruntes_;
    Bibliotheque* bibliothequeInscription_;

public:
    Adherent(const std::string& nom,
             const std::string& prenom,
             const std::string& adresse,
             const std::string& numeroAdherent,
             int nbLivresAutorise);

    // Infos de l’adhérent
    const std::string& getNom() const;
    const std::string& getPrenom() const;
    const std::string& getAdresse() const;
    const std::string& getNumeroAdherent() const;
    int getNbLivresAutorise() const;
    int getNbLivresEmpruntes() const;

    // Bibliothèque
    Bibliotheque* getBibliothequeInscription() const;
    void setBibliothequeInscription(Bibliotheque* b);

    // Emprunts
    bool aAtteintLimite() const;
    bool ajouterEmprunt(Livre* l);
    bool retirerEmprunt(Livre* l);
    bool aEmprunte(Livre* l) const;
    const std::list<Livre*>& getLivresEmpruntes() const;
};

#endif
