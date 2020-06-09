
#include <stdio.h>
#include "stdint.h"
#include <stdlib.h>
#include "ap_int.h"
#include <ap_utils.h>
typedef float  datatype_inh;
typedef float  datatype_int;
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
//	std::cout << "result " << maxcount << std::endl;


    // Runs over output filters
    for(int output = 0; output < o_chan; output++){
        // Runs over output pixel in Y-direction
        for(int y = 0; y < o_size; y++){
            // Runs over output pixel in X-direction
            for(int x = 0; x < o_size; x++){
            	datatype_int acc = 0;
            	datatype_int bias_sum = 0;
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

                            // Convolution operation
                            if(yVal >= 0 && yVal < i_size && xVal >= 0 && xVal < i_size){
                                acc += (datatype_inh) image[(input*i_size + yVal)*i_size + xVal] *
                                       (datatype_inh) (weight[((output*i_chan + input)*w_size + i)*w_size + j] );
                            }
                        }

                    }
		}

                bias_sum = (acc + bias[output]);

			if(bias_sum < 0 && relu_on == 1)
                //std::std::cout << "result " << acc << std::std::endl;
		         out[(output*o_size + y)*o_size + x] = 0;

			else
		         out[(output*o_size + y)*o_size + x] = (datatype_inh) (( bias_sum));
            }
        }
    }
}

void convGolden0(
	datatype_inh *weight,
	datatype_inh *bias,
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
    // Runs over output filters
    for(int output = 0; output < o_chan; output++){
        // Runs over output pixel in Y-direction
        for(int y = 0; y < o_size; y++){
            // Runs over output pixel in X-direction
            for(int x = 0; x < o_size; x++){
            	datatype_int acc = 0;
            	datatype_int bias_sum = 0;
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

                            // Convolution operation
                            if(yVal >= 0 && yVal < i_size && xVal >= 0 && xVal < i_size){
                                acc += (datatype_inh) image[(input*i_size + yVal)*i_size + xVal] *
                                       (datatype_inh) (weight[((output*i_chan + input)*w_size + i)*w_size + j] );
                            }
                        }

                    }
		}

                bias_sum = (acc + bias[output]);

			if(bias_sum < 0 && relu_on == 1)
                //std::std::cout << "result " << acc << std::std::endl;
		         out[(output*o_size + y)*o_size + x] = 0;

			else
		         out[(output*o_size + y)*o_size + x] = (datatype_inh) (( bias_sum));
            }
        }
    }
}

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
void load_weights(
	datatype_inh *weights,
	int i_chan,
	    	    int o_chan,
	    	    int w_size,
				FILE *fid)
{
        assert( fid != NULL );
        int  j;
        float data;
        char str[300];
        static int64_t count = 0;

	for (j = 0; j < o_chan * i_chan * w_size * w_size; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  //std::cout <<   weights[j] << std::endl;
	  weights[j] =  (datatype_inh) (data);
	  //std::cout <<   weights[j] << std::endl;
	  fscanf(fid,"\n");
	  count = count +  1;
	}

	//std::cout <<   count << std::endl;

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
	for (int i = 0; i < fc_chan; ++i) {
//	datatype_inh	bias_sum = 0;
      datatype_int bias_sum = 0;

      datatype_int sum = 0;

		for (int j = 0; j < i_chan * i_size * i_size; ++j) {
			bias_sum += image[j] * (weight[i * i_chan * i_size * i_size + j]);
		}
sum =(bias_sum + bias[i]);
if(sum < 0)
output[i] = 0;
else
output[i] = (datatype_inh)  sum;
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


int main()

{

    datatype_inh weights[4096 * 512 * 10  * 10];
    datatype_inh bias[2048];
    datatype_inh output_1[512 * 448 * 448];
    datatype_inh output_2[512 * 448 * 448];
    datatype_inh output_3[512 * 448 * 448];
    datatype_inh branch_1[512 * 448 * 448];

	int prediction=0;

    int jj;
 	float datai;
 	char stri[2048];

	FILE *fidi = fopen("un_mean_image.txt", "r");/// 497 224*224*3
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

    FILE *fid = fopen("linear_weights.txt", "r");
    //using namespace std::chrono;
    //high_resolution_clock::time_point t1 = high_resolution_clock::now();

    load_weights(weights,3,64,7,fid);
    load_weights(bias,1,64,1,fid);
    convGolden0(weights,bias, output_1,output_2,3,64,224,112,7,2,3,1);
    cout<<"c1"<<endl;


    max_pool(output_2,branch_1,64,64,112,56,3,2,0,0);
    cout<<"pool1"<<endl;

    load_weights(weights,64,256,1,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,branch_1,output_2,64,256,56,56,1,1,0,0);
    cout<<"res2a_branch1"<<endl;


    load_weights(weights,64,64,1,fid);
    load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,branch_1,output_1,64,64,56,56,1,1,0,1);
    cout<<"res2a_branch2a"<<endl;



    load_weights(weights,64,64,3,fid);
    load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,output_1,output_3,64,64,56,56,3,1,1,1);
    cout<<"res2a_branch2b"<<endl;



    load_weights(weights,64,256,1,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_3,output_1,64,256,56,56,1,1,0,0);
    cout<<"res2a_branch2c"<<endl;


    addeltwise(output_1,output_2,branch_1,256,56);
    cout<<"res2a"<<endl;


    load_weights(weights,256,64,1,fid);
    load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,branch_1,output_2,256,64,56,56,1,1,0,1);
    cout<<"res2b_branch2a"<<endl;

    load_weights(weights,64,64,3,fid);
    load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,output_2,output_1,64,64,56,56,3,1,1,1);
    cout<<"res2b_branch2b"<<endl;

    load_weights(weights,64,256,1,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_1,output_2,64,256,56,56,1,1,0,0);
    cout<<"res2b_branch2c"<<endl;

    addeltwise(branch_1,output_2,output_1,256,56);
    cout<<"res2b"<<endl;

