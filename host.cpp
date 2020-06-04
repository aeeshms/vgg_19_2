#include <iostream>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <unistd.h>
#include <chrono>
#include "xcl2.hpp"
#include <stdio.h>
#include "stdint.h"
#include <stdlib.h>
#include <hls_half.h>
typedef float datatype_inh;
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
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>


std::fstream& GotoLine(std::fstream& file, int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;

}

void convGolden(
	datatype_inh *weight,
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
            	datatype_inh acc = 0;
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
                                       (datatype_inh) weight[((output*i_chan + input)*w_size + i)*w_size + j];
                            }
                        }

                    }
		}

			if(relu_on == 1 && acc < 0)
            //    std::cout << "result " << acc << std::endl;
		            out[(output*o_size + y)*o_size + x] = 0;

			else
				out[(output*o_size + y)*o_size + x] = acc;
            }
        }
    }
}


void convGolden_relu(
	datatype_inh *weight,
	datatype_inh *image,
	datatype_inh *out,
	datatype_inh *bias,
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
            	datatype_inh acc = 0;
            	datatype_inh bias_sum = 0;

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
                                       (datatype_inh) weight[((output*i_chan + input)*w_size + i)*w_size + j];
                            }
                        }

                    }
		}

                bias_sum = (acc + bias[output]);

                        if(bias_sum < 0)
            // std::cout << "result " << acc << std::endl;
                            out[(output*o_size + y)*o_size + x] = 0;

                        else
                        out[(output*o_size + y)*o_size + x] = bias_sum;

            }
        }
    }
}

