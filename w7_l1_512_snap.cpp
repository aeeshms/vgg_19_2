#include "stdint.h"
#include <iostream>
#include <hls_stream.h>
#include "ap_fixed.h"
//typedef ap_fixed<16,8> datatype_inh;
#include <hls_half.h>
//typedef int datatype_inh_2;
//typedef int datatype_arg;
//#define ICHAN 128 // 64 to 512
//#define OCHAN 64 // 3 to 512
//#define WSize 1//3//1//3
//#define Stride 1//2//1//1
//#define Padding 1//1//0//1
#include "ap_int.h"
#include <ap_utils.h>
#include <stdio.h>
#include "stdint.h"
#include <stdlib.h>


typedef int16_t datatype_inh;
//typedef ap_int<20> datatype_24bit;
typedef int datatype_24bit;
typedef int16_t datatype_wgt;

//typedef ap_int<12> datatype_inh;
//833

//#define uint8_t int
//#define uint16_t int

//void stream_input(
//hls::stream<datatype_inh> stream_in_7[12],
//ap_int<512>  *input)
//{
//
//datatype_inh buff_1[3][227*227];
//#pragma HLS ARRAY_PARTITION variable=buff_1 complete dim=1
//int noofreads = 3*227*227*16/512 + 1;
//ap_int<512> tmp;
//int curr_frame = 0;
//int curr_off = 0;
//int next_off = 0;
//int curr_frame_boundry = 0;
//int previous_frame_boundry = 0;
//int previous_no_of_bytes = 0;
//int curr_no_of_bytes = 0;
//int next_no_of_bytes = 0;
//int next_state=0;
//int total_read = 0;
//int count = 0;
//int byte64s = 0;
//int offset = 0;
//
//while (total_read < 4831)
//{
//tmp = input[total_read];
//total_read = total_read + 1;
//for (short k = 0; k < 32; k++)
//  {
//  buff_1[curr_frame][k+count*32 + offset] = tmp(16 * (k + 1) - 1, 16 * k);
//  }
//count = count + 1;
//previous_no_of_bytes = (curr_frame+1)*227*227 -(total_read)*32;
//if(previous_no_of_bytes <= 32)
//{
//next_no_of_bytes = 32 - previous_no_of_bytes;
//tmp = input[total_read];
//total_read = total_read + 1;
//for (short k = 0; k < previous_no_of_bytes; k++)
//  {
//  buff_1[curr_frame][227*227-previous_no_of_bytes + k] = tmp(16 * (k + 1) - 1, 16 * k);//k+count*32 + offset
//  }
//curr_frame = curr_frame + 1;
//offset = next_no_of_bytes;
//for (short k = 0; k < next_no_of_bytes; k++)
//  {
//  buff_1[curr_frame][k] = tmp(16 * (k + 1 + previous_no_of_bytes) - 1, 16 * (k + previous_no_of_bytes));
//  }
//previous_no_of_bytes = 0;
//count = 0;
//	}
//}
//
//for (int j = 0 ; j < 227*227 ; j++)
//{
//		datatype_inh dp0 = buff_1[0][j];
//		stream_in_7[0] << dp0;
//		datatype_inh dp1 = buff_1[1][j];
//		stream_in_7[1] << dp1;
//		datatype_inh dp2 = buff_1[2][j];
//		stream_in_7[2] << dp2;
//}
//}
//
//void stream_out_final(hls::stream<datatype_inh> stream_in_7[12],ap_int<512> *output)
//{
////datatype_inh out_buff[4][24*55*55];
////#pragma HLS ARRAY_PARTITION variable=out_buff complete dim=1
////#pragma HLS RESOURCE variable=linebuf_out17 core=RAM_2P_LUTRAM
//
//	datatype_inh buff_2[3][227*227];
//	#pragma HLS ARRAY_PARTITION variable=buff_2 complete dim=1
//	datatype_inh dp0,dp1,dp2;
//for (int j = 0 ; j < 227*227 ; j++)
//{
//
//		stream_in_7[0] >>  dp0;
//		buff_2[0][j] = dp0;
//		stream_in_7[1] >>  dp1;
//		buff_2[1][j] = dp1;
//		stream_in_7[2] >> dp2;
//		buff_2[2][j] = dp2;
//}
//
//ap_int<512> tmp;
//int curr_frame = 0;
//int curr_off = 0;
//int next_off = 0;
//int curr_frame_boundry = 0;
//int previous_frame_boundry = 0;
//int previous_no_of_bytes = 0;
//int curr_no_of_bytes = 0;
//int next_no_of_bytes = 0;
//int next_state=0;
//int total_writes = 0;
//int count = 0;
//int byte64s= 0;
//int offset = 0;
//int noofreads = 3*227*227*16/512 + 1;
//
//while(total_writes < noofreads)
//{
//
//for (short k = 0; k < 32; k++) {
//tmp(16 * (k + 1) - 1, 16 * k) = buff_2[curr_frame][k + count*32 + offset];
//}
//count = count + 1;
//output[total_writes] = tmp;
//total_writes = total_writes + 1;
//
//previous_no_of_bytes = (curr_frame+1)*24*55*55 -(total_writes)*32;
//if(previous_no_of_bytes <= 32)
//{
//next_no_of_bytes = 32 - previous_no_of_bytes;
//for (short k = 0; k < previous_no_of_bytes; k++) {
//tmp(16 * (k + 1) - 1, 16 * k) = buff_2[curr_frame][24*55*55-previous_no_of_bytes + k];
//}
//curr_frame = curr_frame + 1;
//for (short k = 0; k < next_no_of_bytes; k++) {
//tmp(16 * (k + 1 + previous_no_of_bytes) - 1, 16 * (k + previous_no_of_bytes)) = buff_2[curr_frame][k];
//}
//
//output[total_writes] = tmp;
//total_writes = total_writes + 1;
//offset = next_no_of_bytes;
//previous_no_of_bytes = 0;
//next_state = 0;
//count = 0;
//	}
//}
//}



