
#include <stdio.h>
#include "stdint.h"
#include <stdlib.h>
//#include "ap_int.h"
//#include <ap_utils.h>
typedef float  datatype_inh;
//#include"hls_math.h"
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <ctime>
//#include <ratio>
//#include <chrono>
//#include "fixed.h"
using namespace std;
//using namespace numeric;
//typedef Fixed<8,8>  datatype_inh;

#include <stdio.h>
#include "stdint.h"
#include <stdlib.h>
#include <hls_half.h>
#include "ap_fixed.h"

//typedef int8_t datatype_wgt;
//typedef ap_fixed<24,16> datatype_argu;
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <ctime>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <unistd.h>
#include <chrono>
//OpenCL utility layer include
#include <stdio.h>
#include "stdint.h"
//typedef short datatype_inh;
#include <stdlib.h>
//#include "ap_fixed.h"
//typedef ap_fixed<8,8> datatype_inh;
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
//#include <ratio>
//#include <chrono>
//#include "layer_pool_convo.h"
#include <fcntl.h>
#include <string.h>
#include <cstdlib>
//#include <ratio>
//#include <chrono>

#include <iostream>
#include <fstream>
//using namespace std;
#include <limits>
#include <string>
#include <CL/cl_ext.h>
//#define uint16_t int
//#define uint8_t int

#include <x86intrin.h>
#include <immintrin.h>
#include <cstdint>
//typedef int8_t  datatype_wgt;


