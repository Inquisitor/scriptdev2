-- -------------------
-- Instance_Ahnkahet -
-- -------------------

-- -------------
-- Elder Nadox -
-- -------------

-- boss Elder Nadox Achievment
UPDATE `achievement_criteria_requirement` SET `type`='18' WHERE (`criteria_id`='7317') AND (`type`='11');

UPDATE `creature_template` SET `ScriptName` = 'boss_nadox', `AIName`='' WHERE `entry` = 29309;

UPDATE `creature_template` SET `AIName`='',`ScriptName`='mob_nadox_guardian' WHERE (`entry`='30176');
DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 30176;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 30176;

UPDATE `creature_template` SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` = 30178;
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=30178);
INSERT INTO `creature_ai_scripts` VALUES 
(3017801, 30178, 0, 0, 100, 7, 0, 500, 25000, 40000, 11, 56354, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 'Ahn kahar Swarmer - Cast Sprint');

UPDATE `creature_template` SET `ScriptName` = '', `AIName`='' WHERE `entry` = 30172;
UPDATE `creature_template` SET `ScriptName` = '', `AIName`='' WHERE `entry` = 30173;




-- --------------- OLD STUFF ----------------------------------------------------------------------- 


UPDATE `instance_template` SET `ScriptName` = 'instance_ahnkahet' WHERE `map`=619;
UPDATE `creature_template` SET `ScriptName` = 'boss_jedoga', `AIName`='' WHERE `entry`=29310;

UPDATE `creature_template` SET `ScriptName` = 'boss_taldaram', `AIName`='' WHERE `entry`=29308;
UPDATE `creature_template` SET `ScriptName` = 'mob_flame_orb', `AIName`='' WHERE `entry`=30702;
UPDATE `gameobject_template` SET `ScriptName` = 'go_nerubian_device' WHERE `entry` IN (193093,193094);
UPDATE `creature_template` SET `ScriptName` = 'boss_volazj', `AIName`='' WHERE `entry`=29311;
UPDATE `creature_template` SET `ScriptName` = 'mob_twisted_visage' WHERE `entry` = 30621;
UPDATE `creature_template` SET `ScriptName` = 'mob_ancient_void' WHERE `entry` = 30622;
UPDATE `creature_template` SET `ScriptName` = 'npc_twilight_volunteer', `AIName`='' WHERE `entry`=30385;

DELETE FROM `creature_template_addon` WHERE `entry` IN (30385, 31474);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES
(30385, 0, 8, 1, 0, 0, 0, '');
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES
(31474, 0, 8, 1, 0, 0, 0, '');

UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (30114,31473);

DELETE FROM `creature_addon` WHERE guid=131953;
DELETE FROM `creature` WHERE guid IN (131953, 115064);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(131953, 29310, 619, 3, 1, 26777, 0, 357.353, -692.808, -10.7028, 5.56541, 14400, 5, 0, 212700, 0, 0, 1);

DELETE FROM `gameobject` WHERE `guid` = 911321;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(911321, 194394, 619, 2, 1, 371.842, -701.621, -16.1797, 5.67851, 0, 0, 0.297751, -0.954644, -10, 0, 1);

UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` IN (30258, 30391, 30435);
UPDATE `creature_template` SET `ScriptName` ='npc_amanitar_mushroom', `AIName`='' WHERE `entry` IN (30391, 30435);
UPDATE `creature_template` SET `ScriptName` ='boss_amanitar', `AIName`='', `mindmg` = 488, `maxdmg` = 648, `attackpower` = 782, `dmg_multiplier` = 13  WHERE `entry` = 30258;

-- -
-- Mushrooms
-- -

