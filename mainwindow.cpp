#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mpushbutton.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    MPushButton *btn1 = new MPushButton(BtnType::hollow,"click","big","purple",this);
    layout->addWidget(btn1);
    this->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

