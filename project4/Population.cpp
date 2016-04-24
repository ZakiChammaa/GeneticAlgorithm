//Zaki Chammaa
//6584233

#include "Population.h"

population::population(int x, int y, double z, int w)
{
    sizeOf_genotype = x;	//making sizeOf_genotype accessible outside the class
    sizeOf_individual = y;	//making sizeOf_individual accessible outside the class
	alpha = z;
	a = w;

    for(int i = 0; i < y; i++)	//this loop generates y individuals
    {
        real_ind *count = new real_ind(x, z);
        candidate.push_back(*count);
        delete count;
    }
}

population::population(int x, int y, int z)
{
	sizeOf_genotype = x;	//making sizeOf_genotype accessible outside the class
    sizeOf_individual = y;	//making sizeOf_individual accessible outside the class
	alpha = z;

	for(int i = 0; i < y; ++i)
	{
        int_ind *count = new int_ind(y);
        intCandidate.push_back(*count);
        delete count;
    }
}

population::population(int x, int y, int z, bool dummy)
{
	sizeOf_genotype = x;	//making sizeOf_genotype accessible outside the class
    sizeOf_individual = y;	//making sizeOf_individual accessible outside the class
	alpha = z;

	for(int i = 0; i < y; ++i)
	{
        bool_ind *count = new bool_ind(y);
        boolCandidate.push_back(*count);
        delete count;
    }
}

//bool
void population::best_bool()
{
	int best = boolCandidate[0].boolFitness;
    int position = 0;

    for(int i = 0; i < sizeOf_individual; ++i)	//this loop finds the smallest fitness											
    {                                           //and its position
        if(best < boolCandidate[i].boolFitness)
        {
			best = boolCandidate[i].boolFitness;
            position = i;
        }
    }


	cout << "Best: " << best << " $     Weight: " << boolCandidate[position].totalWeight << " Kg";
}

bool_ind population::bestBoolReturn()
{
	int best = boolCandidate[0].boolFitness;
    int position = 0;

	for(int i = 0; i < sizeOf_individual; i++)
	{
		if(boolCandidate[i].totalWeight > 200)
			boolCandidate[i].boolFitness = 0;
	}

    for(int i = 0; i < sizeOf_individual; ++i)	//this loop finds the smallest fitness											
    {                                           //and its position
        if(best < boolCandidate[i].boolFitness)
        {
			best = boolCandidate[i].boolFitness;
            position = i;
        }
    }

	return boolCandidate[position];
}

population population::operator~()
{
	int temp, r1, r2;

	if(a == 1)
	{
		for(int i = 0; i < sizeOf_individual; ++i)
		{
			r1 = rand() % 15;
			r2 = rand() % 15;

			temp = boolParents[i].bool_geno[r1];
			boolParents[i].bool_geno[r1] = boolParents[i].bool_geno[r2];
			boolParents[i].bool_geno[r2] = temp;

			boolParents[i].fitness();

			if(boolParents[i].totalWeight >= 200)	//here is where i set fitness = 0
				boolParents[i].boolFitness = 0;
		}	
	}

	if(a == 2)
	{
		for(int i = 0; i < sizeOf_individual; ++i)
		{
			for(int j = 0; j < (sizeOf_genotype); ++j)
			{
				int r = rand() % 15;

				if(boolParents[i].bool_geno[r] == 0)
					boolParents[i].bool_geno[r] = 1;
				if(boolParents[i].bool_geno[r] == 1)
					boolParents[i].bool_geno[r] = 0;
			}

			boolParents[i].fitness();

			if(boolParents[i].totalWeight >= 200)	//here is where i set fitness = 0
				boolParents[i].boolFitness = 0;
		}
	}
	return *this;
}

