/*
 * Network.cpp
 *
 *  Created on: Aug 10, 2019
 *      Author: yue
 */

#include "Network.h"


void Network::add_layer(Layer* layer){

	this->m_layers.push_back(layer);

}

void Network::set_loss(Loss* loss){

	this->m_loss = loss;
}

uint32_t Network::getNumLayers() const{

	return this->m_layers.size();
}

void Network::feedForward(Matrix& input){

	const int NumLayers = getNumLayers();

	if(NumLayers <= 0)
		return;

	if(input.getColNum() != this->m_layers[0]->in_size()){
		throw invalid_argument("[Network::FeedForward]: input's size should be compatible with number of row in Matrix.");
	}

	m_layers[0]->feedForward(input);

	for(uint16_t i = 1; i < NumLayers; ++i){
		m_layers[i]->feedForward(this->m_layers[i-1]->output());
	}

}


void Network::backProp(Matrix& input, Vector& target){

	const int NumLayers = getNumLayers();

	Matrix scores = this->m_layers[NumLayers - 1]->output();

	this->m_loss->evaluate(scores, target);

	Layer* first_layer = this->m_layers[0];

	Layer* last_layer = this->m_layers[NumLayers - 1];

	last_layer->backProp(first_layer->output() , this->m_loss->get_derivative());

	first_layer->backProp(input, last_layer->get_dx());


}

void Network::update(Optimizer & opt){

	const uint32_t NumLayers = getNumLayers();

	if(NumLayers <= 0)
		return;

	for(uint32_t i = 0; i < NumLayers; ++i)
		m_layers[i]->update(opt);



}

void Network::fit(Optimizer& opt, Matrix x, Vector y, uint16_t batch_size, uint16_t epoch){


	Matrix batch_mask;

	uint32_t numSample = x.getRowNum();

	double* x_pt = x.Data();
	double* y_pt = y.Data();


	if(y.getSize() != numSample){
		throw invalid_argument("[Network::fit]: X and Y have different number of sample");
	}

	shuffle_batch(batch_size, numSample, batch_mask);

	double* batch_mask_pt = batch_mask.Data();

	double loss;
	for(uint16_t i = 0; i < epoch; ++i){
		int count = 0;
		for(uint32_t j = 0; j < batch_mask.getRowNum(); ++j){
			uint16_t bsize = *(batch_mask_pt + j * (batch_mask.getColNum()-1));
			Matrix batch_x(bsize, 3072);
			double* batch_x_pt = batch_x.Data();
			Vector batch_y(bsize);
			double* batch_y_pt = batch_y.Data();
			for(uint16_t k = 0; k < bsize; ++k){
				int index = int(*(batch_mask_pt + j * (batch_mask.getColNum()-1) + k+1));
				for(uint16_t m = 0; m < 3072 ; ++m){
					*(batch_x_pt + k*3072 + m) = *(x_pt + index*3072 + m);
				}
				//batch_x.Data()[k] = x.Data()[index];
				*(batch_y_pt + k) = *(y_pt + index);
				//batch_y.Data()[k] = y.Data()[index];
			}

			this->feedForward(batch_x);
			this->backProp(batch_x, batch_y);
			this->update(opt);
			count++;
			loss = m_loss->get_loss();
			loss_history.push_back(loss);
			//cout << "(batch number " << count << " / " << 245 << ") " << "loss:" << loss << endl;
		}
		cout << "(Epoch " << i << " / " << epoch << ") " << "loss:" << loss << endl;
	}

}

const Matrix& Network::get_dw1() const{
	Layer* first_layer = this->m_layers[0];

	return first_layer->get_dw();


}

const Matrix& Network::get_dw2() const{

	Layer* last_layer = this->m_layers[1];

	return last_layer->get_dw();

}

const Vector& Network::get_db1() const{

	Layer* first_layer = this->m_layers[0];

	return first_layer->get_db();

}


const Vector& Network::get_db2() const{
	Layer* last_layer = this->m_layers[1];

	return last_layer->get_db();

}


