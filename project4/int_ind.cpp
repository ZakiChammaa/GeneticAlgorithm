//Zaki Chammaa
//6584233

#include"Int_Ind.h"

int_ind::int_ind(int x)
{
	int random;
	size_genotype = x;

	do
	{
		int_geno.clear();

		for(int i = 0; i < size_genotype; i++)
		{
			random = (rand() % 30) + 1;
			int_geno.push_back(random);		// storing the random numbers in int_geno
		}

		fitness();

	}while(totalWeight >= 5000);

} 

void int_ind::fitness()
{
	int weight[15] = {25, 20, 31, 45, 15, 32, 28, 26, 13, 17, 19, 38, 21, 38, 29}; 
	int value[15] = {300 ,220 ,350 ,405 ,215 ,328 ,257 ,339 ,223 ,222 ,207 ,360 ,268 ,341 ,301};

	int totalValue = 0;
	totalWeight = 0;

		for(int i = 0; i < 15; i++)
		{
			totalValue = totalValue + (int_geno[i] * value[i]);
			totalWeight = totalWeight + (int_geno[i] * weight[i]);
		}
	
		intFitness = totalValue;
		//cout << totalValue << " " << totalWeight << endl;
}

