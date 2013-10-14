#include "common_handler.hpp"
#include <QDebug>
#include <QString>
#include <QColor>
#include <QPainter>
#include <QPen>

#include "converter.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/nonfree/nonfree.hpp>

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
    path.remove(0,7); // remove the 'file://' part
    qDebug() << "The selected path is " << path;
    m_image = QImage(path);
    if(m_image.width() == 0
            || m_image.height() == 0)
    {
        qCritical("Loading the image from %s was not possible", path.toStdString().c_str());
    }

    m_imgProvider->setNewImage(m_image);

//    m_image.save("/Users/sim/dev/borack_vision/src/build/qImage.png");
//    cv::Mat cvMat = Converter::QImageToCvMat(m_image);
//    cv::imwrite("/Users/sim/dev/borack_vision/src/build/cvMat.png", cvMat);

//    QImage img2 = Converter::CvMatToQImage(cvMat);
//    img2.save("/Users/sim/dev/borack_vision/src/build/qImage2.png");

    findFeatures();

    emit newImage();
}

void CommonHandler::findFeatures()
{

    m_featureOverlay = QPixmap(m_image.size());
    m_featureOverlay.fill(QColor(0,0,0,0));

    QPainter painter(&m_featureOverlay);
    QPen pen;
    pen.setColor(QColor(0,255,0,125));
    pen.setWidth(15);
    painter.setPen(pen);


    cv::Mat descriptors;
    std::vector<cv::KeyPoint> keyPoints;

    cv::Mat mat = Converter::QImageToCvMat(m_image);
//    cv::Mat mask= cv::Mat::ones(mat.cols, mat.rows,  CV_8U);


    cv::SIFT siftDetector(20);
    siftDetector(mat,cv::Mat(),keyPoints,descriptors);

    qDebug() << "Found " << keyPoints.size() << " features";
    qDebug() << "Descriptor size: " << descriptors.cols <<" x " << descriptors.rows;
    foreach (cv::KeyPoint keyPoint, keyPoints) {
//        qDebug("x: %f, y: %f", keyPoint.pt.x, keyPoint.pt.y);
        painter.drawPoint(keyPoint.pt.x, keyPoint.pt.y);
    }

    m_imgProvider->setFeatureOverlay(m_featureOverlay.toImage());

}


