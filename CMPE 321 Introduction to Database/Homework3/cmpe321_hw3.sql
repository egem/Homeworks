-- phpMyAdmin SQL Dump
-- version 4.6.5.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: May 15, 2017 at 09:53 ÖS
-- Server version: 10.1.21-MariaDB
-- PHP Version: 5.6.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cmpe321_hw3`
--

DELIMITER $$
--
-- Procedures
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `list_available_doctors` (IN `appointmentDate` DATE, IN `timeSlotID` INT, IN `branchID` INT)  NO SQL
SELECT 	Doctors.ID AS doctorID,
		Doctors.name as doctorName, 
		Doctors.surname as doctorSurname
        FROM Doctors
        WHERE Doctors.branchID = branchID AND NOT EXISTS
        (SELECT Appointments.doctorID
         FROM Appointments
         WHERE Appointments.date = appointmentDate AND
         Appointments.timeSlotID = timeSlotID AND
         Appointments.doctorID = Doctors.ID)$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `list_future_appointments` (IN `branchName` VARCHAR(70))  NO SQL
IF branchName LIKE "ALL" THEN
SELECT Doctors.name as doctorName, 
		Doctors.surname as doctorSurname,  
        Branches.ID AS branchID, 
        Doctors.ID AS doctorID,
       	Branches.name as branchName, 
        Appointments.date as appointmentDate, 
        TimeSlots.startTime as appointmentStartTime, 
        TimeSlots.endTime as appointmentEndTime,
        Appointments.timeSlotID as timeSlotID,
        Patients.ID as patientID,
        Patients.username as patientUsername,
        Patients.name as patientName,
        Patients.surname as patientSurname
          FROM ((((Appointments
          LEFT JOIN TimeSlots ON Appointments.timeSlotID=TimeSlots.ID)
          LEFT JOIN Doctors ON Appointments.doctorID = Doctors.ID)
          LEFT JOIN Branches ON Doctors.branchID=Branches.ID)
          LEFT JOIN Patients ON Appointments.patientID = Patients.ID)
          	WHERE 
                Appointments.date > CURRENT_DATE OR
                (Appointments.date = CURRENT_DATE AND
                CAST(TimeSlots.endTime As Time) > CURRENT_TIME);
ELSE
SELECT Doctors.name as doctorName, 
		Doctors.surname as doctorSurname,  
        Branches.ID AS branchID, 
        Doctors.ID AS doctorID,
       	Branches.name as branchName, 
        Appointments.date as appointmentDate, 
        TimeSlots.startTime as appointmentStartTime, 
        TimeSlots.endTime as appointmentEndTime,
        Appointments.timeSlotID as timeSlotID,
        Patients.ID as patientID,
        Patients.username as patientUsername,
        Patients.name as patientName,
        Patients.surname as patientSurname
          FROM ((((Appointments
          LEFT JOIN TimeSlots ON Appointments.timeSlotID=TimeSlots.ID)
          LEFT JOIN Doctors ON Appointments.doctorID = Doctors.ID)
          LEFT JOIN Branches ON Doctors.branchID=Branches.ID)
          LEFT JOIN Patients ON Appointments.patientID = Patients.ID)
          	WHERE 
          		Branches.name LIKE branchName AND
                Appointments.date > CURRENT_DATE OR
                (Appointments.date = CURRENT_DATE AND
                 CAST(TimeSlots.endTime As Time) > CURRENT_TIME);
END IF$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `list_past_appointments` (IN `branchName` VARCHAR(70))  NO SQL
IF branchName LIKE "All" THEN
SELECT Doctors.name as doctorName, 
		Doctors.surname as doctorSurname,  
        Branches.ID AS branchID, 
        Doctors.ID AS doctorID,
       	Branches.name as branchName, 
        Appointments.date as appointmentDate, 
        TimeSlots.startTime as appointmentStartTime, 
        TimeSlots.endTime as appointmentEndTime,
        Appointments.timeSlotID as timeSlotID,
        Patients.ID as patientID,
        Patients.username as patientUsername,
        Patients.name as patientName,
        Patients.surname as patientSurname
          FROM ((((Appointments
          LEFT JOIN TimeSlots ON Appointments.timeSlotID=TimeSlots.ID)
          LEFT JOIN Doctors ON Appointments.doctorID = Doctors.ID)
          LEFT JOIN Branches ON Doctors.branchID=Branches.ID)
          LEFT JOIN Patients ON Appointments.patientID = Patients.ID)
          	WHERE 
                Appointments.date < CURRENT_DATE OR
                (Appointments.date = CURRENT_DATE AND
                CAST(TimeSlots.endTime As Time) <= CURRENT_TIME);
ELSE
SELECT Doctors.name as doctorName, 
		Doctors.surname as doctorSurname,  
        Branches.ID AS branchID, 
        Doctors.ID AS doctorID,
       	Branches.name as branchName, 
        Appointments.date as appointmentDate, 
        TimeSlots.startTime as appointmentStartTime, 
        TimeSlots.endTime as appointmentEndTime,
        Appointments.timeSlotID as timeSlotID,
        Patients.ID as patientID,
        Patients.username as patientUsername,
        Patients.name as patientName,
        Patients.surname as patientSurname
          FROM ((((Appointments
          LEFT JOIN TimeSlots ON Appointments.timeSlotID=TimeSlots.ID)
          LEFT JOIN Doctors ON Appointments.doctorID = Doctors.ID)
          LEFT JOIN Branches ON Doctors.branchID=Branches.ID)
          LEFT JOIN Patients ON Appointments.patientID = Patients.ID)
          	WHERE 
          		Branches.name LIKE branchName AND
                Appointments.date < CURRENT_DATE OR
                (Appointments.date = CURRENT_DATE AND
                 CAST(TimeSlots.endTime As Time) <= CURRENT_TIME);
END IF$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `show_all_patients` ()  NO SQL
SELECT * FROM Patients$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `show_user_appointments_info` (IN `userID` INT)  SELECT Doctors.name as doctorName, 
		Doctors.surname as doctorSurname,  
        Branches.ID AS branchID, 
        Doctors.ID AS doctorID,
       	Branches.name as branchName, 
        Appointments.date as appointmentDate, 
        TimeSlots.startTime as appointmentStartTime, 
        TimeSlots.endTime as appointmentEndTime,
        Appointments.timeSlotID as timeSlotID
          FROM (((Appointments
          LEFT JOIN TimeSlots ON Appointments.timeSlotID=TimeSlots.ID)
          LEFT JOIN Doctors ON Appointments.doctorID = Doctors.ID)
          LEFT JOIN Branches ON Doctors.branchID=Branches.ID)
          WHERE Appointments.patientID=userID$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_test` ()  BEGIN
  SELECT 'Number of records: ', count(*) from Patients;
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `Admins`
--

