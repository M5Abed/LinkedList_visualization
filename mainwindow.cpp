// mainwindow.cpp
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <mainwindow.h>

mainwindow::mainwindow(QWidget* parent) : QMainWindow(parent), list(new DoublyLinkedList()) {
    setupUI();
}

mainwindow::~mainwindow() {
    delete list;
}

void mainwindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout* inputLayout = new QHBoxLayout();
    input = new QLineEdit(this);
    input->setPlaceholderText("Enter value or position");
    inputLayout->addWidget(input);

    QPushButton* insertHeadButton = new QPushButton("Insert Head", this);
    QPushButton* insertTailButton = new QPushButton("Insert Tail", this);
    QPushButton* insertAtButton = new QPushButton("Insert At", this);
    QPushButton* deleteHeadButton = new QPushButton("Delete Head", this);
    QPushButton* deleteTailButton = new QPushButton("Delete Tail", this);
    QPushButton* deleteAtButton = new QPushButton("Delete At", this);
    QPushButton* searchButton = new QPushButton("Search", this);
    QPushButton* clearButton = new QPushButton("Clear", this);

    inputLayout->addWidget(insertHeadButton);
    inputLayout->addWidget(insertTailButton);
    inputLayout->addWidget(insertAtButton);
    inputLayout->addWidget(deleteHeadButton);
    inputLayout->addWidget(deleteTailButton);
    inputLayout->addWidget(deleteAtButton);
    inputLayout->addWidget(searchButton);
    inputLayout->addWidget(clearButton);

    mainLayout->addLayout(inputLayout);

    QGraphicsView* view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    view->setScene(scene);
    mainLayout->addWidget(view);

    log = new QTextEdit(this);
    log->setReadOnly(true);
    mainLayout->addWidget(log);

    setCentralWidget(centralWidget);

    connect(insertHeadButton, &QPushButton::clicked, this, &mainwindow::insertHead);
    connect(insertTailButton, &QPushButton::clicked, this, &mainwindow::insertTail);
    connect(insertAtButton, &QPushButton::clicked, this, &mainwindow::insertAt);
    connect(deleteHeadButton, &QPushButton::clicked, this, &mainwindow::deleteHead);
    connect(deleteTailButton, &QPushButton::clicked, this, &mainwindow::deleteTail);
    connect(deleteAtButton, &QPushButton::clicked, this, &mainwindow::deleteAt);
    connect(searchButton, &QPushButton::clicked, this, &mainwindow::search);
    connect(clearButton, &QPushButton::clicked, this, &mainwindow::clear);
}

void mainwindow::logMessage(const QString& message) {
    log->append(message);
}

void mainwindow::updateVisualization()
{
    // Clear the previous visualization
    scene->clear();

    // Get the head of the linked list
    Node* current = list->head;
    int x = 50; // Starting x-coordinate for the boxes

    // Iterate through the linked list to visualize it
    while (current) {
        // Draw a white box for each node
        QGraphicsRectItem *rect = scene->addRect(x, 100, 50, 30, QPen(Qt::white), QBrush(Qt::white));

        // Add the integer value inside the box as text
        QGraphicsTextItem *text = scene->addText(QString::number(current->data));
        text->setDefaultTextColor(Qt::black); // Set the text color to black for visibility
        text->setPos(x + 15, 105);            // Center the text inside the box

        // Draw a white arrow to the next node (if it exists)
        if (current->next) {
            scene->addLine(x + 50, 115, x + 80, 115, QPen(Qt::white, 2)); // Arrow from this box to the next
        }

        // Move to the next position
        x += 80; // Add spacing between boxes
        current = current->next; // Advance to the next node
    }
}

void mainwindow::insertHead() {
    bool ok;
    int value = input->text().toInt(&ok);
    if (ok) {
        list->insertHead(value);
        logMessage("Inserted " + QString::number(value) + " at the head.");
        updateVisualization();
    }
}

void mainwindow::insertTail() {
    bool ok;
    int value = input->text().toInt(&ok);
    if (ok) {
        list->insertTail(value);
        logMessage("Inserted " + QString::number(value) + " at the tail.");
        updateVisualization();
    }
}

void mainwindow::insertAt() {
    bool ok;
    QStringList inputs = input->text().split(',');
    if (inputs.size() == 2) {
        int value = inputs[0].toInt(&ok);
        int position = inputs[1].toInt(&ok);
        if (ok) {
            list->insertAt(value, position);
            logMessage("Inserted " + QString::number(value) + " at position " + QString::number(position) + ".");
            updateVisualization();
        }
    }
}

void mainwindow::deleteHead() {
    list->deleteHead();
    logMessage("Deleted head node.");
    updateVisualization();
}

void mainwindow::deleteTail() {
    list->deleteTail();
    logMessage("Deleted tail node.");
    updateVisualization();
}

void mainwindow::deleteAt() {
    bool ok;
    int position = input->text().toInt(&ok);
    if (ok) {
        list->deleteAt(position);
        logMessage("Deleted node at position " + QString::number(position) + ".");
        updateVisualization();
    }
}

void mainwindow::search() {
    bool ok;
    int value = input->text().toInt(&ok);
    if (ok) {
        Node* result = list->search(value);
        if (result) {
            logMessage("Found value " + QString::number(value) + " in the list.");
        } else {
            logMessage("Value " + QString::number(value) + " not found.");
        }
    }
}

void mainwindow::clear() {
    list->clear();
    logMessage("Cleared the list.");
    updateVisualization();
}
