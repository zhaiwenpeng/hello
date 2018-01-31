#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Untitled----notepad");
    QObject::connect(ui->newAction,SIGNAL(triggered()),this,SLOT(newFileSlot()));
    QObject::connect(ui->openAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));
   // QObject::connect(ui->quitAction,SIGNAL(triggered()),this,SLOT(close());

            //edit menu系统自动提供完成
    QObject::connect(ui->undoAction,SIGNAL(triggered()),ui->textEdit,SLOT(undo()));
    QObject::connect(ui->redoAction,SIGNAL(triggered()),ui->textEdit,SLOT(redo()));
    QObject::connect(ui->copyAction,SIGNAL(triggered()),ui->textEdit,SLOT(copy()));
    QObject::connect(ui->pasteAction,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));
    QObject::connect(ui->selectAction,SIGNAL(triggered()),ui->textEdit,SLOT(select()));
    QObject::connect(ui->cutAction,SIGNAL(triggered()),ui->textEdit,SLOT(cut()));

    QObject::connect(ui->colorAction,SIGNAL(triggered()),this,SLOT(setColorSlot()));
    QObject::connect(ui->fontAction,SIGNAL(triggered()),this,SLOT(setFontSlot()));
    QObject::connect(ui->datetimeAction,SIGNAL(triggered()),this,SLOT(currentDateTimeSlot()));

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFileSlot()
{
    //如果当前文档的内容已经改变了
    if(ui->textEdit->document()->isModified())
    {
        qDebug()<<"current file modified";
    }
    else{
       // qDebug()<<"not modified";
        ui->textEdit->clear();
        this->setWindowTitle("Untitled.txt");
    }
}
void MainWindow::openFileSlot()
{
       //get the file name
    QString fileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
   // qDebug()<<"file Name is"<<fileName;
    if(fileName.isEmpty())//isNull
    {
        QMessageBox::information(this,"Error Message","Please Select a Text File");
        return;
    }
    QFile*file=new QFile;
    file->setFileName(fileName);//set file name
    bool ok=file->open(QIODevice::ReadOnly);
    //open file as read only mode

    if(ok)
    {
        //文件与文本流相关联
       QTextStream in(file);
       ui->textEdit->setText(in.readAll());//read all context from the file
       file->close();
       delete file;

    }
    else
    {
        QMessageBox::information(this,"Error message","File Open Error"+file->errorString());
        return;
    }
}

void MainWindow::saveFileSlot()
{
    if(saveFileName.isEmpty())
    {
        this->saveAsFileSlot();
    }
    else
    {
        QFile *file=new QFile;
        file->setFileName(saveFileName);
        bool ok=file->open(QIODevice::WriteOnly);
        if(ok)
        {
            QTextStream out(file);
            out<<ui->textEdit->toPlainText();//这里是取出textedit当中的纯文本
            file->close();
            delete file;
        }
    }
}

void MainWindow::saveAsFileSlot()
{
    QString saveAsFileName=QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
   //getSaveFileName
    if(saveFileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","Please Select A File");
        return;
    }
    QFile *file=new QFile;
    file->setFileName(saveFileName);
    bool ok=file->open(QIODevice::WriteOnly);
    if(ok)
    {
        QTextStream out(file);
        out<<ui->textEdit->toPlainText();//这里是取出textedit当中的纯文本
        file->close();
        this->setWindowTitle(saveFileName+"---------notepad");
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Error Message","Save File Error");
        return;
    }
}
void MainWindow::printFileSlot()
{
         //QPrintDialog static member call
 }

void MainWindow::setFontSlot()
{
    //get user selected font
    /*
  bool ok;
  QFont font = QFontDialog::getFont(
                  &ok, QFont("Helvetica [Cronyx]", 10), this);
  if (ok) {
      // the user clicked OK and font is set to the font the user selected
  } else {
      // the user canceled the dialog; font is set to the initial
      // value, in this case Helvetica [Cronyx], 10
  }*/

    bool ok;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else
    {
        QMessageBox::information(this,"Error Message","Error Set Font!!");
        return;
    }
}
void MainWindow::setColorSlot()
{
    /*
      const QColorDialog::ColorDialogOptions options = QFlag(colorDialogOptionsWidget->value());
      const QColor color = QColorDialog::getColor(Qt::green, this, "Select Color", options);

      if (color.isValid()) {
          colorLabel->setText(color.name());
          colorLabel->setPalette(QPalette(color));
          colorLabel->setAutoFillBackground(true);
      }*/
    QColor color=QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
    else
    {
        QMessageBox::information(this,"Error Message","Color is unvalid");
        return;
    }
}

void MainWindow::currentDateTimeSlot()
{
    QDateTime current=QDateTime::currentDateTime();
    QString time=current.toString("yyyy-M-dd hh:mm:ss");
    ui->textEdit->append(time);
}
