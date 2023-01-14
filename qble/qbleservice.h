#ifndef QBLESERVICE_H
#define QBLESERVICE_H

#include "qblecharacteristic.h"

#include <QObject>
#include <QtDBus>
#include <QVariantMap>

#define UCHARARR_TO_BYTEARRAY(uarray) \
    QByteArray(reinterpret_cast<const char*>(uarray), sizeof(uarray))

#define UCHAR_TO_BYTEARRAY(uch) \
    QByteArray(reinterpret_cast<const char*>(&uch), 1)


class QBLEService : public QObject
{
    Q_OBJECT
public:
    explicit QBLEService(const QString &uuid, const QString &path, QObject *parent = nullptr);

    Q_SIGNAL void characteristicChanged(const QString &c, const QByteArray &value);
    Q_SIGNAL void characteristicRead(const QString &c, const QByteArray &value);
    Q_SIGNAL void descriptorWritten(const QString &d, const QByteArray &value);

    QString serviceUUID() const;

    QBLECharacteristic *characteristic(const QString &c) const;

    void writeValue(const QString &characteristic, const QByteArray &value);
    void writeAsync(const QString &characteristic, const QByteArray &value);

    QByteArray readValue(const QString &characteristic);
    void readAsync(const QString &characteristic) const;
    void enableNotification(const QString &c);
    void disableNotification(const QString &c);

    Q_SIGNAL void message(const QString &text);
    Q_INVOKABLE virtual bool operationRunning();
    Q_SIGNAL void operationRunningChanged();

protected:
    Q_SIGNAL void propertiesChanged(QString, QVariantMap, QStringList);

private:
    QString m_servicePath;
    QString m_serviceUUID;

    QMap<QString, QBLECharacteristic*> m_characteristicMap;
    QDBusInterface *m_serviceInterface;

    void introspect();

    Q_SLOT void characteristicChangedInt(const QString &characteristic, const QByteArray &value);
    Q_SLOT void characteristicReadInt(const QString &characteristic, const QByteArray &value);
    Q_SLOT void characteristicWrittenInt(const QString &characteristic, const QByteArray &value);
    Q_SLOT void descriptorWrittenInt(const QString &descriptor, const QByteArray &value);

    Q_SLOT void onPropertiesChanged(const QString &interface, const QVariantMap &map, const QStringList &list);
};

#endif // QBLESERVICE_H
