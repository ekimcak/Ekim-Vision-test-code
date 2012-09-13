#ifndef HISTOGRAM1D_H
#define HISTOGRAM1D_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <QFileDialog>
#include <QtGui/QMainWindow>
#include <stdio.h>
#include <iostream>

//-------------------------------- Class HISTOGRAM 1D----------------------------------------

class Histogram1D
{

//------------------------------- private variables -------------------------------
private:
    int histSize[1];  // number of bins
    float hranges[2];  //min and max pixel value
    const float* ranges[1];
    int channels [1];  // only 1 channel used here

//------------------------------- public variables ---------------------------------
public:
    Histogram1D()
    {
     histSize[0]=256;
     hranges[0]=0.0;
     hranges[1]=255.0;
     ranges[0]=hranges;
     channels[0]=0;
    }

//---------------------------- Constuctors of Histogram1D------------------------------------------


//---------------------------- Calculates histogram of image for terminal ---------------------------

    cv::MatND getHistogram(const cv::Mat &image)
    {
        cv::MatND hist;

        cv::calcHist(&image,
                     1,         //histogram from 1 image only
                     channels,  //the channel used
                     cv::Mat(), // no mask is used
                     hist,      // the resulting histogram
                     1,         // it is a 1D histogram
                     histSize, // number of bins
                     ranges);    // pixel value range
        return hist;
    }

//---------------------------------- Makes histogram graph of the image -------------------------------

    cv::Mat getHistogramImage(const cv::Mat &image){

        // Compute histogram first
        cv::MatND hist= getHistogram(image);

        // Get min and max bin values
        double maxVal=0;
        double minVal=0;
        cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

        // Image on which to display histogram
        cv::Mat histImg(histSize[0], histSize[0], CV_8U,cv::Scalar(255));

        // set highest point at 90% of nbins
        int hpt = static_cast<int>(0.9*histSize[0]);

        // Draw vertical line for each bin
        for( int h = 0; h < histSize[0]; h++ ) {

            float binVal = hist.at<float>(h);
            int intensity = static_cast<int>(binVal*hpt/maxVal);
            cv::line(histImg,cv::Point(h,histSize[0]),cv::Point(h,histSize[0]-intensity),cv::Scalar::all(0));
        }

        return histImg;
    }


//------------------------------ Creates "look up" matrix to -------------------------------------------
//------------------------------ transform the image to negative one ------------------------------------
//------------------------------ and shows histogram of negative image ----------------------------------
    cv::Mat applyLookUp(const cv::Mat &image, const cv::Mat &lookup )
    {

        //create lookup
        cv::Mat result;
        cv::LUT(image, lookup, result); //LUT(source, look up table, destination)
        return result;
    }

//----------------------------- Strecthes the image and it's histogram graph --------------------------------

    cv::Mat strecth(const cv::Mat &image, int minValue=0)
    {
        cv::MatND hist=getHistogram(image);  // Compute histogram first
        int imin=0;
        for(; imin<histSize[0];imin++)
        {
            std::cout<<hist.at<float>(imin)<<std::endl;  //shows imin values whish is smaller than histSize[0]
            if(hist.at<float>(imin)>minValue) break;  //if imin value is bigger then minValue break
        }

            int imax= histSize[0]-1;
            for(; imax>=0; imax--)
            {
                if(hist.at<float>(imax)>minValue) break;
            }
            int dim(256); //build a look up table
            cv::Mat lookup(1, &dim, CV_8U);

            for (int i=0; i<256; i++)
            {
                if(i<imin) lookup.at<uchar>(i)=0; //create look up table

                else if(i>imax) lookup.at<uchar>(i)=255;

                // formula creates linear i function between imin and imax
                else lookup.at<uchar>(i)=static_cast<uchar>(255.0*(i-imin)/(imax-imin)+0.5);
            }
            cv::Mat result;
            result=applyLookUp(image,lookup);
            return result;

    }


// ------------------------------ Equalize the image ------------------------------------------------
// ----------------------------- which makes it more realizable ------------------------------------
//------------------------------- shows it's histogram graph -------------------------------------
    cv::Mat equalize(const cv::Mat &image)
    {
        cv::Mat result;
        cv::equalizeHist(image,result);
        return result;
    }



};

#endif // HISTOGRAM1D_H
