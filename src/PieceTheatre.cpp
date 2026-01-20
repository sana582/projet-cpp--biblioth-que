#include "PieceTheatre.h"
#include "Exceptions.h"
#include "Enums.h"
// Constructeur de PieceTheatre
PieceTheatre::PieceTheatre(const std::string& code,
                           const std::string& auteur,
                           const std::string& titre,
                           const std::string& editeur,
                           const std::string& isbn,
                           PublicCible publicCible,
                           int siecle)
    : Livre(code, auteur, titre, editeur, isbn, publicCible), 
      siecle_(siecle)
{
    // Vérifie que le siècle est valide (> 0), sinon lance une exception
    if (siecle_ <= 0) throw InvalidArgumentException("siecle invalide");
}

// Getter pour récupérer le siècle de la pièce
int PieceTheatre::getSiecle() const {
    return siecle_;
}

//afficher les informations de la pièce 
void PieceTheatre::afficher(std::ostream& os) const {
    os << "[Theatre] "
       << "code=" << code_           
       << ", titre=\"" << titre_ << "\"" 
       << ", auteur=" << auteur_      
       << ", isbn=" << isbn_          
       << ", public=" << toString(publicCible_) 
       << ", etat=" << toString(etat_)      
       << ", siecle=" << siecle_ << "e";   
}