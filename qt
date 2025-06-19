#include "influxreader.h"
#include <QNetworkRequest>
#include <QUrl>

InfluxReader::InfluxReader(QObject *parent)
    : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &InfluxReader::onReply);
}

void InfluxReader::queryInflux()
{
    QString org = "BLITAR";
    QString token = "YOUR_TOKEN_HERE";  // ganti token Anda
    QString url = "http://localhost:8086/api/v2/query?org=" + org;

    QNetworkRequest request{QUrl(url)};
    request.setRawHeader("Authorization", ("Token " + token).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/vnd.flux");

    QString fluxQuery = R"(
        from(bucket: "SHT40")
        |> range(start: -5m)
        |> filter(fn: (r) => r._measurement == "sensor_data")
        |> filter(fn: (r) => r._field == "temperature" or r._field == "humidity")
        |> last()
    )";

    manager->post(request, fluxQuery.toUtf8());
}

void InfluxReader::onReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit dataReady("Error: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QString temperature = "N/A";
    QString humidity = "N/A";

    const QList<QByteArray> lines = data.split('\n');
    for (const QByteArray &line : lines) {
        if (line.contains("temperature")) {
            QString value = QString::fromUtf8(line).section(',', -1);
            if (!value.isEmpty()) temperature = value.trimmed();
        } else if (line.contains("humidity")) {
            QString value = QString::fromUtf8(line).section(',', -1);
            if (!value.isEmpty()) humidity = value.trimmed();
        }
    }

    QString result = QString("Temperature: %1 °C\nHumidity: %2 %%").arg(temperature, humidity);
    emit dataReady(result);
    reply->deleteLater();
}
