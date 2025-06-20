#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);

    refreshButton = new QPushButton("Refresh", this);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(textEdit);
    layout->addWidget(refreshButton);

    reader = new InfluxReader(this);

    connect(reader, &InfluxReader::dataReady, this, &MainWindow::updateDisplay);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshData);

    setWindowTitle("InfluxDB Sensor Monitor");
    resize(400, 300);

    reader->queryInflux();
}

void MainWindow::updateDisplay(const QString &data)
{
    textEdit->setText(data);
}

void MainWindow::refreshData()
{
    reader->queryInflux();
}
