void update_line_buff_pool27(datatype_inh linebuf_pool[24][5][111],uint8_t rowAddr[5], uint8_t xx,
		datatype_inh mac_buff[9],uint8_t ochan_no)
{

	uint8_t nstate = 0;
	uint8_t nstate_2 = 0;
	if(xx == 0)
	{
	while(nstate != 3)
	{
		switch(nstate)
		{
		case 0:
		mac_buff[0] =  linebuf_pool[ochan_no][rowAddr[0]][xx];
		mac_buff[3] =  linebuf_pool[ochan_no][rowAddr[1]][xx];
		mac_buff[6] =  linebuf_pool[ochan_no][rowAddr[2]][xx];
		nstate = 1;
		break;
		case 1:
			mac_buff[1] = linebuf_pool[ochan_no][rowAddr[0]][xx+1] ;
			mac_buff[4] = linebuf_pool[ochan_no][rowAddr[1]][xx+1] ;
			mac_buff[7] = linebuf_pool[ochan_no][rowAddr[2]][xx+1] ;
			nstate = 2;
			break;
		case 2:
			mac_buff[2] = linebuf_pool[ochan_no][rowAddr[0]][xx + 2];
			mac_buff[5] = linebuf_pool[ochan_no][rowAddr[1]][xx + 2];
			mac_buff[8] = linebuf_pool[ochan_no][rowAddr[2]][xx + 2];
			nstate = 3;
			break;
		}
	}
	}

	else
	{
		while(nstate_2 != 2)
		{
		switch(nstate_2)
		{
		case 0:
	mac_buff[0] = mac_buff[2];
	mac_buff[1] = linebuf_pool[ochan_no][rowAddr[0]][xx*2 + 1];


	mac_buff[3] = mac_buff[5];
	mac_buff[4] =linebuf_pool[ochan_no][rowAddr[1]][xx*2 + 1];


	mac_buff[6] = mac_buff[8];
	mac_buff[7] = linebuf_pool[ochan_no][rowAddr[2]][xx*2 + 1];
	nstate_2 = 1;
	break;
		case 1:
			mac_buff[2] = linebuf_pool[ochan_no][rowAddr[0]][xx*2 + 2];
			mac_buff[5] = linebuf_pool[ochan_no][rowAddr[1]][xx*2 + 2];
			mac_buff[8] = linebuf_pool[ochan_no][rowAddr[2]][xx*2 + 2];
			nstate_2 = 2;
			break;
		}
	}
	}

}

