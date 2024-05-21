#ifndef SKILLPLATFORM_H
#define SKILLPLATFORM_H

#include "include/Platform.h"

class SkillPlatform : public Platform{
    Q_OBJECT

private:
    QString type;
public:
    SkillPlatform(MyScene* scene, Player* player, int x, int y, QString type);
    ~SkillPlatform();
    virtual void isOnIt();
    virtual void toInitialState();
};

#endif