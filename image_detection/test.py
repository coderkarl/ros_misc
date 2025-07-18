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

#https://docs.ultralytics.com/modes/predict/#inference-arguments
 
# Load the model.
model = YOLO('/home/karl/Documents/descent/train_descent_obs/runs/detect/yolov8n_descent_white_balls/weights/best.pt')
 
# Training.
results = model.predict(
   source='/home/karl/Documents/descent/train_descent_obs/descent_data/2025.06.01_static/',
   show=False,
   imgsz=320,
   name='yolov8n_descent_infer_2025.06.01_static',
   save=True,
   show_labels=False)
