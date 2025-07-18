import zipfile
import requests
import cv2
import matplotlib.pyplot as plt
import glob
import random
import os
import json
import time
from pathlib import Path
from ultralytics import YOLO

# https://docs.ultralytics.com/guides/yolo-data-augmentation/#using-a-configuration-file
 
# Load the model.
#model = YOLO('yolov8n.pt')
#model = YOLO('/home/karl/Documents/descent/train_descent_obs/runs/detect/yolov8n_descent2/weights/best.pt')
model = YOLO('/home/karl/Documents/descent/train_descent_obs/runs/detect/yolov8n_descent_real/weights/best.pt')
 
# Training.
results = model.train(
   data='obs.yaml',
   imgsz=320,
   epochs=200,
   batch=8,
   pretrained=True,
   patience=30,
   augment=True, # Verify this is a parameter
   hsv_h=0.1,
   hsv_s=0.5,
   hsv_v=0.5,
   translate=0.2,
   scale=0.2,
   fliplr=0.5,
   mosaic=0.3,
   mixup=0.1,
   name='yolov8n_descent_white_balls')
