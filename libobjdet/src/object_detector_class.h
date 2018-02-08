#ifndef VISIONRUSH_OBJDET_H_
#define VISIONRUSH_OBJDET_H_

#include <string>
#include <vector>

#ifndef __OPENCV_CORE_HPP__
namespace cv {
  class Mat;
}
#endif

namespace API {
   class Detector;
}

namespace visionrush {
  struct ObjectInfo {
    float x_      = 0.0;
    float y_      = 0.0;
    float width_  = 0.0;
    float height_ = 0.0;
    float score_  = 0.0;
    int   label_  = -1;
    ObjectInfo(float x, float y, float width, float height, float score, int label) {
      x_ = x;
      y_ = y;
      width_  = width;
      height_ = height;
      score_  = score;
      label_  = label;
    }
  };

  class ObjectDetector {
   public:
    // 构造函数
    // param:
    //    proto_file:   [in]  模型结构文件
    //    model_file:   [in]  参数文件
    //    config_file:  [in]  配置文件
    // return:
    //    none.    
    ObjectDetector(const std::string& proto_file, const std::string& model_file, const std::string& config_file, const bool use_gpu = false);


    // 目标检测
    // param:
    //    img:      [in]  Mat图像
    //    obj_info: [out] 图像中的目标信息
    // return:
    //    none.
    void Detect(const cv::Mat& img, std::vector<ObjectInfo>& obj_info);

    ~ObjectDetector();

   private:
    ObjectDetector(const ObjectDetector&);       
    ObjectDetector& operator=(const ObjectDetector&);

    API::Detector* detector_;
  };
}

#endif