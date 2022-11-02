#include "transformtask.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QThread>
#include <QUrl>

TransformTask::TransformTask(const QString &originFile)
    :_originFile(originFile)
{

}

void TransformTask::run()
{
    qDebug() << QThread::currentThreadId();
    QString program = QCoreApplication::applicationDirPath() + "/etc1tool";
    QStringList arguments;
    arguments << "--encode" << _originFile;

    QProcess myProcess;
    myProcess.start(program, arguments);
    myProcess.waitForFinished();

    qDebug() << myProcess.errorString();

    emit onTransformFinished(_originFile);
}

PreviewTask::PreviewTask(const QString &originFile)
    :_originFile(originFile)
{

}

void PreviewTask::run()
{
    qDebug() << QThread::currentThreadId();
    QString program = QCoreApplication::applicationDirPath() + "/etc1tool";
    QStringList arguments;

    QFileInfo info(_originFile);
    QString targetFile = QDir::tempPath() + "/" + info.baseName() + ".png";
    if (!QFile::exists(targetFile)) {
        arguments << "--decode" << _originFile << "-o" << targetFile;

        QProcess myProcess;
        myProcess.start(program, arguments);
        myProcess.waitForFinished();
        qDebug() << myProcess.errorString();
    }
    emit onTransformFinished(targetFile);
}
