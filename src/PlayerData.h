#ifndef PLAYERDATA_H
#define PLAYERDATA_H


#include <QMap>
#include <QString>
#include <QVector>
#include <iostream>
#include <fstream>
#include <QDebug>

class PlayerData{

private:
    QMap<QString, QVector<QMap<QString, QString>*>*>* data;
    QVector<QMap<QString, QString>*>* records;
    QString current_player;

public:
    PlayerData();
    ~PlayerData();
    QMap<QString, QVector<QMap<QString, QString>*>*>* getData();
    QVector<QMap<QString, QString>*>* getPlayerData();
    QVector<QMap<QString, QString>*>* getRecords();
    QString getCurrentPlayer();
    void readDataFile();
    void readRecords();
    void writeDataFile();
    void writeRecords();
    void setCurrentPlayer(QString p_name);
    void addNew(QString str);
    QString exists(QString player);
    void updatePlayerData(int level, int score, QString time);
    void updatePlayerStars(int level, QString stars);
};

#endif