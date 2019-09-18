/*
 * Loss.h
 *
 *  Created on: Aug 6, 2019
 *      Author: yue
 */

#ifndef LOSS_H_
#define LOSS_H_

#include"Config.h"
#include "Matrix.h"
#include "Vector.h"


class Loss{

public:

	virtual ~Loss(){};

	virtual void evaluate(Matrix& scores, Vector& target) = 0;

	virtual const Matrix& get_derivative() const = 0;

	virtual const double get_loss() const = 0;


};



#endif /* LOSS_H_ */
