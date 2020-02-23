#ifndef WIDGET_H
#define WIDGET_H
#include "public_type.h"
#include <QWidget>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QString>
#include <QGraphicsView>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString SourceFilePath;
    void Display1(bool matchflag);
    Mat toDisplayImage;
    MatArray ExeCannyArray;
    bool Confirm = 0;
private:
    Ui::Widget *ui;
    QTimer theTimer;
    QLabel *imageLabel;

signals:
    void sendData(QString);

public slots:
    void chooseFileButton();
    void on_Confirm_clicked();
    //void DisplayMat(Mat Mimage);
};


#endif // WIDGET_H
