#include "Adherent.h"
#include "Exceptions.h"
#include <algorithm>

// Constructeur : crée un adhérent avec ses infos
Adherent::Adherent(const std::string& nom,
                   const std::string& prenom,
                   const std::string& adresse,
                   const std::string& numeroAdherent,
                   int nbLivresAutorise)
    : nom_(nom),
      prenom_(prenom),
      adresse_(adresse),
      numeroAdherent_(numeroAdherent),
      nbLivresAutorise_(nbLivresAutorise),
      bibliothequeInscription_(nullptr)
{
    // Vérifie que les infos ne sont pas vides ou invalides
    if (nom_.empty()) throw InvalidArgumentException("nom vide");
    if (prenom_.empty()) throw InvalidArgumentException("prenom vide");
    if (adresse_.empty()) throw InvalidArgumentException("adresse vide");
    if (numeroAdherent_.empty()) throw InvalidArgumentException("numero adherent vide");
    if (nbLivresAutorise_ < 0) throw InvalidArgumentException("nbLivresAutorise negatif");
}

//GETTERS
const std::string& Adherent::getNom() const { return nom_; }
const std::string& Adherent::getPrenom() const { return prenom_; }
const std::string& Adherent::getAdresse() const { return adresse_; }
const std::string& Adherent::getNumeroAdherent() const { return numeroAdherent_; }

int Adherent::getNbLivresAutorise() const { return nbLivresAutorise_; }
int Adherent::getNbLivresEmpruntes() const { return static_cast<int>(livresEmpruntes_.size()); }

//Bibliothèque
Bibliotheque* Adherent::getBibliothequeInscription() const { return bibliothequeInscription_; }
void Adherent::setBibliothequeInscription(Bibliotheque* b) { bibliothequeInscription_ = b; }

//limite
bool Adherent::aAtteintLimite() const {
    return getNbLivresEmpruntes() >= nbLivresAutorise_;
}

//Gestion des emprunts
bool Adherent::aEmprunte(Livre* l) const {
    return std::find(livresEmpruntes_.begin(), livresEmpruntes_.end(), l) != livresEmpruntes_.end();
}

bool Adherent::ajouterEmprunt(Livre* l) {
    if (l == nullptr) return false;       // pas de livre
    if (aAtteintLimite()) return false;   // limite atteinte
    if (aEmprunte(l)) return false;       // déjà emprunté
    livresEmpruntes_.push_back(l);        // ajoute le livre a la fin de la liste
    return true;
}

bool Adherent::retirerEmprunt(Livre* l) {
    if (l == nullptr) return false;

    auto it = std::find(livresEmpruntes_.begin(), livresEmpruntes_.end(), l); //std::list<livre*>::iterator = auto 
    if (it == livresEmpruntes_.end()) return false; // livre pas trouvé
    livresEmpruntes_.erase(it);           // supprime le livre
    return true;
}

// Retourne la liste des livres empruntés
const std::list<Livre*>& Adherent::getLivresEmpruntes() const {
    return livresEmpruntes_;
}
