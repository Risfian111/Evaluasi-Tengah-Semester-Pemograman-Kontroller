#ifndef INFLUXREADER_H
#define INFLUXREADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class InfluxReader : public QObject
{
    Q_OBJECT

public:
    explicit InfluxReader(QObject *parent = nullptr);
    void queryInflux();

signals:
    void dataReady(const QString &data);

private slots:
    void onReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};

#endif // INFLUXREADER_H
