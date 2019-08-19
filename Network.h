/*
 * Network.h
 *
 *  Created on: Aug 6, 2019
 *      Author: yue
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include"Config.h"
#include"Matrix.h"
#include"Vector.h"
#include"Layer.h"
#include"Loss.h"
#include"random.cpp"

using namespace std;

class Network{


private:
	vector<Layer*> m_layers;
	Loss* m_loss;

	//void update(Optimizer& opt)
	void feedForward(const Matrix& input);

	void backProp(const Matrix& input, Vector& target);

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

};




#endif /* NETWORK_H_ */