void aver_pool_2(
	datatype_inh *in_vector,
	datatype_inh *out_vector,
    int i_chan,
    int o_chan,
    int i_size,
    int o_size
	) {

//	assert(i_chan==o_chan); // assert the input channel is equal to the output channel
	//for (int i = 0; i < i_chan * o_size * o_size; i++)
		//out_vector[i] = -INFINITY;

	for (int c = 0; c < o_chan; ++c) {
	datatype_inh aver = 0;
		for (int ph = 0; ph < i_size; ph++) {
		  for (int pw = 0; pw < i_size; pw++) {

		        aver += in_vector[c * i_size * i_size + i_size * ph + pw];
			//printf("The prediction is %f\n", aver);

		      }

		    }
		       out_vector[c] = aver/(i_size*i_size);
                     //  printf("The prediction is %f\n", out_vector[c]);
		       //out_vector[c] = aver;

		  }
}
void convGolden(
	datatype_inh *weight,
	datatype_inh *bias,
	datatype_inh *mean,
	datatype_inh *vari,
	datatype_inh *gamma,
	datatype_inh *beta,
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
//	static int maxcount = 0;
//	//maxcount = o_chan*i_size*i_size;
//	if(maxcount < o_chan*i_size*i_size)
//		maxcount = o_chan*i_size*i_size;
//	//std::cout << "result " << maxcount << std::endl;

//int scheduler_fac_ichan;
//int scheduler_fac_ochan;
//if(i_chan%64 != 0)
//	//std::cout << "i_chan " << i_chan << std::endl;
//if(o_chan%8 != 0)
//	//std::cout << "o_chan " << o_chan << std::endl;
//
////	if(layer_no == 1)
////	{
////	ichan111= 96;ochan111 = 16;isize111 = 55;osize111 = 55;wsize111 = 1;
////	out_offset111 = 0;wgt_offset111 = 14208;bias_offset111 = 15744; pool_on = 0;osize_pool = 0;pool_offset=0;
////	////ddr_1 = input;
////	////ddr_2 = output;
////	}
//static int layer_no = 0;
//static int wgt_offset = 0;
//static int bias_offset = 0;
//int pool_on = 0;
//int osize_pool = 0;
//if(stride == 2){
//	pool_on = 1;
//	osize_pool = i_size/2;
//}
//
//bias_offset = bias_offset + o_chan * i_chan * w_size * w_size;
//
//////std::cout << "else if(layer_no == " << layer_no << "){" <<  std::endl;
//cout << "i_chan = " << i_chan << ";"
//		<< "o_chan = " << o_chan << ";"
//		<< "i_size = " << i_size << ";"
//		<< "o_size = " << o_size << ";"
//		<< "w_size = " << w_size << ";"
//		//<< "wgt_offset111 = " << wgt_offset << ";"
//		//<< "bias_offset111 = " << bias_offset << ";"
//		//<< "pool_on = " << pool_on << ";"
//		//<< "osize_pool = " << osize_pool << ";"
//		<< endl;
 //<< //std::cout << "}" <<  endl;
//
//layer_no = layer_no + 1;
//wgt_offset = bias_offset + o_chan;


	//////////////////////// find scale /////////////////
//		   int n = o_chan * i_chan * w_size * w_size;
//		   float w_min = *min_element(weight, weight + n);
//		   float w_max = *max_element(weight, weight + n);
//
//		    w_min = min(w_min, 0.f);
//		    w_max = max(w_max, 0.f);
//		    int quant_w_min = 1;
//		    int quant_w_max = 128;
//		    float threshold = max(abs(w_max),abs(w_min));
//		    for (int j = 0; j < o_chan * i_chan * w_size * w_size; j++)
//			{
//		    	if(weight[j] < -threshold)
//			    	weight[j] = -threshold;
//			else if(weight[j] > threshold)
//				weight[j] = threshold;
//			}
//
//		    static int layer_no = 0;
//		   float scale = threshold / (quant_w_max - quant_w_min);
//		   std::cout << "scale[" <<  layer_no << "] = " << scale << ";" << std::endl;

////////////////////////////////////////////////



static int layer_no = 0;
float scale[55] ;
scale[0] = 0.00554586;
scale[1] = 0.0070895;
scale[2] = 0.00564957;
scale[3] = 0.00307118;
scale[4] = 0.00312946;
scale[5] = 0.00233746;
scale[6] = 0.0025062;
scale[7] = 0.00220135;
scale[8] = 0.00207646;
scale[9] = 0.00171617;
scale[10] = 0.00275578;
scale[11] = 0.00505883;
scale[12] = 0.00262941;
scale[13] = 0.00302121;
scale[14] = 0.00342009;
scale[15] = 0.00153309;
scale[16] = 0.00139542;
scale[17] = 0.00271069;
scale[18] = 0.00290161;
scale[19] = 0.00294209;
scale[20] = 0.00226418;
scale[21] = 0.0027265;
scale[22] = 0.00214339;
scale[23] = 0.00221126;
scale[24] = 0.00331294;
scale[25] = 0.00268346;
scale[26] = 0.00210468;
scale[27] = 0.00302513;
scale[28] = 0.00185772;
scale[29] = 0.00343534;
scale[30] = 0.00344578;
scale[31] = 0.0030465;
scale[32] = 0.00202826;
scale[33] = 0.00228145;
scale[34] = 0.00232602;
scale[35] = 0.00158614;
scale[36] = 0.00188548;
scale[37] = 0.00241028;
scale[38] = 0.00175662;
scale[39] = 0.00208633;
scale[40] = 0.00259603;
scale[41] = 0.00230477;
scale[42] = 0.00231139;
scale[43] = 0.00489871;
scale[44] = 0.00260615;
scale[45] = 0.0021378;
scale[46] = 0.00339973;
scale[47] = 0.00454073;
scale[48] = 0.00223514;
scale[49] = 0.00217898;
scale[50] = 0.00405088;
scale[51] = 0.00113195;
scale[52] = 0.00236194;


//		    for (int j = 0; j < o_chan * i_chan * w_size * w_size; j++)
//			{
//			    weight[j] = weight[j]/scale[layer_no];
//			}


		   datatype_inh sca_wgt;

	datatype_inh sca_bias = 0;
	datatype_inh wgt_g = 0;
    // Runs over output filters
    for(int output = 0; output < o_chan; output++){

    	sca_bias = gamma[output]*(bias[output] - mean[output])/sqrt(vari[output] +  0.00012) + beta[output];
    	wgt_g = gamma[output]/sqrt(vari[output] +  0.00012);// sqrt(pow(vari[output],2)
    	//std::cout << "sca_bias[" <<  sca_bias << std::endl;
    	//std::cout << "wgt_g[" <<  wgt_g << std::endl;

        // Runs over output pixel in Y-direction//
        for(int y = 0; y < o_size; y++){
            // Runs over output pixel in X-direction
            for(int x = 0; x < o_size; x++){
            	datatype_inh acc = 0;
            	datatype_inh bias_sum = 0;

          //      long acc = 0;
          //      long bias_sum = 0;

                // Runs over each input channel of input feature map
                for(int input = 0; input < i_chan; input++){
                    // Runs over filter window
                    for(int i = 0; i < w_size; i++){
                        // Runs over filter windows
                        for(int j = 0; j < w_size; j++){

                            // Calculate input padding boundaries
                            int xVal = x*stride + j-padding, yVal = y*stride + i-padding;
                            datatype_inh sca_wgt = (weight[((output*i_chan + input)*w_size + i)*w_size + j])* wgt_g;

//                            if(weight[((output*i_chan + input)*w_size + i)*w_size + j] != 0)
//                            {
//                            sca_wgt = (weight[((output*i_chan + input)*w_size + i)*w_size + j])/wgt_g;
//                            sca_wgt = (round(sca_wgt));
//                            }
//                            else
//                            	sca_wgt = 0 ;

                            // Convolution operation
                            if(yVal >= 0 && yVal < i_size && xVal >= 0 && xVal < i_size){
                                acc += (datatype_inh) image[(input*i_size + yVal)*i_size + xVal] *// (weight[((output*i_chan + input)*w_size + i)*w_size + j]);
                                       (datatype_inh) (sca_wgt);
                            }
                        }

                    }
                }

                //acc = acc/wgt_g;
                ////std::cout << output <<  std::endl;
                //bias_sum = (acc*scale  + sca_bias/scale);//bias[output]);//
                //std::cout << bias_sum <<  std::endl;

                //bias_sum = (acc*scale[layer_no]);//  + sca_bias/scale[layer_no]);//bias[output]);//

                bias_sum = acc + sca_bias;


			if(bias_sum < 0 && relu_on == 1)
                //std:://std::cout << "result " << acc << std::std::endl;
		         out[(output*o_size + y)*o_size + x] = 0;
			else if(relu_on == 0)
				out[(output*o_size + y)*o_size + x] = (datatype_inh) (bias_sum);
			else
		         out[(output*o_size + y)*o_size + x] = (datatype_inh) (( bias_sum));

			////std::cout << "result = " << out[(output*o_size + y)*o_size + x] << std::endl;

			datatype_inh data =  out[(output*o_size + y)*o_size + x];
//			if(max<data)
//				max = data;
//			if((min>data) && (min>0) && (data>0))
//				min=data;

            }
            ////std::cout << "vg "<<  std::endl;
        }

    }
    ////std::cout << "max=" << max << std::endl;
    ////std::cout << "min=" << min << std::endl;

	   layer_no = layer_no + 1;
}


