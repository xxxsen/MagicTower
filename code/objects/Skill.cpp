//
// Created by sen on 18-2-16.
//

#include "Skill.h"

Skill::Skill()
    : MagicObject(MO_SKILL), damage_(1)
{

}

void Skill::setCompatibility(SKCompatibility sp)
{
    sp_ = sp;
}

SKCompatibility Skill::getCompatibility() const
{
    return sp_;
}

uint32_t Skill::getDamage() const
{
    return damage_;
}

Skill &Skill::setDamage(uint32_t damage)
{
    damage_ = damage;
    return *this;
}

bool Skill::construct(const Json::Value &v)
{
    if(v.isMember("capatibility"))
        setCompatibility(static_cast<SKCompatibility>(v["capatibility"].asInt()));
    if(v.isMember("damage"))
        setDamage(v["damage"].asUInt());
    return MagicObject::construct(v);
}

REGIST_OBJECT(Skill);