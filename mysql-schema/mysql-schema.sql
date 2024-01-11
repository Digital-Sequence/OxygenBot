--
-- bot schema
--

DROP DATABASE bot;
CREATE DATABASE bot;

--
-- Table structure for table `BANS`
--

DROP TABLE IF EXISTS `bot`.`BANS`;
CREATE TABLE `bot`.`BANS` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `USERNAME` text DEFAULT NULL,
  `EXPIRES` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `MESSAGES`
--

DROP TABLE IF EXISTS `bot`.`MESSAGES`;
CREATE TABLE `bot`.`MESSAGES` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `CHANNEL_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `MESSAGE_ID` bigint(20) unsigned NOT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `MUTES`
--

DROP TABLE IF EXISTS `bot`.`MUTES`;
CREATE TABLE `bot`.`MUTES` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `EXPIRES` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `ROLES`
--

DROP TABLE IF EXISTS `bot`.`ROLES`;
CREATE TABLE `bot`.`ROLES` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `ROLE_ID` bigint(20) unsigned NOT NULL,
  `NAME` text DEFAULT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `WARNS`
--

DROP TABLE IF EXISTS `bot`.`WARNS`;
CREATE TABLE `bot`.`WARNS` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `COUNT` int(10) unsigned NOT NULL,
  `EXPIRES` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