void update_line_buff_pool27(datatype_inh linebuf_pool[24][5][111],uint8_t rowAddr[5], uint8_t xx,
		datatype_inh mac_buff[9],uint8_t ochan_no)
{

if(xx == 0)
{
	mac_buff[0] =  linebuf_pool[ochan_no][rowAddr[0]][xx]; mac_buff[1] = linebuf_pool[ochan_no][rowAddr[0]][xx+1] ; mac_buff[2] = linebuf_pool[ochan_no][rowAddr[0]][xx + 2] ;
	mac_buff[3] =  linebuf_pool[ochan_no][rowAddr[1]][xx]; mac_buff[4] = linebuf_pool[ochan_no][rowAddr[1]][xx+1] ; mac_buff[5] = linebuf_pool[ochan_no][rowAddr[1]][xx + 2];
	mac_buff[6] =  linebuf_pool[ochan_no][rowAddr[2]][xx]; mac_buff[7] = linebuf_pool[ochan_no][rowAddr[2]][xx+1] ; mac_buff[8] = linebuf_pool[ochan_no][rowAddr[2]][xx + 2];
}

else
{
mac_buff[0] = mac_buff[2];
mac_buff[1] = linebuf_pool[ochan_no][rowAddr[0]][xx*2 + 1];
mac_buff[2] = linebuf_pool[ochan_no][rowAddr[0]][xx*2 + 2];

mac_buff[3] = mac_buff[5];
mac_buff[4] =linebuf_pool[ochan_no][rowAddr[1]][xx*2 + 1];
mac_buff[5] = linebuf_pool[ochan_no][rowAddr[1]][xx*2 + 2];

mac_buff[6] = mac_buff[8];
mac_buff[7] = linebuf_pool[ochan_no][rowAddr[2]][xx*2 + 1];
mac_buff[8] = linebuf_pool[ochan_no][rowAddr[2]][xx*2 + 2];
}
}
int mac7_0_1(datatype_inh wgt_mac_7[7 * 7], datatype_inh mac_buff_7[49]){

//#pragma HLS expression_balance

	datatype_24bit mul[100];
#pragma HLS ARRAY_PARTITION variable=mul complete dim=1

//#pragma HLS PIPELINE
#pragma HLS INLINE
	datatype_24bit result = 0;
   mul[0] = wgt_mac_7[0]*mac_buff_7[0];
   mul[1] = wgt_mac_7[1]*mac_buff_7[1];
   mul[2] = wgt_mac_7[2]*mac_buff_7[2];
   mul[3] = wgt_mac_7[3]*mac_buff_7[3];
   mul[4] = wgt_mac_7[4]*mac_buff_7[4];
   mul[5] = wgt_mac_7[5]*mac_buff_7[5];
   mul[6] = wgt_mac_7[6]*mac_buff_7[6];
   mul[7] = wgt_mac_7[7]*mac_buff_7[7];
   mul[8] = wgt_mac_7[8]*mac_buff_7[8];
   mul[9] = wgt_mac_7[9]*mac_buff_7[9];
   mul[10] = wgt_mac_7[10]*mac_buff_7[10];
   mul[11] = wgt_mac_7[11]*mac_buff_7[11];
   mul[12] = wgt_mac_7[12]*mac_buff_7[12];
   mul[13] = wgt_mac_7[13]*mac_buff_7[13];
   mul[14] = wgt_mac_7[14]*mac_buff_7[14];
   mul[15] = wgt_mac_7[15]*mac_buff_7[15];
   mul[16] = wgt_mac_7[16]*mac_buff_7[16];
   mul[17] = wgt_mac_7[17]*mac_buff_7[17];
   mul[18] = wgt_mac_7[18]*mac_buff_7[18];
   mul[19] = wgt_mac_7[19]*mac_buff_7[19];
   mul[20] = wgt_mac_7[20]*mac_buff_7[20];
   mul[21] = wgt_mac_7[21]*mac_buff_7[21];
   mul[22] = wgt_mac_7[22]*mac_buff_7[22];
   mul[23] = wgt_mac_7[23]*mac_buff_7[23];
   mul[24] = wgt_mac_7[24]*mac_buff_7[24];
   mul[25] = wgt_mac_7[25]*mac_buff_7[25];
   mul[26] = wgt_mac_7[26]*mac_buff_7[26];
   mul[27] = wgt_mac_7[27]*mac_buff_7[27];
   mul[28] = wgt_mac_7[28]*mac_buff_7[28];
   mul[29] = wgt_mac_7[29]*mac_buff_7[29];
   mul[30] = wgt_mac_7[30]*mac_buff_7[30];
   mul[31] = wgt_mac_7[31]*mac_buff_7[31];
   mul[32] = wgt_mac_7[32]*mac_buff_7[32];
   mul[33] = wgt_mac_7[33]*mac_buff_7[33];
   mul[34] = wgt_mac_7[34]*mac_buff_7[34];
   mul[35] = wgt_mac_7[35]*mac_buff_7[35];
   mul[36] = wgt_mac_7[36]*mac_buff_7[36];
   mul[37] = wgt_mac_7[37]*mac_buff_7[37];
   mul[38] = wgt_mac_7[38]*mac_buff_7[38];
   mul[39] = wgt_mac_7[39]*mac_buff_7[39];
   mul[40] = wgt_mac_7[40]*mac_buff_7[40];
   mul[41] = wgt_mac_7[41]*mac_buff_7[41];
   mul[42] = wgt_mac_7[42]*mac_buff_7[42];
   mul[43] = wgt_mac_7[43]*mac_buff_7[43];
   mul[44] = wgt_mac_7[44]*mac_buff_7[44];
   mul[45] = wgt_mac_7[45]*mac_buff_7[45];
   mul[46] = wgt_mac_7[46]*mac_buff_7[46];
   mul[47] = wgt_mac_7[47]*mac_buff_7[47];
   mul[48] = wgt_mac_7[48]*mac_buff_7[48];



   mul[49] = mul[0]+mul[1];
   mul[50] = mul[2]+mul[3];
   mul[51] = mul[4]+mul[5];
   mul[52] = mul[6]+mul[7];
   mul[53] = mul[8]+mul[9];
   mul[54] = mul[10]+mul[11];
   mul[55] = mul[12]+mul[13];
   mul[56] = mul[14]+mul[15];
   mul[57] = mul[16]+mul[17];
   mul[58] = mul[18]+mul[19];
   mul[59] = mul[20]+mul[21];
   mul[60] = mul[22]+mul[23];
   mul[61] = mul[24]+mul[25];
   mul[62] = mul[26]+mul[27];
   mul[63] = mul[28]+mul[29];
   mul[64] = mul[30]+mul[31];
   mul[65] = mul[32]+mul[33];
   mul[66] = mul[34]+mul[35];
   mul[67] = mul[36]+mul[37];
   mul[68] = mul[38]+mul[39];
   mul[69] = mul[40]+mul[41];
   mul[70] = mul[42]+mul[43];
   mul[71] = mul[44]+mul[45];
   mul[72] = mul[46]+mul[47];


   mul[73] = mul[49]+mul[50];
   mul[74] = mul[51]+mul[52];
   mul[75] = mul[53]+mul[54];
   mul[76] = mul[55]+mul[56];
   mul[77] = mul[57]+mul[58];
   mul[78] = mul[59]+mul[60];
   mul[79] = mul[61]+mul[62];
   mul[80] = mul[63]+mul[64];
   mul[81] = mul[65]+mul[66];
   mul[82] = mul[67]+mul[68];
   mul[83] = mul[69]+mul[70];
   mul[84] = mul[71]+mul[72];
   mul[85] = mul[73]+mul[74];
   mul[86] = mul[75]+mul[76];
   mul[87] = mul[77]+mul[78];
   mul[88] = mul[79]+mul[80];
   mul[89] = mul[81]+mul[82];
   mul[90] = mul[83]+mul[84];
   mul[91] = mul[85]+mul[86];
   mul[92] = mul[87]+mul[88];
   mul[93] = mul[89]+mul[90];
   mul[94] = mul[91] + mul[92];
   mul[95] = mul[93] + mul[48];
   result = mul[95] + mul[94];


	return result;
}

