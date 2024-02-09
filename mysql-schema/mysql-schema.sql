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
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `USERNAME` text DEFAULT NULL,
  `DATE` bigint(20) unsigned NOT NULL,
  `EXPIRES` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`GUILD_ID`,`USER_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `BANS_CANCELLED`
--

DROP TABLE IF EXISTS `BANS_CANCELLED`;
CREATE TABLE `BANS_CANCELLED` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `USERNAME` text NOT NULL,
  `DATE` bigint(20) unsigned NOT NULL,
  `CANCELLED` bigint(20) unsigned NOT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `MESSAGES`
--

DROP TABLE IF EXISTS `MESSAGES`;
CREATE TABLE `MESSAGES` (
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `CHANNEL_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `MESSAGE_ID` bigint(20) unsigned NOT NULL,
  `DELETED` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`GUILD_ID`,`CHANNEL_ID`,`USER_ID`,`MESSAGE_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `MUTES`
--

DROP TABLE IF EXISTS `MUTES`;
CREATE TABLE `MUTES` (
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `DATE` bigint(20) unsigned NOT NULL,
  `EXPIRES` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`GUILD_ID`,`USER_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `MUTES_CANCELLED`
--

DROP TABLE IF EXISTS `MUTES_CANCELLED`;
CREATE TABLE `MUTES_CANCELLED` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `DATE` bigint(20) unsigned NOT NULL,
  `CANCELLED` bigint(20) unsigned NOT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `PREFERENCES`
--

DROP TABLE IF EXISTS `PREFERENCES`;
CREATE TABLE `PREFERENCES` (
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `MAX_WARNS` tinyint(4) unsigned NOT NULL,
  `WARN_PUNISHMENT` text NOT NULL,
  PRIMARY KEY (`MAX_WARNS`,`GUILD_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `ROLES`
--

DROP TABLE IF EXISTS `ROLES`;
CREATE TABLE `ROLES` (
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `ROLE_ID` bigint(20) unsigned NOT NULL,
  `NAME` text DEFAULT NULL,
  PRIMARY KEY (`GUILD_ID`,`ROLE_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `WARNS`
--

DROP TABLE IF EXISTS `WARNS`;
CREATE TABLE `WARNS` (
  `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `GUILD_ID` bigint(20) unsigned NOT NULL,
  `USER_ID` bigint(20) unsigned NOT NULL,
  `COUNT` tinyint(3) unsigned NOT NULL,
  `EXPIRES` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`rowid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;