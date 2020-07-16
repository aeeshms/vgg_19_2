void stream_in(
uint8_t  dim_1 = 0;
int dim_2;
for(int i = 0,dim_2 = 0 ; i < 128*55*55 ; i++,dim_2++)
		{
		#pragma HLS PIPELINE
		datatype_inh dp_point;
		dp_point = input[i];
		inp_buff_0[dim_1][dim_2] = dp_point;
		if(dim_2 == isize*isize-1)
		{
			dim_1 = dim_1 + 1;
			dim_2 = 0;
		}
		}
    
    	int8_t wgt_buff_0[128][64][3*3];
	//#pragma HLS RESOURCE variable=wgt_buff_0 core=XPM_MEMORY uram
	#pragma HLS ARRAY_PARTITION variable=wgt_buff_0 complete dim=1
	int8_t wgt[128*3*3];
	uint8_t dim_1 = 0;
	uint8_t dim_2 = 0;
	uint8_t dim_3 = 0;

	for(int jj = 0,dim_3 = 0; jj < 128*64*9 ; jj++,dim_3++)
	{
			#pragma HLS PIPELINE
			int8_t dp_point;
			dp_point = weights[jj];

			wgt_buff_0[dim_1][dim_2][dim_3] = dp_point;

			if(dim_3 == wsize-1)
			{
				dim_1 = dim_1 + 1;
				dim_3 = 0;
			}


			if(dim_1 = ichan_sc-1)
			{
				dim_2 = dim_2 + 1;
				dim_1 = 0;
			}
	}
    }
