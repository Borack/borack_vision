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
    const QString type= l.at(0);
    int index=0;
    if(l.size() > 1)
    {
        index =  l.at(1).toInt();
    }

    qDebug("Id %s",id.toStdString().c_str());


    if(type == "features")
    {
        if(index >= m_featureOverlay.size())
        {
            return QImage();
        }
        size->setWidth(m_featureOverlay.at(index).width());
        size->setHeight(m_featureOverlay.at(index).height());

        return m_featureOverlay.at(index);
    }
    else if(type == "matches")
    {
        size->setWidth(m_matchImage.width());
        size->setHeight(m_matchImage.height());

        return m_matchImage;
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

//-----------------------------------------------------------------------------
void ImageProvider::setMatchImage(const QImage &matchImage)
{
    m_matchImage = matchImage;
}

void ImageProvider::setFeatureOverlay(const QImages& images)
{
    m_featureOverlay = images;
}
