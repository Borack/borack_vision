#ifndef PM_WINDOW_HPP
#define PM_WINDOW_HPP

#include <QMainWindow>
#include <QScopedPointer>

#include <pm_targetscene.hpp>
#include <pm_sourcewidget.hpp>

namespace Ui {
class pm_window;
}

class GCoptimizationGridGraph;

class PmWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit PmWindow(QWidget *parent = 0);
   ~PmWindow();

private slots:
   void on_runButton_clicked();
   
   void on_dataComboBox_currentIndexChanged(int index);

   void on_smoothnessComboBox_currentIndexChanged(int index);

   void on_tabWidget_currentChanged(int index);

   void on_resetButton_clicked();

private:

   //!
   //! \brief Sets up the UI comboboxes, only called on create
   //!
   void setupComboboxes();

   //!
   //! \brief Adds a new source tab
   //!
   void addANewTab();

   //!
   //! \brief Downscales a given \p input vector of images and strokes.
   //! \param[in] input a vector of pairs with images and strokes
   //! \param[out] downscaledVector a vector of downscaled images and strokes
   //! \param[out] downscaleFactor the applied downscaling factor (0,1]
   //!
   void downscale(const PMVector& input, PMVector& downscaledVector, float &downscaleFactor);


   //!
   //! \brief GraphCut setup to run that we can indicate which luminance extreme we want ( e.g.
   //!        always the darker corrrespondence )
   //! \param[in] allInput Vector of images and strokes, required to setup the data costs in the graph.
   //! \param[in] gc Graph with all nodes and internal connection and smoothness cost.
   //! \param[in] isMinimum indicates if we want to have max or minimum luminance
   //!
   void runLuminance(const PMVector &allInput, GCoptimizationGridGraph *gc, bool isMinimum);

   //!
   //! \brief Runs the graph cut algorithm with the provided strokes as hard constraints
   //! \param[in] allInput Vector of images and strokes, required to setup the data costs in the graph.
   //! \param[in] gc Graph with all nodes and internal connection and smoothness cost.
   //!
   void runHard(const PMVector &allInput, GCoptimizationGridGraph *gc);



   Ui::pm_window *ui;                                 //!   The UI window
   QScopedPointer<PMTargetScene> m_tScene;            //!   The actual target scene to render to the result.
   EGraphCut_DataTerm m_gcDataTermMode;               //!   The data term modus
   EGraphCut_SmoothnessTerm m_gcSmoothnessTermMode;   //!   The smoothness term modus


};

#endif // PM_WINDOW_HPP