void update_line_buff_7(datatype_wgt linebuf[9][227],uint8_t rowAddr[9], uint8_t xx,
		uint8_t isize,datatype_wgt mac_buff_7[49],uint8_t xVal_base){
	uint8_t nstate = 0;
	uint8_t nstate_1 = 0;
	if(xx == 0)
	{
		while (nstate != 7)
		{
		switch(nstate){
		case 0:
		mac_buff_7[0*7 + 0] = linebuf[rowAddr[0]][ 0];
		mac_buff_7[1*7 + 0] = linebuf[rowAddr[1]][ 0];
		mac_buff_7[2*7 + 0] = linebuf[rowAddr[2]][ 0];
		mac_buff_7[3*7 + 0] = linebuf[rowAddr[3]][ 0];
		mac_buff_7[4*7 + 0] = linebuf[rowAddr[4]][ 0];
		mac_buff_7[5*7 + 0] = linebuf[rowAddr[5]][ 0];
		mac_buff_7[6*7 + 0] = linebuf[rowAddr[6]][ 0];
		nstate = 1;
		break;
		case 1:
		mac_buff_7[1*7 + 1] = linebuf[rowAddr[1]][ 1];
		mac_buff_7[0*7 + 1] = linebuf[rowAddr[0]][ 1];
		mac_buff_7[2*7 + 1] = linebuf[rowAddr[2]][ 1];
		mac_buff_7[3*7 + 1] = linebuf[rowAddr[3]][ 1];
		mac_buff_7[4*7 + 1] = linebuf[rowAddr[4]][ 1];
		mac_buff_7[5*7 + 1] = linebuf[rowAddr[5]][ 1];
		mac_buff_7[6*7 + 1] = linebuf[rowAddr[6]][ 1];
		nstate = 2;
		break;

		case 2:
		mac_buff_7[2*7 + 2] = linebuf[rowAddr[2]][ 2];
		mac_buff_7[1*7 + 2] = linebuf[rowAddr[1]][ 2];
		mac_buff_7[0*7 + 2] = linebuf[rowAddr[0]][ 2];
		mac_buff_7[3*7 + 2] = linebuf[rowAddr[3]][ 2];
		mac_buff_7[4*7 + 2] = linebuf[rowAddr[4]][ 2];
		mac_buff_7[5*7 + 2] = linebuf[rowAddr[5]][ 2];
		mac_buff_7[6*7 + 2] = linebuf[rowAddr[6]][ 2];
		nstate = 3;
		break;

		case 3:
		mac_buff_7[3*7 + 3] = linebuf[rowAddr[3]][ 3];
		mac_buff_7[1*7 + 3] = linebuf[rowAddr[1]][ 3];
		mac_buff_7[0*7 + 3] = linebuf[rowAddr[0]][ 3];
		mac_buff_7[2*7 + 3] = linebuf[rowAddr[2]][ 3];
		mac_buff_7[4*7 + 3] = linebuf[rowAddr[4]][ 3];
		mac_buff_7[5*7 + 3] = linebuf[rowAddr[5]][ 3];
		mac_buff_7[6*7 + 3] = linebuf[rowAddr[6]][ 3];
		nstate = 4;
		break;

		case 4:
		mac_buff_7[4*7 + 4] = linebuf[rowAddr[4]][ 4];
		mac_buff_7[1*7 + 4] = linebuf[rowAddr[1]][ 4];
		mac_buff_7[0*7 + 4] = linebuf[rowAddr[0]][ 4];
		mac_buff_7[2*7 + 4] = linebuf[rowAddr[2]][ 4];
		mac_buff_7[3*7 + 4] = linebuf[rowAddr[3]][ 4];
		mac_buff_7[5*7 + 4] = linebuf[rowAddr[5]][ 4];
		mac_buff_7[6*7 + 4] = linebuf[rowAddr[6]][ 4];
		nstate = 5;
		break;

		case 5:
		mac_buff_7[6*7 + 5] = linebuf[rowAddr[6]][ 5];
		mac_buff_7[0*7 + 5] = linebuf[rowAddr[0]][ 5];
		mac_buff_7[1*7 + 5] = linebuf[rowAddr[1]][ 5];
		mac_buff_7[2*7 + 5] = linebuf[rowAddr[2]][ 5];
		mac_buff_7[5*7 + 5] = linebuf[rowAddr[5]][ 5];
		mac_buff_7[3*7 + 5] = linebuf[rowAddr[3]][ 5];
		mac_buff_7[4*7 + 5] = linebuf[rowAddr[4]][ 5];
		nstate = 6;
		break;

		case 6:
		mac_buff_7[3*7 + 6] = linebuf[rowAddr[3]][ 6];
		mac_buff_7[4*7 + 6] = linebuf[rowAddr[4]][ 6];
		mac_buff_7[5*7 + 6] = linebuf[rowAddr[5]][ 6];
		mac_buff_7[0*7 + 6] = linebuf[rowAddr[0]][ 6];
		mac_buff_7[1*7 + 6] = linebuf[rowAddr[1]][ 6];
		mac_buff_7[2*7 + 6] = linebuf[rowAddr[2]][ 6];
		mac_buff_7[6*7 + 6] = linebuf[rowAddr[6]][ 6];
		nstate = 7;
		break;
		}
	}

	}

	else
	{
while(nstate_1 != 4)
{
		switch(nstate_1){
		case 0:
		#pragma HLS PIPELINE
		mac_buff_7[0*7 + 0] = mac_buff_7[0*7 + 1 + 0];
		mac_buff_7[1*7 + 0] = mac_buff_7[1*7 + 1 + 0];
		mac_buff_7[2*7 + 0] = mac_buff_7[2*7 + 1 + 0];
		mac_buff_7[3*7 + 0] = mac_buff_7[3*7 + 1 + 0];
		mac_buff_7[4*7 + 0] = mac_buff_7[4*7 + 1 + 0];
		mac_buff_7[5*7 + 0] = mac_buff_7[5*7 + 1 + 0];
		mac_buff_7[5*7 + 0] = mac_buff_7[5*7 + 1 + 0];
		mac_buff_7[6*7 + 0] = mac_buff_7[6*7 + 1 + 0];

		mac_buff_7[1*7 + 1] = mac_buff_7[1*7 + 1 + 1];
		mac_buff_7[0*7 + 1] = mac_buff_7[0*7 + 1 + 1];
		mac_buff_7[2*7 + 1] = mac_buff_7[2*7 + 1 + 1];
		mac_buff_7[3*7 + 1] = mac_buff_7[3*7 + 1 + 1];
		mac_buff_7[4*7 + 1] = mac_buff_7[4*7 + 1 + 1];
		mac_buff_7[5*7 + 1] = mac_buff_7[5*7 + 1 + 1];
		mac_buff_7[6*7 + 1] = mac_buff_7[6*7 + 1 + 1];

		mac_buff_7[2*7 + 2] = mac_buff_7[2*7 + 1 + 2];
		mac_buff_7[1*7 + 2] = mac_buff_7[1*7 + 1 + 2];
		mac_buff_7[0*7 + 2] = mac_buff_7[0*7 + 1 + 2];
		mac_buff_7[3*7 + 2] = mac_buff_7[3*7 + 1 + 2];
		mac_buff_7[4*7 + 2] = mac_buff_7[4*7 + 1 + 2];
		mac_buff_7[5*7 + 2] = mac_buff_7[5*7 + 1 + 2];
		mac_buff_7[6*7 + 2] = mac_buff_7[6*7 + 1 + 2];

		mac_buff_7[3*7 + 3] = mac_buff_7[3*7 + 1 + 3];
		mac_buff_7[1*7 + 3] = mac_buff_7[1*7 + 1 + 3];
		mac_buff_7[0*7 + 3] = mac_buff_7[0*7 + 1 + 3];
		mac_buff_7[2*7 + 3] = mac_buff_7[2*7 + 1 + 3];
		mac_buff_7[4*7 + 3] = mac_buff_7[4*7 + 1 + 3];
		mac_buff_7[5*7 + 3] = mac_buff_7[5*7 + 1 + 3];
		mac_buff_7[6*7 + 3] = mac_buff_7[6*7 + 1 + 3];

		mac_buff_7[4*7 + 4] = mac_buff_7[4*7 + 1 + 4];
		mac_buff_7[1*7 + 4] = mac_buff_7[1*7 + 1 + 4];
		mac_buff_7[0*7 + 4] = mac_buff_7[0*7 + 1 + 4];
		mac_buff_7[2*7 + 4] = mac_buff_7[2*7 + 1 + 4];
		mac_buff_7[3*7 + 4] = mac_buff_7[3*7 + 1 + 4];
		mac_buff_7[5*7 + 4] = mac_buff_7[5*7 + 1 + 4];
		mac_buff_7[6*7 + 4] = mac_buff_7[6*7 + 1 + 4];
		nstate_1 = 2;
		break;

		case 2:
		mac_buff_7[6*7 + 5] =  linebuf[rowAddr[6]][xx*2 + 5];
		mac_buff_7[0*7 + 5] =  linebuf[rowAddr[0]][xx*2 + 5];
		mac_buff_7[1*7 + 5] =  linebuf[rowAddr[1]][xx*2 + 5];
		mac_buff_7[2*7 + 5] =  linebuf[rowAddr[2]][xx*2 + 5];
		mac_buff_7[5*7 + 5] =  linebuf[rowAddr[5]][xx*2 + 5];
		mac_buff_7[3*7 + 5] =  linebuf[rowAddr[3]][xx*2 + 5];
		mac_buff_7[4*7 + 5] =  linebuf[rowAddr[4]][xx*2 + 5];
		nstate_1 = 3;
		break;

		case 3:
		mac_buff_7[3*7 + 6] =  linebuf[rowAddr[3]][xx*2 + 6];
		mac_buff_7[4*7 + 6] =  linebuf[rowAddr[4]][xx*2 + 6];
		mac_buff_7[5*7 + 6] =  linebuf[rowAddr[5]][xx*2 + 6];
		mac_buff_7[0*7 + 6] =  linebuf[rowAddr[0]][xx*2 + 6];
		mac_buff_7[1*7 + 6] =  linebuf[rowAddr[1]][xx*2 + 6];
		mac_buff_7[2*7 + 6] =  linebuf[rowAddr[2]][xx*2 + 6];
		mac_buff_7[6*7 + 6] =  linebuf[rowAddr[6]][xx*2 + 6];
		nstate_1 = 4;
		break;
		}
	}
	}

}

