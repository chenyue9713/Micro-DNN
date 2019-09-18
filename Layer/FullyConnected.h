/*
 * FullyConnected.h
 *
 *  Created on: Aug 7, 2019
 *      Author: yue
 */

#ifndef LAYER_FULLYCONNECTED_H_
#define LAYER_FULLYCONNECTED_H_

#include"../Layer.h"

using namespace std;

class FullyConnected: public Layer{


private:
	Matrix m_weights;
	Vector m_bias;
	Matrix m_out; // a = activate(z)
	Matrix m_z;  // z = x.dot(w) + b
	Matrix m_dw;
	Vector m_db;
	Matrix m_dx;

public:

	FullyConnected(const uint32_t in_size, const uint32_t out_size, const string activation):Layer(in_size, out_size, activation){}

	uint32_t in_size() const;

	uint32_t out_size() const;
	
	void init(const double mu, const double sigma);

	void feedForward(const Matrix & prev_layer_data);

	void backProp(const Matrix & prev_layer_data, const Matrix & next_layer_data);

	void update(Optimizer& opt);

	const Matrix& output() const;

	const Matrix& get_dx() const;

	//Debug
	const Matrix& get_dw() const;
	const Vector& get_db() const;




	// for debug
	void set_parameters(const Matrix& weights, const Vector& bias);

	void Test_forward(const Matrix& x, const Matrix& weights, const Vector& bias);

	void Test_backward(const Matrix& x, const Matrix& weights, const Vector& bias, const Matrix& dout);
};






#endif /* LAYER_FULLYCONNECTED_H_ */
