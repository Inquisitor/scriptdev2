/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: instance_blackrock_spire
SD%Complete: 50
SDComment: To really get this instance working, many encounters will need more love - and also the DB content is surely not yet perfect.
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    AREATRIGGER_ENTER_UBRS      = 2046,
    AREATRIGGER_STADIUM         = 2026,

    // Arena event dialogue - handled by instance
    SAY_NEFARIUS_INTRO_1        = -1229004,
    SAY_NEFARIUS_INTRO_2        = -1229005,
    SAY_NEFARIUS_ATTACK_1       = -1229006,
    SAY_REND_JOIN               = -1229007,
    SAY_NEFARIUS_ATTACK_2       = -1229008,
    SAY_NEFARIUS_ATTACK_3       = -1229009,
    SAY_NEFARIUS_ATTACK_4       = -1229010,
    SAY_REND_LOSE_1             = -1229011,
    SAY_REND_LOSE_2             = -1229012,
    SAY_NEFARIUS_LOSE_3         = -1229013,
    SAY_NEFARIUS_LOSE_4         = -1229014,
    SAY_REND_ATTACK             = -1229015,
    SAY_NEFARIUS_WARCHIEF       = -1229016,
    SAY_NEFARIUS_BUFF_GYTH      = -1229017,
    SAY_NEFARIUS_VICTORY        = -1229018,

    // Emberseer event
    EMOTE_BEGIN                 = -1229000,

    SPELL_EMBERSEER_GROWING     = 16048,
};

/* Areatrigger
1470 Instance Entry
1628 LBRS, between Spiders and Ogres
1946 LBRS, ubrs pre-quest giver (1)
1986 LBRS, ubrs pre-quest giver (2)
1987 LBRS, ubrs pre-quest giver (3)
2026 UBRS, stadium event trigger
2046 UBRS, way to upper
2066 UBRS, The Beast - Exit (to the dark chamber)
2067 UBRS, The Beast - Entry
2068 LBRS, fall out of map
3726 UBRS, entrance to BWL
*/

instance_blackrock_spire::instance_blackrock_spire(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
}

void instance_blackrock_spire::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
    memset(&m_aRoomRuneGuid, 0, sizeof(m_aRoomRuneGuid));
}

void instance_blackrock_spire::OnObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        case GO_EMBERSEER_IN:
            if (GetData(TYPE_ROOM_EVENT) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_DOORS:
            break;
        case GO_EMBERSEER_OUT:
            if (GetData(TYPE_EMBERSEER) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_GYTH_ENTRY_DOOR:
        case GO_GYTH_COMBAT_DOOR:
        case GO_DRAKKISATH_DOOR_1:
        case GO_DRAKKISATH_DOOR_2:
            break;
        case GO_GYTH_EXIT_DOOR:
            if (GetData(TYPE_STADIUM) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        case GO_ROOM_1_RUNE: m_aRoomRuneGuid[0] = pGo->GetObjectGuid(); return;
        case GO_ROOM_2_RUNE: m_aRoomRuneGuid[1] = pGo->GetObjectGuid(); return;
        case GO_ROOM_3_RUNE: m_aRoomRuneGuid[2] = pGo->GetObjectGuid(); return;
        case GO_ROOM_4_RUNE: m_aRoomRuneGuid[3] = pGo->GetObjectGuid(); return;
        case GO_ROOM_5_RUNE: m_aRoomRuneGuid[4] = pGo->GetObjectGuid(); return;
        case GO_ROOM_6_RUNE: m_aRoomRuneGuid[5] = pGo->GetObjectGuid(); return;
        case GO_ROOM_7_RUNE: m_aRoomRuneGuid[6] = pGo->GetObjectGuid(); return;

        case GO_ROOKERY_EGG: m_lRookeryEggGUIDList.push_back(pGo->GetObjectGuid());   return;

        case GO_EMBERSEER_RUNE_1:
        case GO_EMBERSEER_RUNE_2:
        case GO_EMBERSEER_RUNE_3:
        case GO_EMBERSEER_RUNE_4:
        case GO_EMBERSEER_RUNE_5:
        case GO_EMBERSEER_RUNE_6:
        case GO_EMBERSEER_RUNE_7:
            m_lEmberseerRunesGUIDList.push_back(pGo->GetObjectGuid());
            return;

        default:
            return;
    }
    m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
}

void instance_blackrock_spire::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_PYROGUARD_EMBERSEER:
        case NPC_LORD_VICTOR_NEFARIUS:
        case NPC_GYTH:
        case NPC_SCARSHIELD_INFILTRATOR:
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;

        case NPC_BLACKHAND_SUMMONER:
        case NPC_BLACKHAND_VETERAN:      m_lRoomEventMobGUIDList.push_back(pCreature->GetObjectGuid()); break;
        case NPC_BLACKHAND_INCARCERATOR: m_lIncarceratorGUIDList.push_back(pCreature->GetObjectGuid()); break;
    }
}

