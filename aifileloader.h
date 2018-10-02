#ifndef AIFILELOADER_H
#define AIFILELOADER_H

#include <QJsonObject>
#include <QList>

class AIFileLoader
{
public:
    AIFileLoader();
    void loadAIFiles();
    QJsonObject masterDocument() const;
    QList<QJsonObject> characterDocuments() const;

private:
    QJsonObject loadFile(const QString &filename);

    QList<QJsonObject> m_characters;
    QJsonObject m_masterFile;
};

#endif // AIFILELOADER_H
