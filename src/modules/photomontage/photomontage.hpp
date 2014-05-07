#ifndef PHOTOMONTAGE_HPP
#define PHOTOMONTAGE_HPP

#include <QObject>
#include <QPixmap>

#include <pm_modes.hpp>

class PhotoMontage : public QObject
{
   Q_OBJECT
public:
   explicit PhotoMontage(const QPixmap &pixmap, const QPixmap &pixmap2, EGraphCut_DataTerm mode, QObject *parent = 0);

signals:

public slots:

private:

   void setupGraphCut();
//   GCoptimization::EnergyTermType SmoothCostFn(GCoptimization::SiteID site1, GCoptimization::SiteID s2, GCoptimization::LabelID l1, GCoptimization::LabelID l2);

   const QPixmap& m_inputSource;

};

#endif // PHOTOMONTAGE_HPP
