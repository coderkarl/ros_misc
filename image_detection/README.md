# Label Studio
- https://github.com/HumanSignal/label-studio
- docker pull heartexlabs/label-studio:latest
- sudo docker run -it -p 8080:8080 -v ~/Documents/descent/mydata:/label-studio/data heartexlabs/label-studio:latest
- Open browser to localhost:8080

# Ultralytics image detection training
-[https://learnopencv.com/train-yolov8-on-custom-dataset/](https://learnopencv.com/train-yolov8-on-custom-dataset/)
- virtualenv -p python3.8 "ultralytics_env" # Only once
- source ultralytics_env/bin/activate
- pip install ultralytics # Only once
- python3 descent_train.py
- python3 descent_test.py 

# Label images
- Label images using label studio
  - Setup desired classes/categories
  - Type a number to enable bounding box creation. Draw boxes.
  - Use Ctrl + Enter to save. Shift + Down to go to next image.
- Export labels as YOLO format
- Move the images and labels into the following dirs
- image_set_description/
  - images/
  - labels/
- Rename the exported labels to match the images if necessary
- Copy the new set of iamges and labels into the main train/ and val/ dirs
