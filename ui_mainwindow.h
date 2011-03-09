/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Mar 9 11:35:53 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <rendervideoframe.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *rbEncryption;
    QRadioButton *rbDecryption;
    QLabel *LState;
    RenderVideoFrame *webcam;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnPlayPause;
    QPushButton *btnFinished;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpinBox *sbNumber;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnLoad;
    QPushButton *btnSave;
    QGraphicsView *image;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *text;
    QPushButton *btnEncryptDecrypt;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1006, 697);
        QIcon icon;
        icon.addFile(QString::fromUtf8("password.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        rbEncryption = new QRadioButton(groupBox);
        rbEncryption->setObjectName(QString::fromUtf8("rbEncryption"));
        rbEncryption->setChecked(true);

        horizontalLayout_3->addWidget(rbEncryption);

        rbDecryption = new QRadioButton(groupBox);
        rbDecryption->setObjectName(QString::fromUtf8("rbDecryption"));

        horizontalLayout_3->addWidget(rbDecryption);


        verticalLayout_2->addWidget(groupBox);

        LState = new QLabel(centralWidget);
        LState->setObjectName(QString::fromUtf8("LState"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        LState->setFont(font);

        verticalLayout_2->addWidget(LState);

        webcam = new RenderVideoFrame(centralWidget);
        webcam->setObjectName(QString::fromUtf8("webcam"));
        webcam->setMinimumSize(QSize(640, 480));
        webcam->setMaximumSize(QSize(640, 480));

        verticalLayout_2->addWidget(webcam);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_4);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnPlayPause = new QPushButton(groupBox_4);
        btnPlayPause->setObjectName(QString::fromUtf8("btnPlayPause"));

        horizontalLayout_2->addWidget(btnPlayPause);

        btnFinished = new QPushButton(groupBox_4);
        btnFinished->setObjectName(QString::fromUtf8("btnFinished"));
        btnFinished->setEnabled(false);

        horizontalLayout_2->addWidget(btnFinished);


        verticalLayout_2->addWidget(groupBox_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label);

        sbNumber = new QSpinBox(centralWidget);
        sbNumber->setObjectName(QString::fromUtf8("sbNumber"));
        sbNumber->setMinimum(8196);
        sbNumber->setMaximum(2147483647);

        horizontalLayout_4->addWidget(sbNumber);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        btnLoad = new QPushButton(groupBox_2);
        btnLoad->setObjectName(QString::fromUtf8("btnLoad"));

        horizontalLayout_5->addWidget(btnLoad);

        btnSave = new QPushButton(groupBox_2);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setEnabled(false);

        horizontalLayout_5->addWidget(btnSave);


        verticalLayout_3->addWidget(groupBox_2);

        image = new QGraphicsView(centralWidget);
        image->setObjectName(QString::fromUtf8("image"));
        image->setMinimumSize(QSize(350, 300));
        image->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_3->addWidget(image);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        text = new QPlainTextEdit(groupBox_3);
        text->setObjectName(QString::fromUtf8("text"));
        text->setMinimumSize(QSize(0, 223));
        text->setTabChangesFocus(true);
        text->setUndoRedoEnabled(true);

        verticalLayout->addWidget(text);

        btnEncryptDecrypt = new QPushButton(groupBox_3);
        btnEncryptDecrypt->setObjectName(QString::fromUtf8("btnEncryptDecrypt"));
        btnEncryptDecrypt->setEnabled(false);

        verticalLayout->addWidget(btnEncryptDecrypt);


        verticalLayout_3->addWidget(groupBox_3);


        horizontalLayout->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Stecrypt", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Select action", 0, QApplication::UnicodeUTF8));
        rbEncryption->setText(QApplication::translate("MainWindow", "Encryption", 0, QApplication::UnicodeUTF8));
        rbDecryption->setText(QApplication::translate("MainWindow", "Decryption", 0, QApplication::UnicodeUTF8));
        LState->setText(QApplication::translate("MainWindow", "Use webcam to select input key or instead type in some huge number into the Number field below.", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Webcam", 0, QApplication::UnicodeUTF8));
        btnPlayPause->setText(QApplication::translate("MainWindow", "Launch", 0, QApplication::UnicodeUTF8));
        btnFinished->setText(QApplication::translate("MainWindow", "Finished!", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Number", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Image", 0, QApplication::UnicodeUTF8));
        btnLoad->setText(QApplication::translate("MainWindow", "Load", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Text", 0, QApplication::UnicodeUTF8));
        btnEncryptDecrypt->setText(QApplication::translate("MainWindow", "Encrypt", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