//    for (int i = 0; i < 256*56*56; i++){
//        	 printf("%f\n" ,output_1[i]);
//     }

    load_weights(weights,256,64,1,fid);
    load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,output_1,output_2,256,64,56,56,1,1,0,1);
    cout<<"res2c_branch2a"<<endl;

    load_weights(weights,64,64,3,fid);
    load_weights(bias,1,64,1,fid);
    convGolden(weights,bias,output_2,branch_1,64,64,56,56,3,1,1,1);
    cout<<"res2c_branch2b"<<endl;

    load_weights(weights,64,256,1,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,branch_1,output_2,64,256,56,56,1,1,0,0);
    cout<<"res2c_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,256,56);
    cout<<"res2c"<<endl;

    load_weights(weights,256,512,1,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,branch_1,output_2,256,512,56,28,1,2,0,0);
    cout<<"res3a_branch1"<<endl;


    load_weights(weights,256,128,1,fid);
    load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,branch_1,output_1,256,128,56,28,1,2,0,1);
    cout<<"res3a_branch2a"<<endl;

    load_weights(weights,128,128,3,fid);
    load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,output_1,output_3,128,128,28,28,3,1,1,1);
    cout<<"res3a_branch2b"<<endl;

    load_weights(weights,128,512,1,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,output_3,output_1,128,512,28,28,1,1,0,0);
    cout<<"res3a_branch2c"<<endl;


    addeltwise(output_1,output_2,branch_1,512,28);
    cout<<"res3a"<<endl;

    load_weights(weights,512,128,1,fid);
    load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,branch_1,output_2,512,128,28,28,1,1,0,1);
    cout<<"res3b_branch2a"<<endl;

    load_weights(weights,128,128,3,fid);
    load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,output_2,output_1,128,128,28,28,3,1,1,1);
    cout<<"res3b_branch2b"<<endl;

    load_weights(weights,128,512,1,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,output_1,output_2,128,512,28,28,1,1,0,0);
    cout<<"res3b_branch2c"<<endl;

    addeltwise(branch_1,output_2,output_1,512,28);
    cout<<"res3b"<<endl;

    load_weights(weights,512,128,1,fid);
    load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,output_1,output_2,512,128,28,28,1,1,0,1);
    cout<<"res3c_branch2a"<<endl;

    load_weights(weights,128,128,3,fid);
    load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,output_2,branch_1,128,128,28,28,3,1,1,1);
    cout<<"res3c_branch2b"<<endl;

    load_weights(weights,128,512,1,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,branch_1,output_2,128,512,28,28,1,1,0,0);
    cout<<"res3c_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,512,28);
    cout<<"res3c"<<endl;

    load_weights(weights,512,128,1,fid);
    load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,branch_1,output_1,512,128,28,28,1,1,0,1);
    cout<<"res3d_branch2a"<<endl;

    load_weights(weights,128,128,3,fid);
    load_weights(bias,1,128,1,fid);
    convGolden(weights,bias,output_1,output_2,128,128,28,28,3,1,1,1);
    cout<<"res3d_branch2b"<<endl;

    load_weights(weights,128,512,1,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,output_2,output_1,128,512,28,28,1,1,0,0);
    cout<<"res3d_branch2c"<<endl;


    addeltwise(branch_1,output_1,output_2,512,28);
    cout<<"res3d"<<endl;

    load_weights(weights,512,1024,1,fid);
    load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,output_2,branch_1,512,1024,28,14,1,2,0,0);
    cout<<"res4a_branch1"<<endl;


    load_weights(weights,512,256,1,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_2,output_1,512,256,28,14,1,2,0,1);
    cout<<"res4a_branch2a"<<endl;

    load_weights(weights,256,256,3,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_1,output_3,256,256,14,14,3,1,1,1);
    cout<<"res4a_branch2b"<<endl;

    load_weights(weights,256,1024,1,fid);
    load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,output_3,output_1,256,1024,14,14,1,1,0,0);
    cout<<"res4a_branch2c"<<endl;


    addeltwise(branch_1,output_1,output_2,1024,14);
    cout<<"res4a"<<endl;

    load_weights(weights,1024,256,1,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_2,output_1,1024,256,14,14,1,1,0,1);
    cout<<"res4b_branch2a"<<endl;

    load_weights(weights,256,256,3,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_1,branch_1,256,256,14,14,3,1,1,1);
    cout<<"res4b_branch2b"<<endl;

    load_weights(weights,256,1024,1,fid);
    load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,branch_1,output_1,256,1024,14,14,1,1,0,0);
    cout<<"res4b_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,1024,14);
    cout<<"res4b"<<endl;

    load_weights(weights,1024,256,1,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,branch_1,output_1,1024,256,14,14,1,1,0,1);
    cout<<"res4c_branch2a"<<endl;

    load_weights(weights,256,256,3,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_1,output_2,256,256,14,14,3,1,1,1);
    cout<<"res4c_branch2b"<<endl;

    load_weights(weights,256,1024,1,fid);
    load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,output_2,output_1,256,1024,14,14,1,1,0,0);
    cout<<"res4c_branch2c"<<endl;

    addeltwise(branch_1,output_1,output_2,1024,14);
    cout<<"res4c"<<endl;

    load_weights(weights,1024,256,1,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_2,output_1,1024,256,14,14,1,1,0,1);
    cout<<"res4d_branch2a"<<endl;

    load_weights(weights,256,256,3,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_1,branch_1,256,256,14,14,3,1,1,1);
    cout<<"res4d_branch2b"<<endl;

    load_weights(weights,256,1024,1,fid);
    load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,branch_1,output_1,256,1024,14,14,1,1,0,0);
    cout<<"res4d_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,1024,14);
    cout<<"res4d"<<endl;

    load_weights(weights,1024,256,1,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,branch_1,output_2,1024,256,14,14,1,1,0,1);
    cout<<"res4e_branch2a"<<endl;

    load_weights(weights,256,256,3,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_2,output_1,256,256,14,14,3,1,1,1);
    cout<<"res4e_branch2b"<<endl;

    load_weights(weights,256,1024,1,fid);
    load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,output_1,output_2,256,1024,14,14,1,1,0,0);
    cout<<"res4e_branch2c"<<endl;

    addeltwise(branch_1,output_2,output_1,1024,14);
    cout<<"res4e"<<endl;

    load_weights(weights,1024,256,1,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_1,output_2,1024,256,14,14,1,1,0,1);
    cout<<"res4f_branch2a"<<endl;

    load_weights(weights,256,256,3,fid);
    load_weights(bias,1,256,1,fid);
    convGolden(weights,bias,output_2,branch_1,256,256,14,14,3,1,1,1);
    cout<<"res4f_branch2b"<<endl;

    load_weights(weights,256,1024,1,fid);
    load_weights(bias,1,1024,1,fid);
    convGolden(weights,bias,branch_1,output_2,256,1024,14,14,1,1,0,0);
    cout<<"res4f_branch2c"<<endl;

    addeltwise(output_1,output_2,branch_1,1024,14);
    cout<<"res4f"<<endl;

    load_weights(weights,1024,2048,1,fid);
    load_weights(bias,1,2048,1,fid);
    convGolden(weights,bias,branch_1,output_1,1024,2048,14,7,1,2,0,0);
    cout<<"res5a_branch1"<<endl;

    load_weights(weights,1024,512,1,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,branch_1,output_2,1024,512,14,7,1,2,0,1);
    cout<<"res5a_branch2a"<<endl;

    load_weights(weights,512,512,3,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,output_2,output_3,512,512,7,7,3,1,1,1);
    cout<<"res5a_branch2b"<<endl;

    load_weights(weights,512,2048,1,fid);
    load_weights(bias,1,2048,1,fid);
    convGolden(weights,bias,output_3,output_2,512,2048,7,7,1,1,0,0);
    cout<<"res5a_branch2c"<<endl;


    addeltwise(output_1,output_2,branch_1,2048,7);
    cout<<"res5a"<<endl;

    load_weights(weights,2048,512,1,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,branch_1,output_2,2048,512,7,7,1,1,0,1);
    cout<<"res5b_branch2a"<<endl;

    load_weights(weights,512,512,3,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,output_2,output_1,512,512,7,7,3,1,1,1);
    cout<<"res5b_branch2b"<<endl;

    load_weights(weights,512,2048,1,fid);
    load_weights(bias,1,2048,1,fid);
    convGolden(weights,bias,output_1,output_2,512,2048,7,7,1,1,0,0);
    cout<<"res5b_branch2c"<<endl;

    addeltwise(branch_1,output_2,output_1,2048,7);
    cout<<"res5b"<<endl;

    load_weights(weights,2048,512,1,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,output_1,output_2,2048,512,7,7,1,1,0,1);
    cout<<"res5c_branch2a"<<endl;

    load_weights(weights,512,512,3,fid);
    load_weights(bias,1,512,1,fid);
    convGolden(weights,bias,output_2,branch_1,512,512,7,7,3,1,1,1);
    cout<<"res5c_branch2b"<<endl;

    load_weights(weights,512,2048,1,fid);
    load_weights(bias,1,2048,1,fid);
    convGolden(weights,bias,branch_1,output_2,512,2048,7,7,1,1,0,0);
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

    load_weights(weights,2048,1000,1,fid);
    load_weights(bias,1,1000,1,fid);
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

//  high_resolution_clock::time_point t2 = high_resolution_clock::now();
//  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
// std::cout << "It took me " << time_span.count() << " seconds.";


    fclose(fid);
    return 0;
}

