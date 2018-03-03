//
// Created by sen on 18-2-16.
//

#include "NPC.h"
#include "Dialog.h"
#include "DrawPanel.h"
#include "Player.h"

NPC::NPC()
    : MagicObject(MO_NPC), wording_(0)
{

}

bool NPC::construct(const Json::Value &v)
{
    if(v.isMember("wording"))
    {
        wording_ = v["wording"].asUInt();
    }
    return MagicObject::construct(v);
}


void NPC::doCollision(Player &player)
{
    DrawPanel::instance().newWordingDialog(WordingStore::instance().get(wording_))->show();
    player.goBack();
}

uint32_t NPC::getWording() const
{
    return wording_;
}

REGIST_OBJECT(NPC);

void SelectDialogNPC::doCollision(Player &player)
{
    selected_ = -1;
    if(hasBeforeWording())
        DrawPanel::instance().newWordingDialog(WordingStore::instance().get(getBeforeWording()))->show();
    DrawPanel::instance().backup();
    DialogPtr dialog = DrawPanel::instance().newSelectDialog(*WordingStore::instance().get(getWording()).get());
    dialog->show();
    SelectDialog *realDialog = dynamic_cast<SelectDialog *>(dialog.get());
    if(realDialog->hasSelected())
        selected_ = realDialog->getSelected();
    else
        selected_ = -1;
    DrawPanel::instance().restore();
    if(hasAfterWording())
        DrawPanel::instance().newWordingDialog(WordingStore::instance().get(getAfterWording()))->show();
    player.goBack();
}

SelectDialogNPC::SelectDialogNPC()
    : selected_(-1)
{

}

bool SelectDialogNPC::hasSelected() const
{
    return selected_ != -1;
}

int32_t SelectDialogNPC::getSelected() const
{
    return selected_;
}

bool SelectDialogNPC::construct(const Json::Value &v)
{
    if(v.isMember("before_wording"))
        before_ = v["before_wording"].asInt();
    else
        before_ = -1;
    if(v.isMember("after_wording"))
        after_ = v["after_wording"].asInt();
    else
        after_ = -1;
    return NPC::construct(v);
}

int32_t SelectDialogNPC::getBeforeWording() const
{
    return before_;
}

int32_t SelectDialogNPC::getAfterWording() const
{
    return after_;
}

bool SelectDialogNPC::hasBeforeWording() const
{
    return getBeforeWording() != -1;
}

bool SelectDialogNPC::hasAfterWording() const
{
    return getAfterWording() != -1;
}

REGIST_OBJECT(SelectDialogNPC);
