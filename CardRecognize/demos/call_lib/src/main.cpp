#include<CardRecognize/CardRecognize.h>

#include<CardRecognize/CardRecognize.h>
#include <opencv_basic/opencv_match.h>
#include <jsonele/JsonEle.hpp>
#include <StdUtility/StdUtility.h>

class CardItem :public  JsonEle {
public:
    CardItem() 
    {
        __count = 0;
        __flag=0;
    }
    CardItem(const  neb::CJsonObject &v_obj)
    {
        v_obj.Get("__count", __count);
        v_obj.Get("__path", __path);
        v_obj.Get("__mark", __mark);
        v_obj.Get("__flag", __flag);


    }
    virtual ~CardItem() {};
    virtual neb::CJsonObject jsonObj() {
        neb::CJsonObject v_obj;
        v_obj.Add("__count", __count);
        v_obj.Add("__path", __path);
        v_obj.Add("__mark", __mark);
        v_obj.Add("__flag", __flag);

        return v_obj;
    }
public:
    int __count;
    std::string __path;
    std::string __mark;
    /// 是否已处理
    unsigned __flag;


};


/// 分割出目标图片
void splitCard();
void signCard();



///
std::string path_config_temp = "card.temp.config";

std::string dir_config_permanent = "card_permanent";
std::string path_config_permanent = "card_permanent/card.config";

int main(int argc, char* argv[])
{




    /// 在目标块中识别内容
    /// 方法是利用除去边缘的已知块与目标块进行比对,当差异值较小时认为是匹配的
    /// 或者计算特征值,与特征值进行比对
    /// 对于每个模板图片计算Hu矩
    /// 得到目标图片时与所有模板图片的Hu矩相比较,得到差距最小的

    return 0;
}

///{标记,路径,序号}
/// 遍历列表,
/// - 标记,存在标记,在正式表中查找该标记
///   - 若找到,则不操作
///   - 若未找到,插入该标记,保存图片到另一路径,更改序号和路径
/// - 无标记,则在计算图片描述符,在正式表中查找匹配
///   - 找到,则添加标记
///   - 未找到,则输出序号
void signCard()
{
  std::vector<CardItem> list_carditem_temp;
  std::vector<CardItem> list_carditem_perm;

  {
  std::string content_config;
  ns_stdutility::readF(path_config_temp, content_config);
  list_carditem_temp = neb::fromJsonObj<CardItem>(content_config);
  }

  {
  std::string content_config;
  ns_stdutility::readF(dir_config_permanent, content_config);
  list_carditem_perm = neb::fromJsonObj<CardItem>(content_config);
  }

  for(size_t i=0;i<list_carditem_temp.size();i++)
  {
    if(!list_carditem_temp[i].__mark.empty())
    {
      auto pos_find=std::find_if(list_carditem_perm.begin(),list_carditem_perm.end(),
                                 [&](const CardItem & v_item){
        return v_item.__mark==list_carditem_temp[i].__mark;
      });

      if (pos_find != list_carditem_perm.end()) {

      }
      else{

      }

    }
    else{

    }
  }

}


