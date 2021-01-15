#include <stdio.h>
#include "stdint.h"
#include <stdlib.h>
#include <hls_half.h>
typedef int16_t datatype_inh;
typedef int datatype_argu;
#include "ap_fixed.h"
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
#include "xcl2.hpp"
#include <stdio.h>
#include "stdint.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <limits>
#include <string>
#include <CL/cl_ext.h>
#include <x86intrin.h>
#include <immintrin.h>
#include <cstdint>
#include <dirent.h>
#include <pthread.h>

std::string binaryFile;

typedef struct convGoldenArg {
	int8_t *weight;
	datatype_inh *bias;
	datatype_inh *image;
	datatype_inh *out;
    int i_chan;
    int o_chan;
    int i_size;
    int o_size;
    int w_size;
    int stride;
    int padding;
    int relu_on;
} convGoldenArg_t;

typedef struct max_poolArg {
	datatype_inh *in_vector;
	datatype_inh *out_vector;
    int i_chan;
    int o_chan;
    int i_size;
    int o_size;
    int w_size;
    int stride;
    int padding;
    int relu_on;
} max_poolArg_t;

void * convGolden(
	void* arg
)
{
	printf("pthread create convGolden\n");
	convGoldenArg_t *args = (convGoldenArg_t *)arg;
	int8_t *weight = args -> weight;
	datatype_inh *bias = args -> bias;
	datatype_inh *image = args -> image;
	datatype_inh *out = args -> out;
    int i_chan = args -> i_chan;
    int o_chan = args -> o_chan;
    int i_size = args -> i_size;
    int o_size = args -> o_size;
    int w_size = args -> w_size;
    int stride = args -> stride;
    int padding = args -> padding;
    int relu_on = args -> relu_on;
    // Runs over output filters
    for(int output = 0; output < o_chan; output++){
        // Runs over output pixel in Y-direction
        for(int y = 0; y < o_size; y++){
            // Runs over output pixel in X-direction
            for(int x = 0; x < o_size; x++){
            	int acc = 0;
    		    int bias_sum = 0;
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
        		bias_sum = (acc);
				if(bias_sum < 0)
					out[(output*o_size + y)*o_size + x] = 0;
				else
		    		out[(output*o_size + y)*o_size + x] = (datatype_inh) ( bias_sum/pow(2,6));
            }
        }
    }
	return NULL;
}

void *max_pool(
	void* arg
) {
	printf("pthread create max_pool\n");
	max_poolArg_t * args = (max_poolArg_t *) arg;
	datatype_inh *in_vector = args->in_vector;
	datatype_inh *out_vector = args -> out_vector;
	int i_chan = args -> i_chan;
    int o_chan = args -> o_chan;
    int i_size = args -> i_size;
    int o_size = args -> o_size;
    int w_size = args -> w_size;
    int stride = args -> stride;
    int padding = args -> padding;
    int relu_on = args -> relu_on;

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
	return NULL;
}

void load_weights(
	int8_t *weights,
	int i_chan,
	int o_chan,
	int w_size,
	FILE *fid)
{
    assert( fid != NULL );
    int  j;
    float data;
    char str[300];

	for (j = 0; j < o_chan * i_chan * w_size * w_size; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  weights[j] =  (int8_t) (data*pow(2,6));
	  fscanf(fid,"\n");
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
        static int layer_no = 0;
	for (j = 0; j < i_chan * i_size * i_size; j++)
	{

		data = write_out[j];
		dd = (float) data;
		fprintf(fpoint,"%f", dd);
	    fprintf(fpoint,"\n");
	}
	fprintf(fpoint,"%s", "layer_no: ");
	fprintf(fpoint,"%d", layer_no);
	fprintf(fpoint,"\n");
	layer_no = layer_no + 1;
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
		datatype_inh bias_sum = 0;
		datatype_inh sum = 0;
		for (int j = 0; j < i_chan * i_size * i_size; ++j) {
			bias_sum += image[j] * (weight[i * i_chan * i_size * i_size + j]);
		}
		sum =(bias_sum + bias[i]);
		if(relu_on == 1 && sum < 0)
			output[i] = 0;
		else
			output[i] = (datatype_inh)  sum;
	}
}

