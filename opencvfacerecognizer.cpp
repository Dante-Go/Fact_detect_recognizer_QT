#include "opencvfacerecognizer.h"

#include <QFile>

const char* file = "data/a.fr";

OpencvFaceRecognizer::OpencvFaceRecognizer(QObject *parent) : QObject(parent),
  m_type(FaceRecognizer_Invalid),
  m_hadLoad(false)
{

}

OpencvFaceRecognizer::~OpencvFaceRecognizer()
{
  if(!m_ptr.empty()){
      m_ptr->save(file);
    }
}

void OpencvFaceRecognizer::loadRecognizer(OpencvFaceRecognizer::FaceRecognizerType type)
{
  if(m_type == FaceRecognizer_Invalid && type != FaceRecognizer_Invalid)
    {
      switch (type) {
        case FaceRecognizer_Fisher:
          {
            m_ptr = cv::face::FisherFaceRecognizer::create();
            break;
          }
        case FaceRecognizer_Eigen:
          {
            m_ptr = cv::face::EigenFaceRecognizer::create();
            break;
          }
        case FaceRecognizer_LBPH:
          {
            m_ptr = cv::face::LBPHFaceRecognizer::create();
            break;
          }
        default:
          break;
        }
    }

  QFile f(file);
  if(!m_ptr.empty() && f.exists())
    {
      m_ptr->read(file);
      m_hadLoad = true;
    }
}