void update_line_buff_pool2(datatype_inh linebuf_pool[128][5][55],uint8_t rowAddr[5], uint8_t xx,
		datatype_inh mac_buff[9],uint8_t ochan_no)
{

	uint8_t nstate = 0;
	uint8_t next_s = 0;
if(xx == 0)
{
	while(nstate != 3)
	{
	switch(nstate)
	{
	case 0:
	mac_buff[0] =  linebuf_pool[ochan_no][rowAddr[0]][xx];
	mac_buff[3] =  linebuf_pool[ochan_no][rowAddr[1]][xx];
	mac_buff[6] =  linebuf_pool[ochan_no][rowAddr[2]][xx];
	nstate = 1;
	break;
	case 1:
		mac_buff[1] = linebuf_pool[ochan_no][rowAddr[0]][xx+1];
		mac_buff[4] = linebuf_pool[ochan_no][rowAddr[1]][xx+1];
		mac_buff[7] = linebuf_pool[ochan_no][rowAddr[2]][xx+1];
		nstate = 2;
		break;
	case 2:
		mac_buff[2] = linebuf_pool[ochan_no][rowAddr[0]][xx + 2];
		mac_buff[5] = linebuf_pool[ochan_no][rowAddr[1]][xx + 2];
		mac_buff[8] = linebuf_pool[ochan_no][rowAddr[2]][xx + 2];
		nstate = 3;
		break;
	}
	}

}

else
{

	while(next_s != 2)
	{
	switch(next_s)
	{
	case 0:

mac_buff[0] = mac_buff[2];
mac_buff[1] = linebuf_pool[ochan_no][rowAddr[0]][xx*2 + 1];
mac_buff[3] = mac_buff[5];
mac_buff[4] =linebuf_pool[ochan_no][rowAddr[1]][xx*2 + 1];
mac_buff[6] = mac_buff[8];
mac_buff[7] = linebuf_pool[ochan_no][rowAddr[2]][xx*2 + 1];
next_s = 1;
break;

	case 1:
		mac_buff[2] = linebuf_pool[ochan_no][rowAddr[0]][xx*2 + 2];
		mac_buff[5] = linebuf_pool[ochan_no][rowAddr[1]][xx*2 + 2];
		mac_buff[8] = linebuf_pool[ochan_no][rowAddr[2]][xx*2 + 2];
		next_s = 2;
		break;
	}
	}
}
}



