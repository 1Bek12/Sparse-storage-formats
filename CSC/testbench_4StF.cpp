#include <iostream>
#include "Hf4StF.h"
#include <time.h>
#include <random>
#include <fstream>
using namespace std;


int main()
{  //defining the sparse matrix, vector and output vector
	int A[ROW_A][COL_A], B[COL_A],C[ROW_A],C_H[ROW_A];
    int error_counter=0;// to check the results from test bench and hardware

   	int n_z_A=0;
   	/*std::random_device rd;
   	std::mt19937 gen(rd());
   	std::binomial_distribution<int> binomial_distributed_values_A(20, 0.5);
    float zero_prob_A=0.8;

    std::mt19937 sparse_gen(rd());
    std::uniform_real_distribution<float> sparse_dist(0.0, 1.0);*/
	/*
	 for(int i = 0; i < ROW_A; i++)
	 {
	        for(int j = 0; j < COL_A; j++)
	        {
	        	if(sparse_dist(sparse_gen) > zero_prob_A)
	        	{
	        	      A[i][j] = binomial_distributed_values_A(gen);
	        	}else
	        	{
	        		  A[i][j] = 0;
	        	}

	        	
	        		
	        }
	 }
	  */
    fstream Sparse_data("S_60x60_60%.bin");
    for(int i = 0; i < ROW_A; i++)
    {
    	for(int j = 0; j < COL_A; j++)
    	{
                   Sparse_data>>A[i][j];
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
	
	


	 //CSC format

     std::vector<int> nz_vector;
     std::vector<int> row_idx_vector;
     std::vector<int> col_ptr_vector;
     int ar_nz[N], ar_row_idx[M], ar_col_ptr[L], k=0;
     int n_nz_A=0;
     int clp=0;


	 for(int i = 0; i < N; i++)
	 {
	         ar_nz[i]=0;
	 }
	 for(int i = 0; i < N; i++)
	 {
	         ar_row_idx[i]=0;
	 }
	 for(int i = 0; i < L; i++)
	 {
	         ar_col_ptr[i]=0;
	 }

     //computation of vector of column start pointers.
	    //clp++;
	    col_ptr_vector.push_back(0);
 for(int j = 0; j< COL_A; j++)
 {
	 if(j==0)
	 {
	    k++;
	 }

	 for(int i = 0; i < ROW_A; i++)
	 {
	     if( A[i][j]!=0 )
	     {

             if(k!=j && j!=0)
	         {
	               col_ptr_vector.push_back(n_nz_A);
	               clp++;
	               k--;
	               if((k-j)>1)
	               {
	                   k=j;
	               }

	         }
             n_nz_A++;
	     }

	  }
      k++;
      if(k-j<2)
      {
	     k=j+2;
      }
   }
	         //clp++;
	         //n_nz_A+=1;
	         col_ptr_vector.push_back(n_nz_A);




	         for(int j = 0; j < COL_A; j++)
	         {
	             for(int i = 0; i < ROW_A; i++)
	             {
	                 if( A[i][j]!=0 )
	                 {
	                        nz_vector.push_back(A[i][j]);
	                 		//nz_val=A[i][j];
	                 		row_idx_vector.push_back(i);

	                 }
	             }

	         }


	         std::copy(nz_vector.begin(), nz_vector.end(), ar_nz);
	         std::copy(row_idx_vector.begin(), row_idx_vector.end(), ar_row_idx);
	         std::copy(col_ptr_vector.begin(), col_ptr_vector.end(), ar_col_ptr);

	     //test bench computation
	          
	          for(int i = 0; i < ROW_A; i++)
	          {
	         	 for(int j = 0; j < COL_A; j++)
	         	 {
	         		 C[i] += A[i][j]*B[j]; 
	         	 }
	          }
	          
	          ///////////___________function call for ordinary sparse storage format computation____________////////////
	          //full_MVM_t(A,B,C_H);
	          
	          ///////////___________function call for CSC storage format computation____________////////////
	          CSC_t(ar_nz,ar_row_idx,ar_col_ptr,B,C_H);


	          ///////////___________function call for COO storage format computation____________////////////
	          //COO_t( nz_val_A,COO_row,COO_col,COO_val,B,C_H);

	          ///////////___________checking for conditions____________////////////
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

	          // output of non-zero values
	             std::cout<<"The array containing all the non-zero values: "<<std::endl;
	             for(int i = 0; i < N; i++)
	                  {
	                      std::cout << ar_nz[i];
	                      std::cout << "  ";

	                  }

	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"The array containing all the row indexes: "<<std::endl;
	             for(int i = 0; i < N; i++)
	             {
	                       std::cout << ar_row_idx[i];
	                       std::cout << "  ";

	             }

	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;

	             std::cout<<"The array containing all the column pointers: : "<<std::endl;
	             for(int i = 0; i < L; i++)
	             {
	                     std::cout << ar_col_ptr[i];
	                     std::cout << "  ";

	             }

	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;


	             //output of non-zero values
	             std::cout<<" The vector containing all the non-zero values of matrix A:"<<std::endl;

	             for(int i = 0; i < nz_vector.size(); i++)
	             {
	                     std::cout << nz_vector[i];
	                     std::cout << "  ";

	             }
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;

	             //output of row index vector
	             std::cout<<" The vector containing all the non-zero values' row indexes of matrix A:"<<std::endl;
	             for(int i = 0; i < row_idx_vector.size(); i++)
	             {
	                     std::cout << row_idx_vector[i];
	                     std::cout << "  ";

	             }
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;

	             //output of column pointer vector
	             std::cout<<" The vector containing column pointers for the CSC format: ";
	             for(int i = 0; i < col_ptr_vector.size(); i++)
	             {
	                      std::cout << col_ptr_vector[i];
	                      std::cout << "  ";

	              }

	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;

	                 std::cout << "  "<<std::endl;
	                 std::cout << "  "<<std::endl;
	                 std::cout << "  ";
	                 std::cout<<"The clp is "<<clp<<endl;


	                 for(int i = 0; i < L; i++){
	                 	         std::cout<<"The column pointer is "<<ar_col_ptr[i]<<endl;
	                 	 }
	                 std::cout << "  "<<std::endl;
}





