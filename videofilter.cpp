#include "videofilter.h"

#include "qimageprocessor.h"
#include "opencv2/opencv.hpp"


QVideoFrame MyFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, QVideoFilterRunnable::RunFlags flags)
{
  QVideoFrame cloneFrame(*input);
  QImage img;
  using namespace cv;
  Mat imageM;
  if(!imageM.empty())
    {
      bitwise_not(imageM, imageM);
      QImage imageQ(imageM.data,
                    imageM.cols,
                    imageM.rows,
                    QImage::Format_RGB888);
    }
  return cloneFrame;
}
