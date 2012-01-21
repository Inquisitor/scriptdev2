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
SDName: boss_valithria
SD%Complete: 70%
SDComment: by /dev/rsa
SDCategory: Icecrown Citadel
EndScriptData */
// Need move emerald dream to phase 32, correct timers and other
#include "precompiled.h"
#include "icecrown_citadel.h"

static Locations SpawnLoc[]=
{
    {4203.470215f, 2484.500000f, 364.872009f},  // 0 Valithria
    {4240.688477f, 2405.794678f, 364.868591f},  // 1 Valithria Room 1
    {4239.579102f, 2566.753418f, 364.868439f},  // 2 Valithria Room 2
    {4165.112305f, 2405.872559f, 364.872925f},  // 3 Valithria Room 3
    {4166.216797f, 2564.197266f, 364.873047f},  // 4 Valithria Room 4  
    {4228.589844f, 2469.110107f, 364.868988f},  // 5 Portal 1
    {4236.000000f, 2479.500000f, 364.869995f},  // 6 Portal 2
    {4235.410156f, 2489.300049f, 364.872009f},  // 7 Portal 3
    {4239.863281f, 2484.282954f, 364.871185f},  // 8 Portal 4
    {4228.509766f, 2500.310059f, 364.876007f},  // 9 Portal 6
    {4251.833080f, 2458.623535f, 391.041321f},  // 10 Cloud 1
    {4203.649902f, 2483.889893f, 364.960999f},  // 11 Cloud 2
    {4247.037598f, 2444.540527f, 382.742279f},  // 12 Cloud 3
    {4168.562500f, 2447.892822f, 390.273773f},  // 13 Cloud 4
    {4151.910645f, 2452.270996f, 379.948608f},  // 14 Cloud 5
    {4163.886230f, 2467.732178f, 409.547760f},  // 15 Cloud 6
    {4145.806641f, 2498.220947f, 395.431610f},  // 16 Cloud 7
    {4159.713379f, 2413.130615f, 384.285278f},  // 17 Cloud 8
    {4186.778320f, 2899.192139f, 384.888318f},  // 18 Cloud 9
    {4245.999512f, 2511.154297f, 383.564758f},  // 19 Cloud 10
    {4246.204102f, 2518.059326f, 390.944946f},  // 20 Cloud 11
    {4230.643555f, 2519.520752f, 380.044037f},  // 21 Cloud 12

};

enum BossSpells
{
    SPELL_NIGHTMARE_PORTAL        = 71977, 
    SPELL_DREAM_PORTAL            = 72225,  
    SPELL_EMERALD_VIGOR           = 70873,  
    SPELL_TWISTED_NIGHTMARE       = 71941,  
    SPELL_DREAMWALKER_RAGE        = 71189, 
    SPELL_IMMUNITY                = 72724, 
    SPELL_CORRUPTION              = 70904, 
    SPELL_DREAM_SLIP              = 71196, 
    SPELL_ICE_SPIKE               = 70702, 
    SPELL_SUMMON_NIGHTMARE_PORTAL = 71987,  
    SPELL_SUMMON_DREAM_PORTAL     = 71305,  
    SPELL_ROT_WORM_SPAWNED        = 70675,    
    SPELL_SOUL_FEAST              = 71203, 
    SPELL_GUT_SPRAY               = 70633,  
    SPELL_ACID_BURST              = 70744, 
    SPELL_CORROSION               = 70751, 
    SPELL_FIREBALL                = 70754, 
    SPELL_LAY_WASTE               = 69325, 
    SPELL_SUPPRESSER              = 70588, 
    SPELL_DREAM_CLOUD_VISUAL      = 70876,
    SPELL_NIGHTMARE_CLOUD_VISUAL  = 71939,
    SPELL_DREAM_STATE             = 70766,
    SPELL_COLUMN_OF_FROST         = 70704, 
    SPELL_COLUMN_OF_FROST_VISUAL  = 70715,
    SPELL_COLUMN_OF_FROST_TRIG    = 70702,
    SPELL_FROSTBOLT_VOLLEY        = 70759,
    SPELL_MANA_VOID               = 71179,
    SPELL_VOID_BUFF               = 71085,
    
  

// Summons
    NPC_RISEN_ARCHMAGE           = 37868,
    NPC_SUPPRESSOR               = 37863,
    NPC_BLASING_SKELETON         = 36791,
    NPC_BLISTERING_ZOMBIE        = 37934,
    NPC_GLUTTONOUS_ABOMINATION   = 37886,
    //Clouds
    NPC_DREAM_CLOUD              = 37985,
    NPC_NIGHTMARE_CLOUD          = 38421,
//Portals
    NPC_NIGHTMARE_PORTAL         = 38429,
    NPC_DREAM_PORTAL             = 38186,
    NPC_NIGHTMARE_PORTAL_PRE     = 38430,
    NPC_DREAM_PORTAL_PRE         = 37945,
    // Mana void
    NPC_MANA_VOID                = 38068,
    NPC_COLUMN_OF_FROST          = 37918,
//BOSS
    NPC_VALITHRIA_DREAMWALKER    = 36789,
    NPC_VALITHRIA_IN_PORTAL      = 37950,
};                                         

