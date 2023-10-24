#include "MobAnnouncer.h"

#include "Config.h"
#include "Player.h"

void MobAnnouncerUnitScript::OnUnitDeath(Unit* unit, Unit* killer)
{
    if (!sConfigMgr->GetOption<bool>("MobAnnouncer.Enable", false))
    {
        return;
    }

    if (!unit || !killer)
    {
        return;
    }

    if (unit->ToPlayer() && killer->ToCreature() && ShouldAnnounce(killer->GetEntry()))
    {
        auto player = unit->ToPlayer();
        auto creature = killer->ToCreature();

        AnnounceToWorld(Acore::StringFormatFmt("|cffFFFFFFPlayer {}{}|cffFFFFFF was killed by {}{}|cffFFFFFF.", GetHexColorFromClass(player->getClass()), player->GetName(), GetHexColorFromRank(creature->GetCreatureTemplate()->rank), creature->GetName()));
        return;
    }

    if (unit->ToCreature() && killer->ToPlayer() && ShouldAnnounce(unit->GetEntry()))
    {
        auto player = killer->ToPlayer();
        auto creature = unit->ToCreature();

        AnnounceToWorld(Acore::StringFormatFmt("|cffFFFFFFPlayer {}{}|cffFFFFFF killed {}{}|cffFFFFFF.", GetHexColorFromClass(player->getClass()), player->GetName(), GetHexColorFromRank(creature->GetCreatureTemplate()->rank), creature->GetName()));
        return;
    }
}

std::string MobAnnouncerUnitScript::GetHexColorFromClass(uint8 classId)
{
    switch (classId)
    {
    case CLASS_DEATH_KNIGHT:
        return "|cffFC2A43";
    case CLASS_HUNTER:
        return "|cffAAD174";
    case CLASS_PALADIN:
        return "|cffF28CBC";
    case CLASS_ROGUE:
        return "|cffFEF262";
    case CLASS_WARLOCK:
        return "|cff9A81C2";
    case CLASS_DRUID:
        return "|cffF67404";
    case CLASS_MAGE:
        return "|cff70C9F1";
    case CLASS_PRIEST:
        return "|cffF5F3F6";
    case CLASS_SHAMAN:
        return "|cff05D7BA";
    case CLASS_WARRIOR:
        return "|cffC9A074";
    }

    return "|cffFFFFFF";
}

std::string MobAnnouncerUnitScript::GetHexColorFromRank(uint8 rank)
{
    switch (rank)
    {
    case CREATURE_ELITE_NORMAL:
        return "|cffFFFFFF";

    case CREATURE_ELITE_ELITE:
        return "|cffE8AA00";

    case CREATURE_ELITE_RARE:
    case CREATURE_ELITE_RAREELITE:
        return "|cffC1C1C1";

    case CREATURE_ELITE_WORLDBOSS:
        return "|cffEA0B00";

    case CREATURE_UNKNOWN:
        return "|cffFFFFFF";
    }

    return "|cffFFFFFF";
}

bool MobAnnouncerUnitScript::ShouldAnnounce(uint32 entry)
{
    return mobIds.find(entry) != mobIds.end();
}

void MobAnnouncerUnitScript::AnnounceToWorld(std::string message)
{
    sWorld->SendServerMessage(SERVER_MSG_STRING, message);
}

void MobAnnouncerWorldScript::LoadAnnounceMobIds()
{
    auto qResult = WorldDatabase.Query("SELECT entry FROM mobannouncer_ids");

    if (!qResult)
    {
        return;
    }

    LOG_INFO("module", "Loading mob ids from 'mobannouncer_ids'..");

    int count = 0;

    do
    {
        auto fields = qResult->Fetch();

        uint32 entry = fields[0].Get<uint32>();
        mobIds.insert(entry);

        count++;
    } while (qResult->NextRow());

    LOG_INFO("module", "Loaded '{}' mobannouncer_ids.", count);
}

void MobAnnouncerWorldScript::OnAfterConfigLoad(bool reload)
{
    if (reload)
    {
        mobIds.clear();
    }

    LoadAnnounceMobIds();
}

void SC_AddMobAnnouncerScripts()
{
    new MobAnnouncerWorldScript();
    new MobAnnouncerUnitScript();
}
