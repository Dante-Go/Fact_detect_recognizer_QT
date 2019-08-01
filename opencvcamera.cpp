#include "opencvcamera.h"

OpenCVcamera::OpenCVcamera(QObject *parent) : OpenCVcapture(parent),
  m_cameraId(0),
  m_openedCameraId(-1),
  m_image(nullptr),
  m_cvCapture(nullptr),
  m_isIPCrtsp(false),
  m_rtspAddress("")
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

bool OpenCVcamera::isIPCrtsp() const
{
  return m_isIPCrtsp;
}

void OpenCVcamera::setIsIPCrtsp(bool ipcFlag)
{
  if(m_isIPCrtsp != ipcFlag)
    m_isIPCrtsp = ipcFlag;
  emit isIPCrtspChanged();
}

QString OpenCVcamera::rtspAddress() const
{
  return m_rtspAddress;
}

void OpenCVcamera::setRtspAddress(QString rtspAddr)
{
  if(m_rtspAddress != rtspAddr)
    m_rtspAddress = rtspAddr;
  emit rtspAddressChanged();
}

void OpenCVcamera::setRun(bool r)
{
  m_run = r;
  if(m_run)
    {
      if(m_cvCapture == nullptr && m_isIPCrtsp == true && m_rtspAddress != "")
        {
          // rtsp://10.10.27.120:554/live/0/MAIN
          m_cvCapture = new cv::VideoCapture(m_rtspAddress.toStdString());
          m_openedCameraId = -1;
          m_cameraId = -1;
        }
      else {
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





