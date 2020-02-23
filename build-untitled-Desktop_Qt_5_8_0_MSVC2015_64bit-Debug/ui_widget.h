/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *chooseFileButton;
    QGraphicsView *graphicsView;
    QLabel *label;
    QTextBrowser *showPath;
    QPushButton *Confirm;
    QTextBrowser *MatchFound;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(401, 529);
        chooseFileButton = new QPushButton(Widget);
        chooseFileButton->setObjectName(QStringLiteral("chooseFileButton"));
        chooseFileButton->setGeometry(QRect(40, 140, 121, 41));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setPointSize(9);
        chooseFileButton->setFont(font);
        chooseFileButton->setAutoDefault(true);
        graphicsView = new QGraphicsView(Widget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(30, 250, 341, 261));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 0, 331, 51));
        QFont font1;
        font1.setFamily(QStringLiteral("Microsoft YaHei"));
        font1.setPointSize(11);
        font1.setKerning(true);
        label->setFont(font1);
        showPath = new QTextBrowser(Widget);
        showPath->setObjectName(QStringLiteral("showPath"));
        showPath->setGeometry(QRect(30, 50, 341, 71));
        QFont font2;
        font2.setFamily(QStringLiteral("Microsoft YaHei"));
        font2.setPointSize(8);
        showPath->setFont(font2);
        Confirm = new QPushButton(Widget);
        Confirm->setObjectName(QStringLiteral("Confirm"));
        Confirm->setGeometry(QRect(240, 140, 101, 41));
        QFont font3;
        font3.setFamily(QStringLiteral("Microsoft YaHei"));
        font3.setPointSize(9);
        Confirm->setFont(font3);
        MatchFound = new QTextBrowser(Widget);
        MatchFound->setObjectName(QStringLiteral("MatchFound"));
        MatchFound->setGeometry(QRect(30, 190, 341, 41));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        chooseFileButton->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\346\272\220\346\226\207\344\273\266", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "\345\237\272\344\272\216\350\247\206\351\242\221\347\232\204\350\277\220\345\212\250\347\211\251\344\275\223\350\257\206\345\210\253", Q_NULLPTR));
        Confirm->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
