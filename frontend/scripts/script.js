// GESTION DES OPÉRATIONS (LIVRES ET ADHÉRENTS) 

function ajouterLivre(e) {
    e.preventDefault();
    
    const livre = {
        code: document.getElementById('code').value.toUpperCase(),
        type: document.getElementById('type').value,
        titre: document.getElementById('titre').value,
        auteur: document.getElementById('auteur').value,
        editeur: document.getElementById('editeur').value,
        isbn: document.getElementById('isbn').value.toUpperCase(),
        public: document.getElementById('publicCible').value,
        etat: 'Libre',
        emprunteur: null,
        proprietaire: biblioSelectionnee
    };

    const tousLivres = [...bibliotheques[1].livres, ...bibliotheques[2].livres];
    if (tousLivres.find(l => l.code === livre.code)) {
        afficherMessage(' Ce code existe déjà !', 'error');
        return;
    }

    if (livre.type === 'Roman') livre.genre = document.getElementById('genre').value;
    else if (livre.type === 'BD') livre.dessinateur = document.getElementById('dessinateur').value;
    else if (livre.type === 'Poésie') livre.typePoesie = document.getElementById('typePoesie').value;
    else if (livre.type === 'Théâtre') livre.siecle = parseInt(document.getElementById('siecle').value);
    else if (livre.type === 'Album') livre.illustrations = document.getElementById('illustrations').value;

    bibliotheques[biblioSelectionnee].livres.push(livre);
    sauvegarderDonnees();
    afficherMessage(' Livre ajouté et sauvegardé !', 'success');
    e.target.reset();
    updateFormFields();
    mettreAJourStats();
    
    setTimeout(() => montrerSection('menu-principal'), 1500);
}

function emprunterLivre(e) {
    e.preventDefault();
    
    const numAdh = document.getElementById('numAdherentEmp').value.toUpperCase();
    const code = document.getElementById('codeLivreEmp').value.toUpperCase();
    
    const adherent = bibliotheques[biblioSelectionnee].adherents.find(a => a.numero === numAdh);
    if (!adherent) {
        afficherMessage(' Adhérent non trouvé dans cette bibliothèque', 'error');
        return;
    }

    const livre = bibliotheques[biblioSelectionnee].livres.find(l => l.code === code);
    if (!livre) {
        afficherMessage(' Livre non trouvé', 'error');
        return;
    }

    if (livre.etat !== 'Libre') {
        afficherMessage(' Livre non disponible', 'error');
        return;
    }

    if (adherent.livresEmpruntes.length >= adherent.nbLivresAutorise) {
        afficherMessage(' Limite d\'emprunts atteinte', 'error');
        return;
    }

    livre.etat = 'Emprunté';
    livre.emprunteur = `${adherent.prenom} ${adherent.nom}`;
    adherent.livresEmpruntes.push(code);

    sauvegarderDonnees();
    afficherMessage(` Livre emprunté par ${adherent.prenom} ${adherent.nom}`, 'success');
    e.target.reset();
    mettreAJourStats();
    
    setTimeout(() => montrerSection('menu-principal'), 1500);
}

function rendreLivre(e) {
    e.preventDefault();
    
    const numAdh = document.getElementById('numAdherentRen').value.toUpperCase();
    const code = document.getElementById('codeLivreRen').value.toUpperCase();
    
    const adherent = bibliotheques[biblioSelectionnee].adherents.find(a => a.numero === numAdh);
    if (!adherent) {
        afficherMessage(' Adhérent non trouvé', 'error');
        return;
    }

    const livre = bibliotheques[biblioSelectionnee].livres.find(l => l.code === code);
    if (!livre) {
        afficherMessage(' Livre non trouvé', 'error');
        return;
    }

    if (livre.etat !== 'Emprunté') {
        afficherMessage(' Ce livre n\'est pas emprunté', 'error');
        return;
    }

    if (!adherent.livresEmpruntes.includes(code)) {
        afficherMessage(' Ce livre n\'a pas été emprunté par cet adhérent', 'error');
        return;
    }

    if (livre.proprietaire !== biblioSelectionnee) {
        livre.etat = 'Prêté';
    } else {
        livre.etat = 'Libre';
    }
    
    livre.emprunteur = null;
    adherent.livresEmpruntes = adherent.livresEmpruntes.filter(c => c !== code);

    sauvegarderDonnees();
    afficherMessage(` Livre rendu par ${adherent.prenom} ${adherent.nom}`, 'success');
    e.target.reset();
    mettreAJourStats();
    
    setTimeout(() => montrerSection('menu-principal'), 1500);
}

