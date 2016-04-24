//Zaki Chammaa
//6584233

#include"Evolution.h"

evolution::evolution(int S_genotype, int S_ind, int S_genereation, double publicAlpha, int number)
{
	sizeGenotype = S_genotype;
	sizeInd = S_ind;
	generation = S_genereation;
	alpha = publicAlpha;
	a = number;
}

void evolution::doEvolution()
{
	population p(sizeGenotype, sizeInd, alpha, a);

	int newSize;
	int maxAge = generation / 100;

	//ofstream output("bonus.csv");

	for(int i = 0; i < generation; ++i)
	{
		p.parentSelecInt();
		p.elite();
		newSize = p.parents.size() - p.eliteList.size();

		//this for loop is for the split exchange crossover

		/*for(int j = 0; j < newSize; j += 2)
		{
			vector<real_ind> temp;
			temp = (p.parents[j] * p.parents[j+1]);
			p.candidate.push_back(temp[0]);
			p.candidate.push_back(temp[1]);
		}*/


		//this for loop is for the linear combination
		for(int j = 0; j < newSize; j += 2)
		{
			p.candidate.push_back((p.parents[j] * p.parents[j+1])[0]);
			p.candidate.push_back((p.parents[j] * p.parents[j+1])[1]);
		}

		!p;

		for(int j = 0; j < p.parents.size(); ++j)
			p.candidate.push_back(p.parents[j]);

		p.parents.clear();

		for(int j = 0; j < p.candidate.size(); ++j)
		{
			if(p.candidate[j].age >= maxAge)
			{
				p.candidate.erase(p.candidate.begin() + j);
				j--;
			}
		}

		p.childrenSelection(3);

		//output << i+1 << "," << p.get_best2() << endl;
		cout << "Best in generation " << i+1 << " : "; 
		p.get_best();
		cout << endl;

		if(p.sol_found())
			break;
	}
}

void evolution::doIntEvolution()
{
	population p_int(sizeGenotype, sizeInd, a);

		int newSize;
		int maxAge = 10;

	for(int i = 0; i < generation; ++i)
	{
		//cout << "Generation: " << i+1 << endl;
		p_int.parentSelecInt();
		p_int.intElite();
		newSize = p_int.intParents.size() - p_int.intEliteList.size();

		for(int j = 0; j < newSize; j += 2)
		{
			vector<int_ind> temp;
			temp = (p_int.intParents[j] + p_int.intParents[j+1]);
			p_int.intCandidate.push_back(temp[0]);
			p_int.intCandidate.push_back(temp[1]);
		}

		&p_int;

		for(int j = 0; j < p_int.intParents.size(); ++j)
			p_int.intCandidate.push_back(p_int.intParents[j]);

		p_int.intParents.clear();

		for(int j = 0; j < p_int.intCandidate.size(); ++j)
		{
			if(p_int.intCandidate[j].age >= maxAge)
			{
				p_int.intCandidate.erase(p_int.intCandidate.begin() + j);
				j--;
			}
		}

		p_int.childSelecInt(3);

		p_int.tempInt.push_back(p_int.bestIntReturn());

	}

	int best = p_int.tempInt[0].intFitness;
    int position = 0;

	for(int i = 0; i < p_int.tempInt.size(); ++i)	//this loop finds the smallest fitness											
    {                                           //and its position
        if(best < p_int.tempInt[i].intFitness)
        {
			best = p_int.tempInt[i].intFitness;
            position = i;
        }
    }

	cout << "Best fitness is: " << best << " with a weight of " << p_int.tempInt[position].totalWeight << endl;
	cout << "The genotype is: ";

	for(int i = 0; i < 15; i++)
		cout << p_int.tempInt[position].int_geno[i] << " ";

	cout << endl;
}

void evolution::doBoolEvolution()
{
	bool dummy = true;

	int maxAge = 10;
	int newSize;

	population p_bool(sizeGenotype, sizeInd, a, dummy);

	for(int i = 0; i < generation; ++i)
	{
		//cout << "Generation: " << i+1 << endl;
		p_bool.parentSelecBool();
		p_bool.boolElite();

		newSize = p_bool.boolParents.size() - p_bool.boolEliteList.size();


		for(int j = 0; j < newSize; j += 2)
		{
			vector<bool_ind> temp;
			temp = (p_bool.boolParents[j] - p_bool.boolParents[j+1]);
			p_bool.boolCandidate.push_back(temp[0]);
			p_bool.boolCandidate.push_back(temp[1]);
		}

		//cout << p.intCandidate[i].intFitness << endl;
		
		~p_bool;

		for(int j = 0; j < p_bool.boolParents.size(); ++j)
			p_bool.boolCandidate.push_back(p_bool.boolParents[j]);

		p_bool.boolParents.clear();

		for(int j = 0; j < p_bool.intCandidate.size(); ++j)
		{
			if(p_bool.boolCandidate[j].age >= maxAge)
			{
				p_bool.boolCandidate.erase(p_bool.boolCandidate.begin() + j);
				j--;
			}
		}

		p_bool.childSelecBool(3);

		p_bool.tempBool.push_back(p_bool.bestBoolReturn());
	}

	int best = p_bool.tempBool[0].boolFitness;
    int position = 0;

	for(int i = 0; i < p_bool.tempBool.size(); ++i)	//this loop finds the smallest fitness											
    {                                           //and its position
        if(best < p_bool.tempBool[i].boolFitness)
        {
			best = p_bool.tempBool[i].boolFitness;
            position = i;
        }
    }

	cout << "Best fitness is: " << best << " with a weight of " << p_bool.tempBool[position].totalWeight << endl;
	cout << "The genotype is: ";

	for(int i = 0; i < 15; i++)
		cout << p_bool.tempBool[position].bool_geno[i] << " ";

	cout << endl;
}