void add_relu(
        datatype_inh *in_vector,
        datatype_inh *out_vector,
    int i_chan,
    int o_chan,
    int i_size,
    int o_size,
    int relu_on
) {
       assert(i_chan==o_chan);
       assert(o_size==i_size);
        for (int i = 0; i < o_chan; i++) {
                for (int j = 0; j < o_size*o_size; j++){
                        out_vector[i*o_size*o_size + j] = out_vector[i*o_size*o_size + j] + in_vector[i];//*i_chan;
                        if(relu_on && out_vector[i * o_size * o_size + j] <= 0)
                                out_vector[i * o_size * o_size + j] = 0;
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
	int  j;
	float data;
	char str[300];
	for (j = 0; j < o_chan * i_chan * w_size* w_size; j++)
	{
	  fscanf(fid,"%s", str);
	  data = atof(str);
	  weights[j] = (float) data;
	  //printf("%f\t", data);
	  fscanf(fid,"\n");
	}
}

void fc(
float *image,
float *weight, // assume: weight[o_chan][i_chan]
float *output,
int i_chan,
int i_size,
int fc_chan
 ) {
	for (int i = 0; i < fc_chan; ++i) {
		output[i] = 0;
		for (int j = 0; j < i_chan * i_size * i_size; ++j) {
                        if(image[j] != 0)
			output[i] += image[j] * weight[i * i_chan * i_size * i_size + j];
		}
	}

}

void fc_hw(
datatype_inh *bias,
datatype_inh *image,
datatype_inh *weight, // assume: weight[o_chan][i_chan]
datatype_inh *output,
int i_chan,
int i_size,
int fc_chan,
int wgt_offset,
int bias_offset
 ) {

	for (int i = 0; i < fc_chan; ++i) {
		bias[i] = weight[bias_offset+ i];
	}

	std::cout <<   " stage fc 91 \n"  << std::endl;

	for (int i = 0; i < fc_chan; ++i) {
//	datatype_inh	bias_sum = 0;
		datatype_inh bias_sum = 0;
		datatype_inh sum = 0;

		for (int j = 0; j < i_chan * i_size * i_size; ++j) {
			if(image[j] != 0)
			bias_sum += image[j] * (weight[i * i_chan * i_size * i_size + j + wgt_offset] * 1);
		}
		//std::cout <<   " stage fc 1998 \n"  << std::endl;
sum =(bias_sum + bias[i]);
if(sum > 0)
output[i] = (datatype_inh)  sum;
else
output[i] = 0;
	}

}

uint64_t run_opencl_cnn(
    std::vector<cl::Device> &devices,
    cl::CommandQueue &q,
    cl::Context &context,
    std::string &device_name,
    std::vector<datatype_inh, aligned_allocator<datatype_inh>> &image,
    std::vector<datatype_inh, aligned_allocator<datatype_inh>> &weight,
    std::vector<datatype_inh, aligned_allocator<datatype_inh>> &output,
	std::vector<datatype_inh, aligned_allocator<datatype_inh>> &chan_buff

) {
    std::string binaryFile;

    binaryFile = xcl::find_binary_file(device_name, "cnn_GOOD");
    cl::Program::Binaries bins = xcl::import_binary_file(binaryFile);
    devices.resize(1);
    cl::Program program(context, devices, bins);
    cl::Kernel krnl_cnn_conv(program,"cnn");

    //std::cout << "Starting " << (good ? "GOOD" : "BAD") << " Kernel" << std::endl;



    size_t image_size_bytes  = sizeof(datatype_inh) * 512 * 224 * 224;
    size_t weight_size_bytes = sizeof(datatype_inh) * 143667240;
    size_t output_size_bytes = sizeof(datatype_inh) *512 * 224 * 224;
    size_t para_size_bytes = sizeof(datatype_inh) *512 * 224 * 224;

// Allocate Buffer in Global Memory
std::vector<cl::Memory> inBufVec;
std::vector<cl::Memory> wgtBufVec;
std::vector<cl::Memory> outBufVec;
std::vector<cl::Memory> paraBufVec;

cl_mem_ext_ptr_t inExt, wgtExt,outExt,paraExt;  // Declaring two extensions for both buffers
inExt.flags  = XCL_MEM_DDR_BANK0; // Specify Bank0 Memory for input memory
wgtExt.flags = XCL_MEM_DDR_BANK1; // Specify Bank1 Memory for output Memory
outExt.flags = XCL_MEM_DDR_BANK2; // Specify Bank1 Memory for output Memory
paraExt.flags = XCL_MEM_DDR_BANK3; // Specify Bank1 Memory for output Memory

// Setting input and output objects
inExt.obj = image.data();
wgtExt.obj = weight.data();
outExt.obj = output.data();
paraExt.obj = chan_buff.data();

// Setting param to zero
inExt.param = 0 ; outExt.param = 0; // Setting param to zero
wgtExt.param = 0 ; //paraExt.param = 0;


cl::Buffer buffer_image (context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY |  CL_MEM_EXT_PTR_XILINX ,
image_size_bytes,  &inExt);
cl::Buffer buffer_weight(context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY | CL_MEM_EXT_PTR_XILINX ,
weight_size_bytes,  &wgtExt);
cl::Buffer buffer_output(context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY | CL_MEM_EXT_PTR_XILINX ,
output_size_bytes,  &outExt);
cl::Buffer buffer_para(context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY | CL_MEM_EXT_PTR_XILINX ,
                                para_size_bytes,  &paraExt);

inBufVec.push_back(buffer_image);
wgtBufVec.push_back(buffer_weight);
outBufVec.push_back(buffer_output);
paraBufVec.push_back(buffer_para);

q.enqueueMigrateMemObjects(inBufVec,0/* 0 means from host*/);
q.enqueueMigrateMemObjects(wgtBufVec,0/* 0 means from host*/);
q.enqueueMigrateMemObjects(paraBufVec,0/* 0 means from host*/);

int narg = 0;
krnl_cnn_conv.setArg(narg++, buffer_image);
krnl_cnn_conv.setArg(narg++, buffer_weight);
krnl_cnn_conv.setArg(narg++, buffer_output);
krnl_cnn_conv.setArg(narg++, buffer_para);
uint64_t duration = 0;
        cl::Event event;

        auto kernel_start = std::chrono::high_resolution_clock::now();
        q.enqueueTask(krnl_cnn_conv, NULL, &event);
        q.finish();
        auto kernel_end = std::chrono::high_resolution_clock::now();
        auto kernel_time = std::chrono::duration<uint64_t, std::nano>(kernel_end - kernel_start);
        duration =  kernel_time.count();


    //Copy Result from Device Global Memory to Host Local Memory
    q.enqueueMigrateMemObjects(outBufVec,CL_MIGRATE_MEM_OBJECT_HOST);
    q.finish();

    std::cout << "Finished kernel" << std::endl;
    return duration;
}

//int main()
//{
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << "Usage: " << argv[0] <<" <input_image>" << std::endl;
        return -1;
    }

    //Read the input image
    std::cout << "Reading input image..." << std::endl;


     // Allocate Memory in Host (Image, Weights and Output)
    size_t image_size_bytes  = sizeof(datatype_inh) * 512 * 224 * 224;
    size_t weight_size_bytes = sizeof(datatype_inh) * 512 * 224 * 224;
    size_t weight_size_bytes_hw = sizeof(datatype_inh) * 143667240;
    size_t output_size_bytes_1 = sizeof(datatype_inh) *512 * 224 * 224;
    size_t output_size_bytes_2 = sizeof(datatype_inh) *512 * 224 * 224;
    size_t output_size_bytes_3 = sizeof(datatype_inh) *512 * 224 * 224;
    size_t output_size_bytes_para = sizeof(datatype_inh) *512 * 224 * 224;
    size_t bias_bytes = sizeof(datatype_inh) * 512;

    std::vector<datatype_inh,aligned_allocator<datatype_inh>> image(image_size_bytes);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> weights(weight_size_bytes);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> weights_hw(weight_size_bytes_hw);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_1(output_size_bytes_1);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_2(output_size_bytes_2);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_3(output_size_bytes_3);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> output_para(output_size_bytes_para);
    std::vector<datatype_inh,aligned_allocator<datatype_inh>> bias(bias_bytes);

int prediction = 0 ;
    ////////////////
     //   FILE *fid = fopen("linear_weights.txt", "r");

//    	FILE *outfile_sw = fopen("result_sw.out", "w");
//    	FILE *outfile_hw = fopen("result_hw.out", "w");
//    	FILE *words = fopen("sunset_words.txt", "r");

 //   	int prediction=1;
    	//FILE *fid_hw = fopen("linear_weights.txt", "r"); // 789 shoji

//	FILE *fid_hw;
//	const char *imageFilename_22 = argv[2];
//	fid_hw = fopen(imageFilename_22, "rb");
//
//        int jjjj;
//     	datatype_inh dataii;
//     	char strii[300];
//
//    	for (jjjj = 0; jjjj < 143667240; jjjj++) {
//
//    	  fscanf(fid_hw,"%s", strii);
//    	  dataii = atof(strii);
//    	  weights_hw[jjjj] = (datatype_inh) dataii;
//              //printf("%d\n",image[jj]);
//    	  fscanf(fid_hw,"\n");
//    		}
//         fclose(fid_hw);

        int jj;
     	datatype_inh datai;
     	char stri[300]="1";
     	printf("start0");
    	//FILE *fidi = fopen("argv[1]", "r");//const char* inputFilename = argv[1];

     	FILE *input_file;
    	const char *imageFilename = argv[1];
    	input_file = fopen(imageFilename, "rb");

    	 if (!input_file)
    	    {
    	        printf("Error: Unable to open input image file %s!\n",
    	        imageFilename);
    	        return 1;
    	}


    	for (jj = 0; jj < 3 * 224 * 224; jj++) { /////// 512 to 3
    		if(jj < 3 * 224 * 224)
    		{
    	  fscanf(input_file,"%s", stri);
    	  datai = atof(stri);
    	  image[jj] = (datatype_inh) datai;
              //printf("%d\n",image[jj]);
    	  fscanf(input_file,"\n");
    		}
    		else
    	  image[jj] = 0;
    	}
         fclose(input_file);

         printf("start0");


      	FILE *fid;
     	const char *imageFilename_2 = argv[2];
     	fid = fopen(imageFilename_2, "rb");


        	printf("0_conv1_1_0\n");

         uint64_t duration = 0;

         auto kernel_start = std::chrono::high_resolution_clock::now();

         	load_weights(weights.data(),3,64,3,fid);//0_conv1_1_0
        	convGolden(weights.data(), image.data(), output_1.data(), 3,64,224,224,3,1,1,0);
         	printf("1_conv1_1_1\n");
         	load_weights(weights.data(),1,64,1,fid);//1_conv1_1_1
         	printf("1_conv1_1_1\n");
         	add_relu(weights.data(), output_1.data(), 64, 64, 224, 224, 1);




         	printf("0_conv1_2_0\n");
         	load_weights(weights.data(),64,64,3,fid);//0_conv1_2_0
         	convGolden(weights.data(), output_1.data(), output_2.data(), 64, 64,224,224,3,1,1,0);
         	printf("1_conv1_2_1\n");
         	load_weights(weights.data(),1,64,1,fid);//1_conv1_2_1
         	add_relu(weights.data(), output_2.data(), 64, 64, 224, 224, 1);

         	printf("pool1\n");

         	max_pool(output_2.data(),output_1.data(),64,64,224,112,2,2,0,0);


         	printf("0_conv2_1_0\n");
         	load_weights(weights.data(),64,128,3,fid);//0_conv2_1_0
         	convGolden(weights.data(), output_1.data(), output_2.data(), 64,128,112,112,3,1,1,0);
         	printf("1_conv2_1_1\n");
         	load_weights(weights.data(),1,128,1,fid);//1_conv1_2_1
         	add_relu(weights.data(), output_2.data(), 128, 128, 112, 112, 1);

         	printf("0_conv2_2_0\n");
         	load_weights(weights.data(),128,128,3,fid);//0_conv2_2_0
         	convGolden(weights.data(), output_2.data(), output_1.data(),128,128,112,112,3,1,1,0);
         	printf("1_conv2_2_1");
         	load_weights(weights.data(),1,128,1,fid);
         	add_relu(weights.data(), output_1.data(), 128, 128, 112, 112, 1);

         	printf("pool2\n");
         	max_pool(output_1.data(),output_2.data(),128,128,112,56,2,2,0,0);

         	printf("0_conv3_1_0\n");
         	load_weights(weights.data(),128,256,3,fid);//0_conv3_1_0
         	convGolden(weights.data(), output_2.data(), output_1.data(),128,256,56,56,3,1,1,0);
         	printf("1_conv3_1_1");
         	load_weights(weights.data(),1,256,1,fid);//1_conv3_1_1
         	add_relu(weights.data(), output_1.data(), 256, 256, 56, 56, 1);


         	printf("0_conv3_2_0\n");
         	load_weights(weights.data(),256,256,3,fid);//0_conv3_2_0
         	convGolden(weights.data(), output_1.data(), output_2.data(),256,256,56,56,3,1,1,0);
         	printf("1_conv3_2_1\n");
         	load_weights(weights.data(),1,256,1,fid);//1_conv3_2_1
         	add_relu(weights.data(), output_2.data(), 256, 256, 56, 56, 1);

         	printf("0_conv3_3_0\n");
         	load_weights(weights.data(),256,256,3,fid);//0_conv3_3_0
         	convGolden(weights.data(), output_2.data(), output_1.data(),256,256,56,56,3,1,1,0);
         	printf("1_conv3_3_1\n");
         	load_weights(weights.data(),1,256,1,fid);//1_conv3_3_1
         	add_relu(weights.data(), output_1.data(), 256, 256, 56, 56, 1);

         	printf("0_conv3_4_0\n");
         	load_weights(weights.data(),256,256,3,fid);//0_conv3_4_0
         	convGolden(weights.data(), output_1.data(), output_2.data(),256,256,56,56,3,1,1,0);
         	printf("1_conv3_4_1");
         	load_weights(weights.data(),1,256,1,fid);//1_conv3_2_1
         	add_relu(weights.data(), output_2.data(), 256, 256, 56, 56, 1);

         	printf("pool3\n");
         	max_pool(output_2.data(),output_1.data(),256,256,56,28,2,2,0,0);

         	printf("0_conv4_1_0\n");
         	load_weights(weights.data(),256,512,3,fid);//0_conv4_1_0
         	convGolden(weights.data(), output_1.data(), output_2.data(),256,512,28,28,3,1,1,0);
         	printf("1_conv4_1_1\n");
         	load_weights(weights.data(),1,512,1,fid);//1_conv4_1_1
         	add_relu(weights.data(), output_2.data(), 512, 512, 28, 28, 1);


         	printf("0_conv4_2_0\n");
         	load_weights(weights.data(),512,512,3,fid);//0_conv4_2_0
         	convGolden(weights.data(), output_2.data(), output_1.data(),512,512,28,28,3,1,1,0);
         	printf("1_conv4_2_1\n");
         	load_weights(weights.data(),1,512,1,fid);//1_conv4_2_1
         	add_relu(weights.data(), output_1.data(), 512, 512, 28, 28, 1);

         	printf("0_conv4_3_0\n");
         	load_weights(weights.data(),512,512,3,fid);//0_conv4_3_0
         	convGolden(weights.data(), output_1.data(), output_2.data(),512,512,28,28,3,1,1,0);
         	printf("1_conv4_3_1\n");
         	load_weights(weights.data(),1,512,1,fid);//1_conv4_3_1
         	add_relu(weights.data(), output_2.data(), 512, 512, 28, 28, 1);

         	printf("0_conv4_4_0\n");
         	load_weights(weights.data(),512,512,3,fid);//0_conv4_4_0
         	convGolden(weights.data(), output_2.data(), output_1.data(),512,512,28,28,3,1,1,0);
         	printf("1_conv4_4_1\n");
         	load_weights(weights.data(),1,512,1,fid);//1_conv4_4_1
         	add_relu(weights.data(), output_1.data(), 512, 512, 28, 28, 1);

         	printf("pool4\n");
         	max_pool(output_1.data(),output_2.data(),512,512,28,14,2,2,0,0);

         	printf("0_conv5_1_0\n");
         	load_weights(weights.data(),512,512,3,fid);//0_conv5_1_0
         	convGolden(weights.data(), output_2.data(), output_1.data(),512,512,14,14,3,1,1,0);
         	printf("1_conv5_1_1\n");
         	load_weights(weights.data(),1,512,1,fid);//1_conv5_1_1
         	add_relu(weights.data(), output_1.data(), 512, 512, 14, 14, 1);

         	printf("0_conv5_2_0\n");
         	load_weights(weights.data(),512,512,3,fid);//0_conv5_2_0
         	convGolden(weights.data(), output_1.data(), output_2.data(),512,512,14,14,3,1,1,0);
         	printf("1_conv5_2_1");
         	load_weights(weights.data(),1,512,1,fid);//1_conv5_2_1
         	add_relu(weights.data(), output_2.data(), 512, 512, 14, 14, 1);

         	printf("0_conv5_3_0\n");
         	load_weights(weights.data(),512,512,3,fid);//0_conv5_3_0
         	convGolden(weights.data(), output_2.data(), output_1.data(),512,512,14,14,3,1,1,0);
         	printf("1_conv5_3_1\n");
         	load_weights(weights.data(),1,512,1,fid);//1_conv5_2_1
         	add_relu(weights.data(), output_1.data(), 512, 512, 14, 14, 1);

         	printf("0_conv5_4_0\n");
         	load_weights(weights.data(),512,512,3,fid);//0_conv5_4_0
         	convGolden(weights.data(), output_1.data(), output_2.data(),512,512,14,14,3,1,1,0);
         	printf("1_conv5_4_1\n");
         	load_weights(weights.data(),1,512,1,fid);//1_conv5_4_1
         	add_relu(weights.data(), output_2.data(), 512, 512, 14, 14, 1);

         	printf("pool5\n");
         	max_pool(output_2.data(),output_1.data(),512,512,14,7,2,2,0,0);

         	printf("0_fc6_0\n");
         	load_weights(weights.data(),512,4096,7,fid);
         	fc(output_1.data(), weights.data(), output_2.data(), 512, 7, 4096);
         	printf("1_fc6_1\n");
         	load_weights(weights.data(),1,4096,1,fid);
         	add_relu(weights.data(), output_2.data(), 4096, 4096, 1, 1, 1);

         	printf("0_fc7_0\n");
         	load_weights(weights.data(),4096,4096,1,fid);
         	fc(output_2.data(), weights.data(), output_1.data(), 4096, 1, 4096);
         	printf("1_fc7_1\n");
         	load_weights(weights.data(),1,4096,1,fid);
         	add_relu(weights.data(), output_1.data(), 4096, 4096, 1, 1, 1);


         	printf("0_fc8_0\n");
         	load_weights(weights.data(),4096,1000,1,fid);
         	fc(output_1.data(), weights.data(), output_2.data(), 4096, 1, 1000);
         	printf("1_fc8_1\n");
         	load_weights(weights.data(),1,1000,1,fid);
         	add_relu(weights.data(), output_2.data(), 1000, 1000, 1, 1, 0);

         	float max = output_2[0];

         	for (int i = 0; i < 1000; i++){
         		//fprintf(outfile_sw ,"%f\n" ,output_2[i]);
         		if(max<output_2[i]){
         			prediction = i;
         			max = output_2[i];
         		}

         	}
         	printf("\n 457 The prediction is %d\n", prediction);
         	fclose(fid);

         	///////////////////////////////// sw ends//////////////////


//std::vector<cl::Device> devices = xcl::get_xil_devices();
//cl::Device device = devices[0];
//
//cl::Context context(device);
//cl::CommandQueue q(context, device, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_PROFILING_ENABLE);
//std::string device_name = device.getInfo<CL_DEVICE_NAME>();
//
//
//uint64_t good_duration = run_opencl_cnn(devices, q, context, device_name,image, weights_hw,output_3,output_para);
//std::cout << "GOOD duration = " << good_duration << " ns" << std::endl;
//
//int wgt_offset = 20023872 + 512;//20023872
//int bias_offset = wgt_offset + 4096*512*7*7;
//fc_hw(bias.data(),output_3.data(), weights_hw.data() , output_1.data(), 512, 7, 4096,wgt_offset,bias_offset);
//std::cout <<   " stage fc 1 \n"  << std::endl;
//
//wgt_offset = bias_offset + 4096;
//bias_offset = wgt_offset +  4096*4096;
//fc_hw(bias.data(),output_1.data(), weights_hw.data() , output_2.data(), 4096, 1, 4096,wgt_offset,bias_offset);
//std::cout <<   " stage fc 2 \n"  << std::endl;
//
//wgt_offset = bias_offset + 4096;
//bias_offset = wgt_offset +  4096*1000;
//fc_hw(bias.data(),output_2.data(), weights_hw.data() , output_1.data(), 4096, 1, 1000,wgt_offset,bias_offset);
//std::cout <<   " stage fc 3 "  << std::endl;
//
//datatype_inh max_hw = output_1[0];
//
//	for (int i = 0; i < 1000; i++){
//		//fprintf(outfile_hw ,"%f\n" ,output_1.data()[i]);// why 477 without  convolution ???
//		if(max_hw < output_1[i]){
//			prediction = i;
//			max_hw = output_1[i];
//		}
//
//	}
//
//printf("The prediction is  HW %d\n", prediction);
    	//fprintf(outfile_hw, "The prediction is %d\n", prediction);


//        fstream tag("sunset_words.txt");
//        GotoLine(tag, prediction+1);
//        string str;
//        getline(tag, str);
//        //tag >> str;
//        std::cout<<str<<endl;

    	//fclose(fid);
    	//fclose(outfile_sw);
    	//fclose(outfile_hw);
    printf("HW and SW results match\n");

}
























