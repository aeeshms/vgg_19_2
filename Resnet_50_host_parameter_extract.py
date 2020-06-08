#!/usr/bin/env python2.7

import sys
import struct
import caffe
import time
import numpy as np
import random


file1 = open("testfile.txt",'w');


#coding: utf-8

## Get Input Files
## Auto-Detect .caffemodel and .prototxt files, if only one of each is present
prototxt = "undef"
caffemodels = "undef"
if len(sys.argv) == 3:
    ## Files given via CLI argument
    if (os.path.isfile(sys.argv[1])): prototxt = sys.argv[1]
    if (os.path.isfile(sys.argv[2])): caffemodel = sys.argv[2]
elif len(sys.argv) == 1:
    ## No CLI Arguments, try to auto-detect files
    prototxts = [file for file in os.listdir(".") if file.endswith(".prototxt")]
    caffemodels = [file for file in os.listdir(".") if file.endswith(".caffemodel")]
    if len(prototxts) == 1 and len(caffemodels) == 1:
        prototxt = prototxts[0]
        caffemodel = caffemodels[0]
    else:
        print("Error: Could not auto-detect .prototxt and .caffemodel files.")

## Usage Help if Input Files not Found
if prototxt == "undef" or caffemodel == "undef" :
    print("Usage: %s [<model.prototxt> <snapshot.caffemodel>]" % sys.argv[0])
    exit(-1)
print("Using prototxt: {}, caffemodel: {}".format(prototxt, caffemodel))

# Functions to Reshape and Save given Weight/Bias Blob
def append_filters(weights, blob):
    ch_out = blob.shape[0]
    ch_in = blob.shape[1]
    kernel = blob.shape[2]
    for ci in range(ch_in):
        for co in range(ch_out):
            for ky in range(kernel):
                for kx in range(kernel):
                    weights.append(blob.data[co][ci][kx][ky]) ### BEWARE: X, Y MIGHT BE SWITCHED!
#def append_bias(weights, blob):
#    ch_out = blob.shape[0]
#    for co in range(ch_out):
#        weights.append(blob.data[co])

######
###### Extract C++ Layer Description + Weights
######

start_time = time.clock()

# Load Network from prototxt / caffemodel
caffe.set_mode_cpu() # use CPU for more compatibility
net = caffe.Net(prototxt, caffemodel, caffe.TEST);

# Initialize Helper Variables
weights = []
layer_count = 0
weights_count = 0
weights_cache_needed = 0
image_cache_needed = 0
max_num_chout = 0
max_active_area = 0
max_image_cache = 0
max_dimension = 0
max_channels = 0
total_inputs = 0    # total num. elements read from / written to memory
total_outputs = 0
total_dram_IO = 0   # total num. DRAM accesses (input + output) (data + weights)

# manually initialize width/height for first layer
width_out  = net.blobs['data'].width
height_out = net.blobs['data'].height

# Push all Layer Names into List:
layer_names = list(net._layer_names)
layers = []

#import pdb; pdb.set_trace()

