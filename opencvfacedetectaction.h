#ifndef OPENCVFACEDETECTACTION_H
#define OPENCVFACEDETECTACTION_H

#include <QObject>
#include "opencvaction.h"
#include "typedef.h"
#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"


class OpenCVfaceDetectAction : public OpenCVaction
{
  Q_OBJECT
public:
  explicit OpenCVfaceDetectAction(QObject *parent = nullptr);
  ~OpenCVfaceDetectAction();

  void action(cv::Mat &imgin, cv::Mat *&imgout);

  void startTrain(){
    m_isTrain = true;
  }

  void startPredict(){
    m_isPredict = true;
  }

  void setLabel(int i){
    m_label = i;
  }

signals:
  void a();
  void train(const Mats &src, const Ints &labels);
  void predict(const cv::Mat &src);
public slots:

private:
  cv::CascadeClassifier* m_cascade;
  double m_scale;
  bool m_isTrain;
  bool m_isPredict;
  int m_srcNum;
  int m_label;
  Mats m_mats;
  Ints m_labels;

  static cv::Mat getSubMat(cv::Mat &imgin, const CvRect &rect);
  static cv::Mat norm_0_255(cv::InputArray _src);
};

#endif // OPENCVFACEDETECTACTION_H
