#include <stdio.h>
#include <random>
#include <iostream>
#include <fstream>
#define ROW_A 8
#define COL_A 8

#include <strstream>
int main()
{


	    int A[ROW_A][COL_A];
		float zero_prob_A=0.7;
	
		std::random_device rd;
		std::mt19937 gen(rd());
		std::binomial_distribution<int> binomial_distributed_values_A(20, 0.5);


		std::mt19937 sparse_gen(rd());
		std::uniform_real_distribution<float> sparse_dist(0.0, 1.0);

		for (int i = 0; i < ROW_A; i++)
		{
			for (int j = 0; j < COL_A; j++)
			{
				if (sparse_dist(sparse_gen) > zero_prob_A)
				{
					A[i][j] = binomial_distributed_values_A(gen);
				}
				else
				{
					A[i][j] = 0;
				}
			}
		}
		
		for (int i = 0; i < ROW_A; i++)
		{
			for (int j = 0; j < COL_A; j++)
			{
				std::cout << A[i][j];
			    std::cout << " ";
			}
			std::cout << std::endl;
		}

		std::fstream sparse("Sparse_A.txt");
		for (size_t i = 0; i < ROW_A; i++)
		{
			for (size_t j = 0; j < COL_A; j++)
			{
				sparse << A[i][j] << " ";
				if (j == COL_A - 1)
				{
					sparse << "\n";
				}
				
			}

		}

   
}

