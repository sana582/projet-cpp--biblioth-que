#include <iostream>
#include "src/Bibliotheque.h"
#include "src/Adherent.h"
#include "src/Roman.h"
#include "src/BandeDessinee.h"
#include "src/RecueilPoesie.h"
#include "src/PieceTheatre.h"
#include "src/Album.h"
#include "src/Enums.h"

int main() {
    std::cout << "DEMO Gestion de bibliotheques\n";

    // 1) On crée deux bibliothèques 
    Bibliotheque b1("Biblio Centrale", "Marseille", "B001");
    Bibliotheque b2("Biblio Nord", "Aix-en-Provence", "B002");

    // 2) On crée deux adhérents
    Adherent a1("Naimi", "Salima", "Marseille", "A001", 2);
    Adherent a2("Riahi", "Sana", "Aix-en-Provence", "A002", 1);

    std::cout << "\n\n - INSCRIPTION : \n";

    // On inscrit A001 dans b1
    b1.inscrire(&a1);

    // On inscrit A002 dans b2
    b2.inscrire(&a2);

    // On essaye de réinscrire A001 dans b1
    std::cout << "On essaye de re-inscrire A001 dans b1\n";
    b1.inscrire(&a1);

    // On essaye d'inscrire A001 dans b2 alors qu'il est déjà dans b1 :  refus
    std::cout << "On essaye d'inscrire A001 dans b2 alors qu'il est deja dans b1\n";
    b2.inscrire(&a1);

    std::cout << "\n\n - AJOUT / ACHAT DES LIVRES : \n";

    // On ajoute différents types de livres dans b1 pour tester l'héritage + afficher()
    b1.acheterLivre(new Roman("R001", "Victor Hugo", "Les Miserables", "Editeur1", "ISBN-111",
                              PublicCible::Adulte, GenreRoman::Litterature));

    b1.acheterLivre(new BandeDessinee("BD01", "Goscinny", "Asterix", "Editeur2", "ISBN-222",
                                      PublicCible::ToutPublic, "Uderzo"));

    b1.acheterLivre(new RecueilPoesie("P001", "Baudelaire", "Les Fleurs du Mal", "Editeur3", "ISBN-333",
                                      PublicCible::Adulte, TypePoesie::Vers));

    b1.acheterLivre(new PieceTheatre("T001", "Moliere", "Tartuffe", "Editeur4", "ISBN-444",
                                     PublicCible::ToutPublic, 17));

    b1.acheterLivre(new Album("A001", "AuteurX", "Album Photos&Dessins", "Editeur5", "ISBN-555",
                              PublicCible::Jeunesse, TypeIllustration::PhotosEtDessins));


    std::cout << "\n\n - AFFICHAGE DES LIVRES (B1) : \n";

    // On affiche tous les livres
    b1.afficherLivres(std::cout);

    std::cout << "\n\n - AFFICHAGE PAR CATEGORIE (B1) : \n";

    // On affiche par catégorie 
    b1.afficherLivresParCategorie(std::cout);

    std::cout << "\n\n - RECHERCHE (CODE / ISBN) : \n";

    // On vérifie les recherches : une valeur correcte puis une valeur fausse
    std::cout << "Recherche code R001: " << (b1.trouverLivreParCode("R001") ? "TROUVE" : "NON") << "\n";
    std::cout << "Recherche code XXX : " << (b1.trouverLivreParCode("XXX") ? "TROUVE" : "NON") << "\n";
    std::cout << "Recherche ISBN-555 : " << (b1.trouverLivreParISBN("ISBN-555") ? "TROUVE" : "NON") << "\n";
    std::cout << "Recherche ISBN-NOPE: " << (b1.trouverLivreParISBN("ISBN-NOPE") ? "TROUVE" : "NON") << "\n";

    std::cout << "\n\n - EMPRUNT : \n";

    // Cas refus : adhérent inexistant
    std::cout << "A999 essaye d'emprunter R001 (adherent inexistant)\n";
    std::cout << "Resultat: " << (b1.emprunterLivre("A999", "R001") ? "OK" : "REFUSE") << "\n";

    // Cas refus : livre inexistant
    std::cout << "A001 essaye d'emprunter ZZZ (livre inexistant)\n";
    std::cout << "Resultat: " << (b1.emprunterLivre("A001", "ZZZ") ? "OK" : "REFUSE") << "\n";

    // Cas normal : emprunt R001
    std::cout << "A001 emprunte R001\n";
    std::cout << "Resultat: " << (b1.emprunterLivre("A001", "R001") ? "OK" : "REFUSE") << "\n";

    // Cas normal : emprunt BD01 (2e livre)
    std::cout << "A001 emprunte BD01\n";
    std::cout << "Resultat: " << (b1.emprunterLivre("A001", "BD01") ? "OK" : "REFUSE") << "\n";

    // Cas refus : limite atteinte (A001 a droit à 2 livres max)
    std::cout << "A001 essaye d'emprunter P001 (limite atteinte)\n";
    std::cout << "Resultat: " << (b1.emprunterLivre("A001", "P001") ? "OK" : "REFUSE") << "\n";

    // Cas refus : livre déjà emprunté
    std::cout << "A001 essaye d'emprunter encore R001 (deja emprunte)\n";
    std::cout << "Resultat: " << (b1.emprunterLivre("A001", "R001") ? "OK" : "REFUSE") << "\n";

    std::cout << "\n\n - ETAT DES LIVRES APRES EMPRUNT : \n";
    b1.afficherLivres(std::cout);

    std::cout << "\n\n - RENDU : \n";

    // Cas normal : rendu BD01
    std::cout << "A001 rend BD01\n";
    std::cout << "Resultat: " << (b1.rendreLivre("A001", "BD01") ? "OK" : "REFUSE") << "\n";

    // Cas refus : rendre un livre déjà rendu
    std::cout << "A001 essaye de rendre encore BD01\n";
    std::cout << "Resultat: " << (b1.rendreLivre("A001", "BD01") ? "OK" : "REFUSE") << "\n";

    // Cas refus : rendu par mauvais adhérent
    std::cout << "A002 essaye de rendre R001 alors qu'il ne l'a pas emprunte\n";
    std::cout << "Resultat: " << (b1.rendreLivre("A002", "R001") ? "OK" : "REFUSE") << "\n";

    // Cas refus : livre inexistant
    std::cout << "A001 essaye de rendre ZZZ (inexistant)\n";
    std::cout << "Resultat: " << (b1.rendreLivre("A001", "ZZZ") ? "OK" : "REFUSE") << "\n";

    std::cout << "\n\n - PRET ENTRE BIBLIOTHEQUES : \n";

    // Cas normal : prêter un livre libre de b1 vers b2
    std::cout << "b1 prete T001 a b2\n";
    std::cout << "Resultat: " << (b1.preterLivreVers(b2, "T001") ? "OK" : "REFUSE") << "\n";

    // Cas refus : prêter un livre emprunté (R001 est encore emprunté par A001)
    std::cout << "b1 essaye de preter R001 (emprunte)\n";
    std::cout << "Resultat: " << (b1.preterLivreVers(b2, "R001") ? "OK" : "REFUSE") << "\n";

    // Cas refus : prêter encore une fois le même livre déjà prêté
    std::cout << "b1 essaye de preter encore T001 (deja prete)\n";
    std::cout << "Resultat: " << (b1.preterLivreVers(b2, "T001") ? "OK" : "REFUSE") << "\n";

    // Cas refus : livre inexistant
    std::cout << "b1 essaye de preter ZZZ (inexistant)\n";
    std::cout << "Resultat: " << (b1.preterLivreVers(b2, "ZZZ") ? "OK" : "REFUSE") << "\n";

    std::cout << "\n\nLivres de b2 apres pret:\n";
    b2.afficherLivres(std::cout);

    std::cout << "\n\n - DEMANDE PAR ISBN : \n";

    // Cas normal : b2 demande un livre à b1 par ISBN
    std::cout << "b2 demande ISBN-555 a b1\n";
    std::cout << "Resultat: " << (b2.demanderLivreParISBN(b1, "ISBN-555") ? "OK" : "REFUSE") << "\n";

    // Cas refus : ISBN inexistant
    std::cout << "b2 demande ISBN-NOPE a b1\n";
    std::cout << "Resultat: " << (b2.demanderLivreParISBN(b1, "ISBN-NOPE") ? "OK" : "REFUSE") << "\n";

    std::cout << "\n\nLivres de b2 apres demande ISBN:\n";
    b2.afficherLivres(std::cout);

    std::cout << "\n\n - RETOUR DES LIVRES PRETES NON EMPRUNTES : \n";

    // On demande à b2 de rendre automatiquement les livres prêtés qui n'ont pas été empruntés
    int nbRendus = b2.rendreLivresPretesNonEmpruntes();
    std::cout << "Nombre rendus automatiquement: " << nbRendus << "\n";

    std::cout << "\n\nLivres de b1 apres retour des prets:\n";
    b1.afficherLivres(std::cout);

    std::cout << "\n\n - SUPPRESSION DE LIVRES :\n";

    // Cas normal : suppression d'un livre libre
    std::cout << "b1 supprime P001 (Pilon)\n";
    std::cout << "Resultat: " << (b1.supprimerLivreParCode("P001", MotifSuppression::Pilon) ? "OK" : "REFUSE") << "\n";

    // Cas refus : suppression d'un livre emprunté (R001)
    std::cout << "b1 essaye de supprimer R001 (encore emprunte)\n";
    std::cout << "Resultat: " << (b1.supprimerLivreParCode("R001", MotifSuppression::Perdu) ? "OK" : "REFUSE") << "\n";

    // Cas refus : suppression d'un livre inexistant
    std::cout << "b1 essaye de supprimer ZZZ (inexistant)\n";
    std::cout << "Resultat: " << (b1.supprimerLivreParCode("ZZZ", MotifSuppression::Perdu) ? "OK" : "REFUSE") << "\n";

    std::cout << "\n\nLivres de b1 apres suppression:\n";
    b1.afficherLivres(std::cout);

    std::cout << "\n\n - DESINSCRIPTION :\n";


    // On rend le dernier livre pour pouvoir se désinscrire proprement
    std::cout << "A001 rend R001\n";
    std::cout << "Resultat: " << (b1.rendreLivre("A001", "R001") ? "OK" : "REFUSE") << "\n";

 

    std::cout << "\n\nFIN DEMO\n";
    return 0;
}