for id,layer_name in enumerate(layer_names):
    # doesn't include input "data": not a layer

    layer  = net.layers[id]
    #print layer.bottom 
    if ((layer.type == "Convolution") or (layer.type == "Pooling") or (layer.type == "ReLU") or (layer.type == "InnerProduct") or (layer.type == "BatchNorm") or (layer.type == "Scale")):

        try:
            params = net.params[layer_name]
        except:
            #print("Layer %d: %s doesn't have any params.\n" % (id,layer_name))
            pass
        try:
            blob   = net.blobs[layer_name]
        except:
            #print("Layer %d: %s doesn't have any blobs.\n" % (id,layer_name))
            pass

        # Trim down Name
        name = layer_name.replace("fire", "f")
        name = name.replace("expand1x1", "e1")
        name = name.replace("expand3x3", "e3")
        name = name.replace("squeeze1x1","s1")
        name = name.replace("squeeze3x3","s3")
        name = name.replace("conv","c")      # conv10 -> c10
        name = name.replace("split1","p1")   # c10/split1 -> c10p1
        name = name.replace("split2","p2")   # c10/split1 -> c10p1

        # Extract Layer Attributes
        width_in  = width_out
        height_in = height_out
        width_out = blob.width
        height_out = blob.height
        ch_out = blob.channels

        # defaults:
        ch_in = 0
        kernel = 0
        stride = 0
        pad = 0
        relu = 0
        is_first_split_layer = 0
        is_second_split_layer = 0
        global_pool = 0
        layer_type_string = "LAYER_DATA"

        # CONV Layer: Extract Specifications, Add to Table
        if (layer.type == "Convolution"):

            # Extract CONV Layer Attributes
            kernel = params[0].shape[3]
            ch_in = params[0].shape[1]

            # Hack: derive stride from input-to-output relation
            stride = width_in/width_out;

            # Hack: derive padding from input-to-output relation
            if (width_in == stride*width_out): pad = (kernel-1)/2
            else: pad = 0

            # For "expand" and "split" layers, need to concat the output
            #    channels. Recognize split layers by their name:
            #    "expand1x1/expand3x3" and "split1/split2".
            if ("expand1x1" in layer_name) or ("split1" in layer_name):
                is_first_split_layer = 1
            if ("expand3x3" in layer_name) or ("split2" in layer_name):
                is_second_split_layer = 1

            # Add Layer to Layer Stack
           # print id,name,type,width_in,height_in,ch_in,ch_out,kernel,pad,stride,relu;

          # file.write("%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d" % id,name,type,width_in,height_in,ch_in,ch_out,kernel,pad,stride,relu);
            file1.write(str(name) +  ',' + str(ch_in) + ',' + str(ch_out) + ',' + str(width_in) + ',' + str(height_out) + ',' + str(kernel) + ',' + str(stride) + ',' + str(pad) + "\n");
            #file1.write('load_weights(weights,bias' + str(kernel) + ',' + str(ch_out) + ',' +  str(kernel) + ',fid,1);');
            #file1.write('convo(weights,bias,image' + str(kernel) + ',' + str(ch_out) + ',' +  str(kernel) + ',fid,1);');

