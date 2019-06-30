//////
/*
	Name: 
	Copyright: 
	Author: 
	Date: 
	Description: 
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<math.h>
#include"struct.h"
using namespace std;

//input the matrix;
//input method

void load_data(char* file,vector<string>& vec_c,vector<string>& vec_g ,vector< vector<double> >& mv)
{

	ifstream in(file);
	istringstream istr;
	string s,s_name,s_c,s_g;
	double data;
	vector<double> data_;
	//read first line
	getline(in,s);
	istr.str(s);
	istr>>s_name;
	while(istr>>s_c) vec_c.push_back(s_c);
	istr.clear();
	//read from second line
	while(getline(in,s))
	{
	    istr.str(s);
	    istr>>s_g;
	    vec_g.push_back(s_g);
	    while(istr>>data) data_.push_back(data);
	    mv.push_back(data_);
	    istr.clear();
	    data_.clear();
	}
	return;
}
///

vector<double> add_v(vector<double>&a,vector<double>&b)
{
	for(int i=0;i<b.size();i++)
	{
		a.push_back(b[i]);
	}
	return a;
}

////
/*
void add_v(vector<double>&a,vector<double>&b)
{
	for(int i=0;i<b.size();i++)
	{
		a.push_back(b[i]);
	}
	return;
}
*/
// the max size seq2[i] of seq2

vector<double> maxa(vector<vector<double> >a)
{
	int i;
	vector<double>maxa;
	for(i=0;i<a.size();i++)
	{
		if(maxa.size()<a[i].size()) 
		{
			maxa.swap(a[i]);
		}
	}			
	return maxa;
}

///
vector<vector<double> > deletea_w(vector<vector<double> >a,int k2)
{
	int i;
	vector<vector<double> >b;
	for(i=0;i<a.size();i++)
	{
		if(a[i][0]>=k2)
		{ 
		 b.push_back(a[i]);
		} 
		
	}
	vector<vector<double> >(0).swap(a);
	return b;
}




///

vector<vector<double> > deletea2(vector<vector<double> >a,int k2)
{
	int i;
	vector<vector<double> >b;
	for(i=0;i<a.size();i++)
	{
		if(a[i][3]>=k2)
		{ 
		 b.push_back(a[i]);
		} 
		
	}
	vector<vector<double> >(0).swap(a);
	return b;
}

//sort comp

bool compare_s(vector<double>&a,vector<double>&b)
{
	vector<double>a1(a[0]);
	vector<double>b1(b[0]);
	a1.assign(a.begin()+5,a.begin()+5+a[0]);
	b1.assign(b.begin()+5,b.begin()+5+b[0]);
	bool comp=(a1>b1);
	vector<double>(0).swap(a1);
	vector<double>(0).swap(b1);
	return comp;
}


///unique comp

bool compare_u(vector<double>&a,vector<double>&b)
{
	vector<double>a1(a[0]);
	vector<double>b1(b[0]);
	a1.assign(a.begin()+5,a.begin()+5+a[0]);
	b1.assign(b.begin()+5,b.begin()+5+b[0]);
	bool comp=(a1==b1);
	vector<double>(0).swap(a1);
	vector<double>(0).swap(b1);
	return comp;
}

//sort seeds

bool compare_sd(vector<double>&a,vector<double>&b)
{
    int a1=a[3];
    int b1=b[3];
   // cout<<"####3"<<endl;
    return(a1>b1);
}





//delete the repeat ones
 //problem
 
vector<vector<double> > deletea(vector<vector<double> >a)//,int k2) 
{
	sort(a.begin(),a.end(),compare_s);
	a.erase(unique( a.begin(), a.end() ,compare_u), a.end() );//I think that here must be a problem.		
	return a;
}
//


bool compare_int(vector<double>&a,vector<double>&b)
{
if(b.size()==0)
{return false;}
else{

	return((a[0]*a[3])<(b[0]*b[3]));}
}








bool operator_v0(vector<double>&a,vector<double>&b)
{
	double i1=sqrt(a[0]*a[3])/(a[0]+a[3]);
	double i2=sqrt(b[0]*b[3])/(b[0]+b[3]);
	return (i1>i2);
}
//
bool operator_v(vector<double>&a,vector<double>&b)
{
	return a.size()>b.size();
}
//