void update_line_buff_7(datatype_inh linebuf[9][227],uint8_t rowAddr[9], uint8_t xx,
		uint8_t isize,datatype_inh mac_buff_7[49],uint8_t xVal_base){

#pragma HLS INLINE
if(xx == 0)
{
	for (uint8_t ii = 0 ; ii < 7 ; ii++)
			{
		    #pragma HLS UNROLL
		for (uint8_t i = 0 ; i < 7 ; i++)
			{
			#pragma HLS UNROLL
				mac_buff_7[ii*7 + i] = linebuf[rowAddr[ii]][xVal_base + i];
			}
			}

}

else if(xx == 1)
{
	for(uint8_t hh = 0 ; hh < 2 ; hh++)
	{
		#pragma HLS UNROLL
	for (uint8_t ii = 0 ; ii < 7 ; ii++)
		{
	    #pragma HLS UNROLL
	for (uint8_t i = 0 ; i < 7 ; i++)
		{
		#pragma HLS UNROLL
		if(i<6)
		mac_buff_7[ii*7 + i] = mac_buff_7[ii*7 + i+1];
		else{
			mac_buff_7[ii*7 + i] = linebuf[rowAddr[ii]][xVal_base + i - 1 + hh];
			//std:: cout<<"padding "<<mac_buff_7[ii*7 + i]<< std::endl;
		}
		}
		}
	}
}

else
{
	for(uint8_t hh = 0 ; hh < 2 ; hh++)
	{
	#pragma HLS UNROLL
	for (uint8_t ii = 0 ; ii < 7 ; ii++)
		{
	    #pragma HLS UNROLL
	for (uint8_t i = 0 ; i < 7 ; i++)
		{
		#pragma HLS UNROLL
		if(i<6)
		mac_buff_7[ii*7 + i] = mac_buff_7[ii*7 + i+1];
		else{
			mac_buff_7[ii*7 + i] = linebuf[rowAddr[ii]][xVal_base + 6 - 1 + hh];
			//std:: cout<<"padding "<<mac_buff_7[ii*7 + i]<< std::endl;
		}
		}
		}
	}

}
}

void stream_input_7(
hls::stream<datatype_inh> stream_in_7[12],
ap_int<512>  *input)
{

datatype_inh buff_1[3][227*227];
#pragma HLS ARRAY_PARTITION variable=buff_1 complete dim=1
int noofreads = 3*227*227*16/512 + 1;
ap_int<512> tmp;
int curr_frame = 0;
int curr_off = 0;
int next_off = 0;
int curr_frame_boundry = 0;
int previous_frame_boundry = 0;
int previous_no_of_bytes = 0;
int curr_no_of_bytes = 0;
int next_no_of_bytes = 0;
int next_state=0;
int total_read = 0;
int count = 0;
int byte64s = 0;
int offset = 0;

while (total_read < 4831)
{
tmp = input[total_read];
total_read = total_read + 1;
for (short k = 0; k < 32; k++)
  {
  buff_1[curr_frame][k+count*32 + offset] = tmp(16 * (k + 1) - 1, 16 * k);
  }
count = count + 1;
previous_no_of_bytes = (curr_frame+1)*227*227 -(total_read)*32;
if(previous_no_of_bytes <= 32)
{
next_no_of_bytes = 32 - previous_no_of_bytes;
tmp = input[total_read];
total_read = total_read + 1;
for (short k = 0; k < previous_no_of_bytes; k++)
  {
  buff_1[curr_frame][227*227-previous_no_of_bytes + k] = tmp(16 * (k + 1) - 1, 16 * k);//k+count*32 + offset
  }
curr_frame = curr_frame + 1;
offset = next_no_of_bytes;
for (short k = 0; k < next_no_of_bytes; k++)
  {
  buff_1[curr_frame][k] = tmp(16 * (k + 1 + previous_no_of_bytes) - 1, 16 * (k + previous_no_of_bytes));
  }
previous_no_of_bytes = 0;
count = 0;
	}
}

for (int j = 0 ; j < 227*227 ; j++)
{
		datatype_inh dp0 = buff_1[0][j];
		stream_in_7[0] << dp0;
		stream_in_7[3] << dp0;
		stream_in_7[6] << dp0;
		stream_in_7[9] << dp0;
		datatype_inh dp1 = buff_1[1][j];
		stream_in_7[1] << dp1;
		stream_in_7[4] << dp1;
		stream_in_7[7] << dp1;
		stream_in_7[10] << dp1;
		datatype_inh dp2 = buff_1[2][j];
		stream_in_7[2] << dp2;
		stream_in_7[5] << dp2;
		stream_in_7[8] << dp2;
		stream_in_7[11] << dp2;

}
}