struct MANGOS_DLL_DECL boss_valithria_dreamwalkerAI : public BSWScriptedAI
{
    boss_valithria_dreamwalkerAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        pInstance = (instance_icecrown_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_icecrown_spire* pInstance;
    bool battlestarted;
    bool intro;
    uint8 currentDoor;
    uint8 currentDoor2;
    int8 portalscount;
    std::list<ObjectGuid> mobsGUIDList;
    uint32 speedK;
    Creature* dummyTarget;
    uint32 VolTimer;
    uint32 VolTimer1;
    uint32 BasicVolTimer;
    uint8 AdsCount;
    bool First;

    void Reset()
    {
        if(!pInstance) return;
        m_creature->SetRespawnDelay(7*DAY);
        m_creature->SetHealth(m_creature->GetMaxHealth()/2.0f);
        if (pInstance->GetData(TYPE_VALITHRIA) != DONE)
            pInstance->SetData(TYPE_VALITHRIA, NOT_STARTED);
        else m_creature->ForcedDespawn();
        resetTimers();
        SetCombatMovement(false);
        setStage(0);
        speedK = 0;
        portalscount = 0;
        battlestarted = false;
        First=true;
        intro = false;
        currentDoor = 0;    
        currentDoor2 = 0;
        VolTimer1 = 5000;
        AdsCount=0;
        First=true;
        BasicVolTimer=25000;
        mobsGUIDList.clear();
        if (Creature* pTemp = pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA_QUEST))
                if (pTemp->GetVisibility() == VISIBILITY_ON)
                            pTemp->SetVisibility(VISIBILITY_OFF);
        doCast(SPELL_CORRUPTION);
    }

    uint32 GetDoor(uint8 doornum)
    {
        switch (doornum) {
            case 1:
               return GO_VALITHRIA_DOOR_2;
               break;
            case 2:
               return GO_VALITHRIA_DOOR_4;
               break;
            case 3:
               return GO_VALITHRIA_DOOR_3;
               break;
            case 4:
               return GO_VALITHRIA_DOOR_1;
               break;
            default:
               return 0;
               break;
        };
    }

    void CallMobs(uint8 door, uint8 ad)
    {
       if(!door) return;
        uint32 randommob; 
                             switch (ad) 
                             {
                              case 0: randommob = NPC_SUPPRESSOR;             break;
                              case 1: randommob = NPC_BLISTERING_ZOMBIE;      break;
                              case 2: randommob = NPC_BLASING_SKELETON;       break;
                              case 3: randommob = NPC_GLUTTONOUS_ABOMINATION; break;
                              case 4: randommob = NPC_RISEN_ARCHMAGE;         break;
                              default: break;
                              }
                             if (Unit* pTemp = doSummon(randommob, SpawnLoc[door].x, SpawnLoc[door].y, SpawnLoc[door].z, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000))
                                    mobsGUIDList.push_back(pTemp->GetObjectGuid());  
    }

    void SummPortal(uint32 npc, uint8 countportal)
    {
      if (countportal == 2)
      for(uint8 i = 6; i <= 8 ; ++i) doSummon(npc, SpawnLoc[i].x, SpawnLoc[i].y, SpawnLoc[i].z);
      else
        for(uint8 i = 5; i <= 9 ; ++i) doSummon(npc, SpawnLoc[i].x, SpawnLoc[i].y, SpawnLoc[i].z);
      
    }

