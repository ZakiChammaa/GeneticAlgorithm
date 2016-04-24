//Zaki Chammaa
//6584233

#ifndef BOOL_IND_H
#define BOOL_IND_H

#include"Individual.h"

class bool_ind : public individual
{
	vector <int> bool_geno;
    int boolFitness;
	int totalWeight;

	public:

		bool_ind();
		bool_ind(int);

		virtual void fitness();

		friend vector<bool_ind> operator-(bool_ind &i1 , bool_ind &i2);

	friend class population;
	friend class evolution;
};

#endif