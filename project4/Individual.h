//Zaki Chammaa
//6584233

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include<algorithm>
using namespace std;
const double PI = 3.1415926;
class population;
class individual
{
	protected:
	
	int size_genotype;
	int size_individual;
	double alpha;	int age;

    public:

		virtual void fitness() = 0;
};
#endif