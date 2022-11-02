#include "transformlistview.h"
#include "transformtask.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QThreadPool>

TransformListView::TransformListView(QWidget *parent)
    :QListView(parent)
{
    setAcceptDrops(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TransformListView::dragEnterEvent(QDragEnterEvent *event) {
    auto mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        for (auto url : mimeData->urls()) {
            QString filePath = url.toLocalFile();
            QFileInfo info(filePath);
            if (info.suffix()!= "png") {
                continue;
            } else {
                event->acceptProposedAction();
                return;
            }
        }
    }
    event->ignore();
}

void TransformListView::dropEvent(QDropEvent *event) {
    auto mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        for (auto url : mimeData->urls()) {
            QString filePath = url.toLocalFile().toUtf8();
            QFileInfo info(filePath);
            if (info.suffix()!= "png") {
                return;
            }

            _convertFiles.insert(filePath, "");
            updateListView();

            TransformTask* task = new TransformTask(filePath);
            connect(task, &TransformTask::onTransformFinished, this, &TransformListView::onTransformFinished);
            QThreadPool::globalInstance()->start(task);
        }
    }
}

void TransformListView::dragMoveEvent(QDragMoveEvent* event) {
    event->acceptProposedAction();
}

void TransformListView::onTransformFinished(const QString& transformedFile) {
    QFileInfo info(transformedFile);
    _convertFiles.insert(transformedFile, info.baseName() + ".pkm");
    updateListView();
}

void TransformListView::updateListView() {
    QStringList list;
    QHashIterator<QString, QString> i(_convertFiles);
    while (i.hasNext()) {
        i.next();
        if (i.value().isEmpty()) {
            list << i.key();
        } else {
            list << i.key() + "--------------------->" + i.value();
        }
    }
    _model.setStringList(list);
    setModel(&_model);
}
