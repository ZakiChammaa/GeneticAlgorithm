//Zaki Chammaa	
//6584233

#ifndef REAL_IND_H
#define REAL_IND_H

#include"Individual.h"

class real_ind: public individual
{
	vector <double> real_geno;
    double Fitness;

	public:

	real_ind();
	real_ind(int, double);

	virtual void fitness();

	friend real_ind operator!(real_ind &test);
	friend vector<real_ind> operator*(real_ind &i1 , real_ind &i2);

	friend class population;
	friend class evolution;
};

#endif