void population::parentSelecBool()		//this one does roulette, i used the same as for real
{
	int r;
	int totalFitness;

	for(int i = 0; i < boolCandidate.size(); ++i)
		boolCandidate[i].fitness();

	while(boolCandidate.size() != 0)
	{
		totalFitness = 0;

		for(int i = 0; i < boolCandidate.size(); ++i)
		{
			totalFitness = totalFitness + boolCandidate[i].boolFitness;
		}
	
		r = rand() % totalFitness;
		totalFitness = 0;

		for(int i = 0; i < boolCandidate.size(); ++i)
		{
			totalFitness = totalFitness + boolCandidate[i].boolFitness;

			if(totalFitness > r)
			{
				boolParents.push_back(boolCandidate[i]);
				boolCandidate.erase(boolCandidate.begin() + (i));
				break;
			}
		}
	} 
}

void population::childSelecBool(int k)		//tournament
{
	int worstPosition = 0;
	int r;


	while(boolCandidate.size() != sizeOf_individual)		//this is to stop at half the size of population
	{
		int smallest = 5000;
		for(int j = 0; j < k; ++j)
		{
			r = rand() % boolCandidate.size();

			boolTournament.push_back(boolCandidate[r]);

			if(smallest > boolTournament[j].boolFitness)
			{
				smallest = boolTournament[j].boolFitness;
				worstPosition = r;
			}
		}
		boolCandidate.erase(boolCandidate.begin() + worstPosition);
		boolTournament.clear();
	}

	for(int i = 0; i < boolCandidate.size(); ++i)
		boolCandidate[i].age++;
}
vector<bool_ind> operator-(bool_ind &i1 , bool_ind &i2)
{
	bool_ind child1(i1.size_genotype), child2(i1.size_genotype);
	vector<bool_ind> children;

	int splitPos = rand() % (i1.size_genotype-1 )+ 1;

	for(int i = 0; i < splitPos; i++)
	{
		child1.bool_geno[i] = i1.bool_geno[i];
		child2.bool_geno[i] = i2.bool_geno[i];
	}

	for(int i = splitPos; i < i1.size_genotype; i++)
	{
		child1.bool_geno[i] = i2.bool_geno[i];
		child2.bool_geno[i] = i1.bool_geno[i];
	}

	child1.fitness();
	child2.fitness();

	if(child1.totalWeight >= 200)
		child1.boolFitness = 0;

	if(child2.totalWeight >= 200)
		child2.boolFitness = 0;

	children.push_back(child1);
	children.push_back(child2);


	children[0].age = 0;
	children[1].age = 0;

	return children;
}

void population::boolElite()
{
	bool flag = true;
	bool_ind tempElite(sizeOf_genotype);
	tempElite = boolParents[0];

	while(flag == true)
	{
		for(int i = 0; i < boolParents.size(); ++i)
		{
			if(boolParents[i].boolFitness > tempElite.boolFitness)
				tempElite.boolFitness = boolParents[i].boolFitness;
		}

		if(intEliteList.size() < 10)
		{
			for(int i = 0; i < boolEliteList.size(); ++i)		
			{
				if(tempElite.boolFitness == boolEliteList[i].boolFitness)
				{
					flag = false;
					break;
				}
			}

			if(flag == true)
				boolEliteList.push_back(tempElite);
			else
				break;
		}

		else
		{
			int largest = boolEliteList[0].boolFitness;
			int worstPosition = 0;

			for(int i = 0; i < boolEliteList.size(); ++i)
			{
				if(largest > boolEliteList[i].boolFitness)
				{
					largest = boolEliteList[i].boolFitness;
					worstPosition = i;
				}
			}

			if(largest > tempElite.boolFitness)
				break;
			else
			{
				for(int i = 0; i < boolEliteList.size(); ++i)		
				{
					if(tempElite.boolFitness == boolEliteList[i].boolFitness)
					{
						flag = false;
						break;
					}
				}

				if(flag == true)
				{
					boolEliteList.erase(boolEliteList.begin() + worstPosition);
					boolEliteList.push_back(tempElite);
				}
				else
					break;
			}
		}
		break;
	}

	for(int i = 0; i < boolEliteList.size(); ++i)
		boolCandidate.push_back(boolEliteList[i]);
}



//Integer
void population::best_int()
{
	int best = intCandidate[0].intFitness;
    int position = 0;

    for(int i = 0; i < sizeOf_individual; ++i)	//this loop finds the smallest fitness											
    {                                           //and its position
        if(best < intCandidate[i].intFitness)
        {
			best = intCandidate[i].intFitness;
            position = i;
        }
    }


	cout << "Best: " << best << " $     Weight: " << intCandidate[position].totalWeight << " Kg";
}

