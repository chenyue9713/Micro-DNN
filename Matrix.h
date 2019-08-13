/*
 * Matrix.h
 *
 *  Created on: Aug 6, 2019
 *      Author: yue
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include"Config.h"
#include"Vector.h"
using namespace std;

class Matrix{

private:
	vector<vector<double>> m_data;
	uint32_t m_col;
	uint32_t m_row;


public:

	Matrix();
	Matrix(const uint32_t row, const uint32_t col);
	Matrix(const vector<vector<double>>& in_data);
	~Matrix(){};

	const vector<vector<double>> getData() const;
	vector<double>* Data();

	void setData(const vector<vector<double>> & in_data); 

	void resize(const uint32_t row, const uint32_t col);

	const uint32_t getRowNum() const;
	const uint32_t getColNum() const;

	const Matrix transpose() const;
	Matrix addColWise(Vector & in_Vector) const;
	Matrix addRowWise(Vector & in_Vector) const;
	Matrix substractColWise(const Vector & in_Vector) const;
	Matrix substractRowWise(const Vector & in_Vector) const;

	const Vector ColWiseMax() const;
	const Vector RowWiseMax() const;

	Vector ColWiseSum() const;
	Vector RowWiseSum() const;

	Vector RowWiseMean() const;

	const double sum() const;


	Matrix dotProduct(const Matrix & in_Matrix) const;

	Matrix operator*(const Matrix & in_data) const;
	Matrix operator*(const double in_num) const;
	Matrix operator-(const Matrix& in_Matrix) const;
	Matrix operator+(const Matrix& in_Matrix) const;

};





#endif /* MATRIX_H_ */
