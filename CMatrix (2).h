
#include "string.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class CMatrix
{
	int nR, nC;
	double** values;
public:
	CMatrix();
	~CMatrix();
	enum MI{MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE};
	CMatrix(int nR, int nC, int initialization = MI_ZEROS, double initializationValue = 0.0);
	CMatrix(int nR, int nC, double first, ...);
	CMatrix(CMatrix& m);
	CMatrix(double d);
	CMatrix(string s);
	void copy(const CMatrix& m);
	void copy(double d);
	void copy(string s);
	void reset();

	string getString();
	CMatrix operator=(const CMatrix& m);
	CMatrix operator=(double d);
	CMatrix operator=(string s);
	void add(CMatrix& m);
	void operator+=(CMatrix& m);
	void operator+=(double d);
	CMatrix operator+(CMatrix& m);
	CMatrix operator+(double d);
	void sub(CMatrix& m);
	void operator-=(CMatrix& m);
	void operator-=(double d);
	CMatrix operator-(CMatrix& m);
	CMatrix operator-(double d);
	void dotDiv(double d);
	void mul(CMatrix& m);
	void operator*=(CMatrix& m);
	void operator*=(double d);
	CMatrix operator*(CMatrix& m);
	CMatrix operator*(double d);
	CMatrix inverse(CMatrix& m);
	void div(CMatrix& m);
	void operator/=(CMatrix& m);
	void operator/=(double d);
	CMatrix operator/(CMatrix& m);
	CMatrix operator/(double d);
	void transpose(CMatrix &m);
	CMatrix operator++(); //Pre Increment
	CMatrix operator++(int); //Post Increment, int is not used
	CMatrix operator--(); //Pre Increment
	CMatrix operator--(int); //Post Increment, int is not used
	CMatrix operator-();
	CMatrix operator+();
	friend istream& operator >> (istream &is,CMatrix& C); //Stream
	friend ostream& operator << (ostream &os,CMatrix& C); //Stream
	void setSubMatrix(int iR, int iC,CMatrix& m);
	CMatrix getSubMatrix(int r, int c, int nr, int nc);
	CMatrix getCofactor(int r, int c);
	void addColumn(CMatrix& m);
	void addRow(CMatrix& m);
	double& operator[](int i){return values[i/nC][i%nC];}
	double& operator()(int i){return values[i/nC][i%nC];}
	double& operator()(int r, int c){return values[r][c];}
	int getn(){return nR*nC;};
	int getnR(){return nR;};
	int getnC(){return nC;};
	double getDeterminant();
	double getTranspose();
	double getInverse();
	void rand_(int r,int c);
        void eye(int r,int c);
        void zeros(int r,int c);
        void ones(int r,int c);
	CMatrix dotPower(CMatrix& R);
	CMatrix dotpower(double d);
	CMatrix power(int n);
	double powert(double base, int exp);
	CMatrix root();
	void log_10() ;
	void log2() ;
	void ln() ;
        int factorial(int number);
        double sin_equation(double x);
        double cos_equation(double x);
        double tan_equation(double x);


};
