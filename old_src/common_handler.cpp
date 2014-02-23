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

void CommonHandler::loadImage(QString p)
{
    m_images.clear();
    m_featureOverlays.clear();

    QStringList paths = p.split(",");
    foreach(QString path, paths)
    {
        path.remove(0,7); // remove the 'file://' part
        qDebug() << "The selected path is " << path;
        m_images.push_back(QImage(path));
        if(m_images.back().width() == 0
                || m_images.back().height() == 0)
        {
            qCritical("Loading the image from %s was not possible", path.toStdString().c_str());
        }

        m_imgProvider->setNewImage(m_images);

        //    m_image.save("/Users/sim/dev/borack_vision/src/build/qImage.png");
        //    cv::Mat cvMat = Converter::QImageToCvMat(m_image);
        //    cv::imwrite("/Users/sim/dev/borack_vision/src/build/cvMat.png", cvMat);

        //    QImage img2 = Converter::CvMatToQImage(cvMat);
        //    img2.save("/Users/sim/dev/borack_vision/src/build/qImage2.png");

    }

    findFeatures();
    visualizeMatches(0,1);

    emit newImage();
}

void CommonHandler::findFeatures()
{
    qDebug() << Q_FUNC_INFO;
    foreach(QImage img, m_images)
    {

        QPixmap pixMap(img.size());
        pixMap.fill(QColor(0,0,0,0));


        QPainter painter(&pixMap);
        QPen pen;
        pen.setColor(QColor(0,255,0,125));
        pen.setWidth(15);
        painter.setPen(pen);


        cv::Mat descriptors;
        KeyPoints keyPoints;

        cv::Mat mat = Converter::QImageToCvMat(img);
        //    cv::Mat mask= cv::Mat::ones(mat.cols, mat.rows,  CV_8U);


        cv::SIFT siftDetector(20);
        siftDetector(mat,cv::Mat(),keyPoints,descriptors);

        m_vecOfKeypoints.push_back(keyPoints);
        m_vecOfDescriptors.push_back(descriptors);

        qDebug() << "Found " << keyPoints.size() << " features";
        qDebug() << "Descriptor size: " << descriptors.cols <<" x " << descriptors.rows;
        foreach (cv::KeyPoint keyPoint, keyPoints) {
            //        qDebug("x: %f, y: %f", keyPoint.pt.x, keyPoint.pt.y);
            painter.drawPoint(keyPoint.pt.x, keyPoint.pt.y);
        }

        m_featureOverlays.push_back(pixMap.toImage());
    }

    m_imgProvider->setFeatureOverlay(m_featureOverlays);

}

void CommonHandler::visualizeMatches(int indexOfRef, int indexOfObs)
{
    if(indexOfRef >= m_images.size()
            || indexOfObs >= m_images.size())
    {
        return;
    }

    cv::Mat ref = Converter::QImageToCvMat(m_images.at(indexOfRef));
    cv::Mat obs = Converter::QImageToCvMat(m_images.at(indexOfObs));

    cv::Mat out;//(ref.cols + obs.cols, std::max(ref.rows, ref.cols), CV_8UC4);
//    ref.copyTo(out(cv::Rect(0,0,ref.cols,ref.rows)));
//    obs.copyTo(out(cv::Rect(ref.cols,0,obs.cols,obs.rows)));
                cv::hconcat(ref,obs,out);
            m_matchImage = Converter::CvMatToQImage(out);
    m_imgProvider->setMatchImage(m_matchImage);
}


