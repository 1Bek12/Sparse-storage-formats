

#include <iostream>
#include <fstream>
#include <vector>
#define ROW_A 120
#define COL_A 120

#define ROW_PTR 121


#define COL_PTR 121
#define ELL_C 73
#define N 7232
#define M 7232
#define L 121
#define nz_A 7232
using namespace std;
int main()
{
	int A[ROW_A][COL_A], B[COL_A], C[ROW_A], ELL_clm_indx[ROW_A][ELL_C], ELL_val[ROW_A][ELL_C], k = 0;
	ifstream outdata("S_120x120_sparsity_50_percent.TXT");
	for (size_t i = 0; i < ROW_A; i++)
	{
		for (size_t j = 0; j < COL_A; j++)
		{
			outdata >> A[i][j];
		}

	}

	for (size_t i = 0; i < ROW_A; i++)
	{
		for (size_t j = 0; j < ELL_C; j++)
		{
			ELL_clm_indx[i][j] = 0;
			ELL_val[i][j] = 0;
		}
	}




	for (size_t i = 0; i < ROW_A; i++)
	{
		int E = 0;
		for (size_t j = 0; j < COL_A; j++)
		{
			if (A[i][j] != 0)
			{
				ELL_val[i][E] = A[i][j];
				ELL_clm_indx[i][E] = j;
				E++;
			}
		}
	}



	fstream ELL_v("ELL_val.TXT");


	for (size_t i = 0; i < ROW_A; i++)
	{
		for (size_t j = 0; j < ELL_C; j++)
		{
			ELL_v << ELL_val[i][j] << " ";
			if (j == ELL_C - 1)
			{
				ELL_v << "\n";
			}
		}
	}


	fstream ELL_col("ELL_col.TXT");
	for (size_t i = 0; i < ROW_A; i++)
	{
		for (size_t j = 0; j < ELL_C; j++)
		{
			ELL_col << A[i][j] << " ";
			if (j == ELL_C - 1)
			{
				ELL_col << "\n";
			}
		}
	}

	//COO format

	int nz_val_A = 0;
	std::vector<int> row_indx;
	std::vector<int> col_indx;
	std::vector<int> val_vec;

	int COO_row[N];
	int COO_col[N];
	int COO_val[N];

	for (int i = 0; i < N; i++)
	{
		COO_row[i] = 0;
	}
	for (int i = 0; i < N; i++)
	{
		COO_col[i] = 0;
	}
	for (int i = 0; i < N; i++)
	{
		COO_val[i] = 0;
	}


	for (int i = 0; i < ROW_A; ++i)
	{
		for (int j = 0; j < COL_A; ++j)
		{
			if (A[i][j] != 0)
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
	std::copy(val_vec.begin(), val_vec.end(), COO_val);


	fstream COO_row_indx("COO_row_indx.TXT");
	for (int i = 0; i < nz_A; i++)
	{
		COO_row_indx << COO_row[i] << " ";
	}

	fstream COO_col_indx("COO_col_indx.TXT");
	for (int i = 0; i < nz_A; i++)
	{
		COO_col_indx << COO_col[i] << " ";
	}

	fstream COO_val_id("COO_val.TXT");
	for (int i = 0; i < nz_A; i++)
	{
		COO_val_id << COO_val[i] << " ";
	}

	


	///////CSC format




	std::vector<int> nz_vector;
	std::vector<int> row_idx_vector;
	std::vector<int> col_ptr_vector;
	int ar_nz_col[N], ar_row_idx[N], ar_col_ptr[L];
	int n_nz_A = 0;
	int clp = 0;


	for (int i = 0; i < N; i++)
	{
		ar_nz_col[i] = 0;
	}
	for (int i = 0; i < N; i++)
	{
		ar_row_idx[i] = 0;
	}
	for (int i = 0; i < L; i++)
	{
		ar_col_ptr[i] = 0;
	}

	//computation of vector of column start pointers.
	   //clp++;
	col_ptr_vector.push_back(0);
	for (int j = 0; j < COL_A; j++)
	{
		if (j == 0)
		{
			k++;
		}

		for (int i = 0; i < ROW_A; i++)
		{
			if (A[i][j] != 0)
			{

				if (k != j && j != 0)
				{
					col_ptr_vector.push_back(n_nz_A);
					clp++;
					k--;
					if ((k - j) > 1)
					{
						k = j;
					}

				}
				n_nz_A++;
			}

		}
		k++;
		if (k - j < 2)
		{
			k = j + 2;
		}
	}
	//clp++;
	//n_nz_A+=1;
	col_ptr_vector.push_back(n_nz_A);




	for (int j = 0; j < COL_A; j++)
	{
		for (int i = 0; i < ROW_A; i++)
		{
			if (A[i][j] != 0)
			{
				nz_vector.push_back(A[i][j]);
				//nz_val=A[i][j];
				row_idx_vector.push_back(i);

			}
		}

	}



	std::copy(nz_vector.begin(),      nz_vector.end(),      ar_nz_col);
	std::copy(row_idx_vector.begin(), row_idx_vector.end(), ar_row_idx);
	std::copy(col_ptr_vector.begin(), col_ptr_vector.end(), ar_col_ptr);

 

	fstream ar_nz_CSC("ar_nz_CSC.TXT");
	for (int i = 0; i < nz_A; i++)
	{
		ar_nz_CSC << ar_nz_col[i]<<" ";
	}

	fstream ar_row_idx_CSC("ar_row_idx_CSC.TXT");
	for (int i = 0; i < nz_A; i++)
	{
		ar_row_idx_CSC << ar_row_idx[i]<<" ";
	}

	fstream ar_col_ptr_CSC("ar_col_ptr_CSC.TXT");
	for (int i = 0; i < COL_PTR; i++)
	{
		ar_col_ptr_CSC << ar_col_ptr[i]<<" ";
	}

	for (int i = 0; i < COL_PTR; i++)
	{
		cout << ar_col_ptr[i] << " ";
	}
	cout << endl;
	
	/////////////CSR



	std::vector<int> nz_vector1;
	std::vector<int> col_idx_vector;
	std::vector<int> row_ptr_vector;
	int ar_nz[N], ar_col_idx[N], ar_row_ptr[L];
	int n_nz_A1 = 0;
	int rwp = 0;


	for (int i = 0; i < N; i++)
	{
		ar_nz[i] = 0;
	}
	for (int i = 0; i < N; i++)
	{
		ar_col_idx[i] = 0;
	}
	for (int i = 0; i < L; i++)
	{
		ar_row_ptr[i] = 0;
	}

	//computation of vector of column start pointers.

	int g = 0;
	int n_nz_A_CSR = 0;
	row_ptr_vector.push_back(0);
	for (int i = 0; i < ROW_A; i++)
	{
		if (i == 0)
		{
			g++;
		}

		for (int j = 0; j < COL_A; j++)
		{
			if (A[i][j] != 0)
			{

				if (g != i && i != 0)
				{
					row_ptr_vector.push_back(n_nz_A_CSR);
					rwp++;
					g--;
					if((k-i)>1){
					g = i;
					}

				}
				n_nz_A_CSR++;
			}

		}
		g++;
		if (g - i < 2)
		{
			g = i + 2;
		}
	}
	rwp++;
	n_nz_A_CSR++;
	row_ptr_vector.push_back(n_nz_A_CSR);
	
	for (int i = 0; i < ROW_PTR; i++)
	{
		cout<< row_ptr_vector[i]<<" ";
	}
	
	for (int i = 0; i < COL_A; i++)
	{
		for (int j = 0; j < ROW_A; j++)
		{
			if (A[i][j] != 0)
			{
				nz_vector1.push_back(A[i][j]);
				col_idx_vector.push_back(j);
			}
		}
	}


	std::copy(nz_vector1.begin(), nz_vector1.end(), ar_nz);
	std::copy(col_idx_vector.begin(), col_idx_vector.end(), ar_col_idx);
	std::copy(row_ptr_vector.begin(), row_ptr_vector.end(), ar_row_ptr);
	

	        
	fstream ar_nz_CSR("ar_nz_CSR.TXT");
	for (int i = 0; i < nz_A; i++)
	{
		ar_nz_CSR << ar_nz[i]<<" ";
	}

	fstream ar_col_idx_CSR("ar_col_idx_CSR.TXT");
	for (int i = 0; i < nz_A; i++)
	{
		ar_col_idx_CSR << ar_col_idx[i]<<" ";
	}

	fstream ar_row_ptr_CSR("ar_row_ptr_CSR.TXT");
	for (int i = 0; i < ROW_PTR; i++)
	{
		ar_row_ptr_CSR << ar_row_ptr[i]<<" ";
	}
	///
	

}


