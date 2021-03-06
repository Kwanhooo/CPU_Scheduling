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

    //参数
    const int maxPID = 100000;
    const int maxTime = 60;
    const int maxPriority = 63;
    const int agingTime = 30;

    //U参数
    int TIME_SLICE;
    int MAX_PROGRAM_AMOUNT;
    int randomlyEventRate;

    //IO参数
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
    void on_spinBox_autoIOGap_valueChanged(int arg1);
    void on_spinBox_IORate_valueChanged(int arg1);
    void on_spinBox_timeSlice_valueChanged(int arg1);
    void on_spinBox_maxProcAmount_valueChanged(const QString &arg1);
    void on_lineEdit_timeScale_textChanged(const QString &arg1);

private:
    Ui::Simulator *ui;

    int startMode;

    PCB* runningProc;//指向正在运行的进程
    //容器
    QList<PCB*> readyList;
    QList<PCB*> waitingList;
    QList<PCB*> IOList;
    QList<PCB*> suspendedList;
    QList<PCB*> terminatedList;
    QList<PCB*> backupProcList;

    //调度方法
    PCB* getTopPriority();//获取最高优先级

    //三种调度方法
    void nonPriorityAction();
    void preemptiveProrityAction();
    void roundRobinAction();

    //通用方法
    void addLog(QString content);//加日志（控制台&UI）
    /*
     * 刷新UI中的展示列表
     */
    void refreshReadyUI();
    void refreshRunningUI();
    void refreshTerminatedUI();
    void resetRunningUI();
    void refreshBackupUI();
    void refreshSuspendedUI();
    void refreshWaitingUI();
    void refreshIOUI();

    void loadProc();//从后备队列里面载入新的进程

    /*
     * 随机产生IO事件
     * 用在自动化运行
     */
    void ramdomlyEvent();

    void loadIOProc(QString IOType);//从等待队列里面选取进程进行IO

    void IOAction();//完成IO动作
    void IOAll();//一次性IO完

    void automaticRun();//自动运行
};

#endif // SIMULATOR_H