//
//
//
//
//
//    int  j;
//    datatype_inh data;
//    float dd;
////        char str[300];
//    static int layer_no_2 = 0;
//    datatype_inh max=0;
//    datatype_inh min=60000;
//    datatype_inh avg = 0;
//   datatype_inh sum = 0;
//for (j = 0; j < o_chan * o_size * o_size; j++)
//{
//
//	data = out[j];
//	if(max<data)
//		max = data;
//	if((min>data) && (min>0) && (data>0))
//		min=data;
//    sum = sum + data;
//}
//avg = sum/(o_chan * o_size * o_size);
////std::cout <<   "avg = " << avg << std::endl;
////std::cout <<   "max = " << max << std::endl;
////std::cout <<   "min = " << min << std::endl;
//layer_no_2 = layer_no_2 + 1;

//}
//
//void convGolden0(
//	datatype_inh *weight,
//	datatype_inh *bias,
//	datatype_inh *image,
//	datatype_inh *out,
//    int i_chan,
//    int o_chan,
//    int i_size,
//    int o_size,
//    int w_size,
//    int stride,
//    int padding,
//    int relu_on
//)
//{
//    // Runs over output filters
//    for(int output = 0; output < o_chan; output++){
//        // Runs over output pixel in Y-direction
//        for(int y = 0; y < o_size; y++){
//            // Runs over output pixel in X-direction
//            for(int x = 0; x < o_size; x++){
//            	datatype_int acc = 0;
//            	datatype_int bias_sum = 0;
//          //      long acc = 0;
//          //      long bias_sum = 0;
//
//                // Runs over each input channel of input feature map
//                for(int input = 0; input < i_chan; input++){
//                    // Runs over filter window
//                    for(int i = 0; i < w_size; i++){
//                        // Runs over filter windows
//                        for(int j = 0; j < w_size; j++){
//
//                            // Calculate input padding boundaries
//                            int xVal = x*stride + j-padding, yVal = y*stride + i-padding;
//
//                            // Convolution operation
//                            if(yVal >= 0 && yVal < i_size && xVal >= 0 && xVal < i_size){
//                                acc += (datatype_inh) image[(input*i_size + yVal)*i_size + xVal] *
//                                       (datatype_inh) (weight[((output*i_chan + input)*w_size + i)*w_size + j] );
//                            }
//                        }
//
//                    }
//		}
//
//                bias_sum = (acc + bias[output]);
//
//			if(bias_sum < 0 && relu_on == 1)
//                //std:://std::cout << "result " << acc << std::std::endl;
//		         out[(output*o_size + y)*o_size + x] = 0;
//
//			else
//		         out[(output*o_size + y)*o_size + x] = (datatype_inh) (( bias_sum));
//            }
//        }
//    }
//}

