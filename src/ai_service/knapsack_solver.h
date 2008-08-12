/** \file subset_sum_solver.h
 *
 * $Id: knapsack_solver.h,v 1.1 2005/06/27 11:57:53 vuarand Exp $
 */

#ifndef RYAI_KNAPSACK_SOLVER_H
#define RYAI_KNAPSACK_SOLVER_H

//////////////////////////////////////////////////////////////////////////////
// IKnapsackContext                                                          //
//////////////////////////////////////////////////////////////////////////////

class IKnapsackContext
{
public:
	virtual ~IKnapsackContext() { }
	virtual float weight(size_t i) = 0;
	virtual float value(size_t i) = 0;
	virtual size_t size() = 0;
};

//////////////////////////////////////////////////////////////////////////////
// CKnapsackSolver                                                          //
//////////////////////////////////////////////////////////////////////////////

/// This class resolves the knapsack problem, in french "probleme du sac a
/// dos"
class CKnapsackSolver
{
public:
	enum Algorithm
	{
		UndefinedAlgorithm,
		Optimal,
		FullAddCheck,
		AddCheck,
		FastAddCheck,
		FullSingleReplace,
		SingleReplace,
		FastSingleReplace,
		VeryFastSingleReplace,
	//- /!\ Algorithms below don't respect constraints
		TakeAll
	};
	static std::string toString(Algorithm a);
	static CKnapsackSolver::Algorithm fromString(std::string const& a);
private:
	IKnapsackContext* _Context;
	bool* _Take;
	bool _AllocatedTake;
	float _WBest;
	float _VBest;
	float _WMax;
public:
	explicit CKnapsackSolver(IKnapsackContext* context, bool* take = NULL);
	virtual ~CKnapsackSolver();
	bool take(size_t i);
	float totalWeight();
	float totalValue();
	float totalFreeWeight();
	
	/// @param wMax Max weight that can be taken
	/// @note Not thread safe
	void optimize(float wMax, Algorithm algorithm = Optimal);
private:
	float weight(size_t i);
	float value(size_t i);
	size_t size();
	/// @name Algorithms entry points
	//@{
	void optimizeOptimal();
	void optimizeFullAddCheck();
	void optimizeAddCheck();
	void optimizeFastAddCheck();
	void optimizeFullSingleReplace();
	void optimizeSingleReplace();
	void optimizeFastSingleReplace();
	void optimizeVeryFastSingleReplace();
	void optimizeTakeAll();
	//@}
	/// @name Algorithms helper functions
	//@{
	void optimizeOptimalRec(int i, float w, float v, bool* take);
	//@}
};

//////////////////////////////////////////////////////////////////////////////
// CKnapsackContext                                                         //
//////////////////////////////////////////////////////////////////////////////

class CKnapsackContext
: public IKnapsackContext
{
	size_t _Size;
	float* _Weights;
	float* _Values;
public:
	CKnapsackContext(size_t size, float* weights, float* values);
	virtual float weight(size_t i);
	virtual float value(size_t i);
	virtual size_t size();
};

#endif
