-- ---------------
-- Oculus instance
-- ---------------
-- ---------------------- Script Names ----------------------
UPDATE `creature_template` SET `AIName` = '', `vehicle_id` = 70, `ScriptName` = 'mob_oculus_dragon' WHERE `entry` IN (27692,27756,27755);
UPDATE `instance_template` SET `ScriptName` = 'instance_oculus' WHERE `map` = 578;
UPDATE `creature_template` SET `ScriptName` = 'npc_unstable_sphere' WHERE entry = 28166;
UPDATE `creature_template` SET `ScriptName` = 'boss_drakos' WHERE entry = 27654;
UPDATE `creature_template` SET `ScriptName` = 'boss_eregos' WHERE entry = 27656;
UPDATE `creature_template` SET `ScriptName` = 'boss_varos' WHERE entry = 27447;
UPDATE `creature_template` SET `ScriptName` = 'npc_varos_orb' WHERE entry = 28183;
UPDATE `creature_template` SET `ScriptName` = 'npc_varos_beam_target' WHERE entry = 28239;
UPDATE `creature_template` SET `ScriptName` = 'npc_oculus_robot' WHERE entry = 27641;
UPDATE `creature_template` SET `ScriptName` = 'boss_urom' WHERE entry = 27655;
UPDATE `creature_template` SET `ScriptName` = 'npc_planar_anomaly' WHERE entry = 30879;
UPDATE `creature_template` SET `ScriptName` = 'npc_belgar_image' WHERE entry = 28012;
UPDATE `gameobject_template` SET `ScriptName` = 'go_oculus_portal' WHERE `entry` = 188715;

-- -----------------------  Instance fixes DB -----------------------------

-- Unstable Sphere Fixes
UPDATE `creature_template` SET `minlevel` = 81, `maxlevel` = 81, `unit_flags` = 33587202 WHERE `entry` = 28166;

-- from traponinet
/* Belgaristrasz and his companions give Drake, after completed quest (13124) */
UPDATE `creature_template` SET `npcflag` = npcflag|1 WHERE `entry` IN (27657, 27658, 27659);
UPDATE `creature_template` SET `gossip_menu_id` = 27657 WHERE `entry` = 27657;
UPDATE `creature_template` SET `gossip_menu_id` = 27658 WHERE `entry` = 27658;
UPDATE `creature_template` SET `gossip_menu_id` = 27659 WHERE `entry` = 27659;

REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) values
-- (61407, 1, 27447),  -- TargetEntry 27447 does not have any implicit target TARGET_SCRIPT(38) or TARGET_SCRIPT_COORDINATES (46) or TARGET_FOCUS_OR_SCRIPTED_GAMEOBJECT (40).
(51024, 1, 28239),
(51022, 1, 28239),
(57963, 1, 27656);

