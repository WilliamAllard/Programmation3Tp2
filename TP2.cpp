#include "TP2.h"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <queue>

void TP2::lireLabyrinthe(const std::string filePath)
{
	std::ifstream tp2{ filePath, std::ios::in | std::ios::binary };

	if (tp2.is_open()) {
		tp2.read((char*)&m_fichierEntente, sizeof(m_fichierEntente));
		tp2.read((char*)&m_solutionEntete, sizeof(m_solutionEntete));
		
		for (int i = 0; i <	m_fichierEntente.laby_noHeader_size/ sizeof(TP2LienCase); i++)
		{
			TP2LienCase lien;
			tp2.read((char*)&lien, sizeof(TP2LienCase));
			m_lienCase.push_back(lien);
		}

        // Si il y a une solution, il ajout au struct TP2EtapeChemin les données du fichier
        if (m_solutionEntete.number_case_travel > 0) {
            for (int i = 0; i < m_solutionEntete.number_case_travel; i++) {
                TP2EtapeChemin etape;
                tp2.read((char*)&etape, sizeof(TP2EtapeChemin));
                m_etapeChemin.push_back(etape);
            }
        }
    }
}

void TP2::ecrireSolution(const std::string filePath)
{
    if (m_etapeChemin.empty()) throw std::runtime_error("Aucune solution à écrire");

    std::ofstream tp2Sol(filePath, std::ios_base::binary);

    if (tp2Sol) {
        TP2SolutionEntete nouvelleSolution;
        nouvelleSolution.number_case_travel = m_etapeChemin.size();
        int liensOffset = sizeof(TP2FichierEntente) + sizeof(TP2SolutionEntete);
        nouvelleSolution.data_decalage_sinceStart = liensOffset + m_fichierEntente.laby_noHeader_size;

        TP2FichierEntente nouveauHeader = m_fichierEntente;
        nouveauHeader.file_size = nouvelleSolution.data_decalage_sinceStart + nouvelleSolution.number_case_travel * sizeof(TP2EtapeChemin);

        tp2Sol.write((char*)&nouveauHeader, sizeof(nouveauHeader));
        tp2Sol.write((char*)&nouvelleSolution, sizeof(nouvelleSolution));

        for (int i = 0; i < m_lienCase.size(); ++i) {
            TP2LienCase lien = m_lienCase[i];
            tp2Sol.write((char*)&lien, sizeof(lien));
        }

        for (int i = 0; i < m_etapeChemin.size(); ++i) {
            TP2EtapeChemin chemin = m_etapeChemin[i];
            tp2Sol.write((char*)&chemin, sizeof(chemin));
        }
    }
}

void TP2::solution() {
    int nombreCase = m_fichierEntente.laby_case_number;
    std::vector<char> visiter(nombreCase, 0);
    std::vector<int> precedent(nombreCase, -1);
    std::queue<uint16_t> file;

    visiter[m_fichierEntente.laby_case_startNumber] = 1;
    file.push(m_fichierEntente.laby_case_startNumber);

    while (!file.empty()) {
        uint16_t caseActuelle = file.front();
        file.pop();
        if (caseActuelle == m_fichierEntente.laby_case_endNumber) break;

        for (int i = 0; i < m_lienCase.size(); ++i) {
            TP2LienCase lien = m_lienCase[i];
            if (lien.case_origine == caseActuelle && !visiter[lien.case_destination]) {
                visiter[lien.case_destination] = 1;
                precedent[lien.case_destination] = caseActuelle;
                file.push(lien.case_destination);
            }
            if (lien.case_destination == caseActuelle && !visiter[lien.case_origine]) {
                visiter[lien.case_origine] = 1;
                precedent[lien.case_origine] = caseActuelle;
                file.push(lien.case_origine);
            }
        }
    }

    m_etapeChemin.clear();
    for (int numeroCase = m_fichierEntente.laby_case_endNumber; numeroCase != -1; numeroCase = precedent[numeroCase]) {
        TP2EtapeChemin chemin;
        chemin.numero_case = numeroCase;
        m_etapeChemin.push_back(chemin);
    }
    // Inverse le m_etapeChemin pour pemettre le chemin du debut a la fin et non de la fin au début
    std::reverse(m_etapeChemin.begin(), m_etapeChemin.end());
}

void TP2::afficherLiens()
{
    std::cout << "Liens" << std::endl;
    for (int i = 0; i < m_lienCase.size(); ++i) {
        TP2LienCase& lien = m_lienCase[i];
        std::cout << lien.case_origine << " - " << lien.case_destination << '\n';
    }
}

void TP2::afficherSolution()
{
    std::cout << "Solution" << std::endl;
    for (int i = 0; i < m_etapeChemin.size(); ++i) {
        std::cout << m_etapeChemin[i].numero_case
            << (i + 1 < m_etapeChemin.size() ? "-" : "");
    }
    std::cout << '\n';
}