/*
 * Vector.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: yue
 */
#include "Vector.h"

Vector::Vector(){
	this->m_size = 0;
}
Vector::Vector(const uint32_t size){
	this->m_size = size;
	this->m_data.resize(size);
}
Vector::Vector(vector<double>& in_data){
	this->m_size = in_data.size();
	this->m_data = in_data;
}

Vector::~Vector(){

}

double* Vector::Data(){
	return this->m_data.data();
}

void Vector::resize(const uint32_t size){
	this->m_size = size;
	this->m_data.resize(size);
}

void Vector::setData(vector<double>& in_data){
	this->m_size = in_data.size();
	this->m_data = in_data;
}

const uint32_t Vector::getSize() const{
	return this->m_size;
}

Vector Vector::operator*(Vector & in_Vector) const{

	if(this->m_size != in_Vector.getSize()){
		throw invalid_argument("[Vector::*]: in_Vector size should be same with size of the Vector.");
	}

	Vector new_Vector = *this;

	double* new_data_pt = new_Vector.Data();
	double* in_data_pt = in_Vector.Data();

	for(uint32_t i = 0; i < this->m_size; ++i, ++new_data_pt, ++in_data_pt){
		*new_data_pt *= *in_data_pt;
	}
	return new_Vector;
}

Vector Vector::operator*(const double in_num) const{

	Vector new_Vector = *this;

	double* new_data_pt = new_Vector.Data();

	for(uint32_t i = 0; i < this->m_size; ++i, ++new_data_pt){
		*new_data_pt *= in_num;
	}
	return new_Vector;
}

Vector Vector::operator+(Vector & in_Vector) const{

	if(this->m_size != in_Vector.getSize()){
		throw invalid_argument("[Vector::*]: in_Vector size should be same with size of the Vector.");
	}

	Vector new_Vector = *this;

	double* new_data_pt = new_Vector.Data();
	double* in_data_pt = in_Vector.Data();

	for(uint32_t i = 0; i < this->m_size; ++i, ++new_data_pt, ++in_data_pt){
		*new_data_pt += *in_data_pt;
	}
	return new_Vector;
}

Vector Vector::operator+(const double in_num) const{

	Vector new_Vector = *this;

	double* new_data_pt = new_Vector.Data();

	for(uint32_t i = 0; i < this->m_size; ++i, ++new_data_pt){
		*new_data_pt += in_num;
	}
	return new_Vector;
}

Vector Vector::operator-(Vector & in_Vector) const{

	if(this->m_size != in_Vector.getSize()){
		throw invalid_argument("[Vector::*]: in_Vector size should be same with size of the Vector.");
	}

	Vector new_Vector = *this;

	double* new_data_pt = new_Vector.Data();
	double* in_data_pt = in_Vector.Data();

	for(uint32_t i = 0; i < this->m_size; ++i, ++new_data_pt, ++in_data_pt){
		*new_data_pt -= *in_data_pt;
	}
	return new_Vector;
}

Vector Vector::operator-(const double in_num) const{

	Vector new_Vector = *this;

	double* new_data_pt = new_Vector.Data();

	for(uint32_t i = 0; i < this->m_size; ++i, ++new_data_pt){
		*new_data_pt -= in_num;
	}
	return new_Vector;
}