int_ind population::bestIntReturn()
{
	int best = intCandidate[0].intFitness;
    int position = 0;

    for(int i = 0; i < sizeOf_individual; ++i)	//this loop finds the smallest fitness											
    {                                           //and its position
        if(best < intCandidate[i].intFitness)
        {
			best = intCandidate[i].intFitness;
            position = i;
        }
    }

	return intCandidate[position];
}

population population::operator&()
{
	int temp, r1, r2;

	if(a == 1)
	{
		for(int i = 0; i < sizeOf_individual; ++i)
		{
			r1 = rand() % 15;
			r2 = rand() % 15;

			temp = intParents[i].int_geno[r1];
			intParents[i].int_geno[r1] = intParents[i].int_geno[r2];
			intParents[i].int_geno[r2] = temp;

			intParents[i].fitness();

			if(intParents[i].totalWeight >= 5000)	//here is where i set fitness = 0
				intParents[i].intFitness = 0;
		}
		
	}

	if(a == 2)
	{
		int pm = 10;
		int number;
		random_device rnd;

		for(int i = 0; i < sizeOf_individual; ++i)
		{
			for(int j = 0; j < (sizeOf_genotype); ++j)
			{
				if(rand() % 100 < pm)
				{
					normal_distribution <double> x(intParents[i].int_geno[j],2);

					repeat:
						number = x(rnd);
						if(number < 0)
							number = number * -1;

						if(number > 30 || number == 0)
							goto repeat;

						intParents[i].int_geno[j] = number;	
				}	
			}
			intParents[i].fitness();

			if(intParents[i].totalWeight >= 5000)	//here is where i set fitness = 0
				intParents[i].intFitness = 0;
		}
	}
	return *this;
}

void population::parentSelecInt()		//this one does roulette, i used the same as for real
{
	int r;
	int totalFitness;

	for(int i = 0; i < intCandidate.size(); ++i)
		intCandidate[i].fitness();

	while(intCandidate.size() != 0)
	{
		totalFitness = 0;

		for(int i = 0; i < intCandidate.size(); ++i)
		{
			totalFitness = totalFitness + intCandidate[i].intFitness;
		}
	
		r = rand() % totalFitness;
		totalFitness = 0;

		for(int i = 0; i < intCandidate.size(); ++i)
		{
			totalFitness = totalFitness + intCandidate[i].intFitness;

			if(totalFitness > r)
			{
				intParents.push_back(intCandidate[i]);
				intCandidate.erase(intCandidate.begin() + (i));
				break;
			}
		}
	} 
}

void population::childSelecInt(int k)		//tournament
{
	int worstPosition = 0;
	int r;
	int smallest;


	while(intCandidate.size() != sizeOf_individual)		//this is to stop at half the size of population
	{
		//int_ind temp(sizeOf_genotype); 
		//temp = *(max_element(intCandidate.begin(), intCandidate.end()));

		smallest = 100000;

		for(int j = 0; j < k; ++j)
		{
			r = rand() % intCandidate.size();

			intTournament.push_back(intCandidate[r]);

			if(smallest > intTournament[j].intFitness)
			{
				smallest = intTournament[j].intFitness;
				worstPosition = r;
			}
		}
		intCandidate.erase(intCandidate.begin() + worstPosition);
		intTournament.clear();
	}

	//for(int i = 0; i < intCandidate.size();i++)
		//cout << intCandidate[i].intFitness << endl;



	for(int i = 0; i < intCandidate.size(); ++i)
		intCandidate[i].age++;
}
vector<int_ind> operator+(int_ind &i1 , int_ind &i2)
{
	int_ind child1(i1.size_genotype), child2(i1.size_genotype);
	vector<int_ind> children;

	int splitPos = rand() % (i1.size_genotype-1 )+ 1;

	for(int i = 0; i < splitPos; i++)
	{
		child1.int_geno[i] = i1.int_geno[i];
		child2.int_geno[i] = i2.int_geno[i];
	}

	for(int i = splitPos; i < i1.size_genotype; i++)
	{
		child1.int_geno[i] = i2.int_geno[i];
		child2.int_geno[i] = i1.int_geno[i];
	}

	child1.fitness();
	child2.fitness();

	if(child1.totalWeight >= 5000)
		child1.intFitness = 0;

	if(child2.totalWeight >= 5000)
		child2.intFitness = 0;

	children.push_back(child1);
	children.push_back(child2);


	children[0].age = 0;
	children[1].age = 0;

	return children;
}

