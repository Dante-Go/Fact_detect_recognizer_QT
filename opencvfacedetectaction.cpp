#include "opencvfacedetectaction.h"
#include <QDebug>
#include <QTime>
#include <vector>

const char* cascade_name = "E:/OpenCV_QT/Face_detect_track/data/haarcascade_frontalface_alt2.xml";
const int w = 240;
const int h = 300;

OpenCVfaceDetectAction::OpenCVfaceDetectAction(QObject *parent) : OpenCVaction(parent),
  m_cascade(nullptr),
  m_scale(1.3),
  m_isTrain(false),
  m_isPredict(false),
  m_srcNum(2),
  m_label(0)
{
  m_cascade = new cv::CascadeClassifier(cascade_name);
  if(!m_cascade)
    {
      qDebug() << "load Cascade fail!";
    }
}

OpenCVfaceDetectAction::~OpenCVfaceDetectAction()
{
  if(m_cascade)
    {
      delete m_cascade;
    }
}

void OpenCVfaceDetectAction::action(cv::Mat &imgIn, cv::Mat *&imgOut)
{
  using namespace cv;
  imgOut = new cv::Mat(imgIn);
  if(!m_cascade)
    {
      qDebug() << "Cascade is invaild!";
      return;
    }

  static int srcIndex = 0;

  Mat gray(imgIn.size(), CV_8UC1);
  Mat small_img(cvSize(cvRound(imgIn.cols / m_scale),
                       cvRound(imgIn.rows / m_scale)),
                CV_8UC3);
  cvtColor(imgIn, gray, CV_RGB2GRAY);
  resize(gray, small_img, small_img.size(), 0, 0, INTER_LINEAR);

  equalizeHist(small_img, small_img);

  double t = (double)cvGetTickCount();
  std::vector<cv::Rect> faces;
  m_cascade->detectMultiScale(small_img, faces, 1.1, 2,
                              0|CV_HAAR_SCALE_IMAGE, cvSize(50, 50));
  t = (double)cvGetTickCount() - t;
  qDebug() <<"detection time = " << t / ((double)cvGetTickFrequency()*1000.) << "ms";

  for(std::vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++)
    {
      Mat smallImgROI;
      Point center;
      Scalar color = CV_RGB(255, 255, 255);
      rectangle(*imgOut, cvPoint(r->x * m_scale, r->y * m_scale),
                cvPoint((r->x + r->width) * m_scale, (r->y + r->height) * m_scale),
                color, 2, CV_AA);

      if(m_isTrain)
        {
          if(faces.size() != 1)
            {
              break;
            }
          ++srcIndex;

          Rect t_rect;
          t_rect.x = r->x * m_scale;
          t_rect.y = r->y * m_scale;
          t_rect.width = r->width * m_scale;
          t_rect.height = r->height * m_scale;

          cv::Mat t = getSubMat(gray, t_rect);
          m_mats.push_back(t);
          cv::imshow("face", t);
          m_labels.push_back(m_label);
          if(srcIndex == m_srcNum)
            {
              emit train(m_mats, m_labels);
              srcIndex = 0;
              m_isTrain = false;
              m_mats.clear();
              m_labels.clear();
            }
        }
      if(m_isPredict)
        {
          if(faces.size() != 1)
            {
              break;
            }

          Rect t_rect;
          t_rect.x = r->x * m_scale;
          t_rect.y = r->y * m_scale;
          t_rect.width = r->width * m_scale;
          t_rect.height = r->height * m_scale;

          cv::Mat t = getSubMat(gray, t_rect);
          cv::imshow("pface", t);
          emit predict(t);
          m_isPredict = false;
        }
    }

  gray.release();
  small_img.release();

  emit a();
}

cv::Mat OpenCVfaceDetectAction::getSubMat(cv::Mat &imgin, const CvRect &rect)
{
  //  IplImage *s = cvCreateImage(cvSize(w, h), imgin->depth, imgin->nChannels);
  //  cvSetImageROI(imgin, rect);
  //  cvResize(imgin, s);
  //  cvResetImageROI(imgin);
  //  return norm_0_255(cv::Mat(s, false));
  cv::Mat s = cv::Mat(imgin);
  cv::Mat roi = imgin(rect);
  cv::resize(roi, s, cv::Size(w,h));

  return norm_0_255(s);

}

cv::Mat OpenCVfaceDetectAction::norm_0_255(cv::InputArray _src)
{
  cv::Mat src = _src.getMat();
  cv::Mat dst;

  switch (src.channels()) {
    case 1:
      {
        cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC1);
        break;
      }
    case 3:
      {
        cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC3);
        break;
      }
    default:
      {
        src.copyTo(dst);
        break;
      }
    }
  return dst;
}


