#ifndef CHARACTERLISTWIDGET_H
#define CHARACTERLISTWIDGET_H

#include <QMap>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>

#include "gameobject.h"

class CharacterListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CharacterListWidget(QVector<GameObject*> &characters, QWidget *parent = nullptr);

signals:

public slots:

private:
    QMap<int, GameObject*> m_characters;
    QScrollArea* m_scrollArea;
    QWidget* m_widgetList;
    QVBoxLayout* m_listLayout;
    QHBoxLayout* m_mainLayout;
};

#endif // CHARACTERLISTWIDGET_H
