//Zaki Chammaa
//6584233

#ifndef INT_IND_H
#define INT_IND_H

#include"Individual.h"

class int_ind : public individual
{
	vector <int> int_geno;
    int intFitness;
	int totalWeight;

	public:

		int_ind();
		int_ind(int);

		virtual void fitness();
		friend vector<int_ind> operator+(int_ind &i1 , int_ind &i2);

	friend class population;
	friend class evolution;

};



#endif