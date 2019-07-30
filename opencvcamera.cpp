#include "opencvcamera.h"

OpenCVcamera::OpenCVcamera(QObject *parent) : OpenCVcapture(parent),
  m_cameraId(0),
  m_openedCameraId(-1),
  m_image(nullptr),
  m_cvCapture(nullptr)
{

}

OpenCVcamera::~OpenCVcamera()
{
  if(m_cvCapture != nullptr)
    {
      m_cvCapture->release();
      delete m_cvCapture;
      m_cvCapture = nullptr;
    }

  delete m_image;
  m_image = nullptr;
}

int OpenCVcamera::cameraId() const
{
  return m_cameraId;
}

void OpenCVcamera::setCameraId(int id)
{
  m_cameraId = id;
}

void OpenCVcamera::setRun(bool r)
{
  m_run = r;
  if(m_run)
    {
      if(m_cvCapture == nullptr)
        {
          m_cvCapture = new cv::VideoCapture(m_cameraId);
          m_openedCameraId = m_cameraId;
        }
      else if (m_cameraId != m_openedCameraId) {
          m_cvCapture->release();
          delete m_cvCapture;
          m_cvCapture = nullptr;
          m_cvCapture = new cv::VideoCapture(m_cameraId);
          m_openedCameraId = m_cameraId;
        }
    }
  else {
      if(m_cvCapture)
        {
          m_cvCapture->release();
          delete m_cvCapture;
          m_cvCapture = nullptr;
          m_openedCameraId = -1;
        }
    }
}

cv::Mat *OpenCVcamera::getFrame()
{
  if(m_cvCapture)
    {
      if(m_cvCapture->isOpened())
        {
          m_image = new cv::Mat();
          m_cvCapture->read(*m_image);
        }
      else {
          m_image = nullptr;
        }
    }
  else {
      delete m_image;
      m_image = nullptr;
    }
  return m_image;
}





