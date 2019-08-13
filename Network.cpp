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

	this->m_layers[0]->feedForward(input);

	for(uint16_t i = 1; i < NumLayers; ++i){
		this->m_layers[i]->feedForward(this->m_layers[i-1]->output());
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


