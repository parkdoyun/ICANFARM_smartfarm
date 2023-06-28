-- MariaDB dump 10.17  Distrib 10.5.5-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: farmData
-- ------------------------------------------------------
-- Server version	10.5.5-MariaDB-1:10.5.5+maria~focal

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `farmData`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `farmData` /*!40100 DEFAULT CHARACTER SET utf8mb4 */;

USE `farmData`;

--
-- Table structure for table `hibernate_sequence`
--

DROP TABLE IF EXISTS `hibernate_sequence`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hibernate_sequence` (
  `next_not_cached_value` bigint(21) NOT NULL,
  `minimum_value` bigint(21) NOT NULL,
  `maximum_value` bigint(21) NOT NULL,
  `start_value` bigint(21) NOT NULL COMMENT 'start value when sequences is created or value if RESTART is used',
  `increment` bigint(21) NOT NULL COMMENT 'increment value',
  `cache_size` bigint(21) unsigned NOT NULL,
  `cycle_option` tinyint(1) unsigned NOT NULL COMMENT '0 if no cycles are allowed, 1 if the sequence should begin a new cycle when maximum_value is passed',
  `cycle_count` bigint(21) NOT NULL COMMENT 'How many cycles have been done'
) ENGINE=InnoDB SEQUENCE=1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hibernate_sequence`
--

LOCK TABLES `hibernate_sequence` WRITE;
/*!40000 ALTER TABLE `hibernate_sequence` DISABLE KEYS */;
INSERT INTO `hibernate_sequence` VALUES (1001,1,9223372036854775806,1,1,1000,0,0);
/*!40000 ALTER TABLE `hibernate_sequence` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hub`
--

DROP TABLE IF EXISTS `hub`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hub` (
  `id` bigint(20) NOT NULL,
  `default_hub` bit(1) DEFAULT b'0',
  `humid_rate` double DEFAULT 0,
  `humid_setting` double DEFAULT 0,
  `is_co2` bit(1) DEFAULT b'0',
  `is_fan` bit(1) DEFAULT b'0',
  `is_humid` bit(1) DEFAULT b'0',
  `is_light` bit(1) DEFAULT b'0',
  `is_temp` bit(1) DEFAULT b'0',
  `join_date` datetime(6) DEFAULT NULL,
  `light_turn_off` datetime(6) DEFAULT '2000-01-01 00:00:00.000000',
  `light_turn_on` datetime(6) DEFAULT '2000-01-01 00:00:00.000000',
  `nickname` varchar(255) DEFAULT NULL,
  `serial` varchar(255) NOT NULL,
  `temp_rate` double DEFAULT 0,
  `temp_setting` double DEFAULT 0,
  `member_id` bigint(20) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `UK_j0finrd70103s6dopee60e3au` (`serial`),
  KEY `FKms5g2vi7drkxiegbim5onalyq` (`member_id`),
  CONSTRAINT `FKms5g2vi7drkxiegbim5onalyq` FOREIGN KEY (`member_id`) REFERENCES `member` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hub`
--

LOCK TABLES `hub` WRITE;
/*!40000 ALTER TABLE `hub` DISABLE KEYS */;
INSERT INTO `hub` VALUES (1,'',5,55,'','','','','\0','2023-05-18 11:05:01.269259','2023-05-18 20:00:00.000000','2023-05-18 05:00:00.000000','hub1','f_pjt',5,23,2),(3,'',0,69,'','','','','\0','2023-05-18 11:19:18.982490','2023-05-18 12:00:00.000000','2023-05-18 03:00:00.000000','hub1','test',5,38,6);
/*!40000 ALTER TABLE `hub` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `member`
--

DROP TABLE IF EXISTS `member`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `member` (
  `id` bigint(20) NOT NULL,
  `email` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `passwd` varchar(255) DEFAULT NULL,
  `role` varchar(255) DEFAULT 'ROLE_USER',
  `rpi_pw` varchar(255) DEFAULT '000000',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `member`
--

LOCK TABLES `member` WRITE;
/*!40000 ALTER TABLE `member` DISABLE KEYS */;
INSERT INTO `member` VALUES (2,'aaa@naver.com','aaa','$2a$10$LRZBRZdU/07P9bGjbhw1huv1dIvK6kTsgfaLj.P6c7YDTex1z66ca','ROLE_USER','000000'),(4,'stella@naver.com','선민영','$2a$10$XkWXt/XAWB0MuT4Q72Q8Xe6TUfirNePCrpeOgdK1.W4SZYM8UO9Tu','ROLE_USER','135790'),(5,'stella11@naver.com','SSun','$2a$10$PEtzXDl5UW4ZCRGWh190K.9t5yVj75/mMlE5N/oOOwO.8QFeawxL6','ROLE_USER','000000'),(6,'stella22@naver.com','SSun','$2a$10$IkWd3YOSIWJY5xLHsJ.qEurFK1PXboaIHnPquMl7WxjJ8RO4S3f56','ROLE_USER','135790');
/*!40000 ALTER TABLE `member` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-05-19  3:49:17