void weight_stream(hls::stream<datatype_inh> stream_weight_7[12],datatype_inh wgt_buff_7[4][3][24][49])
{
#pragma HLS DATAFLOW
//#pragma HLS stable variable=wgt_buff_7
	x1:
	for (uint8_t yy = 0 ; yy < 111; yy++)
	{
		for (uint8_t ii = 0 ; ii < 24; ii++)
		{
			for (uint8_t iii = 0 ; iii < 7*7 ; iii++)
			{
					datatype_inh dp0 = wgt_buff_7[0][0][ii][iii];
					stream_weight_7[0] << dp0;
					datatype_inh dp1 = wgt_buff_7[0][1][ii][iii];
					stream_weight_7[1] << dp1;
					datatype_inh dp2 = wgt_buff_7[0][2][ii][iii];
					stream_weight_7[2] << dp2;
				}
			}
		}

	x2:
	for (uint8_t yy = 0 ; yy < 111; yy++)
	{
	for (uint8_t ii = 0 ; ii < 24; ii++)
		{
			for (uint8_t iii = 0 ; iii < 7*7 ; iii++)
			{
					datatype_inh dp0 = wgt_buff_7[1][0][ii][iii];
					stream_weight_7[3] << dp0;
					datatype_inh dp1 = wgt_buff_7[1][1][ii][iii];
					stream_weight_7[4] << dp1;
					datatype_inh dp2 = wgt_buff_7[1][2][ii][iii];
					stream_weight_7[5] << dp2;
				}
			}
	}

	x3:
	for (uint8_t yy = 0 ; yy < 111; yy++)
	{
		for (uint8_t ii = 0 ; ii < 24; ii++)

		{
			for (uint8_t iii = 0 ; iii < 7*7 ; iii++)
			{
					datatype_inh dp0 = wgt_buff_7[2][0][ii][iii];
					stream_weight_7[6] << dp0;
					datatype_inh dp1 = wgt_buff_7[2][1][ii][iii];
					stream_weight_7[7] << dp1;
					datatype_inh dp2 = wgt_buff_7[2][2][ii][iii];
					stream_weight_7[8] << dp2;
				}
			}
	}

	x4:
	for (uint8_t yy = 0 ; yy < 111; yy++)
	{
		for (uint8_t ii = 0 ; ii < 24; ii++)
			{
			for (uint8_t iii = 0 ; iii < 7*7 ; iii++)
			{
					datatype_inh dp0 = wgt_buff_7[3][0][ii][iii];
					stream_weight_7[9] << dp0;
					datatype_inh dp1 = wgt_buff_7[3][1][ii][iii];
					stream_weight_7[10] << dp1;
					datatype_inh dp2 = wgt_buff_7[3][2][ii][iii];
					stream_weight_7[11] << dp2;
				}
			}
	}
}
void stream_weight_w7(
hls::stream<datatype_inh> stream_weight_7[12],
ap_int<512> *weights
)
{

datatype_inh wgt_buff[4*3*49*24];//441

//	for(int j = 0; j < 441 ; j++)
//		{
//		ap_int<512> tmp;
//		//tmp = i;//weights[j];
//		for (short k = 0; k < 32; k++)
//		{
//		#pragma HLS PIPELINE
//		  wgt_buff[k+32*j] = tmp.range(16 * (k + 1) - 1, 16 * k) + j + k;}
//		//output[j] = tmp + j;
//		}
//
	datatype_inh wgt_buff_7[4][3][24][49];
	#pragma HLS ARRAY_PARTITION variable=wgt_buff_7 complete dim=1
	#pragma HLS ARRAY_PARTITION variable=wgt_buff_7 complete dim=2

	for(uint8_t count = 0 ; count < 4 ; count++)
	{
		for(uint8_t i = 0 ; i < 3 ; i++)
			{
				for(uint16_t j = 0; j < 24 ; j++)
				{
					for(uint8_t k = 0 ; k < 7 * 7 ; k++)
						wgt_buff_7[count][i][j][k] = i ;// wgt_buff[i*7*7 + (j+count*24)*7*7*3 + k];
				}
			}
	}


weight_stream(stream_weight_7,wgt_buff_7);
}


