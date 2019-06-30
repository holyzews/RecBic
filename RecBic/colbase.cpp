
#include<iostream>
#include<omp.h>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<math.h>
#include"colbase.h"
#include"struct.h"
//#include"cluster.h"
using namespace std;

void colbased(const char* fn)
{
	
		//input your arr_c.
		FILE *fw = mustOpen(fn,"w");
		

		int col1;
		int col2;
		double m=rows;

		int n=cols;
		int bestofbic,cc,kk;
		bestofbic=po->RPT_BLOCK;
		int bestofbic1=100*bestofbic;
		
		if(po->ROW_MINWIDTH==0.05)
		{cc=(int)(rows*0.05);}
		else
		{cc=po->ROW_MINWIDTH;}
		if(po->COL_MAXWIDTH!=0)
		{
		kk=po->COL_MAXWIDTH;
		}
		else
		{
		kk=0.8*cols;
			}

		

		int i6,i7;
		vector<vector< double> >bic_s1;
		vector<vector< double> >bic_s4;


	if(!po->IS_const)
	{
	int Part;
	if(n<300)
	{
    	Part=3;
    	}
    	else{
    	Part=int(n/70);
    	}
    	int step_k;
    	int cendi;
    	int stepc=cols/Part;
    	cout<<"Generating seeds"<<endl;;
	for(step_k=0;step_k<Part;step_k++)
	{	
		vector<double>bic;	
		vector<double>v_cols;
		vector<double>v_rows_a;
		vector<double>v_rows_d;
		cendi=(step_k+1)*stepc;
		if(step_k==Part-1)
		{
			cendi=cols;	}		
		for (col1=step_k*stepc;col1<cendi;col1++)
		{
				for (col2=step_k*stepc;col2<cendi;col2++)
				{
						if(col2!=col1)
						{
								v_cols.push_back(col1);
								v_cols.push_back(col2);
								//here bug 
								for ( int line=0;line<m;line++)
								{		
										if(arr_c[line][col1]*arr_c[line][col2]!=0)
										{
										if (arr_c[line][col1]>=arr_c[line][col2])
										{
												v_rows_a.push_back(line);
										}
										if(arr_c[line][col1]<arr_c[line][col2])
										{
												v_rows_d.push_back(line);
										}
										}
								}
								
								{
								
										bic.push_back(2);
										bic.push_back(v_rows_a.size());
										bic.push_back(v_rows_d.size());
										bic.push_back(v_rows_a.size()+v_rows_d.size());

										bic.push_back(1);
									
										bic=add_v(bic,v_cols);
										bic=add_v(bic,v_rows_a);
										bic=add_v(bic,v_rows_d);
										bic_s1.push_back(bic); 
					 
								}							
								
								vector<double>(0).swap(v_cols);
								vector<double>(0).swap(v_rows_a);
								vector<double>(0).swap(v_rows_d);
								vector<double>(0).swap(bic); 
								
						}			
				}
		}
		}
		
	///////////######################################################################3///////////////	
		//biclusters temp for i2 cols		
		
		//biclusters temp in the q step 
		vector<vector< double> >bic_s5;//the final biclusters
		
		//the col we add, 
		int i2;//the seq we add to,
		int q=3;//q represents the seq size of col,this is important,	
		
		int l_s;
	
		int canshu;
		vector<double>unique_rows;
		
            l_s=bic_s1.size();//the size of seq1 	
				//	ss=q;
			
/////////////////////////////////////////////////
				vector<vector< double> >bic_s3;
				#pragma omp parallel
				{	
				vector< vector<double>> subbic_s3;
				#pragma omp for nowait									 
				for (i2=0;i2<l_s;i2++)
				{
				
				int s;//s rep where we put the col3
				int ms=6;
				int j;
				vector<vector< double> >bic_s2;
				vector<double>bic;
				vector<double>v_cols;
				vector<double>cols_int;	
				vector<double>v_rows_a;
				vector<double>v_rows_d;
						int cols_i2= 7;
						int rows_i2=7+bic_s1[i2][1];
						int rows_mi2=7+bic_s1[i2][3];
						int rows_li2=bic_s1[i2].size();
						
						vector<double>(2).swap(cols_int);
						
						cols_int.assign(bic_s1[i2].begin()+5, bic_s1[i2].begin()+7);
						for (int col3=0;col3<n;col3++)
						{
								
								if(find(cols_int.begin(),cols_int.end(), col3)==cols_int.end())
								{	
										
										v_cols=cols_int;
											
										v_cols.insert(v_cols.begin(),col3);	
										for (j=cols_i2;j<rows_i2;j++)
										{
												
												if(arr_c[(int)bic_s1[i2][j]][col3]!=0)
												{
												
												if (arr_c[(int)bic_s1[i2][j]][col3]>=arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][5]])
												{	
														v_rows_a.push_back(bic_s1[i2][j]);
												}
												}
												
										}
										for (j=rows_i2;j<bic_s1[i2].size();j++)
										{
												if(arr_c[(int)bic_s1[i2][j]][col3]!=0)
												{
												if (arr_c[(int)bic_s1[i2][j]][col3]<=arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][5]])
												{	
														v_rows_d.push_back(bic_s1[i2][j]);
												}
												}
										}
										if(v_rows_a.size()>=v_rows_d.size())
										{	
										

												bic.push_back(v_cols.size());
												bic.push_back(v_rows_a.size());
												bic.push_back(v_rows_d.size());
												bic.push_back(v_rows_a.size()+v_rows_d.size());//
												bic.push_back(1);              
												bic=add_v(bic,v_cols);
												bic=add_v(bic,v_rows_a);
												bic=add_v(bic,v_rows_d);
												bic_s2.push_back(bic);
										}									
												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic); 
									

										for(s=6;s<=ms;s++)
										{
												v_cols=cols_int;
												v_cols.insert(v_cols.begin()+s-5,col3);
												for (j=cols_i2;j<rows_i2;j++)
												{
														if(arr_c[(int)bic_s1[i2][j]][col3]!=0){
														if (arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][s-1]]>=arr_c[(int)bic_s1[i2][j]][col3]&&arr_c[(int)bic_s1[i2][j]][col3]>=arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][s]])						
														{	
																v_rows_a.push_back(bic_s1[i2][j]);	
														}
														}
												}
												for (j=rows_i2;j<rows_li2;j++)
												{
														if(arr_c[(int)bic_s1[i2][j]][col3]!=0)
														{
														if (arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][s-1]]<=arr_c[(int)bic_s1[i2][j]][col3]&&arr_c[(int)bic_s1[i2][j]][col3]<=arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][s]])						
														{	
																v_rows_d.push_back(bic_s1[i2][j]);	
														}
														}
												}					
												if(v_rows_a.size()>=v_rows_d.size())
												{
														bic.push_back(v_cols.size());
														bic.push_back(v_rows_a.size());
														bic.push_back(v_rows_d.size());
														bic.push_back(v_rows_a.size()+v_rows_d.size());//
														bic.push_back(1);
														bic=add_v(bic,v_cols);
														bic=add_v(bic,v_rows_a);
														bic=add_v(bic,v_rows_d);
														bic_s2.push_back(bic);
												}																				
												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic);	
										}
										
		
										v_cols=cols_int;

										v_cols.push_back(col3);

										for (j=cols_i2;j<rows_i2;j++)
										{
												if(arr_c[(int)bic_s1[i2][j]][col3]!=0)
												{
												if (arr_c[(int)bic_s1[i2][j]][col3]<=arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][ms]])
												{	
														v_rows_a.push_back(bic_s1[i2][j]);
												}
												}
										}

										for (j=rows_i2;j<rows_li2;j++)
										{
												if(arr_c[(int)bic_s1[i2][j]][col3]!=0)
												{
												if (arr_c[(int)bic_s1[i2][j]][col3]>=arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][ms]])
												{	
														v_rows_d.push_back(bic_s1[i2][j]);
												}
												}
										}
										if(v_rows_a.size()>=v_rows_d.size())
										{
											
												bic.push_back(v_cols.size());
												bic.push_back(v_rows_a.size());
												bic.push_back(v_rows_d.size());
												bic.push_back(v_rows_a.size()+v_rows_d.size());//
												bic.push_back(1);
												bic=add_v(bic,v_cols);
												bic=add_v(bic,v_rows_a);
												bic=add_v(bic,v_rows_d);
												bic_s2.push_back(bic);
										}

												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic);
								
																																
								}
	
						}
						
						int all_score=0;
						int max_score=0;
						long double p_value;
						float ave_score;
						int p_i;
						int pmax_i=0;
						
						if(bic_s2.size()==0)
						{
						continue;
						}
						
						for(p_i=0;p_i<bic_s2.size();p_i++)
						{
							
							all_score=all_score+bic_s2[p_i][3];
							if(bic_s2[p_i][3]>max_score)
							{
								max_score=bic_s2[p_i][3];
								pmax_i=p_i;
							}
						}
						ave_score=(all_score*1.0)/bic_s2.size();
						p_value=get_pvalues(ave_score,max_score);
						vector<double>bic_int;					
						bic_int=bic_s2[pmax_i];	
						vector<vector<double> >(0).swap(bic_s2);					
						bic_int[4]=p_value;								
    					subbic_s3.push_back(bic_int);
	   								
						}//// bingxing for jieshu//
					#pragma omp critical
					{
bic_s3.insert(bic_s3.end(),subbic_s3.begin(),subbic_s3.end());}
						}
						
				
				bic_s1=deletea2(bic_s3,cc);	///cc is here;
				bic_s1=deletea(bic_s1);
				sort(bic_s1.begin(),bic_s1.end(),operator_v1);
				cout<<"Totally "<<bic_s1.size()<<" seeds"<<endl;
				//bic_s1=filtering(bic_s1,3,0.6);
				

		
		//////#############################################333/////////////////
		
		
		vector<vector<double> >seeds;
		seeds=bic_s1;
		
		//int shuchu=po->COL_MAXWIDTH*bestofbic*0.7;//改之?
		int shuchu=bestofbic1;
		int coutshu=0;
		int seed_len=bic_s1.size();
		vector<bool>seed_flag(seed_len,1);
		vector<double> temp_step;
		vector<double> bic_max;
		vector<double> bic_max2;		
		int seed_len1=bic_s1.size();
		
		//sc3(bic_s1,seed_len1,fn);//2018.6.20
		//while(q<kk)
		cout<<"Expanding"<<endl;
		for (i2=0;i2<seed_len;i2++)
		{
		if(coutshu>shuchu)
    	{
    	break;
    	
		}
		else{
		if(seed_flag[i2])
		{
		
		temp_step=seeds[i2];
		
		
		for(q=3;q<kk;q++)
		{     
        		cout<<".";
		int ms;
		int s;
		int j;
		vector<vector< double> >bic_s2;
		vector<double>cols_int;
		vector<double>bic;	
		vector<double>v_cols;
		vector<double>v_rows_a;
		vector<double>v_rows_d;
        		vector<double> bic_int;
			
				//l_s=bic_s1.size();//the size of seq1 	
				//	ss=q;
				ms = q+4;
				//cout<<"coladded= "<<q<<endl;
				if(l_s<1)
				{
					break;
				}	
				if(temp_step[3]<2){break;}
										 
						int cols_i2= q+5;
						int rows_i2=q+5+temp_step[1];
						int rows_mi2=q+5+temp_step[3];
						int rows_li2=temp_step.size();

						vector<double>(q).swap(cols_int);
						cols_int.assign(temp_step.begin()+5, temp_step.begin()+5+q);
						for (int col3=0;col3<n;col3++)
						{
									
								if(find(cols_int.begin(),cols_int.end(), col3)==cols_int.end())
								{	
										v_cols=cols_int;
										v_cols.insert(v_cols.begin(),col3);
										for (j=cols_i2;j<rows_i2;j++)
										{
												if(arr_c[(int)temp_step[j]][col3]!=0)
												{
												if (arr_c[(int)temp_step[j]][col3]>=arr_c[(int)temp_step[j]][(int)temp_step[5]])
												{	
														v_rows_a.push_back(temp_step[j]);
												}
												}
										}
										for (j=rows_i2;j<temp_step.size();j++)
										{
												if(arr_c[(int)temp_step[j]][col3]!=0)
												{
												if (arr_c[(int)temp_step[j]][col3]<=arr_c[(int)temp_step[j]][(int)temp_step[5]])
												{	
														v_rows_d.push_back(temp_step[j]);
												}
												}
										}
										if(v_rows_a.size()>=v_rows_d.size())
										{	

												bic.push_back(v_cols.size());
												bic.push_back(v_rows_a.size());
												bic.push_back(v_rows_d.size());
												bic.push_back(v_rows_a.size()+v_rows_d.size());//
												bic.push_back(1);              
												bic=add_v(bic,v_cols);
												bic=add_v(bic,v_rows_a);
												bic=add_v(bic,v_rows_d);
												bic_s2.push_back(bic);												

										}									
												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic); 

										for(s=6;s<=ms;s++)
										{
												v_cols=cols_int;
												v_cols.insert(v_cols.begin()+s-5,col3);
												for (j=cols_i2;j<rows_i2;j++)
												{
														if(arr_c[(int)temp_step[j]][col3]!=0)
														{
														if (arr_c[(int)temp_step[j]][(int)temp_step[s-1]]>=arr_c[(int)temp_step[j]][col3]&&arr_c[(int)temp_step[j]][col3]>=arr_c[(int)temp_step[j]][(int)temp_step[s]])						
														{	
																v_rows_a.push_back(temp_step[j]);	
														}
														}
												}
												for (j=rows_i2;j<rows_li2;j++)
												{
														if(arr_c[(int)temp_step[j]][col3]!=0)
														{
														if (arr_c[(int)temp_step[j]][(int)temp_step[s-1]]<=arr_c[(int)temp_step[j]][col3]&&arr_c[(int)temp_step[j]][col3]<=arr_c[(int)temp_step[j]][(int)temp_step[s]])						
														{	
																v_rows_d.push_back(temp_step[j]);	
														}
														}
												}					
												if(v_rows_a.size()>=v_rows_d.size())
												{
														bic.push_back(v_cols.size());
														bic.push_back(v_rows_a.size());
														bic.push_back(v_rows_d.size());
														bic.push_back(v_rows_a.size()+v_rows_d.size());//
														bic.push_back(1);
														bic=add_v(bic,v_cols);
														bic=add_v(bic,v_rows_a);
														bic=add_v(bic,v_rows_d);
														bic_s2.push_back(bic);
												}																				
												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic);														
										}	
										v_cols=cols_int;
										v_cols.push_back(col3);
										for (j=cols_i2;j<rows_i2;j++)
										{
												if(arr_c[(int)temp_step[j]][col3]!=0)
												{
												if (arr_c[(int)temp_step[j]][col3]<=arr_c[(int)temp_step[j]][(int)temp_step[ms]])
												{	
														v_rows_a.push_back(temp_step[j]);
												}
												}
										}

										for (j=rows_i2;j<rows_li2;j++)
										{
												if(arr_c[(int)temp_step[j]][col3]!=0)
												{
												if (arr_c[(int)temp_step[j]][col3]>=arr_c[(int)temp_step[j]][(int)temp_step[ms]])
												{	
														v_rows_d.push_back(temp_step[j]);
												}
												}
										}
										if(v_rows_a.size()>=v_rows_d.size())
										{
												bic.push_back(v_cols.size());
												bic.push_back(v_rows_a.size());
												bic.push_back(v_rows_d.size());
												bic.push_back(v_rows_a.size()+v_rows_d.size());//
												bic.push_back(1);
												bic=add_v(bic,v_cols);
												bic=add_v(bic,v_rows_a);
												bic=add_v(bic,v_rows_d);
												bic_s2.push_back(bic);
										}
												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic);
																																
								}
						}						
						int all_score=0;
						int max_score=0;
						long double p_value;
						float ave_score;
						int p_i;
						int pmax_i=0;
						
						if(bic_s2.size()==0)
						{
						break;}
						
						for(p_i=0;p_i<bic_s2.size();p_i++)
						{
							
							all_score=all_score+bic_s2[p_i][3];
							if(bic_s2[p_i][3]>max_score)
							{
								max_score=bic_s2[p_i][3];
								pmax_i=p_i;
							}
						}
						ave_score=(all_score*1.0)/bic_s2.size();
						p_value=get_pvalues(ave_score,max_score);
											
						bic_int=bic_s2[pmax_i];
						vector<vector<double> >(0).swap(bic_s2);						
						bic_int[4]=p_value;
						
						//if(q==3)
						if(test(rows,q))
						
						{
	
						temp_step.swap(bic_int);
    					vector<double>(0).swap(bic_int);
    					bic_max=temp_step;
    					bic_max2=temp_step;//9.3
		
						continue;}
						else{

						if(compare_int(bic_int, bic_max))//int<max

						{

    						temp_step.swap(bic_int);

    						vector<double>(0).swap(bic_int);	

						}

						else//int>=max

						{

						if(compare_int(bic_int,bic_max2)){//int<max2 7int=max=max2, 8int>max2,max2=int, 9int<max<max2,10max<int<max2
						
						bic_max=bic_int;					
						temp_step.swap(bic_int);
						vector<double>(0).swap(bic_int);
						}
						else{//int>=max2

    						bic_max2=bic_int;

    						temp_step.swap(bic_int);

    						vector<double>(0).swap(bic_int);
    						}
	

						}

							}




		}//kk for ends here	
	bic_s4.push_back(bic_max);			
       //seed_flag=cheak_seed(bic_max,seeds,seed_flag);       
       vector<double>(0).swap(bic_max);
	 bic_s4.push_back(bic_max2);//9.3
       seed_flag=cheak_seed(bic_max2,seeds,seed_flag);//9.3  
       	
        vector<double>(0).swap(bic_max2);//9.3     
       seed_flag[i2]=0;
       
    	coutshu+=1;
	
		}
		}
		
		}
		





		if(bic_s4.size()==0)
		{
			cout<<"no biclusters,you need to relax your limits(eg:-x to set less rows)"<<endl; 
		}
		else
		{
		
		//add noise rows 
		int cnt_col=0;
		int cnt_col1=0;
		int colscore;
		vector<vector<double> >che_bics4;
		for(int i=0;i<bic_s4.size();i++)
		{ 	
			if(bic_s4[i].size()!=0)
				{
					che_bics4.push_back(bic_s4[i]);
				}
		}
		bic_s4.swap(che_bics4);
		vector<vector<double> >(0).swap(che_bics4);
		for(int i=0;i<bic_s4.size();i++)
		{
		
    		for(int j=0;j<rows;j++)
    		{
        		if(find(bic_s4[i].begin()+5+int(bic_s4[i][0]),bic_s4[i].end(),j)==bic_s4[i].end())
        		{
                vector<double> temp_add;
                int add_count=0;
                for(int i1=0;i1<bic_s4[i][0];i1++)
                {	if(arr_c[j][int(bic_s4[i][i1+5])]!=0)
                	{
                    	temp_add.push_back(arr_c[j][int(bic_s4[i][i1+5])]);
                    	add_count+=1;
                    }
                }
                
                //colscore=LIS(temp_add,int(bic_s4[i][0]));
                colscore=LIS(temp_add,add_count);
                vector<double>(0).swap(temp_add);
                if (colscore>=po->TOLERANCE*bic_s4[i][0])
                   { bic_s4[i].push_back(j);
                   bic_s4[i][1]+=1;
                   bic_s4[i][3]+=1;
                   }
		else{
					add_count=0;
                    for(int i1=0;i1<bic_s4[i][0];i1++)
                    {
                    if(arr_c[j][int(bic_s4[i][i1+5])]!=0)
                    {
                    	temp_add.push_back(-1*arr_c[j][int(bic_s4[i][i1+5])]);
                    	add_count+=1;
                    }
                    }
                    //colscore=LIS(temp_add,int(bic_s4[i][0]));
                    colscore=LIS(temp_add,add_count);
		    vector<double>(0).swap(temp_add);

                    if (colscore>=po->TOLERANCE*bic_s4[i][0])
                      { bic_s4[i].push_back(j);
                       bic_s4[i][2]+=1;
                      bic_s4[i][3]+=1;
                       }
                 
                 }
                
        		
        		}
    		
    		}				
		
		}
		
							
		///
			if(bestofbic1>bic_s4.size())
			{
				canshu=bic_s4.size();
			}
			else
			{
				canshu=bestofbic1;
			}		
			partial_sort(bic_s4.begin(),bic_s4.begin()+canshu,bic_s4.end(),operator_v1);				
			for(i7=0;i7<canshu;i7++)
			{
					bic_s5.push_back(bic_s4[i7]);
			} 			
			bic_s5=deletea_w(bic_s5,po->COL_WIDTH);					
			sort(bic_s5.begin(),bic_s5.end(),operator_v1);		
			vector<vector<double> >(0).swap(bic_s4);
			bic_s5=filtering(bic_s5,cols,po->FILTER);
			bic_s5=filtering(bic_s5,cols,0.8);
			
				
    	sc3(bic_s5,bestofbic,fn);
        cout<<endl<<"Done!"<<endl;
		}		
	}
	else
{
{
	int Part;
	if(n<300)
	{
    	Part=3;
    	}
    	else{
    	Part=int(n/70);
    	}
    	int step_k;
    	int cendi;
    	int stepc=cols/Part;
    	cout<<"Generating seeds"<<endl;;
	for(step_k=0;step_k<Part;step_k++)
	{	
		vector<double>bic;	
		vector<double>v_cols;
		vector<double>v_rows_a;
		vector<double>v_rows_d;
		cendi=(step_k+1)*stepc;
		if(step_k==Part-1)
		{
			cendi=cols;	}		
		for (col1=step_k*stepc;col1<cendi;col1++)
		{
				for (col2=step_k*stepc;col2<cendi;col2++)
				{
						if(col2!=col1)
						{
								v_cols.push_back(col1);
								v_cols.push_back(col2);
								//here bug 
								for ( int line=0;line<m;line++)
								{		
										if(arr_c[line][col1]*arr_c[line][col2]!=0)
										{
										if (arr_c[line][col1]==arr_c[line][col2])
										{
												v_rows_a.push_back(line);
										}
										
										}
								}
								
								{
								
										bic.push_back(2);
										bic.push_back(v_rows_a.size());
										bic.push_back(v_rows_d.size());
										bic.push_back(v_rows_a.size()+v_rows_d.size());

										bic.push_back(1);
									
										bic=add_v(bic,v_cols);
										bic=add_v(bic,v_rows_a);
										bic=add_v(bic,v_rows_d);
										bic_s1.push_back(bic); 
					 
								}							
								
								vector<double>(0).swap(v_cols);
								vector<double>(0).swap(v_rows_a);
								vector<double>(0).swap(v_rows_d);
								vector<double>(0).swap(bic); 
								
						}			
				}
		}
		}
		
	///////////######################################################################3///////////////	
		//biclusters temp for i2 cols		
		
		//biclusters temp in the q step 
		vector<vector< double> >bic_s5;//the final biclusters
		
		//the col we add, 
		int i2;//the seq we add to,
		int q=3;//q represents the seq size of col,this is important,	
		
		int l_s;
	
		int canshu;
		vector<double>unique_rows;
		
            l_s=bic_s1.size();//the size of seq1 	
				//	ss=q;
			
/////////////////////////////////////////////////
				vector<vector< double> >bic_s3;
				#pragma omp parallel
				{	
				vector< vector<double>> subbic_s3;
				#pragma omp for nowait									 
				for (i2=0;i2<l_s;i2++)
				{
				
				int s;//s rep where we put the col3
				int ms=6;
				int j;
				vector<vector< double> >bic_s2;
				vector<double>bic;
				vector<double>v_cols;
				vector<double>cols_int;	
				vector<double>v_rows_a;
				vector<double>v_rows_d;
						int cols_i2= 7;
						int rows_i2=7+bic_s1[i2][1];
						int rows_mi2=7+bic_s1[i2][3];
						int rows_li2=bic_s1[i2].size();
						
						vector<double>(2).swap(cols_int);
						
						cols_int.assign(bic_s1[i2].begin()+5, bic_s1[i2].begin()+7);
						for (int col3=0;col3<n;col3++)
						{
								
								if(find(cols_int.begin(),cols_int.end(), col3)==cols_int.end())
								{	
										
										v_cols=cols_int;
											
										v_cols.insert(v_cols.begin(),col3);	
										for (j=cols_i2;j<rows_i2;j++)
										{
												
												if(arr_c[(int)bic_s1[i2][j]][col3]!=0)
												{
												
												if (arr_c[(int)bic_s1[i2][j]][col3]==arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][5]])
												{	
														v_rows_a.push_back(bic_s1[i2][j]);
												}
												}
												
										}
										
										
										{	
										

												bic.push_back(v_cols.size());
												bic.push_back(v_rows_a.size());
												bic.push_back(v_rows_d.size());
												bic.push_back(v_rows_a.size()+v_rows_d.size());//
												bic.push_back(1);              
												bic=add_v(bic,v_cols);
												bic=add_v(bic,v_rows_a);
												bic=add_v(bic,v_rows_d);
												bic_s2.push_back(bic);
										}									
												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic); 
									

										for(s=6;s<=ms;s++)
										{
												v_cols=cols_int;
												v_cols.insert(v_cols.begin()+s-5,col3);
												for (j=cols_i2;j<rows_i2;j++)
												{
														if(arr_c[(int)bic_s1[i2][j]][col3]!=0){
														if (arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][s-1]]==arr_c[(int)bic_s1[i2][j]][col3]&&arr_c[(int)bic_s1[i2][j]][col3]>=arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][s]])						
														{	
																v_rows_a.push_back(bic_s1[i2][j]);	
														}
														}
												}
														
												
												{
														bic.push_back(v_cols.size());
														bic.push_back(v_rows_a.size());
														bic.push_back(v_rows_d.size());
														bic.push_back(v_rows_a.size()+v_rows_d.size());//
														bic.push_back(1);
														bic=add_v(bic,v_cols);
														bic=add_v(bic,v_rows_a);
														bic=add_v(bic,v_rows_d);
														bic_s2.push_back(bic);
												}																				
												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic);	
										}
										
		
										v_cols=cols_int;

										v_cols.push_back(col3);

										for (j=cols_i2;j<rows_i2;j++)
										{
												if(arr_c[(int)bic_s1[i2][j]][col3]!=0)
												{
												if (arr_c[(int)bic_s1[i2][j]][col3]==arr_c[(int)bic_s1[i2][j]][(int)bic_s1[i2][ms]])
												{	
														v_rows_a.push_back(bic_s1[i2][j]);
												}
												}
										}

										
										
										{
											
												bic.push_back(v_cols.size());
												bic.push_back(v_rows_a.size());
												bic.push_back(v_rows_d.size());
												bic.push_back(v_rows_a.size()+v_rows_d.size());//
												bic.push_back(1);
												bic=add_v(bic,v_cols);
												bic=add_v(bic,v_rows_a);
												bic=add_v(bic,v_rows_d);
												bic_s2.push_back(bic);
										}

												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic);
								
																																
								}
	
						}
						
						int all_score=0;
						int max_score=0;
						long double p_value;
						float ave_score;
						int p_i;
						int pmax_i=0;
						
						if(bic_s2.size()==0)
						{
						continue;
						}
						
						for(p_i=0;p_i<bic_s2.size();p_i++)
						{
							
							all_score=all_score+bic_s2[p_i][3];
							if(bic_s2[p_i][3]>max_score)
							{
								max_score=bic_s2[p_i][3];
								pmax_i=p_i;
							}
						}
						ave_score=(all_score*1.0)/bic_s2.size();
						p_value=get_pvalues(ave_score,max_score);
						vector<double>bic_int;					
						bic_int=bic_s2[pmax_i];	
						vector<vector<double> >(0).swap(bic_s2);					
						bic_int[4]=p_value;								
    					subbic_s3.push_back(bic_int);
	   								
						}//// bingxing for jieshu//
					#pragma omp critical
					{
bic_s3.insert(bic_s3.end(),subbic_s3.begin(),subbic_s3.end());}
						}
						
				
				bic_s1=deletea2(bic_s3,cc);	///cc is here;
				bic_s1=deletea(bic_s1);
				sort(bic_s1.begin(),bic_s1.end(),operator_v1);
				cout<<"Totally "<<bic_s1.size()<<" seeds"<<endl;
				//bic_s1=filtering(bic_s1,3,0.6);
				

		
		//////#############################################333/////////////////
		
		
		vector<vector<double> >seeds;
		seeds=bic_s1;
		
		//int shuchu=po->COL_MAXWIDTH*bestofbic*0.7;//改之?
		int shuchu=bestofbic1;
		int coutshu=0;
		int seed_len=bic_s1.size();
		vector<bool>seed_flag(seed_len,1);
		
		vector<double> temp_step;
		vector<double> bic_max;
		vector<double> bic_max2;		
		int seed_len1=bic_s1.size();
		
		//sc3(bic_s1,seed_len1,fn);//2018.6.20
		//while(q<kk)
		cout<<"Expanding"<<endl;
		for (i2=0;i2<seed_len;i2++)
		{
		if(coutshu>shuchu)
    	{
    	break;
    	
		}
		else{
		if(seed_flag[i2])
		{
		
		temp_step=seeds[i2];
		
		
		for(q=3;q<kk;q++)
		{     
        		cout<<".";
		int ms;
		int s;
		int j;
		vector<vector< double> >bic_s2;
		vector<double>cols_int;
		vector<double>bic;	
		vector<double>v_cols;
		vector<double>v_rows_a;
		vector<double>v_rows_d;
        		vector<double> bic_int;
			
				//l_s=bic_s1.size();//the size of seq1 	
				//	ss=q;
				ms = q+4;
				
				if(l_s<1)
				{
					break;
				}	
				if(temp_step[3]<2){break;}
										 
						int cols_i2= q+5;
						int rows_i2=q+5+temp_step[1];
						int rows_mi2=q+5+temp_step[3];
						int rows_li2=temp_step.size();
							
						vector<double>(q).swap(cols_int);
						cols_int.assign(temp_step.begin()+5, temp_step.begin()+5+q);
						for (int col3=0;col3<n;col3++)
						{
								
								if(find(cols_int.begin(),cols_int.end(), col3)==cols_int.end())
								{	
										v_cols=cols_int;
										v_cols.insert(v_cols.begin(),col3);
										
										for (j=cols_i2;j<rows_i2;j++)
										{		
												if(arr_c[(int)temp_step[j]][col3]!=0)
												{
												if (arr_c[(int)temp_step[j]][col3]==arr_c[(int)temp_step[j]][(int)temp_step[5]])
												{	
														v_rows_a.push_back(temp_step[j]);
													
												}
												}
										}
										
										//cout<<"where"<<endl;
										{	

												bic.push_back(v_cols.size());
												bic.push_back(v_rows_a.size());
												bic.push_back(v_rows_d.size());
												bic.push_back(v_rows_a.size()+v_rows_d.size());//
												bic.push_back(1);              
												bic=add_v(bic,v_cols);
												bic=add_v(bic,v_rows_a);
												bic=add_v(bic,v_rows_d);
												bic_s2.push_back(bic);												

										}									
												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic); 

										for(s=6;s<=ms;s++)
										{
												v_cols=cols_int;
												v_cols.insert(v_cols.begin()+s-5,col3);
												for (j=cols_i2;j<rows_i2;j++)
												{
														if(arr_c[(int)temp_step[j]][col3]!=0)
														{
														if (arr_c[(int)temp_step[j]][(int)temp_step[s-1]]==arr_c[(int)temp_step[j]][col3]&&arr_c[(int)temp_step[j]][col3]>=arr_c[(int)temp_step[j]][(int)temp_step[s]])						
														{	
																v_rows_a.push_back(temp_step[j]);	
														}
														}
												}
																	
												
												{
														bic.push_back(v_cols.size());
														bic.push_back(v_rows_a.size());
														bic.push_back(v_rows_d.size());
														bic.push_back(v_rows_a.size()+v_rows_d.size());//
														bic.push_back(1);
														bic=add_v(bic,v_cols);
														bic=add_v(bic,v_rows_a);
														bic=add_v(bic,v_rows_d);
														bic_s2.push_back(bic);
												}																				
												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic);														
										}	
										v_cols=cols_int;
										//cout<<"oooo"<<endl;
										v_cols.push_back(col3);
										for (j=cols_i2;j<rows_i2;j++)
										{
												if(arr_c[(int)temp_step[j]][col3]!=0)
												{
												if (arr_c[(int)temp_step[j]][col3]==arr_c[(int)temp_step[j]][(int)temp_step[ms]])
												{	
														v_rows_a.push_back(temp_step[j]);
												}
												}
										}

										
										{
												bic.push_back(v_cols.size());
												bic.push_back(v_rows_a.size());
												bic.push_back(v_rows_d.size());
												bic.push_back(v_rows_a.size()+v_rows_d.size());//
												bic.push_back(1);
												bic=add_v(bic,v_cols);
												bic=add_v(bic,v_rows_a);
												bic=add_v(bic,v_rows_d);
												bic_s2.push_back(bic);
										}
												vector<double>(0).swap(v_cols);
												vector<double>(0).swap(v_rows_a);
												vector<double>(0).swap(v_rows_d);
												vector<double>(0).swap(bic);
																																
								}
						}						
						int all_score=0;
						int max_score=0;
						long double p_value;
						float ave_score;
						int p_i;
						int pmax_i=0;
						//cout<<333<<bic_s2.size()<<endl;
						if(bic_s2.size()==0)
						{
						break;}
						for(p_i=0;p_i<bic_s2.size();p_i++)
						{
							
							all_score=all_score+bic_s2[p_i][3];
							if(bic_s2[p_i][3]>max_score)
							{
								max_score=bic_s2[p_i][3];
								pmax_i=p_i;
							}
						}
						ave_score=(all_score*1.0)/bic_s2.size();
						p_value=get_pvalues(ave_score,max_score);
											
						bic_int=bic_s2[pmax_i];
						vector<vector<double> >(0).swap(bic_s2);						
						bic_int[4]=p_value;
						//if(q==3)
						if(test(rows,q))
						{
						temp_step.swap(bic_int);
    					vector<double>(0).swap(bic_int);
    					bic_max=temp_step;
    					bic_max2=temp_step;//9.3
		
						continue;}
						else{

						if(compare_int(bic_int, bic_max))//int<max

						{

    						temp_step.swap(bic_int);

    						vector<double>(0).swap(bic_int);	

						}

						else//int>=max

						{

						if(compare_int(bic_int,bic_max2))
						{//int<max2 7int=max=max2, 8int>max2,max2=int, 9int<max<max2,10max<int<max2
						
						bic_max=bic_int;					
						temp_step.swap(bic_int);
						vector<double>(0).swap(bic_int);
						}
						else{//int>=max2

    						bic_max2=bic_int;

    						temp_step.swap(bic_int);

    						vector<double>(0).swap(bic_int);
    						}
	

						}

							}




		}//kk for ends here
	
	bic_s4.push_back(bic_max);			
       //seed_flag=cheak_seed(bic_max,seeds,seed_flag);       
       vector<double>(0).swap(bic_max);
	 bic_s4.push_back(bic_max2);//9.3
       seed_flag=cheak_seed(bic_max2,seeds,seed_flag);//9.3  
       
        vector<double>(0).swap(bic_max2);//9.3     
       seed_flag[i2]=0;
       
    	coutshu+=1;
	
		}
		}
		
		}
		
		if(bic_s4.size()==0)
		{
			cout<<"no biclusters,you need to relax your limits(eg:-x to set less rows)"<<endl; 
		}
		else
		{
		
		//add noise rows 
		int cnt_col=0;
		int cnt_col1=0;
		int colscore;
		vector<vector<double> >che_bics4;
		for(int i=0;i<bic_s4.size();i++)
		{ 	
			if(bic_s4[i].size()!=0)
				{
					che_bics4.push_back(bic_s4[i]);
				}
		}
		bic_s4.swap(che_bics4);
		vector<vector<double> >(0).swap(che_bics4);
		for(int i=0;i<bic_s4.size();i++)
		{
    		for(int j=0;j<rows;j++)
    		{
        		if(find(bic_s4[i].begin()+5+int(bic_s4[i][0]),bic_s4[i].end(),j)==bic_s4[i].end())
        		{
                vector<double> temp_add;
                int add_count=0;
                for(int i1=0;i1<bic_s4[i][0];i1++)
                {	if(arr_c[j][int(bic_s4[i][i1+5])]!=0)
                	{
                    	temp_add.push_back(arr_c[j][int(bic_s4[i][i1+5])]);
                    	add_count+=1;
                    }
                }
                
                //colscore=LIS(temp_add,int(bic_s4[i][0]));
                colscore=LIS(temp_add,add_count);
                vector<double>(0).swap(temp_add);
                if (colscore>=po->TOLERANCE*bic_s4[i][0])
                   { bic_s4[i].push_back(j);
                   bic_s4[i][1]+=1;
                   bic_s4[i][3]+=1;
                   }
		else{
					add_count=0;
                    for(int i1=0;i1<bic_s4[i][0];i1++)
                    {
                    if(arr_c[j][int(bic_s4[i][i1+5])]!=0)
                    {
                    	temp_add.push_back(-1*arr_c[j][int(bic_s4[i][i1+5])]);
                    	add_count+=1;
                    }
                    }
                    //colscore=LIS(temp_add,int(bic_s4[i][0]));
                    colscore=LIS(temp_add,add_count);
		    vector<double>(0).swap(temp_add);
                    if (colscore>=po->TOLERANCE*bic_s4[i][0])
                      { bic_s4[i].push_back(j);
                       bic_s4[i][2]+=1;
                      bic_s4[i][3]+=1;
                       }
                 
                 }
                
        		
        		}
    		
    		}				
		
		}
		
							
		///
			if(bestofbic1>bic_s4.size())
			{
				canshu=bic_s4.size();
			}
			else
			{
				canshu=bestofbic1;
			}		
			partial_sort(bic_s4.begin(),bic_s4.begin()+canshu,bic_s4.end(),operator_v1);				
			for(i7=0;i7<canshu;i7++)
			{
					bic_s5.push_back(bic_s4[i7]);
			} 			
			bic_s5=deletea_w(bic_s5,po->COL_WIDTH);					
			sort(bic_s5.begin(),bic_s5.end(),operator_v1);		
			vector<vector<double> >(0).swap(bic_s4);
			bic_s5=filtering(bic_s5,cols,0.8);
			bic_s5=filtering(bic_s5,cols,po->FILTER);
				
    	sc3(bic_s5,bestofbic,fn);
        cout<<endl<<"Done!"<<endl;
		}		
	}

}				
		return;
}

