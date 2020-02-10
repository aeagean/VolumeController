#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

using namespace QtHub;

#if (QT_VERSION <= QT_VERSION_CHECK(5, 0, 0))
    #include <QtConcurrentRun>
#else
    #include <QtConcurrent>
#endif

VolumeController *_createVolumeController()
{
    return new VolumeController();
}

static VolumeController *createVolumeController()
{
    QFuture<VolumeController *> future = QtConcurrent::run(_createVolumeController);
    return future.result();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_volumeController = createVolumeController();
    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, [this](){
        int value = m_volumeController->getMicVolume();
        ui->horizontalSlider->setValue(value);

        ui->horizontalSlider_2->setValue(m_volumeController->getSpeakerVolume());
    });

    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
     qDebug() << "result: " << m_volumeController->setMicVolume(value);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
     qDebug() << "result: " << m_volumeController->setSpeakerVolume(value);
}
