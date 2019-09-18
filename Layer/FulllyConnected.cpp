/*
 * FulllyConnected.cpp
 *
 *  Created on: Aug 7, 2019
 *      Author: yue
 */

#include"FullyConnected.h"

uint32_t FullyConnected::in_size() const{
	return this->m_in_size;
}

uint32_t FullyConnected::out_size() const{
	return this->m_out_size;
}


void FullyConnected::init(const double mu, const double sigma){

	this->m_weights.resize(this->m_in_size, this->m_out_size);
	this->m_bias.resize(this->m_out_size);
	this->m_dw.resize(this->m_in_size,  this->m_out_size);
	this->m_db.resize(this->m_out_size);

	//randomize weights under normal distribution 
	default_random_engine generator;
	normal_distribution<double> distribution(mu,sigma);

	double* m_weights_data = this->m_weights.Data();
	for(uint32_t i = 0; i < this->m_in_size * m_out_size; ++i,++m_weights_data){
		double number = distribution(generator);
		*m_weights_data = number;
	}

}

void FullyConnected::feedForward(const Matrix & prev_layer_data){

	if(this->m_in_size != prev_layer_data.getColNum()){
		throw invalid_argument("[FullyConnected::feedForward]: prev_layer_data size should be compitable with m_weights's size.");
	}

	this->m_dx.resize(prev_layer_data.getRowNum(), this->m_in_size);
	this->m_z.resize(prev_layer_data.getRowNum(), this->m_out_size);
	this->m_out.resize(prev_layer_data.getRowNum(), this->m_out_size);

	this->m_z = prev_layer_data.dotProduct(m_weights).addRowWise(m_bias);

	Activation act;
	if(this->m_activation == "None")
		this->m_out = this->m_z;
	else if(this->m_activation == "relu")
		act.Relu_forward(m_z, m_out);

}

void FullyConnected::backProp(const Matrix & prev_layer_data, const Matrix & next_layer_data){

	Activation act;
	Matrix dLz = next_layer_data;
	if(this->m_activation == "relu")
		act.Relu_backward(this->m_z, dLz);
	this->m_dw = prev_layer_data.transpose().dotProduct(dLz);
	this->m_db = dLz.RowWiseSum();
	Matrix weight_transpose = this->m_weights.transpose();
	this->m_dx = dLz.dotProduct(weight_transpose);

}

void FullyConnected::Test_forward(const Matrix& x, const Matrix& weights, const Vector& bias){
	this->m_weights = weights;
	this->m_bias = bias;
	
	feedForward(x);

	
}


void FullyConnected::Test_backward(const Matrix& x, const Matrix& weights, const Vector& bias, const Matrix& dout){
	this->m_weights = weights;
	this->m_bias = bias;

	feedForward(x);

	backProp(x, dout);
}

const Matrix& FullyConnected::output() const{
	return this->m_out;
}

const Matrix& FullyConnected::get_dx() const{
	return this->m_dx;
}

//debug
const Matrix& FullyConnected::get_dw() const{
	return this->m_dw;
}
const Vector& FullyConnected::get_db() const{
	return this->m_db;
}

void FullyConnected::set_parameters(const Matrix& weights, const Vector& bias){
	this->m_weights = weights;
	this->m_bias = bias;
}

void FullyConnected::update(Optimizer& opt){

	opt.update(this->m_dw, this->m_weights);
	opt.update(this->m_db, this->m_bias);

}







