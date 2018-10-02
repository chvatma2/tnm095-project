#ifndef AISUBSYSTEM_H
#define AISUBSYSTEM_H

#include <QJsonDocument>

class AISubsystem
{
public:
    AISubsystem();
    void addCharacterFromJson(const QJsonDocument& characterDocument);

private:

};

#endif // AISUBSYSTEM_H
