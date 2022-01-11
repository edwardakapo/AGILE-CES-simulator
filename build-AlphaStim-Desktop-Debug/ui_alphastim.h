/********************************************************************************
** Form generated from reading UI file 'alphastim.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALPHASTIM_H
#define UI_ALPHASTIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlphaStim
{
public:
    QWidget *centralwidget;
    QPushButton *power_button;
    QFrame *screen;
    QProgressBar *battery;
    QLineEdit *timer;
    QTextEdit *text_display;
    QProgressBar *intensity_level;
    QLabel *intensity_1;
    QLabel *intensity_2;
    QLabel *intensity_3;
    QLabel *intensity_4;
    QLabel *intensity_5;
    QLabel *label;
    QLabel *test_circuit;
    QFrame *controls;
    QPushButton *yes;
    QPushButton *no;
    QPushButton *show_records;
    QPushButton *up;
    QPushButton *down;
    QPushButton *start;
    QPushButton *frequency_button;
    QLabel *frequency_label_0;
    QLabel *frequency_label_2;
    QPushButton *waveform_button;
    QLabel *waveform_label_0;
    QLabel *waveform_label_1;
    QPushButton *duration_button;
    QLabel *duration_label_0;
    QLabel *duration_label_2;
    QLabel *duration_label_1;
    QLabel *waveform_label_2;
    QLabel *frequency_label_1;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QPushButton *electrode_1;
    QPushButton *electrode_2;
    QFrame *admin;
    QPushButton *test_9;
    QPushButton *test_8;
    QPushButton *swap_batteries;
    QPushButton *test_1;
    QPushButton *test_2;
    QLabel *test_label_1;
    QLabel *test_title;
    QLabel *test_label_2;
    QPushButton *test_3;
    QLabel *test_label_3;
    QLabel *test_label_4;
    QPushButton *test_4;
    QLabel *test_label_8;
    QLabel *test_label_9;
    QLabel *label_4;
    QLabel *test_label_5;
    QPushButton *test_5;
    QLabel *test_label_6;
    QPushButton *test_6;
    QLabel *label_5;
    QPushButton *test_7;
    QLabel *test_label_7;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AlphaStim)
    {
        if (AlphaStim->objectName().isEmpty())
            AlphaStim->setObjectName(QString::fromUtf8("AlphaStim"));
        AlphaStim->resize(1117, 717);
        centralwidget = new QWidget(AlphaStim);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        power_button = new QPushButton(centralwidget);
        power_button->setObjectName(QString::fromUtf8("power_button"));
        power_button->setGeometry(QRect(10, 10, 111, 91));
        power_button->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background:rgb(237, 212, 0)\n"
"}"));
        power_button->setCheckable(true);
        screen = new QFrame(centralwidget);
        screen->setObjectName(QString::fromUtf8("screen"));
        screen->setEnabled(false);
        screen->setGeometry(QRect(140, 10, 411, 431));
        screen->setStyleSheet(QString::fromUtf8("background:rgb(238, 238, 236)"));
        screen->setFrameShape(QFrame::Box);
        screen->setFrameShadow(QFrame::Plain);
        screen->setLineWidth(2);
        screen->setMidLineWidth(0);
        battery = new QProgressBar(screen);
        battery->setObjectName(QString::fromUtf8("battery"));
        battery->setGeometry(QRect(20, 40, 374, 31));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        battery->setFont(font);
        battery->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"	border: 2px solid grey;\n"
"	border-radius: 5px;\n"
"	text-align: center;\n"
"}\n"
"QProgressBar::chunk:enabled {\n"
"	background-color:rgb(138, 226, 52);\n"
"	border-radius: 5px;\n"
"}\n"
"QProgressBar::chunk:!enabled {\n"
"	background-color:rgb(238, 238, 236);\n"
"	border-radius: 5px;\n"
"}"));
        battery->setValue(100);
        battery->setInvertedAppearance(false);
        timer = new QLineEdit(screen);
        timer->setObjectName(QString::fromUtf8("timer"));
        timer->setGeometry(QRect(20, 80, 374, 131));
        QFont font1;
        font1.setPointSize(50);
        timer->setFont(font1);
        timer->setAlignment(Qt::AlignCenter);
        timer->setReadOnly(true);
        text_display = new QTextEdit(screen);
        text_display->setObjectName(QString::fromUtf8("text_display"));
        text_display->setGeometry(QRect(20, 290, 374, 131));
        text_display->setStyleSheet(QString::fromUtf8("QTextEdit::disabled{\n"
"color:rgb(0, 0, 0);\n"
"}"));
        text_display->setReadOnly(true);
        intensity_level = new QProgressBar(screen);
        intensity_level->setObjectName(QString::fromUtf8("intensity_level"));
        intensity_level->setGeometry(QRect(20, 250, 374, 31));
        intensity_level->setFont(font);
        intensity_level->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"	border: 2px solid grey;\n"
"	border-radius: 5px;\n"
"	text-align: center;\n"
"}\n"
"QProgressBar::chunk {\n"
"	background-color:rgb(138, 226, 52);\n"
"	border-radius: 5px;\n"
"	width: 35px;\n"
"	margin: 0.5px\n"
"}"));
        intensity_level->setMaximum(500);
        intensity_level->setValue(0);
        intensity_level->setInvertedAppearance(false);
        intensity_1 = new QLabel(screen);
        intensity_1->setObjectName(QString::fromUtf8("intensity_1"));
        intensity_1->setGeometry(QRect(80, 220, 31, 21));
        QFont font2;
        font2.setPointSize(16);
        intensity_1->setFont(font2);
        intensity_1->setAlignment(Qt::AlignCenter);
        intensity_2 = new QLabel(screen);
        intensity_2->setObjectName(QString::fromUtf8("intensity_2"));
        intensity_2->setGeometry(QRect(160, 220, 21, 21));
        intensity_2->setFont(font2);
        intensity_2->setAlignment(Qt::AlignCenter);
        intensity_3 = new QLabel(screen);
        intensity_3->setObjectName(QString::fromUtf8("intensity_3"));
        intensity_3->setGeometry(QRect(230, 220, 31, 21));
        intensity_3->setFont(font2);
        intensity_3->setAlignment(Qt::AlignCenter);
        intensity_4 = new QLabel(screen);
        intensity_4->setObjectName(QString::fromUtf8("intensity_4"));
        intensity_4->setGeometry(QRect(300, 220, 31, 21));
        intensity_4->setFont(font2);
        intensity_4->setAlignment(Qt::AlignCenter);
        intensity_5 = new QLabel(screen);
        intensity_5->setObjectName(QString::fromUtf8("intensity_5"));
        intensity_5->setGeometry(QRect(380, 220, 21, 21));
        intensity_5->setFont(font2);
        intensity_5->setAlignment(Qt::AlignCenter);
        label = new QLabel(screen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 111, 17));
        QFont font3;
        font3.setPointSize(14);
        label->setFont(font3);
        test_circuit = new QLabel(screen);
        test_circuit->setObjectName(QString::fromUtf8("test_circuit"));
        test_circuit->setEnabled(false);
        test_circuit->setGeometry(QRect(140, 10, 131, 17));
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        font4.setWeight(75);
        test_circuit->setFont(font4);
        test_circuit->setStyleSheet(QString::fromUtf8("color:rgb(239, 41, 41)"));
        controls = new QFrame(centralwidget);
        controls->setObjectName(QString::fromUtf8("controls"));
        controls->setEnabled(false);
        controls->setGeometry(QRect(140, 440, 411, 221));
        controls->setStyleSheet(QString::fromUtf8("background:rgb(186, 189, 182)"));
        controls->setFrameShape(QFrame::Box);
        controls->setFrameShadow(QFrame::Plain);
        controls->setLineWidth(2);
        yes = new QPushButton(controls);
        yes->setObjectName(QString::fromUtf8("yes"));
        yes->setGeometry(QRect(20, 10, 81, 31));
        no = new QPushButton(controls);
        no->setObjectName(QString::fromUtf8("no"));
        no->setGeometry(QRect(110, 10, 81, 31));
        show_records = new QPushButton(controls);
        show_records->setObjectName(QString::fromUtf8("show_records"));
        show_records->setGeometry(QRect(20, 50, 171, 31));
        up = new QPushButton(controls);
        up->setObjectName(QString::fromUtf8("up"));
        up->setGeometry(QRect(220, 10, 81, 31));
        down = new QPushButton(controls);
        down->setObjectName(QString::fromUtf8("down"));
        down->setGeometry(QRect(310, 10, 81, 31));
        start = new QPushButton(controls);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(220, 50, 171, 31));
        frequency_button = new QPushButton(controls);
        frequency_button->setObjectName(QString::fromUtf8("frequency_button"));
        frequency_button->setGeometry(QRect(20, 100, 171, 25));
        frequency_label_0 = new QLabel(controls);
        frequency_label_0->setObjectName(QString::fromUtf8("frequency_label_0"));
        frequency_label_0->setGeometry(QRect(220, 100, 51, 21));
        frequency_label_0->setStyleSheet(QString::fromUtf8(""));
        frequency_label_0->setAlignment(Qt::AlignCenter);
        frequency_label_2 = new QLabel(controls);
        frequency_label_2->setObjectName(QString::fromUtf8("frequency_label_2"));
        frequency_label_2->setGeometry(QRect(340, 100, 51, 21));
        frequency_label_2->setStyleSheet(QString::fromUtf8(""));
        frequency_label_2->setAlignment(Qt::AlignCenter);
        waveform_button = new QPushButton(controls);
        waveform_button->setObjectName(QString::fromUtf8("waveform_button"));
        waveform_button->setGeometry(QRect(20, 140, 171, 25));
        waveform_label_0 = new QLabel(controls);
        waveform_label_0->setObjectName(QString::fromUtf8("waveform_label_0"));
        waveform_label_0->setGeometry(QRect(230, 140, 31, 21));
        waveform_label_0->setStyleSheet(QString::fromUtf8(""));
        waveform_label_0->setAlignment(Qt::AlignCenter);
        waveform_label_1 = new QLabel(controls);
        waveform_label_1->setObjectName(QString::fromUtf8("waveform_label_1"));
        waveform_label_1->setGeometry(QRect(290, 140, 31, 21));
        waveform_label_1->setStyleSheet(QString::fromUtf8(""));
        waveform_label_1->setAlignment(Qt::AlignCenter);
        duration_button = new QPushButton(controls);
        duration_button->setObjectName(QString::fromUtf8("duration_button"));
        duration_button->setGeometry(QRect(20, 180, 171, 25));
        duration_label_0 = new QLabel(controls);
        duration_label_0->setObjectName(QString::fromUtf8("duration_label_0"));
        duration_label_0->setGeometry(QRect(220, 180, 51, 31));
        duration_label_0->setStyleSheet(QString::fromUtf8(""));
        duration_label_0->setAlignment(Qt::AlignCenter);
        duration_label_2 = new QLabel(controls);
        duration_label_2->setObjectName(QString::fromUtf8("duration_label_2"));
        duration_label_2->setGeometry(QRect(340, 180, 51, 31));
        duration_label_2->setStyleSheet(QString::fromUtf8(""));
        duration_label_2->setAlignment(Qt::AlignCenter);
        duration_label_1 = new QLabel(controls);
        duration_label_1->setObjectName(QString::fromUtf8("duration_label_1"));
        duration_label_1->setGeometry(QRect(280, 180, 51, 31));
        duration_label_1->setStyleSheet(QString::fromUtf8(""));
        duration_label_1->setAlignment(Qt::AlignCenter);
        waveform_label_2 = new QLabel(controls);
        waveform_label_2->setObjectName(QString::fromUtf8("waveform_label_2"));
        waveform_label_2->setGeometry(QRect(340, 140, 61, 21));
        waveform_label_2->setStyleSheet(QString::fromUtf8(""));
        waveform_label_2->setAlignment(Qt::AlignCenter);
        frequency_label_1 = new QLabel(controls);
        frequency_label_1->setObjectName(QString::fromUtf8("frequency_label_1"));
        frequency_label_1->setGeometry(QRect(280, 100, 51, 21));
        frequency_label_1->setStyleSheet(QString::fromUtf8(""));
        frequency_label_1->setAlignment(Qt::AlignCenter);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(580, 110, 241, 16));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(3);
        line->setFrameShape(QFrame::HLine);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(820, 60, 111, 21));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setLineWidth(3);
        line_2->setFrameShape(QFrame::HLine);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(820, 170, 111, 21));
        line_3->setFrameShadow(QFrame::Plain);
        line_3->setLineWidth(3);
        line_3->setFrameShape(QFrame::HLine);
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(810, 70, 16, 111));
        line_4->setFrameShadow(QFrame::Plain);
        line_4->setLineWidth(3);
        line_4->setFrameShape(QFrame::VLine);
        electrode_1 = new QPushButton(centralwidget);
        electrode_1->setObjectName(QString::fromUtf8("electrode_1"));
        electrode_1->setGeometry(QRect(930, 34, 171, 71));
        electrode_1->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background:rgb(237, 212, 0)\n"
"}"));
        electrode_1->setCheckable(true);
        electrode_2 = new QPushButton(centralwidget);
        electrode_2->setObjectName(QString::fromUtf8("electrode_2"));
        electrode_2->setGeometry(QRect(930, 144, 171, 71));
        electrode_2->setStyleSheet(QString::fromUtf8("QPushButton::checked{\n"
"	background:rgb(237, 212, 0)\n"
"}"));
        electrode_2->setCheckable(true);
        admin = new QFrame(centralwidget);
        admin->setObjectName(QString::fromUtf8("admin"));
        admin->setGeometry(QRect(570, 240, 531, 421));
        admin->setFrameShape(QFrame::StyledPanel);
        admin->setFrameShadow(QFrame::Raised);
        test_9 = new QPushButton(admin);
        test_9->setObjectName(QString::fromUtf8("test_9"));
        test_9->setGeometry(QRect(10, 360, 81, 25));
        test_8 = new QPushButton(admin);
        test_8->setObjectName(QString::fromUtf8("test_8"));
        test_8->setGeometry(QRect(10, 330, 81, 25));
        swap_batteries = new QPushButton(admin);
        swap_batteries->setObjectName(QString::fromUtf8("swap_batteries"));
        swap_batteries->setGeometry(QRect(140, 10, 251, 41));
        test_1 = new QPushButton(admin);
        test_1->setObjectName(QString::fromUtf8("test_1"));
        test_1->setGeometry(QRect(10, 120, 80, 25));
        test_1->setStyleSheet(QString::fromUtf8(""));
        test_2 = new QPushButton(admin);
        test_2->setObjectName(QString::fromUtf8("test_2"));
        test_2->setGeometry(QRect(10, 150, 80, 25));
        test_label_1 = new QLabel(admin);
        test_label_1->setObjectName(QString::fromUtf8("test_label_1"));
        test_label_1->setGeometry(QRect(100, 120, 411, 21));
        test_title = new QLabel(admin);
        test_title->setObjectName(QString::fromUtf8("test_title"));
        test_title->setGeometry(QRect(10, 90, 511, 21));
        test_title->setFont(font);
        test_label_2 = new QLabel(admin);
        test_label_2->setObjectName(QString::fromUtf8("test_label_2"));
        test_label_2->setGeometry(QRect(100, 150, 411, 21));
        test_3 = new QPushButton(admin);
        test_3->setObjectName(QString::fromUtf8("test_3"));
        test_3->setGeometry(QRect(10, 180, 80, 25));
        test_label_3 = new QLabel(admin);
        test_label_3->setObjectName(QString::fromUtf8("test_label_3"));
        test_label_3->setGeometry(QRect(100, 180, 421, 21));
        test_label_4 = new QLabel(admin);
        test_label_4->setObjectName(QString::fromUtf8("test_label_4"));
        test_label_4->setGeometry(QRect(100, 210, 411, 21));
        test_4 = new QPushButton(admin);
        test_4->setObjectName(QString::fromUtf8("test_4"));
        test_4->setGeometry(QRect(10, 210, 80, 25));
        test_label_8 = new QLabel(admin);
        test_label_8->setObjectName(QString::fromUtf8("test_label_8"));
        test_label_8->setGeometry(QRect(100, 330, 411, 21));
        test_label_9 = new QLabel(admin);
        test_label_9->setObjectName(QString::fromUtf8("test_label_9"));
        test_label_9->setGeometry(QRect(100, 360, 411, 21));
        label_4 = new QLabel(admin);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 70, 111, 17));
        test_label_5 = new QLabel(admin);
        test_label_5->setObjectName(QString::fromUtf8("test_label_5"));
        test_label_5->setGeometry(QRect(100, 240, 411, 21));
        test_5 = new QPushButton(admin);
        test_5->setObjectName(QString::fromUtf8("test_5"));
        test_5->setGeometry(QRect(10, 240, 81, 25));
        test_label_6 = new QLabel(admin);
        test_label_6->setObjectName(QString::fromUtf8("test_label_6"));
        test_label_6->setGeometry(QRect(100, 270, 411, 21));
        test_6 = new QPushButton(admin);
        test_6->setObjectName(QString::fromUtf8("test_6"));
        test_6->setGeometry(QRect(10, 270, 81, 25));
        label_5 = new QLabel(admin);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 390, 271, 17));
        test_7 = new QPushButton(admin);
        test_7->setObjectName(QString::fromUtf8("test_7"));
        test_7->setGeometry(QRect(10, 300, 81, 25));
        test_label_7 = new QLabel(admin);
        test_label_7->setObjectName(QString::fromUtf8("test_label_7"));
        test_label_7->setGeometry(QRect(100, 300, 411, 21));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(570, 220, 91, 17));
        AlphaStim->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AlphaStim);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1117, 22));
        AlphaStim->setMenuBar(menubar);
        statusbar = new QStatusBar(AlphaStim);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AlphaStim->setStatusBar(statusbar);

        retranslateUi(AlphaStim);

        QMetaObject::connectSlotsByName(AlphaStim);
    } // setupUi

    void retranslateUi(QMainWindow *AlphaStim)
    {
        AlphaStim->setWindowTitle(QApplication::translate("AlphaStim", "AlphaStim", nullptr));
        power_button->setText(QApplication::translate("AlphaStim", "Power On/Off", nullptr));
        battery->setFormat(QApplication::translate("AlphaStim", "Battery %p%", nullptr));
        timer->setText(QApplication::translate("AlphaStim", "00:00:00", nullptr));
        text_display->setPlaceholderText(QString());
        intensity_level->setFormat(QApplication::translate("AlphaStim", "Intensity Level %v\316\274a", nullptr));
        intensity_1->setText(QApplication::translate("AlphaStim", "1", nullptr));
        intensity_2->setText(QApplication::translate("AlphaStim", "2", nullptr));
        intensity_3->setText(QApplication::translate("AlphaStim", "3", nullptr));
        intensity_4->setText(QApplication::translate("AlphaStim", "4", nullptr));
        intensity_5->setText(QApplication::translate("AlphaStim", "5", nullptr));
        label->setText(QApplication::translate("AlphaStim", "Test Circuit:", nullptr));
        test_circuit->setText(QApplication::translate("AlphaStim", "Disconnected", nullptr));
        yes->setText(QApplication::translate("AlphaStim", "Yes", nullptr));
        no->setText(QApplication::translate("AlphaStim", "No", nullptr));
        show_records->setText(QApplication::translate("AlphaStim", "Show/Hide Records", nullptr));
        up->setText(QApplication::translate("AlphaStim", "Up", nullptr));
        down->setText(QApplication::translate("AlphaStim", "Down", nullptr));
        start->setText(QApplication::translate("AlphaStim", "Start", nullptr));
        frequency_button->setText(QApplication::translate("AlphaStim", "Frequency (Hz)", nullptr));
        frequency_label_0->setText(QApplication::translate("AlphaStim", "0.5", nullptr));
        frequency_label_2->setText(QApplication::translate("AlphaStim", "100", nullptr));
        waveform_button->setText(QApplication::translate("AlphaStim", "Waveform", nullptr));
        waveform_label_0->setText(QApplication::translate("AlphaStim", "Alpha", nullptr));
        waveform_label_1->setText(QApplication::translate("AlphaStim", "Beta", nullptr));
        duration_button->setText(QApplication::translate("AlphaStim", "Timer (min)", nullptr));
        duration_label_0->setText(QApplication::translate("AlphaStim", "20", nullptr));
        duration_label_2->setText(QApplication::translate("AlphaStim", "60", nullptr));
        duration_label_1->setText(QApplication::translate("AlphaStim", "40", nullptr));
        waveform_label_2->setText(QApplication::translate("AlphaStim", "Gamma", nullptr));
        frequency_label_1->setText(QApplication::translate("AlphaStim", "77", nullptr));
        electrode_1->setText(QApplication::translate("AlphaStim", "Electrode 1", nullptr));
        electrode_2->setText(QApplication::translate("AlphaStim", "Electrode 2", nullptr));
        test_9->setText(QApplication::translate("AlphaStim", "Test 9", nullptr));
        test_8->setText(QApplication::translate("AlphaStim", "Test 8", nullptr));
        swap_batteries->setText(QApplication::translate("AlphaStim", "Swap Batteries?", nullptr));
        test_1->setText(QApplication::translate("AlphaStim", "Test 1", nullptr));
        test_2->setText(QApplication::translate("AlphaStim", "Test 2", nullptr));
        test_label_1->setText(QApplication::translate("AlphaStim", "Toggles power on and off several times.", nullptr));
        test_title->setText(QApplication::translate("AlphaStim", "Tests should be run from POWERED OFF+DISCONNECTED state and separately.", nullptr));
        test_label_2->setText(QApplication::translate("AlphaStim", "Connects and disconnects electrodes to show test circuit.", nullptr));
        test_3->setText(QApplication::translate("AlphaStim", "Test 3", nullptr));
        test_label_3->setText(QApplication::translate("AlphaStim", "Increases and decreases the current intensity checking min-max bounds.", nullptr));
        test_label_4->setText(QApplication::translate("AlphaStim", "Configures and starts a therapy session.", nullptr));
        test_4->setText(QApplication::translate("AlphaStim", "Test 4", nullptr));
        test_label_8->setText(QApplication::translate("AlphaStim", "Forces a low battery state and checks for warnings.", nullptr));
        test_label_9->setText(QApplication::translate("AlphaStim", "Simulates a fault which causes 700\316\274a intensity.", nullptr));
        label_4->setText(QApplication::translate("AlphaStim", "Automated Tests:", nullptr));
        test_label_5->setText(QApplication::translate("AlphaStim", "Check basic system configuration", nullptr));
        test_5->setText(QApplication::translate("AlphaStim", "Test 5", nullptr));
        test_label_6->setText(QApplication::translate("AlphaStim", "Save Therapy Session", nullptr));
        test_6->setText(QApplication::translate("AlphaStim", "Test 6", nullptr));
        label_5->setText(QApplication::translate("AlphaStim", "Read console logs for state verification steps.", nullptr));
        test_7->setText(QApplication::translate("AlphaStim", "Test 7", nullptr));
        test_label_7->setText(QApplication::translate("AlphaStim", "Simulate 30 minute auto off", nullptr));
        label_3->setText(QApplication::translate("AlphaStim", "Admin Controls", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlphaStim: public Ui_AlphaStim {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALPHASTIM_H