void population::intElite()
{
	bool flag = true;
	int_ind tempElite(sizeOf_genotype);
	tempElite = intParents[0];

	while(flag == true)
	{
		for(int i = 0; i < intParents.size(); ++i)
		{
			if(intParents[i].intFitness > tempElite.intFitness)
				tempElite.intFitness = intParents[i].intFitness;
		}

		if(intEliteList.size() < 10)
		{
			for(int i = 0; i < intEliteList.size(); ++i)		
			{
				if(tempElite.intFitness == intEliteList[i].intFitness)
				{
					flag = false;
					break;
				}
			}

			if(flag == true)
				intEliteList.push_back(tempElite);
			else
				break;
		}

		else
		{
			double largest = intEliteList[0].intFitness;
			int worstPosition = 0;

			for(int i = 0; i < intEliteList.size(); ++i)
			{
				if(largest > intEliteList[i].intFitness)
				{
					largest = intEliteList[i].intFitness;
					worstPosition = i;
				}
			}

			if(largest > tempElite.intFitness)
				break;
			else
			{
				for(int i = 0; i < intEliteList.size(); ++i)		
				{
					if(tempElite.intFitness == intEliteList[i].intFitness)
					{
						flag = false;
						break;
					}
				}

				if(flag == true)
				{
					intEliteList.erase(intEliteList.begin() + worstPosition);
					intEliteList.push_back(tempElite);
				}
				else
					break;
			}
		}
		break;
	}


	for(int i = 0; i < intEliteList.size(); ++i)
		intCandidate.push_back(intEliteList[i]);
}

//Real
void population::get_best()		//function finds the best fitness in a population
{
    double smallest = candidate[0].Fitness;
    int position = 0;

	for(int i = 0; i < sizeOf_individual; ++i)	//this loop finds the smallest fitness											
    {                                           //and its position
        if(smallest > candidate[i].Fitness)
        {
            smallest = candidate[i].Fitness;
            position = i;
        }
    }

	cout << smallest << endl;
}

population population::operator!()
{
	double pm = 10.0;
	double mean, std;
	random_device rnd;

	for(int i = 0; i < sizeOf_individual; ++i)
	{
		for(int j = 0; j < (sizeOf_genotype); ++j)
		{
			if(rand() % 100 < pm)
			{
				mean = parents[i].real_geno[j];
				std = fabs(parents[i].real_geno[j] / 10.0);
				normal_distribution <double> x(mean,std);
				double number = x(rnd);
				parents[i].real_geno[j] = number;
			}
		}

		parents[i].fitness();
	}

	return *this;
}

void population::parentSelection()		//selecting parents from the pool of individuals
										//roulette selection
{
	double r;

	while(candidate.size() != 0)
	{
		double totalFitness = 0.0;

		for(int i = 0; i < candidate.size(); ++i)
			totalFitness = totalFitness + candidate[i].Fitness;

		r = ((totalFitness * rand() / RAND_MAX));
		totalFitness = 0.0;

		for(int i = 0; i < candidate.size(); ++i)
		{
			totalFitness = totalFitness + candidate[i].Fitness;

			if(totalFitness > r)
			{
				parents.push_back(candidate[i]);
				candidate.erase(candidate.begin() + (i));
				break;
			}
		}
	}
}

