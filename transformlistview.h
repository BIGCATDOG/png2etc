#ifndef TRANSFORMLISTVIEW_H
#define TRANSFORMLISTVIEW_H

#include <QListView>
#include <QHash>
#include <QStringListModel>

class TransformListView : public QListView
{
    Q_OBJECT
public:
    explicit TransformListView(QWidget *parent = nullptr);

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent* event);

private:
    void updateListView();

private slots:
    void onTransformFinished(const QString& transformedFile);

private:
    QStringListModel        _model;
    QHash<QString, QString> _convertFiles;
};

#endif // TRANSFORMLISTVIEW_H
