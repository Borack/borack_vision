#include "common_handler.hpp"
#include <QDebug>
#include <QString>

#include "converter.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

CommonHandler::CommonHandler(ImageProvider* imageProvider, QObject *parent)
    : QObject(parent)
    , m_imgProvider(imageProvider)
{

}

CommonHandler::~CommonHandler()
{

}

void CommonHandler::loadImage(QString path)
{
    path.remove(0,7);
    qDebug() << "The selected path is " << path;
    m_image = QImage(path);
    if(m_image.width() == 0
            || m_image.height() == 0)
    {
        qCritical("Loading the image from %s was not possible", path.toStdString().c_str());
    }

    m_imgProvider->setNewImage(m_image);

    m_image.save("/Users/sim/dev/borack_vision/src/build/qImage.png");
    cv::Mat cvMat = Converter::QImageToCvMat(m_image);
    cv::imwrite("/Users/sim/dev/borack_vision/src/build/cvMat.png", cvMat);

    QImage img2 = Converter::CvMatToQImage(cvMat);
    img2.save("/Users/sim/dev/borack_vision/src/build/qImage2.png");

    emit newImage();
}


