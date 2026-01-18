```mermaid
classDiagram
direction LR

class Bibliotheque {
  - nom : string
  - adresse : string
  - code : string
  - livres : List~Livre*~
  - adherents : List~Adherent*~
  + inscrire(a:Adherent*) void
  + desinscrire(numAdh:string) bool

  + afficherLivres(os:ostream) void
  + afficherLivresParCategorie(os:ostream) void

  + acheterLivre(l:Livre*) void
  + ajouterLivre(l:Livre*) void
  + trouverLivreParCode(code:string) Livre*
  + trouverLivreParISBN(isbn:string) Livre*

  + emprunterLivre(numAdh:string, codeLivre:string) bool
  + rendreLivre(numAdh:string, codeLivre:string) bool

  + preterLivreVers(dest:Bibliotheque&, codeLivre:string) bool
  + demanderLivreParISBN(source:Bibliotheque&, isbn:string) bool

  + supprimerLivreParCode(codeLivre:string, motif:MotifSuppression) bool
  + rendreLivresPretesNonEmpruntes() int
}

class Adherent {
  - nom : string
  - prenom : string
  - adresse : string
  - numeroAdherent : string
  - nbLivresAutorise : int
  - livresEmpruntes : List~Livre*~
  - bibliothequeInscription : Bibliotheque*
  + getNumero() string
  + getNbAutorise() int
  + setBibliotheque(b:Bibliotheque*) void
  + aAtteintLimite() bool
}

class Livre {
  <<abstract>>
  # code : string
  # auteur : string
  # titre : string
  # editeur : string
  # isbn : string
  # publicCible : PublicCible
  # etat : EtatLivre
  # proprietaire : Bibliotheque*
  # emprunteurActuel : Adherent*

  + Livre(code,auteur,titre,editeur,isbn,publicCible)
  + ~Livre()
  + getCode() string
  + getISBN() string
  + getEtat() EtatLivre
  + estLibre() bool
  + setProprietaire(b:Bibliotheque*) void
  + setEmprunteur(a:Adherent*) void
  + setEtat(e:EtatLivre) void
  + afficher(os:ostream) void
}

class BandeDessinee {
  - dessinateur : string
  + afficher(os:ostream) void
}
class RecueilPoesie {
  - type : TypePoesie
  + afficher(os:ostream) void
}
class Roman {
  - genre : GenreRoman
  + afficher(os:ostream) void
}
class PieceTheatre {
  - siecle : int
  + afficher(os:ostream) void
}
class Album {
  - illustrations : TypeIllustration
  + afficher(os:ostream) void
}

class PublicCible {
  <<enumeration>>
  Adulte
  Ados
  Jeunesse
  ToutPublic
}
class EtatLivre {
  <<enumeration>>
  Libre
  Emprunte
  Prete
}
class TypePoesie {
  <<enumeration>>
  Vers
  Prose
  VersEtProse
}
class TypeIllustration {
  <<enumeration>>
  Photos
  Dessins
  PhotosEtDessins
}
class MotifSuppression {
  <<enumeration>>
  Perdu
  Pilon
}
class GenreRoman {
  <<enumeration>>
  Litterature
  RomanNoir
  RomanPolicier
  RomanAnimalier
  RomanAmour
  RomanMoeurs
  RomanGothique
  RomanCourtois
  RomanEpistolaire
  RomanFeuilleton
  RomanGraphique
  RomanHistorique
  RomanPhoto
  RomanPicaresque
  RomanMemoires
  RomanPopulaire
  RomanAventures
  RomanAnticipation
  RomanEspionnage
  RomanApprentissage
  RomanChevalerie
  RomanAutobiographique
  NouveauRoman
  RomanChevaleresque
  Conte
  Nouvelle
  Autre
}

%% Relations
Bibliotheque "1" -- "0..*" Livre : contient
Adherent "0..*" -- "1" Bibliotheque : inscrit

Livre "0..*" -- "0..1" Adherent : emprunt


%% Heritage
Livre <|-- BandeDessinee
Livre <|-- RecueilPoesie
Livre <|-- Roman
Livre <|-- PieceTheatre
Livre <|-- Album

 ```