function preterLivre(e) {
    e.preventDefault();
    
    const code = document.getElementById('codeLivrePret').value.toUpperCase();
    const index = bibliotheques[1].livres.findIndex(l => l.code === code);
    
    if (index === -1) {
        afficherMessage(' Livre non trouvé dans B1', 'error');
        return;
    }

    const livre = bibliotheques[1].livres[index];
    
    if (livre.etat !== 'Libre') {
        afficherMessage(' Livre non disponible pour le prêt', 'error');
        return;
    }

    bibliotheques[1].livres.splice(index, 1);
    livre.etat = 'Prêté';
    bibliotheques[2].livres.push(livre);

    sauvegarderDonnees();
    afficherMessage(' Livre prêté à B2 avec succès !', 'success');
    e.target.reset();
    mettreAJourStats();
    
    setTimeout(() => montrerSection('menu-principal'), 1500);
}

function demanderLivre(e) {
    e.preventDefault();
    
    const isbn = document.getElementById('isbnDemande').value.toUpperCase();
    const index = bibliotheques[1].livres.findIndex(l => l.isbn === isbn);
    
    if (index === -1) {
        afficherMessage(' Livre avec cet ISBN non trouvé dans B1', 'error');
        return;
    }

    const livre = bibliotheques[1].livres[index];
    
    if (livre.etat !== 'Libre') {
        afficherMessage(' Livre non disponible', 'error');
        return;
    }

    bibliotheques[1].livres.splice(index, 1);
    livre.etat = 'Prêté';
    bibliotheques[2].livres.push(livre);

    sauvegarderDonnees();
    afficherMessage(' Livre demandé et transféré à B2 !', 'success');
    e.target.reset();
    mettreAJourStats();
    
    setTimeout(() => montrerSection('menu-principal'), 1500);
}

function supprimerLivre(e) {
    e.preventDefault();
    
    const code = document.getElementById('codeLivreSupp').value.toUpperCase();
    const motif = document.getElementById('motifSupp').value;
    const index = bibliotheques[biblioSelectionnee].livres.findIndex(l => l.code === code);
    
    if (index === -1) {
        afficherMessage(' Livre non trouvé', 'error');
        return;
    }

    const livre = bibliotheques[biblioSelectionnee].livres[index];
    
    if (livre.etat === 'Emprunté') {
        afficherMessage(' Impossible de supprimer un livre emprunté', 'error');
        return;
    }

    bibliotheques[biblioSelectionnee].livres.splice(index, 1);
    sauvegarderDonnees();
    afficherMessage(` Livre supprimé (${motif})`, 'success');
    e.target.reset();
    mettreAJourStats();
    
    setTimeout(() => montrerSection('menu-principal'), 1500);
}

function inscrireAdherent(e) {
    e.preventDefault();
    
    const adherent = {
        numero: document.getElementById('numAdh').value.toUpperCase(),
        nom: document.getElementById('nomAdh').value,
        prenom: document.getElementById('prenomAdh').value,
        adresse: document.getElementById('adresseAdh').value,
        nbLivresAutorise: parseInt(document.getElementById('nbLivresAdh').value),
        livresEmpruntes: []
    };

    if (bibliotheques[1].adherents.find(a => a.numero === adherent.numero)) {
        afficherMessage(' Ce numéro d\'adhérent existe déjà', 'error');
        return;
    }

    bibliotheques[1].adherents.push(adherent);
    sauvegarderDonnees();
    afficherMessage(' Adhérent inscrit avec succès !', 'success');
    e.target.reset();
    afficherAdherents();
    mettreAJourStats();
}

function retournerLivresPretes() {
    let compteur = 0;
    
    const livresARetourner = [];
    bibliotheques[2].livres.forEach((livre, index) => {
        if (livre.etat === 'Prêté' && livre.emprunteur === null && livre.proprietaire === 1) {
            livresARetourner.push(index);
        }
    });

    livresARetourner.reverse().forEach(index => {
        const livre = bibliotheques[2].livres[index];
        bibliotheques[2].livres.splice(index, 1);
        livre.etat = 'Libre';
        bibliotheques[1].livres.push(livre);
        compteur++;
    });

    if (compteur > 0) {
        sauvegarderDonnees();
        afficherMessage(` ${compteur} livre(s) rendu(s) à B1`, 'success');
    } else {
        afficherMessage(' Aucun livre à retourner', 'success');
    }
    
    mettreAJourStats();
}