void max_pool(
	datatype_inh *in_vector,
	datatype_inh *out_vector,
    int i_chan,
    int o_chan,
    int i_size,
    int o_size,
    int w_size,
    int stride,
    int padding,// padding
    int relu_on

) {

//	assert(i_chan==o_chan); // assert the input channel is equal to the output channel
	for (int i = 0; i < i_chan * o_size * o_size; i++)
		out_vector[i] = -INFINITY;

	for (int c = 0; c < i_chan; ++c) {
		for (int ph = 0; ph < o_size; ph++) {
		  for (int pw = 0; pw < o_size; pw++) {

		   int hstart = ph * stride - padding;
                   int wstart = pw * stride - padding;
	           int hend = fmin(hstart + w_size, i_size);
		   int wend = fmin(wstart + w_size, i_size);
		   hstart = fmax(0, ph * stride - padding);
		   wstart = fmax(0, pw * stride - padding);


		    const int pool_index = ph * o_size + pw;
		    for (int h = hstart; h < hend; h++) {
		      for (int w = wstart; w < wend; ++w) {
		        const int index = h * i_size + w;
		        if (in_vector[c * i_size * i_size + index] > out_vector[c * o_size * o_size + pool_index])
		        {
		          out_vector[c * o_size * o_size + pool_index] = in_vector[c * i_size * i_size + index];
		        }
		      }
		    }
		  }
		}
	}

}
//static float count = 0;
//static float count2 = 0;
//static float noofochan = 0;

void load_weights_0(
	datatype_inh *weights,
	datatype_inh *bias,
	datatype_inh *mean,
	datatype_inh *vari,
	datatype_inh *gamma,
	datatype_inh *beta,
	int i_chan,
	int o_chan,
	int w_size,
	FILE *fid)
{
        assert( fid != NULL );
        int  j;
        float data;
        char str[300];
        //static int64_t count = 0;

	for (j = 0; j < o_chan * i_chan * w_size * w_size; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  ////std::cout <<   weights[j] << std::endl;
	  weights[j] =  (datatype_inh) (data);
	  ////std::cout <<   weights[j] << std::endl;
	  fscanf(fid,"\n");
	  //count = count +  1;
	}

	//noofochan = noofochan + o_chan;

	for (j = 0; j < o_chan; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  bias[j] =  (datatype_inh) (data);
	  fscanf(fid,"\n");
	  //count = count +  1;
	}


	for (j = 0; j < o_chan; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  mean[j] =  (datatype_inh) (data);
	  fscanf(fid,"\n");
	  //count = count +  1;
	}

	for (j = 0; j < o_chan; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  vari[j] =  (datatype_inh) (data);
	  fscanf(fid,"\n");
	  //count = count +  1;
	}

	  fscanf(fid,"%s", str);
	  datatype_inh blob_2 = atof(str);
	  fscanf(fid,"\n");
	 // count = count +  1;
//	  //std::cout <<   str << std::endl;
//	  //std::cout <<   blob_2 << std::endl;


//		for (j = 0; j < o_chan; j++)
//		{
//			mean[j] = mean[j]/blob_2;
//			vari[j] = vari[j]/blob_2;
//		}

	for (j = 0; j < o_chan; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  gamma[j] =  (datatype_inh) (data);
	  fscanf(fid,"\n");
	  //count = count +  1;
	}


	for (j = 0; j < o_chan; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  beta[j] =  (datatype_inh) (data);
	  fscanf(fid,"\n");
	 //count = count +  1;
	}
	////std::cout <<   count+count2 << std::endl;

}

