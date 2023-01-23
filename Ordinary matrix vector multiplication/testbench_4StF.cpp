#include <iostream>
#include "Hf4StF.h"
#include <time.h>
#include <random>
#include <fstream>
using namespace std;
//using namespace std;


int main()
{  //defining the sparse matrix, vector and output vector
	int A[ROW_A][COL_A], B[COL_A],C[ROW_A],C_H[ROW_A];
    int error_counter=0;// to check the results from test bench and hardware

   	int n_z_A=0;


   	std::ifstream outdata("S_60x60_60%.bin");

   	   	 for(int i=0; i<ROW_A; i++)
   	   	 {
   	   	     for(int j=0; j<COL_A; j++)
   	   	     {
   	   	             outdata>>A[i][j];
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
	
	


	     //test bench computation
	          
	          for(int i = 0; i < ROW_A; i++)
	          {
	         	 for(int j = 0; j < COL_A; j++)
	         	 {
	         		 C[i]=C[i] + A[i][j]*B[j];
	         	 }
	          }
	          
	          ///////////___________function call for ordinary sparse storage format computation____________////////////
	          Ordinary_SpMVM_t(A,B,C_H);
	          


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



}





