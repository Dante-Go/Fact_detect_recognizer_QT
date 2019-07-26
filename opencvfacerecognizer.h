#ifndef OPENCVFACERECOGNIZER_H
#define OPENCVFACERECOGNIZER_H

#include <QObject>
#include "typedef.h"
#include <vector>
#include <string>

#include "opencv2/opencv.hpp"
#include "opencv2/face.hpp"

class OpencvFaceRecognizer : public QObject
{
  Q_OBJECT
public:
  typedef enum {
    FaceRecognizer_Invalid,
    FaceRecognizer_Fisher,
    FaceRecognizer_Eigen,
    FaceRecognizer_LBPH
  }FaceRecognizerType;
  explicit OpencvFaceRecognizer(QObject *parent = nullptr);
  ~OpencvFaceRecognizer();

  void loadRecognizer(FaceRecognizerType type = FaceRecognizer_Eigen);

signals:
  void who(int i) const;

public slots:
  void train(Mats src, Ints labels){
    if(!m_ptr.empty()){
        m_ptr->train(src, labels);
        m_hadLoad = true;
      }
  }

  void update(Mats src, Ints labels){
    if(!m_ptr.empty()){
        m_ptr->update(src, labels);
        m_hadLoad = true;
      }
  }

  int predict(cv::Mat src) const {
    int re = -1;
    if(!m_ptr.empty() && m_hadLoad){
        re = m_ptr->predict(src);
        emit who(re);
      }
    return re;
  }

  void save(const std::string &filename) const {
    if(!m_ptr.empty()){
        m_ptr->save(filename);
      }
  }

  void load(const std::string &filename) const {
    if(!m_ptr.empty()){
//        m_ptr->load(filename);
        m_ptr->read(filename);
      }
  }

private:
  FaceRecognizerType m_type;
  bool m_hadLoad;
  cv::Ptr<cv::face::FaceRecognizer> m_ptr;

};

#endif // OPENCVFACERECOGNIZER_H
