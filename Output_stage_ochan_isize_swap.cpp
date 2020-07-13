// Performance degrades by 20%

void stream_out_pool_fused_output_0(
hls::stream<datatype_inh> &stream_pool_fused_out_0,
hls::stream<datatype_inh> &stream_convo_out_final_0,
hls::stream<datatype_inh> &stream_pool_fused_out_1,
hls::stream<datatype_inh> &stream_convo_out_final_1,
datatype_inh *output_1,
uint16_t ochan2, uint8_t osize_pool2,bool pool_on2,uint8_t isize2, int out_offset1,
                 int pool_offset1,uint16_t aa_ochan2,uint8_t ichan_index2, uint8_t bb2,uint16_t ochan_fac2,
				 uint8_t osize_pool,
				 bool pool_on1,
				 uint8_t isize1,
				 uint8_t ichan_index1,
				 uint8_t ochan_fac1){

	uint8_t isize = isize1;
	uint8_t  ochan_fac = ochan_fac1;
	bool pool_on = pool_on1;
	uint8_t ichan_index = ichan_index1;
	int out_offset = out_offset1;
	int pool_offset = pool_offset1;

datatype_inh linebuf_out1[2][128*56];
#pragma HLS ARRAY_PARTITION variable=linebuf_out1 complete dim=1

datatype_inh linebuf_out2[2][128*56];
#pragma HLS ARRAY_PARTITION variable=linebuf_out2 complete dim=1

datatype_inh linebuf_out11[2][128*56];
#pragma HLS ARRAY_PARTITION variable=linebuf_out11 complete dim=1

datatype_inh linebuf_out22[2][128*56];
#pragma HLS ARRAY_PARTITION variable=linebuf_out22 complete dim=1

bool swap_out = true;
bool pac_out = 0;

bool swap_out_2 = true;
bool pac_out_2 = 0;

if(pool_on == 1 and ichan_index == 0)
 {
  for(uint8_t yy = 0 ; yy < osize_pool-1; yy++)
   {
		swap_out = !swap_out;

		if(swap_out == true or yy == 0)
		{
		  for(int xx = 0 ; xx < osize_pool*ochan_fac; xx++)
			{
			#pragma HLS PIPELINE
			datatype_inh dp_0;
			stream_pool_fused_out_0 >> dp_0;
			linebuf_out1[0][xx] = dp_0;


			datatype_inh dp_01;
			stream_pool_fused_out_1 >> dp_01;
			linebuf_out1[1][xx] = dp_01;
			}
		}

	   if(swap_out == 0)
	   {
		   for(uint8_t ochan_no = 0 ; ochan_no < ochan_fac ; ochan_no++)
		   {
			  for(uint8_t xx = 0 ; xx < osize_pool; xx++)
				{
				#pragma HLS PIPELINE
				datatype_inh dp_0;
				//stream_pool_fused_out_0 >> dp_0;
				output_1[xx + ochan_no*osize_pool*osize_pool + (yy+pac_out)*osize_pool + osize_pool*osize_pool*ochan_fac*0 + pool_offset] = linebuf_out1[0][xx + ochan_no*osize_pool];


				datatype_inh dp_01;
				//stream_pool_fused_out_1 >> dp_01;
				output_1[xx + ochan_no*osize_pool*osize_pool + (yy+pac_out)*osize_pool + osize_pool*osize_pool*ochan_fac*1 + pool_offset] = linebuf_out1[1][xx + ochan_no*osize_pool];
				}
		   }

	   }

		if(swap_out == 0)
		{
			  for(int xx = 0 ; xx < osize_pool*ochan_fac; xx++)
				{
				#pragma HLS PIPELINE
				datatype_inh dp_0;
				stream_pool_fused_out_0 >> dp_0;
				linebuf_out2[0][xx] = dp_0;


				datatype_inh dp_01;
				stream_pool_fused_out_1 >> dp_01;
				linebuf_out2[1][xx] = dp_01;
				}

		}

	   if(swap_out == 1)
	   {
		   for(uint8_t ochan_no = 0 ; ochan_no < ochan_fac ; ochan_no++)
		   {
			  for(uint8_t xx = 0 ; xx < osize_pool; xx++)
				{
				#pragma HLS PIPELINE
				datatype_inh dp_0;
				//stream_pool_fused_out_0 >> dp_0;
				output_1[xx + (ochan_no)*osize_pool*osize_pool + (yy+1)*osize_pool + osize_pool*osize_pool*ochan_fac*0 + pool_offset] = linebuf_out2[0][xx + ochan_no*osize_pool];


				datatype_inh dp_01;
				//stream_pool_fused_out_1 >> dp_01;
				output_1[xx + (ochan_no)*osize_pool*osize_pool + (yy+1)*osize_pool + osize_pool*osize_pool*ochan_fac*1 + pool_offset] = linebuf_out2[1][xx + ochan_no*osize_pool];
				}
		   }

	   }

	   pac_out = 1;
    }
}


else if(ichan_index == 0)
 {
  for(uint8_t yy = 0 ; yy < isize-1; yy++)
   {
		swap_out_2 = !swap_out_2;

		if(swap_out_2 == true or yy == 0)
		{
		  for(int xx = 0 ; xx < isize*ochan_fac; xx++)
			{
			#pragma HLS PIPELINE
			datatype_inh dp_0;
			stream_convo_out_final_0 >> dp_0;
			linebuf_out11[0][xx] = dp_0;


			datatype_inh dp_01;
			stream_convo_out_final_1 >> dp_01;
			linebuf_out11[1][xx] = dp_01;
			}
		}

	   if(swap_out_2 == 0)
	   {
		   for(uint8_t ochan_no = 0 ; ochan_no < ochan_fac ; ochan_no++)
		   {
			  for(uint8_t xx = 0 ; xx < isize; xx++)
				{
				#pragma HLS PIPELINE
				datatype_inh dp_0;
				//stream_pool_fused_out_0 >> dp_0;
				output_1[xx + ochan_no*isize*isize + (yy+pac_out_2)*isize + isize*isize*ochan_fac*0 + out_offset] = linebuf_out11[0][xx + ochan_no*isize];


				datatype_inh dp_01;
				//stream_pool_fused_out_1 >> dp_01;
				output_1[xx + ochan_no*isize*isize + (yy+pac_out_2)*isize + isize*isize*ochan_fac*1 + out_offset] = linebuf_out11[1][xx + ochan_no*isize];
				}
		   }

	   }

		if(swap_out_2 == 0)
		{
			  for(int xx = 0 ; xx < isize*ochan_fac; xx++)
				{
				#pragma HLS PIPELINE
				datatype_inh dp_0;
				stream_convo_out_final_0 >> dp_0;
				linebuf_out22[0][xx] = dp_0;


				datatype_inh dp_01;
				stream_convo_out_final_1 >> dp_01;
				linebuf_out22[1][xx] = dp_01;
				}
		}

	   if(swap_out_2 == 1)
	   {
		   for(uint8_t ochan_no = 0 ; ochan_no < ochan_fac ; ochan_no++)
		   {
			  for(uint8_t xx = 0 ; xx < isize; xx++)
				{
				#pragma HLS PIPELINE
				datatype_inh dp_0;
				//stream_pool_fused_out_0 >> dp_0;
				output_1[xx + (ochan_no)*isize*isize + (yy+1)*isize + isize*isize*ochan_fac*0 + out_offset] = linebuf_out22[0][xx + ochan_no*isize];


				datatype_inh dp_01;
				//stream_pool_fused_out_1 >> dp_01;
				output_1[xx + (ochan_no)*isize*isize + (yy+1)*isize + isize*isize*ochan_fac*1 + out_offset] = linebuf_out22[1][xx + ochan_no*isize];
				}
		   }

	   }
	   pac_out_2 = 1;
    }
}

}