    void QueryEvadeMode()
    {
        if ( m_creature->GetHealthPercent() > 1.0f  )
        {
            Map* pMap = m_creature->GetMap();
            Map::PlayerList const &players = pMap->GetPlayers();
            for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
            {
                if(Player* pPlayer = i->getSource())
                if(pPlayer->isAlive() && !pPlayer->isGameMaster()
                && pPlayer->IsWithinDistInMap(m_creature, 90.0f)) return;
            }
        }
        pInstance->SetData(TYPE_VALITHRIA, FAIL);
        DoScriptText(-1631409,m_creature);
        DespawnMobs();
        m_creature->DeleteThreatList();
        m_creature->CombatStop(true);
        m_creature->LoadCreatureAddon();
        if (m_creature->isAlive())
            m_creature->GetMotionMaster()->MoveTargetedHome();
        m_creature->SetLootRecipient(NULL);
        pInstance->DoCloseDoor(GetDoor(currentDoor));
        pInstance->DoCloseDoor(GetDoor(currentDoor2));
        Reset();
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (!pInstance || ( intro && battlestarted)) return;

        if (pWho->GetTypeId() != TYPEID_PLAYER) return;

        if (!intro)
        {
            DoScriptText(-1631401,m_creature,pWho);
            intro = true;
            doCast(SPELL_IMMUNITY);
        }
        if (!battlestarted && pWho->isAlive() && pWho->IsWithinDistInMap(m_creature, 40.0f))
        {    
            DoScriptText(-1631401,m_creature,pWho);
            battlestarted = true;
            pInstance->SetData(TYPE_VALITHRIA, IN_PROGRESS);
            m_creature->SetHealth(m_creature->GetMaxHealth()/2.0f);
            dummyTarget = pInstance->GetSingleCreatureFromStorage(NPC_COMBAT_TRIGGER);
            if (!dummyTarget)
                dummyTarget = m_creature->SummonCreature(NPC_COMBAT_TRIGGER, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 1000);
            if (!dummyTarget->isAlive())
                dummyTarget->Respawn();
            if (dummyTarget)
            {    
                dummyTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                dummyTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                dummyTarget->GetMotionMaster()->MoveIdle();
                dummyTarget->StopMoving();
            }
            m_creature->SetInCombatWith(dummyTarget);
            m_creature->SetHealth(m_creature->GetMaxHealth()/2.0f);
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        if(!pInstance) return;

        switch (urand(0,1)) {
            case 0:
               DoScriptText(-1631403,m_creature,pVictim);
               break;
            case 1:
               DoScriptText(-1631404,m_creature,pVictim);
               break;
        };
    }

    void JustSummoned(Creature* summoned)
    {
        if(!pInstance || !summoned || !battlestarted) return;
        if ( summoned->GetEntry() != NPC_NIGHTMARE_PORTAL )
        {
             m_creature->SetInCombatWithZone();
             m_creature->SetInCombatWith(summoned);
             summoned->SetInCombatWith(m_creature);
             summoned->AddThreat(m_creature, 100.0f);
             summoned->GetMotionMaster()->MoveChase(m_creature);
        }
    }

    void DespawnMobs()
    {
        if (mobsGUIDList.empty())
            return;

        for(std::list<ObjectGuid>::iterator itr = mobsGUIDList.begin(); itr != mobsGUIDList.end(); ++itr)
        {
            if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
            {
                if (pTemp->isAlive())
                {
                    pTemp->DeleteThreatList();
                    pTemp->CombatStop(true);
                    pTemp->DealDamage(pTemp, pTemp->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                }
            }
        }
        mobsGUIDList.clear();
    }

    void JustDied(Unit *killer)
    {
        if(!pInstance) return
        pInstance->SetData(TYPE_VALITHRIA, FAIL);
        DoScriptText(-1631409,m_creature);
        DespawnMobs();
        m_creature->Respawn();
        Reset();
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (!m_creature || !m_creature->isAlive())
            return;

        if (uiDamage >= m_creature->GetHealth()) uiDamage = 0;
    }

    void AttackStart(Unit *who)
    {
    }

    void UpdateAI(const uint32 diff)
    { 
        if (!hasAura(SPELL_CORRUPTION,m_creature) && getStage() == 0)
             doCast(SPELL_CORRUPTION);

        if (!battlestarted) return;

        QueryEvadeMode();

        switch(getStage())
        {
            case 0:
                    if ( m_creature->GetHealthPercent() > 90.0f ) setStage(2);
                    if ( m_creature->GetHealthPercent() < 10.0f ) setStage(3);
                    break;
            case 1:
                    if ( m_creature->GetHealthPercent() < 90.0f && m_creature->GetHealthPercent() > 10.0f ) setStage(0);
                    if ( m_creature->GetHealthPercent() > 99.9f ) setStage(5);
                    break;
            case 2:
                    DoScriptText(-1631407,m_creature);
                    setStage(1);
                    break;
            case 3:
                    DoScriptText(-1631406,m_creature);
                    setStage(1);
                    break;
            case 4:
                    break;
            case 5:
                    DoScriptText(-1631408,m_creature);
                    if (hasAura(SPELL_CORRUPTION,m_creature)) doRemove(SPELL_CORRUPTION);
                    setStage(6);
                    return;
                    break;
            case 6:
                    if (timedQuery(SPELL_CORRUPTION, diff)) setStage(7);
                    return;
                    break;
            case 7:
                    doCast(SPELL_DREAMWALKER_RAGE);
                    setStage(8);
                    return;
                    break;
            case 8:
                    if (timedQuery(SPELL_CORRUPTION, diff))
                    {
                        setStage(9);
                        DespawnMobs();
                    }
                    return;
                    break;
            case 9:
                    if (Creature* pTemp = pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA_QUEST))
                    {
                        pTemp->SetPhaseMask(65535,true);
                        if (pTemp->HasAura(SPELL_CORRUPTION))
                             pTemp->RemoveAurasDueToSpell(SPELL_CORRUPTION);
                        if (pTemp->GetVisibility() == VISIBILITY_OFF)
                            pTemp->SetVisibility(VISIBILITY_ON);
                    }
                    pInstance->SetData(TYPE_VALITHRIA, DONE);
                    setStage(10);
                    m_creature->ForcedDespawn();
                    break;
            default:
                    break;
        }


        if (First)
        {
            VolTimer=BasicVolTimer;
            VolTimer1=5000;
            AdsCount=0;
            First=false;
        }
        if (VolTimer<=1000)
        {
            if (VolTimer1<=1000)
            {
                if (currentDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || currentDifficulty == RAID_DIFFICULTY_25MAN_HEROIC) 
                {
                    pInstance->DoCloseDoor(GetDoor(currentDoor2));
                    currentDoor2 = urand(1,2);
                    pInstance->DoOpenDoor(GetDoor(currentDoor2));
                    CallMobs(currentDoor2, AdsCount);
                    pInstance->DoCloseDoor(GetDoor(currentDoor));
                    currentDoor = urand(3,4);
                    pInstance->DoOpenDoor(GetDoor(currentDoor));
                    CallMobs(currentDoor, AdsCount);
                }
                else 
                {
                    pInstance->DoCloseDoor(GetDoor(currentDoor));
                    currentDoor = urand(1,2);
                    pInstance->DoOpenDoor(GetDoor(currentDoor));
                    CallMobs(currentDoor, AdsCount);
                }
                if (urand(0,1) == 1) DoScriptText(-1631402,m_creature);
                AdsCount++;
                VolTimer1=5000;
            }
            else VolTimer1 -= diff;
            if (AdsCount>4)
            {
                if (BasicVolTimer<=0)BasicVolTimer=5000; else BasicVolTimer -= 5000;
                VolTimer = BasicVolTimer;
                AdsCount=0;
                First=false;
            }
        }
        else  VolTimer -= diff;

        if (timedQuery(SPELL_NIGHTMARE_PORTAL, diff))
        {
            DoScriptText(-1631405,m_creature);
            if (currentDifficulty==RAID_DIFFICULTY_25MAN_HEROIC) doCast(SPELL_NIGHTMARE_PORTAL); else doCast(SPELL_DREAM_PORTAL); 
            switch (currentDifficulty) 
            {
                case RAID_DIFFICULTY_10MAN_NORMAL:
                   SummPortal(NPC_DREAM_PORTAL, 2);
                   break;
                case RAID_DIFFICULTY_10MAN_HEROIC:
                   SummPortal(NPC_DREAM_PORTAL, 2);
                   break;
                case RAID_DIFFICULTY_25MAN_NORMAL:
                   SummPortal(NPC_DREAM_PORTAL, 4);
                   break;
                case RAID_DIFFICULTY_25MAN_HEROIC:
                   SummPortal(NPC_NIGHTMARE_PORTAL, 4);
                   break;
                default:  break;    
            }
        }
        return;
    }
};

CreatureAI* GetAI_boss_valithria_dreamwalker(Creature* pCreature)
{
    return new boss_valithria_dreamwalkerAI(pCreature);
};

//portals
struct MANGOS_DLL_DECL mob_nightmare_portalAI : public BSWScriptedAI
{
    mob_nightmare_portalAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_desp;
    bool b_cast;

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        SetCombatMovement(false);
        m_desp=6000;
        b_cast=false;
    }
    void AttackStart(Unit *pWho)
    {
        return;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS) return;
        if (timedQuery(SPELL_SUMMON_NIGHTMARE_PORTAL, uiDiff))
        {
            doCast(SPELL_SUMMON_NIGHTMARE_PORTAL);
            b_cast=true;  
        }
        if ((m_desp<=1000)&&(b_cast)) m_creature->ForcedDespawn(); else m_desp -= uiDiff; 
    }

};

