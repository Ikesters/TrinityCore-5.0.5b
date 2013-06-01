#Pandaren sql, not finish,do not use (server crash)
DELETE FROM `playercreateinfo` WHERE race = 24;
INSERT INTO `playercreateinfo` VALUES
(24, 1, 860, 5736, 1471.67, 3466.25, 181.675, 0),
(24, 3, 860, 5736, 1471.67, 3466.25, 181.675, 0),
(24, 4, 860, 5736, 1471.67, 3466.25, 181.675, 0),
(24, 5, 860, 5736, 1471.67, 3466.25, 181.675, 0),
(24, 7, 860, 5736, 1471.67, 3466.25, 181.675, 0),
(24, 8, 860, 5736, 1471.67, 3466.25, 181.675, 0),
(24, 10, 860, 5736, 1471.67, 3466.25, 181.675, 0);

DELETE FROM `player_xp_for_level` WHERE `lvl` BETWEEN 85 AND 89;
INSERT INTO `player_xp_for_level` (`lvl`, `xp_for_next_level`) VALUES
(85, 16863000),
(86, 21215000),
(87, 40040000),
(88, 52034000),
(89, 91651000);