void instance_blackrock_spire::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_ROOM_EVENT:
            if (uiData == DONE)
                DoUseDoorOrButton(GO_EMBERSEER_IN);
            m_auiEncounter[0] = uiData;
            break;
        case TYPE_EMBERSEER:
            // Don't set the same data twice
            if (m_auiEncounter[1] == uiData)
                break;
            // Combat door
            DoUseDoorOrButton(GO_DOORS);
            // Respawn all incarcerators and reset the runes on FAIL
            if (uiData == FAIL)
            {
                for (GUIDList::const_iterator itr = m_lIncarceratorGUIDList.begin(); itr != m_lIncarceratorGUIDList.end(); ++itr)
                {
                    if (Creature* pIncarcerator = instance->GetCreature(*itr))
                    {
                        if (!pIncarcerator->isAlive())
                            pIncarcerator->Respawn();
                        pIncarcerator->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                    }
                }

                DoUseEmberseerRunes(true);
            }
            else if (uiData == DONE)
            {
                DoUseEmberseerRunes();
                DoUseDoorOrButton(GO_EMBERSEER_OUT);
            }
            m_auiEncounter[1] = uiData;
            break;
        case TYPE_FLAMEWREATH:
            m_auiEncounter[2] = uiData;
            break;
        case TYPE_STADIUM:
            if (uiData == IN_PROGRESS || uiData == FAIL)
                DoUseDoorOrButton(GO_GYTH_ENTRY_DOOR);
            else if (uiData == DONE)
            {
                DoUseDoorOrButton(GO_GYTH_ENTRY_DOOR);
                DoUseDoorOrButton(GO_GYTH_EXIT_DOOR);
            }
            m_auiEncounter[3] = uiData;
            break;
        case TYPE_VALTHALAK:
            m_auiEncounter[4] = uiData;
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " " << m_auiEncounter[3] << " " << m_auiEncounter[4];

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_blackrock_spire::SetData64(uint32 uiType, uint64 uiData)
{
    if (uiType == TYPE_ROOM_EVENT && GetData(TYPE_ROOM_EVENT) == IN_PROGRESS)
    {
        uint8 uiNotEmptyRoomsCount = 0;
        for (uint8 i = 0; i < MAX_ROOMS; ++i)
        {
            if (m_aRoomRuneGuid[i])                       // This check is used, to ensure which runes still need processing
            {
                m_alRoomEventMobGUIDSorted[i].remove(ObjectGuid(uiData));
                if (m_alRoomEventMobGUIDSorted[i].empty())
                {
                    DoUseDoorOrButton(m_aRoomRuneGuid[i]);
                    m_aRoomRuneGuid[i].Clear();
                }
                else
                    ++uiNotEmptyRoomsCount;                 // found an not empty room
            }
        }
        if (!uiNotEmptyRoomsCount)
            SetData(TYPE_ROOM_EVENT, DONE);
    }
}

void instance_blackrock_spire::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3] >> m_auiEncounter[4];

    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

uint32 instance_blackrock_spire::GetData(uint32 uiType)
{
    switch(uiType)
    {
        case TYPE_ROOM_EVENT:   return m_auiEncounter[0];
        case TYPE_EMBERSEER:    return m_auiEncounter[1];
        case TYPE_FLAMEWREATH:  return m_auiEncounter[2];
        case TYPE_STADIUM:      return m_auiEncounter[3];
        case TYPE_VALTHALAK:    return m_auiEncounter[4];
    }
    return 0;
}

void instance_blackrock_spire::DoSortRoomEventMobs()
{
    if (GetData(TYPE_ROOM_EVENT) != NOT_STARTED)
        return;

    for (uint8 i = 0; i < MAX_ROOMS; ++i)
    {
        if (GameObject* pRune = instance->GetGameObject(m_aRoomRuneGuid[i]))
        {
            for (GUIDList::const_iterator itr = m_lRoomEventMobGUIDList.begin(); itr != m_lRoomEventMobGUIDList.end(); ++itr)
            {
                Creature* pCreature = instance->GetCreature(*itr);
                if (pCreature && pCreature->isAlive() && pCreature->GetDistance(pRune) < 10.0f)
                    m_alRoomEventMobGUIDSorted[i].push_back(*itr);
            }
        }
    }

    SetData(TYPE_ROOM_EVENT, IN_PROGRESS);
}

