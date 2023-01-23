#include <iostream>
#include "header_csr.h"
#include <time.h>
#include <random>
#include <fstream>
using namespace std;


int main()
{  //defining the sparse matrix, vector and output vector
	int A[ROW_A][COL_A], B[COL_A],C[ROW_A],C_H[ROW_A];
    int error_counter=0;// to check the results from test bench and hardware

   	int n_z_A=0;

    fstream Sparse_data("S_30x30_70%.bin");
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

    for(int i = 0; i < ROW_A; i++)
	{
    cout<<C_H[i]<<" ";
    }
    cout<<endl;
    //CSC format

     std::vector<int> nz_vector;
     std::vector<int> col_idx_vector;
     std::vector<int> row_ptr_vector;
     int ar_nz[N], ar_col_idx[M], ar_row_ptr[L], k=0;
     int n_nz_A=0;
     int rwp=0;


	 for(int i = 0; i < M; i++)
	 {
	         ar_nz[i]=0;
	 }
	 for(int i = 0; i < N; i++)
	 {
	         ar_col_idx[i]=0;
	 }
	 for(int i = 0; i < L; i++)
	 {
	         ar_row_ptr[i]=0;
	 }
      cout<<endl;
      for(int i = 0; i < M; i++)
      	 {
      	         cout<<ar_nz[i];
      	 }

     //computation of vector of column start pointers.


	 row_ptr_vector.push_back(0);
     for(int i = 0; i< ROW_A; i++)
     {
	 if(i==0)
	 {
	    k++;
	 }

	 for(int j = 0; j < COL_A; j++)
	 {
	     if( A[i][j]!=0 )
	     {

             if(k!=i && i!=0)
	         {
	               row_ptr_vector.push_back(n_nz_A);
	               rwp++;

	                k=i;


	         }
             n_nz_A++;
	     }

	   }
       k++;
       if(k-i<2)
       {
	     k=i+2;
       }
    }
	         rwp++;
	         n_nz_A++;
	         row_ptr_vector.push_back(n_nz_A);




	         for(int i = 0; i < COL_A; i++)
	         {
	             for(int j = 0; j < ROW_A; j++)
	             {
	                 if( A[i][j]!=0 )
	                 {
	                        nz_vector.push_back(A[i][j]);
	                 		col_idx_vector.push_back(j);
                     }
	             }
             }

	         std::cout<<" The vector containing row pointers for the CSR format: ";
	        	             for(int i = 0; i < row_ptr_vector.size(); i++)
	        	             {
	        	                      std::cout << row_ptr_vector[i];
	        	                      std::cout << "  ";

	        	              }
	         std::copy(nz_vector.begin(),      nz_vector.end(),      ar_nz);
             std::copy(col_idx_vector.begin(), col_idx_vector.end(), ar_col_idx);
         std::copy(row_ptr_vector.begin(), row_ptr_vector.end(), ar_row_ptr);

   //test bench computation

	          for(int i = 0; i < ROW_A; i++)
	          {
	         	 for(int j = 0; j < COL_A; j++)
	         	 {
	         		 C[i] += A[i][j]*B[j];
	         	 }
	          }
              ///////////___________function call for CSC storage format computation____________////////////
             CSR_t(ar_nz,ar_col_idx,ar_row_ptr,B,C_H);



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
	             for(int i = 0; i < M; i++)
	             {
	                 std::cout << ar_nz[i];
	                 std::cout << "  ";

	             }

	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"The array containing all the column indexes: "<<std::endl;
	             for(int i = 0; i < N; i++)
	             {
	                       std::cout << ar_col_idx[i];
	                       std::cout << "  ";
                 }

	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;

	             std::cout<<"The array containing all the row pointers: : "<<std::endl;
	             for(int i = 0; i < L; i++)
	             {
	                     std::cout << ar_row_ptr[i];
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
	             std::cout<<" The vector containing all the non-zero values' col indexes of matrix A:"<<std::endl;
	             for(int i = 0; i < col_idx_vector.size(); i++)
	             {
	                     std::cout << col_idx_vector[i];
	                     std::cout << "  ";

	             }
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;

	             //output of column pointer vector
	             std::cout<<" The vector containing row pointers for the CSR format: ";
	             for(int i = 0; i < row_ptr_vector.size(); i++)
	             {
	                      std::cout << row_ptr_vector[i];
	                      std::cout << "  ";

	              }

	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;

	                 std::cout << "  "<<std::endl;



	                 for(int i = 0; i < L; i++){
	                 	         std::cout<<"The row pointer is "<<ar_row_ptr[i]<<endl;
	                 	 }
	                 std::cout << "  "<<std::endl;
}