DELETE FROM `gossip_scripts` WHERE `id` IN (27657, 27658, 27659);
INSERT INTO `gossip_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES 
(27657,0,17,37815,1,0,0,0,0,0,0,0,0,0,0,0,''),(27658,0,17,37860,1,0,0,0,0,0,0,0,0,0,0,0,''),(27659,0,17,37859,1,0,0,0,0,0,0,0,0,0,0,0,'');

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (27657, 27658, 27659);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`, `cond_1`, `cond_1_val_1`, `cond_1_val_2`, `cond_2`, `cond_2_val_1`, `cond_2_val_2`, `cond_3`, `cond_3_val_1`, `cond_3_val_2`) VALUES
(27657,0,0,'What\'s can Emerald Drake?.',1,1,13259,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(27657,1,2,'Take the Emerald Essence if you want to fly on the wings of the Green Flight.',1,1,-1,0,27657,0,0,NULL,16,37859,1,16,37815,1,16,37860,1),
(27659,0,0,'What\'s can Bronze Drake?.',1,1,13255,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(27659,1,2,'Take the Amber Essence if you want to fly on the wings of the Bronze Flight.',1,1,-1,0,27659,0,0,NULL,16,37859,1,16,37815,1,16,37860,1),
(27658,0,0,'What\'s can Ruby Drake?.',1,1,13257,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0),
(27658,1,2,'Take the Ruby Essence if you want to fly on the wings of the Red Flight.',1,1,-1,0,27658,0,0,NULL,16,37859,1,16,37815,1,16,37860,1);
-- (27658,0,0,'GOSSIP_OPTION_QUESTGIVER',2,2,0,0,0,0,0,NULL,0,0,0,0,0,0,0,0,0);

DELETE FROM `locales_gossip_menu_option` WHERE `menu_id` IN (27657, 27658, 27659);
INSERT INTO `locales_gossip_menu_option` (`menu_id`, `id`, `option_text_loc1`, `option_text_loc2`, `option_text_loc3`, `option_text_loc4`, `option_text_loc5`, `option_text_loc6`, `option_text_loc7`, `option_text_loc8`, `box_text_loc1`, `box_text_loc2`, `box_text_loc3`, `box_text_loc4`, `box_text_loc5`, `box_text_loc6`, `box_text_loc7`, `box_text_loc8`) VALUES
(27657, 0, 'What\'s can Emerald Drake?', NULL, NULL, NULL, NULL, NULL, NULL, 'Что умеет Изумрудный дракон?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(27657, 1, 'Take the Emerald Essence if you want to fly on the wings of the Green Flight.', NULL, NULL, NULL, NULL, NULL, NULL, 'Возьмите Изумрудную эссенцию, если Вы хотите лететь на зеленом драконе.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(27659, 0, 'What\'s can Bronze Drake?', NULL, NULL, NULL, NULL, NULL, NULL, 'Что умеет Бронзовый дракон?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(27659, 1, 'Take the Amber Essence if you want to fly on the wings of the Bronze Flight.', NULL, NULL, NULL, NULL, NULL, NULL, 'Возьмите Янтарную эссенцию, если Вы хотите лететь на бронзовом драконе.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(27658, 0, 'What\'s can Red Drake?', NULL, NULL, NULL, NULL, NULL, NULL, 'Что умеет Красный дракон?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(27658, 1, 'Take the Ruby Essence if you want to fly on the wings of the Red Flight.', NULL, NULL, NULL, NULL, NULL, NULL, 'Возьмите Рубиновую эссенцию, если Вы хотите лететь на красном драконе.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

DELETE FROM `gossip_menu` WHERE `entry` IN (27657, 27658, 27659);
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES (27657,13258),(27658,13254),(27659,13256);
DELETE FROM `gossip_menu` WHERE `entry` IN (13259, 13255, 13257);
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES (13259,13259),(13255,13255),(13257,13257);

-- Fix YTDB bug
UPDATE `npc_text` SET `text0_0` = `text0_1` WHERE `text0_0` = '' AND `ID` IN (13258,13259);
UPDATE `locales_npc_text` SET `Text0_0_loc8` = `Text0_1_loc8` WHERE `Text0_0_loc8` = '' AND `entry` IN (13258,13259);

UPDATE `creature` SET `spawnMask` = 3 WHERE `map` = 578 AND `spawnMask` = 1;

-- Eregos chests
UPDATE `gameobject` SET `spawnMask` = 2 WHERE `map` = 578 AND `id` = 193603;
UPDATE `gameobject` SET `spawnMask` = 1 WHERE `map` = 578 AND `id` = 191349;

UPDATE `creature_template` SET `InhabitType` = 3, spell6 = 0 WHERE `entry` IN (27755,27756,27692);
REPLACE INTO `creature_template_addon` VALUES (27755,0,0,0,0,0,0,'57403');
REPLACE INTO `creature_template_addon` VALUES (27756,0,0,0,0,0,0,'57403');
REPLACE INTO `creature_template_addon` VALUES (27692,0,0,0,0,0,0,'57403');

/* hack for broken Nexus Portal */
UPDATE `gameobject_template` SET `data0` = 49665 WHERE `entry` = 189985;
UPDATE `spell_target_position` SET `id` = 49665 WHERE `id` = 49305;

UPDATE `creature_template` SET `spell6` = 57403, `InhabitType` = 3 WHERE `entry` IN (27692,27755,27756);

DELETE FROM gameobject_scripts WHERE id IN 
(40557,42275);
INSERT INTO gameobject_scripts 
(id, delay, command, datalong, datalong2, dataint, x, y, z, o, comments) 
VALUES 
(42275, 1, 6, 571, 0, '0', 3878.0, 6984.0, 106.0, 0, ''),
(40557, 1, 6, 578, 0, '0', 1001.61, 1051.13, 359.48, 3.1, '');

DELETE FROM `spell_script_target` WHERE `entry` IN (49460, 49346, 49464);
INSERT INTO `spell_script_target` VALUES (49460, 1, 27755);
INSERT INTO `spell_script_target` VALUES (49346, 1, 27692);
INSERT INTO `spell_script_target` VALUES (49464, 1, 27756);

-- from lanc
UPDATE `creature_template` SET
    spell1 = 50232,
    spell2 = 50248,
    spell3 = 50240,
    spell4 = 50253,
    spell5 = 0
WHERE `entry` IN (27756);

UPDATE `creature_template` SET
    spell1 = 49840,
    spell2 = 49838,
    spell3 = 49592,
    spell4 = 0,
    spell5 = 0
WHERE `entry` IN (27755);
 
UPDATE `creature_template` SET
    spell1 = 50328,
    spell2 = 50341,
    spell3 = 50344,
    spell4 = 0,
    spell5 = 0
WHERE `entry` IN (27692);

DELETE FROM `spell_script_target` WHERE `entry` IN (49460, 49346, 49464);
INSERT INTO `spell_script_target` VALUES (49460, 1, 27755);
INSERT INTO `spell_script_target` VALUES (49346, 1, 27692);
INSERT INTO `spell_script_target` VALUES (49464, 1, 27756);

-- herbalism flower   a ytdb bugs flowers cant wander around lol
UPDATE `creature_template` SET `unit_flags` = 33555204, `dynamicflags` = 8 WHERE `entry` = 29888;
UPDATE `creature_template` SET `speed_walk` = 0, `speed_run` = 0, `movementId` = 0 WHERE `entry` = 29888;

-- Varos
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 27447; -- added immune to pacify
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 31559; -- added immune to pacify to hard version 

-- Drakos the Interrogator
UPDATE `creature_template` SET `maxhealth` = 431392 WHERE `entry` = 31558;  -- Hard Instance Version  data from wow.com
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 27654;  -- added immune to pacify
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299931 WHERE `entry` = 31558;  -- added immune to pacify to hard version

-- ---------------------Achievements ------------------------------
-- Oculus
DELETE FROM `achievement_criteria_requirement` where `criteria_id` IN(203,204,205,206);
INSERT INTO `achievement_criteria_requirement` VALUES(203,12,0,0),(204,12,0,0),(205,12,0,0),(206,12,0,0);

-- Oculus (heroic)
DELETE FROM `achievement_criteria_requirement` WHERE `criteria_id` IN(6859,6860,6861,6862);
INSERT INTO `achievement_criteria_requirement` VALUES(6859,12,1,0),(6860,12,1,0),(6861,12,1,0),(6862,12,1,0);

-- Make It Count + Expirienced Drake Rider
DELETE FROM `achievement_criteria_requirement` WHERE `criteria_id` IN(7145,7178,7179,7177);
INSERT INTO `achievement_criteria_requirement` VALUES(7145,12,1,0),(7178,12,1,0),(7179,12,1,0),(7177,12,1,0);