typedef struct aver_pool_2_arg {
	datatype_inh *in_vector;
	datatype_inh *out_vector;
    int i_chan;
    int o_chan;
    int i_size;
    int o_size;
    int w_size;
    int stride;
    int padding;
    int relu_on;
 } aver_pool_2_arg_t;


void* aver_pool_2(
	void* arg
	) {
	printf("pthread create aver_pool!\n");
	aver_pool_2_arg_t * args = (aver_pool_2_arg_t *) arg;
	datatype_inh *in_vector = args->in_vector;
	datatype_inh *out_vector = args->out_vector;
    int i_chan = args -> i_chan;
    int o_chan = args -> o_chan;
    int i_size = args -> i_size;
    int o_size = args -> o_size;
    int w_size = args -> w_size;
    int stride = args -> stride;
    int padding = args -> padding;
    int relu_on = args -> relu_on;

	for (int i = 0; i < i_chan * o_size * o_size; i++)
		out_vector[i] = -INFINITY;

	for (int c = 0; c < o_chan; ++c) {
		datatype_inh aver = 0;
		for (int ph = 0; ph < i_size; ph++) {
		  	for (int pw = 0; pw < i_size; pw++) {
		    	aver += in_vector[c * i_size * i_size + i_size * ph + pw];
		    }
		}
		out_vector[c] = aver;
	}
}