void splitCard()
{
  std::string content_config;
  ns_stdutility::readF(path_config_temp, content_config);
  auto list_card = neb::fromJsonObj<CardItem>(content_config);
  int count_card = list_card.size();
  std::string path_image = "C:/Users/sxy/Desktop/mj/2022-12-04_170457.png";
  cv::Mat mat_target = cv::imread(path_image);
  cv::Mat mat_target_gray;
  cv::cvtColor(mat_target, mat_target_gray, CV_BGR2GRAY);


  /// 对图片做模板计算
  std::string path_template = "C:/Users/sxy/Desktop/mj/template_whole.png";
  std::string path_template_in = "C:/Users/sxy/Desktop/mj/template_in.png";

  cv::Mat mat_template = cv::imread(path_template);
  cv::Mat mat_template_in = cv::imread(path_template_in);


  cv::cvtColor(mat_template, mat_template, CV_BGR2GRAY);
  cv::Mat mat_mask = cv::Mat::zeros(mat_template.rows, mat_template.cols, CV_8U);
  cv::Rect rect_mask(1, 20, mat_template_in.cols, mat_template_in.rows);
  mat_mask.setTo(255);
  mat_mask(rect_mask).setTo(0);
  //cv::imshow("mat_mask", mat_mask);
  //cv::waitKey();
  cv::imwrite("mat_mask.jpg", mat_mask);
  //double min_ssd = -1;

  //cv::Rect rect_template(0,0, mat_target_gray.cols, mat_target_gray.rows);

  //std::cout << " mat_target_gray.rows - mat_template.rows:" << mat_target_gray.rows - mat_template.rows << std::endl;
  //std::cout << " mat_target_gray.cols - mat_template.cols:" << mat_target_gray.cols - mat_template.cols << std::endl;

  ///// 求出ssd最小值
  //for (int r = 0; r < mat_target_gray.rows - mat_template.rows; r++)
  //{
  //    for (int c = 0; c < mat_target_gray.cols - mat_template.cols; c++)
  //    {
  //        std::cout << "min_ssd:" << min_ssd << std::endl;
  //        std::cout << "r:" << r << std::endl;
  //        std::cout << "c:" << c << std::endl;


  //        cv::Rect rect_target_block(c, r, mat_template.cols, mat_template.rows);

  //        if (!(rect_target_block.tl().inside(rect_template) && rect_target_block.br().inside(rect_template)))
  //        {
  //            continue;
  //        }
  //        double tmpssd = opencv_match::calMAD(mat_target_gray(rect_target_block), mat_template, mat_mask);
  //        if (min_ssd < 0) {
  //            min_ssd = tmpssd;
  //        }
  //        else {
  //            min_ssd = min_ssd < tmpssd ? min_ssd : tmpssd;
  //        }
  //            std::cout << "min_ssd:" << min_ssd << std::endl;

  //    }
  //}

  //std::cout << "min_ssd:" << min_ssd << std::endl;

  double min_ssd = 0;

  /// 遍历图像求出所有区域,且使得不交叉
  /// ssd值小于该值的认为是目标区域
  double limit_ssd = min_ssd + 1;
  cv::Point point_bottom_tl(140,685);
  cv::Point point_bottom_br(1055, 706);

  /// 保留目标区域
  std::vector<cv::Rect> list_rect_target_card_block;
  for (int r = point_bottom_tl.y; r < point_bottom_br.y ; r++)
  {
      bool has_in_row = false;
      for (int c = point_bottom_tl.x; c < point_bottom_br.x ; c++)
      {
                  std::cout << "r:" << r << std::endl;
      std::cout << "c:" << c << std::endl;
          cv::Rect rect_target_block(c, r, mat_template.cols, mat_template.rows);
          double tmpssd = opencv_match::calMAD(mat_target_gray(rect_target_block), mat_template, mat_mask);
          if (tmpssd <= limit_ssd) {
              list_rect_target_card_block.push_back(rect_target_block);
              /// 若满足条件,则跳过这篇区域
              c += mat_template.cols;
              has_in_row = true;
          }
      }
      if (has_in_row == true) {
          r += mat_template.rows;
      }
  }

  /// draw
  /// 绘图验证
  {
      cv::Mat mat_draw = mat_target_gray.clone();

      for (auto it : list_rect_target_card_block)
      {
          cv::rectangle(mat_draw, it, cv::Scalar(255, 0, 0));
          std::string path_card_tmp = std::to_string(count_card)+ "_card.jpg";
          CardItem tmpitem;
          tmpitem.__count = count_card;
          tmpitem.__path = path_card_tmp;
          cv::imwrite(path_card_tmp, mat_target_gray(it));
          list_card.push_back(tmpitem);
          count_card++;
      }
      cv::imwrite("mat_draw.jpg", mat_draw);
      std::string str_save = neb::toJsomObj<CardItem>(list_card).ToFormattedString();
      ns_stdutility::writeF(path_config,str_save);

  }
}

