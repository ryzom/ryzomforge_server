#include "simulation_random.h"
#include "nel/misc/debug.h"

//
// Implementation of a random number generator that draws from a
// gaussian distribution.  The underlying (uniform deviate)
// pseudorandom number generator is the Park and Miller "Minimum
// standard" generator with Bayes-Durham shuffle
//
// Copyright (c) 2001 Wesley H. Huang.  All rights reserved.
//
#include <math.h>
//#include <rand.h>


// default random generator seed (nothing special about this number
// except that it's not 0)
const long defaultSeed = 18846224; 
long pmRandGenSeed = defaultSeed;

// set the seed (optional)
void pmRandSeed(long s)
{
	if (s == 0) // can't use 0 as a seed
		pmRandGenSeed = defaultSeed;	// use the default
	else
		pmRandGenSeed = s;
}
 
// parameters for the random number generator
const long a = 16807;
const long m = 2147483647;
const long q = m/a;		// 127773
const long r = m % a;		// 2836
const long pmRandMax = m;

// Park and Miller's "Minimal Standard" generator using Schrage's
// method to do the computation in 32 bit arithmetic without overflow.
//
// This is a multiplicative congruential generator: I_{j+1} = a I_j mod m
// using the above constants (which are very carefully picked).
//
// The result is an integer between 1 and m-1 inclusive.
//
// Reference: Numerical Recipes in C, 2nd ed, pg 278.
long pmRand()
{
	long k = pmRandGenSeed/q;
	pmRandGenSeed = a*(pmRandGenSeed - k*q) - r*k;
	if (pmRandGenSeed < 0)
		pmRandGenSeed += m;
	return pmRandGenSeed;
}

// the Bayes-Durham shuffle
long pmRandShuffle()
{
	const int size = 32;
	const long div = 1 + (pmRandMax-1)/size;
	static bool initialized = false;
	static long rn[size];
	static long next;
	int index;

	if (!initialized)
	{
		int k;
		for (k= 0; k < size; k++) // warm up
			pmRand();
		for (k= 0; k < size; k++) // fill table
			rn[k] =pmRand();
		next = pmRand();
		initialized = true;
	}
	index = next/div;		// find out which table entry to use next
	next = rn[index];		// that random nember determines the next index
	rn[index] = pmRand();		// refill the table slot
	return next;			// return the random number
}
  
// 
// This is a simple but pretty good random number generator.
//
// Returns a floating point number in (0.0, 1.0)
float myRand()
{
	return pmRandShuffle()/(pmRandMax + 1.0f);
}

void myRandSeed(long s)
{
	pmRandSeed(s);
}

// returns a number drawn from the exponential distribution with the given mean
float exponential( float mean )
{
	float uniform = myRand();

	nlassert( uniform < 1.0f );
	float exponential = -logf( 1.0f - uniform ) * mean;

//	nldebug( "uniform rand: %.2f, exponential rand: %.2f", uniform, exponential );
	return exponential;
}

// returns a number drawn from a gaussian distribution with the
//	specified mean and standard deviation
float gaussian(float mean, float stdev)
{
	static bool cached = false;
	static float extra;  	// the extra number from a 0 mean unit stdev gaussian

	if (cached)
	{
		cached = false;
		return extra*stdev + mean;
	}
	else
	{
		// pick a random point in the unit circle (excluding the origin)
		float a,b,c;
		do
		{
			a = 2.0f*myRand()-1.0f;
			b = 2.0f*myRand()-1.0f;
			c = a*a + b*b;
		}
		while (c >= 1.0f || c == 0.0);

		// transform it into two values drawn from a gaussian
		float t = sqrtf(-2.0f*logf(c)/c);
		extra = t*a;
		cached = true;
		return t*b*stdev + mean;
	}
}
