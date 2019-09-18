/*
 * Layer.h
 *
 *  Created on: Aug 6, 2019
 *      Author: yue
 */

#ifndef LAYER_H_
#define LAYER_H_

#include"Config.h"
#include"Optimizer.h"
#include"Activation.h"
#include<random>
#include "Matrix.h"
#include "Vector.h"

class Layer{

protected:

	const uint32_t m_in_size;
	const uint32_t m_out_size;
	const string m_activation;


public:
	Layer(const uint32_t in_size, const uint32_t out_size, string activation): m_in_size(in_size), m_out_size(out_size), m_activation(activation){};

	virtual ~Layer(){};

	virtual uint32_t in_size() const = 0;

	virtual uint32_t out_size() const = 0;

	virtual void init(const double mu, const double sigma) = 0;

	virtual void feedForward(const Matrix& prev_layer_data) = 0;

	virtual void backProp(const Matrix& prev_layer_data, const Matrix & next_layer_data) = 0;

	virtual void update(Optimizer& opt) = 0;

	virtual const Matrix& output() const = 0;

	virtual const Matrix& get_dx() const = 0;

	// for debug
	virtual void set_parameters(const Matrix& weights, const Vector& bias) = 0;

	virtual void Test_forward(const Matrix& x, const Matrix& weights, const Vector& bias) = 0;

	virtual void Test_backward(const Matrix& x, const Matrix& weights, const Vector& bias, const Matrix& dout) = 0;

	virtual const Matrix& get_dw() const = 0;
	virtual const Vector& get_db() const = 0;

};




#endif /* LAYER_H_ */
