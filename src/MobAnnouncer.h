#ifndef MODULE_MOB_ANNOUNCER_H
#define MODULE_MOB_ANNOUNCER_H

#include "ScriptMgr.h"

#include <unordered_set>

std::unordered_set<uint32> mobIds;

class MobAnnouncerUnitScript : public UnitScript
{
public:
    MobAnnouncerUnitScript() : UnitScript("MobAnnouncerUnitScript") { }

    void OnUnitDeath(Unit* /*unit*/, Unit* /*killer*/) override;

    bool ShouldAnnounce(uint32 /*entry*/);
    void AnnounceToWorld(std::string /*message*/);

    std::string GetHexColorFromClass(uint8 /*classId*/);
    std::string GetHexColorFromRank(uint8 /*rank*/);
};

class MobAnnouncerWorldScript : public WorldScript
{
public:
    MobAnnouncerWorldScript() : WorldScript("MobAnnouncerWorldScript") { }

    void OnAfterConfigLoad(bool /*reload*/) override;

    void LoadAnnounceMobIds();
};

#endif // MODULE_MOB_ANNOUNCER_H
