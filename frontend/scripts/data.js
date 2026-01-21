// GESTION DES DONNÉES ET SAUVEGARDE 

let biblioSelectionnee = 1;
let filtreType = 'tous';
let bibliotheques = {};

// Charger les données depuis le fichier JSON au démarrage
window.addEventListener('load', async () => {
    await chargerDonneesDepuisJSON();
});

async function chargerDonneesDepuisJSON() {
    try {
        const response = await fetch('pages/bibliotheques_data.json');
        if (!response.ok) {
            throw new Error('Impossible de charger le fichier JSON');
        }
        bibliotheques = await response.json();
        afficherMessage('Données chargées depuis le fichier JSON', 'success');
        
        mettreAJourStats();
        afficherAdherents();
        updateFormFields();
        
    } catch (error) {
        console.error('Erreur lors du chargement des données:', error);
        afficherMessage('Erreur: Impossible de charger bibliotheques_data.json', 'error');
    }
}

function sauvegarderDonnees() {
    afficherMessage('Données mises à jour !', 'success');
}

function exporterJSON() {
    const dataStr = JSON.stringify(bibliotheques, null, 2);
    const dataBlob = new Blob([dataStr], { type: 'application/json' });
    const url = URL.createObjectURL(dataBlob);
    const link = document.createElement('a');
    link.href = url;
    link.download = 'bibliotheques_export_' + new Date().toISOString().split('T')[0] + '.json';
    link.click();
    URL.revokeObjectURL(url);
    afficherMessage('Fichier JSON exporté avec succès !', 'success');
}

function importerJSON(event) {
    const file = event.target.files[0];
    if (!file) return;

    const reader = new FileReader();
    reader.onload = function(e) {
        try {
            const donnees = JSON.parse(e.target.result);
            bibliotheques = donnees;
            mettreAJourStats();
            afficherMessage(' Données importées avec succès !', 'success');
            montrerSection('menu-principal');
        } catch (error) {
            afficherMessage(' Erreur lors de l\'importation du fichier', 'error');
        }
    };
    reader.readAsText(file);
    event.target.value = '';
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