#include <iostream>
#include "Hf4StF.h"
#include <time.h>
#include <random>
#include <fstream>
using namespace std;


int main()
{  //defining the sparse matrix, vector and output vector
	d_in A[ROW_A][COL_A], B[COL_A],C[ROW_A],C_H[ROW_A];
    d_in error_counter=0;// to check the results from test bench and hardware

    for(int i = 0; i < ROW_A; i++)
   	{
   	    for(int j = 0; j < COL_A; j++)
   	    {
   	        A[i][j] = 0;
   	    }
    }

    fstream sparse_file("S_30x30_50%.bin");
    for(int i = 0; i < ROW_A; i++)
    {
       	for(int j = 0; j < COL_A; j++)
       	{
       	    sparse_file>>A[i][j];
       	}
    }



	       
	 for(int i = 0; i < COL_A; i++)
	 {
	     B[i] = 1;
	 }
	     
	     
	 for(int i = 0; i < ROW_A; i++)
	 {
	     C[i] = 0;
	     C_H[i] = 0;
	 }
	
	 //_________/////_______COO format____________________///////////////___________

	 int nz_val_A=0;
	 std::vector<int> row_indx;;
	 std::vector<int> col_indx;
	 std::vector<int> val_vec;

	 d_in COO_row[N];
	 d_in COO_col[N];
	 d_in COO_val[N];

	 for(int i = 0; i < N; i++)
	 {
		     COO_row[i]=0;
	 }
	 for(int i = 0; i < N; i++)
	 {
		     COO_col[i]=0;
     }
     for(int i = 0; i < N; i++)
     {
    	     COO_val[i]=0;
	 }


     for(int i = 0; i < ROW_A; ++i)
   	 {
   	     for(int j = 0; j < COL_A; ++j)
   	     {
   	           if( A[i][j]!=0 )
   	           {
   	                   row_indx.push_back(i);
   	                   col_indx.push_back(j);
   	                   val_vec.push_back(A[i][j]);
   	                   nz_val_A++;

   	           }
   	      }

   	  }




     std::copy(row_indx.begin(), row_indx.end(), COO_row);
     std::copy(col_indx.begin(), col_indx.end(), COO_col);
     std::copy(val_vec.begin(),  val_vec.end(),  COO_val);



/////////_____/////______TEST BENCH COMPUTATION_____///////__________///////
	          
	          for(int i = 0; i < ROW_A; i++)
	          {
	         	 for(int j = 0; j < COL_A; j++)
	         	 {
	         		 C[i] += A[i][j]*B[j]; 
	         	 }
	          }
	          


	          ///////////___________function call for COO storage format computation____________////////////
	          //COO_t
	        		  COO_t(COO_row,COO_col,COO_val,B,C_H);


	         for(int i = 0; i < ROW_A; i++)
	          {
	              if(C[i] != C_H[i])
	              {
	         	     error_counter++;
	         	 }
	          }
	          
	          std::cout<< "  " << std::endl;
	          std::cout<<"The error counter:  "<<error_counter<<std::endl;
	          std::cout<< "  " << std::endl;
	          
	          if(error_counter == 0)
	          {
	         	 std::cout << "The test is passed correctly "<<std::endl;
	          }else{
	         	 std::cout << "There is an error in the code "  <<std::endl;
	          }
	          std::cout << "  " << std::endl;
	          std::cout << "  " << std::endl;


	          // output of sparse matrix A


	          for(int i = 0; i < ROW_A; i++)
	          {
	         	 for(int j = 0; j < COL_A; j++)
	         	 {
	         		std::cout << A[i][j];
	         		std::cout << "  ";
	         	 }
	         	    std::cout<<"  "<<std::endl;
	          }
	          
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;
	          

	          //output of vector sparse vector B


	          for(int i = 0; i < COL_A; i++)
	          {
	              std::cout << B[i];
	              std::cout << "  ";
	              
	          }
	          
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;
	          //output of vector C
	          for(int i = 0; i < ROW_A; i++)
	          {
	              std::cout << C[i];
	              std::cout << "  ";
	          }
	          
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;
	          //Output of vector C_H
	          for(int i = 0; i < ROW_A; i++)
	          {
	              std::cout << C_H[i];
	              std::cout << "  ";
	              
	          }
	          


	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;

	               for(int i = 0; i < N; i++)
	            	 {
	            	 std::cout <<COO_row[i];
	            			 std::cout << "  ";
	            	 }
	             std::cout<<"  "<<std::endl;
	            	 for(int i = 0; i < N; i++)
	            	 {
	            		 std::cout <<COO_col[i];
	            		     std::cout << "  ";
	                 }
	            	 std::cout<<"  "<<std::endl;
	                 for(int i = 0; i < N; i++)
	                 {
	                	 std::cout <<COO_val[i];
	                	     std::cout << "  ";
	            	 }
}