#convGolden(weights,bias, image, output_1, 3,64,224,224,3,1,1,0);

            layers.append({
                'id': id,
                'name': name,
                'type': "LAYER_CONV",
                'width': width_in,
                'height': height_in,
                'ch_in': ch_in,
                'ch_out': ch_out,
                'kernel': kernel,
                'pad': pad,
                'stride': stride,
                'relu': relu,
                'is_first_split_layer': is_first_split_layer,
                'is_second_split_layer': is_second_split_layer,
                'global_pool': 0
            })
            #print layers
            # Count Number of Weights:
            #weights_count += ch_in*ch_out*kernel*kernel + ch_out

            # Append Weights and Biases to List
            #append_filters(weights, params[0])
            #append_bias(weights, params[1])

            # Count Total Number of Layer:
            layer_count = layer_count + 1

            # Update Maximum necessary Cache sizes:
            weights_size = ch_in*ch_out*kernel*kernel + ch_out
            print "layer",name,"weights_size",weights_size
            input_size = ch_in*width_in*height_in
            output_size = ch_out*width_out*height_out
            pixels_per_row = ch_in*width_in;
            image_cache_size = 4*pixels_per_row;
            max_image_cache = max(max_image_cache, input_size)
            weights_cache_needed = max(weights_cache_needed, weights_size)
            image_cache_needed = max(image_cache_size, image_cache_needed)
            max_num_chout = max(ch_out, max_num_chout)
            max_active_area = max(ch_in*kernel*kernel, max_active_area)
            max_dimension = max(max_dimension, max(width_in, height_in))
            max_channels = max(max_channels, max(ch_in, ch_out))
            total_inputs = total_inputs + ch_in*width_in*height_in
            total_outputs = total_outputs + ch_out*width_out*height_out
            total_dram_IO = total_dram_IO + input_size + output_size + weights_size

        # POOLING LAYERS:
        # Modify Previous CONV Layer to add Pooling
        if (layer.type == "Pooling"):
            ch_in = blob.channels

            # Get Pooling Parameters
            #kernel = params[0].shape[3]
	    #print kernel
            stride = width_in/width_out
            pool_type = "POOL_UNKNOWN"

            # Calculate Pooling Type
            # Actually only "POOL_GLOBAL" is currently supported on FPGA
            if (kernel == 3 and stride == 2):
                pool_type = "POOL_3x3S2"
                #raise ValueError("FOUND UNSUPPORTED POOL_3x3S2")
            elif (kernel == 2 and stride == 2):
                pool_type = "POOL_2x2S2"
                raise ValueError("FOUND UNSUPPORTED POOL_2x2S2")
            elif (kernel == 1 and stride == width_in):
                pool_type = "POOL_GLOBAL"

            # Modify last CONV layer(s) to add Pooling...
            last_conv_layers = [layers.pop()]

            # If last layer = "split" layer, fetch it's twin as well...
            # Recognize Split layers by name:
            ll = last_conv_layers[0]['name']
            if ("e1" in ll) or ("e3" in ll) or ("p1" in ll) or ("p2" in ll):
                last_conv_layers.append(layers.pop())

            # Set layer pooling parameter
            for convlayer in reversed(last_conv_layers):
                if pool_type == "POOL_GLOBAL":
                    convlayer['global_pool'] = 1
                layers.append(convlayer)
           # print id,name,type,width_in,height_in,ch_in,ch_out,kernel,pad,stride;
            file1.write(str(name) + ','  + str(ch_in) + ','  + str(ch_in) + ',' + str(width_in) + ',' + str(height_out) + ',' + str(kernel) + ',' + str(stride) + ',' + str(relu) + "\n");

        # ReLU LAYERS:
        # Modify Previous CONV Layer to add ReLU
        if (layer.type == "ReLU"):

            # Modify last CONV layer(s) to add ReLU...
            last_conv_layer = layers.pop()

            # Set layer ReLU parameter
            last_conv_layer['relu'] = 1

            # Re-Add to List
            layers.append(last_conv_layer)
	if (layer.type == "InnerProduct"):
            ch_in = blob.channels
	    #ch_in = params[0].shape[1]
	    ch_out = params[0].shape[0]
            # Get Pooling Parameters
            #kernel = params[0].shape[3]

	    print id,name,type,width_in,height_in,ch_in,ch_out,kernel,pad,stride;
            #file1.write(str(name) + ','  + str(ch_in) + ','  + str(width_in) + ',' + str(height_out) + ',' + str(kernel) + ',' + str(stride) + ',' + str(relu) + "\n");

            file1.write(str(name) + ',' + str(ch_in) + ',' + str(ch_out) + ',' + str(width_in) + ',' + str(height_out) + "\n");

        if (layer.type == "BatchNorm"):
            ch_in = blob.channels
            #ch_in = params[0].shape[1]
            ch_out = params[0].shape[0]
            # Get Pooling Parameters
            #kernel = params[0].shape[3]

            #print id,name,type,width_in,height_in,ch_in,ch_out,kernel,pad,stride;
            #file1.write(str(name) + ','  + str(ch_in) + ','  + str(width_in) + ',' + str(height_out) + ',' + str(kernel) + ',' + str(stride) + ',' + str(relu) + "\n");

            file1.write(str(name) + ',' + str(ch_in) + ',' + str(ch_out) + ',' + str(width_in) + ',' + str(height_out) + "\n");

        if (layer.type == "Scale"):
            ch_in = blob.channels
            #ch_in = params[0].shape[1]
            ch_out = params[0].shape[0]
            # Get Pooling Parameters
            #kernel = params[0].shape[3]

           # print id,name,type,width_in,height_in,ch_in,ch_out,kernel,pad,stride;
            #file1.write(str(name) + ','  + str(ch_in) + ','  + str(width_in) + ',' + str(height_out) + ',' + str(kernel) + ',' + str(stride) + ',' + str(relu) + "\n");

            file1.write(str(name) + ',' + str(ch_in) + ',' + str(ch_out) + ',' + str(width_in) + ',' + str(height_out) + "\n");


# Generate Network Description:

#print layers



#print("Total Operations took %d seconds on CPU." % time_taken)

# ###