CreatureAI* GetAI_mob_nightmare_portal(Creature *pCreature)
{
    return new mob_nightmare_portalAI(pCreature);
};
struct MANGOS_DLL_DECL mob_dream_portalAI : public BSWScriptedAI
{
    mob_dream_portalAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_desp;
    bool b_cast;

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        SetCombatMovement(false);
        m_desp=6000;
        b_cast=false;
    }


    void AttackStart(Unit *pWho)
    {
        return;
    }

    void UpdateAI(const uint32 uiDiff)
    {
         if (!m_pInstance || m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS) return; 
         m_creature->StopMoving();
         if (timedQuery(SPELL_SUMMON_DREAM_PORTAL, uiDiff))
         {
             doCast(SPELL_SUMMON_DREAM_PORTAL);
             b_cast=true;
         }
         if ((m_desp<=1000)&&(b_cast)) m_creature->ForcedDespawn(); else m_desp -= uiDiff; 
     }

};

CreatureAI* GetAI_mob_dream_portal(Creature *pCreature)
{
    return new mob_dream_portalAI(pCreature);
};

//portals_PRE
struct MANGOS_DLL_DECL mob_portal_preAI : public BSWScriptedAI
{
    mob_portal_preAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {

    }

    void AttackStart(Unit *pWho)
    {
        return;
    }

