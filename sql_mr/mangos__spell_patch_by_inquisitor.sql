DELETE FROM `spell_patch` WHERE `dbc` = 'Spell.dbc' AND `entry` IN (69674, 70873);

INSERT INTO `spell_patch`(`entry`,`dbc`,`data`,`comment`) VALUES 
-- ICC
    ( '69674','Spell.dbc','86 77 87 77 88 77 89 0 90 0 91 0','Icecrown Citadel - Rotface - Mutated Infection will affect single player')
   ,( '70873','Spell.dbc','86 77 87 77 88 77 89 0 90 0 91 0','Icecrown Citadel - Valithria Dreamwalker - Emerald Vigor target correction')
   ,( '64626','Spell.dbc','92 22 93 22 94 22','Icecrown Citadel - Sindragosa - [Frost Bomb] Explosion - radius up to 200 (from 30)')
;