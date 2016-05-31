#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>
#include <QObject>
#include <QMetaEnum>

class Settings
{
    Q_GADGET
    Q_ENUMS(CipherMode)
    Q_ENUMS(Hash)
    Q_ENUMS(Key)
public:
    enum CipherMode{ ECB, CBC, PCBC, CFB, OFB };
    enum Hash{ MD4, MD5, SHA1, SHA224, SHA256, SHA512 };
    enum Key{ key128 = 128, key192 = 192, key256 = 256 };
private:
    QString cipher_path, password, icon_path, author, filename, descr;
    CipherMode cipher_mode;
    Hash hash;
    Key key;
public:
    Settings(): cipher_path(), password(), icon_path(), author(), filename(), descr(), cipher_mode(ECB){}
    void setCipherPath(const QString& cipher_path){ this->cipher_path = cipher_path; }
    void setPassword(const QString& password){ this->password = password; }
    void setIconPath(const QString& icon_path){ this->icon_path = icon_path; }
    void setAuthor(const QString& author){ this->author = author; }
    void setFilename(const QString& filename){ this->filename = filename; }
    void setDescr(const QString& descr){ this->descr = descr; }
    void setCipherMode(const QString& cipher_mode)
    {
        const QMetaObject &mo = Settings::staticMetaObject;
        int index = mo.indexOfEnumerator("CipherMode");
        QMetaEnum metaEnum = mo.enumerator(index);
        int value = metaEnum.keyToValue(qPrintable(cipher_mode));
        this->cipher_mode = static_cast<CipherMode>(value);
    }
    void setHash(const QString& hash)
    {
        const QMetaObject &mo = Settings::staticMetaObject;
        int index = mo.indexOfEnumerator("Hash");
        QMetaEnum metaEnum = mo.enumerator(index);
        int value = metaEnum.keyToValue(qPrintable(hash));
        this->hash = static_cast<Hash>(value);
    }
    void setKey(const QString& key)
    {
        const QMetaObject &mo = Settings::staticMetaObject;
        int index = mo.indexOfEnumerator("Key");
        QMetaEnum metaEnum = mo.enumerator(index);
        int value = metaEnum.keyToValue(qPrintable(key));
        this->key = static_cast<Key>(value);
    }
    const QString& getCipherPath() const { return cipher_path; }
    const QString& getPassword() const { return password; }
    const QString& getIconPath() const { return icon_path; }
    const QString& getAuthor() const { return author; }
    const QString& getFilename() const { return filename; }
    const QString& getDescr() const { return descr; }
    const QString getCipherMode() const
    {
        const QMetaObject &mo = Settings::staticMetaObject;
        int index = mo.indexOfEnumerator("CipherMode");
        QMetaEnum metaEnum = mo.enumerator(index);
        return metaEnum.valueToKey(cipher_mode);
    }
    const QString getHash() const
    {
        const QMetaObject &mo = Settings::staticMetaObject;
        int index = mo.indexOfEnumerator("Hash");
        QMetaEnum metaEnum = mo.enumerator(index);
        return metaEnum.valueToKey(hash);
    }
    const QString getKey() const
    {
        const QMetaObject &mo = Settings::staticMetaObject;
        int index = mo.indexOfEnumerator("Key");
        QMetaEnum metaEnum = mo.enumerator(index);
        return metaEnum.valueToKey(key);
    }
    const CipherMode getCipherModeEnum() const
    {
        return cipher_mode;
    }
    const Key getKeyEnum() const
    {
        return key;
    }
    const Hash getHashEnum() const
    {
        return hash;
    }
};

#endif // SETTINGS_H