void instance_blackrock_spire::OnCreatureDeath(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_DRAKKISATH:
            // Just open the doors, don't save anything because it's the last boss
            DoUseDoorOrButton(GO_DRAKKISATH_DOOR_1);
            DoUseDoorOrButton(GO_DRAKKISATH_DOOR_2);
            break;
    }
}

void instance_blackrock_spire::OnCreatureEvade(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        // Emberseer should evade if the incarcerators evade
        case NPC_BLACKHAND_INCARCERATOR:
            if (Creature* pEmberseer = GetSingleCreatureFromStorage(NPC_PYROGUARD_EMBERSEER))
                pEmberseer->AI()->EnterEvadeMode();
            break;
    }
}

void instance_blackrock_spire::OnCreatureEnterCombat(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        // Once one of the Incarcerators gets Aggro, the door should close
        case NPC_BLACKHAND_INCARCERATOR:
            SetData(TYPE_EMBERSEER, IN_PROGRESS);
            break;
    }
}

void instance_blackrock_spire::DoProcessEmberseerEvent()
{
    if (GetData(TYPE_EMBERSEER) == DONE || GetData(TYPE_EMBERSEER) == IN_PROGRESS)
        return;

    if (m_lIncarceratorGUIDList.empty())
    {
        error_log("SD2: Npc %u couldn't be found. Please check your DB content!", NPC_BLACKHAND_INCARCERATOR);
        return;
    }

    // start to grow
    if (Creature* pEmberseer = GetSingleCreatureFromStorage(NPC_PYROGUARD_EMBERSEER))
    {
        // If already casting, return
        if (pEmberseer->HasAura(SPELL_EMBERSEER_GROWING))
            return;

        DoScriptText(EMOTE_BEGIN, pEmberseer);
        pEmberseer->CastSpell(pEmberseer, SPELL_EMBERSEER_GROWING, true);
    }

    // remove the incarcerators flags and stop casting
    for (GUIDList::const_iterator itr = m_lIncarceratorGUIDList.begin(); itr != m_lIncarceratorGUIDList.end(); ++itr)
    {
        if (Creature* pCreature = instance->GetCreature(*itr))
        {
            if (pCreature->isAlive())
            {
                pCreature->InterruptNonMeleeSpells(false);
                pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
            }
        }
    }
}

void instance_blackrock_spire::DoUseEmberseerRunes(bool bReset)
{
    if (m_lEmberseerRunesGUIDList.empty())
        return;

    for (GUIDList::const_iterator itr = m_lEmberseerRunesGUIDList.begin(); itr != m_lEmberseerRunesGUIDList.end(); itr++)
    {
        if (bReset)
        {
            if (GameObject* pRune = instance->GetGameObject(*itr))
                pRune->ResetDoorOrButton();
        }
        else
            DoUseDoorOrButton(*itr);
    }
}

InstanceData* GetInstanceData_instance_blackrock_spire(Map* pMap)
{
    return new instance_blackrock_spire(pMap);
}

bool AreaTrigger_at_blackrock_spire(Player* pPlayer, AreaTriggerEntry const* pAt)
{
    if (pPlayer->isDead())
        return false;

    switch (pAt->id)
    {
        case AREATRIGGER_ENTER_UBRS:
            if (instance_blackrock_spire* pInstance = (instance_blackrock_spire*) pPlayer->GetInstanceData())
                pInstance->DoSortRoomEventMobs();
            break;
        case AREATRIGGER_STADIUM:
            if (instance_blackrock_spire* pInstance = (instance_blackrock_spire*) pPlayer->GetInstanceData())
                if (Creature* pGyth = pInstance->GetSingleCreatureFromStorage(NPC_GYTH))
                    if (pGyth->isAlive() && !pGyth->isInCombat())
                        pGyth->AI()->AttackStart(pPlayer);
            break;
    }
    return false;
}

bool ProcessEventId_event_spell_altar_emberseer(uint32 uiEventId, Object* pSource, Object* pTarget, bool bIsStart)
{
    if (bIsStart && pSource->GetTypeId() == TYPEID_PLAYER)
    {
        if (instance_blackrock_spire* pInstance = (instance_blackrock_spire*)((Player*)pSource)->GetInstanceData())
        {
            pInstance->DoProcessEmberseerEvent();
            return true;
        }
    }
    return false;
}

void AddSC_instance_blackrock_spire()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_blackrock_spire";
    pNewScript->GetInstanceData = &GetInstanceData_instance_blackrock_spire;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_blackrock_spire";
    pNewScript->pAreaTrigger = &AreaTrigger_at_blackrock_spire;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "event_spell_altar_emberseer";
    pNewScript->pProcessEventId = &ProcessEventId_event_spell_altar_emberseer;
    pNewScript->RegisterSelf();
}
