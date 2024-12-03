#ifndef CRESOLUTIONEDITDLG_H
#define CRESOLUTIONEDITDLG_H

#include <QWidget>

namespace Ui {
class CResolutionEditDlg;
}

class CResolutionEditDlg : public QWidget
{
    Q_OBJECT

public:
    explicit CResolutionEditDlg(QWidget *parent = 0);
    ~CResolutionEditDlg();

private:
    Ui::CResolutionEditDlg *ui;
};

#endif // CRESOLUTIONEDITDLG_H
