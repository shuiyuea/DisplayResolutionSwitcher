#include "mainwindow.h"
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

void MainWindow::AddResolutionBtn(const QString &strName)
{
    QString strBtnName = strName;
    if(strName.isEmpty()||strName == ""){
        strBtnName = "模式"+QString::number(m_mapBtn.size()+1);
    }
    QPushButton *pBtn = new QPushButton(strBtnName);
    pBtn->setFixedSize(200,200);
    ui->groupBoxMode->layout()->addWidget(pBtn);
    m_mapBtn.insert(pBtn,m_mapBtn.size()+1);
    connect(pBtn,&QPushButton::clicked,this,&MainWindow::SlotBtnClicked);
    qDebug()<<m_mapBtn.size();
}

void MainWindow::on_btnAdd_clicked()
{
    m_EditDlg.show();
    return;

    //添加分辨率切换按钮
    if(m_mapBtn.size()==4){
        return;
    }
    AddResolutionBtn("");
}

void MainWindow::SlotBtnClicked()
{
    //判断是哪一个按钮被按下
    QPushButton *pBtn=qobject_cast<QPushButton*>(sender());
    if(pBtn == nullptr)
    {
        return;
    }
    int nConfigNum = m_mapBtn.value(pBtn);
    qDebug() << nConfigNum;
    if(nConfigNum > m_listResolution.size())
        return;
    auto config = m_listResolution.at(nConfigNum-1);
    ChangeResolution(config.nWidth,config.nHeight);
}

void MainWindow::Init()
{
    m_mapBtn.insert(ui->btnMode1,1);
    connect(ui->btnMode1,&QPushButton::clicked,this,&MainWindow::SlotBtnClicked);

    //AddResolutionBtn("2560 x 1080");
    AddResolutionBtn("1920 x 1080");
    AddResolutionBtn("1080 x 720");

    m_listResolution.append(ResolutionConfig{2560,1080});
    m_listResolution.append(ResolutionConfig{1920,1080});
    m_listResolution.append(ResolutionConfig{1080,720});
}
