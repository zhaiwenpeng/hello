#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtDebug>//19
#include <QFile>//20
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QFontDialog>
#include <QFont>
#include <QColor>
#include <QColorDialog>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString saveFileName;
    QString saveAsFileName;
private slots :
    void newFileSlot();
    void openFileSlot();//打开一个已经存在的文本文件20
    void saveFileSlot();//保存文件到磁盘21
    void saveAsFileSlot();
    void printFileSlot();
    void setFontSlot();//设置字体的槽
    void setColorSlot();//设置文本颜色的槽
    void currentDateTimeSlot();//获取当前时间，并通过一定格式打印出来
};

#endif // MAINWINDOW_H
