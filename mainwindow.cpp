#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transformtask.h"
#include <QFile>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QThreadPool>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listView, &TransformListView::doubleClicked, this, &MainWindow::onItemDoubleClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onItemDoubleClicked(const QModelIndex &index)
{
    auto data = index.data().toString();
    auto targetFile = data.split(">").back();
    auto targetPath = data.sliced(0, data.lastIndexOf("/"));
    auto fullPath = targetPath + "/" + targetFile;

    PreviewTask* task = new PreviewTask(fullPath);
    connect(task, &PreviewTask::onTransformFinished, this, &MainWindow::onPreviewRequest);
    QThreadPool::globalInstance()->start(task);

}

void MainWindow::onPreviewRequest(const QString &targetFile)
{
    if (!QFile::exists(targetFile)) {
        return;
    }

    QScrollArea *area = new QScrollArea;
    QLabel* label = new QLabel;

    QPixmap pic(targetFile);
    label->setPixmap(pic);
    area->setWidget(label);
    area->resize(pic.size());
    area->show();
}


