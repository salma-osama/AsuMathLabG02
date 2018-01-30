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
#define num 50

string trim(string s)
{
	string r;
	for(int i=0; i<s.length(); i++)
	{
		if(s[i]!=' ')r+=s[i];
	}
	return r;
}

bool isDouble(string s)
{
	for(int i=0; i<s.length(); i++)
	{
		if(s[i] != '.' && !(isdigit(s[i])) && s[i] != '-')
			return false;
	}
	return true;
}
CMatrix fix_matrix(string s,int& counter)
{
	CMatrix result;
	 int n=0;
     s.erase(s.begin());
	 s.erase(s.length()-1);
	 
	 int pos=0;
	 string matrices[50];
	   counter=0;
	 int flag=0;
	 for(int i=pos;i<=s.length();i++)
	 {
		 string a;
	 if(s[i]=='[') 
		 counter++;
	 else if(s[i]==']') 
		 counter--;
	 else if((s[i]==';' || s[i]=='\0')&& counter==0 )
	 {
		 a=s.substr(pos,i-pos);
		 pos=i+1;
	 if((a.find('[')!=-1) || (a.find(']')!=-1))
		 flag=1;
	 }
	
	 if(flag==1)
	{
		CMatrix sub_result;
		int pos2=0;
		flag=0;
		for(int j=0;j<=a.length();j++)
		{
		if((a[j]==',') || (a[j]=='\0'))
		{
		matrices[n]=a.substr(pos2,j-pos2);
        CMatrix k;
		k.copy(matrices[n]);
		sub_result.addColumn(k);
		pos2=j+1;
		n++;
		}
		}
       
		result.addRow(sub_result);
	 }
	 else if(flag==0)
	 {
		 CMatrix b;
		 b.copy(a);
		 result.addRow(b);
	 }
}

	
return result;
} 
void modify(string* operators, string* operands, int ioperator, int ioperand, int ioperators, int ioperands)
{
	for(int i = ioperator; i<ioperators-1; i++)
	{
		operators[i] = operators[i+1];
	}
	if(ioperand != -1)
	{
		for(int i = ioperand; i<ioperands-1; i++)
		{
			operands[i] = operands[i+1];
		}
	}
}
int choose(string* operators, int open, int close)
{
	for(int i = open+1; i<close; i++)
	{
		if(operators[i] == "^"||operators[i] == ".^")return i;
	}
	for(int i = open+1; i<close; i++)
	{
		if(operators[i] == "*"||operators[i] == "/"||operators[i] == ".*"||operators[i] == "./")return i;
	}
	for(int i = open+1; i<close; i++)
	{
		if(operators[i] == "+"||operators[i] == "-"||operators[i] == ".+"||operators[i] == ".-")return i;
	}
	return -1;
}
string doOp(string operation, string operand1, string operand2)
{
	double value;
	string svalue;
	if(operand1.find("[")==-1&&operand2.find("]")==-1)
	{
		if(operation == "+")value = atof(operand1.c_str())+atof(operand2.c_str());
		else if(operation == "-")value = atof(operand1.c_str())-atof(operand2.c_str());
		else if(operation == "*")value = atof(operand1.c_str())*atof(operand2.c_str());
		else if(operation == "/")value = atof(operand1.c_str())/atof(operand2.c_str());
		else if(operation == "^")value = pow(atof(operand1.c_str()),atof(operand2.c_str()));
		return to_string(value);
	}
	else if(operand1.find("[")!=-1&&operand2.find("]")!=-1)
	{
		if(operation == "+"||operation == ".+")
		{
			CMatrix m1(operand1);
			CMatrix m2(operand2);
			CMatrix r;
			r=m1+m2;
			svalue = r.stringof();
		}
		else if(operation == "-"||operation==".-")
		{
			CMatrix m1(operand1);
			CMatrix m2(operand2);
			CMatrix r;
			r=m1-m2;
			svalue = r.stringof();
		}
		else if(operation == "*")
		{
			CMatrix m1(operand1);
			CMatrix m2(operand2);
			CMatrix r;
			r=m1*m2;
			svalue = r.stringof();
		}
		else if(operation == "/")
		{
			CMatrix m1(operand1);
			CMatrix m2(operand2);
			CMatrix r;
			r=m1/m2;
			svalue = r.stringof();
		}
		else if(operation == ".*")
		{
			CMatrix m1(operand1);
			CMatrix m2(operand2);
			CMatrix r;
			r=m1.dotTimes(m2);
			svalue = r.stringof();
		}
		else if(operation == "./")
		{
			CMatrix m1(operand1);
			CMatrix m2(operand2);
			CMatrix r;
			r=m1.dotDivision(m2);
			svalue = r.stringof();
		}
		else if(operation == ".^")
		{
			CMatrix m1(operand1);
			CMatrix m2(operand2);
			CMatrix r;
			r=m1.dotPower(m2);
			svalue = r.stringof();
		}
		return svalue;
	}
	else if(operand1.find("[")!=-1&&operand2.find("]")==-1)
	{
		if(operation == "+"||operation == ".+")
		{
			CMatrix m1(operand1);
			CMatrix r;
			r=m1.dotplus(atof(operand2.c_str()));
			svalue = r.stringof();
		}
		else if(operation == "-"||operation==".-")
		{
			CMatrix m1(operand1);
			CMatrix r;
			r=m1.dotminus(atof(operand2.c_str()));
			svalue = r.stringof();
		}
		else if(operation == "*"||operation == ".*")
		{
			CMatrix m1(operand1);
			CMatrix r;
			r=m1.dottimes(atof(operand2.c_str()));
			svalue = r.stringof();
		}
		else if(operation == "/"||operation == "./")
		{
			CMatrix m1(operand1);
			CMatrix r;
			r=m1.dotdivision(atof(operand2.c_str()));
			svalue = r.stringof();
		}
		else if(operation == ".^")
		{
			CMatrix m1(operand1);
			CMatrix r;
			r=m1.dotpower(atof(operand2.c_str()));
			svalue = r.stringof();
		}
		else if(operation == "^")
		{
			CMatrix m1(operand1);
			CMatrix r;
			r=m1.power(atoi(operand2.c_str()));
			svalue = r.stringof();
		}
		return svalue;
	}
	else if(operand1.find("[")==-1&&operand2.find("]")!=-1)
	{
		if(operation == "+"||operation == ".+")
		{
			CMatrix m1(operand1);
			CMatrix r;
			r=m1.dotplus(atof(operand2.c_str()));
			svalue = r.stringof();
		}
		else if(operation == "-"||operation==".-")
		{
			CMatrix m1(operand1);
			CMatrix r;
			r=m1.dotminus(atof(operand2.c_str()));
			r = -r;
			svalue = r.stringof();
		}
		else if(operation == "*"||operation == ".*")
		{
			CMatrix m1(operand1);
			CMatrix r;
			r=m1.dottimes(atof(operand2.c_str()));
			svalue = r.stringof();
		}
		else if(operation == "./")
		{
			CMatrix m1(operand1);
			CMatrix r;
			r=m1.dotdiv(atof(operand2.c_str()));
			svalue = r.stringof();
		}
		return svalue;
	}
}
void parse(string s, string*operators, string*operands, int& ioperators, int& ioperands)
{
	ioperators = 0; ioperands = 0;
	int index = 0,index1 = 0, index2 = 0, flag = 0;
	for(int i=0; i<s.length(); i++)
	{
		if(s.substr(i,3) == "in("||s.substr(i,3) == "os("||s.substr(i,3) == "an("||s.substr(i,4) == "qrt("||s.substr(i,3) == "rt("||s.substr(i,2) == "n("||s.substr(i,2) == "s("||s.substr(i,2) == "t("
			||s.substr(i,3) == "og("||s.substr(i,2) == "g("||s.substr(i,5) == "og10("||s.substr(i,4) == "g10("||s.substr(i,3) == "10("||s.substr(i,2) == "0("||s.substr(i,4) == "og2("||s.substr(i,3) == "g2("||s.substr(i,2) == "2("
			||((s[i]=='+'||s[i]=='-'||s[i]=='/'||s[i]=='*'||s[i]=='^')&&s[i-1]=='.'))continue;
		int flag3;
		flag3 = (i==0)?1:0;
		if(i>0)flag3 = (s[i-1]=='(')?1:0;
		if(s[i]=='('||s[i]==')'||s[i]=='+'||(s[i]=='-'&&flag3==0)||s[i]=='/'||s[i]=='*'||s[i]=='^')
		{
			operators[ioperators] = s[i];
			ioperators++;
			index2 = i-1;
			if(index2>=0 &&index2>=index1 && index != i && flag == 0)
			{
				operands[ioperands] = s.substr(index1, index2-index1+1);
				ioperands++;
			}
			flag = 1;
			index = i+1;
		}
		else if(s.substr(i,2)==".+"||s.substr(i,2)==".-"||s.substr(i,2)==".*"||s.substr(i,2)=="./"||s.substr(i,2)==".^")
		{
			operators[ioperators] = s.substr(i,2);
			ioperators++;
			index2 = i-1;
			if(index2>=0 &&index2>=index1 && index != i && flag == 0)
			{
				operands[ioperands] = s.substr(index1, index2-index1+1);
				ioperands++;
			}
			flag = 1;
			index = i+2;
		}
		else if(s.substr(i,3)=="sin"||s.substr(i,3)=="cos"||s.substr(i,3)=="tan"||s.substr(i,3)=="log")
		{
			operators[ioperators] = s.substr(i,3);
			ioperators++;
			if(i==0)flag=1;
		}
		else if(s.substr(i,4)=="sqrt"||s.substr(i,4)=="log2")
		{
			operators[ioperators] = s.substr(i,4);
			ioperators++;
			if(i==0)flag=1;
		}
		else if(s.substr(i,5)=="log10")
		{
			operators[ioperators] = s.substr(i,5);
			ioperators++;
			if(i==0)flag=1;
		}
		else
		{
			if(flag == 1)index1 = i;
			flag = 0;
			if(i==s.length()-1)
			{
				operands[ioperands] = s.substr(index1, i-index1+1);
				ioperands++;
			}
		}
	}
}
string solve(string*operators, string*operands, int ioperators, int ioperands)
{
	int count = 0;
	int opindex = 0, clindex = 0, iop = 0, praceindex=0;
	string value;
	while(ioperators > ioperands-1)
	{
		if(operators[praceindex] == "(")
		{
			if(praceindex!=0)
			{
				if(operators[praceindex-1] == "sin" || operators[praceindex-1] == "cos" || operators[praceindex-1] == "tan" || operators[praceindex-1] == "log"
					||operators[praceindex-1] == "sqrt"||operators[praceindex-1] == "log"||operators[praceindex-1] == "log2"||operators[praceindex-1] == "log10")count+=2;
				else count++;
			}
			else
				count++;
			opindex = praceindex;
			for(int i=opindex+1; i<ioperators; i++)
			{
				if(operators[i] == "(")
				{
					opindex = i;
					if(operators[opindex-1] == "sin" || operators[opindex-1] == "cos" || operators[opindex-1] == "tan" || operators[opindex-1] == "sqrt"
						||operators[opindex-1] == "log" ||operators[opindex-1] == "log2" ||operators[opindex-1] == "log10")count+=2;
					else count++;
				}
				else if(operators[i] == ")")
				{
					clindex = i;
					break;
				}
			}
			iop = choose(operators, opindex, clindex);
			if(iop == -1)
			{
				if(opindex!=0)
				{
					if(operators[opindex-1] == "sin" || operators[opindex-1] == "cos" || operators[opindex-1] == "tan" ||operators[opindex-1]=="sqrt"
						||operators[opindex-1] == "log" ||operators[opindex-1] == "log2" ||operators[opindex-1] == "log10")
					{
						if(operators[opindex-1]=="sin")
						{
							if(operands[opindex-count+1].find("[")==-1)operands[opindex-count+1] = to_string(sin(atof(operands[opindex-count+1].c_str())));
							else 
							{
								CMatrix r1(operands[opindex-count+1]);
								CMatrix r2;
								r2 = r1.sine();
								operands[opindex-count+1] = r2.stringof();
							}
						}
						else if(operators[opindex-1]=="cos")
						{
							if(operands[opindex-count+1].find("[")==-1)operands[opindex-count+1] = to_string(cos(atof(operands[opindex-count+1].c_str())));
							else 
							{
								CMatrix r1(operands[opindex-count+1]);
								CMatrix r2;
								r2 = r1.cosine();
								operands[opindex-count+1] = r2.stringof();
							}
						}
						if(operators[opindex-1]=="tan")
						{
							if(operands[opindex-count+1].find("[")==-1)operands[opindex-count+1] = to_string(tan(atof(operands[opindex-count+1].c_str())));
							else 
							{
								CMatrix r1(operands[opindex-count+1]);
								CMatrix r2;
								r2 = r1.tan_();
								operands[opindex-count+1] = r2.stringof();
							}
						}
						if(operators[opindex-1]=="sqrt")
						{
							if(operands[opindex-count+1].find("[")==-1)operands[opindex-count+1] = to_string(sqrt(atof(operands[opindex-count+1].c_str())));
							else 
							{
								CMatrix r1(operands[opindex-count+1]);
								CMatrix r2;
								r2 = r1.root();
								operands[opindex-count+1] = r2.stringof();
							}
						}
						if(operators[opindex-1]=="log")
						{
							if(operands[opindex-count+1].find("[")==-1)operands[opindex-count+1] = to_string(log(atof(operands[opindex-count+1].c_str())));
							else 
							{
								CMatrix r1(operands[opindex-count+1]);
								CMatrix r2;
								r2 = r1.log_();
								operands[opindex-count+1] = r2.stringof();
							}
						}
						if(operators[opindex-1]=="log2")
						{
							if(operands[opindex-count+1].find("[")==-1)operands[opindex-count+1] = to_string(log(atof(operands[opindex-count+1].c_str()))/log(2));
							else 
							{
								CMatrix r1(operands[opindex-count+1]);
								CMatrix r2;
								r2 = r1.log_2();
								operands[opindex-count+1] = r2.stringof();
							}
						}
						if(operators[opindex-1]=="log10")
						{
							if(operands[opindex-count+1].find("[")==-1)operands[opindex-count+1] = to_string(log10(atof(operands[opindex-count+1].c_str())));
							else 
							{
								CMatrix r1(operands[opindex-count+1]);
								CMatrix r2;
								r2 = r1.log_10();
								operands[opindex-count+1] = r2.stringof();
							}
						}
						modify(operators, operands, opindex-1, -1, ioperators, ioperands);
						opindex--;
						modify(operators, operands, opindex, -1, ioperators, ioperands);
						clindex-=2;
						modify(operators, operands, clindex, -1, ioperators, ioperands);
						ioperators = ioperators-3;
					}
					else
					{
						modify(operators, operands, opindex, -1, ioperators, ioperands);
						clindex--;
						modify(operators, operands, clindex, -1, ioperators, ioperands);
						ioperators = ioperators-2;
					}
				}
				else
				{
					modify(operators, operands, opindex, -1, ioperators, ioperands);
					clindex--;
					modify(operators, operands, clindex, -1, ioperators, ioperands);
					ioperators = ioperators-2;
				}
			}
			else
			{
				value = doOp(operators[iop], operands[iop-count], operands[iop-count+1]);
				operands[iop-count] = value;
				modify(operators,operands,iop,iop-count+1,ioperators,ioperands);
				ioperators--;
				ioperands--;
			}
			count = 0;
			praceindex = 0;
		}
		else praceindex++;
	}
	while(ioperators)
	{
		iop = choose(operators,-1,ioperators);
		value = doOp(operators[iop], operands[iop], operands[iop+1]);
		operands[iop] = value;
		modify(operators, operands, iop, iop+1,ioperators, ioperands);
		ioperators--;
		ioperands--;
	}
	string re = operands[0];
	return re;
}

