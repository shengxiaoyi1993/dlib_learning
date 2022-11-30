#ifndef CARDRECOGNIZE_H
#define CARDRECOGNIZE_H

/// 本库用于识别边缘均匀 中间有内容的物体
/// 基本思路是用一个带掩膜的模板图片检测出图片中所有块
/// 再根据中间的内容识别出该物体
///
/// 1. 用带掩膜的模板检测出所有区域
/// 2. 内部纹理判断,是背面还是正面
/// 3. 截取所有正面的画面,对图片进行标记
/// 4. 识别过程对每张牌都生进行以上过程,若没有被识别则保存到本地

#include <opencv2/opencv.hpp>
#include <string>

class CardRecognizer
{
public:
  CardRecognizer(const std::string &dir_content,
                 const std::string &path_template
                 );
  ~CardRecognizer()=default;
  void setMask(const cv::Mat& m_msk);
  ///
  int recognize(const cv::Mat &m_image,std::vector<std::string>&list_card);

private:
  std::string __dir_content;
  std::string __path_content;
  cv::Mat __mat_mask;
  cv::Mat __mat_template;
  std::map<std::string,cv::Mat> __map_card;

};




#endif
