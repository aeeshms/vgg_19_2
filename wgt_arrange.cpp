void wgt_rrange(
	FILE *fpoint,
	datatype_wgt *weight,
	datatype_wgt *bias,
	datatype_inh *image,
	datatype_inh *out,
    int i_chan,
    int o_chan,
    int i_size,
    int o_size,
    int w_size,
    int stride,
    int padding,
    int relu_on
)
{

		for(uint8_t unit = 0 ; unit < 4; unit = unit + 1)
			{
		for(uint8_t ichan_no = 0 ; ichan_no < 3 ; ichan_no = ichan_no + 1)
			{
			for(uint8_t ochan_no = 0 ; ochan_no < 24 ; ochan_no = ochan_no + 1)
				{
				for(uint8_t cc = 0 ; cc < w_size*w_size ; cc = cc + 1)
				{
				//int16_t data ;
				float data ;
				data = weight[cc + ochan_no*i_chan*w_size*w_size +  w_size*w_size*ichan_no + unit*24*3*w_size*w_size];
//std::cout <<   cc + ochan_no*i_chan*w_size*w_size +  w_size*w_size*ichan_no +
//		bb*64*w_size*w_size + aa*256*w_size*w_size*i_chan + unit*ochan_fac*i_chan*w_size*w_size << std::endl;
				//std::string str = std::to_string(data);
				//std::cout <<   write_out[j] << std::endl;
				//int16_t dd = (int16_t) (data*64);
				fprintf(fpoint,"%f", data);
				fprintf(fpoint,"\n");
				//count = count + 1;
				}
			}

			}
			}



	if(o_chan <= 256){
	scheduler_fac_ochan = 1;
	ochan_fac = (o_chan >> 3);
	}
	else{
	scheduler_fac_ochan = ceil(((float) o_chan)/256);
	ochan_fac = 32;
	 }

	if(i_chan <= 64){
	scheduler_fac_ichan = 1;
	}
	else{
	scheduler_fac_ichan = ceil(((float)i_chan)/64);
	}
//	std::cout << "i_chan " << i_chan << std::endl;
//	std::cout << "o_chan " << o_chan << std::endl;
//	std::cout << "scheduler_fac_ichan " << scheduler_fac_ichan << std::endl;
//	std::cout << "scheduler_fac_ochan " << scheduler_fac_ochan << std::endl;
//	std::cout << "ochan_fac " << ochan_fac << std::endl;
	static int count;
	static int count_act;

	//count_act = 0;



	//std::cout << "add range " << i_chan*ochan_fac*8*w_size*w_size << std::endl;

for(uint8_t aa = 0 ; aa < scheduler_fac_ochan; aa = aa + 1)
	{
	for(uint8_t bb = 0 ; bb < scheduler_fac_ichan ; bb = bb + 1)
		{

		if(i_chan <= 64)
		{
		ichan_sc = i_chan;
		}
		else{
		if(i_chan == 96 and bb == 1)
			ichan_sc = 32;
		else
		ichan_sc = 64;
		}


		for(uint8_t unit = 0 ; unit < 8; unit = unit + 1)
			{
		for(uint8_t ichan_no = 0 ; ichan_no < ichan_sc ; ichan_no = ichan_no + 1)
			{
			for(uint8_t ochan_no = 0 ; ochan_no < ochan_fac ; ochan_no = ochan_no + 1)
				{
				for(uint8_t cc = 0 ; cc < w_size*w_size ; cc = cc + 1)
				{
				//int16_t data ;
				float data ;
data = weight[cc + ochan_no*i_chan*w_size*w_size +  w_size*w_size*ichan_no +
			  bb*64*w_size*w_size + aa*256*w_size*w_size*i_chan + unit*ochan_fac*i_chan*w_size*w_size];
//std::cout <<   cc + ochan_no*i_chan*w_size*w_size +  w_size*w_size*ichan_no +
//		bb*64*w_size*w_size + aa*256*w_size*w_size*i_chan + unit*ochan_fac*i_chan*w_size*w_size << std::endl;
				//std::string str = std::to_string(data);
				//std::cout <<   write_out[j] << std::endl;
				int16_t dd = (int16_t) (data*64);
				fprintf(fpoint,"%d", dd);
				fprintf(fpoint,"\n");
				count = count + 1;
				}
			}

		}
	}
	}
	}
}
