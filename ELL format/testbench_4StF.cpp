#include <iostream>
#include <string.h>
#include "Hf4StF.h"
#include <time.h>
#include <random>
#include <vector>
#include <fstream>
using namespace std;

int main()
{  //defining the sparse matrix, vector and output vector

     int ELL_clm_indx[ROW_A][ELL_COL], ELL_val[ROW_A][ELL_COL];
	 int A[ROW_A][COL_A], B[COL_A],C[ROW_A],C_H[ROW_A];
     int error_counter=0;// to check the results from test bench and hardware
     //int n_z_A=0;
   	 //float zero_prob=0.8;

   	 //A[ROW_A][COL_A]=Sparse_mat(A,zero_prob);

   	 std::ifstream outdata("S_120x120_70%.bin");

   	 for(int i=0; i<ROW_A; i++)
   	 {
   	     for(int j=0; j<COL_A; j++)
   	     {
   	             outdata>>A[i][j];
   	     }
   	 }


   	 outdata.close();


   	 for(int i = 0; i < COL_A; i++)
   	 {
   	   	     B[i] =1;
   	 }

   	 for(int i = 0; i < ROW_A; i++)
   	 {
   	         C[i] = 0;
   	         C_H[i] = 0;
   	         	     //C_stream[i].write(0);
   	 }






   	 for(int i = 0; i < ROW_A; i++)
   	 {
   		 for(int j = 0; j < COL_A; j++)
   	     {
   			     std::cout << A[i][j];
   			     std::cout << "  ";
   		 }
   			 std::cout<<std::endl;
   	 }


 	for(int i = 0; i < COL_A; i++)
    {
    		std::cout << B[i];
    		std::cout << "  ";
    }

     /*
	 for(int i = 0; i < COL_A; i++)
	 {
	    	 B[i] = 1;
	 }
	 std::cout<<"  "<<std::endl;
	 std::cout<<"  "<<std::endl;*/

	 /*std::cout<<"  "<<std::endl;
	 std::cout<<"  "<<std::endl;
	 for(int i = 0; i < ROW_A; i++)
	 {
	         C[i] = 0;
	         C_H[i] = 0;
	 }*/

	
//COO format...................................................................................
//coo format consists of 3 arrays
	/* int nz_val_A=0;
     int COO_row[N];
	 int COO_col[N];
	 int COO_val[N];

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
	 //creating coo structure
     COO_indx COO_format;
     COO_format=COO_indx_f(COO_format,A,nz_val_A);

     std::copy(COO_format.row_indx.begin(), COO_format.row_indx.end(), COO_row);
     std::copy(COO_format.col_indx.begin(), COO_format.col_indx.end(), COO_col);
     std::copy(COO_format.val_vec.begin(),  COO_format.val_vec.end(),  COO_val);


*/
	 //CSC format...............................................................................
    /* int ar_nz[N], ar_row_idx[M], ar_col_ptr[L];
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

     CSC_indx CSC_format;
	 CSC_format=CSC_indx_f(CSC_format,A);
	 clp=CSC_format.clp;
	 n_nz_A=CSC_format.n_nz_A;
     std::copy(CSC_format.nz_vector.begin(),      CSC_format.nz_vector.end(), ar_nz);
	 std::copy(CSC_format.row_idx_vector.begin(), CSC_format.row_idx_vector.end(), ar_row_idx);
	 std::copy(CSC_format.col_ptr_vector.begin(), CSC_format.col_ptr_vector.end(), ar_col_ptr);
*/
	 //CSR format.................................................................................
	 /*int CSR_nz_val[N];
	 int CSR_col_idx[N];
     int CSR_row_ptr[L];
     int n_nz_A1=0;
     int rwp=0;
     for(int i = 0; i < N; i++)
     {
    	 CSR_nz_val[i]=0;
     }
     for(int i = 0; i < N; i++)
     {
    	 CSR_col_idx[i]=0;
     }
     for(int i = 0; i < L; i++)
     {
    	 CSR_row_ptr[i]=0;
     }
     CSR_indx CSR_format;
     n_nz_A1=CSR_format.n_nz_A1;
     rwp=CSR_format.rwp;
     std::copy(CSR_format.CSR_nz_vector.begin(),      CSR_format.CSR_nz_vector.end(),       CSR_nz_val);
     std::copy(CSR_format.CSR_col_idx_vector.begin(), CSR_format.CSR_col_idx_vector.end(), CSR_col_idx);
     std::copy(CSR_format.CSR_row_ptr_vector.begin(), CSR_format.CSR_row_ptr_vector.end(), CSR_row_ptr);
    */
     //ELL format.................................................................................



	  //initializing the values for ELL format
      //ELL_indx ELL_format;
      //ELL_format=ELL_indx_f(ELL_format,A);
      //max_ell=ELL_format.max_ell;
      //std::cout<<"The ell_max is equal to ";
      //std::cout<<max_ell;
      for(int i=0; i<ROW_A; i++)
      {
      	  for(int j=0; j<ELL_COL; j++)
      	  {
      	  	    ELL_clm_indx[i][j]=0;
      	  		ELL_val[i][j]=0;
      	  }
      }



      for(int i=0; i<ROW_A; i++)
      {
          int E=0;
          for(int j=0; j<COL_A; j++)
          {
        	  if(A[i][j]!=0)
        	  {
        	  	 ELL_val[i][E]=A[i][j];
                 ELL_clm_indx[i][E]=j;
        	  	 E++;
        	  }
          }


       }


          /////////_____/////______TEST BENCH COMPUTATION_____///////__________///////
	          
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
	          //CSC_t(clp,ar_nz,ar_row_idx,ar_col_ptr,B,C_H);

              //CSR_format__________________
              //CSR_t(rwp,CSR_nz_val, CSR_col_idx, CSR_row_ptr,B,C_H);
	          ///////////___________function call for COO storage format computation____________////////////
	          //COO_t( nz_val_A,COO_row,COO_col,COO_val,B,C_H);*/
              ////////////____________function call for ELL format computation_______////////
	          ELL_t(ELL_clm_indx,ELL_val,B,C_H);


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


	       //output of vector sparse vector B

	          
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;
	          std::cout<<"The Vector C computed in test bench: ";
	          //output of vector C
	          for(int i = 0; i < ROW_A; i++)
	          {
	              std::cout << C[i];
	              std::cout << "  ";
	          }
	          
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;
	          std::cout<<"The Vector C_H computed in top level function: ";
	          //Output of vector C_H
	          for(int i = 0; i < ROW_A; i++)
	          {
	              std::cout << C_H[i];
	              std::cout << "  ";
	              
	          }
	          
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;


	          for(int i = 0; i < ROW_A; i++)
	          {
	         	 for(int j = 0; j < ELL_COL; j++)
	         	 {
	         		std::cout<<ELL_clm_indx[i][j];
	         		std::cout<<"  ";

	         	 }
	         	std::cout<<std::endl;
	          }
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;
	          std::cout<<"  "<<std::endl;

	        for(int i = 0; i < ROW_A; i++)
	        {
	            for(int j = 0; j < ELL_COL; j++)
	            {
	            	std::cout<<ELL_val[i][j];
	            	std::cout<<"  ";
	            }
	            std::cout<<std::endl;
	        }
/*
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

	             for(int i = 0; i < CSC_format.nz_vector.size(); i++)
	             {
	                     std::cout << CSC_format.nz_vector[i];
	                     std::cout << "  ";

	             }
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;

	             //output of row index vector
	             std::cout<<" The vector containing all the non-zero values' row indexes of matrix A:"<<std::endl;
	             for(int i = 0; i < CSC_format.row_idx_vector.size(); i++)
	             {
	                     std::cout << CSC_format.row_idx_vector[i];
	                     std::cout << "  ";

	             }
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;
	             std::cout<<"  "<<std::endl;

	             //output of column pointer vector
	             std::cout<<" The vector containing column pointers for the CSC format: ";
	             for(int i = 0; i < CSC_format.col_ptr_vector.size(); i++)
	             {
	                      std::cout << CSC_format.col_ptr_vector[i];
	                      std::cout << "  ";

	              }

	             /*std::cout<<std::endl;
	             std::cout<<std::endl;
	             for(int i = 0; i < N; i++)
	            	 {
	            	 cout <<COO_row[i];

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
	            	 }*/
}
/*
int Sparse_mat(int A[ROW_A][COL_A],float zero_prob_A)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::binomial_distribution<int> binomial_distributed_values_A(20, 0.5);


	std::mt19937 sparse_gen(rd());
    std::uniform_real_distribution<float> sparse_dist(0.0, 1.0);

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
	return A[ROW_A][COL_A];

}
CSC_indx CSC_indx_f(CSC_indx dd, int A[ROW_A][COL_A])
{
	int k=0;
	dd.clp=0;
	dd.n_nz_A=0;

	dd.col_ptr_vector.push_back(0);
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

		       dd.n_nz_A++;
		       if(k!=j && j!=0)
		       {
		          dd.col_ptr_vector.push_back(dd.n_nz_A);
		          dd.clp++;
		          k--;
		          if((k-j)>1)
		          {
		              k=j;
		          }
		       }
		    }

		 }
		 k++;
		 if(k-j<2)
		 {
		    k=j+2;
		 }
	}
		    dd.clp++;
		    dd.n_nz_A++;
		    dd.col_ptr_vector.push_back(dd.n_nz_A);
            for(int j = 0; j < COL_A; j++)
		    {
		        for(int i = 0; i < ROW_A; i++)
		        {
		            if( A[i][j]!=0 )
		            {
		                dd.nz_vector.push_back(A[i][j]);
		                //nz_val=A[i][j];
		                dd.row_idx_vector.push_back(i);
                    }
		        }

		    }
return dd;

}
COO_indx COO_indx_f(COO_indx dd, int D[ROW_A][COL_A], int nz_val_A)
{
	for(int i = 0; i < ROW_A; i++)
	{
	   	     for(int j = 0; j < COL_A; ++j)
	   	     {
	   	           if( D[i][j]!=0 )
	   	           {
	   	                   dd.row_indx.push_back(i);
	   	                   dd.col_indx.push_back(j);
	   	                   dd.val_vec.push_back(D[i][j]);
	   	                   nz_val_A++;

                   }
	   	     }

	 }

return dd;
}

CSR_indx CSR_indx_f(CSR_indx dd, int A[ROW_A][COL_A])
{


	int k=0;
	dd.rwp=0;
	dd.n_nz_A1=0;

	dd.CSR_row_ptr_vector.push_back(0);
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

		                dd.n_nz_A1++;
		                if(k!=i && i!=0)
		                {
		                   dd.CSR_row_ptr_vector.push_back(dd.n_nz_A1);
		                   dd.rwp++;
		                   k--;
		                   if((k-i)>1)
		                   {
		                       k=i;
		                   }
		            	}
		             }

		        }
		        k++;
		        if(k-i<2)
		        {
		        	 k=i+2;
		        }
		    }
		    dd.rwp++;
		    dd.n_nz_A1++;
		    dd.CSR_row_ptr_vector.push_back(dd.n_nz_A1);
            for(int i = 0; i < ROW_A; i++)
		    {
		        for(int j = 0; j < COL_A; j++)
		        {
		            if( A[i][j]!=0 )
		            {
		                dd.CSR_nz_vector.push_back(A[i][j]);
		                //nz_val=A[i][j];
		                dd.CSR_col_idx_vector.push_back(j);

                    }
		        }

		    }

 return dd;

}*/




