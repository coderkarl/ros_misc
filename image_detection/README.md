# Label Studio
- https://github.com/HumanSignal/label-studio
- docker pull heartexlabs/label-studio:latest
- sudo docker run -it -p 8080:8080 -v ~/Documents/descent/mydata:/label-studio/data heartexlabs/label-studio:latest
- Open browser to localhost:8080

# Ultralytics image detection training
- [https://learnopencv.com/train-yolov8-on-custom-dataset/](https://learnopencv.com/train-yolov8-on-custom-dataset/)
- virtualenv -p python3.8 "ultralytics_env" # Only once
- source ultralytics_env/bin/activate
- pip install ultralytics # Only once
- python3 descent_train.py
- python3 descent_test.py

# Export detection model for oak d lite depthai ros
## Export model references
- <https://learnopencv.com/object-detection-on-edge-device/>
- <https://docs.luxonis.com/cloud/hubai/features/model-conversion/>
- <https://hub.luxonis.com/ai/models/>
- <https://github.com/luxonis/depthai-ros/issues/452>
- <https://github.com/luxonis/depthai-ros/issues/371>
### Different Luxonis Converters and Status
- <https://tools.luxonis.com/>
  - Recommended converter
  - YOLOv8(detection only), RVC2
  - File best.pt from train.py
  - Input image shape 320
  - Output is result.zip with best_openvino_2022.1_6shave.blob and best.json
  - mv best.json ros_best.json
    ```
    "model": {
        "model_name": "/home/karl/Downloads/result/best_openvino_2022.1_6shave.blob",
        "zoo": "path"
    },
    ```
## Run model with depthai ros
- custom_camera.yaml
```
/**:
  ros__parameters:
    camera:
      i_enable_imu: true
      i_enable_ir: true
      i_nn_type: rgb
      i_pipeline_type: RGB
    nn:
      i_nn_config_path: /home/karl/Downloads/result/ros_best.json
      i_enable_passthrough: true
    rgb:
      i_enable_preview: true
    label_map: ["ball","box","hoop","ramp"]
```
- ros2 launch depthai_filters example_det2d_overlay.launch.py params_file:=/home/karl/ros2_ws/src/descentracer/descent_perception/config/custom_camera.yaml
- <https://hub.luxonis.com/ai/>
  - Sign in via github
  - AI, Models, + Add Model
  - The conversion worked online and I downloaded a folder with a .superblob and json
  - I tried to setup the ros_nn_config.json in the 
- <https://blobconverter.luxonis.com/>
  - Not tested. See <https://docs.luxonis.com/software/ai-inference/conversion>

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
- <https://deepai.org/machine-learning-model/text2img>
