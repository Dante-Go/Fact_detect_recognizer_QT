#include "opencvcannyaction.h"

OpenCVcannyAction::OpenCVcannyAction(QObject *parent) : OpenCVaction(parent)
{

}

OpenCVcannyAction::~OpenCVcannyAction()
{

}

void OpenCVcannyAction::action(cv::Mat &imgin, cv::Mat *&imgout)
{
  cv::Mat* pImageCanny = new cv::Mat(imgin);
  cv::cvtColor(imgin, *pImageCanny, CV_RGB2GRAY);
  cv::Mat* imgCannyout = new cv::Mat(imgin.size(), CV_8UC1);
  cvCanny(pImageCanny, imgCannyout, 15, 145, 3);
  pImageCanny->release();
  imgout = new cv::Mat(imgin.size(), CV_8UC3);
  cvCvtColor(imgCannyout, imgout, CV_GRAY2RGB); // QT not support Format_Indexed8.
  imgCannyout->release();
}