void convo_7(hls::stream<datatype_inh> &stream_convo7_in,
hls::stream<datatype_wgt> &stream_convo7_wgt,
hls::stream<int> &stream_convo7_out)
 {

//#pragma HLS function_instantiate variable=stream_convo7_in
//hls::stream<int> &stream_convo7_out)
// {

#pragma HLS function_instantiate variable=stream_convo7_in


datatype_inh linebuf[9][227];
#pragma HLS RESOURCE variable=linebuf core=RAM_2P_BRAM
#pragma HLS ARRAY_PARTITION variable=linebuf complete dim=1

//#pragma HLS DEPENDENCE variable=linebuf inter false
//#pragma HLS DEPENDENCE variable=linebuf inter false

uint8_t rowAddr[9];
#pragma HLS ARRAY_PARTITION variable=rowAddr complete dim=1


//datatype_wgt wgt_buff_0[96][7 * 7];
//#pragma HLS ARRAY_PARTITION variable=wgt_buff_0 complete dim=1


datatype_inh wgt_mac_7[7 * 7];
#pragma HLS ARRAY_PARTITION variable=wgt_mac_7 complete dim=1

for(uint8_t i = 0; i < 227; i++)
{
#pragma HLS PIPELINE
stream_convo7_in >> linebuf[0][i];
}

for(uint8_t i = 0; i < 227; i++)
{
#pragma HLS PIPELINE
stream_convo7_in >> linebuf[1][i];
}
for(uint8_t i = 0; i < 227; i++)
{
#pragma HLS PIPELINE
stream_convo7_in >> linebuf[2][i];
}

for(ap_uint<4> i = 0; i < 9; i++){
		#pragma HLS UNROLL
			rowAddr[i] = i;	}

//for (uint8_t i = 0 ; i < 24; i++)
//	{
//	or (uint8_t ii = 0 ; ii < 7*7 ; ii++)
//		{
//	//#pragma HLS LOOP_TRIPCOUNT min=124*124 max=124*124
//	#pragma HLS PIPELINE
//stream_convo7_wgt >> wgt_buff_0[i][ii];
////std:: cout<<"wsize \n"<< wgt_buff_0[i][ii]<< std::endl;
//}}

ap_uint<4> rowena = 0;
datatype_inh mac_buff_7[7 * 7];
#pragma HLS ARRAY_PARTITION variable=mac_buff_7 complete dim=1

//datatype_inh mac_buff_2[9];
//#pragma HLS ARRAY_PARTITION variable=mac_buff_2 complete dim=1

 for(ap_uint<4> i = 0; i < 7-3; i++)
 {
   for(uint8_t ii = 0; ii < 227; ii++)
     {
	   stream_convo7_in >> linebuf[3+i][ii];
     }
 }
 //std:: cout<<"stride "<< stride<< std::endl;
 //std:: cout<<"padding "<< std::endl;

	for(uint8_t yy = 0 ; yy < 111; yy++)
		{
		//std:: cout<<"yy= " << yy<< std::endl;
		//#pragma HLS DEPENDENCE variable=linebuf inter false
		for(uint8_t ochan_no = 0 ; ochan_no < 24 ; ochan_no++)
		{
			 for (uint8_t k = 0 ; k < 7*7 ; k++)
					{
					//#pragma HLS PIPELINE
				 datatype_inh nnm;
				 stream_convo7_wgt >> nnm;
				 wgt_mac_7[k] = nnm;
					//wgt_mac_7[k]  = wgt_buff_0[ochan_no][k];
					}

			 //std:: cout<<"ochan_no= " << ochan_no<< std::endl;

	        for(uint8_t xx = 0 ; xx < 111; xx++)
	        	{

	        	uint8_t xVal_base = xx * 2 - 0;
	        	//uint8_t yVal = yy * stride - padding;
	        	//int sum = 1;
	        	//if (yVal >= 0 && yVal < isize && xVal_base >= 0 && (xVal_base) < isize)
	        		//if (xVal_base >= 0 && (xVal_base) < isize)
	        	//{
	        	    #pragma HLS PIPELINE
	        		update_line_buff_7(linebuf,rowAddr,xx,227,mac_buff_7,xVal_base);
	        		stream_convo7_out << mac7_0_1(wgt_mac_7,mac_buff_7);
	            //}
	        	//else

	        		//stream_convo7_out_0_0 << 0;


//	        	for (int i = 0; i < wsize; i++, yVal++) {
//	        	    // Runs over filter window
//	        	    convXaxis:
//	        	        for (int j = 0, xVal = xVal_base; j < wsize; j++, xVal++) {
//	        	#pragma HLS PIPELINE II=1
//
//	        	        	update_line_buff_7(linebuf, rowAddr, i,mac_buff);
//	        	        	//stream_convo_out_43_0 << mac_0_1(wgt_mac_0,mac_buff);
//	        	        	 {
//	        	        	      sum = sum + linebuf[rowAddr[i]][xVal] * wgt_buff_0[ochan_no][i * wsize + j];
//	        	        	                }
//	        	        	     }
//	        	}
	        	 //std:: cout<<"convo/s111 = "<< sum<< std::endl;
	             //stream_convo7_out_0_0 << sum;
	        	}
		}
		//std:: cout<<yy<< std::endl;
	        	        if((yy*2 + 1) < (227 - 7))
	        	        				   {
	        	        					 for(ap_uint<2> j = 0 ; j < 2 ; j++)
	        	        					 {
	        	        					   for(uint8_t i = 0; i < 227; i++)
	        	        					   {
	        	        	stream_convo7_in >>  linebuf[rowAddr[7+j]][i];
	        	        	//std:: cout<<"padding yy2"<< std::endl;

	        	        					   }
	        	        					 }
	        	        					// std:: cout<<"padding "<< std::endl;
//	        	        					 for(uint8_t i = 0; i < stride; i++){
//	        	        						 {
//	        	        					    for(uint8_t row = 0; row < (wsize+stride); row++)
//	        	        						rowAddr[row] = (rowAddr[row] + 1) % (wsize+stride);
//	        	        				    }
//	        	        				   }

	        	        					 if(rowena == 0){rowAddr[0] = 2 ; rowAddr[1] = 3 ; rowAddr[2] = 4 ;rowAddr[3] = 5 ;rowAddr[4] = 6 ;
	        	        					 rowAddr[5] = 7 ; rowAddr[6] = 8 ; rowAddr[7] = 0 ;rowAddr[8] = 1 ;
	        	        					 rowena = 1;}

	        	        					 else if(rowena == 1){rowAddr[0] = 4 ; rowAddr[1] = 5 ; rowAddr[2] = 6 ;rowAddr[3] = 7 ;rowAddr[4] = 8 ;
	        	        					 rowAddr[5] = 0 ; rowAddr[6] = 1 ; rowAddr[7] = 2 ;rowAddr[8] = 3 ;
	        	        					 rowena = 2;}


	        	        					 else if(rowena == 2){rowAddr[0] = 6 ; rowAddr[1] = 7 ; rowAddr[2] = 8 ;rowAddr[3] = 0 ;rowAddr[4] = 1 ;
	        	        					 rowAddr[5] = 2 ; rowAddr[6] = 3 ; rowAddr[7] = 4 ;rowAddr[8] = 5 ;
	        	        					 rowena = 3;}


	        	        					 else if(rowena == 3){rowAddr[0] = 8 ; rowAddr[1] = 0 ; rowAddr[2] = 1 ;rowAddr[3] = 2 ;rowAddr[4] = 3 ;
	        	        					 rowAddr[5] = 4 ; rowAddr[6] = 5 ; rowAddr[7] = 6 ;rowAddr[8] = 7 ;
	        	        					 rowena = 4;}

	        	        					 else if(rowena == 4){rowAddr[0] = 1 ; rowAddr[1] = 2 ; rowAddr[2] = 3 ;rowAddr[3] = 4 ;rowAddr[4] = 5 ;
	        	        					 rowAddr[5] = 6 ; rowAddr[6] = 7 ; rowAddr[7] = 8 ;rowAddr[8] = 0 ;
	        	        					 rowena = 5;}

	        	        					 else if(rowena == 5){rowAddr[0] = 3 ; rowAddr[1] = 4 ; rowAddr[2] = 5 ;rowAddr[3] = 6 ;rowAddr[4] = 7 ;
	        	        					 rowAddr[5] = 8 ; rowAddr[6] = 0 ; rowAddr[7] = 1 ;rowAddr[8] = 2 ;
	        	        					 rowena = 6;}

	        	        					 else if(rowena == 6){rowAddr[0] = 5 ; rowAddr[1] = 6 ; rowAddr[2] = 7 ;rowAddr[3] = 8 ;rowAddr[4] = 0 ;
	        	        					 rowAddr[5] = 1 ; rowAddr[6] = 2 ; rowAddr[7] = 3 ;rowAddr[8] = 4 ;
	        	        					 rowena = 7;}

	        	        					 else if(rowena == 7){rowAddr[0] = 7 ; rowAddr[1] = 8 ; rowAddr[2] = 0 ;rowAddr[3] = 1 ;rowAddr[4] = 2 ;
	        	        					 rowAddr[5] = 3 ; rowAddr[6] = 4 ; rowAddr[7] = 5 ;rowAddr[8] = 6 ;
	        	        					 rowena = 8;}

	        	        					 else if(rowena == 8){rowAddr[0] = 0 ; rowAddr[1] = 1 ; rowAddr[2] = 2 ;rowAddr[3] = 3 ;rowAddr[4] = 4 ;
	        	        					 rowAddr[5] = 5 ; rowAddr[6] = 6 ; rowAddr[7] = 7 ;rowAddr[8] = 8 ;
	        	        					 rowena = 0;}
	        	        					 //std:: cout<<"padding 2"<< std::endl;

		}
	        	        //std:: cout<<yy<< std::endl;
 }
	//std:: cout<<yy<< std::endl;
 }

