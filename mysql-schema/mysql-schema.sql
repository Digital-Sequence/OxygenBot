--
-- Current Database: `bot`
--

CREATE DATABASE `bot`;
USE `bot`;

--
-- Table structure for table `BANS`
--

DROP TABLE IF EXISTS `BANS`;
CREATE TABLE `BANS` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `IS_BAN` bit(1) DEFAULT NULL,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `USERNAME` text DEFAULT NULL,
  `DATE` bigint(20) unsigned NOT NULL,
  `EXPIRES` bigint(20) unsigned DEFAULT NULL,
  `CANCELLED` bit(1) DEFAULT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `MESSAGES`
--

DROP TABLE IF EXISTS `MESSAGES`;
CREATE TABLE `MESSAGES` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `CHANNEL_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `MESSAGE_ID` bigint(20) unsigned NOT NULL,
  `DELETED` bit(1) DEFAULT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `MUTES`
--

DROP TABLE IF EXISTS `MUTES`;
CREATE TABLE `MUTES` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `IS_MUTE` bit(1) DEFAULT NULL,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `EXPIRES` bigint(20) unsigned DEFAULT NULL,
  `DATE` bigint(20) unsigned NOT NULL,
  `CANCELLED` bit(1) DEFAULT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `ROLES`
--

DROP TABLE IF EXISTS `ROLES`;
CREATE TABLE `ROLES` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `ROLE_ID` bigint(20) unsigned NOT NULL,
  `NAME` text DEFAULT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `WARNS`
--

DROP TABLE IF EXISTS `WARNS`;
CREATE TABLE `WARNS` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `COUNT` int(10) unsigned NOT NULL,
  `EXPIRES` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;