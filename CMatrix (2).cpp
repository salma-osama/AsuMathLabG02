
#include <iostream>
#include "math.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include "CMatrix.h"
#include "stdarg.h"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

CMatrix::CMatrix()
{
	nR = nC = 0;
	values = NULL;
}
CMatrix::~CMatrix()
{
	reset();
}
CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue)
{
	this->nR = nR;
	this->nC = nC;
	if((nR*nC)==0){values=NULL; return;}
	values = new double*[nR];
	for(int iR=0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC=0;iC<nC;iC++)
		{
			switch(initialization)
			{
			case MI_ZEROS: values[iR][iC] = 0; break;
			case MI_ONES: values[iR][iC] = 1; break;
			case MI_EYE: values[iR][iC] = (iR==iC)?1:0; break;
			case MI_RAND: values[iR][iC] = (rand()%1000000)/1000000.0; break;
			case MI_VALUE: values[iR][iC] = initializationValue; break;
			}
		}
	}
}
CMatrix::CMatrix(int nR, int nC, double first, ...)
{
	this->nR = nR;
	this->nC = nC;
	if((nR*nC)==0){values=NULL; return;}
	values = new double*[nR];
	va_list va;
	va_start(va, first);
	for(int iR=0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC=0;iC<nC;iC++)
		{
			values[iR][iC] = (iC==0&&iR==0)?first:va_arg(va, double);
		}
	}
	va_end(va);
}
CMatrix::CMatrix(CMatrix& m)
{
	nR = nC = 0;
	values = NULL;
	copy(m);
}
CMatrix::CMatrix(string s)
{
	nR = nC = 0;
	values = NULL;
	copy(s);
}
void CMatrix::copy(const CMatrix& m)
{
	reset();
	this->nR = m.nR;
	this->nC = m.nC;
	if((nR*nC)==0)
	{values=NULL; return;}
	values = new double*[nR];
	for(int iR=0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC=0;iC<nC;iC++)
		{
			values[iR][iC] = m.values[iR][iC];
		}
	}
}
CMatrix::CMatrix(double d)
{
	nR = nC = 0;
	values = NULL;
	copy(d);

}
void CMatrix::copy(double d)
{
	reset();
	this->nR = 1;
	this->nC = 1;
	values = new double*[1];
	values[0] = new double[1];
	values[0][0] = d;
}
void CMatrix::copy(string s)
{
	reset();
	char* buffer = new char[s.length()+1];
	strcpy(buffer, s.c_str());
	char* lineContext;
	const char* lineSeparators = ";\r\n";
	char* line = strtok_r(buffer,lineSeparators, &lineContext);
	while(line)
	{
		CMatrix row; 
		char* context;
		const char* separators = " []";
		char* token = strtok_r(line, separators, &context);
		while(token)
		{
			double xx = atof(token);
			CMatrix item ;
			item = xx;
			row.addColumn(item);
			token = strtok_r(NULL, separators, &context);
		}
		if(row.nC>0 && (row.nC==nC || nR==0))
			addRow(row);
		line = strtok_r(NULL, lineSeparators, &lineContext);
	}
	delete[] buffer;
}
void CMatrix::reset()
{
	if(values)
	{
		for(int i=0;i<nR;i++)
			delete[] values[i];
		delete[] values;
	}
	nR = nC = 0;
	values = NULL;
}
string CMatrix::getString()
{
	string s;
	for(int iR=0;iR<nR;iR++)
	{
		for(int iC=0;iC<nC;iC++)
		{
			char buffer[50];
			snprintf(buffer, 50, "%f\t", values[iR][iC]);
			s += buffer;
		}
		s+="\n";
	}
	return s;
}
CMatrix CMatrix::operator=(const CMatrix& m)
{
	copy(m);
	return *this;
}
CMatrix CMatrix::operator=(double d)
{
	copy(d);
	return *this;
}
CMatrix CMatrix::operator=(string s)
{
	copy(s);
	return *this;
}
void CMatrix::add(CMatrix& m)
{
	if(nR != m.nR || nC != m.nC)throw("Invalid matrix dimensions");
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC] += m.values[iR][iC];
}
void CMatrix::operator+=(CMatrix& m)
{
	add(m);
}
void CMatrix::operator+=(double d)
{
	CMatrix m(nR, nC, MI_VALUE, d);
	add(m);
}
CMatrix CMatrix::operator+(CMatrix& m)
{
	CMatrix r = *this;
	r+=m;
	return r;
}
CMatrix CMatrix::operator+(double d)
{
	CMatrix r = *this;
	r+=d;
	return r;
}
void CMatrix::sub(CMatrix& m)
{
	if(nR != m.nR || nC != m.nC)throw("Invalid matrix dimensions");
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC] -= m.values[iR][iC];
}
void CMatrix::operator-=(CMatrix& m)
{
	sub(m);
}
void CMatrix::operator-=(double d)
{
	CMatrix m(nR, nC, MI_VALUE, d);
	sub(m);
}
CMatrix CMatrix::operator-(CMatrix& m)
{
	CMatrix r = *this;
	r-=m;
	return r;
}
CMatrix CMatrix::operator-(double d)
{
	CMatrix r = *this;
	r-=d;
	return r;
}
void CMatrix::dotDiv(double d)
{
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC] = d/values[iR][iC];
}
void CMatrix::mul(CMatrix& m)
{
	CMatrix r(nR, m.nC);
	 if(nC != m.nR)throw("Invalid matrix dimension");
	for(int iR=0;iR<r.nR;iR++)
		for(int iC=0;iC<r.nC;iC++)
		{
			r.values[iR][iC] = 0;
			for(int k=0;k<nC;k++)
				r.values[iR][iC] += values[iR][k]*m.values[k][iC];
		}
	copy(r);
}
void CMatrix::operator*=(CMatrix& m)
{
	mul(m);
}
void CMatrix::operator*=(double d)
{
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC] *= d;
}
CMatrix CMatrix::operator*(CMatrix& m)
{
	CMatrix r = *this;
	r*=m;
	return r;
}
CMatrix CMatrix::operator*(double d)
{
	CMatrix r = *this;
	r*=d;
	return r;
}
CMatrix CMatrix::operator++()
{
	CMatrix m(nR, nC, MI_VALUE, 1.0);
	add(m);
	return *this;
}
CMatrix CMatrix::operator++(int)
{
	CMatrix C = *this;
	CMatrix m(nR, nC, MI_VALUE, 1.0);
	add(m);
	return C;
}
CMatrix CMatrix::operator--()
{
	CMatrix m(nR, nC, MI_VALUE, -1.0);
	add(m);
	return *this;
}
CMatrix CMatrix::operator--(int)
{
	CMatrix r = *this;
	CMatrix m(nR, nC, MI_VALUE, -1.0);
	add(m);
	return r;
}
CMatrix CMatrix::operator-()
{
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC] = -values[iR][iC];
	return *this;
}
CMatrix CMatrix::operator+()
{
	return *this;
}
void CMatrix::setSubMatrix(int r, int c,CMatrix& m)
{
	if((r+m.nR)>nR || (c+m.nC)>nC)
		{throw("Invalid matrix dimension");return;}
	for(int iR=0;iR<m.nR;iR++)
		for(int iC=0;iC<m.nC;iC++)
			values[r+iR][c+iC] = m.values[iR][iC];
}
CMatrix CMatrix::getSubMatrix(int r, int c, int nr, int nc)
{
	if((r+nr)>nR || (c+nc)>nC){throw("Invalid matrix dimension");exit;}
	CMatrix m(nr, nc);
	for(int iR=0;iR<m.nR;iR++)
		for(int iC=0;iC<m.nC;iC++)
			m.values[iR][iC] = values[r+iR][c+iC];
	return m;
}

