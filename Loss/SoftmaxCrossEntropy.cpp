/*
 * SoftmaxClassEntropy.cpp
 *
 *  Created on: Aug 8, 2019
 *      Author: yue
 */

#include "SoftmaxCrossEntropy.h"


void SoftmaxCrossEntropy::evaluate(const Matrix& scores, const Vector& target){

	Matrix shifted_scores = scores.substractColWise(scores.ColWiseMax());

	Matrix shifted_scores_exp =  shifted_scores;

	vector<double>* shifted_scores_exp_data = shifted_scores_exp.Data();

	for(uint32_t i = 0; i < shifted_scores_exp.getRowNum(); ++i){
		for(uint32_t j = 0; j < shifted_scores_exp.getColNum(); ++j){
			shifted_scores_exp_data[i][j] = exp(shifted_scores_exp_data[i][j]);
		}
	}

	Vector Z = shifted_scores_exp.ColWiseSum();

	double* Z_data = Z.Data();

	for(uint32_t i = 0; i < Z.getSize(); ++i)
		Z_data[i] = log(Z_data[i]);
	
	Matrix log_probs = shifted_scores.substractColWise(Z);

	vector<vector<double>> probs_data = log_probs.getData();

	for(uint32_t i = 0; i < log_probs.getRowNum(); ++i){
		for(uint32_t j = 0; j < log_probs.getColNum(); ++j){
			probs_data[i][j] = exp(probs_data[i][j]);
		}
	}

	Matrix probs(probs_data);

	double NumSample = scores.getRowNum();

	this->m_loss = 0;
	vector<vector<double>> log_probs_data = log_probs.getData();
	vector<double> target_data = target.getData();

	for(uint32_t i = 0; i < NumSample; ++i){
		int index = int(target_data[i]);
		this->m_loss -= log_probs_data[i][index];
	}
	this->m_loss /= NumSample;

	this->m_dscores = probs;

	vector<double>* m_dscores_data = m_dscores.Data();

	for(uint32_t i = 0; i < NumSample; ++i){
		int index = int(target_data[i]);
		m_dscores_data[i][index] -= 1;
	} 	

	for(uint32_t i = 0; i < NumSample; ++i){
		for(uint32_t j = 0; j < m_dscores.getColNum(); ++j){
			m_dscores_data[i][j] /= NumSample;
		}
	}
	
}

const Matrix& SoftmaxCrossEntropy::get_derivative() const{
	return this->m_dscores;
}

const double SoftmaxCrossEntropy::get_loss() const{
	return this->m_loss;
}
