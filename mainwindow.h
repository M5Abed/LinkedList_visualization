#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTextEdit>
#include <QLineEdit>

#include "doublylinkedlist.h"

class mainwindow : public QMainWindow {
    Q_OBJECT

public:
    mainwindow(QWidget* parent = nullptr);
    ~mainwindow();

private:
    DoublyLinkedList* list;
    QGraphicsScene* scene;
    QTextEdit* log;
    QLineEdit* input;

    void setupUI();
    void logMessage(const QString& message);
    void updateVisualization();

private slots:
    void insertHead();
    void insertTail();
    void insertAt();
    void deleteHead();
    void deleteTail();
    void deleteAt();
    void search();
    void clear();
};
#endif // MAINWINDOW_H
