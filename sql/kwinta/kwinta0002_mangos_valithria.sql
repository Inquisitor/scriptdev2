update creature_template set modelid_1=30844, ScriptName='' where entry=38429;
update creature_template_addon set auras=71986 where entry=38429;
insert into creature_template_addon VALUES (38421, 0, 0, 0, 0, 0, 0, 71939);
Update creature_template set faction_A=14, faction_H=14 where entry=38421;
Update creature_template set faction_A=14, faction_H=14 where entry=37985;
Update creature_template SET ScriptName="mob_dream_portal" where entry=38186;
Update creature_template SET ScriptName="mob_gluttonous_abomination" where entry=37886; 
Update creature_template SET ScriptName="mob_nightmare_portal" where entry=38429;
Update creature_template SET ScriptName="mob_nightmare_cloud" where entry=38421; 
Update creature_template SET ScriptName="mob_dream_cloud" where entry=37985; 
Update creature_template SET ScriptName="mob_blistering_zombie" where entry=37934; 
Update creature_template SET ScriptName="mob_blazing_skeleton" where entry=36791;
Update creature_template SET ScriptName="mob_suppresser" where entry=37863;
Update creature_template SET ScriptName="mob_valitria_in_portal" where entry=37950;
Update creature_template SET ScriptName="mob_portal_pre" where entry in (37945, 38430);  
Update creature_template SET ScriptName="mob_column_of_frost" where entry = 37918;
Update creature_template SET ScriptName="mob_mana_void" where entry = 38068;
Update creature_template SET ScriptName="mob_risen_archmage" where entry = 37868;
Update creature_template SET unit_flags=33554436 where entry=38429;
Update creature_template SET unit_flags=33554436 where entry=38186;
Update creature_template set MovementType=1 where entry=38421;
Update creature_template set flags_extra=2 where entry in (38430, 37945);
Update creature_template set InhabitType=5 where entry in (37985, 38421);
Update creature_template Set IconName="vehichleCursor",  npcflag=1 where entry in (37945, 38430);
