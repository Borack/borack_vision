#include "photomontage.hpp"
#include <GCoptimization.h>
#include <QDebug>

//-----------------------------------------------------------------------------
PhotoMontage::PhotoMontage(const QPixmap &pixmap, QObject *parent)
   : m_inputSource(pixmap)
   , QObject(parent)
{
   setupGraphCut();
}

//-----------------------------------------------------------------------------
void PhotoMontage::setupGraphCut()
{
   GCoptimizationGridGraph* gc = new GCoptimizationGridGraph(m_inputSource.width(), m_inputSource.height(), 2);
   qDebug() << "Graph is setup";
}