void load_weights_fc(
	datatype_inh *weights,
	datatype_inh *bias,
	int i_chan,
	    	    int o_chan,
	    	    int w_size,
				FILE *fid)
{
        assert( fid != NULL );
        int  j;
        float data;
        char str[300];
        //static int64_t count = 0;

        //noofochan = noofochan + o_chan;


 //////////////       scale = 0.00579653;

	for (j = 0; j < o_chan * i_chan * w_size * w_size; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  ////std::cout <<   weights[j] << std::endl;
	  weights[j] =  (datatype_inh) (data);
	  ////std::cout <<   weights[j] << std::endl;
	  fscanf(fid,"\n");
	  //count = count +  1;
	}


	for (j = 0; j < o_chan; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  bias[j] =  (datatype_inh) (data);
	  fscanf(fid,"\n");
	  //count = count +  1;
	}

	////std::cout <<   count+count2 << std::endl;

}

void load_weights(
	datatype_inh *weights,
	datatype_inh *bias,
	datatype_inh *mean,
	datatype_inh *vari,
	datatype_inh *gamma,
	datatype_inh *beta,
	int i_chan,
	    	    int o_chan,
	    	    int w_size,
				FILE *fid)
{
        assert( fid != NULL );
        int  j;
        float data;
        char str[300];


        //noofochan = noofochan + o_chan;


	for (j = 0; j < o_chan * i_chan * w_size * w_size; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  ////std::cout <<   weights[j] << std::endl;
	  weights[j] =  (datatype_inh) (data);
	  ////std::cout <<   weights[j] << std::endl;
	  fscanf(fid,"\n");
	  //count2 = count2 +  1;
	}



	for (j = 0; j < o_chan; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  mean[j] =  (datatype_inh) (data);
	  fscanf(fid,"\n");
	  //count = count +  1;
	}

	for (j = 0; j < o_chan; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  vari[j] =  (datatype_inh) (data);
	  fscanf(fid,"\n");
	  //count = count +  1;
	}

	  fscanf(fid,"%s", str);
	  datatype_inh blob_2 = atof(str);
	  fscanf(fid,"\n");
	 //count = count +  1;
//	  //std::cout <<   str << std::endl;
//
//	  //std::cout <<   blob_2 << std::endl;
//
//
//		for (j = 0; j < o_chan; j++)
//		{
//			mean[j] = mean[j]/blob_2;
//			vari[j] = vari[j]/blob_2;
//		}


	for (j = 0; j < o_chan; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  gamma[j] =  (datatype_inh) (data);
	  fscanf(fid,"\n");
	  //count = count +  1;
	}


	for (j = 0; j < o_chan; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  beta[j] =  (datatype_inh) (data);
	  fscanf(fid,"\n");
	  //count = count +  1;
	}

	for (j = 0; j < o_chan; j++)
	{
	  //fscanf(fid,"%s", str);
	  //data = atof(str);
	  bias[j] =  0;//(datatype_inh) (data);
	  //fscanf(fid,"\n");
	  //count = count +  1;
	}



	////std::cout <<   count2+count << std::endl;


}
void fc(
datatype_inh *bias,
datatype_inh *image,
datatype_inh *weight, // assume: weight[o_chan][i_chan]
datatype_inh *output,
int i_chan,
int i_size,
int fc_chan,
int relu_on
 ) {

//	   int n = fc_chan * i_chan * i_size * i_size;
//	   float w_min = *min_element(weight, weight + n);
//	   float w_max = *max_element(weight, weight + n);
//
//	    w_min = min(w_min, 0.f);
//	    w_max = max(w_max, 0.f);
//	    int quant_w_min = 1;
//	    int quant_w_max = 128;
//	    float threshold = max(abs(w_max),abs(w_min));
//	    for (int j = 0; j < fc_chan * i_chan * i_size * i_size; j++)
//		{
//	    	if(weight[j] < -threshold)
//		    	weight[j] = -threshold;
//		else if(weight[j] > threshold)
//			weight[j] = threshold;
//		}
//
	    float  xx;
//	   float scale = threshold / (quant_w_max - quant_w_min);
//	   std::cout << "scale = " << scale << std::endl;

	for (int i = 0; i < fc_chan; i++) {
//	datatype_inh	bias_sum = 0;
      datatype_inh bias_sum = 0;

      datatype_inh sum = 0;

		for (int j = 0; j < i_chan * i_size * i_size; ++j)
		{
			//if((weight[i * i_chan * i_size * i_size + j]) != 0)
			//{
			   xx = (weight[i * i_chan * i_size * i_size + j]);///0.00579653;
			//}
			//else
				//xx = 0;
			bias_sum += image[j] * xx;
			//bias_sum += image[j] * (weight[i * i_chan * i_size * i_size + j]);
		}
sum =(bias_sum);//*0.00579653);// + bias[i]/0.00579653);
if(sum < 0)
output[i] = 0;
else
output[i] = (datatype_inh)  (sum);

////std::cout <<   output[i] << std::endl;
	}

}



