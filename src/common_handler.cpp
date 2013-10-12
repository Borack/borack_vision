#include "common_handler.hpp"
#include <QDebug>
#include <QString>



CommonHandler::CommonHandler(QObject *parent)
    : QObject(parent)
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

}


