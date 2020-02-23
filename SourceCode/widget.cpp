#include "widget.h"
#include "ui_widget.h"
#include "contour.h"
#include "fileexecution.h"
#include "mixtureofgauss.h"
#include "canny.h"
#include "contourmatch.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //signal slot
    connect(ui->chooseFileButton, SIGNAL(clicked()), this, SLOT(chooseFileButton()));
    imageLabel = new QLabel(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::chooseFileButton()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile(*.*)"));
    ui->showPath->setText(fileName);
    this->SourceFilePath = fileName;
}



void Widget::on_Confirm_clicked()
{
    bool matchflag = 0;
    bool MatchFoundFlag = 0;
    this->Confirm = 1;
    //test if open successfully
    //ui->showPath->setText(this->SourceFilePath);
    if (this->Confirm == 1)
    {
        //Video TEST
        string SFilePath = this->SourceFilePath.toStdString();
        //Execute Input File
        MatArray SourceVideo = FileExecute(SFilePath);
        //SaveMatArray(SourceVideo, 1, 0, 1);
        MatArray ExeGauss = MOGGuass(SourceVideo);
        ExeCannyArray.counter = ExeGauss.counter;
        //SaveMatArray(ExeGauss, 1, 0, 2);
        //Set Windows to show the procedure
        namedWindow("SourceVideo");
        namedWindow("ExeGauss");
        namedWindow("ExeCanny");
        namedWindow("ExeContour");

        for (int i = 1; i < ExeGauss.counter; i++)
        {
            if(!ExeGauss.Frame[i].empty())
            {
                //Execute canny algorithm
                ExeCannyArray.Frame[i] = getCanny(ExeGauss.Frame[i]);
                //SaveMats(ExeCannyArray.Frame[i], 1, 1, 4, i);
                //set a var to save number of contour
                int ContourCount;
                //Execute findContour algorithm
                Mat ExeContour = getContour(ExeGauss.Frame[i], ContourCount, 1000);
                //Save number of contour to Disk File
                FILE *ct;
                ct = fopen("Contour_Count.txt", "a+");
                fprintf(ct, "%d\n", ContourCount);
                fclose(ct);
                waitKey(5);
                //Show execute procedure
                imshow("SourceVideo", SourceVideo.Frame[i]);
                imshow("ExeGauss",ExeGauss.Frame[i]);
                imshow("ExeCanny",ExeCannyArray.Frame[i]);
                imshow("ExeContour",ExeContour);
                if (ContourCount >= 1)
                {
                    //if there exist contour
                    Mat MatchFound;
                    //SaveMats(ExeContour, 1, 0, 3, i);
                    //execute contourMatch to find whether there are contour that match the source
                    MatchFound = contourMatch(ExeCannyArray.Frame[i], matchflag);
                    if (matchflag)
                    {
                        //if match found, display it
                        MatchFoundFlag = 1;
                        imwrite("MatchFound.jpg", MatchFound);
                        this->toDisplayImage = MatchFound;
                        Display1(matchflag);
                    }
                }
            }
        }
        //destroy the windows which showed the procedure
        destroyWindow("SourceVideo");
        destroyWindow("ExeGauss");
        destroyWindow("ExeCanny");
        destroyWindow("ExeContour");
    }
    if (!MatchFoundFlag)
    {   //if Match not found
        Mat nullImgM = imread("null.jpg");
        QImage nullImgQ = Mat2QImage(nullImgM);
        QGraphicsScene *scene = new QGraphicsScene;
        ui->MatchFound->setText("Match Source Not Found");
        scene->addPixmap(QPixmap::fromImage(nullImgQ));
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
        update();
    }
}


void Widget::Display1(bool matchflag)
{
    if (matchflag)
    {   //if Match found, display it
        Mat Mimage = this->toDisplayImage;
        imwrite("MatchFound.jpg", Mimage);
        QImage img = Mat2QImage(Mimage);
        ui->MatchFound->setText("Match Source Found");
        ui->graphicsView->updatesEnabled();
        ui->graphicsView->update();
        ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        //ui->graphicsView->resize(img.width(), img.height());
        QGraphicsScene *scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(img));
        ui->graphicsView->setScene(scene);
        //ui->graphicsView->adjustSize();
        ui->graphicsView->show();
        update();
    }
}