    void StartEvent(Player* pPlayer, Creature* pCreature)
    {
        pPlayer->CastSpell(pPlayer, SPELL_DREAM_STATE, true);
        pCreature->ForcedDespawn(100);

    }

    void UpdateAI(const uint32 uiDiff)
    {
    }

};

CreatureAI* GetAI_mob_portal_pre(Creature *pCreature)
{
    return new mob_portal_preAI(pCreature);
};
bool GossipHello_mob_portal_pre(Player* pPlayer, Creature* pCreature)
{
    pPlayer->CLOSE_GOSSIP_MENU();
    ((mob_portal_preAI*)pCreature->AI())->StartEvent(pPlayer, pCreature);
        return true;
}
//clouds
struct MANGOS_DLL_DECL mob_nightmare_cloudAI : public BSWScriptedAI
{
    mob_nightmare_cloudAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool b_Cast;
    uint32 m_uiTimeToReset;

    void Reset()
    {
        b_Cast = false;
        DoCastSpellIfCan(m_creature, SPELL_NIGHTMARE_CLOUD_VISUAL, CAST_TRIGGERED);
    }

    void AttackStart(Unit *pWho)
    {
     return;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (b_Cast)return;
        if (pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if (m_creature->GetDistance(pWho) < 5.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_TWISTED_NIGHTMARE) == CAST_OK)
                {
                    b_Cast = true;
                    m_uiTimeToReset = 30000; // simulating respawn
                    m_creature->RemoveAllAuras();
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (b_Cast)
        {
            if (m_uiTimeToReset <= uiDiff)
            {
                Reset();
            }
            else
                m_uiTimeToReset -= uiDiff;
        }
    }
};

CreatureAI* GetAI_mob_nightmare_cloud(Creature *pCreature)
{
    return new mob_nightmare_cloudAI(pCreature);
};
struct MANGOS_DLL_DECL mob_dream_cloudAI : public BSWScriptedAI
{
    mob_dream_cloudAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool b_Cast;
    uint32 m_uiTimeToReset;

