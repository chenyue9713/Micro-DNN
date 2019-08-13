/*
 * SoftmaxClassEntropy.h
 *
 *  Created on: Aug 8, 2019
 *      Author: yue
 */

#ifndef LOSS_SOFTMAXCROSSENTROPY_H_
#define LOSS_SOFTMAXCROSSENTROPY_H_

#include"../Matrix.h"
#include"../Vector.h"
#include"../Config.h"
#include"../Loss.h"


class SoftmaxCrossEntropy: public Loss{

private:

	Matrix m_dscores;
	double m_loss;

public:

	void evaluate(const Matrix& scores, const Vector& target);

	const Matrix& get_derivative() const;

	const double get_loss() const;






};


#endif /* LOSS_SOFTMAXCROSSENTROPY_H_ */
