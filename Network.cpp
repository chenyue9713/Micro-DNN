/*
 * Network.cpp
 *
 *  Created on: Aug 10, 2019
 *      Author: yue
 */

#include"Network.h"


void Network::add_layer(Layer* layer){

	this->m_layers.push_back(layer);

}

void Network::set_loss(Loss* loss){

	this->m_loss = loss;
}

uint32_t Network::getNumLayers() const{

	return this->m_layers.size();
}

void Network::feedForward(const Matrix& input){

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


void Network::backProp(const Matrix& input, Vector& target){

	const int NumLayers = getNumLayers();

	Matrix scores = this->m_layers[NumLayers - 1]->output();

	this->m_loss->evaluate(scores, target);

	const double loss = this->m_loss->get_loss();

	Layer* first_layer = this->m_layers[0];

	Layer* last_layer = this->m_layers[NumLayers - 1];

	last_layer->backProp(first_layer->output() , this->m_loss->get_derivative());

	first_layer->backProp(input, last_layer->get_dx());


}

void Network::update(Optimizer & opt){

	const int NumLayers = getNumLayers();

	if(NumLayers <= 0)
		return;

	for(uint32_t i = 0; i < NumLayers; ++i)
		m_layers[i]->update(opt);



}

void Network::fit(Optimizer& opt, Matrix x, Vector y, uint16_t batch_size, uint16_t epoch){


	Matrix batch_mask;

	uint32_t numSample = x.getRowNum();


	if(y.getSize() != numSample){
		throw invalid_argument("[Network::fit]: X and Y have different number of sample");
	}

	shuffle_batch(batch_size, numSample, batch_mask);

	double loss;
	for(uint16_t i = 0; i < epoch; ++i){
		int count = 0;
		for(auto batch: batch_mask.getData()){
			uint16_t bsize = batch[0];
			Matrix batch_x(bsize, 3072);
			Vector batch_y(bsize);
			for(uint16_t k = 0; k < bsize; ++k){
				int index = int(batch[k+1]);
				batch_x.Data()[k] = x.Data()[index];
				batch_y.Data()[k] = y.Data()[index];
			}

			this->feedForward(batch_x);
			this->backProp(batch_x, batch_y);
			this->update(opt);
			count++;
			loss = m_loss->get_loss();
			loss_history.push_back(loss);
			cout << "(batch number " << count << " / " << 245 << ") " << "loss:" << loss << endl;
		}
		cout << "(Epoch " << i << " / " << epoch << ") " << "loss:" << loss << endl;


	}


}