void addeltwise(
datatype_inh *image,
datatype_inh *input,
datatype_inh *output,
int i_chan,
int i_size

 ) {
	for (int i = 0; i < i_chan; ++i) {

		for (int j = 0; j < i_size * i_size; j++) {
			 datatype_inh sum = 0;
			 sum = image[j + i * i_size * i_size] + input[j + i * i_size * i_size];
			 if(sum > 0)
			 output[j + i * i_size * i_size] = sum;
			 else
			 output[j + i * i_size * i_size] = 0;


	}

}
}



void write_layers(
	datatype_inh *write_out,
	int i_chan,
	int i_size,
	FILE *fpoint)
{
        assert( fpoint != NULL );
        int  j;
        datatype_inh data;
        float dd;
//        char str[300];
        static int layer_no = 0;
        int max=0;
        int min=6000;
        long int avg = 0;
        long int sum = 0;
	for (j = 0; j < i_chan * i_size * i_size; j++)
	{

		data = write_out[j];
		if(max<data)
			max = data;
		if((min>data) && (min>0) && (data>0))
			min=data;
		////std::cout <<   data << std::endl;
		//std::string str = std::to_string(data);
		////std::cout <<   write_out[j] << std::endl;
		//dd = (int) data;
		//fprintf(fpoint,"%d", dd);
	    fprintf(fpoint,"\n");
	    sum = sum + data;
	}
//	avg = sum/(i_chan * i_size * i_size);
//	//std::cout <<   "avg = " << avg << std::endl;
//	//fprintf(fpoint,"%s", "layer_no: ");
//	//fprintf(fpoint,"%d", layer_no);
//	//fprintf(fpoint,"\n");
//	//std::cout <<   "max = " << max << std::endl;
//	//std::cout <<   "min = " << min << std::endl;
//	layer_no = layer_no + 1;
}


int main()

