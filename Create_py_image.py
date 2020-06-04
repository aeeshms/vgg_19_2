import numpy as np
import matplotlib.pyplot as plt 
import sys 
import caffe
import time
# Set the right path to your model definition file, pretrained model weights,
# and the image you would like to classify.
MODEL_FILE = 'deploy.prototxt'
PRETRAINED = 'VGG_ILSVRC_19_layers.caffemodel'

# load the model
caffe.set_mode_cpu();
#caffe.set_device(0)
net = caffe.Classifier(MODEL_FILE, PRETRAINED, 'test')
# test on a image
image_path = 'test_image_2.jpeg'
input_image = caffe.io.load_image(image_path)
# make the transformer
transformer = caffe.io.Transformer({'data': net.blobs['data'].data.shape})
transformer.set_transpose('data', (2,0,1))
transformer.set_channel_swap('data', (2,1,0)) # if using RGB instead of BGR
// add mean here
transformer.set_raw_scale('data', 255.0)

net.blobs['data'].reshape(1,3,224,224)
# and formats them for the Caffe net automatically
net.blobs['data'].data[...] = transformer.preprocess('data', input_image)


output_ = net.blobs['data'].data
#print output_.shape
output_ = output_.flatten()
np.savetxt("py_image_2.txt",output_ , delimiter=' ',fmt ='%f')
start_time = time.time()
output = net.forward()
prediction = output['prob'].argmax()
# match the label
label_mapping = np.loadtxt("imagenet1000_clsid_to_human.txt", str, delimiter='\n')
print label_mapping[prediction]
print("--- %s seconds ---" % (time.time() - start_time))
# pred = net.predict([input_image*255])
~                                            
