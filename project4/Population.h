//Zaki Chammaa
//6584233

#ifndef POPULATION_H
#define POPULATION_H

#include "Real_Ind.h"
#include"Int_Ind.h"
#include "bool_ind.h"


class population
{
	//real vectors
	vector<real_ind> candidate;
	vector<real_ind> parents;
	vector<real_ind> tournament;
	vector<real_ind> eliteList;

	//int vectors
	vector <int_ind> intCandidate;
	vector <int_ind> intParents;
	vector <int_ind> intTournament;
	vector<int_ind> intEliteList;

	//bool vectors
	vector<bool_ind> boolCandidate;
	vector<bool_ind> boolParents;
	vector<bool_ind> boolTournament;
	vector<bool_ind> boolEliteList;

	//temp vectors
	vector<int_ind> tempInt;
	vector<bool_ind> tempBool;

    int sizeOf_individual;
    int sizeOf_genotype;
	double alpha;
	int a;

    public:

    population();
    population(int, int, double, int);
	population(int, int, int);
	population(int, int, int, bool);

	bool sol_found();
	bool isEqual(double, double);

	void get_best();
	void best_int();
	void best_bool();

	int_ind bestIntReturn();
	bool_ind bestBoolReturn();

	void parentSelection();
	void parentSelecInt();
	void parentSelecBool();


	void childrenSelection(int);
	void childSelecInt(int);
	void childSelecBool(int);


	void elite();
	void intElite();
	void boolElite();

	population operator!();							// Mutates the population; returns self, which is now a new population
	population operator&();
	population operator~();

	friend class evolution;
};

#endif