#include <iostream>

#include "Bibliotheque.h"
#include "Adherent.h"
#include "Roman.h"
#include "BandeDessinee.h"
#include "RecueilPoesie.h"
#include "PieceTheatre.h"
#include "Album.h"
#include "Enums.h"

int main() {
    std::cout << "DEMO Gestion de bibliotheques\n";

    // 1) On cree deux bibliotheques
    Bibliotheque b1("Biblio Centrale", "Marseille", "B001");
    Bibliotheque b2("Biblio Nord", "Aix-en-Provence", "B002");

    // 2) On cree deux adherents
    Adherent a1("Naimi", "Salima", "Marseille", "A001", 2);
    Adherent a2("Riahi", "Sana", "Aix-en-Provence", "A002", 1);

    std::cout << "\n\n - INSCRIPTION : \n";

    // Inscription normale
    b1.inscrire(&a1);
    b2.inscrire(&a2);

    // Cas "bizarre" pour voir le comportement
    std::cout << "On essaye de re-inscrire A001 dans b1\n";
    b1.inscrire(&a1);

    std::cout << "On essaye d'inscrire A001 dans b2 alors qu'il est deja dans b1\n";
    b2.inscrire(&a1);

    std::cout << "\n\n - AJOUT / ACHAT DES LIVRES : \n";

    // 3) On ajoute plusieurs types de livres dans b1
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

    // On essaye un duplicata pour verifier si b1 refuse
    std::cout << "On essaye d'ajouter un duplicata avec le code R001\n";
    b1.acheterLivre(new Roman("R001", "X", "Duplicata", "Ed", "ISBN-X",
                              PublicCible::Adulte, GenreRoman::Autre));

    std::cout << "\n\n - AFFICHAGE DES LIVRES (B1) : \n";
    b1.afficherLivres(std::cout);

    std::cout << "\n\n - AFFICHAGE PAR CATEGORIE (B1) : \n";
    b1.afficherLivresParCategorie(std::cout);

    std::cout << "\n\n - RECHERCHE (CODE / ISBN) : \n";
    std::cout << "Recherche code R001: " << (b1.trouverLivreParCode("R001") ? "TROUVE" : "NON") << "\n";
    std::cout << "Recherche code XXX : " << (b1.trouverLivreParCode("XXX") ? "TROUVE" : "NON") << "\n";
    std::cout << "Recherche ISBN-555 : " << (b1.trouverLivreParISBN("ISBN-555") ? "TROUVE" : "NON") << "\n";
    std::cout << "Recherche ISBN-NOPE: " << (b1.trouverLivreParISBN("ISBN-NOPE") ? "TROUVE" : "NON") << "\n";

    std::cout << "\n\nFIN DEMO (version 1)\n";
    return 0;
}