{

    datatype_inh weights[4096 * 512 * 10  * 10];
    datatype_inh bias[2048];
    datatype_inh mean[2048];
    datatype_inh vari[2048];
    datatype_inh gamma[2048];
    datatype_inh beta[2048];
    datatype_inh blob_2;
    datatype_inh output_1[512 * 448 * 448];// 512*56*56 //int8
    datatype_inh output_2[512 * 448 * 448];
    datatype_inh output_3[512 * 448 * 448];
    datatype_inh branch_1[512 * 448 * 448];

	int prediction=0;

    int jj;
 	float datai;
 	char stri[2048];


 	//FILE *fpoint1;
 	//const char *out_dump = argv[4];
 	//fpoint1 = fopen("out_dump", "w+");

	FILE *fidi = fopen("py_image.txt", "r");/// 497 church 224*224*3
	// 312 with both mean and unmean image
	for (jj = 0; jj < 3 * 224  * 224; jj++) {
	  fscanf(fidi,"%s", stri);
	  datai = atof(stri);
	  output_1[jj] = (datatype_inh) datai;
      //printf("%f\t",output_1[jj]);
	  fscanf(fidi,"\n");
	}
    fclose(fidi);
    //printf("%d\t",output_1[100]);
    int jp;
//	for (jp = 0; jp < 2048; jp++) {
//		bias[jp] =  0;
//	}

    FILE *fid = fopen("original_linear_weights_2.txt", "r");/// 25610269 total weights
    //FILE *fid = fopen("linear_weights.txt", "r");/// 25610269 total weights 25610216 ext
    //using namespace std::chrono;
    //high_resolution_clock::time_point t1 = high_resolution_clock::now();

    load_weights_0(weights,bias,mean,vari,gamma,beta,3,64,7,fid);
    //load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,3,64,224,112,7,2,3,1);
    cout<<"c1"<<endl;


    max_pool(output_2,branch_1,64,64,112,56,3,2,0,0);
    cout<<"pool1"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,64,256,1,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,64,256,56,56,1,1,0,0);

    cout<<"res2a_branch1"<<endl;


    load_weights(weights,bias,mean,vari,gamma,beta,64,64,1,fid);
    //load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_1,64,64,56,56,1,1,0,1);
    cout<<"res2a_branch2a"<<endl;


    load_weights(weights,bias,mean,vari,gamma,beta,64,64,3,fid);
    //load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,branch_1,64,64,56,56,3,1,1,1);
    cout<<"res2a_branch2b"<<endl;


    load_weights(weights,bias,mean,vari,gamma,beta,64,256,1,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_1,64,256,56,56,1,1,0,0);
    cout<<"res2a_branch2c"<<endl;


    addeltwise(output_1,output_2,branch_1,256,56);
    cout<<"res2a"<<endl;


    load_weights(weights,bias,mean,vari,gamma,beta,256,64,1,fid);
    //load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,256,64,56,56,1,1,0,1);
    cout<<"res2b_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,64,64,3,fid);
    //load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,output_1,64,64,56,56,3,1,1,1);
    cout<<"res2b_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,64,256,1,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,64,256,56,56,1,1,0,0);
    cout<<"res2b_branch2c"<<endl;

    addeltwise(branch_1,output_2,output_1,256,56);
    cout<<"res2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,64,1,fid);
    //load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,256,64,56,56,1,1,0,1);
    cout<<"res2c_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,64,64,3,fid);
    //load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,branch_1,64,64,56,56,3,1,1,1);
    cout<<"res2c_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,64,256,1,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,64,256,56,56,1,1,0,0);
    cout<<"res2c_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,256,56);
    cout<<"res2c"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,512,1,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,256,512,56,28,1,2,0,0);
    cout<<"res3a_branch1"<<endl;


    load_weights(weights,bias,mean,vari,gamma,beta,256,128,1,fid);
    //load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_1,256,128,56,28,1,2,0,1);
    cout<<"res3a_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,128,128,3,fid);
    //load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_3,128,128,28,28,3,1,1,1);
    cout<<"res3a_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,128,512,1,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_3,output_1,128,512,28,28,1,1,0,0);
    cout<<"res3a_branch2c"<<endl;


    addeltwise(output_1,output_2,branch_1,512,28);
    cout<<"res3a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,512,128,1,fid);
    //load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,512,128,28,28,1,1,0,1);
    cout<<"res3b_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,128,128,3,fid);
    //load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,output_1,128,128,28,28,3,1,1,1);
    cout<<"res3b_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,128,512,1,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,128,512,28,28,1,1,0,0);
    cout<<"res3b_branch2c"<<endl;

    addeltwise(branch_1,output_2,output_1,512,28);
    cout<<"res3b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,512,128,1,fid);
    //load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,512,128,28,28,1,1,0,1);
    cout<<"res3c_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,128,128,3,fid);
    //load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,branch_1,128,128,28,28,3,1,1,1);
    cout<<"res3c_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,128,512,1,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,128,512,28,28,1,1,0,0);
    cout<<"res3c_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,512,28);
    cout<<"res3c"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,512,128,1,fid);
    //load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_1,512,128,28,28,1,1,0,1);
    cout<<"res3d_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,128,128,3,fid);
    //load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,128,128,28,28,3,1,1,1);
    cout<<"res3d_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,128,512,1,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,output_1,128,512,28,28,1,1,0,0);
    cout<<"res3d_branch2c"<<endl;


    addeltwise(branch_1,output_1,output_2,512,28);
    cout<<"res3d"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,512,1024,1,fid);
    //load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,branch_1,512,1024,28,14,1,2,0,0);
    cout<<"res4a_branch1"<<endl;


    load_weights(weights,bias,mean,vari,gamma,beta,512,256,1,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,output_1,512,256,28,14,1,2,0,1);
    cout<<"res4a_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,256,3,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_3,256,256,14,14,3,1,1,1);
    cout<<"res4a_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,1024,1,fid);
    //load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_3,output_1,256,1024,14,14,1,1,0,0);
    cout<<"res4a_branch2c"<<endl;


    addeltwise(branch_1,output_1,output_2,1024,14);
    cout<<"res4a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,1024,256,1,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,output_1,1024,256,14,14,1,1,0,1);
    cout<<"res4b_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,256,3,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,branch_1,256,256,14,14,3,1,1,1);
    cout<<"res4b_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,1024,1,fid);
    //load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_1,256,1024,14,14,1,1,0,0);
    cout<<"res4b_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,1024,14);
    cout<<"res4b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,1024,256,1,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_1,1024,256,14,14,1,1,0,1);
    cout<<"res4c_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,256,3,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,256,256,14,14,3,1,1,1);
    cout<<"res4c_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,1024,1,fid);
    //load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,output_1,256,1024,14,14,1,1,0,0);
    cout<<"res4c_branch2c"<<endl;

    addeltwise(branch_1,output_1,output_2,1024,14);
    cout<<"res4c"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,1024,256,1,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,output_1,1024,256,14,14,1,1,0,1);
    cout<<"res4d_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,256,3,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,branch_1,256,256,14,14,3,1,1,1);
    cout<<"res4d_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,1024,1,fid);
    //load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_1,256,1024,14,14,1,1,0,0);
    cout<<"res4d_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,1024,14);
    cout<<"res4d"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,1024,256,1,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,1024,256,14,14,1,1,0,1);
    cout<<"res4e_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,256,3,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,output_1,256,256,14,14,3,1,1,1);
    cout<<"res4e_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,1024,1,fid);
    //load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,256,1024,14,14,1,1,0,0);
    cout<<"res4e_branch2c"<<endl;

    addeltwise(branch_1,output_2,output_1,1024,14);
    cout<<"res4e"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,1024,256,1,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,1024,256,14,14,1,1,0,1);
    cout<<"res4f_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,256,3,fid);
    //load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,branch_1,256,256,14,14,3,1,1,1);
    cout<<"res4f_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,256,1024,1,fid);
    //load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,256,1024,14,14,1,1,0,0);
    cout<<"res4f_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,1024,14);
    cout<<"res4f"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,1024,2048,1,fid);
    //load_weights(bias,1,2048,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_1,1024,2048,14,7,1,2,0,0);
    cout<<"res5a_branch1"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,1024,512,1,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,1024,512,14,7,1,2,0,1);
    cout<<"res5a_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,512,512,3,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,output_3,512,512,7,7,3,1,1,1);
    cout<<"res5a_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,512,2048,1,fid);
    //load_weights(bias,1,2048,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_3,output_2,512,2048,7,7,1,1,0,0);
    cout<<"res5a_branch2c"<<endl;


    addeltwise(output_1,output_2,branch_1,2048,7);
    cout<<"res5a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,2048,512,1,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,2048,512,7,7,1,1,0,1);
    cout<<"res5b_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,512,512,3,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,output_1,512,512,7,7,3,1,1,1);
    cout<<"res5b_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,512,2048,1,fid);
    //load_weights(bias,1,2048,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,512,2048,7,7,1,1,0,0);
    cout<<"res5b_branch2c"<<endl;

    addeltwise(branch_1,output_2,output_1,2048,7);
    cout<<"res5b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,2048,512,1,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_1,output_2,2048,512,7,7,1,1,0,1);
    cout<<"res5c_branch2a"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,512,512,3,fid);
    //load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,output_2,branch_1,512,512,7,7,3,1,1,1);
    cout<<"res5c_branch2b"<<endl;

    load_weights(weights,bias,mean,vari,gamma,beta,512,2048,1,fid);
    //load_weights(bias,1,2048,1,fid);
    convGolden(weights,bias,mean,vari,gamma,beta,branch_1,output_2,512,2048,7,7,1,1,0,0);
    cout<<"res5c_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,2048,7);
