UPDATE `creature_template` SET `minhealth` = 20066450, `maxhealth` = 20066450 WHERE `entry` = 38490;
SET @RAID_DIFFICULTY_10MAN_NORMAL = 0;
SET @RAID_DIFFICULTY_25MAN_NORMAL = 1;
SET @RAID_DIFFICULTY_10MAN_HEROIC = 2;
SET @RAID_DIFFICULTY_25MAN_HEROIC = 3;
SET @SPAWNMASK_RAID_10MAN_NORMAL = (1 << @RAID_DIFFICULTY_10MAN_NORMAL);
SET @SPAWNMASK_RAID_25MAN_NORMAL = (1 << @RAID_DIFFICULTY_25MAN_NORMAL);
SET @SPAWNMASK_RAID_10MAN_HEROIC = (1 << @RAID_DIFFICULTY_10MAN_HEROIC);
SET @SPAWNMASK_RAID_25MAN_HEROIC = (1 << @RAID_DIFFICULTY_25MAN_HEROIC);
SET @GO_GUNSHIP_ARMORY_A_10      = 201872;
SET @GO_GUNSHIP_ARMORY_A_25      = 201873;
SET @GO_GUNSHIP_ARMORY_A_10H     = 201874;
SET @GO_GUNSHIP_ARMORY_A_25H     = 201875;
SET @GO_GUNSHIP_ARMORY_H_10      = 202177;
SET @GO_GUNSHIP_ARMORY_H_25      = 202178;
SET @GO_GUNSHIP_ARMORY_H_10H     = 202179;
SET @GO_GUNSHIP_ARMORY_H_25H     = 202180;
SET @GO_GUID_START = 542000;
SET @POS_MAP = 631;
SET @POS_H_X = -437.67;  SET @POS_H_Y = 1995.77; SET @POS_H_Z = 191.235;   SET @POS_H_O = 1.54094;
SET @POS_H_R0 = 0;       SET @POS_H_R1 = 0;      SET @POS_H_R2 = 0.696473; SET @POS_H_R3 = 0.717583;
SET @POS_A_X = -436.984; SET @POS_A_Y = 2429.68; SET @POS_A_Z = 191.233;   SET @POS_A_O = 4.61969;
SET @POS_A_R0 = 0;       SET @POS_A_R1 = 0;      SET @POS_A_R2 = 0.739109; SET @POS_A_R3 = -0.673586;
SET @PHASE_MASK = 1;     SET @STATE = 1;         SET @ANIM_PROGRESS = 100; SET @SPAWN_TIME_SECS = -604800;

DELETE FROM `gameobject` WHERE `guid` BETWEEN @GO_GUID_START AND @GO_GUID_START + 7;
INSERT INTO gameobject (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
 (@GO_GUID_START + 0, @GO_GUNSHIP_ARMORY_H_10,  @POS_MAP, @SPAWNMASK_RAID_10MAN_NORMAL, @PHASE_MASK, @POS_H_X, @POS_H_Y, @POS_H_Z, @POS_H_O, @POS_H_R0, @POS_H_R1, @POS_H_R2, @POS_H_R3, @SPAWN_TIME_SECS, @ANIM_PROGRESS, @STATE)
,(@GO_GUID_START + 1, @GO_GUNSHIP_ARMORY_H_10H, @POS_MAP, @SPAWNMASK_RAID_10MAN_HEROIC, @PHASE_MASK, @POS_H_X, @POS_H_Y, @POS_H_Z, @POS_H_O, @POS_H_R0, @POS_H_R1, @POS_H_R2, @POS_H_R3, @SPAWN_TIME_SECS, @ANIM_PROGRESS, @STATE)
,(@GO_GUID_START + 2, @GO_GUNSHIP_ARMORY_H_25,  @POS_MAP, @SPAWNMASK_RAID_25MAN_NORMAL, @PHASE_MASK, @POS_H_X, @POS_H_Y, @POS_H_Z, @POS_H_O, @POS_H_R0, @POS_H_R1, @POS_H_R2, @POS_H_R3, @SPAWN_TIME_SECS, @ANIM_PROGRESS, @STATE)
,(@GO_GUID_START + 3, @GO_GUNSHIP_ARMORY_H_25H, @POS_MAP, @SPAWNMASK_RAID_25MAN_HEROIC, @PHASE_MASK, @POS_H_X, @POS_H_Y, @POS_H_Z, @POS_H_O, @POS_H_R0, @POS_H_R1, @POS_H_R2, @POS_H_R3, @SPAWN_TIME_SECS, @ANIM_PROGRESS, @STATE)
,(@GO_GUID_START + 4, @GO_GUNSHIP_ARMORY_A_10,  @POS_MAP, @SPAWNMASK_RAID_10MAN_NORMAL, @PHASE_MASK, @POS_A_X, @POS_A_Y, @POS_A_Z, @POS_A_O, @POS_A_R0, @POS_A_R1, @POS_A_R2, @POS_A_R3, @SPAWN_TIME_SECS, @ANIM_PROGRESS, @STATE)
,(@GO_GUID_START + 5, @GO_GUNSHIP_ARMORY_A_10H, @POS_MAP, @SPAWNMASK_RAID_10MAN_HEROIC, @PHASE_MASK, @POS_A_X, @POS_A_Y, @POS_A_Z, @POS_A_O, @POS_A_R0, @POS_A_R1, @POS_A_R2, @POS_A_R3, @SPAWN_TIME_SECS, @ANIM_PROGRESS, @STATE)
,(@GO_GUID_START + 6, @GO_GUNSHIP_ARMORY_A_25,  @POS_MAP, @SPAWNMASK_RAID_25MAN_NORMAL, @PHASE_MASK, @POS_A_X, @POS_A_Y, @POS_A_Z, @POS_A_O, @POS_A_R0, @POS_A_R1, @POS_A_R2, @POS_A_R3, @SPAWN_TIME_SECS, @ANIM_PROGRESS, @STATE)
,(@GO_GUID_START + 7, @GO_GUNSHIP_ARMORY_A_25H, @POS_MAP, @SPAWNMASK_RAID_25MAN_HEROIC, @PHASE_MASK, @POS_A_X, @POS_A_Y, @POS_A_Z, @POS_A_O, @POS_A_R0, @POS_A_R1, @POS_A_R2, @POS_A_R3, @SPAWN_TIME_SECS, @ANIM_PROGRESS, @STATE)

;