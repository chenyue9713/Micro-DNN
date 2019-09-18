/*
 * Matrix.h
 *
 *  Created on: Aug 19, 2019
 *      Author: yue
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include"Config.h"
#include "Vector.h"

using namespace std;

class Matrix{

public:
	uint32_t m_row;
	uint32_t m_col;
	uint32_t m_size;
	vector<double> m_data;

public:
	Matrix();
	~Matrix();
	Matrix(const uint32_t row, const uint32_t col);
	Matrix(const uint32_t row, const uint32_t col, vector<double>& in_data);

	void resize(const uint32_t row, const uint32_t col);

	void setData(const uint32_t row, const uint32_t col, vector<double>& in_data);

	double* Data();
	const vector<double> getData() const;

	Matrix transpose() const;

	const uint32_t getRowNum() const;

	const uint32_t getColNum() const;

	Matrix addColWise(Vector & in_Vector) const;
	Matrix addRowWise(Vector & in_Vector) const;
	Matrix substractRowWise(Vector & in_Vector) const;
	Matrix substractColWise(Vector & in_Vector) const;
	Matrix divideRowWise(Vector & in_Vector) const;

	Vector ColWiseMax() const;
	Vector RowWiseMax() const;

	Vector ColWiseSum() const;
	Vector RowWiseSum() const;

	Vector RowWiseMean() const;
	Vector RowWiseStdev() const;

	const double sum() const;

	Matrix dotProduct(Matrix & in_Matrix) const;

	Matrix operator*(Matrix & in_Matrix) const;
	Matrix operator*(const double in_num) const;
	Matrix operator-(Matrix& in_Matrix) const;
	Matrix operator+(Matrix& in_Matrix) const;

	//const Matrix transpose2() const;




};



#endif /* MATRIX_H_ */
