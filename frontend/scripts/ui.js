// GESTION DE L'INTERFACE UTILISATEUR 

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
        const btnText = btn.textContent.trim();
        btn.classList.toggle('active', 
            (type === 'tous' && btnText === 'Tous') ||
            (type !== 'tous' && btnText.includes(type))
        );
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
        html = `<div class="form-group"><label>Genre :</label><select id="genre" required><option value="Littérature">Littérature</option><option value="Roman noir">Roman Noir</option><option value="Roman policier">Roman Policier</option><option value="Roman d'aventures">Roman d'Aventures</option><option value="Nouvelle">Nouvelle</option><option value="Roman historique">Roman Historique</option></select></div>`;
    } else if (type === 'BD') {
        html = `<div class="form-group"><label>Dessinateur :</label><input type="text" id="dessinateur" required placeholder="Nom du dessinateur"></div>`;
    } else if (type === 'Poésie') {
        html = `<div class="form-group"><label>Type de Poésie :</label><select id="typePoesie" required><option value="Vers">Vers</option><option value="Prose">Prose</option><option value="Vers et Prose">Vers et Prose</option></select></div>`;
    } else if (type === 'Théâtre') {
        html = `<div class="form-group"><label>Siècle :</label><input type="number" id="siecle" required min="1" max="21" placeholder="Ex: 17"></div>`;
    } else if (type === 'Album') {
        html = `<div class="form-group"><label>Type d'Illustrations :</label><select id="illustrations" required><option value="Photos">Photos</option><option value="Dessins">Dessins</option><option value="Photos et dessins">Photos et Dessins</option></select></div>`;
    }
    container.innerHTML = html;
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