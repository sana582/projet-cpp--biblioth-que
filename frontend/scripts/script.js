// Base de données
        let biblioSelectionnee = 1;
        let filtreType = 'tous';

        let bibliotheques = {
            1: {
                nom: "Bibliothèque Centrale",
                ville: "Marseille",
                code: "B001",
                livres: [
                    { code: "R001", type: "Roman", titre: "Les Misérables", auteur: "Victor Hugo", editeur: "Editeur1", isbn: "ISBN-111", public: "Adulte", etat: "Libre", genre: "Littérature", emprunteur: null, proprietaire: 1 },
                    { code: "BD01", type: "BD", titre: "Astérix", auteur: "Goscinny", editeur: "Editeur2", isbn: "ISBN-222", public: "Tout public", etat: "Libre", dessinateur: "Uderzo", emprunteur: null, proprietaire: 1 },
                    { code: "P001", type: "Poésie", titre: "Les Fleurs du Mal", auteur: "Baudelaire", editeur: "Editeur3", isbn: "ISBN-333", public: "Adulte", etat: "Libre", typePoesie: "Vers", emprunteur: null, proprietaire: 1 },
                    { code: "T001", type: "Théâtre", titre: "Tartuffe", auteur: "Molière", editeur: "Editeur4", isbn: "ISBN-444", public: "Tout public", etat: "Libre", siecle: 17, emprunteur: null, proprietaire: 1 },
                    { code: "A001", type: "Album", titre: "Album Photos", auteur: "AuteurX", editeur: "Editeur5", isbn: "ISBN-555", public: "Jeunesse", etat: "Libre", illustrations: "Photos et dessins", emprunteur: null, proprietaire: 1 }
                ],
                adherents: [
                    { numero: "A001", nom: "Naimi", prenom: "Salima", adresse: "Marseille", nbLivresAutorise: 2, livresEmpruntes: [] }
                ]
            },
            2: {
                nom: "Bibliothèque Nord",
                ville: "Aix-en-Provence",
                code: "B002",
                livres: [],
                adherents: []
            }
        };

        function selectionnerBiblio(num) {
            biblioSelectionnee = num;
            document.querySelectorAll('.biblio-card').forEach((card, i) => {
                card.classList.toggle('selected', i + 1 === num);
            });
            if (document.getElementById('voir-livres').classList.contains('active')) {
                afficherLivres();
            }
        }

        function montrerSection(id) {
            document.querySelectorAll('.section').forEach(s => s.classList.remove('active'));
            document.getElementById(id).classList.add('active');
            
            if (id === 'voir-livres') {
                filtreType = 'tous';
                document.querySelectorAll('.tab-btn').forEach((btn, i) => {
                    btn.classList.toggle('active', i === 0);
                });
                afficherLivres();
            } else if (id === 'menu-principal') {
                mettreAJourStats();
            } else if (id === 'ajouter') {
                updateFormFields();
            } else if (id === 'adherents') {
                afficherAdherents();
            }
            cacherMessage();
        }

        function afficherParType(type) {
            filtreType = type;
            document.querySelectorAll('.tab-btn').forEach(btn => {
                btn.classList.toggle('active', btn.textContent.includes(type === 'tous' ? 'Tous' : type));
            });
            afficherLivres();
        }

        function afficherLivres() {
            const container = document.getElementById('liste-livres');
            const livres = bibliotheques[biblioSelectionnee].livres;
            
            const livresFiltres = filtreType === 'tous' 
                ? livres 
                : livres.filter(l => l.type === filtreType);

            if (livresFiltres.length === 0) {
                container.innerHTML = '<p style="text-align: center; color: #999; padding: 40px;">Aucun livre dans cette catégorie</p>';
                return;
            }

            container.innerHTML = livresFiltres.map(livre => {
                let details = '';
                if (livre.genre) details += `<div class="livre-info"><strong>Genre:</strong> ${livre.genre}</div>`;
                if (livre.dessinateur) details += `<div class="livre-info"><strong>Dessinateur:</strong> ${livre.dessinateur}</div>`;
                if (livre.typePoesie) details += `<div class="livre-info"><strong>Type:</strong> ${livre.typePoesie}</div>`;
                if (livre.siecle) details += `<div class="livre-info"><strong>Siècle:</strong> ${livre.siecle}e</div>`;
                if (livre.illustrations) details += `<div class="livre-info"><strong>Illustrations:</strong> ${livre.illustrations}</div>`;
                if (livre.emprunteur) details += `<div class="livre-info"><strong>Emprunté par:</strong> ${livre.emprunteur}</div>`;

                let badgeClass = livre.etat === 'Libre' ? 'libre' : (livre.etat === 'Emprunté' ? 'emprunte' : 'prete');
                
                return `
                    <div class="livre-card">
                        <h3>${livre.titre}</h3>
                        <div class="livre-info"><strong>Code:</strong> ${livre.code}</div>
                        <div class="livre-info"><strong>Auteur:</strong> ${livre.auteur}</div>
                        <div class="livre-info"><strong>ISBN:</strong> ${livre.isbn}</div>
                        <div class="livre-info"><strong>Éditeur:</strong> ${livre.editeur}</div>
                        <div class="livre-info"><strong>Public:</strong> ${livre.public}</div>
                        ${details}
                        <span class="badge ${badgeClass}">${livre.etat}</span>
                    </div>
                `;
            }).join('');
        }

        function updateFormFields() {
            const type = document.getElementById('type').value;
            const container = document.getElementById('specificFields');
            
            let html = '';
            if (type === 'Roman') {
                html = `
                    <div class="form-group">
                        <label>Genre :</label>
                        <select id="genre" required>
                            <option value="Littérature">Littérature</option>
                            <option value="Roman noir">Roman Noir</option>
                            <option value="Roman policier">Roman Policier</option>
                            <option value="Roman d'aventures">Roman d'Aventures</option>
                            <option value="Nouvelle">Nouvelle</option>
                            <option value="Roman historique">Roman Historique</option>
                        </select>
                    </div>
                `;
            } else if (type === 'BD') {
                html = `
                    <div class="form-group">
                        <label>Dessinateur :</label>
                        <input type="text" id="dessinateur" required placeholder="Nom du dessinateur">
                    </div>
                `;
            } else if (type === 'Poésie') {
                html = `
                    <div class="form-group">
                        <label>Type de Poésie :</label>
                        <select id="typePoesie" required>
                            <option value="Vers">Vers</option>
                            <option value="Prose">Prose</option>
                            <option value="Vers et Prose">Vers et Prose</option>
                        </select>
                    </div>
                `;
            } else if (type === 'Théâtre') {
                html = `
                    <div class="form-group">
                        <label>Siècle :</label>
                        <input type="number" id="siecle" required min="1" max="21" placeholder="Ex: 17">
                    </div>
                `;
            } else if (type === 'Album') {
                html = `
                    <div class="form-group">
                        <label>Type d'Illustrations :</label>
                        <select id="illustrations" required>
                            <option value="Photos">Photos</option>
                            <option value="Dessins">Dessins</option>
                            <option value="Photos et dessins">Photos et Dessins</option>
                        </select>
                    </div>
                `;
            }
            container.innerHTML = html;
        }

        function mettreAJourStats() {
            const totalLivres = bibliotheques[1].livres.length + bibliotheques[2].livres.length;
            const tousLivres = [...bibliotheques[1].livres, ...bibliotheques[2].livres];
            const libres = tousLivres.filter(l => l.etat === 'Libre').length;
            const empruntes = tousLivres.filter(l => l.etat === 'Emprunté').length;
            const pretes = tousLivres.filter(l => l.etat === 'Prêté').length;
            const adherents = bibliotheques[1].adherents.length + bibliotheques[2].adherents.length;

            document.getElementById('totalLivres').textContent = totalLivres;
            document.getElementById('livresLibres').textContent = libres;
            document.getElementById('livresEmpruntes').textContent = empruntes;
            document.getElementById('livresPretes').textContent = pretes;
            document.getElementById('totalAdherents').textContent = adherents;
            document.getElementById('livres-b1').textContent = bibliotheques[1].livres.length;
            document.getElementById('livres-b2').textContent = bibliotheques[2].livres.length;
        }

        function afficherMessage(texte, type) {
            const msg = document.getElementById('message');
            msg.textContent = texte;
            msg.className = `message ${type} show`;
            setTimeout(() => msg.classList.remove('show'), 4000);
        }

        function cacherMessage() {
            document.getElementById('message').classList.remove('show');
        }

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

            // Vérifier code unique
            const tousLivres = [...bibliotheques[1].livres, ...bibliotheques[2].livres];
            if (tousLivres.find(l => l.code === livre.code)) {
                afficherMessage('❌ Ce code existe déjà !', 'error');
                return;
            }

            // Champs spécifiques
            if (livre.type === 'Roman') {
                livre.genre = document.getElementById('genre').value;
            } else if (livre.type === 'BD') {
                livre.dessinateur = document.getElementById('dessinateur').value;
            } else if (livre.type === 'Poésie') {
                livre.typePoesie = document.getElementById('typePoesie').value;
            } else if (livre.type === 'Théâtre') {
                livre.siecle = parseInt(document.getElementById('siecle').value);
            } else if (livre.type === 'Album') {
                livre.illustrations = document.getElementById('illustrations').value;
            }

            bibliotheques[biblioSelectionnee].livres.push(livre);
            afficherMessage('✅ Livre ajouté avec succès !', 'success');
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
                afficherMessage('❌ Adhérent non trouvé dans cette bibliothèque', 'error');
                return;
            }

            const livre = bibliotheques[biblioSelectionnee].livres.find(l => l.code === code);
            if (!livre) {
                afficherMessage('❌ Livre non trouvé', 'error');
                return;
            }

            if (livre.etat !== 'Libre') {
                afficherMessage('❌ Livre non disponible', 'error');
                return;
            }

            if (adherent.livresEmpruntes.length >= adherent.nbLivresAutorise) {
                afficherMessage('❌ Limite d\'emprunts atteinte', 'error');
                return;
            }

            livre.etat = 'Emprunté';
            livre.emprunteur = `${adherent.prenom} ${adherent.nom}`;
            adherent.livresEmpruntes.push(code);

            afficherMessage(`✅ Livre emprunté par ${adherent.prenom} ${adherent.nom}`, 'success');
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
                afficherMessage('❌ Adhérent non trouvé', 'error');
                return;
            }

            const livre = bibliotheques[biblioSelectionnee].livres.find(l => l.code === code);
            if (!livre) {
                afficherMessage('❌ Livre non trouvé', 'error');
                return;
            }

            if (livre.etat !== 'Emprunté') {
                afficherMessage('❌ Ce livre n\'est pas emprunté', 'error');
                return;
            }

            if (!adherent.livresEmpruntes.includes(code)) {
                afficherMessage('❌ Ce livre n\'a pas été emprunté par cet adhérent', 'error');
                return;
            }

            // Retour à l'état approprié
            if (livre.proprietaire !== biblioSelectionnee) {
                livre.etat = 'Prêté';
            } else {
                livre.etat = 'Libre';
            }
            
            livre.emprunteur = null;
            adherent.livresEmpruntes = adherent.livresEmpruntes.filter(c => c !== code);

            afficherMessage(`✅ Livre rendu par ${adherent.prenom} ${adherent.nom}`, 'success');
            e.target.reset();
            mettreAJourStats();
            
            setTimeout(() => montrerSection('menu-principal'), 1500);
        }

        function preterLivre(e) {
            e.preventDefault();
            
            const code = document.getElementById('codeLivrePret').value.toUpperCase();
            const index = bibliotheques[1].livres.findIndex(l => l.code === code);
            
            if (index === -1) {
                afficherMessage('❌ Livre non trouvé dans B1', 'error');
                return;
            }

            const livre = bibliotheques[1].livres[index];
            
            if (livre.etat !== 'Libre') {
                afficherMessage('❌ Livre non disponible pour le prêt', 'error');
                return;
            }

            // Transférer le livre
            bibliotheques[1].livres.splice(index, 1);
            livre.etat = 'Prêté';
            bibliotheques[2].livres.push(livre);

            afficherMessage('✅ Livre prêté à B2 avec succès !', 'success');
            e.target.reset();
            mettreAJourStats();
            
            setTimeout(() => montrerSection('menu-principal'), 1500);
        }

        function demanderLivre(e) {
            e.preventDefault();
            
            const isbn = document.getElementById('isbnDemande').value.toUpperCase();
            const index = bibliotheques[1].livres.findIndex(l => l.isbn === isbn);
            
            if (index === -1) {
                afficherMessage('❌ Livre avec cet ISBN non trouvé dans B1', 'error');
                return;
            }

            const livre = bibliotheques[1].livres[index];
            
            if (livre.etat !== 'Libre') {
                afficherMessage('❌ Livre non disponible', 'error');
                return;
            }

            // Transférer le livre
            bibliotheques[1].livres.splice(index, 1);
            livre.etat = 'Prêté';
            bibliotheques[2].livres.push(livre);

            afficherMessage('✅ Livre demandé et transféré à B2 !', 'success');
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
                afficherMessage('❌ Livre non trouvé', 'error');
                return;
            }

            const livre = bibliotheques[biblioSelectionnee].livres[index];
            
            if (livre.etat === 'Emprunté') {
                afficherMessage('❌ Impossible de supprimer un livre emprunté', 'error');
                return;
            }

            bibliotheques[biblioSelectionnee].livres.splice(index, 1);
            afficherMessage(`✅ Livre supprimé (${motif})`, 'success');
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

            // Vérifier si existe déjà
            if (bibliotheques[1].adherents.find(a => a.numero === adherent.numero)) {
                afficherMessage('❌ Ce numéro d\'adhérent existe déjà', 'error');
                return;
            }

            bibliotheques[1].adherents.push(adherent);
            afficherMessage('✅ Adhérent inscrit avec succès !', 'success');
            e.target.reset();
            afficherAdherents();
            mettreAJourStats();
        }

        function afficherAdherents() {
            const tbody = document.getElementById('listeAdherents');
            const adherents = bibliotheques[1].adherents;
            
            tbody.innerHTML = adherents.map(a => `
                <tr>
                    <td>${a.numero}</td>
                    <td>${a.nom}</td>
                    <td>${a.prenom}</td>
                    <td>${a.adresse}</td>
                    <td>${a.nbLivresAutorise}</td>
                    <td>${a.livresEmpruntes.length}</td>
                </tr>
            `).join('');
        }

        function retournerLivresPretes() {
            let compteur = 0;
            
            // Parcourir les livres de B2
            const livresARetourner = [];
            bibliotheques[2].livres.forEach((livre, index) => {
                if (livre.etat === 'Prêté' && livre.emprunteur === null && livre.proprietaire === 1) {
                    livresARetourner.push(index);
                }
            });

            // Retourner les livres à B1
            livresARetourner.reverse().forEach(index => {
                const livre = bibliotheques[2].livres[index];
                bibliotheques[2].livres.splice(index, 1);
                livre.etat = 'Libre';
                bibliotheques[1].livres.push(livre);
                compteur++;
            });

            if (compteur > 0) {
                afficherMessage(`✅ ${compteur} livre(s) rendu(s) à B1`, 'success');
            } else {
                afficherMessage('ℹ️ Aucun livre à retourner', 'success');
            }
            
            mettreAJourStats();
        }

        // Initialisation
        updateFormFields();
        mettreAJourStats();
        afficherAdherents();