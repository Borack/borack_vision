#include "image_provider.hpp"
#include <QDebug>
#include <QString>

ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{

}

//-----------------------------------------------------------------------------

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

    QStringList l = id.split("/");
    const bool featureRequest = l.at(0) == "features";
    const int index =  l.at(1).toInt();
    qDebug("Request feature: %d from index %d", featureRequest, index);


    if(featureRequest)
    {
        if(index >= m_featureOverlay.size())
        {
            return QImage();
        }
        size->setWidth(m_featureOverlay.at(index).width());
        size->setHeight(m_featureOverlay.at(index).height());

        return m_featureOverlay.at(index);
    }
    else
    {
        if(index >= m_img.size())
        {
            return QImage();
        }
        size->setWidth(m_img.at(index).width());
        size->setHeight(m_img.at(index).height());

        return m_img.at(index);
    }
}

//-----------------------------------------------------------------------------

void ImageProvider::setNewImage(const QImages &images)
{
    qDebug() << Q_FUNC_INFO;
    m_img = images;
}

void ImageProvider::setFeatureOverlay(const QImages& images)
{
    m_featureOverlay = images;
}
