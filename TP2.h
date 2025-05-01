#ifndef TP2_H
#define TP2_H

#pragma once

#include <vector>
#include <string>

#include "Header.h"
#include "IAffichable.h"
#include "ILectureEcriture.h"

class TP2 : public IAffichable, public ILectureEcriture
{
private:
	TP2FichierEntente m_fichierEntente;
	TP2SolutionEntete m_solutionEntete;
	std::vector<TP2LienCase> m_lienCase;
	std::vector<TP2EtapeChemin> m_etapeChemin;

public:
	void lireLabyrinthe(const std::string filePath);
	void ecrireSolution(const std::string filePath);
	void solution();
	void afficherLiens();
	void afficherSolution();
	void afficherDonneesFichier();
};

#endif