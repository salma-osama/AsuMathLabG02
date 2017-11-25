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
		if(s[i] != '.' && !(isdigit(s[i])))
			return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	string variables[num];
	CMatrix matrices[num];
	string var;
	string mat;
	string v;
	CMatrix m;
	int index = 0;
	string s;
	char oper1 = '+', oper2 = '-', oper3 = '*', oper4 = '/';
	if(argc>1)
	{
		string file = argv[1];
		ifstream infile(argv[1]);
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
						m.copy(mat);
					else if(mat.find("./")!=-1)
					{
						mat = trim(mat);
						string op1 = mat.substr(0,mat.find("."));
						string op2;
						if(mat.find_last_of(';')!=mat.length()-1)
							op2 = mat.substr(mat.find("/")+1, mat.length()-mat.find("/")-1);
						else 
							op2 = mat.substr(mat.find("/")+1, mat.length()-mat.find("/")-2);
						int index2, flag2=0;
						for(int i=0; i<index; i++)
						{
							if(variables[i] == op2)
							{
								index2 = i;
								flag2 = 1;
							}
							if(flag2 == 1) break;
						}
						if(flag2 != 1) {cout << op2 << " is not defined" << endl;continue;}
						CMatrix temp;
						temp = matrices[index2];
						temp.dotDiv(atof(op1.c_str()));
						m = temp;
					}
					else if(mat.find(oper1)!=-1 || mat.find(oper2)!=-1 || mat.find(oper3)!=-1 || mat.find(oper4)!=-1)
					{
						mat = trim(mat);
						char oper;
						if(mat.find(oper1)!=-1)oper = oper1;
						else if(mat.find(oper2)!=-1)oper = oper2;
						else if(mat.find(oper3)!=-1)oper = oper3;
						else if(mat.find(oper4)!=-1)oper = oper4;
						string op1 = mat.substr(0,mat.find(oper));
						string op2;
						if(mat.find_last_of(';')!=mat.length()-1)
							{op2 = mat.substr(mat.find(oper)+1, mat.length()-mat.find(oper)-1);
							}
						else 
							op2 = mat.substr(mat.find(oper)+1, mat.length()-mat.find(oper)-2);
						int index1, flag1=0;
						int index2, flag2=0;
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
						if(!isDouble(op2))
						{
							for(int i=0; i<index; i++)
							{
								if(variables[i] == op2)
								{
									index2 = i;
									flag2 = 1;
								}
								if(flag2 == 1) break;
							}
							if(flag2 != 1) {cout << op2 << " is not defined" << endl;continue;}
						}
						if(oper == oper1) 
						{
							if(!isDouble(op2))
							{
								if(matrices[index1].getnR() != matrices[index2].getnR()||
									matrices[index1].getnC()!=matrices[index2].getnC())
								{
									cout << "Invalid matrix dimension" << endl;
									continue;
								}
								m = matrices[index1] + matrices[index2];
							}	
							else m = matrices[index1] + atof(op2.c_str());
						}
						else if(oper == oper2) 
						{
							if(!isDouble(op2))
							{
								if(matrices[index1].getnR() != matrices[index2].getnR()||
									matrices[index1].getnC()!=matrices[index2].getnC())
								{
									cout << "Invalid matrix dimension" << endl;
									continue;
								}
								m = matrices[index1] - matrices[index2];
							}
							else m = matrices[index1] - atof(op2.c_str());
						}
						else if(oper == oper3) 
						{
							if(!isDouble(op2))
							{
								if(matrices[index1].getnC() != matrices[index2].getnR())
								{
									cout << "Invalid matrix dimension" << endl;
									continue;
								}
								m = matrices[index1] * matrices[index2];
							}
							else m = matrices[index1] * atof(op2.c_str());
						}
						else if(oper == oper4) 
						{
							if(!isDouble(op2))
							{
								if(matrices[index1].getnC() != matrices[index2].getnR()||
									matrices[index2].getnR() != matrices[index2].getnC())
								{
									cout << "Invalid matrix dimension" << endl;
									continue;
								}
								try
								{
									m = matrices[index1] / matrices[index2];
								}
								catch(char const*std)
								{
									cout << std << endl;
									continue;
								}
							}
							else m = matrices[index1] / atof(op2.c_str());
						}
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
								if(s.find_last_of(';')!=s.length()-1)
								{
									cout << v << " = " << endl;
									cout << m << endl;
								}
							}
							if(flag==1)break;
						}
						if(flag==0)
						{
							variables[index] = v;
							matrices[index] = m;
							index ++;
							if(s.find_last_of(';')!=s.length()-1)
							{
								cout << v << " = " << endl;
								cout << m << endl;
							}
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
			}
			cout << "File read succeeded" << endl;
		}
		else cout << " Failed" << endl;
	}
	else
	{
		while(getline(cin,s))
		{	
			if(s.find("=") != -1)
			{
				var = trim(s.substr(0,s.find_last_of('=')+1));
				mat = s.substr(s.find_last_of('=')+1, s.length()-s.find_last_of('=')-1);
				if(mat.find("[")!=-1 && mat.find("]")!=-1)
					m.copy(mat);
				else if(mat.find("./")!=-1)
				{
					mat = trim(mat);
					string op1 = mat.substr(0,mat.find("."));
					string op2;
					if(mat.find_last_of(';')!=mat.length()-1)
						op2 = mat.substr(mat.find("/")+1, mat.length()-mat.find("/")-1);
					else 
						op2 = mat.substr(mat.find("/")+1, mat.length()-mat.find("/")-2);
					int index2, flag2=0;
					for(int i=0; i<index; i++)
					{
						if(variables[i] == op2)
						{
							index2 = i;
							flag2 = 1;
						}
						if(flag2 == 1) break;
					}
					if(flag2 != 1) {cout << op2 << " is not defined" << endl;continue;}
					CMatrix temp;
					temp = matrices[index2];
					temp.dotDiv(atof(op1.c_str()));
					m = temp;
				}
				else if(mat.find(oper1)!=-1 || mat.find(oper2)!=-1 || mat.find(oper3)!=-1 || mat.find(oper4)!=-1)
				{
					mat = trim(mat);
					char oper;
					if(mat.find(oper1)!=-1)oper = oper1;
					else if(mat.find(oper2)!=-1)oper = oper2;
					else if(mat.find(oper3)!=-1)oper = oper3;
					else if(mat.find(oper4)!=-1)oper = oper4;
					string op1 = mat.substr(0,mat.find(oper));
					string op2;
					if(mat.find_last_of(';')!=mat.length()-1)
						op2 = mat.substr(mat.find(oper)+1, mat.length()-mat.find(oper)-1);
					else 
						op2 = mat.substr(mat.find(oper)+1, mat.length()-mat.find(oper)-2);
					int index1, flag1=0;
					int index2, flag2=0;
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
					if(!isDouble(op2)) 
					{
						for(int i=0; i<index; i++)
						{
							if(variables[i] == op2)
							{
								index2 = i;
								flag2 = 1;
							}
							if(flag2 == 1) break;
						}
						if(flag2 != 1) {cout << op2 << " is not defined" << endl;continue;}
					}
					if(oper == oper1) 
					{
						if(!isDouble(op2))
						{
							if(matrices[index1].getnR() != matrices[index2].getnR()||
								matrices[index1].getnC()!=matrices[index2].getnC())
							{
								cout << "Invalid matrix dimension" << endl;
								continue;
							}
							m = matrices[index1] + matrices[index2];
						}
						else m = matrices[index1] + atof(op2.c_str());
					}
					else if(oper == oper2) 
					{
						if(!isDouble(op2))
						{
							if(matrices[index1].getnR() != matrices[index2].getnR()||
								matrices[index1].getnC()!=matrices[index2].getnC())
							{
								cout << "Invalid matrix dimension" << endl;
								continue;
							}
							m = matrices[index1] - matrices[index2];
						}
						else m = matrices[index1] - atof(op2.c_str());
					}
					else if(oper == oper3) 
					{
						if(!isDouble(op2))
						{
							if(matrices[index1].getnC() != matrices[index2].getnR())
							{
								cout << "Invalid matrix dimension" << endl;
								continue;
							}
							m = matrices[index1] * matrices[index2];
						}
						else m = matrices[index1] * atof(op2.c_str());
					}
					else if(oper == oper4) 
					{
						if(!isDouble(op2))
						{
							if(matrices[index1].getnC() != matrices[index2].getnR()||
								matrices[index2].getnR() != matrices[index2].getnC())
							{
								cout << "Invalid matrix dimension" << endl;
								continue;
							}
							try{
							m = matrices[index1] / matrices[index2];}
							catch(char const*std){cout << std << endl;continue;}
						}
						else m = matrices[index1] / atof(op2.c_str());
					}
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
	return 0;
}