DELETE FROM `creature` WHERE `map` = 619 AND `id` IN (30391);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(600047, 30391, 619, 2, 1, 0, 0, 358.386, -885.553, -76.1054, 3.06235, 30, 0, 0, 1, 0, 0, 0),
(600048, 30391, 619, 2, 1, 0, 0, 355.893, -871.712, -76.1473, 2.37356, 30, 0, 0, 1, 0, 0, 0),
(600049, 30391, 619, 2, 1, 0, 0, 350.343, -874.985, -76.7057, 3.40793, 30, 0, 0, 1, 0, 0, 0),
(600050, 30391, 619, 2, 1, 0, 0, 339.429, -875.16, -75.6668, 2.76233, 30, 0, 0, 1, 0, 0, 0),
(600051, 30391, 619, 2, 1, 0, 0, 333.095, -874.652, -73.8099, 3.95457, 30, 0, 0, 1, 0, 0, 0),
(600052, 30391, 619, 2, 1, 0, 0, 324.208, -878.923, -70.915, 3.95457, 30, 0, 0, 1, 0, 0, 0),
(600053, 30391, 619, 2, 1, 0, 0, 319.612, -893.614, -66.4438, 6.25892, 30, 0, 0, 1, 0, 0, 0),
(600054, 30391, 619, 2, 1, 0, 0, 335.775, -899.115, -76.1423, 0.282045, 30, 0, 0, 1, 0, 0, 0),
(600055, 30391, 619, 2, 1, 0, 0, 344.644, -898.122, -77.6435, 0.282045, 30, 0, 0, 1, 0, 0, 0),
(600056, 30391, 619, 2, 1, 0, 0, 353.341, -894.159, -77.208, 0.282045, 30, 0, 0, 1, 0, 0, 0),
(600057, 30391, 619, 2, 1, 0, 0, 363.279, -897.252, -79.5129, 0.282045, 30, 0, 0, 1, 0, 0, 0),
(600058, 30391, 619, 2, 1, 0, 0, 364.47, -903.557, -80.3345, 4.7651, 30, 0, 0, 1, 0, 0, 0),
(600059, 30391, 619, 2, 1, 0, 0, 366.219, -915.939, -82.5392, 5.04784, 30, 0, 0, 1, 0, 0, 0),
(600060, 30391, 619, 2, 1, 0, 0, 368.297, -920.562, -82.5588, 5.59919, 30, 0, 0, 1, 0, 0, 0),
(600061, 30391, 619, 2, 1, 0, 0, 381.647, -923.685, -82.4737, 0.190153, 30, 0, 0, 1, 0, 0, 0),
(600062, 30391, 619, 2, 1, 0, 0, 389.079, -916.929, -81.4451, 1.40831, 30, 0, 0, 1, 0, 0, 0),
(600063, 30391, 619, 2, 1, 0, 0, 386.916, -909.718, -79.9835, 1.40831, 30, 0, 0, 1, 0, 0, 0),
(600064, 30391, 619, 2, 1, 0, 0, 386.976, -898.374, -79.2561, 2.5652, 30, 0, 0, 1, 0, 0, 0),
(600065, 30391, 619, 2, 1, 0, 0, 390.349, -882.168, -76.0919, 1.56146, 30, 0, 0, 1, 0, 0, 0),
(600066, 30391, 619, 2, 1, 0, 0, 387.136, -871.625, -75.4158, 2.15051, 30, 0, 0, 1, 0, 0, 0),
(600067, 30391, 619, 2, 1, 0, 0, 378.056, -864.542, -73.8699, 3.01759, 30, 0, 0, 1, 0, 0, 0),
(600068, 30391, 619, 2, 1, 0, 0, 363.749, -858.04, -75.1185, 3.01759, 30, 0, 0, 1, 0, 0, 0),
(600069, 30391, 619, 2, 1, 0, 0, 352.564, -862.387, -74.7834, 3.01759, 30, 0, 0, 1, 0, 0, 0),
(600070, 30391, 619, 2, 1, 0, 0, 343.924, -860.44, -74.5909, 2.23533, 30, 0, 0, 1, 0, 0, 0),
(600071, 30391, 619, 2, 1, 0, 0, 339.94, -852.104, -74.3732, 0.995972, 30, 0, 0, 1, 0, 0, 0),
(600072, 30391, 619, 2, 1, 0, 0, 347.839, -848.228, -73.7097, 6.23065, 30, 0, 0, 1, 0, 0, 0),
(600073, 30391, 619, 2, 1, 0, 0, 324.306, -858.725, -75.0947, 3.68596, 30, 0, 0, 1, 0, 0, 0),
(600074, 30391, 619, 2, 1, 0, 0, 347.971, -882.318, -75.884, 3.55872, 30, 0, 0, 1, 0, 0, 0),
(600075, 30391, 619, 2, 1, 0, 0, 347.965, -889.829, -76.747, 3.55872, 30, 0, 0, 1, 0, 0, 0),
(600076, 30391, 619, 2, 1, 0, 0, 368.578, -877.354, -75.676, 1.46878, 30, 0, 0, 1, 0, 0, 0),
(600077, 30391, 619, 2, 1, 0, 0, 378.003, -852.353, -73.5427, 0.519235, 30, 0, 0, 1, 0, 0, 0),
(600078, 30391, 619, 2, 1, 0, 0, 361.828, -841.2, -70.86, 2.94298, 30, 0, 0, 1, 0, 0, 0),
(600079, 30391, 619, 2, 1, 0, 0, 346.972, -839.523, -73.5286, 2.94298, 30, 0, 0, 1, 0, 0, 0),
(600080, 30391, 619, 2, 1, 0, 0, 337.009, -843.074, -74.3865, 2.94298, 30, 0, 0, 1, 0, 0, 0),
(600081, 30391, 619, 2, 1, 0, 0, 330.036, -847.017, -74.318, 3.25321, 30, 0, 0, 1, 0, 0, 0),
(600082, 30391, 619, 2, 1, 0, 0, 328.839, -838.69, -72.921, 1.8929, 30, 0, 0, 1, 0, 0, 0),
(600083, 30391, 619, 2, 1, 0, 0, 322.452, -829.799, -73.5624, 2.6563, 30, 0, 0, 1, 0, 0, 0),
(600084, 30391, 619, 2, 1, 0, 0, 316.367, -822.016, -73.1033, 1.71618, 30, 0, 0, 1, 0, 0, 0),
(600085, 30391, 619, 2, 1, 0, 0, 320.592, -812.011, -73.8038, 0.957487, 30, 0, 0, 1, 0, 0, 0),
(600086, 30391, 619, 2, 1, 0, 0, 322.619, -803.898, -72.9384, 2.07668, 30, 0, 0, 1, 0, 0, 0),
(600087, 30391, 619, 2, 1, 0, 0, 331.481, -811.702, -72.9227, 5.46332, 30, 0, 0, 1, 0, 0, 0),
(600088, 30391, 619, 2, 1, 0, 0, 341.894, -826.849, -73.049, 5.46332, 30, 0, 0, 1, 0, 0, 0),
(600089, 30391, 619, 2, 1, 0, 0, 387.58, -856.341, -71.0935, 5.72486, 30, 0, 0, 1, 0, 0, 0),
(600090, 30391, 619, 2, 1, 0, 0, 401.977, -867.49, -73.3215, 5.27247, 30, 0, 0, 1, 0, 0, 0),
(600091, 30391, 619, 2, 1, 0, 0, 408.72, -872.115, -73.0256, 6.03823, 30, 0, 0, 1, 0, 0, 0),
(600092, 30391, 619, 2, 1, 0, 0, 416.438, -875.336, -70.4833, 5.08397, 30, 0, 0, 1, 0, 0, 0),
(600093, 30391, 619, 2, 1, 0, 0, 403.004, -895.527, -75.561, 5.60391, 30, 0, 0, 1, 0, 0, 0),
(600094, 30391, 619, 2, 1, 0, 0, 409.35, -902.562, -77.2837, 5.22927, 30, 0, 0, 1, 0, 0, 0),
(600095, 30391, 619, 2, 1, 0, 0, 414.538, -911.69, -79.8006, 5.22927, 30, 0, 0, 1, 0, 0, 0),
(600096, 30391, 619, 2, 1, 0, 0, 419.727, -920.818, -80.7403, 5.22927, 30, 0, 0, 1, 0, 0, 0),
(600097, 30391, 619, 2, 1, 0, 0, 428.151, -920.833, -79.0992, 0.892305, 30, 0, 0, 1, 0, 0, 0),
(600098, 30391, 619, 2, 1, 0, 0, 436.712, -911.759, -78.8367, 0.0605679, 30, 0, 0, 1, 0, 0, 0),
(600099, 30391, 619, 2, 1, 0, 0, 461.167, -910.276, -77.4777, 0.0605679, 30, 0, 0, 1, 0, 0, 0),
(600100, 30391, 619, 2, 1, 0, 0, 419.827, -930.386, -77.7951, 4.29465, 30, 0, 0, 1, 0, 0, 0),
(600101, 30391, 619, 2, 1, 0, 0, 418.017, -939.624, -80.2493, 4.29465, 30, 0, 0, 1, 0, 0, 0),
(600102, 30391, 619, 2, 1, 0, 0, 417.247, -948.532, -79.3315, 4.29465, 30, 0, 0, 1, 0, 0, 0),
(600103, 30391, 619, 2, 1, 0, 0, 409.236, -952.042, -80.6495, 4.29465, 30, 0, 0, 1, 0, 0, 0),
(600104, 30391, 619, 2, 1, 0, 0, 410.077, -959.059, -78.9977, 4.29465, 30, 0, 0, 1, 0, 0, 0),
(600105, 30391, 619, 2, 1, 0, 0, 403.871, -964.208, -77.8873, 4.29465, 30, 0, 0, 1, 0, 0, 0),
(600106, 30391, 619, 2, 1, 0, 0, 401.693, -970.428, -77.3012, 4.90255, 30, 0, 0, 1, 0, 0, 0),
(600107, 30391, 619, 2, 1, 0, 0, 402.379, -980.099, -75.4585, 4.60567, 30, 0, 0, 1, 0, 0, 0),
(600108, 30391, 619, 2, 1, 0, 0, 399.272, -984.535, -75.9494, 3.15425, 30, 0, 0, 1, 0, 0, 0),
(600109, 30391, 619, 2, 1, 0, 0, 380.102, -984.145, -74.2926, 2.13402, 30, 0, 0, 1, 0, 0, 0),
(600110, 30391, 619, 2, 1, 0, 0, 369.565, -973.481, -77.4914, 2.56756, 30, 0, 0, 1, 0, 0, 0),
(600111, 30391, 619, 2, 1, 0, 0, 360.748, -967.779, -79.832, 2.56756, 30, 0, 0, 1, 0, 0, 0),
(600112, 30391, 619, 2, 1, 0, 0, 350.138, -958.988, -79.4422, 2.16229, 30, 0, 0, 1, 0, 0, 0),
(600113, 30391, 619, 2, 1, 0, 0, 342.879, -944.352, -79.8533, 1.64157, 30, 0, 0, 1, 0, 0, 0);

UPDATE `creature_template` SET `minhealth` = 1 WHERE `entry` = 30391;
UPDATE `creature_template` SET `minmana` = 0 WHERE `entry` = 29310;
