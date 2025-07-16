# Label Studio
- https://github.com/HumanSignal/label-studio
- docker pull heartexlabs/label-studio:latest
- sudo docker run -it -p 8080:8080 -v ~/Documents/descent/mydata:/label-studio/data heartexlabs/label-studio:latest

# Ultralytics image detection training
-[https://learnopencv.com/train-yolov8-on-custom-dataset/](https://learnopencv.com/train-yolov8-on-custom-dataset/)
- virtualenv -p python3.8 "ultralytics_env" # Only once
- source ultralytics_env/bin/activate
- pip install ultralytics # Only once
- python3 descent_train.py
- python3 descent_test.py 
