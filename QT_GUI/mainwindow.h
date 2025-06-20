#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include "influxreader.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void updateDisplay(const QString &data);
    void refreshData();

private:
    InfluxReader *reader;
    QTextEdit *textEdit;
    QPushButton *refreshButton;
};

#endif // MAINWINDOW_H
