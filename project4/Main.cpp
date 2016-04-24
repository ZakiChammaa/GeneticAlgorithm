//Zaki Chammaa
//6584233

#include "Int_Ind.h"
#include"Real_Ind.h"
#include"bool_ind.h"
#include "Population.h"
#include "Evolution.h"

int main()
{ 
    srand(time(0));

	evolution e1(15, 100, 100, 0.8, 1);	//(size of individuals, number of individuals, generation, alpha, mutation type)

	cout << "Processing the integer population with the swap mutation." << endl;
	cout << "This will take a few seconds..." << endl;
	cout << endl;

	e1.doIntEvolution();

	cout << endl;
	cout << "Processing the boolean population with the swap mutation." << endl;
	cout << "This will take a few seconds..." << endl;
	cout << endl;

	e1.doBoolEvolution();

	evolution e2(15, 100, 100, 0.8, 2);

	cout << endl;
	cout << "Processing the integer population with the uniform distribution mutation." << endl;
	cout << "This will take a few seconds..." << endl;
	cout << endl;

	e2.doIntEvolution();

	cout << endl;
	cout << "Processing the boolean population with the random flip mutation." << endl;
	cout << "This will take a few seconds..." << endl;
	cout << endl;

	e2.doBoolEvolution();
	cout << endl;



	

	system("PAUSE");

    return 0;
}