void population::childrenSelection(int k)		//child selection that occurs after the crossover in main												//tournament selection
{
	int worstPosition = 0;

	while(candidate.size() != sizeOf_individual)
	{
		double largest = 0.0;
		for(int j = 0; j < k; ++j)
		{
			int r = rand() % candidate.size();
			tournament.push_back(candidate[r]);

			if(largest < tournament[j].Fitness)
			{
				largest = tournament[j].Fitness;
				worstPosition = r;
			}
		}
		candidate.erase(candidate.begin() + worstPosition);
		tournament.clear();
	}

	for(int i = 0; i < candidate.size(); ++i)
		candidate[i].age++;
}

bool population::sol_found()
{
	bool cond = false;

	for(int i = 0; i < sizeOf_individual; ++i)
	{
		if(isEqual(candidate[i].Fitness,0.0))
		{
			cout << "Solution Found: " << candidate[i].Fitness << endl;
			cond = true;
			break;
		}
	}
	return cond;
}

vector<real_ind> operator*(real_ind &i1 , real_ind &i2)
{

	//split exchange crossover

	/*int splitPos;
	real_ind child1(i1.size_genotype, i1.alpha), child2(i1.size_genotype, i1.alpha);
	vector<real_ind> children;

	splitPos = rand() % (i1.size_genotype-1 )+ 1;

	for(int i = 0; i < splitPos; i++)
	{
		child1.real_geno[i] = i1.real_geno[i];
		child2.real_geno[i] = i2.real_geno[i];
	}

	for(int i = splitPos; i < i1.size_genotype; i++)
	{
		child1.real_geno[i] = i2.real_geno[i];
		child2.real_geno[i] = i1.real_geno[i];
	}

	child1.Fitness = child1.fitness();
	child2.Fitness = child2.fitness();

	children.push_back(child1);
	children.push_back(child2);
	children[0].age = 0;
	children[1].age = 0;

	return children;
	*/

	//linear combination crossover
	real_ind child1(i1.size_genotype, i1.alpha), child2(i1.size_genotype, i1.alpha);
	vector<real_ind> children;

	for(int i = 0; i < i1.size_genotype; ++i)
	{
		child1.real_geno[i] = (i1.alpha * i1.real_geno[i]) + ((1 - i1.alpha) * i2.real_geno[i]);
		child2.real_geno[i] = (i1.alpha * i2.real_geno[i]) + ((1 - i1.alpha) * i1.real_geno[i]);
	}

	child1.fitness();
	child2.fitness();

	children.push_back(child1);
	children.push_back(child2);
	children[0].age = 0;
	children[1].age = 0;

	return children;
}

bool population::isEqual(double number1, double number2)
{
	if(fabs(number1 - number2) < numeric_limits<double>::epsilon( ))
		return true;
	else
		return false;
}

void population::elite()
{
	bool flag = true;
	real_ind tempElite(sizeOf_genotype, alpha);
	tempElite = parents[0];

	while(flag == true)
	{
		for(int i = 0; i < parents.size(); ++i)
		{
			if(parents[i].Fitness < tempElite.Fitness)
				tempElite.Fitness = parents[i].Fitness;
		}

		if(eliteList.size() < 10)
		{
			for(int i = 0; i < eliteList.size(); ++i)		
			{
				if(isEqual(tempElite.Fitness, eliteList[i].Fitness))
				{
					flag = false;
					break;
				}
			}

			if(flag == true)
				eliteList.push_back(tempElite);
			else
				break;
		}

		else
		{
			double largest = eliteList[0].Fitness;
			int worstPosition = 0;

			for(int i = 0; i < eliteList.size(); ++i)
			{
				if(largest < eliteList[i].Fitness)
				{
					largest = eliteList[i].Fitness;
					worstPosition = i;
				}
			}

			if(largest < tempElite.Fitness)
				break;
			else
			{
				for(int i = 0; i < eliteList.size(); ++i)		
				{
					if(isEqual(tempElite.Fitness, eliteList[i].Fitness))
					{
						flag = false;
						break;
					}
				}

				if(flag == true)
				{
					eliteList.erase(eliteList.begin() + worstPosition);
					eliteList.push_back(tempElite);
				}
				else
					break;
			}
		}
		break;
	}


	for(int i = 0; i < eliteList.size(); ++i)
		candidate.push_back(eliteList[i]);
}



