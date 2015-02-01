#include "pb_window.hpp"
#include "ui_pb_window.h"

#include <opencv2/opencv.hpp>
PBWindow::PBWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::PBWindow)
{
   ui->setupUi(this);
}

PBWindow::~PBWindow()
{
   delete ui;
}

void PBWindow::on_runButton_clicked()
{

   cv::Mat img1 = cv::imread("/Users/sim/dev/borack_vision/resources/BPA_20141101_054.jpg");
   cv::Mat img2 = cv::imread("/Users/sim/dev/borack_vision/resources/BPA_20141101_055.jpg");

   const int nLevels = 4;
   std::vector<cv::Mat> gaussPyramid1(nLevels);
   std::vector<cv::Mat> laplacePyramid1(nLevels);
   std::vector<cv::Mat> gaussPyramid2(nLevels);
   std::vector<cv::Mat> laplacePyramid2(nLevels);


   gaussPyramid1[0] = img1;
   gaussPyramid2[0] = img2;

   cv::Mat tmp;
   cv::Mat resized;

   // create laplacian pyramids
   for(int i = 1; i<nLevels; i++)
   {
      cv::pyrDown(gaussPyramid1[i-1], tmp, cv::Size(gaussPyramid1[i-1].cols/2.0f, gaussPyramid1[i-1].rows/2.0f));
      gaussPyramid1[i] = tmp;
      cv::resize(gaussPyramid1[i], resized, cv::Size( gaussPyramid1[i-1].cols , gaussPyramid1[i-1].rows));
      laplacePyramid1[i-1] = gaussPyramid1[i-1] - resized;

      cv::pyrDown(gaussPyramid2[i-1], tmp, cv::Size(gaussPyramid2[i-1].cols/2.0f, gaussPyramid2[i-1].rows/2.0f));
      gaussPyramid2[i] = tmp;
      cv::resize(gaussPyramid2[i], resized, cv::Size( gaussPyramid2[i-1].cols , gaussPyramid2[i-1].rows));
      laplacePyramid2[i-1] = gaussPyramid2[i-1] - resized;
   }

   laplacePyramid1[nLevels-1] = gaussPyramid1[nLevels-1];
   laplacePyramid2[nLevels-1] = gaussPyramid2[nLevels-1];

   cv::imwrite("imga-level4.png", gaussPyramid1[3]);
   cv::imwrite("imga-lap-level2.png", laplacePyramid1[2]);

}
