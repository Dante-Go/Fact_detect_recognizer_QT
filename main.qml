import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import QtMultimedia 5.12
import com.gtland.plugin 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 600
    title: qsTr("CvQml")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File");
            MenuItem {
                text: qsTr("&Open");
                onTriggered: {
                    opencvCamera.m_run = true;
                }
            }
            MenuItem {
                text: qsTr("&Close");
                onTriggered: {
                    opencvCamera.m_run = false;
                }
            }
            MenuItem {
                text: qsTr("E&xit");
                onTriggered: {
                    Qt.quit();
                }
            }
        }
    }

    OpenCVcamera {
        id: opencvCamera;
        m_cameraId: 0;
        m_run: false;
        m_isIPCrtsp: m_rtspAddress != "";
        m_rtspAddress: rtspAddress.text;
    }

    OpenCVshowFrame {
        anchors {left: parent.left; top: parent.top;}
        id: opencvShowFrame;
        m_capture: opencvCamera;
        m_frameRate: 60;
        m_run: true;
        width: 640;
        height: 380;
        onWho: {
            console.log(i);
            messageDialog.show(qsTr("ID:") + i);
        }
    }

    TextField {
        id: rtspAddress;
        anchors.left: parent.left;
        anchors.top: opencvShowFrame.bottom;
        anchors.topMargin: 3;
        width: parent.width;
        height: 30;
        anchors.leftMargin: 0;
    }

    Label {
        id: label;
        anchors.left: parent.left;
        anchors.top: opencvShowFrame.bottom;
        anchors.topMargin: 40;
        text: qsTr("");
    }

    TextField {
        id: employeeId;
        y: 0;
        anchors.left: parent.left;
        anchors.top: label.bottom;
        anchors.topMargin: 5;
        width: 80;
        height: 30;
        anchors.leftMargin: 0;
        validator: RegExpValidator {
            regExp: /[0-9]+/;
        }
        placeholderText: qsTr("ID");
    }

    Button {
        id: button;
        text: qsTr("save");
        anchors.left: employeeId.right;
        anchors.top: employeeId.top;

        onClicked: {
            if(employeeId.text.length != 0 && opencvCamera.m_run){
                opencvShowFrame.setLabel(parseInt(employeeId.text));
                console.log(parseInt(employeeId.text));
                opencvShowFrame.startTrain();
                messageDialog.show(qsTr("OK!"));
            }
        }
    }

    Button {
        id: button2;
        text: qsTr("select");
        anchors.right: parent.right;
        anchors.top: button.top;

        onClicked: {
            if(opencvCamera.m_run)
            {
                opencvShowFrame.startPredict();
            }
        }
    }

    MessageDialog {
        id: messageDialog;
        title: qsTr("May I have your attention, please?");

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }

//    ImageProcessor
//    {
//        id: imgProcessor;

//        onImageProcessed:
//        {
//            imgViewer.setImage(image);
//            imageDrawer.open();
//        }
//    }

//    Camera
//    {
//        id: camera;
////        imageCapture
////        {
////            onImageSaved:
////            {
////                imgProcessor.processImage(path);
////            }
////        }
//    }

//    VideoFilter{
//        id: myFilter;

//    }

//    VideoOutput
//    {
//        source: camera;
//        anchors.fill: parent;

//        filters: [myFilter];

////        MouseArea
////        {
////            anchors.fill: parent;
////            onClicked:
////            {
////                camera.imageCapture.capture();

////            }
////        }
//    }

//    Drawer
//    {
//        id: imageDrawer;
//        width: parent.width;
//        height: parent.height;

//        ImageViewer
//        {
//            id: imgViewer;
//            anchors.fill: parent;
//        }
//    }
}
