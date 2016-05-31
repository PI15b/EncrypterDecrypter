#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>

class Settings
{
private:
    QString cipher_path, password, icon_path, author, filename, descr;
public:
    Settings(): cipher_path(), password(), icon_path(), author(), filename(), descr(){}
    void setCipherPath(const QString& cipher_path){ this->cipher_path = cipher_path; }
    void setPassword(const QString& password){ this->password = password; }
    void setIconPath(const QString& icon_path){ this->icon_path = icon_path; }
    void setAuthor(const QString& author){ this->author = author; }
    void setFilename(const QString& filename){ this->filename = filename; }
    void setDescr(const QString& descr){ this->descr = descr; }
    const QString& getCipherPath() const { return cipher_path; }
    const QString& getPassword() const { return password; }
    const QString& getIconPath() const { return icon_path; }
    const QString& getAuthor() const { return author; }
    const QString& getFilename() const { return filename; }
    const QString& getDescr() const { return descr; }
};

#endif // SETTINGS_H