void CMatrix::addColumn(CMatrix& m)
{
	CMatrix n(max(nR, m.nR), nC+m.nC);
	n.setSubMatrix(0, 0, *this);
	n.setSubMatrix(0, nC, m);
	*this = n;
}
void CMatrix::addRow(CMatrix& m)
{
	CMatrix n(nR+m.nR, max(nC, m.nC));
	n.setSubMatrix(0, 0, *this);
	n.setSubMatrix(nR, 0, m);
	*this = n;
}

CMatrix CMatrix::getCofactor(int r, int c)
{
	//if(nR<=1 && nC<=1){cout<<"Invalid matrix dimension"<<endl;exit;}
	CMatrix m(nR-1, nC-1);
	for(int iR=0;iR<m.nR;iR++)
		for(int iC=0;iC<m.nC;iC++)
		{
			int sR = (iR<r)?iR:iR+1;
			int sC = (iC<c)?iC:iC+1;
			m.values[iR][iC] = values[sR][sC];
		}
		return m;
}

double CMatrix::getDeterminant()
{
	//if(nR!=nC){cout<<"Invalid matrix dimension"<<endl;exit;}
	if(nR==1&&nC==1)
		return values[0][0];
	double value = 0, m = 1;
	for(int iR=0;iR<nR;iR++)
	{
		value+= m * values[0][iR] * getCofactor(0, iR).getDeterminant();
		m *= -1;
	}
	return value;
}
/*CMatrix CMatrix::inverse(CMatrix& m)
{ 	//if(nR!=nC){cout<<"Invalid matrix dimension"<<endl;exit;}
	int sign = 1;
	CMatrix temp(m.nR, m.nC), r(m.nR, m.nC);
	for(int i=0; i<nR; i++)
	{
		for(int j=0; j<nC; j++)
		{
			CMatrix n ;
			n = m.getCofactor(i, j);
			temp.values[i][j] = n.getDeterminant();
			sign = ((i+j)%2==0)? 1 : -1;
			r.values[j][i] = sign * temp.values[i][j] * (1.0/m.getDeterminant());
		}
	}
	return r;
}*/
CMatrix CMatrix::inverse(CMatrix &m)
{
	CMatrix a(m.nR, m.nC*2);
	a.setSubMatrix(0, 0, m);
	int i,j,k;
	double t;
	for(i=0; i<a.nR; i++)
	{
		for(j=a.nR; j<a.nC; j++)
		{
			if(i==(j-a.nR)) a.values[i][j]=1;
			else a.values[i][j] = 0;
		}
	}
	for(i=0; i<a.nR; i++)
	{
		int x = i;
		t = a.values[x][x];
		while(t == 0) 
		{x = i+1;
		t = a.values[x][x];}
		for(j=x; j<a.nC; j++)
			a.values[i][j]/=t;
			
		for(j=0; j<a.nR; j++)
		{
			if(i!=j)
			{
				t = a.values[j][i];
				for(k=0; k<a.nC; k++)
					a.values[j][k] = a.values[j][k] - t*a.values[i][k];
			}
		}
	}
	CMatrix r;
	r = a.getSubMatrix(0, a.nR, a.nR, a.nR);
	return r;
}
void CMatrix::div(CMatrix &m)
{
	CMatrix I;
	try{
	I = inverse(m);}
	catch(char const* std){throw(std);}
	mul(I);
}
void CMatrix::operator/=(CMatrix &m)
{
	try{div(m);}
	catch(char const* std){throw(std);}
}
void CMatrix::operator/=(double d)
{
	for(int iR=0; iR<nR; iR++)
		for(int iC=0; iC<nC; iC++)
			values[iR][iC] /= d;
}
CMatrix CMatrix::operator/(CMatrix &m)
{
	CMatrix r = *this;
	try{r/=m;}
	catch(char const* std){throw(std);}
	return r;
}
CMatrix CMatrix::operator/(double d)
{
	CMatrix r = *this;
	r/=d;
	return r;
}
void CMatrix::transpose(CMatrix &m)
{
	for(int i=0; i<m.nR; i++)
		for(int j=0; j<m.nC; j++)
			values[j][i] = m.values[i][j];
}
istream& operator >> (istream &is,CMatrix& m)
{
	string s;
	getline(is, s, ']');
	s+="]";
	CMatrix x(s);
	m = x;
	return is;
}
ostream& operator << (ostream &os,CMatrix& m){
	os<<m.getString();
	return os;
}
void CMatrix::rand_(int r,int c)
{
reset();
this->nR=r;
this->nC=c;
if((nR*nC)==0){values=NULL; return;}
	values = new double*[nR];
	for(int iR=0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC=0;iC<nC;iC++)
		{
           values[iR][iC] = (rand()%100)/10.0;  
		}
    }

}
void CMatrix::eye(int r,int c)
{
reset();
this->nR=r;
this->nC=c;
if((nR*nC)==0){values=NULL; return;}
	values = new double*[nR];
	for(int iR=0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC=0;iC<nC;iC++)
		{
           values[iR][iC] = (iR==iC)?1:0;  
		}
    }

}
void CMatrix::zeros(int r,int c)
{
reset();
this->nR=r;
this->nC=c;
if((nR*nC)==0){values=NULL; return;}
	values = new double*[nR];
	for(int iR=0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC=0;iC<nC;iC++)
		{
           values[iR][iC]=0;  
		}
    }

}
void CMatrix::ones(int r,int c)
{
reset();
this->nR=r;
this->nC=c;
if((nR*nC)==0){values=NULL; return;}
	values = new double*[nR];
	for(int iR=0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC=0;iC<nC;iC++)
		{

			values[iR][iC]=1;
		}
    }

}
CMatrix CMatrix::root()
{
	CMatrix r;
	//if(nC==0 && nR ==0)throw("Invalid matrix dimensions");
	for(int i=0; i<nR; i++)
		for(int j=0; j<nC; j++)
			r.values[i][j] = sqrt(values[i][j]);
	return r;
}
double CMatrix::powert(double base, int exp)
{
	double result = 1;
	for (int i = 1; i <= exp; i++)
	{
		result *= base;
	}
	return result;
}
CMatrix CMatrix::dotpower(double d)
{
	CMatrix r;
	for(int i=0; i<nR; i++)
		for(int j=0; j<nC; j++)
			r.values[i][j] = pow(values[i][j],d);
	return r;
}
CMatrix CMatrix::power(int n)
{
	CMatrix r = *this;
	CMatrix t;
	for(int i=0; i<n; i++)
	{
		if(i==0)t = r;
		else t*=r;
	}
	return t;
}
CMatrix CMatrix::dotPower(CMatrix& R)
{
	CMatrix r;
	for(int i=0; i<nR; i++)
		for(int j=0; j<nC; j++)
			r.values[i][j] = pow(values[i][j],R.values[i][j]);
	return r;
}

