#ifndef TRANSFORMTASK_H
#define TRANSFORMTASK_H

#include <QObject>
#include <QRunnable>

class TransformTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    TransformTask(const QString& originFile);
    virtual void run() override;

signals:
    void onTransformFinished(const QString& originFile);

private:
    QString        _originFile;
};

#endif // TRANSFORMTASK_H
