/*
 * SDG.H
 *
 *  Created on: Aug 14, 2019
 *      Author: yue
 */

#ifndef OPTIMIZER_SGD_H_
#define OPTIMIZER_SGD_H_

#include"../Optimizer.h"


class SGD: public Optimizer{


public:

	double m_lr;
	double m_decay;

	SGD(): m_lr(0.001), m_decay(0.99){};

	void update(Matrix& dw, Matrix& w){
		Matrix temp_dw = dw * this->m_lr;
		w = w - temp_dw;

	}

	void update(Vector& db, Vector& b){
		Vector temp_db = db * this->m_lr;
		b = b - temp_db;
		this->m_lr = this->m_lr * this->m_decay;
	}

};





#endif /* OPTIMIZER_SGD_H_ */