void update_line_buff_0(datatype_inh linebuf[4][55],uint8_t rowAddr[4], uint8_t xx,
		uint8_t isize,datatype_inh mac_buff[9]
		)
{

	uint8_t nstate = 0;
	if(xx == 0)
	{
		while(nstate != 2)
		{
	switch(nstate)
	{
	case 0:
		mac_buff[0] =  0; mac_buff[1] = linebuf[rowAddr[0]][xx] ; //mac_buff[2] = linebuf[rowAddr[0]][xx + 1] ;
		mac_buff[3] =  0; mac_buff[4] = linebuf[rowAddr[1]][xx] ; //mac_buff[5] = linebuf[rowAddr[1]][xx + 1];
		mac_buff[6] =  0; mac_buff[7] = linebuf[rowAddr[2]][xx] ; //mac_buff[8] = linebuf[rowAddr[2]][xx + 1];
		nstate = 1;
		break;
	case 1:
		mac_buff[2] = linebuf[rowAddr[0]][xx + 1];
		mac_buff[5] = linebuf[rowAddr[1]][xx + 1];
		mac_buff[8] = linebuf[rowAddr[2]][xx + 1];
		nstate = 2;
		break;
	}
		}
	}

	else if(xx == isize- 1)
	{
		mac_buff[0] = mac_buff[1];
		mac_buff[1] = mac_buff[2];
		mac_buff[2] = 0;

		mac_buff[3] = mac_buff[4];
		mac_buff[4] = mac_buff[5];
		mac_buff[5] = 0;

		mac_buff[6] = mac_buff[7];
		mac_buff[7] = mac_buff[8];
		mac_buff[8] = 0;
	}

	else
	{
	mac_buff[0] = mac_buff[1];
	mac_buff[1] = mac_buff[2];
	mac_buff[2] = linebuf[rowAddr[0]][xx + 1];

	mac_buff[3] = mac_buff[4];
	mac_buff[4] = mac_buff[5];
	mac_buff[5] = linebuf[rowAddr[1]][xx + 1];

	mac_buff[6] = mac_buff[7];
	mac_buff[7] = mac_buff[8];
	mac_buff[8] = linebuf[rowAddr[2]][xx + 1];
	}

}


// This code fails in the  final bitstream but has a single cycle behavior
