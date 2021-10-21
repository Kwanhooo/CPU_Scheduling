#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QWidget>
#include <QList>
#include <QThread>

#include "pcb.h"

#define PREEMPTIVE_PRIORITY 1195
#define NON_PRIORITY 1196
#define ROUND_ROBIN 1197

namespace Ui {
class Simulator;
}

class Simulator : public QWidget
{
    Q_OBJECT

public:
    explicit Simulator(QWidget *parent = nullptr);
    ~Simulator();
    const int maxPID = 100000;
    const int maxTime = 60;
    const int maxPriority = 127;


    int TIME_SLICE;
    int MAX_PROGRAM_AMOUNT;
    int randomlyEventRate;

    int USBOccupy;
    int PrinterOccupy;
    int GraphicsOccupy;
    int DiskOccupy;
    int timeScale;
    int IOCount;
    int autoIOGap;

    QTimer *timer;

public slots:
    void getNewPCB(PCB* pcb);
    void setupSimulator(int startMode);

private slots:
    void on_pushButton_custom_clicked();
    void on_pushButton_random_clicked();
    void on_pushButton_manual_clicked();
    void on_pushButton_auto_clicked();
    void on_pushButton_IO_clicked();
    void on_pushButton_suspend_clicked();
    void on_pushButton_IO_All_clicked();
    void on_pushButton_suspend_off_clicked();
    void on_pushButton_auto_stop_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_autoIOGap_valueChanged(int arg1);
    void on_spinBox_IORate_valueChanged(int arg1);
    void on_spinBox_timeSlice_valueChanged(int arg1);
    void on_spinBox_maxProcAmount_valueChanged(const QString &arg1);

private:
    Ui::Simulator *ui;

    int startMode;

    //优先权调度容器
    QList<PCB*> readyList;
    PCB* runningProc;
    QList<PCB*> waitingList;
    QList<PCB*> IOList;
    QList<PCB*> suspendedList;
    QList<PCB*> terminatedList;
    QList<PCB*> backupProcList;

    //优先权调度方法
    PCB* getTopPriority();
    void nonPriorityAction();
    void preemptiveProrityAction();
    void roundRobinAction();

    //通用方法
    void addLog(QString content);
    void refreshReadyUI();
    void refreshRunningUI();
    void refreshTerminatedUI();
    void resetRunningUI();
    void refreshBackupUI();
    void loadProc();
    void refreshSuspendedUI();
    void ramdomlyEvent();
    void refreshWaitingUI();
    void refreshIOUI();
    void loadIOProc(QString IOType);
    void IOAction();
    void automaticRun();
    void IOAll();
};

#endif // SIMULATOR_H
