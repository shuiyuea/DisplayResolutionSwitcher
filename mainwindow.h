#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include <QMap>
#include "CResolutionEditDlg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();

    void SlotBtnClicked();

private:
    Ui::MainWindow *ui;

private:
    void Init();
    void ChangeResolution(int nWidth,int nHeight);
    void AddResolutionBtn(const QString& strName);

private:
    QMap<QPushButton*,int> m_mapBtn;
    struct ResolutionConfig{
        int nWidth;
        int nHeight;
    };
    QList<ResolutionConfig> m_listResolution;

    CResolutionEditDlg m_EditDlg;
};

#endif // MAINWINDOW_H
