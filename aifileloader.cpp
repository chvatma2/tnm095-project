#include "aifileloader.h"

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

AIFileLoader::AIFileLoader()
{

}

void AIFileLoader::loadAIFiles()
{
    QDir characterDir("./ai/characters");
    qDebug() << characterDir.absolutePath();
    QDirIterator characterDirIterator(characterDir.absolutePath(), QDir::NoDotAndDotDot | QDir::AllEntries);
    while (characterDirIterator.hasNext())
    {
        m_characters.push_back(loadFile(characterDirIterator.next()));
    }
    m_masterFile = loadFile("./ai/master.json");
}

QJsonObject AIFileLoader::loadFile(const QString &filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    return QJsonDocument::fromJson(file.readAll()).object();
}

QJsonObject AIFileLoader::masterDocument() const
{
    return m_masterFile;
}

QList<QJsonObject> AIFileLoader::characterDocuments() const
{
    return m_characters;
}