void handlingErrors(string file)
{   

	string s;
	ifstream infile("errorsexample1.m");
	cout<<"no"<<endl;
	if(!infile.bad())
	{
		while(getline(infile,s))
		{
			
			string r= trim(s);
			int length= r.length();
			
			for(int i=0; i<length ;i++)
			{
				int a=r.find("/");
				if(a!=-1)
				{  
					if(r.find("0")!=-1) throw("This gives an undefined value"); 
				}	
		//============================================================================================
				int b=r.find("[");
			
				if(b!=-1)
				{ 
					int newlength=length-b;
				
				for(int i=b; i<newlength ;i++)
				{ 
				
				if(r.find("]")==-1)  throw("wrong enteries ");
				if(r.find("]")>newlength+1) throw("wrong enteries ");
				}
				}
		//=============================================================================================
				int c=r.find("(");
				
				if(c!=-1)
				{
					int newlength1=length-c;
				for(int i=c; i<newlength1 ;i++)
				{
				if(r.find(")")==-1)  throw("wrong enteries ");
				if(r.find(")")>newlength1+1) throw("wrong enteries ");
				}
				}
        //===============================================================================================
				int d=r.rfind("+");
				int e=r.rfind("-");
				int f= r.rfind("*");
				int g =r.rfind("/");
				if(d==r.length()-1 || e==r.length()-1 || f==r.length()-1 || g==r.length()-1 ) throw("wrong enteries ");
         //===========================================================================================

				int x=r.find(";");
				int count=0,count1=0;
				for(int i=0; i<x ;i++)
				{
				if(isdigit(r[i])) count++;
				
				}
				cout<<count<<endl;
				for(int j=x+1 ; j<length ;j++)
				{
				if(isdigit(r[j])) count1++;
				}
				cout<<count1<<endl;
				if(count != count1)throw("wrong enteries 3");
			
				} //de bta3t elfor
			} //de bta3t elwhile
			infile.close();
		}
	if(infile.bad()) 
		{cout<<"file not read"<<endl;}
	
}
int main(int argc, char* argv[])
{ 
	try{
	string variables[num];
	CMatrix matrices[num];
	string var;
	string mat;
	string v;
	CMatrix m;
	int index = 0;
        int n=0;
	string s;
	if(argc>1)
	{
		string file = argv[1];
		ifstream infile(argv[1]);
		if(file =="errorsexample.m")
		{
		handlingErrors(file);	
		}
		if(!infile.bad())
		{
			while(getline(infile, s))	
			{
				if(s.find("\r")!=-1)s.erase(s.find("\r"),2);
				if(s == "")continue;
				if(s.find("=") != -1)
				{
					var = trim(s.substr(0,s.find_last_of('=')+1));
					mat = s.substr(s.find_last_of('=')+1, s.length()-s.find_last_of('=')-1);
					if(mat.find("[")!=-1 && mat.find("]")!=-1)
						m.copy(mat);//m=fix_matrix(mat,n);
					else if(mat.find("(")!=-1||mat.find(")")!=-1||mat.find("+")!=-1||mat.find("-")!=-1||mat.find("*")!=-1||mat.find("/")!=-1||mat.find("^")!=-1)
					{
						mat = trim(mat);
						if(mat.find(";")!=-1)mat = mat.substr(0,mat.length()-1);
						string*operators = new string[mat.length()];
						string*operands = new string[mat.length()];
						int ioperands = 0;
						int ioperators = 0;
						parse(mat,operators,operands,ioperators,ioperands);
						for(int i=0; i<ioperands; i++)cout << operands[i] << endl;

						int flag2 = 1;
						for(int i=0; i<ioperands; i++)
						{
							if(!isDouble(operands[i]))
							{
								for(int j=0; j<index; j++)
								{
									if(operands[i]==variables[j])
									{
										operands[i] = matrices[j].stringof();
										flag2 = 1;
										break;
									}
									else flag2=0;
								}
								if(flag2 == 0){cout << operands[i] << " is not defined" << endl;break;}
							}
						}
						if(flag2 == 0)continue;
						string s1 = solve(operators,operands,ioperators,ioperands);
						if(s1.find("[")==-1) 
						{
							CMatrix m2(atof(s1.c_str()));
							m = m2;
						}
						else
						{
							CMatrix m2(s1);
							m = m2;
						}
						delete[] operators;
						delete[] operands;
					}
					else if(mat.find("'")!=-1)
					{
						mat = trim(mat);
						string op1 = mat.substr(0,mat.find("'"));
						int index1, flag1=0;
						for(int i=0; i<index; i++)
						{
							if(variables[i] == op1)
							{
								index1 = i;
								flag1 = 1;
							}
							if(flag1 == 1) break;
						}
						if(flag1 != 1) {cout << op1 << " is not defined" << endl;continue;}
						CMatrix temp(matrices[index1].getnC(), matrices[index1].getnR());
						temp.transpose(matrices[index1]);
						m = temp;	
					}
					else
					{
						int flag=0; 
						mat = trim(mat);
						if(isDouble(mat)) 
						{
							CMatrix m1(atof(mat.c_str()));
							m = m1;
						}
						else
						{
							for(int i=0; i<index; i++)
							{
								if(variables[i] == mat)
								{
									m = matrices[i];
									flag=1;
									break;
								}
							}
							if(flag==0) cout << mat << " is not defined" << endl;
						}
					}
					while(var.find("=")!=-1)
					{
						int flag=0;
						v = var.substr(0,var.find('='));
						for(int i=0; i<index; i++)
						{
							if(variables[i] == v)
							{
								matrices[i] = m;
								flag=1;
							}
							if(flag==1)break;
						}
						if(flag==0)
						{
							variables[index] = v;
							matrices[index] = m;
							index ++;
						}
						var = var.substr(var.find("=")+1,var.length()-var.find("=")-1);
					}
				}
				else
				{
					int flag=0;
					s = trim(s);
					for(int i=0; i<index; i++)
					{
						if(variables[i] == s)
						{
							m = matrices[i];
							flag = 1;
							break;
						}
					}
					if(flag==0) cout << s << " is not defined" << endl;
				}
				if(s.find_last_of(';')!=s.length()-1)
					cout << m << endl;
			}
			cout << "File read succeeded" << endl;
		}
		else cout << " Failed" << endl;
	}
	else
	{
		while(getline(cin,s))
		{	
			if(s.find("\r")!=-1)s.erase(s.find("\r"),2);
				if(s == "")continue;
				if(s.find("=") != -1)
				{
					var = trim(s.substr(0,s.find_last_of('=')+1));
					mat = s.substr(s.find_last_of('=')+1, s.length()-s.find_last_of('=')-1);
					if(mat.find("[")!=-1 && mat.find("]")!=-1)
						m.copy(mat); //m=fix_matrix(mat,n);
					
					else if(mat.find("(")!=-1||mat.find(")")!=-1||mat.find("+")!=-1||mat.find("-")!=-1||mat.find("*")!=-1||mat.find("/")!=-1||mat.find("^")!=-1)
					{
						mat = trim(mat);
						if(mat.find(";")!=-1)mat = mat.substr(0,mat.length()-1);
						string*operators = new string[mat.length()];
						string*operands = new string[mat.length()];
						int ioperands = 0;
						int ioperators = 0;
						parse(mat,operators,operands,ioperators,ioperands);
						int flag2 = 1;
						for(int i=0; i<ioperands; i++)
						{
							if(!isDouble(operands[i]))
							{
								for(int j=0; j<index; j++)
								{
									if(operands[i]==variables[j])
									{
										operands[i] = matrices[j].stringof();
										flag2 = 1;
										break;
									}
									else flag2=0;
								}
								if(flag2 == 0){cout << operands[i] << " is not defined" << endl;break;}
							}
						}
						if(flag2 == 0)continue;
						string s1 = solve(operators,operands,ioperators,ioperands);
						if(s1.find("[")==-1) 
						{
							CMatrix m2(atof(s1.c_str()));
							m = m2;
						}
						else
						{
							CMatrix m2(s1);
							m = m2;
						}
						delete[] operators;
						delete[] operands;
					}
					else if(mat.find("'")!=-1)
					{
						mat = trim(mat);
						string op1 = mat.substr(0,mat.find("'"));
						int index1, flag1=0;
						for(int i=0; i<index; i++)
						{
							if(variables[i] == op1)
							{
								index1 = i;
								flag1 = 1;
							}
							if(flag1 == 1) break;
						}
						if(flag1 != 1) {cout << op1 << " is not defined" << endl;continue;}
						CMatrix temp(matrices[index1].getnC(), matrices[index1].getnR());
						temp.transpose(matrices[index1]);
						m = temp;	
					}
					else
					{
						int flag=0; 
						mat = trim(mat);
						if(isDouble(mat)) 
						{
							CMatrix m1(atof(mat.c_str()));
							m = m1;
						}
						else
						{
							for(int i=0; i<index; i++)
							{
								if(variables[i] == mat)
								{
									m = matrices[i];
									flag=1;
									break;
								}
							}
							if(flag==0) cout << mat << " is not defined" << endl;
						}
					}
					while(var.find("=")!=-1)
					{
						int flag=0;
						v = var.substr(0,var.find('='));
						for(int i=0; i<index; i++)
						{
							if(variables[i] == v)
							{
								matrices[i] = m;
								flag=1;
							}
							if(flag==1)break;
						}
						if(flag==0)
						{
							variables[index] = v;
							matrices[index] = m;
							index ++;
						}
						var = var.substr(var.find("=")+1,var.length()-var.find("=")-1);
					}
				}
				else
				{
					int flag=0;
					s = trim(s);
					for(int i=0; i<index; i++)
					{
						if(variables[i] == s)
						{
							m = matrices[i];
							flag = 1;
							break;
						}
					}
					if(flag==0) cout << s << " is not defined" << endl;
				}
				if(s.find_last_of(';')!=s.length()-1)
					cout << m << endl;
		}
	}
	delete[] variables;
	delete[] matrices;
	}
	catch(char* error)
	{
	cout<<"Error: "<<error<<endl;
	
	}
}
