/*
 * SoftmaxClassEntropy.cpp
 *
 *  Created on: Aug 8, 2019
 *      Author: yue
 */

#include "SoftmaxCrossEntropy.h"


void SoftmaxCrossEntropy::evaluate(Matrix& scores, Vector& target){

	Vector scores_ColWiseMax =  scores.ColWiseMax();
	Matrix shifted_scores = scores.substractColWise(scores_ColWiseMax);

	Matrix shifted_scores_exp =  shifted_scores;

	double* shifted_scores_exp_data = shifted_scores_exp.Data();

	for(uint32_t i = 0; i < shifted_scores_exp.getRowNum(); ++i){
		for(uint32_t j = 0; j < shifted_scores_exp.getColNum(); ++j){
			*(shifted_scores_exp_data + shifted_scores_exp.getColNum()*i + j) = exp(*(shifted_scores_exp_data + shifted_scores_exp.getColNum()*i + j));
		}
	}

	Vector Z = shifted_scores_exp.ColWiseSum();

	double* Z_data = Z.Data();

	for(uint32_t i = 0; i < Z.getSize(); ++i)
		Z_data[i] = log(Z_data[i]);
	
	Matrix log_probs = shifted_scores.substractColWise(Z);

	Matrix probs = log_probs;

	double* probs_data = probs.Data();

	for(uint32_t i = 0; i < log_probs.getRowNum(); ++i){
		for(uint32_t j = 0; j < log_probs.getColNum(); ++j){
			*(probs_data + log_probs.getColNum()*i + j) = exp(*(probs_data + log_probs.getColNum()*i + j));
		}
	}

	double NumSample = scores.getRowNum();

	this->m_loss = 0;
	double* log_probs_data = log_probs.Data();
	uint32_t log_probs_data_ColNum = log_probs.getColNum();
	double* target_data = target.Data();

	for(uint32_t i = 0; i < NumSample; ++i){
		int index = int(*(target_data + i));
		this->m_loss -= *(log_probs_data + log_probs_data_ColNum*i + index);
	}
	this->m_loss /= NumSample;

	this->m_dscores = probs;

	double* m_dscores_data = m_dscores.Data();
	uint32_t m_dscores_data_ColNum = m_dscores.getColNum();

	for(uint32_t i = 0; i < NumSample; ++i){
		int index = int(target_data[i]);
		*(m_dscores_data + m_dscores_data_ColNum*i + index) -= 1;
	} 	

	for(uint32_t i = 0; i < NumSample; ++i){
		for(uint32_t j = 0; j < m_dscores.getColNum(); ++j){
			*(m_dscores_data + m_dscores.getColNum()*i + j) /= NumSample;
		}
	}
	
}

const Matrix& SoftmaxCrossEntropy::get_derivative() const{
	return this->m_dscores;
}

const double SoftmaxCrossEntropy::get_loss() const{
	return this->m_loss;
}
