#include "CResolutionEditDlg.h"
#include "ui_CResolutionEditDlg.h"

CResolutionEditDlg::CResolutionEditDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CResolutionEditDlg)
{
    ui->setupUi(this);
}

CResolutionEditDlg::~CResolutionEditDlg()
{
    delete ui;
}
