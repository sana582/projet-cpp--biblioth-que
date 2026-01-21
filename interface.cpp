#include <iostream>
#include <string>
#include "src/Bibliotheque.h"
#include "src/Adherent.h"
#include "src/Roman.h"
#include "src/BandeDessinee.h"
#include "src/RecueilPoesie.h"
#include "src/PieceTheatre.h"
#include "src/Album.h"
#include "src/Enums.h"

int main() {
    std::cout << "=== Gestion de Bibliotheques - Version interactive etudiante ===\n";

    // Création de deux bibliothèques
    Bibliotheque b1("Biblio Centrale", "Marseille", "B001");
    Bibliotheque b2("Biblio Nord", "Aix-en-Provence", "B002");

    // Création de deux adhérents pour tester
    Adherent a1("Naimi", "Salima", "Marseille", "A001", 2);
    Adherent a2("Riahi", "Sana", "Aix-en-Provence", "A002", 1);

    // Inscription automatique
    b1.inscrire(&a1);
    b2.inscrire(&a2);

    int choix;
    do {
        std::cout << "\n=== MENU PRINCIPAL ===\n";
        std::cout << "1. Ajouter un livre\n";
        std::cout << "2. Afficher tous les livres (B1 ou B2)\n";
        std::cout << "3. Rechercher un livre (code ou ISBN)\n";
        std::cout << "4. Emprunter un livre\n";
        std::cout << "5. Rendre un livre\n";
        std::cout << "6. Preter un livre entre bibliotheques\n";
        std::cout << "7. Demander un livre par ISBN entre bibliotheques\n";
        std::cout << "8. Rendre les livres pretes non empruntes\n";
        std::cout << "9. Supprimer un livre\n";
        std::cout << "0. Quitter\n";
        std::cout << "Choix: "; std::cin >> choix;
        std::cin.ignore(); // nettoyer buffer

        std::string code, auteur, titre, editeur, isbn, codeAdherent, codeLivre;
        int paramInt;
        std::string paramStr;
        int choixLivre;
        Bibliotheque* bib = &b1;

        switch (choix) {

            case 1: { // AJOUT LIVRE
                std::cout << "Choisir bibliotheque (1=B1, 2=B2): "; std::cin >> choixLivre;
                bib = (choixLivre == 2) ? &b2 : &b1;
                std::cout << "Type de livre: 1=Roman, 2=BandeDessinee, 3=RecueilPoesie, 4=PieceTheatre, 5=Album\n";
                std::cin >> choixLivre;
                std::cin.ignore();

                std::cout << "Code: "; std::getline(std::cin, code);
                std::cout << "Auteur: "; std::getline(std::cin, auteur);
                std::cout << "Titre: "; std::getline(std::cin, titre);
                std::cout << "Editeur: "; std::getline(std::cin, editeur);
                std::cout << "ISBN: "; std::getline(std::cin, isbn);

                switch(choixLivre) {
                    case 1:
                        bib->acheterLivre(new Roman(code, auteur, titre, editeur, isbn,
                                                    PublicCible::Adulte, GenreRoman::Litterature));
                        break;
                    case 2:
                        std::cout << "Auteur Illustration: "; std::getline(std::cin, paramStr);
                        bib->acheterLivre(new BandeDessinee(code, auteur, titre, editeur, isbn,
                                                           PublicCible::ToutPublic, paramStr));
                        break;
                    case 3:
                        bib->acheterLivre(new RecueilPoesie(code, auteur, titre, editeur, isbn,
                                                           PublicCible::Adulte, TypePoesie::Vers));
                        break;
                    case 4:
                        std::cout << "Nombre de personnages: "; std::cin >> paramInt; std::cin.ignore();
                        bib->acheterLivre(new PieceTheatre(code, auteur, titre, editeur, isbn,
                                                          PublicCible::ToutPublic, paramInt));
                        break;
                    case 5:
                        bib->acheterLivre(new Album(code, auteur, titre, editeur, isbn,
                                                    PublicCible::Jeunesse, TypeIllustration::PhotosEtDessins));
                        break;
                    default: std::cout << "Choix invalide\n"; break;
                }
                break;
            }

            case 2: { // AFFICHAGE LIVRES
                std::cout << "Afficher livres? "; std::cin >> choixLivre;
                bib = (choixLivre == 2) ? &b2 : &b1;
                bib->afficherLivres(std::cout);
                break;
            }

            case 3: { // RECHERCHE
                std::cout << "Rechercher par 1=Code, 2=ISBN: ";
                std::cin >> choixLivre; std::cin.ignore();
                std::cout << "Bibliotheque (1=B1, 2=B2)? ";
                std::cin >> paramInt; std::cin.ignore();
                bib = (paramInt == 2) ? &b2 : &b1;

                if(choixLivre == 1) {
                    std::cout << "Code du livre: "; std::getline(std::cin, code);
                    std::cout << (bib->trouverLivreParCode(code) ? "TROUVE" : "NON TROUVE") << "\n";
                } else {
                    std::cout << "ISBN du livre: "; std::getline(std::cin, isbn);
                    std::cout << (bib->trouverLivreParISBN(isbn) ? "TROUVE" : "NON TROUVE") << "\n";
                }
                break;
            }

            case 4: { // EMPRUNT
                std::cout << "Bibliotheque (1=B1, 2=B2)? "; std::cin >> choixLivre;
                bib = (choixLivre == 2) ? &b2 : &b1;
                std::cin.ignore();
                std::cout << "Code adherent: "; std::getline(std::cin, codeAdherent);
                std::cout << "Code livre: "; std::getline(std::cin, codeLivre);
                std::cout << (bib->emprunterLivre(codeAdherent, codeLivre) ? "OK" : "REFUSE") << "\n";
                break;
            }

            case 5: { // RENDU
                std::cout << "Bibliotheque (1=B1, 2=B2)? "; std::cin >> choixLivre;
                bib = (choixLivre == 2) ? &b2 : &b1;
                std::cin.ignore();
                std::cout << "Code adherent: "; std::getline(std::cin, codeAdherent);
                std::cout << "Code livre: "; std::getline(std::cin, codeLivre);
                std::cout << (bib->rendreLivre(codeAdherent, codeLivre) ? "OK" : "REFUSE") << "\n";
                break;
            }

            case 6: { // PRET ENTRE BIBLIOTHEQUES
                std::cout << "Bibliotheque prete (1=B1, 2=B2)? "; std::cin >> choixLivre;
                bib = (choixLivre == 2) ? &b2 : &b1;
                Bibliotheque* bibDest = (bib == &b1) ? &b2 : &b1;
                std::cin.ignore();
                std::cout << "Code livre a preter: "; std::getline(std::cin, codeLivre);
                std::cout << (bib->preterLivreVers(*bibDest, codeLivre) ? "OK" : "REFUSE") << "\n";
                break;
            }

            case 7: { // DEMANDE PAR ISBN
                std::cout << "Bibliotheque demandeuse (1=B1, 2=B2)? "; std::cin >> choixLivre;
                bib = (choixLivre == 2) ? &b2 : &b1;
                Bibliotheque* bibDest = (bib == &b1) ? &b2 : &b1;
                std::cin.ignore();
                std::cout << "ISBN du livre a demander: "; std::getline(std::cin, isbn);
                std::cout << (bib->demanderLivreParISBN(*bibDest, isbn) ? "OK" : "REFUSE") << "\n";
                break;
            }

            case 8: { // RETOUR LIVRES PRETES NON EMPRUNTES
                std::cout << "Bibliotheque (1=B1, 2=B2)? "; std::cin >> choixLivre;
                bib = (choixLivre == 2) ? &b2 : &b1;
                std::cout << "Nombre livres rendus: " << bib->rendreLivresPretesNonEmpruntes() << "\n";
                break;
            }

            case 9: { // SUPPRESSION LIVRES
                std::cout << "Bibliotheque (1=B1, 2=B2)? "; std::cin >> choixLivre;
                bib = (choixLivre == 2) ? &b2 : &b1;
                std::cin.ignore();
                std::cout << "Code livre a supprimer: "; std::getline(std::cin, codeLivre);
                std::cout << "Motif (1=Pilon, 2=Perdu)? "; std::cin >> paramInt;
                std::cout << (bib->supprimerLivreParCode(codeLivre, 
                          (paramInt==1?MotifSuppression::Pilon:MotifSuppression::Perdu)) ? "OK" : "REFUSE") << "\n";
                break;
            }

            case 0:
                std::cout << "Fin du programme\n";
                break;

            default:
                std::cout << "Choix invalide\n";
                break;
        }

    } while(choix != 0);

    return 0;
}
