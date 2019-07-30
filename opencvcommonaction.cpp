#include "opencvcommonaction.h"

OpenCVcommonAction::OpenCVcommonAction()
{

}

OpenCVcommonAction::~OpenCVcommonAction()
{

}

void OpenCVcommonAction::action(cv::Mat &imgin, cv::Mat *&imgout)
{
  imgout = new cv::Mat(imgin);
  cv::cvtColor(imgin, *imgout, CV_BGR2RGB);
}
