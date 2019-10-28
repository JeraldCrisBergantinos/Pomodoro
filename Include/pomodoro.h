#ifndef POMODORO_H
#define POMODORO_H

#include <QWidget>

#include <memory>

namespace Ui {
class Pomodoro;
}

class Pomodoro : public QWidget
{
    Q_OBJECT

public:
    explicit Pomodoro(QWidget *parent = 0);
    ~Pomodoro();

private slots:
    void on_pbCompute_clicked();
    void logout();
    void endWork();
    void endBreak();

    void on_pbStart_clicked();

private:
    Ui::Pomodoro *ui;
    class PomodoroData;
    std::shared_ptr<PomodoroData> m_d;
};

#endif // POMODORO_H
