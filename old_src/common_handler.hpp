#ifndef COMMON_HANDLER_HPP
#define COMMON_HANDLER_HPP

#include <QObject>
#include <types.hpp>

#include "image_provider.hpp"

class CommonHandler : public QObject
{
    Q_OBJECT
public:
    explicit CommonHandler(ImageProvider* imageProvider, QObject *parent = 0);
    ~CommonHandler();

    Q_INVOKABLE void loadImage(QString path);

signals:
    void newImage();

public slots:

private:

    void findFeatures();
    void visualizeMatches(int indexOfRef, int indexOfObs);


    QImage m_matchImage;
    QImages m_images;
    QImages m_featureOverlays;
    ImageProvider* m_imgProvider;
    Mats m_vecOfDescriptors;
    VectorOfKeypoints m_vecOfKeypoints;


};

#endif // COMMON_HANDLER_HP
