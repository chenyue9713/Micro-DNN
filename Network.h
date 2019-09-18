/*
 * Network.h
 *
 *  Created on: Aug 6, 2019
 *      Author: yue
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "Loss.h"
#include"Config.h"
#include"Layer.h"
#include "Matrix.h"
#include "random.cpp"
#include "Vector.h"
#include "Optimizer.h"

using namespace std;

class Network{


private:
	vector<Layer*> m_layers;
	Loss* m_loss;


	void update(Optimizer & opt);

public:

	vector<double> loss_history;
	vector<double> train_acc_history;

	Network(){};

	~Network(){};

	void add_layer(Layer* layer);

	void set_loss(Loss* loss);

	uint32_t getNumLayers() const;

	void fit(Optimizer& opt, Matrix x, Vector y, uint16_t batch_size, uint16_t epoch);

	//debug
	const Matrix& get_dw1() const;
	const Vector& get_db1() const;
	const Matrix& get_dw2() const;
	const Vector& get_db2() const;

	void feedForward(Matrix& input);

	void backProp(Matrix& input, Vector& target);

};




#endif /* NETWORK_H_ */
