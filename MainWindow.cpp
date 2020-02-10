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
    ui->horizontalSlider->setRange(0, 100);
    ui->horizontalSlider_2->setRange(0, 100);
    m_volumeController = createVolumeController();

    connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));

    m_updateTimer.start(500);
    //计划好看的slider样式
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << "Set mic volume: " << value
             << "; Result: " << m_volumeController->setMicVolume(value);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    qDebug() << "Set speaker voluem: " << value
             << "; Result: " << m_volumeController->setSpeakerVolume(value);
}

void MainWindow::onUpdate()
{
    int micVolume     = m_volumeController->getMicVolume();
    int speakerVolume = m_volumeController->getSpeakerVolume();

    ui->horizontalSlider->setValue(micVolume);
    ui->horizontalSlider_2->setValue(speakerVolume);

    ui->label_2->setText(QString::fromLocal8Bit("录音音量：(%1%)").arg(micVolume));
    ui->label_3->setText(QString::fromLocal8Bit("扬声器音量：(%1%)").arg(speakerVolume));
}
