/*
 * Vector.h
 *
 *  Created on: Aug 6, 2019
 *      Author: yue
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include"Config.h"
using namespace std;


class Vector{

private:
	vector<double> m_data;
	uint32_t m_size;

public:
	Vector();
	Vector(const uint32_t size);
	Vector(vector<double>& in_data);
	~Vector();

	const vector<double> getData() const;
	double* Data();

	void setData(const vector<double> & in_data);

	void resize(uint32_t size);

	const uint32_t getSize() const;

	Vector operator*(const Vector & in_Vector) const;
	Vector operator*(const double in_num) const;
	Vector operator+(const Vector & in_Vector) const;
	Vector operator+(const double in_num) const;
	Vector operator-(const Vector & in_Vector) const;
	Vector operator-(const double in_num) const;



};





#endif /* VECTOR_H_ */