bool operator_v1(vector<double>&a,vector<double>&b)//ÐèÒªÐÞ¸Ä 
{
   vector<double> unq_a;
   vector<double> unq_b;

   unq_a.assign(a.begin()+5+a[0],a.end());    
   sort(unq_a.begin(),unq_a.end());
   int nunq_a=std::unique(unq_a.begin(),unq_a.end())-unq_a.begin();
   unq_b.assign(b.begin()+5+b[0],b.end());       
   sort(unq_b.begin(),unq_b.end());
   int nunq_b=std::unique(unq_b.begin(),unq_b.end())-unq_b.begin();
   vector<double>(0).swap(unq_b);
   vector<double>(0).swap(unq_a);   
	return (a[0]*nunq_a)>(b[0]*nunq_b);


}

bool operator_v2(vector<double>&a,vector<double>&b)
{
	return (a[0]>b[0]);
}

//
bool operator_v3(vector<double>&a,vector<double>&b)
{
	return (a[4]<b[4]);
}
//

///filtering

vector<vector<double> > filtering(vector<vector<double> >a,int col_s,float filter_p)
{
	int a_s=a.size();
	if(a_s==0)
	{	
	return a;
	}
//	cout<<"a_s= "<<a_s<<endl;
	bool flag[a_s];
	for(int i=0;i<a_s;i++)
	{
		flag[i]=true;
	}
	vector<vector<double> >temp_s1;
	for(int i=0;i<a_s;i++)
	{

		if(flag[i])
		{
			for(int j=i+1;j<a_s;j++)
			{
				int score=0;			
				if(flag[j])
				{
					int scores[col_s];
					memset(scores,0,col_s*sizeof(int));		
					for(int i1=5;i1<a[i][0]+5;i1++)
					{
						scores[(int)a[i][i1]]+=1;
					}	
					for(int i1=5;i1<a[j][0]+5;i1++)
					{
						scores[(int)a[j][i1]]+=1;
					}					
					for(int b=0;b<col_s;b++)
					{
						if(scores[b]==2)
						{
							score+=1;
						}
					}
	//				cout<<"score= "<<score<<endl;
					if(score>=floor(min(a[i][0],a[j][0])*filter_p)&&a[i][0]*a[i][3]>=a[j][0]*a[j][3])
					{
						flag[j]=false;
					}								
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
	}
	for(int i3=0;i3<a_s;i3++)
	{
		if(flag[i3])
		{
			temp_s1.push_back(a[i3]);
		}
	}		
	return temp_s1;
}

///cheak seed
/*
vector<bool> cheak_seed(vector<double>&a,vector<vector<double> >&b,vector<bool> c)
{
if(a.size()==0)
{return c;}
else{
    vector<double>temp;
    int ll=a[0]+5;
    temp.assign(a.begin()+5,a.begin()+ll);
    //cout<<"here"<<endl;
    for (int i=0;i<b.size();i++)
    {
        if(c[i])
        {
        //cout<<"where"<<endl;
        if(((!(find(temp.begin(),temp.end(),b[i][5])==temp.end()))||(!(find(temp.begin(),temp.end(),b[i][6])==temp.end()))||(!(find(temp.begin(),temp.end(),b[i][7])==temp.end()))))
        {
        c[i]=0;
        }
        else{
        continue;
        }
        }
    }
    vector<double>(0).swap(temp);
    return c;}
}
/////
*/
/*
///8-6
vector<bool> cheak_seed(vector<double>&a,vector<vector<double> >&b,vector<bool> c)
{
if(a.size()==0)
{return c;}
else{
    vector<double>temp;
    int ll=a[0]+5;
    temp.assign(a.begin()+5,a.begin()+ll);
    //cout<<"here"<<endl;
    for (int i=0;i<b.size();i++)
    {
        if(c[i])
        {
        //cout<<"where"<<endl;
        if((((find(temp.begin(),temp.end(),b[i][5])==temp.end()))||((find(temp.begin(),temp.end(),b[i][6])==temp.end()))||((find(temp.begin(),temp.end(),b[i][7])==temp.end()))))
        {
        continue;
        }
        else{
        c[i]=0;
        }
        }
    }
    vector<double>(0).swap(temp);
    return c;}
}
////
*/

vector<bool> cheak_seed(vector<double>&a,vector<vector<double> >&b,vector<bool> c)

{
if(a.size()==0)
{return c;}
else{

    vector<double>temp;
    int ll=a[0]+5;
    temp.assign(a.begin()+5,a.begin()+ll);
    for (int i=0;i<b.size();i++)
    {
        if(c[i])
        {
        if(((!(find(temp.begin(),temp.end(),b[i][5])==temp.end()))&&(!(find(temp.begin(),temp.end(),b[i][6])==temp.end()))&&(!(find(temp.begin(),temp.end(),b[i][7])==temp.end()))))
        {
        c[i]=0;
        }
        else{
        continue;
        }

        }

    }

    vector<double>(0).swap(temp);

    return c;}

}







///N!

bool test(double b,double a)
{
	if(b<300)
	{
		return a==3;
	}
	else
	{	

		return (b)/((sqrt(2*a*3.14))*pow((a/2.718),a))>10;
	}	
	
}










int upper_bound(int arr[], int s, int e, int key)
{
    int mid;
    if (arr[e] <= key)
        return e + 1;
    while (s < e)
    {
        mid = s + (e - s) / 2;
        if (arr[mid] <= key)
            s = mid + 1;
        else
            e = mid;
    }
    return s;
}
//

int LIS(vector<double> &d, int n)
{
	if (n==0)
	{
		return 0;
	}
	else
	{
    int i = 0; int len = 1; int *end=new int[n+1];
    end[1] = d[0]; //初始化：长度�?的LIS末尾为d[0]
    for (i = 1; i < n; i++)
    {
        int pos = upper_bound(end, 1, len, d[i]); //�
        end[pos] = d[i];
        if (len < pos) //按需要更新LIS长度
            len = pos;
    }
    delete[] end;
    return len;
    }
}







/*
vector<vector<double> > filter2(vector<vector<double> >a)
{
	int as=a.size();
	for(int i;i<as;i++)
	{
		a[i]	
		
	}
	
	
	
	
}

*/























long double get_pvalues (float a, int b)
{
	long double x,y,z,t;
	x=1.0;
	t=exp(1);
	y=exp(-a);
	z=sqrt(2*3.1415926*b);
	for (int i=0;i<b;i++)
	{
		x=x*t*a/b;
	}
	return (x*y/z);

}
//real
void sc3(vector<vector<double> >a,int best,const char* fn)
{
	ofstream fon(fn);
//	int a_b=a.size();
    int nn=a.size();
    int ni=min(best,nn);
    vector<double>v_genes;
	for (int t=0;t<ni;t++)
	 {
       v_genes.assign(a[t].begin()+5+a[t][0],a[t].end());
       sort(v_genes.begin(),v_genes.end());
       v_genes.erase(unique(v_genes.begin(),v_genes.end()),v_genes.end());       
       fon<<"BC: "<<t<<endl;
       fon<<" Genes ["<<v_genes.size()<<"]: ";
       for(int i=0;i<v_genes.size();i++)
       {
           fon<<genes[(int)v_genes[i]]<<" ";
       }
       v_genes.clear();
       
	 	int a1= a[t][0]+5;
		 fon<<"\n";
		 fon<<" Conds ["<<a[t][0]<<"]: ";
		for(int t3=5;t3<a1;t3++)
	 	{
	 		fon<<conds[(int)a[t][t3]]<<" ";
	 		
		 }

		 fon<<"\n";	
		 fon<<"\n";
}
}


/*
void sc3(vector<vector<double> >a,int best,const char* fn)
{
	ofstream fon(fn);
//	int a_b=a.size();
    int nn=a.size();
    int ni=min(best,nn);
    vector<double>v_genes;
	for (int t=0;t<ni;t++)
	 {
       v_genes.assign(a[t].begin()+5+a[t][0],a[t].end());
       sort(v_genes.begin(),v_genes.end());
       v_genes.erase(unique(v_genes.begin(),v_genes.end()),v_genes.end());       
       for(int i=0;i<v_genes.size();i++)
       {
           fon<<v_genes[i]<<" ";
       }
       v_genes.clear();
       
	 	int a1= a[t][0]+5;
		 fon<<"\n";

		for(int t3=5;t3<a1;t3++)
	 	{
	 		fon<<a[t][t3]<<" ";
	 		
		 }

		 fon<<"\n";	
		 fon<<"\n";
}
}
*/
/*

void sc3(vector<vector<double> >a,int best,const char* fn)
{
	ofstream fon(fn);
	for (int t=0;t<best;t++)
	 {
	 	int a1= a[t][0]+5;
		int a3=a[t].size();
		fon<<"v_genes: "<<endl;
		 for(int t3=a1;t3<a3;t3++)
	 	{
	 		fon<<a[t][t3]<<" ";
	 		
		 }
		 fon<<"\n";
		fon<<"conditions: "<<endl;
		for(int t3=5;t3<a1;t3++)
	 	{
	 		fon<<a[t][t3]<<" ";
	 		
		 }

		 fon<<"\n";	
		 fon<<"\n";
	}
}

*/











