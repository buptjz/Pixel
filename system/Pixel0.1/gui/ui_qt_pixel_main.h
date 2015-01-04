/********************************************************************************
** Form generated from reading UI file 'qt_pixel_main.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_PIXEL_MAIN_H
#define UI_QT_PIXEL_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *TabSegment;
    QGroupBox *groupBox_7;
    QPushButton *opensampleImageBtn_3;
    QGraphicsView *sampleImageView_3;
    QPushButton *searchBtn_3;
    QLabel *label_3;
    QComboBox *MatchType_3;
    QPushButton *pushButton_4;
    QComboBox *MatchType_4;
    QPushButton *searchBtn_4;
    QPushButton *pushButton_5;
    QLabel *label_4;
    QGroupBox *groupBox_8;
    QListWidget *ImagePatchView_3;
    QPushButton *pushButton_6;
    QWidget *TabSearch;
    QGroupBox *groupBox_2;
    QPushButton *OpensampleImageBtn;
    QGraphicsView *SampleImageView;
    QPushButton *SearchBtn;
    QLabel *label_2;
    QComboBox *MatchType;
    QPushButton *pushButton;
    QGroupBox *groupBox_3;
    QListWidget *SuperImagePatchView;
    QListWidget *ImagePatchView;
    QWidget *tab;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QGroupBox *groupBox;
    QPushButton *OpenImageLibBtn;
    QLineEdit *ImageLibPath;
    QCommandLinkButton *AddinLibBtn;
    QGroupBox *groupBox_4;
    QTextEdit *LogDisplay_2;
    QGroupBox *log;
    QTextEdit *LogDisplay;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(791, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(15, 5, 766, 416));
        tabWidget->setUsesScrollButtons(true);
        TabSegment = new QWidget();
        TabSegment->setObjectName(QStringLiteral("TabSegment"));
        TabSegment->setEnabled(true);
        groupBox_7 = new QGroupBox(TabSegment);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setEnabled(true);
        groupBox_7->setGeometry(QRect(10, 10, 201, 381));
        groupBox_7->setCheckable(false);
        opensampleImageBtn_3 = new QPushButton(groupBox_7);
        opensampleImageBtn_3->setObjectName(QStringLiteral("opensampleImageBtn_3"));
        opensampleImageBtn_3->setEnabled(true);
        opensampleImageBtn_3->setGeometry(QRect(10, 20, 171, 21));
        sampleImageView_3 = new QGraphicsView(groupBox_7);
        sampleImageView_3->setObjectName(QStringLiteral("sampleImageView_3"));
        sampleImageView_3->setEnabled(true);
        sampleImageView_3->setGeometry(QRect(10, 50, 171, 131));
        sampleImageView_3->setFrameShape(QFrame::NoFrame);
        sampleImageView_3->setFrameShadow(QFrame::Plain);
        searchBtn_3 = new QPushButton(groupBox_7);
        searchBtn_3->setObjectName(QStringLiteral("searchBtn_3"));
        searchBtn_3->setEnabled(true);
        searchBtn_3->setGeometry(QRect(20, 250, 161, 24));
        label_3 = new QLabel(groupBox_7);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(true);
        label_3->setGeometry(QRect(20, 190, 54, 12));
        MatchType_3 = new QComboBox(groupBox_7);
        MatchType_3->setObjectName(QStringLiteral("MatchType_3"));
        MatchType_3->setEnabled(true);
        MatchType_3->setGeometry(QRect(90, 185, 91, 21));
        pushButton_4 = new QPushButton(groupBox_7);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setEnabled(true);
        pushButton_4->setGeometry(QRect(20, 220, 161, 23));
        MatchType_4 = new QComboBox(groupBox_7);
        MatchType_4->setObjectName(QStringLiteral("MatchType_4"));
        MatchType_4->setEnabled(true);
        MatchType_4->setGeometry(QRect(90, 285, 91, 21));
        searchBtn_4 = new QPushButton(groupBox_7);
        searchBtn_4->setObjectName(QStringLiteral("searchBtn_4"));
        searchBtn_4->setEnabled(true);
        searchBtn_4->setGeometry(QRect(20, 350, 161, 24));
        pushButton_5 = new QPushButton(groupBox_7);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setEnabled(true);
        pushButton_5->setGeometry(QRect(20, 320, 161, 23));
        label_4 = new QLabel(groupBox_7);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setEnabled(true);
        label_4->setGeometry(QRect(20, 290, 54, 12));
        groupBox_8 = new QGroupBox(TabSegment);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setEnabled(true);
        groupBox_8->setGeometry(QRect(235, 15, 516, 381));
        ImagePatchView_3 = new QListWidget(groupBox_8);
        ImagePatchView_3->setObjectName(QStringLiteral("ImagePatchView_3"));
        ImagePatchView_3->setEnabled(true);
        ImagePatchView_3->setGeometry(QRect(10, 25, 491, 291));
        pushButton_6 = new QPushButton(groupBox_8);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setEnabled(true);
        pushButton_6->setGeometry(QRect(10, 320, 491, 51));
        tabWidget->addTab(TabSegment, QString());
        TabSearch = new QWidget();
        TabSearch->setObjectName(QStringLiteral("TabSearch"));
        groupBox_2 = new QGroupBox(TabSearch);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 201, 361));
        OpensampleImageBtn = new QPushButton(groupBox_2);
        OpensampleImageBtn->setObjectName(QStringLiteral("OpensampleImageBtn"));
        OpensampleImageBtn->setGeometry(QRect(20, 20, 171, 21));
        SampleImageView = new QGraphicsView(groupBox_2);
        SampleImageView->setObjectName(QStringLiteral("SampleImageView"));
        SampleImageView->setGeometry(QRect(20, 50, 171, 171));
        SampleImageView->setFrameShape(QFrame::NoFrame);
        SampleImageView->setFrameShadow(QFrame::Plain);
        SearchBtn = new QPushButton(groupBox_2);
        SearchBtn->setObjectName(QStringLiteral("SearchBtn"));
        SearchBtn->setGeometry(QRect(20, 320, 161, 24));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 240, 54, 12));
        MatchType = new QComboBox(groupBox_2);
        MatchType->setObjectName(QStringLiteral("MatchType"));
        MatchType->setGeometry(QRect(90, 235, 91, 21));
        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 270, 161, 23));
        groupBox_3 = new QGroupBox(TabSearch);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(240, 10, 506, 366));
        SuperImagePatchView = new QListWidget(groupBox_3);
        SuperImagePatchView->setObjectName(QStringLiteral("SuperImagePatchView"));
        SuperImagePatchView->setGeometry(QRect(10, 20, 481, 131));
        ImagePatchView = new QListWidget(groupBox_3);
        ImagePatchView->setObjectName(QStringLiteral("ImagePatchView"));
        ImagePatchView->setEnabled(true);
        ImagePatchView->setGeometry(QRect(10, 160, 476, 196));
        tabWidget->addTab(TabSearch, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 220, 161, 23));
        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 150, 161, 23));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 701, 81));
        OpenImageLibBtn = new QPushButton(groupBox);
        OpenImageLibBtn->setObjectName(QStringLiteral("OpenImageLibBtn"));
        OpenImageLibBtn->setGeometry(QRect(20, 30, 75, 23));
        ImageLibPath = new QLineEdit(groupBox);
        ImageLibPath->setObjectName(QStringLiteral("ImageLibPath"));
        ImageLibPath->setGeometry(QRect(110, 30, 431, 20));
        AddinLibBtn = new QCommandLinkButton(groupBox);
        AddinLibBtn->setObjectName(QStringLiteral("AddinLibBtn"));
        AddinLibBtn->setGeometry(QRect(550, 20, 131, 41));
        AddinLibBtn->setIconSize(QSize(16, 16));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(35, 395, 711, 121));
        LogDisplay_2 = new QTextEdit(groupBox_4);
        LogDisplay_2->setObjectName(QStringLiteral("LogDisplay_2"));
        LogDisplay_2->setGeometry(QRect(20, 20, 671, 91));
        tabWidget->addTab(tab, QString());
        log = new QGroupBox(centralwidget);
        log->setObjectName(QStringLiteral("log"));
        log->setEnabled(true);
        log->setGeometry(QRect(15, 435, 766, 121));
        LogDisplay = new QTextEdit(log);
        LogDisplay->setObjectName(QStringLiteral("LogDisplay"));
        LogDisplay->setEnabled(true);
        LogDisplay->setGeometry(QRect(30, 20, 706, 81));
        MainWindow->setCentralWidget(centralwidget);
        log->raise();
        tabWidget->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 791, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "\351\200\211\346\213\251", 0));
        opensampleImageBtn_3->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\345\276\205\345\210\206\345\211\262\345\233\276\345\203\217", 0));
        searchBtn_3->setText(QApplication::translate("MainWindow", "\345\210\206\345\211\262", 0));
        label_3->setText(QApplication::translate("MainWindow", "\345\210\206\345\211\262\346\226\271\346\263\225", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "\345\210\206\345\211\262\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        searchBtn_4->setText(QApplication::translate("MainWindow", "\345\216\273\351\207\215", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "\345\216\273\351\207\215\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        label_4->setText(QApplication::translate("MainWindow", "\345\216\273\351\207\215\346\226\271\346\263\225", 0));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "\345\210\206\345\211\262\345\233\276\345\205\203\345\261\225\347\244\272", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "\345\210\206\345\211\262\347\273\223\346\236\234\345\255\230\345\205\245\346\225\260\346\215\256\345\272\223", 0));
        tabWidget->setTabText(tabWidget->indexOf(TabSegment), QApplication::translate("MainWindow", "\345\210\206\345\211\262", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\351\200\211\346\213\251", 0));
        OpensampleImageBtn->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\240\267\346\234\254\345\233\276", 0));
        SearchBtn->setText(QApplication::translate("MainWindow", "\346\220\234  \347\264\242", 0));
        label_2->setText(QApplication::translate("MainWindow", "\345\214\271\351\205\215\346\226\271\346\263\225", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\345\214\271\351\205\215\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\346\243\200\347\264\242\347\273\223\346\236\234", 0));
        tabWidget->setTabText(tabWidget->indexOf(TabSearch), QApplication::translate("MainWindow", "\346\243\200\347\264\242", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\345\214\271\351\205\215\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "\345\210\206\345\211\262\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\272\223", 0));
        OpenImageLibBtn->setText(QApplication::translate("MainWindow", "\345\233\276\347\211\207\345\272\223", 0));
        AddinLibBtn->setText(QApplication::translate("MainWindow", "\345\212\240\345\205\245\345\233\276\345\203\217\345\272\223", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\346\227\245\345\277\227\346\211\223\345\215\260", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\346\211\271\351\207\217\345\205\245\345\272\223", 0));
        log->setTitle(QApplication::translate("MainWindow", "\346\227\245\345\277\227\346\211\223\345\215\260", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_PIXEL_MAIN_H
