import caffe
import numpy as np
import argparse
import os
from tempfile import TemporaryFile

def extract_caffe_model(model, weights, output_path):
  """extract caffe model's parameters to numpy array, and write them to files
  Args:
    model: path of '.prototxt'
    weights: path of '.caffemodel'
    output_path: output path of numpy params 
  Returns:
    None
  """
  net = caffe.Net(model, caffe.TEST)
  net.copy_from(weights)

  if not os.path.exists(output_path):
    os.makedirs(output_path)

  output = np.array([])  
  for item in net.params.items():
    name, layer = item
    print('convert layer: ' + name)

    num = 0 
    for p in net.params[name]:
      np.save(output_path + '/' + str(num) + '_' + str(name) + '_' + str(num), p.data)
      load_data = np.load(output_path + '/' + str(num) + '_' + str(name) + '_' + str(num) + '.npy')
      output = np.append(output, load_data.flatten())
      #np.savetxt(str(num)+'.txt',load_data.flatten() , delimiter=' ',fmt ='%f')
      num += 1
    output = output.flatten()
    #print(output.ravel())
    np.savetxt("linear_weights.txt",output , delimiter=' ',fmt ='%f')



if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument("--model", help="model prototxt path .prototxt")
  parser.add_argument("--weights", help="caffe model weights path .caffemodel")
  parser.add_argument("--output", help="output path")
  args = parser.parse_args()
  extract_caffe_model(args.model, args.weights, args.output)
