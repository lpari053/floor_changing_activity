import onnxmltools
import onnx
from tensorflow.keras.models import load_model
import tensorflow as tf
import keras2onnx
# Charger le modèle Keras sauvegardé
net = load_model('activity.keras')

onnx_model = keras2onnx.convert_keras(net,         # keras model
                         name="example",           # the converted ONNX model internal name                     
                         target_opset=9,           # the ONNX version to export the model to
                         channel_first_inputs=None # which inputs to transpose from NHWC to NCHW
                         )

onnx.save_model(onnx_model, "example.onnx")