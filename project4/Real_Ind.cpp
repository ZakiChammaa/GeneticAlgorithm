//Zaki Chammaa
//6584233

#include "Real_Ind.h"

real_ind::real_ind(int x, double y)		// overloaded constructor
{
    double random;
	size_genotype = x;
	alpha = y;
	age = 0;

    for(int i = 0; i < size_genotype; i++)
    {
		random = ((65.536 * rand() / RAND_MAX)) - 32.768;	// equation that generates random numbers
		real_geno.push_back(random);		// storing the random numbers in real_geno
    }

    fitness();	// assigning the value of answer in fitness() to the variable Fitness
}

void real_ind::fitness()	// function which computes the equation for fitness
{
    double sum1 = 0.0;
    double sum2 = 0.0;
    double answer = 0.0;

    for(int i = 0; i < size_genotype; i++)	// computing the first summation of the equation
		sum1 = (real_geno.at(i) * real_geno.at(i)) + sum1;

    for(int i = 0; i < size_genotype; i++)	// computing the second equation of the summation
		sum2 = cos(2.0 * PI * real_geno.at(i)) + sum2;

    sum1 = -0.2 * sqrt(sum1 / size_genotype);	// summation now holds the value: -0.2 * sqrt(sum1 / size_genotype)
	sum2 = sum2 / size_genotype;	// updating the value of sum2 to: sum2 / size_genotype

    answer = -20.0 * exp(sum1) - exp(sum2) + 20.0 + exp(1.0);	// computing the equation for fitness

	Fitness = answer;
}
