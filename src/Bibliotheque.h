#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <string>
#include <list>
#include <ostream>
#include "Enums.h"

class Livre;
class Adherent;

//Représente une bibliothèque :nom, adresse, code, ses livres,ses adhérents.
//Gère les opérations métier : emprunter,rendre, prêter, demander par ISBN...

class Bibliotheque {
private:
    std::string nom_;
    std::string adresse_;
    std::string code_;

    std::list<Livre*> livres_;
    std::list<Adherent*> adherents_;

public:
    Bibliotheque(const std::string& nom,
                 const std::string& adresse,
                 const std::string& code);

    // Infos
    const std::string& getNom() const;
    const std::string& getAdresse() const;
    const std::string& getCode() const;

    // Adhérents
    void inscrire(Adherent* a);
    bool desinscrire(const std::string& numAdh);
    Adherent* trouverAdherent(const std::string& numAdh) const;

    // Livres
    void ajouterLivre(Livre* l);
    void acheterLivre(Livre* l); 
    bool retirerLivre(Livre* l);

    Livre* trouverLivreParCode(const std::string& codeLivre) const;
    Livre* trouverLivreParISBN(const std::string& isbn) const;

    // Affichages
    void afficherLivres(std::ostream& os) const;
    void afficherLivresParCategorie(std::ostream& os) const;

    // Emprunt / retour par code
    bool emprunterLivre(const std::string& numAdh, const std::string& codeLivre);
    bool rendreLivre(const std::string& numAdh, const std::string& codeLivre);

    // Prêt interbibliothèque / demande ISBN
    bool preterLivreVers(Bibliotheque& dest, const std::string& codeLivre);
    bool demanderLivreParISBN(Bibliotheque& source, const std::string& isbn);

    // Suppression
    bool supprimerLivreParCode(const std::string& codeLivre, MotifSuppression motif);

    // Rendre les livres prêtés qui ne sont pas empruntés
    int rendreLivresPretesNonEmpruntes();

    // Accès listes 
    const std::list<Livre*>& getLivres() const;
    const std::list<Adherent*>& getAdherents() const;
};

#endif
