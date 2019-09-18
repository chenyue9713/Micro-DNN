/*
 * Vector.h
 *
 *  Created on: Aug 20, 2019
 *      Author: yue
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include"Config.h"

using namespace std;

class Vector{

private:
	uint32_t m_size;
	vector<double> m_data;

public:
	Vector();
	Vector(const uint32_t size);
	Vector(vector<double>& in_data);
	~Vector();

	double* Data();

	void resize(const uint32_t size);

	void setData(vector<double>& in_data);

	const uint32_t getSize() const;

	Vector operator*(Vector & in_Vector) const;
	Vector operator*(const double in_num) const;
	Vector operator+(Vector & in_Vector) const;
	Vector operator+(const double in_num) const;
	Vector operator-(Vector & in_Vector) const;
	Vector operator-(const double in_num) const;







};




#endif /* VECTOR_H_ */
