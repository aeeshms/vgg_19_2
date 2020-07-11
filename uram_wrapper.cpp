#pragma HLS RESOURCE variable=output_5 core=XPM_MEMORY uram latency=10

// the above line improves the freq. of operation for large URAM bank in Vivado_hls but gives wrong result


/////////////////  Break the URAM path with a FSM way_1 /////////////////////////
	static datatype_24bit para_02[64*55*55];
	#pragma HLS RESOURCE variable=para_02 core=XPM_MEMORY uram
	hls::stream<int> stream_uram_out_2("u2");
	#pragma HLS STREAM variable=stream_uram_out_2 depth=16
	int dp_0;
	int dp_1;
	int dp_3;
	int fac = 0;
	//int nstate = 0;
for(int ochan_no = 0 ; ochan_no < ochan_fac*osize*osize ; ochan_no++)
 {
	int nstate = 0;
	switch (nstate)
	{
	case 0:
		#pragma HLS PIPELINE
		stream_adder_out_1 >> dp_0;
		dp_1 = para_02[ochan_no];
		nstate = 1;
		//break;
	case 1:
		#pragma HLS PIPELINE
		dp_3 = dp_1 + dp_0;
		if(ichan_index == 0)
		{
		stream_tile_2 << dp_3;
		para_02[ochan_no] =  0;
		}
		else
		{
		para_02[ochan_no] = dp_3;
		}
		//nstate = 2;
		break;
	}
 }
 ///////////////////////////////////////////////////
 
 //////////////// Way_2 Define a stream interface giving highest freq of operation @300MHZ
 int uram_wrapper_1(hls::stream<datatype_24bit> &stream_uram_addr,
		hls::stream<datatype_24bit> &stream_uram_data,bool wr_rd)
{
	static int para_uram[64*55*55];
	#pragma HLS RESOURCE variable=para_uram core=XPM_MEMORY uram
	int addr;
	int uram_data;
	if(wr_rd == 1)
	{
		stream_uram_addr >> addr;
		return para_uram[addr];
	}
	else
	{
		stream_uram_addr >> addr;
		stream_uram_data >> uram_data;
		para_uram[addr] = uram_data;
		return 0;
	}

}
//////////////////

but both the ways the latency goes up
