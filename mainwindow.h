#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <QFileDialog>
#include <QtGui/QMainWindow>
#include <stdio.h>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionOpen_Image_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();



    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    cv::Mat image;
};


#endif // MAINWINDOW_H
