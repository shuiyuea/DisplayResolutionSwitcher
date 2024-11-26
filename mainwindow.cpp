﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ChangeResolution(2560,1080);
}

void MainWindow::on_pushButton_2_clicked()
{
    ChangeResolution(1920,1080);
}

void MainWindow::ChangeResolution(int nWidth, int nHeight)
{
    DEVMODE dm;
    ZeroMemory(&dm, sizeof(dm));
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
    //dm.dmSize = sizeof(dm);
    dm.dmPelsWidth = nWidth;
    dm.dmPelsHeight = nHeight;
    //dm.dmBitsPerPel = bitDepth;
    //dm.dmDisplayFrequency = refreshRate;
    //dm.dmDisplayOrientation = orientation;
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY | DM_DISPLAYORIENTATION;

    LONG result = ChangeDisplaySettingsEx(NULL, &dm, NULL, CDS_TEST, NULL);
    if (result == DISP_CHANGE_SUCCESSFUL) {
        result = ChangeDisplaySettingsEx(NULL, &dm, NULL, 0, NULL);
        if (result == DISP_CHANGE_SUCCESSFUL) {
            qDebug() << "changed successfully!" ;
        } else {
            qDebug() << "change fail!" << result ;
        }
    } else {
        qDebug() << "Test failed to change display settings: " << result;
    }
}

void MainWindow::on_btnAdd_clicked()
{
    //添加快捷切换按钮
    if(m_mapBtn.size()==4){
        return;
    }

    QString strBtnName = "模式"+QString::number(m_mapBtn.size()+1);
    QPushButton *pBtn=new QPushButton(strBtnName);
    pBtn->setFixedSize(200,200);
    ui->groupBoxMode->layout()->addWidget(pBtn);
    m_mapBtn.insert(m_mapBtn.size()+1,pBtn);

    qDebug()<<m_mapBtn.size();
}

void MainWindow::Init()
{
    m_mapBtn.insert(1,ui->btnMode1);
}
