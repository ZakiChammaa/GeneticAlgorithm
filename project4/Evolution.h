//Zaki Chammaa
//6584233

#ifndef EVOLUTION_H
#define EVOLUTION_H

#include"Population.h"

class evolution
{
	int sizeGenotype, sizeInd, generation, a;
	double alpha;

	public:
		evolution();
		evolution(int, int, int, double, int);
		void doEvolution();
		void doIntEvolution();
		void doBoolEvolution();

};
#endif