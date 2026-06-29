DROP TABLE IF EXISTS `mod_exp_rate_tuner_character_settings`;
CREATE TABLE `mod_exp_rate_tuner_character_settings` (
	`guid` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
	`exprate` INT(10) UNSIGNED NOT NULL DEFAULT '100',
	PRIMARY KEY (`guid`) USING BTREE
);