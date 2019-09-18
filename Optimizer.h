/*
 * Optimizer.h
 *
 *  Created on: Aug 6, 2019
 *      Author: yue
 */

#ifndef OPTIMIZER_H_
#define OPTIMIZER_H_

#include "Matrix.h"
#include "Vector.h"

class Optimizer{

public:

	virtual ~Optimizer(){};

	virtual void reset(){};

	virtual void update(Matrix& dw, Matrix& weight)=0;

	virtual void update(Vector& db, Vector& bias)=0;

};



#endif /* OPTIMIZER_H_ */