void stream_adder_func_s5(
hls::stream<int> &stream_convo7_out_0_0,
hls::stream<int> &stream_convo7_out_0_1,
hls::stream<int> &stream_convo7_out_0_2,
hls::stream<int> &stream_convo7_out_0_3){

int add_0 ;//= 0 ;

//#pragma HLS RESOURCE variable=add_0 core=HAddSub_fulldsp latency=2
//#pragma HLS RESOURCE variable=add_1 core=HAddSub_fulldsp latency=2

for(int yy = 0 ; yy < 111*24*111; yy++)
	{
//	for(uint16_t ochan_no = 0 ; ochan_no < ochan ; ochan_no++)
//	{
//     	for(uint8_t xx = 0 ; xx < osize; xx++)
//     	{

#pragma HLS PIPELINE

int dp_0;
stream_convo7_out_0_0 >> dp_0;
int dp_1;
stream_convo7_out_0_1 >> dp_1;
int dp_2;
stream_convo7_out_0_2 >> dp_2;

add_0 = dp_0 + dp_1 + dp_2;
stream_convo7_out_0_3 << add_0;

}}

void stream_out_7(
hls::stream<int> &stream_convo7_out_0_34,
hls::stream<datatype_inh> &stream_convo_in_0_pool_fused73 ){

	//datatype_inh out_buff[112*112];

	datatype_inh pool_out[111];
	#pragma HLS RESOURCE variable=pool_out core=RAM_1P_LUTRAM
	//#pragma HLS RESOURCE variable=para_out core=XPM_MEMORY uram
	int dp7,sum;

		for (uint16_t i = 0 ; i < 111 ; i++)
			{
			for(uint16_t ochan_no = 0; ochan_no < 24; ochan_no++)
				{
			for (uint8_t j = 0 ; j < 111 ; j++)
				{
			//#pragma HLS LOOP_TRIPCOUNT min=124*124 max=124*124
			#pragma HLS PIPELINE
				//sum = 0;
				stream_convo7_out_0_34 >> dp7;
				sum = dp7 ;//+ bias73[ochan_no];
				if (sum  > 0)
					pool_out[j] = (sum >> 6);
					//stream_convo_in_0_pool_fused73 << (sum >> 6);
				else
					pool_out[j] = 0;
					//stream_convo_in_0_pool_fused73 << 0;
			}

			for (uint8_t ii = 0 ; ii < 111 ; ii++)
				{
				//#pragma HLS LOOP_TRIPCOUNT min=124*124 max=124*124
				//#pragma HLS PIPELINE
					stream_convo_in_0_pool_fused73 << (datatype_inh) pool_out[ii];
				}
			}
	}
	//std::cout <<  "   out = "   <<   std::endl;
}

void stream_out_pool_fused_7(hls::stream<datatype_inh> &stream_convo_in_0_pool_fused70,
		hls::stream<datatype_inh> &stream_convo_in_0_pool_fused7_out0
){
	datatype_inh acc1,acc2,acc3;
	uint8_t rowAddr_pool[5];
	#pragma HLS ARRAY_PARTITION variable=rowAddr_pool complete dim=1
	datatype_inh mac_buff[3 * 3];
	#pragma HLS ARRAY_PARTITION variable=mac_buff complete dim=1

	ap_uint<4> rowena = 0;
	datatype_inh linebuf_pool[24][5][111];
	#pragma HLS ARRAY_PARTITION variable=linebuf_pool complete dim=2
	#pragma HLS RESOURCE variable=linebuf_pool core=RAM_2P_BRAM

//#pragma HLS DEPENDENCE variable=linebuf_pool inter false

	for(ap_uint<2> yy = 0 ; yy < 3; yy++)
		{
		for(uint16_t ochan_no = 0 ; ochan_no < 24 ; ochan_no++)
		{
			for(uint8_t xx = 0 ; xx < 111; xx++)
             {
				datatype_inh dp_0;
				stream_convo_in_0_pool_fused70 >> dp_0;
				linebuf_pool[ochan_no][yy][xx] = dp_0;
             }
		}
		}

for(ap_uint<3> i = 0; i < 5; i++){
	#pragma HLS UNROLL
		rowAddr_pool[i] = i;}
	for(uint8_t yy1 = 0 ; yy1 < 55; yy1++)
		{
	for(uint16_t ochan_no2 = 0 ; ochan_no2 < 24 ; ochan_no2++)
				{
		for(uint8_t xx1 = 0 ; xx1 < 55; xx1++)
									 {
		datatype_inh acc_pool = 0 ;
	    #pragma HLS PIPELINE
		update_line_buff_pool27(linebuf_pool, rowAddr_pool, xx1,mac_buff,ochan_no2);
		acc1 = mac_buff[0] >= mac_buff[1] ? mac_buff[0] >= mac_buff[2] ? mac_buff[0] : mac_buff[2] : mac_buff[1] >= mac_buff[2] ? mac_buff[1] : mac_buff[2] ;
		acc2 = mac_buff[3] >= mac_buff[4] ? mac_buff[3] >= mac_buff[5] ? mac_buff[3] : mac_buff[5] : mac_buff[4] >= mac_buff[5] ? mac_buff[4] : mac_buff[5] ;
		acc3 = mac_buff[6] >= mac_buff[7] ? mac_buff[6] >= mac_buff[8] ? mac_buff[6] : mac_buff[8] : mac_buff[7] >= mac_buff[8] ? mac_buff[7] : mac_buff[8] ;
		acc_pool =  (acc1 >= acc2) ? (acc1 >= acc3 ? acc1 : acc3)  : (acc2 >= acc3 ? acc2 : acc3) ;
		//if(xx < (osize_pool+2) and yy < (osize_pool+2))
		//output[xx1 + ochan_no2*osize_pool*osize_pool + yy1*osize_pool ] = acc_pool;
		stream_convo_in_0_pool_fused7_out0 << acc_pool;
									 }
				}
		if((yy1*2 + 1) < (111 - 3))
					   {
				 for(ap_uint<2> j = 0 ; j < 2 ; j++)
				 {
					 for(uint16_t ochan_no3 = 0 ; ochan_no3 < 24 ; ochan_no3++)
												{
						   for(uint8_t i = 0; i < 111; i++)
						   {
							//#pragma HLS PIPELINE
							   stream_convo_in_0_pool_fused70 >> linebuf_pool[ochan_no3][rowAddr_pool[j+3]][i];
						   }
						   //for(int row = 0; row < wsize; row++)
						   	    //rowAddr[row] = (rowAddr[row] + 1) % (wsize);
						 }
					   }
//						for(uint8_t row = 0; row < (3); row++)
//						rowAddr_pool[row] = (rowAddr_pool[row] + 1) % (3);
//						for(uint8_t row = 0; row < (3); row++)
//						rowAddr_pool[row] = (rowAddr_pool[row] + 1) % (3);
				  if(rowena == 0){rowAddr_pool[0] = 2 ; rowAddr_pool[1] = 3 ; rowAddr_pool[2] = 4 ;rowAddr_pool[3] = 0 ;rowAddr_pool[4] = 1 ;rowena = 1;}
				  else if(rowena == 1){rowAddr_pool[0] = 4 ; rowAddr_pool[1] = 0 ; rowAddr_pool[2] = 1 ;rowAddr_pool[3] = 2 ;rowAddr_pool[4] = 3 ;rowena = 2;}
				  else if(rowena == 2){rowAddr_pool[0] = 1 ; rowAddr_pool[1] = 2 ; rowAddr_pool[2] = 3 ;rowAddr_pool[3] = 4 ;rowAddr_pool[4] = 0 ;rowena = 3;}
				  else if(rowena == 3){rowAddr_pool[0] = 3 ; rowAddr_pool[1] = 4 ; rowAddr_pool[2] = 0 ;rowAddr_pool[3] = 1 ;rowAddr_pool[4] = 2 ;rowena = 4;}
				  else if(rowena == 4){rowAddr_pool[0] = 0 ; rowAddr_pool[1] = 1 ; rowAddr_pool[2] = 2 ;rowAddr_pool[3] = 3 ;rowAddr_pool[4] = 4 ;rowena = 0;}
					   }
	}
}


