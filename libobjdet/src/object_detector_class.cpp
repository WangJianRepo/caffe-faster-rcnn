#include <iostream>
#include <string>
#include <vector>

#include <caffe/common.hpp>
#include <objdet/api.hpp>
#include <opencv2/opencv.hpp>

#include "object_detector_class.h"

namespace visionrush
{
  ObjectDetector::ObjectDetector(const std::string &proto_file, const std::string &model_file, const std::string &config_file, const bool use_gpu) : detector_(NULL)
  {
    if (use_gpu) {
      caffe::Caffe::set_mode(caffe::Caffe::GPU);
    }
    else {
      caffe::Caffe::set_mode(caffe::Caffe::CPU);
    }

    API::Set_Config(config_file);
    detector_ = new API::Detector(const_cast<std::string&>(proto_file), const_cast<std::string&>(model_file));
  }

  ObjectDetector::~ObjectDetector()
  {
    if (detector_ != NULL)
    {
      delete detector_;
      detector_ = NULL;
    }
  }

  void ObjectDetector::Detect(const cv::Mat &img, std::vector<ObjectInfo> &obj_info) {
    std::vector<caffe::Frcnn::BBox<float>> results;
    detector_->predict(img, results);
    for (size_t obj = 0; obj < results.size(); obj++) {
      obj_info.push_back(ObjectInfo(results[obj][0], results[obj][1], results[obj][2] - results[obj][0], results[obj][3] - results[obj][1], results[obj].confidence, results[obj].id));
    }
  }
}