CREATE TABLE `Admins` (
  `ID` int(11) NOT NULL,
  `username` varchar(30) NOT NULL,
  `name` varchar(30) NOT NULL,
  `surname` varchar(30) NOT NULL,
  `password` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Admins`
--

INSERT INTO `Admins` (`ID`, `username`, `name`, `surname`, `password`) VALUES
(1, 'root', 'Albert', 'Einstein', '1234');

-- --------------------------------------------------------

--
-- Table structure for table `Appointments`
--

CREATE TABLE `Appointments` (
  `date` date NOT NULL,
  `timeSlotID` int(11) NOT NULL,
  `doctorID` int(11) NOT NULL,
  `patientID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Appointments`
--

INSERT INTO `Appointments` (`date`, `timeSlotID`, `doctorID`, `patientID`) VALUES
('2017-04-23', 3, 5, 1),
('2017-05-02', 3, 1, 3),
('2017-05-10', 2, 1, 2),
('2017-05-19', 2, 1, 1),
('2017-05-23', 3, 1, 1),
('2017-05-23', 3, 5, 1),
('2017-05-26', 3, 1, 1),
('2017-05-29', 1, 1, 1),
('2017-05-29', 1, 5, 1);

-- --------------------------------------------------------

--
-- Table structure for table `Branches`
--

CREATE TABLE `Branches` (
  `ID` int(11) NOT NULL,
  `name` varchar(70) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Branches`
--

INSERT INTO `Branches` (`ID`, `name`) VALUES
(1, 'Audiologist'),
(2, 'Allergist'),
(3, 'Anesthesiologist'),
(4, 'Cardiologist'),
(6, 'Dermatologist'),
(8, 'Epidemiologist'),
(9, 'Gynecologist'),
(10, 'Immunologist'),
(11, 'Neurologist'),
(12, 'Pediatricia'),
(13, 'p'),
(14, 'z');

--
-- Triggers `Branches`
--
DELIMITER $$
CREATE TRIGGER `delete_doctor_branch` AFTER DELETE ON `Branches` FOR EACH ROW BEGIN
  DELETE FROM Doctors WHERE Doctors.branchID = old.ID;
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `Doctors`
--

CREATE TABLE `Doctors` (
  `ID` int(11) NOT NULL,
  `name` varchar(30) NOT NULL,
  `surname` varchar(30) NOT NULL,
  `branchID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Doctors`
--

INSERT INTO `Doctors` (`ID`, `name`, `surname`, `branchID`) VALUES
(1, 'Ahmet', 'Gurcan', 13),
(5, 'marie', 'curie', 13);

--
-- Triggers `Doctors`
--
DELIMITER $$
CREATE TRIGGER `delete_doctor_appointments` AFTER DELETE ON `Doctors` FOR EACH ROW BEGIN
  DELETE FROM Appointments WHERE Appointments.doctorID = old.id;
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `Patients`
--

CREATE TABLE `Patients` (
  `ID` int(11) NOT NULL,
  `username` varchar(30) NOT NULL,
  `name` varchar(30) NOT NULL,
  `surname` varchar(30) NOT NULL,
  `password` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Patients`
--

INSERT INTO `Patients` (`ID`, `username`, `name`, `surname`, `password`) VALUES
(1, 'egem', 'Ahmet Ege', 'Mahlec', '1234'),
(2, 'aytena', 'Ayten', 'Mahlec', 'a'),
(3, 'mistik', 'Mustafa', 'Mahlec', 'm'),
(4, 'ecem', 'Ece', 'Mahlec Yilmaz', 'e'),
(5, 'hakany', 'Hakan', 'Yilmaz', 'h');

-- --------------------------------------------------------

--
-- Table structure for table `TimeSlots`
--

CREATE TABLE `TimeSlots` (
  `ID` int(11) NOT NULL,
  `startTime` time NOT NULL,
  `endTime` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `TimeSlots`
--

INSERT INTO `TimeSlots` (`ID`, `startTime`, `endTime`) VALUES
(1, '08:00:00', '08:05:00'),
(2, '08:05:00', '08:10:00'),
(3, '08:10:00', '08:15:00'),
(4, '08:15:00', '08:20:00'),
(5, '23:30:00', '23:40:00');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Admins`
--
ALTER TABLE `Admins`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `Appointments`
--
ALTER TABLE `Appointments`
  ADD PRIMARY KEY (`date`,`timeSlotID`,`doctorID`);

--
-- Indexes for table `Branches`
--
ALTER TABLE `Branches`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `Doctors`
--
ALTER TABLE `Doctors`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `Patients`
--
ALTER TABLE `Patients`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `TimeSlots`
--
ALTER TABLE `TimeSlots`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Admins`
--
ALTER TABLE `Admins`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `Branches`
--
ALTER TABLE `Branches`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;
--
-- AUTO_INCREMENT for table `Doctors`
--
ALTER TABLE `Doctors`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT for table `Patients`
--
ALTER TABLE `Patients`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT for table `TimeSlots`
--
ALTER TABLE `TimeSlots`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
