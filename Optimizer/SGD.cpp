/*
 * SGD.cpp
 *
 *  Created on: Aug 11, 2019
 *      Author: yue
 */

#ifndef OPTIMIZER_SGD_CPP_
#define OPTIMIZER_SGD_CPP_

#include"../Optimizer.h"


class SGD: public Optimizer{


public:

	double m_lr;
	double m_decay;

	SGD(): m_lr(0.001), m_decay(0.99){};

	void update(const Matrix& dw, Matrix& w){
		w = w - dw * this->m_lr;

	}

	void update(const Vector& db, Vector& b){
		b = b - db * this->m_lr;
		this->m_lr = this->m_lr * this->m_decay;
	}

};




#endif /* OPTIMIZER_SGD_CPP_ */
