#include "pomodoro.h"
#include "ui_pomodoro.h"

#include <QDesktopWidget>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>

class Pomodoro::PomodoroData {
    public:
        std::shared_ptr<QTimer> logoutTimer;
        std::shared_ptr<QTimer> workTimer;
        std::shared_ptr<QTimer> breakTimer;
};

Pomodoro::Pomodoro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pomodoro),
    m_d(std::make_shared<PomodoroData>())
{
    ui->setupUi(this);

    this->setFixedSize( this->size() );
    move(qApp->desktop()->availableGeometry(this).center()-rect().center());
}

Pomodoro::~Pomodoro()
{
    delete ui;
}

void Pomodoro::on_pbCompute_clicked()
{
    int addSecs = 10 * 60 * 60;//10 hours
    ui->teLogoutTime->setTime( ui->teLoginTime->time().addSecs( addSecs ) );

    m_d->logoutTimer = std::make_shared<QTimer>();
    connect( m_d->logoutTimer.get(), &QTimer::timeout,
             this, &Pomodoro::logout );
    m_d->logoutTimer->start( addSecs * 1000 );//ms
}

void Pomodoro::logout()
{
    QMessageBox::critical( this, "LOGOUT", "UMUWI KA NA!!!" );
}

void Pomodoro::endWork()
{
    m_d->workTimer->stop();
    m_d->breakTimer->start();
    QMessageBox::critical( this, "TIME OUT", "BREAK KA MUNA!!!" );
}

void Pomodoro::endBreak()
{
    m_d->workTimer->start();
    m_d->breakTimer->stop();
    QMessageBox::critical( this, "TIME OUT", "WORK KA NA!!!" );
}

void Pomodoro::on_pbStart_clicked()
{
    m_d->workTimer = std::make_shared<QTimer>();
    connect( m_d->workTimer.get(), &QTimer::timeout,
             this, &Pomodoro::endWork );
    int workLength = ui->leWorkLength->text().toInt() * 60 * 1000;//ms
    m_d->workTimer->start( workLength );

    m_d->breakTimer = std::make_shared<QTimer>();
    connect( m_d->breakTimer.get(), &QTimer::timeout,
             this, &Pomodoro::endBreak );
    int breakLength = ui->leBreakLength->text().toInt() * 60 * 1000;//ms
    m_d->breakTimer->setInterval( breakLength );
}