void call_save_out(datatype_inh out_buff[4][24*55*55],hls::stream<datatype_inh> stream_convo_final_7[4])
{
#pragma HLS DATAFLOW
//#pragma HLS stable variable=out_buff

	x1:
	for(uint8_t yy1 = 0 ; yy1 < 55; yy1++)
	{
	for(uint16_t ochan_no2 = 0 ; ochan_no2 < 24 ; ochan_no2++)
			{
			for(uint8_t xx1 = 0 ; xx1 < 55; xx1++)
				{
				datatype_inh dp;
				stream_convo_final_7[0] >> dp;
				out_buff[0][xx1+ochan_no2*55*55+yy1*55] = dp;
				}
			}
	}
	x2:
	for(uint8_t yy1 = 0 ; yy1 < 55; yy1++)
	{
	for(uint16_t ochan_no2 = 0 ; ochan_no2 < 24 ; ochan_no2++)
			{
			for(uint8_t xx1 = 0 ; xx1 < 55; xx1++)
				{
				datatype_inh dp;
				stream_convo_final_7[1] >> dp;
				out_buff[1][xx1+ochan_no2*55*55+yy1*55] = dp;
				}
			}
	}
	x3:
	for(uint8_t yy1 = 0 ; yy1 < 55; yy1++)
	{
	for(uint16_t ochan_no2 = 0 ; ochan_no2 < 24 ; ochan_no2++)
			{
			for(uint8_t xx1 = 0 ; xx1 < 55; xx1++)
				{
				datatype_inh dp;
				stream_convo_final_7[2] >> dp;
				out_buff[2][xx1+ochan_no2*55*55+yy1*55] = dp;
				}
			}
	}
	x4:
	for(uint8_t yy1 = 0 ; yy1 < 55; yy1++)
	{
	for(uint16_t ochan_no2 = 0 ; ochan_no2 < 24 ; ochan_no2++)
			{
			for(uint8_t xx1 = 0 ; xx1 < 55; xx1++)
				{
				datatype_inh dp;
				stream_convo_final_7[3] >> dp;
				out_buff[3][xx1+ochan_no2*55*55+yy1*55] = dp;
				}
			}
	}


}

void stream_out_final_7(hls::stream<datatype_inh> stream_convo_final_7[4],ap_int<512> *output)
{
datatype_inh out_buff[4][24*55*55];
#pragma HLS ARRAY_PARTITION variable=out_buff complete dim=1
//#pragma HLS RESOURCE variable=linebuf_out17 core=RAM_2P_LUTRAM

call_save_out(out_buff,stream_convo_final_7);


ap_int<512> tmp;
int curr_frame = 0;
int curr_off = 0;
int next_off = 0;
int curr_frame_boundry = 0;
int previous_frame_boundry = 0;
int previous_no_of_bytes = 0;
int curr_no_of_bytes = 0;
int next_no_of_bytes = 0;
int next_state=0;
int total_writes = 0;
int count = 0;
int byte64s= 0;
int offset = 0;
int noofreads = 4*24*55*55*16/512;//9075

while(total_writes < noofreads)
{

for (short k = 0; k < 32; k++) {
tmp(16 * (k + 1) - 1, 16 * k) = out_buff[curr_frame][k + count*32 + offset];
}
count = count + 1;
output[total_writes] = tmp;
total_writes = total_writes + 1;

previous_no_of_bytes = (curr_frame+1)*24*55*55 -(total_writes)*32;
if(previous_no_of_bytes <= 32)
{
next_no_of_bytes = 32 - previous_no_of_bytes;
for (short k = 0; k < previous_no_of_bytes; k++) {
tmp(16 * (k + 1) - 1, 16 * k) = out_buff[curr_frame][24*55*55-previous_no_of_bytes + k];
}
curr_frame = curr_frame + 1;
for (short k = 0; k < next_no_of_bytes; k++) {
tmp(16 * (k + 1 + previous_no_of_bytes) - 1, 16 * (k + previous_no_of_bytes)) = out_buff[curr_frame][k];
}

output[total_writes] = tmp;
total_writes = total_writes + 1;
offset = next_no_of_bytes;
previous_no_of_bytes = 0;
next_state = 0;
count = 0;
	}
}
}


