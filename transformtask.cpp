#include "transformtask.h"
#include <QCoreApplication>
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