//    cout<<"res2b"<<endl;
//
//        for (int i = 0; i < 2048*7*7; i++){
//
//             //if(branch_1[i] != 0){
//            	 printf("%d\n" ,branch_1[i]);
//             //}
//         }

    aver_pool_2(branch_1,output_2,2048,2048,7,1);
    cout<<"pool5"<<endl;

    load_weights_fc(weights,bias,2048,1000,1,fid);
    //load_weights(bias,1,1000,1,fid);
    //printf("%f\n" ,bias[999]);
    fc(bias,output_2,weights,output_1,2048,1,1000,1);
    cout<<"fc1000"<<endl;

//	for (int i = 0; i < 1000; i++){
//
//		 //if(branch_1[i] != 0){
//			 printf("%f\n" ,output_1[i]);
//		 //}
//	 }

    datatype_inh max = output_1[0];

    for (int i = 0; i < 1000; i++){
        //printf("%d\n" ,output_1[i]);
        if(max<output_1[i]){
            prediction = i;
            max = output_1[i];
        }
    }
   cout<<"prediction::"<<prediction<<endl;
   printf("The prediction is %d\n", prediction);
   //printf("The ochan is %d\n", noofochan);/// 25530472 in quantized file//
   //25610269-3*(27560-1000)=25530589-64////////////// 25610216 extra 53 values in the file

//  high_resolution_clock::time_point t2 = high_resolution_clock::now();
//  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
// //std::cout << "It took me " << time_span.count() << " seconds.";


    fclose(fid);
    return 0;
}