//void call_save_out(datatype_inh linebuf_out[4][24*55*55],hls::stream<datatype_inh> stream_convo_final_7[4])
//{
//#pragma HLS DATAFLOW
//#pragma HLS stable variable=linebuf_out
//
//	x1:
//	for(uint8_t yy1 = 0 ; yy1 < 55; yy1++)
//	{
//	for(uint16_t ochan_no2 = 0 ; ochan_no2 < 24 ; ochan_no2++)
//			{
//			for(uint8_t xx1 = 0 ; xx1 < 55; xx1++)
//				{
//				datatype_inh dp;
//				stream_convo_final_7[0] >> dp;
//				linebuf_out[0][xx1+ochan_no2*55*55+yy1*55] = dp;
//				}
//			}
//	}
//	x2:
//	for(uint8_t yy1 = 0 ; yy1 < 55; yy1++)
//	{
//	for(uint16_t ochan_no2 = 0 ; ochan_no2 < 24 ; ochan_no2++)
//			{
//			for(uint8_t xx1 = 0 ; xx1 < 55; xx1++)
//				{
//				datatype_inh dp;
//				stream_convo_final_7[1] >> dp;
//				linebuf_out[1][xx1+ochan_no2*55*55+yy1*55] = dp;
//				}
//			}
//	}
//	x3:
//	for(uint8_t yy1 = 0 ; yy1 < 55; yy1++)
//	{
//	for(uint16_t ochan_no2 = 0 ; ochan_no2 < 24 ; ochan_no2++)
//			{
//			for(uint8_t xx1 = 0 ; xx1 < 55; xx1++)
//				{
//				datatype_inh dp;
//				stream_convo_final_7[2] >> dp;
//				linebuf_out[2][xx1+ochan_no2*55*55+yy1*55] = dp;
//				}
//			}
//	}
//	x4:
//	for(uint8_t yy1 = 0 ; yy1 < 55; yy1++)
//	{
//	for(uint16_t ochan_no2 = 0 ; ochan_no2 < 24 ; ochan_no2++)
//			{
//			for(uint8_t xx1 = 0 ; xx1 < 55; xx1++)
//				{
//				datatype_inh dp;
//				stream_convo_final_7[3] >> dp;
//				linebuf_out[3][xx1+ochan_no2*55*55+yy1*55] = dp;
//				}
//			}
//	}
//
//
//}
//
//
//void stream_out_final_7(hls::stream<datatype_inh> stream_convo_final_7[4],ap_int<512> *output)
//{
//datatype_inh linebuf_out[4][24*55*55];
//#pragma HLS ARRAY_PARTITION variable=linebuf_out complete dim=1
////#pragma HLS RESOURCE variable=linebuf_out17 core=RAM_2P_LUTRAM
//call_save_out(linebuf_out,stream_convo_final_7);
//datatype_inh out_buff[96*55*55];
//for (uint8_t ai = 0 ; ai < 4 ; ai++)
//{
//	for (int i = 0 ; i < 24*55*55 ; i++)
//	{
//		out_buff[ai*24*55*55 + i] = linebuf_out[ai][i];
//
//	}
//}
//for (int i = 0 ; i < 9075 ; i++)
//	{
//		ap_int<512> tmp;
//		for (short k = 0; k < 32; k++) {
//        	tmp(16 * (k + 1) - 1, 16 * k) = out_buff[k + i*32];}
//        output[i] = tmp;
//	}
//}



void convo_hw(ap_int<512>  *input,ap_int<512>  *output,ap_int<512> *weights)
{

	hls::stream<datatype_inh> stream_convo_7_in[12];//("inp_stream");
	#pragma HLS STREAM variable=stream_convo_7_in depth=4
	hls::stream<int> stream_convo7_out[12];//("out_stream");
	#pragma HLS STREAM variable=stream_convo7_out depth=4
	hls::stream<datatype_inh> stream_convo7_wgt_0[12];//("wgt_stream");
	#pragma HLS STREAM variable=stream_convo7_wgt_0 depth=4
	hls::stream<int> stream_convo7_adder_0[4];//("adder_stream");
	#pragma HLS STREAM variable=stream_convo7_adder_0 depth=4
	hls::stream<datatype_inh> stream_convo7_bias_0[4];//("adder_stream");
	#pragma HLS STREAM variable=stream_convo7_bias_0 depth=4
	hls::stream<datatype_inh> stream_convo7_pool_0[4];//("adder_stream");
	#pragma HLS STREAM variable=stream_convo7_pool_0 depth=4



#pragma HLS dataflow


//	stream_input(stream_convo_7_in,input);
//	stream_out_final(stream_convo_7_in,output);


	//std:: cout<<" 111 "<< std::endl;
	stream_input_7(stream_convo_7_in,input);
	//std:: cout<<" 222 "<< std::endl;
	stream_weight_w7(stream_convo7_wgt_0,weights);
	//std:: cout<<" 333 "<< std::endl;stream_convo7_in
    for(uint8_t xx = 0 ; xx < 12; xx++)
	    {
		 #pragma HLS UNROLL
		 convo_7(stream_convo_7_in[xx],stream_convo7_wgt_0[xx],stream_convo7_out[xx]);
		 }
    //std:: cout<<" 444 "<< std::endl;
    for(uint8_t xx = 0 ; xx < 4; xx++)
	    {
		#pragma HLS UNROLL
		 stream_adder_func_s5(stream_convo7_out[xx*3],stream_convo7_out[xx*3+1],stream_convo7_out[xx*3+2],stream_convo7_adder_0[xx]);
	     stream_out_7(stream_convo7_adder_0[xx],stream_convo7_bias_0[xx] );
	     stream_out_pool_fused_7(stream_convo7_bias_0[xx],stream_convo7_pool_0[xx]);
	    }
   //std:: cout<<" 555 "<< std::endl;
   stream_out_final_7(stream_convo7_pool_0,output);

}


extern "C"{
	void cnn(
			ap_int<512> *output_5,         // Read-Only Image
			ap_int<512> *weights,       // Read-Only Weight Matrix
			ap_int<512> *output_6        // Output Filters/Images
	)
{
#pragma HLS INTERFACE m_axi port=output_5 offset=slave depth=512*224*224 bundle=gmem1
#pragma HLS INTERFACE m_axi port=weights offset=slave depth=1248424*2 bundle=gmem0
#pragma HLS INTERFACE m_axi port=output_6 offset=slave depth=512*224*224 bundle=gmem2
//#pragma HLS INTERFACE m_axi port=para1 offset=slave bundle=gmem3
#pragma HLS INTERFACE s_axilite port=output_5 bundle=control
#pragma HLS INTERFACE s_axilite port=weights  bundle=control
#pragma HLS INTERFACE s_axilite port=output_6 bundle=control
//#pragma HLS INTERFACE s_axilite port=para1 bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control
//#pragma HLS allocation instances=cnn1 limit=1 function
convo_hw(output_5,output_6,weights);
}
}