    void Reset()
    {
        b_Cast = false;
        DoCastSpellIfCan(m_creature, SPELL_DREAM_CLOUD_VISUAL, CAST_TRIGGERED);
    }

    void AttackStart(Unit *pWho)
    {
     return;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (b_Cast)return;
        if (pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if (m_creature->GetDistance(pWho) < 5.0f)
            {
                doCast(SPELL_EMERALD_VIGOR, pWho);
                b_Cast = true;
                m_uiTimeToReset = 30000; // simulating respawn
                m_creature->RemoveAllAuras();
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (b_Cast)
        {
            if (m_uiTimeToReset <= uiDiff)
            {
                Reset();
            }
            else
                m_uiTimeToReset -= uiDiff;
        }
    }
};

CreatureAI* GetAI_mob_dream_cloud(Creature *pCreature)
{
    return new mob_dream_cloudAI(pCreature);
};
//   Ads 
struct MANGOS_DLL_DECL mob_gluttonous_abominationAI : public BSWScriptedAI
{
    mob_gluttonous_abominationAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_ui_Timer;
  

    void Reset()
    {
        m_ui_Timer = 30000;
    }


    void JustDied(Unit *killer)
    {
        m_creature->CastSpell(m_creature, SPELL_ROT_WORM_SPAWNED, true);
        m_creature->CastSpell(m_creature, SPELL_SOUL_FEAST, true);
    }

    void MoveInLineOfSight(Unit* pWho)     
    {
        if (pWho->isAlive()) 
        {
            Unit * pVictim = m_creature->getVictim();
            if (pVictim && pVictim->GetTypeId() == TYPEID_PLAYER)
                return;
            if ( pWho->GetTypeId() == TYPEID_PLAYER && pWho->IsWithinDistInMap(m_creature, m_creature->GetAttackDistance(m_creature)))  
            {
                m_creature->AddThreat(pWho, 2.0f);
                m_creature->Attack(pWho, true);
                SetCombatMovement(true);
                pWho->SetInCombatWith(m_creature);
                m_creature->SetInCombatWith(pWho);  
            }
            else
            {
                if (pWho->GetEntry() == NPC_VALITHRIA_DREAMWALKER && pWho->IsWithinDistInMap(m_creature, 10.0f))   
                {
                    m_creature->AddThreat(pWho, 1.0f);
                    m_creature->Attack(pWho, true);
                    SetCombatMovement(true);
                    m_creature->SetInCombatWith(pWho);  
                    pWho->SetInCombatWith(m_creature);
                }
            }
        }
    }

  void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)   return;
        timedCast(SPELL_GUT_SPRAY, uiDiff); 
        DoMeleeAttackIfReady();
        if (m_ui_Timer < uiDiff)
        {
            m_creature->ForcedDespawn();
        }
        else
        {
            m_ui_Timer -= uiDiff;
        }
    } 
  

};
CreatureAI* GetAI_mob_gluttonous_abomination(Creature *pCreature)
{
    return new mob_gluttonous_abominationAI(pCreature);
};


struct MANGOS_DLL_DECL mob_blistering_zombieAI : public BSWScriptedAI
{
    mob_blistering_zombieAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_ui_Timer;
    bool b_CastT;

    void Reset()
    {
        m_ui_Timer = 30000;
        b_CastT= false;
    }

  
    void DamageTaken(Unit* done_by, uint32 &damage)
    {
        if ((m_creature->GetHealthPercent()<1.0f)||(damage > m_creature->GetHealth()))
        {
             damage = 0;
             m_creature->CastSpell(m_creature, SPELL_SOUL_FEAST, true);
             doCast(SPELL_ACID_BURST);
             b_CastT= true;
         }
    }



