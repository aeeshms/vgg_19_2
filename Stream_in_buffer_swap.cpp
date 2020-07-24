void stream_in(
hls::stream<datatype_inh> stream_in[128],
uint8_t isize2,
datatype_inh *input,
int bb2,uint16_t ichan2,int8_t wsize2,uint16_t ochan_fac2,
int inp_offset,
uint8_t isize1,
uint16_t ichan1,int8_t wsize1,uint16_t ochan_fac1,bool swap, uint8_t bb, uint8_t ichan_index
		)
{
uint16_t ichan_sc;
uint8_t isize = isize1;

uint8_t isize22 = isize1;
uint8_t isize33 = isize1;
uint16_t  ochan_fac = ochan_fac1;
uint8_t  wsize = wsize1;
uint16_t ichan = ichan1;
int inp_offset1 = inp_offset;

static datatype_inh inp_buff_0[128][55*55];
#pragma HLS RESOURCE variable=inp_buff_0 core=XPM_MEMORY uram
#pragma HLS ARRAY_PARTITION variable=inp_buff_0 complete dim=1

static datatype_inh inp_buff_1[128][55*55];
#pragma HLS RESOURCE variable=inp_buff_1 core=XPM_MEMORY uram
#pragma HLS ARRAY_PARTITION variable=inp_buff_1 complete dim=1

if(ichan < 128)
		ichan_sc = ichan;
else
		ichan_sc = 128;
//static bool swap_buff = false;
static uint8_t xx = 0;

if(bb < ichan_index - 1 or bb == 0)
{
for(uint16_t i = 0 ; i < ichan_sc ; i++)
		{
				for(int k = 0 ; k < isize * isize ; k++)
						{
						#pragma HLS PIPELINE
						datatype_inh dp_point;
						dp_point = (datatype_inh) input[k + i*isize22*isize33 + (bb)*isize*isize*128];
						inp_buff_0[i][k] = dp_point;
						}

		}
//std:: cout<<"inp_buff_0 = " << std::endl;
std:: cout<<"inp_buff_0 write = " << std::endl;
}


if(swap == false)
{
for (int i = 0 ; i < isize*isize ; i++)
	{
	for (int j = 0 ; j < 128 ; j++)
	{
	#pragma HLS UNROLL
	datatype_inh dpin_0 = inp_buff_0[j][i];
	stream_in[j] << dpin_0;
	}
	}
std:: cout<<"inp_buff_0 read = " << std::endl;
}

if(bb < ichan_index - 1)
{
for(uint16_t i = 0 ; i < ichan_sc ; i++)
		{
				for(int k = 0 ; k < isize * isize ; k++)
						{
						#pragma HLS PIPELINE
						datatype_inh dp_point;
						dp_point = (datatype_inh) input[k + i*isize22*isize33 + (bb+1)*isize*isize*128];
						inp_buff_1[i][k] = dp_point;
						}

		}
//std:: cout<<"inp_buff_1 = " << std::endl;
std:: cout<<"inp_buff_1 write = " << std::endl;
}



if(swap == true)
{
for (int i = 0 ; i < isize*isize ; i++)
	{
	for (int j = 0 ; j < 128 ; j++)
	{
	#pragma HLS UNROLL
	datatype_inh dpin_0 = inp_buff_1[j][i];
	stream_in[j] << dpin_0;
	}
	}
std:: cout<<"inp_buff_1 read = " << std::endl;
}

}
