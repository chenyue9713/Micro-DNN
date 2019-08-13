/*
 * Vector.cpp
 *
 *  Created on: Aug 6, 2019
 *      Author: yue
 */

#include "Vector.h"

Vector::Vector(){
	this->m_size = 0;
}

Vector::Vector(const uint32_t size){
	this->m_size = size;
	for(uint32_t i = 0; i < this->m_size; ++i){
		this->m_data.push_back(0);
	}
}

Vector::Vector(vector<double>& in_data){
	this->m_size = in_data.size();
	this->m_data = in_data;
}

Vector::~Vector(){
}


const vector<double> Vector::getData() const{
	return this->m_data;
}

double* Vector::Data(){
	return this->m_data.data();
}

void Vector::setData(const vector<double> & in_data){
	this->m_size = in_data.size();
	this->m_data = in_data;
}

void Vector::resize(uint32_t size){
	this->m_size = size;
	for(uint32_t i = 0; i < this->m_size; ++i){
		this->m_data.push_back(0);
	}

}

const uint32_t Vector::getSize() const{
	return this->m_size;
}

Vector Vector::operator*(const Vector & in_Vector) const{

	if(this->m_size != in_Vector.getSize()){
		throw invalid_argument("[Vector::*]: in_Vector size should be same with size of the Vector.");
	}

	Vector new_Vector(this->m_size);
	double* new_data = new_Vector.Data();

	vector<double> in_data = in_Vector.getData();

	for(uint32_t i = 0; i < this->m_size; ++i)
		new_data[i] = this->m_data[i] * in_data[i];

	return new_Vector;
}

Vector Vector::operator*(const double in_num) const{

	Vector new_Vector(this->m_size);
	double* new_data = new_Vector.Data();

	for(uint32_t i = 0; i < this->m_size; ++i)
		new_data[i] = this->m_data[i] * in_num;

	return new_Vector;
}

Vector Vector::operator+(const Vector & in_Vector) const{

	if(this->m_size != in_Vector.getSize()){
		throw invalid_argument("[Vector::+]: in_Vector size should be same with size of the Vector.");
	}

	Vector new_Vector(this->m_size);
	double* new_data = new_Vector.Data();

	vector<double> in_data = in_Vector.getData();

	for(uint32_t i = 0; i < this->m_size; ++i)
		new_data[i] = this->m_data[i] + in_data[i];

	return new_Vector;

}
Vector Vector::operator+(const double in_num) const{

	Vector new_Vector(this->m_size);
	double* new_data = new_Vector.Data();

	for(uint32_t i = 0; i < this->m_size; ++i)
		new_data[i] = this->m_data[i] + in_num;

	return new_Vector;

}
Vector Vector::operator-(const Vector & in_Vector) const{

	if(this->m_size != in_Vector.getSize()){
		throw invalid_argument("[Vector::-]: in_Vector size should be same with size of the Vector.");
	}

	Vector new_Vector(this->m_size);
	double* new_data = new_Vector.Data();

	vector<double> in_data = in_Vector.getData();

	for(uint32_t i = 0; i < this->m_size; ++i)
		new_data[i] = this->m_data[i] - in_data[i];

	return new_Vector;

}
Vector Vector::operator-(const double in_num) const{

	Vector new_Vector(this->m_size);
	double* new_data = new_Vector.Data();

	for(uint32_t i = 0; i < this->m_size; ++i)
		new_data[i] = this->m_data[i] - in_num;

	return new_Vector;

}
