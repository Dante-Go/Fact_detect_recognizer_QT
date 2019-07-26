#include <QGuiApplication>
#include <QQmlApplicationEngine>

//#include "qimageprocessor.h"
//#include "qimageviewer.h"
//#include "videofilter.h"

#include "opencvcamera.h"
#include "opencvshowframe.h"


int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

//  qmlRegisterType<QImageProcessor>("com.gtland.plugin", 1, 0, "ImageProcessor");
//  qmlRegisterType<QImageViewer>("com.gtland.plugin", 1, 0, "ImageViewer");
//  qmlRegisterType<VideoFilter>("com.gtland.plugin", 1, 0, "VideoFilter");
  qmlRegisterType<OpenCVcamera>("com.gtland.plugin", 1, 0, "OpenCVcamera");
  qmlRegisterType<OpenCVshowFrame>("com.gtland.plugin", 1, 0, "OpenCVshowFrame");


  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
