//
// Created by sen on 18-2-16.
//

#ifndef MAGICTOWER_SKILL_H
#define MAGICTOWER_SKILL_H

#include <string>
#include "MagicObject.h"

class Skill : public MagicObject
{
public:
    Skill();

public:
    void setCompatibility(SKCompatibility sp);
    SKCompatibility getCompatibility() const;
    uint32_t getDamage() const;
    Skill &setDamage(uint32_t damage);
    bool construct(const Json::Value &v) override;

private:
    SKCompatibility sp_;
    uint32_t damage_;
};

#endif //MAGICTOWER_SKILL_H