  void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)   return;
        timedCast(SPELL_CORROSION, uiDiff); 
        DoMeleeAttackIfReady();
        if (timedQuery(SPELL_ACID_BURST, uiDiff)&&(b_CastT)) m_creature->ForcedDespawn();
        if (m_ui_Timer < uiDiff)
        {
            m_creature->ForcedDespawn();
        }
        else
        {
            m_ui_Timer -= uiDiff;
        }
    } 
  

};
CreatureAI* GetAI_mob_blistering_zombie(Creature *pCreature)
{
    return new mob_blistering_zombieAI(pCreature);
};

struct MANGOS_DLL_DECL mob_blazing_skeletonAI : public BSWScriptedAI
{
    mob_blazing_skeletonAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_ui_Timer;

    void Reset()
    {
        m_ui_Timer = 30000;
    }

    void JustDied(Unit *killer)
    {
        m_creature->CastSpell(m_creature, SPELL_SOUL_FEAST, true);
        m_creature->RemoveCorpse();
    }
   

  void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)   return;
        timedCast(SPELL_FIREBALL , uiDiff); 
        DoMeleeAttackIfReady();
        timedCast(SPELL_LAY_WASTE , uiDiff);
        if (m_ui_Timer < uiDiff)
        {
            m_creature->ForcedDespawn();
        }
        else
        {
            m_ui_Timer -= uiDiff;
        }
    } 
  

};
CreatureAI* GetAI_mob_blazing_skeleton(Creature *pCreature)
{
    return new mob_blazing_skeletonAI(pCreature);
};





struct MANGOS_DLL_DECL mob_suppresserAI : public BSWScriptedAI
{
    mob_suppresserAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_ui_Timer;

    void Reset()
    {
        m_ui_Timer = 30000;
    }

    void JustDied(Unit *killer)
    {
        m_creature->CastSpell(m_creature, SPELL_SOUL_FEAST, true);
        m_creature->RemoveCorpse();
    }
    
    
    void MoveInLineOfSight(Unit* pWho)
    {
        if (pWho->isAlive() &&  (pWho->GetEntry() == NPC_VALITHRIA_DREAMWALKER) && pWho->IsWithinDistInMap(m_creature, 100.0f) )   
        {
            m_creature->Attack(pWho, true);
            m_creature->SetInCombatWith(pWho);  
            pWho->SetInCombatWith(m_creature);
            m_creature->AddThreat(pWho, 100.0f);
        } 
        else
        {
            m_creature->AddThreat(pWho, 0.0f);
        }
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)   return;
        timedCast(SPELL_SUPPRESSER , uiDiff); 
        DoMeleeAttackIfReady();      
        if (m_ui_Timer < uiDiff)
        {
            m_creature->ForcedDespawn();
        }
        else
        {
            m_ui_Timer -= uiDiff;
        }
    } 
  

};
CreatureAI* GetAI_mob_suppresser(Creature *pCreature)
{
    return new mob_suppresserAI(pCreature);
};


// Risen Archmage
struct MANGOS_DLL_DECL mob_risen_archmageAI : public ScriptedAI
{
    mob_risen_archmageAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiFrostboltVolleyTimer;
    uint32 m_uiColumnOfFrostTimer;
    uint32 m_uiManaVoidTimer;

    void Reset()
    {
        m_uiFrostboltVolleyTimer = urand(3000, 5000);
        m_uiColumnOfFrostTimer = urand(3000, 5000);
        m_uiManaVoidTimer = urand(5000, 10000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Frostbolt Volley
        if (m_uiFrostboltVolleyTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_FROSTBOLT_VOLLEY) == CAST_OK)
                m_uiFrostboltVolleyTimer = urand(5000, 15000);
        }
        else
            m_uiFrostboltVolleyTimer -= uiDiff;

        // Column of Frost
        if (m_uiColumnOfFrostTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_COLUMN_OF_FROST) == CAST_OK)
                    m_uiColumnOfFrostTimer = urand(10000, 15000);
            }
        }
        else
            m_uiColumnOfFrostTimer -= uiDiff;

        // Mana Void
        if (m_uiManaVoidTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_MANA_VOID) == CAST_OK)
                    m_uiManaVoidTimer = urand(10000, 15000);
            }
        }
        else
            m_uiManaVoidTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_risen_archmage(Creature *pCreature)
{
    return new mob_risen_archmageAI(pCreature);
};
//frost colum
struct MANGOS_DLL_DECL mob_column_of_frostAI : public ScriptedAI
{
    mob_column_of_frostAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        SetCombatMovement(false);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        //m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_uiColumnOfFrostTimer = 3000;
        DoCastSpellIfCan(m_creature, SPELL_COLUMN_OF_FROST_VISUAL, CAST_TRIGGERED);
    }

    uint32 m_uiColumnOfFrostTimer;

    void Reset(){}
    void AttackStart(Unit *pWho){}
    void UpdateAI(const uint32 uiDiff)
    {
        // Column of Frost
        if (m_uiColumnOfFrostTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_COLUMN_OF_FROST_TRIG) == CAST_OK)
            {
                m_uiColumnOfFrostTimer = 2000;
                m_creature->ForcedDespawn(1000);
            }
        }
        else
            m_uiColumnOfFrostTimer -= uiDiff;
    }
};
                        