void CMatrix :: log_10()
{
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC]=log10(values[iR][iC]);
}
void CMatrix :: log2()
{
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC]=(log(values[iR][iC])/log(2));
}
void CMatrix :: ln()
{
	for(int iR=0;iR<nR;iR++)
		for(int iC=0;iC<nC;iC++)
			values[iR][iC]=log(values[iR][iC]);
}
int CMatrix :: factorial(int number)
{
	double result = 1 ; 
	for (int i = 1; i <= number; i++)
	{
		result *= i;
	}
	return result;
double CMatrix :: sin_equation(double x) // using taylor expansion sinx=x-x^3/3*2*1+x^5/5*4*3*2*1
{ 
	double y=(x/180)*PI;
	bool sign = true; // true for +  and flase for - 
	double sum = 0;
	for (int i = 1 ; i <= 10 ; i += 2)
	{
			if (sign ==true)
		{
		    sum += powert(y, i) / factorial(i);
		}
		else
		{
			sum -= powert(y, i) / factorial(i);
		} 
			if (sign == true)
		{
			sign = false;
		}
		else
		{
			sign = true;
		}
	}
	            if(x==0)
			   sum = 0;
		   else if ( x==90)
			   sum = 1;
		   else if ( x==180)
			   sum = 0;
		   else if ( x==270)
			   sum = -1;
		   else if ( x==360)
			   sum = 0;
	    return sum ;
}
double CMatrix ::  cos_equation(double x) // using taylor expansion cosx=1-x^2/2*1+x^4/4*3*2*1
{
	double y=(x/180)*PI;
	bool sign = true; // true for +  and flase for - 
	double sum = 0;
	for (int i = 0; i <= 10 ;i += 2)
	{
			if (sign ==true)
		{
			sum += (double)powert(y, i) / (double)factorial(i);
		}
		else
		{
		    sum -= (double)powert(y, i) / (double)factorial(i);
		} 
			if (sign == true)
		{
			sign = false;
		}
		else
		{
			sign = true;
		}
	}
	            if(x==0)
			   sum = 1;
		   else if ( x==90)
			   sum = 0;
		   else if ( x==180)
			   sum = -1;
		   else if ( x==270)
			   sum = 0;
		   else if ( x==360)
			   sum = 1;
	    return sum ;
}
double CMatrix :: tan_equation(double x)
{
	double sum ;
	            if(x==45)
			   sum = 1;
		   else if ( x==135)
			   sum = -1;
		   else if ( x==225)
			   sum = 1;
		   else if ( x==315)
			   sum = -1;
		   else if ( x==405)
			   sum = 1;
		   else
		   {	   sum = sin_equation(x)/cos_equation(x);
                   }
return sum;
}
string CMatrix::stringof()
{
	string s = "[";
	for(int i=0; i<nR; i++)
	{
		for(int j=0; j<nC; j++)
		{
			s+=to_string(values[i][j]);
			if(j!=nC-1)s+=" ";
		}
		if(i!=nR-1)s+=";";
	}
	s+="]";
	return s;
}
