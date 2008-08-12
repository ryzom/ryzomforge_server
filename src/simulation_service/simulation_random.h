#ifndef SIMULATION_RANDOM_H
#define SIMULATION_RANDOM_H

// returns a number drawn from the exponential distribution with the given mean
float exponential( float mean = 1.0f );

// returns a number drawn from a gaussian distribution with the
// specified mean and standard deviation
float gaussian( float mean, float stdev );

// This is a simple but pretty good random number generator.
float myRand();

// set the seed (optional)
void myRandSeed(long s);

// Park and Miller's "Minimal Standard" generator using Schrage's
// method to do the computation in 32 bit arithmetic without overflow.
long pmRand();

// Bayes-Durham shuffle
long pmRandShuffle();

// set the seed (optional)
void pmRandSeed(long s);

#endif	// SIMULATION_RANDOM_H