CreatureAI* GetAI_mob_column_of_frost(Creature *pCreature)
{
    return new mob_column_of_frostAI(pCreature);
};


//mana void
struct MANGOS_DLL_DECL mob_mana_voidAI : public ScriptedAI
{
    mob_mana_voidAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        DoCastSpellIfCan(m_creature, SPELL_VOID_BUFF, CAST_TRIGGERED);
        m_creature->ForcedDespawn(30000);
    }
    void Reset(){}
    void AttackStart(Unit *pWho){}
    void UpdateAI(const uint32 uiDiff){}
};

CreatureAI* GetAI_mob_mana_void(Creature *pCreature)
{
    return new mob_mana_voidAI(pCreature);
};
//VALITRIA IN PORTAL
struct MANGOS_DLL_DECL mob_valitria_in_portalAI : public BSWScriptedAI
{
  mob_valitria_in_portalAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_ui_Timer;
    bool b_SumCloud;

    void Reset()
    {
        m_ui_Timer = 20000;
        b_SumCloud = false;
    }
  
 void UpdateAI(const uint32 uiDiff)
    {
        if (b_SumCloud || !m_pInstance || m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)   return;
        if (m_pInstance || m_pInstance->GetData(TYPE_VALITHRIA) == IN_PROGRESS)   
        {
               for(uint8 i = 10; i <= 21 ; ++i) 
               {
                 if (currentDifficulty==RAID_DIFFICULTY_25MAN_HEROIC) 
                 {
                     doSummon(NPC_NIGHTMARE_CLOUD, SpawnLoc[i].x, SpawnLoc[i].y, SpawnLoc[i].z); 
                 }
                 else 
                 {
                     doSummon(NPC_DREAM_CLOUD, SpawnLoc[i].x, SpawnLoc[i].y, SpawnLoc[i].z);    
                 }
               }
               b_SumCloud=true;
        }
 }
     };

CreatureAI* GetAI_mob_valitria_in_portal(Creature *pCreature)
{
    return new mob_valitria_in_portalAI(pCreature);
};


void AddSC_boss_valithria_dreamwalker()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_valithria_dreamwalker";
    newscript->GetAI = &GetAI_boss_valithria_dreamwalker;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_nightmare_portal";
    newscript->GetAI = &GetAI_mob_nightmare_portal;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "mob_dream_portal";
    newscript->GetAI = &GetAI_mob_dream_portal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_nightmare_cloud";
    newscript->GetAI = &GetAI_mob_nightmare_cloud;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_dream_cloud";
    newscript->GetAI = &GetAI_mob_dream_cloud;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_gluttonous_abomination";
    newscript->GetAI = &GetAI_mob_gluttonous_abomination;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_blistering_zombie";
    newscript->GetAI = &GetAI_mob_blistering_zombie;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_blazing_skeleton";
    newscript->GetAI = &GetAI_mob_blazing_skeleton;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_suppresser";
    newscript->GetAI = &GetAI_mob_suppresser;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "mob_valitria_in_portal";
    newscript->GetAI = &GetAI_mob_valitria_in_portal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_portal_pre";
    newscript->GetAI = &GetAI_mob_portal_pre;
    newscript->pGossipHello = &GossipHello_mob_portal_pre;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_column_of_frost";
    newscript->GetAI = &GetAI_mob_column_of_frost;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_mana_void";
    newscript->GetAI = &GetAI_mob_mana_void;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_risen_archmage";
    newscript->GetAI = &GetAI_mob_risen_archmage;
    newscript->RegisterSelf();
}
    