int main(int argc, char* argv[])
{
    if(argc != 11)
    {
		printf("Missing arguments, expect: ./squeezenet_next <image1> <image2> <image3> <image4> <image5> <image6> <image7> <image8> <weight> <binary>\n");
        std::cout << "Usage: " << argv[0] <<" <input_image>" << std::endl;
        return -1;
    }
    binaryFile = argv[10];

    // Allocate Memory in Host (Image, Weights and Output)
    size_t image_size_bytes  = sizeof(datatype_inh) * 512 * 224 * 224;
    size_t weight_size_bytes = sizeof(datatype_inh) * 96*49*3;
    size_t weight_size_bytes_hw = sizeof(int8_t) * 1280000;
    size_t output_size_bytes_1 = sizeof(datatype_inh) *512*55*55;
    size_t output_size_bytes_2 = sizeof(datatype_inh) *512*55*55;
    size_t output_size_bytes_3 = sizeof(datatype_inh) *512 * 224 * 224;
    size_t output_size_bytes_4 = sizeof(datatype_inh) *512 * 224 * 224;
    size_t output_size_bytes_para = sizeof(datatype_inh) * 512 * 224 * 224;//4845824;
    size_t output_size_bytes = sizeof(datatype_inh) *512 * 224 * 224;
    size_t bias_bytes = sizeof(datatype_inh) * 1024;
    size_t para_bytes = sizeof(int) * 1024;

    size_t input_tt = sizeof(int8_t) * 128 * 55 * 55;
    size_t weight_size_bytes_w7 = sizeof(int8_t) * 96*49*3;
    size_t output_tt = sizeof(datatype_inh) * 1024 ;

    std::vector<int8_t,aligned_allocator<int8_t>> weights_w7(weight_size_bytes_w7);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> weights(weight_size_bytes);
    std::vector<int8_t,aligned_allocator<int8_t>> weights_hw_1(weight_size_bytes_hw);
	std::vector<int8_t,aligned_allocator<int8_t>> weights_hw_2(weight_size_bytes_hw);
	std::vector<int8_t,aligned_allocator<int8_t>> weights_hw_3(weight_size_bytes_hw);
	std::vector<int8_t,aligned_allocator<int8_t>> weights_hw_4(weight_size_bytes_hw);
    std::vector<int8_t,aligned_allocator<int8_t>> weights_1(weight_size_bytes_hw);
    std::vector<int8_t,aligned_allocator<int8_t>> weights_2(weight_size_bytes_hw);
    std::vector<int8_t,aligned_allocator<int8_t>> weights_3(weight_size_bytes_hw);

    std::vector<int8_t,aligned_allocator<int8_t>> output_3(input_tt);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_avg(output_tt);

    std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_1_1(output_size_bytes_1);
	std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_1_2(output_size_bytes_1);
	std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_1_3(output_size_bytes_1);
	std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_1_4(output_size_bytes_1);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_2_1(output_size_bytes_2);
	std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_2_2(output_size_bytes_2);
	std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_2_3(output_size_bytes_2);
	std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_2_4(output_size_bytes_2);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> bias(bias_bytes);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_para(output_size_bytes_para);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> tmp2(output_size_bytes_para);

    std::vector<int,aligned_allocator<int>> weights_hw1(para_bytes);

	std::cout << "Reading weight file" << std::endl;
	FILE *fid_hw;
	const char *imageFilename_22 = argv[9];
	fid_hw = fopen(imageFilename_22, "rb");
        int jjjj;
     	float dataii;
     	char strii[300];

    	for (jjjj = 0; jjjj < 1280000; jjjj++) {
    	if( jjjj < 1248424)
    	{
    	  	fscanf(fid_hw,"%s", strii);
			dataii = atof(strii);
			weights_hw_1[jjjj] = (int8_t) (dataii *pow(2,6));
			weights_hw_2[jjjj] = (int8_t) (dataii *pow(2,6));
			weights_hw_3[jjjj] = (int8_t) (dataii *pow(2,6));
			weights_hw_4[jjjj] = (int8_t) (dataii *pow(2,6));
			weights_1[jjjj] = weights_hw_1[jjjj];
			weights_2[jjjj] = weights_hw_1[jjjj];
			weights_3[jjjj] = weights_hw_1[jjjj];
			if(jjjj < 96*49*3)
    		  	weights_w7[jjjj] = weights_hw_1[jjjj];
    	  	fscanf(fid_hw,"\n");
    	}
    	else
    	{
    		weights_hw_1[jjjj] = 0;
			weights_hw_2[jjjj] = 0;
			weights_hw_3[jjjj] = 0;
			weights_hw_4[jjjj] = 0;
    	    weights_1[jjjj] = weights_hw_1[jjjj];
    	    weights_2[jjjj] = weights_hw_1[jjjj];
    	    weights_3[jjjj] = weights_hw_1[jjjj];
    	}
    	}
        fclose(fid_hw);

		int round = 0;

		uint64_t total_duration = 0;
		auto total_time_start = std::chrono::high_resolution_clock::now();
		for (round = 0; round < 2; round++) {
        int jj;
     	float datai;
     	char stri_1[300]="1";
     	printf("Read image file 1 in round %d\n", round + 1);
     	FILE *input_file_1;
    	const char *imageFilename_1 = argv[1 + round * 4]; // image
    	input_file_1 = fopen(imageFilename_1, "rb");

    	 if (!input_file_1)
    	    {
    	        printf("Error: Unable to open input image file %s!\n",imageFilename_1);
    	      return 1;
    	}

    	for (jj = 0; jj < 128*55*55; jj++) {
    		if(jj < 3 * 227 * 227)
    		{
			fscanf(input_file_1,"%s", stri_1);
			datai = atof(stri_1);
			output_1_1[jj] = (datatype_inh) datai;//rand() % 100 + 10);//
			fscanf(input_file_1,"\n");
    		}
    		else{
        		output_1_1[jj] = (datatype_inh) 0;
    		}
    	}
        fclose(input_file_1);

        char stri_2[300]="1";
     	printf("Read image file 2 in round %d\n", round + 1);
     	FILE *input_file_2;
    	const char *imageFilename_2 = argv[2 + round * 4];
    	input_file_2 = fopen(imageFilename_2, "rb");
    	if (!input_file_2)
    	    {
    	        printf("Error: Unable to open input image file %s!\n",
    	        imageFilename_2);
    	        return 1;
    	}

    	for (jj = 0; jj < 128*55*55; jj++) {
    		if(jj < 3 * 227 * 227)
    		{
    	  fscanf(input_file_2,"%s", stri_2);
    	  datai = atof(stri_2);
		  output_1_2[jj] = (datatype_inh) datai;
    	  fscanf(input_file_2,"\n");
    		}
    		else{
				 output_1_2[jj] = (datatype_inh) 0;
    		}
    	}
         fclose(input_file_2);

		char stri_3[300]="1";
     	printf("Read image file 3 in round %d\n", round + 1);
     	FILE *input_file_3;
    	const char *imageFilename_3 = argv[3 + round * 4];
    	input_file_3 = fopen(imageFilename_3, "rb");

    	 if (!input_file_3)
    	    {
    	        printf("Error: Unable to open input image file %s!\n",
    	        imageFilename_3);
    	        return 1;
    	}


    	for (jj = 0; jj < 128*55*55; jj++) {
    		if(jj < 3 * 227 * 227)
    		{
    	  fscanf(input_file_3,"%s", stri_3);
    	  datai = atof(stri_3);
		  output_1_3[jj] = (datatype_inh) datai;
    	  fscanf(input_file_3,"\n");
    	}
    		else{
				 output_1_3[jj] = (datatype_inh) 0;
    		}
    	}
        fclose(input_file_3);

		char stri_4[300]="1";
     	printf("Read image file 4 in round %d\n", round + 1);
     	FILE *input_file_4;
    	const char *imageFilename_4 = argv[4 + round * 4];
    	input_file_4 = fopen(imageFilename_4, "rb");

    	 if (!input_file_4)
    	    {
    	        printf("Error: Unable to open input image file %s!\n",
    	        imageFilename_4);
    	        return 1;
    	}


    	for (jj = 0; jj < 128*55*55; jj++) {
    		if(jj < 3 * 227 * 227)
    		{
			fscanf(input_file_4,"%s", stri_4);
			datai = atof(stri_4);
			output_1_4[jj] = (datatype_inh) datai;
			fscanf(input_file_4,"\n");
    		}
    		else{
				 output_1_4[jj] = (datatype_inh) 0;
    		}
    	}
        fclose(input_file_4);
pthread_t tid1;
pthread_t tid2;
pthread_t tid3;
pthread_t tid4;

printf("start pthread for sw layers (start)\n");

printf("start convGolden\n");
uint64_t good_duration_2 = 0;
auto kernel_start_2 = std::chrono::high_resolution_clock::now();

auto start_convGolden = std::chrono::high_resolution_clock::now();

convGoldenArg_t args_convGolden[4];
int idx = 0;
for (idx = 0; idx < 4; idx++) {
	args_convGolden[idx].i_chan = 3;
	args_convGolden[idx].o_chan = 96;
	args_convGolden[idx].i_size = 227;
	args_convGolden[idx].o_size= 111;
	args_convGolden[idx].w_size = 7;
	args_convGolden[idx].stride = 2;
	args_convGolden[idx].padding = 0;
	args_convGolden[idx].relu_on= 1;
}
args_convGolden[0].weight = weights_hw_1.data();
args_convGolden[0].bias = bias.data();
args_convGolden[0].image = output_1_1.data();
args_convGolden[0].out = output_2_1.data();

args_convGolden[1].weight = weights_hw_2.data();
args_convGolden[1].bias = bias.data();
args_convGolden[1].image = output_1_2.data();
args_convGolden[1].out = output_2_2.data();

args_convGolden[2].weight = weights_hw_3.data();
args_convGolden[2].bias = bias.data();
args_convGolden[2].image = output_1_3.data();
args_convGolden[2].out = output_2_3.data();

args_convGolden[3].weight = weights_hw_4.data();
args_convGolden[3].bias = bias.data();
args_convGolden[3].image = output_1_4.data();
args_convGolden[3].out = output_2_4.data();

pthread_create(&tid1, NULL, convGolden, &args_convGolden[0]);
pthread_create(&tid2, NULL, convGolden, &args_convGolden[1]);
pthread_create(&tid3, NULL, convGolden, &args_convGolden[2]);
pthread_create(&tid4, NULL, convGolden, &args_convGolden[3]);
    
pthread_join(tid1, NULL);
pthread_join(tid2, NULL);
pthread_join(tid3, NULL);
pthread_join(tid4, NULL);

auto end_convGolden = std::chrono::high_resolution_clock::now();
printf("end convGolden\n");
auto conv_Golden_time = std::chrono::duration<uint64_t, std::nano>(end_convGolden - start_convGolden);
uint64_t conv_Golden_duration =  conv_Golden_time.count();
std::cout << "convGolden duration = " << conv_Golden_duration << " ns" << std::endl;


max_poolArg_t args_max_pool[4];

printf("start args_max_pool\n");
auto start_args_max = std::chrono::high_resolution_clock::now();

for (idx = 0; idx < 4; idx++) {
	args_max_pool[idx].i_chan = 96;
	args_max_pool[idx].o_chan = 96;
	args_max_pool[idx].i_size = 111;
	args_max_pool[idx].o_size= 55;
	args_max_pool[idx].w_size = 3;
	args_max_pool[idx].stride = 2;
	args_max_pool[idx].padding = 0;
	args_max_pool[idx].relu_on= 0;
}

args_max_pool[0].in_vector = output_2_1.data();
args_max_pool[0].out_vector = output_1_1.data();

args_max_pool[1].in_vector = output_2_2.data();
args_max_pool[1].out_vector = output_1_2.data();

args_max_pool[2].in_vector = output_2_3.data();
args_max_pool[2].out_vector = output_1_3.data();

args_max_pool[3].in_vector = output_2_4.data();
args_max_pool[3].out_vector = output_1_4.data();

pthread_create(&tid1, NULL, max_pool, &args_max_pool[0]);
pthread_create(&tid2, NULL, max_pool, &args_max_pool[1]);
pthread_create(&tid3, NULL, max_pool, &args_max_pool[2]);
pthread_create(&tid4, NULL, max_pool, &args_max_pool[3]);
    
// Wait for all the threads to end
pthread_join(tid1, NULL);
pthread_join(tid2, NULL);
pthread_join(tid3, NULL);
pthread_join(tid4, NULL);

auto end_args_max = std::chrono::high_resolution_clock::now();
printf("end args_max_pool\n");
auto args_max_time = std::chrono::duration<uint64_t, std::nano>(end_args_max - start_args_max);
uint64_t args_max_duration =  args_max_time.count();
std::cout << "args_max_pool duration = " << args_max_duration << " ns" << std::endl;

cl::Context context;
cl::Kernel krnl_cnn_conv_1, krnl_cnn_conv_2, krnl_cnn_conv_3, krnl_cnn_conv_4;
cl_int err;
auto devices = xcl::get_xil_devices();
auto fileBuf = xcl::read_binary_file(binaryFile);
cl::Program::Binaries bins{{fileBuf.data(), fileBuf.size()}};
int valid_device = 0;
auto device = devices[0];
OCL_CHECK(err, context = cl::Context({device}, NULL, NULL, NULL, &err));
OCL_CHECK(err, cl::CommandQueue q_1(context, {device}, CL_QUEUE_PROFILING_ENABLE, &err));
OCL_CHECK(err, cl::CommandQueue q_2(context, {device}, CL_QUEUE_PROFILING_ENABLE, &err));
OCL_CHECK(err, cl::CommandQueue q_3(context, {device}, CL_QUEUE_PROFILING_ENABLE, &err));
OCL_CHECK(err, cl::CommandQueue q_4(context, {device}, CL_QUEUE_PROFILING_ENABLE, &err));
std::cout << "Trying to program device[" << 0
          << "]: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
cl::Program program(context, {device}, bins, NULL, &err);
if (err != CL_SUCCESS) {
    std::cout << "Failed to program device[" << 0
              << "] with xclbin file!\n";
} else {
    std::cout << "Device[" << 0 << "]: program successful!\n";
    OCL_CHECK(err, krnl_cnn_conv_1 = cl::Kernel(program, "cnn_one", &err));
	OCL_CHECK(err, krnl_cnn_conv_2 = cl::Kernel(program, "cnn_two", &err));
	OCL_CHECK(err, krnl_cnn_conv_3 = cl::Kernel(program, "cnn_three", &err));
	OCL_CHECK(err, krnl_cnn_conv_4 = cl::Kernel(program, "cnn_four", &err));
    valid_device++;
}

if (valid_device == 0) {
std::cout << "Failed to program any device found, exit!\n";
exit(EXIT_FAILURE);
}

OCL_CHECK(err,
          cl::Buffer buffer_image_1(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  output_size_bytes_1,
									output_1_1.data(),
                                    &err));

OCL_CHECK(err,
          cl::Buffer buffer_image_2(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  output_size_bytes_1,
									output_1_2.data(),
                                    &err));

OCL_CHECK(err,
          cl::Buffer buffer_image_3(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  output_size_bytes_1,
									output_1_3.data(),
                                    &err));

OCL_CHECK(err,
          cl::Buffer buffer_image_4(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  output_size_bytes_1,
									output_1_4.data(),
                                    &err));

OCL_CHECK(err,
          cl::Buffer buffer_weight_1(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  weight_size_bytes_hw,
									weights_hw_1.data(),
                                    &err));

OCL_CHECK(err,
          cl::Buffer buffer_weight_2(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  weight_size_bytes_hw,
									weights_hw_2.data(),
                                    &err));

OCL_CHECK(err,
          cl::Buffer buffer_weight_3(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  weight_size_bytes_hw,
									weights_hw_3.data(),
                                    &err));

OCL_CHECK(err,
          cl::Buffer buffer_weight_4(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  weight_size_bytes_hw,
									weights_hw_4.data(),
                                    &err));

OCL_CHECK(err,
          cl::Buffer buffer_avg_1(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  output_size_bytes_1,
				  output_2_1.data(),
                                    &err));
OCL_CHECK(err,
          cl::Buffer buffer_avg_2(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  output_size_bytes_1,
				  output_2_2.data(),
                                    &err));

OCL_CHECK(err,
          cl::Buffer buffer_avg_3(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  output_size_bytes_1,
				  output_2_3.data(),
                                    &err));
OCL_CHECK(err,
          cl::Buffer buffer_avg_4(context,
        		  CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
				  output_size_bytes_1,
				  output_2_4.data(),
                                    &err));

krnl_cnn_conv_1.setArg(0, buffer_image_1);
krnl_cnn_conv_1.setArg(1, buffer_weight_1);
krnl_cnn_conv_1.setArg(2, buffer_avg_1);
krnl_cnn_conv_1.setArg(3, 0);

krnl_cnn_conv_2.setArg(0, buffer_image_2);
krnl_cnn_conv_2.setArg(1, buffer_weight_2);
krnl_cnn_conv_2.setArg(2, buffer_avg_2);
krnl_cnn_conv_2.setArg(3, 0);

krnl_cnn_conv_3.setArg(0, buffer_image_3);
krnl_cnn_conv_3.setArg(1, buffer_weight_3);
krnl_cnn_conv_3.setArg(2, buffer_avg_3);
krnl_cnn_conv_3.setArg(3, 0);

krnl_cnn_conv_4.setArg(0, buffer_image_4);
krnl_cnn_conv_4.setArg(1, buffer_weight_4);
krnl_cnn_conv_4.setArg(2, buffer_avg_4);
krnl_cnn_conv_4.setArg(3, 0);

vector<cl::Event> migrateEvent(4);

q_1.enqueueMigrateMemObjects({buffer_image_1},0/* 0 means from host*/, NULL, &migrateEvent[0]);
q_2.enqueueMigrateMemObjects({buffer_image_2},0/* 0 means from host*/, NULL, &migrateEvent[1]);
q_3.enqueueMigrateMemObjects({buffer_image_3},0/* 0 means from host*/, NULL, &migrateEvent[2]);
q_4.enqueueMigrateMemObjects({buffer_image_4},0/* 0 means from host*/, NULL, &migrateEvent[3]);

cl::Event::waitForEvents(migrateEvent);

q_1.enqueueMigrateMemObjects({buffer_image_1},0/* 0 means from host*/, NULL, &migrateEvent[0]);
q_2.enqueueMigrateMemObjects({buffer_image_2},0/* 0 means from host*/, NULL, &migrateEvent[1]);
q_3.enqueueMigrateMemObjects({buffer_image_3},0/* 0 means from host*/, NULL, &migrateEvent[2]);
q_4.enqueueMigrateMemObjects({buffer_image_4},0/* 0 means from host*/, NULL, &migrateEvent[3]);

cl::Event::waitForEvents(migrateEvent);

uint64_t duration = 0;
auto kernel_start_1 = std::chrono::high_resolution_clock::now();

printf("Hardware command enqueue.\n");
vector<cl::Event> kernel_events(4);
q_1.enqueueTask(krnl_cnn_conv_1, NULL, &kernel_events[0]);
std::cout << "enqueue 1" << std::endl;
q_2.enqueueTask(krnl_cnn_conv_2, NULL, &kernel_events[1]);
std::cout << "enqueue 2" << std::endl;
q_3.enqueueTask(krnl_cnn_conv_3, NULL, &kernel_events[2]);
std::cout << "enqueue 3" << std::endl;
q_4.enqueueTask(krnl_cnn_conv_4, NULL, &kernel_events[3]);
std::cout << "enqueue 4" << std::endl;

std::cout << "Start hardware kernel" << std::endl;
cl::Event::waitForEvents(kernel_events);
auto kernel_end_1 = std::chrono::high_resolution_clock::now();
auto kernel_time_1 = std::chrono::duration<uint64_t, std::nano>(kernel_end_1 - kernel_start_1);
duration =  kernel_time_1.count();

q_1.enqueueMigrateMemObjects({buffer_avg_1},CL_MIGRATE_MEM_OBJECT_HOST, NULL, &migrateEvent[0]);
q_2.enqueueMigrateMemObjects({buffer_avg_2},CL_MIGRATE_MEM_OBJECT_HOST, NULL, &migrateEvent[1]);
q_3.enqueueMigrateMemObjects({buffer_avg_3},CL_MIGRATE_MEM_OBJECT_HOST, NULL, &migrateEvent[2]);
q_4.enqueueMigrateMemObjects({buffer_avg_4},CL_MIGRATE_MEM_OBJECT_HOST, NULL, &migrateEvent[3]);
cl::Event::waitForEvents(migrateEvent);



printf("start pthread for sw layers (after)\n");

printf("start aver_pool\n");
auto start_aver_pool = std::chrono::high_resolution_clock::now();

aver_pool_2_arg_t arg_aver_pool_2[4];

for (idx = 0; idx < 4; idx++) {
	arg_aver_pool_2[idx].i_chan = 1000;
	arg_aver_pool_2[idx].o_chan = 1000;
	arg_aver_pool_2[idx].i_size = 13;
	arg_aver_pool_2[idx].o_size= 1;
	arg_aver_pool_2[idx].w_size = 2;
	arg_aver_pool_2[idx].stride = 2;
	arg_aver_pool_2[idx].padding = 0;
	arg_aver_pool_2[idx].relu_on= 0;
}

arg_aver_pool_2[0].in_vector = output_2_1.data();
arg_aver_pool_2[0].out_vector = output_1_1.data();

arg_aver_pool_2[1].in_vector = output_2_2.data();
arg_aver_pool_2[1].out_vector = output_1_2.data();

arg_aver_pool_2[2].in_vector = output_2_3.data();
arg_aver_pool_2[2].out_vector = output_1_3.data();

arg_aver_pool_2[3].in_vector = output_2_4.data();
arg_aver_pool_2[3].out_vector = output_1_4.data();

pthread_create(&tid1, NULL, aver_pool_2, &arg_aver_pool_2[0]);
pthread_create(&tid2, NULL, aver_pool_2, &arg_aver_pool_2[1]);
pthread_create(&tid3, NULL, aver_pool_2, &arg_aver_pool_2[2]);
pthread_create(&tid4, NULL, aver_pool_2, &arg_aver_pool_2[3]);
    
// Wait for all the threads to end
pthread_join(tid1, NULL);
pthread_join(tid2, NULL);
pthread_join(tid3, NULL);
pthread_join(tid4, NULL);

auto end_aver_pool = std::chrono::high_resolution_clock::now();
auto kernel_end_2 = std::chrono::high_resolution_clock::now();
printf("end aver_pool\n");
auto aver_time = std::chrono::duration<uint64_t, std::nano>(end_aver_pool - start_aver_pool);
uint64_t aver_duration =  aver_time.count();
std::cout << "args_aver_pool duration = " << aver_duration << " ns" << std::endl;

datatype_inh max2_1 = output_1_1[0];
int prediction_1 = 0;
        for (int i = 0; i < 1000; i++){
                if(max2_1<output_1_1[i]){
                        prediction_1 = i;
                        max2_1 = output_1_1[i];
                }

        }
        printf("The prediction of image 1 in round %d is %d\n", round+1, prediction_1);

datatype_inh max2_2 = output_1_2[0];
int prediction_2 = 0;
        for (int i = 0; i < 1000; i++){
                if(max2_2<output_1_2[i]){
                        prediction_2 = i;
                        max2_2 = output_1_2[i];
                }

        }
        printf("The prediction of image 2 in round %d is %d\n", round+1, prediction_2);

datatype_inh max2_3 = output_1_3[0];
int prediction_3 = 0;
        for (int i = 0; i < 1000; i++){
                if(max2_3<output_1_3[i]){
                        prediction_3 = i;
                        max2_3 = output_1_3[i];
                }

        }
        printf("The prediction of image 3 in round %d is %d\n", round+1, prediction_3);

datatype_inh max2_4 = output_1_4[0];
int prediction_4 = 0;
        for (int i = 0; i < 1000; i++){
                if(max2_4<output_1_4[i]){
                        prediction_4 = i;
                        max2_4 = output_1_4[i];
                }

        }
        printf("The prediction of image 4 in round %d is %d\n", round+1, prediction_4);


auto kernel_time_2 = std::chrono::duration<uint64_t, std::nano>(kernel_end_2 - kernel_start_2);
good_duration_2 =  kernel_time_2.count();
std::cout << "Hardware duration = " << duration << " ns" << std::endl;
std::cout << "Overall duration in one round = " << good_duration_2 << " ns" << std::endl;
}
auto total_time_end = std::chrono::high_resolution_clock::now();
auto total_time = std::chrono::duration<uint64_t, std::nano>(total_time_end - total_time_start);
total_duration = total_time.count();
std::cout << "Total time = " << total_duration << " ns" << std::endl;

return 0;
}
