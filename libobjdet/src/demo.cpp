#include "object_detector_class.h"

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {
  if (argc != 6) {
    std::cout << "Usage: " << argv[0] << " proto_file model_file config_file image_path use_gpu";
    return -1;
  }
  std::string proto_file            = argv[1];
  std::string model_file            = argv[2];
  std::string default_config_file   = argv[3];
  std::string img_path              = argv[4];
  bool  use_gpu = (argv[5] == "1" || argv[5] == "true");
  float image_thresh = 0.8;

  cv::Mat cv_image = cv::imread(img_path);

  std::vector<visionrush::ObjectInfo> obj_info;
  visionrush::ObjectDetector obj_det(proto_file, model_file, default_config_file, use_gpu);
  obj_det.Detect(cv_image, obj_info);

  std::vector<visionrush::ObjectInfo> filtered_res;
  for (size_t obj = 0; obj < obj_info.size(); obj++) {
    if ( obj_info[obj].score_ >= image_thresh ) {
      filtered_res.push_back( obj_info[obj] );
    }
  }
  
  for (size_t obj = 0; obj < filtered_res.size(); obj++) {
    std::cout << filtered_res[obj].label_ << "  " << filtered_res[obj].x_ << " " << filtered_res[obj].y_ << " " << filtered_res[obj].width_ << " " << filtered_res[obj].height_ << "     " << filtered_res[obj].score_ << std::endl;
  }
}
