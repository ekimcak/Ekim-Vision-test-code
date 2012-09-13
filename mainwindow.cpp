#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "histogram1D.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//-------------------- Opens image in b & w-----------------------------------------------
//------------------ and shows that b&W image---------------------------------------------
void MainWindow::on_actionOpen_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("open image"),".",tr("image files(*.jpg *.png *.bmp)"));
    image= cv::imread(fileName.toAscii().data(),0);
    cv::namedWindow("original image");
    cv::imshow("original image", image);
}
//-----------------------------------------------------------------------------------------



//----------------- shows image's histogram on terminal-----------------------------------
void MainWindow::on_pushButton_2_clicked()
{
    Histogram1D terminal;

    cv::MatND histo=terminal.getHistogram(image);
// shows values of histgoram on terminal
   for (int i=0; i<256; i++)
        std::cout<<"value"<<i<<"="<<histo.at<float>(i)<<std::endl;
}
//-----------------------------------------------------------------------------------------



// ------------------ transforms the image to threshold-------------------------------------
void MainWindow::on_pushButton_3_clicked()
{
    cv::Mat thresholded;
    cv::threshold(image,thresholded,189,232,cv::THRESH_BINARY);
    cv::namedWindow("threshold");
    cv::imshow("threshold",thresholded);
}
//-----------------------------------------------------------------------------------------



//------------------ shows histogram values on the graphic----------------------------------
void MainWindow::on_pushButton_clicked()
{
    Histogram1D graph;

    cv::namedWindow("histogram graph");
    cv::imshow("histogram graph", graph.getHistogramImage(image));
}
//-----------------------------------------------------------------------------------------




//-------------------- tranforms the image to negative---------------------------------------
//-------------------- shows it's histogram values on graphic--------------------------------
void MainWindow::on_pushButton_4_clicked()
{
    Histogram1D negative;
    //build look up
    int dim(256);
    cv::Mat lut(1, &dim, CV_8U); // lut is a matrix which is in 1D
    for(int i=0; i<256; i++)
    {
        lut.at<uchar>(i)=255-i; //takes all the values and reverses it
    }
    cv::Mat negativeResult;
    negativeResult=negative.applyLookUp(image,lut);
    cv::namedWindow("negative");
    cv::imshow("negative",negativeResult);

    //negative image histogram
    cv::imshow("negative histogram",negative.getHistogramImage(negativeResult));

}
//-----------------------------------------------------------------------------------------




//---------------------------stretches the image on some level---------------------------------------
//--------------------------- and also show it's histogram level on a grahp--------------------------
void MainWindow::on_pushButton_5_clicked()
{
    Histogram1D str;

    cv::Mat strecthLevel;

    cv::namedWindow("stretched");
    int x= ui->lineEdit->text().toInt();


    cv::Mat strecthed = str.strecth(image,x);
    cv::imshow("stretched", strecthed);
    cv::imshow("stretched histogram",str.getHistogramImage(strecthed));
}
//-----------------------------------------------------------------------------------------




//-------------------- equalized the b&w image -------------------------------------------------
//---------------------- shows it's histogram values on a graph --------------------------------
void MainWindow::on_pushButton_6_clicked()
{
    Histogram1D equa;

    cv::namedWindow("equalized");
    cv::namedWindow("equalized histogram");

    cv::Mat equalized=equa.equalize(image);
    cv::imshow("equalized",equalized);
    cv::imshow("equalized histogram",equa.getHistogramImage(equalized));

}
//-----------------------------------------------------------------------------------------

void MainWindow::on_textEdit_textChanged()
{

}
