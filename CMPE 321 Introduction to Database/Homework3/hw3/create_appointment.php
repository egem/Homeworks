<?php
$dbServername = "localhost";
$dbUsername = "root";
$dbPassword = "";
$dbName = "cmpe321_hw3";
?>

<!DOCTYPE HTML>
<html>
<head>
  <title>Login</title>
  <link rel="stylesheet" href="login_style.css">
</head>
<body>
  <form name="DateFilter" action="create_appointment.php" method="GET">
    <input name="appointmentDate" id="meeting" type="date" value="<?php echo date('Y-m-d'); ?>"/>
    <?php
    // Create connection
    $conn = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }else{

      // List branches
      $sql = "SELECT ID, startTime, endTime FROM TimeSlots";

      $result = $conn->query($sql);
      ?>
      <select name ="timeSlotID">
      <?php
      if ($result)
      {

        // output data of each row
        while($row = $result->fetch_assoc()) {
        ?>
          <option name = "<?php echo $row["ID"];?>" value="<?php echo $row["ID"];?>"><?php echo $row["startTime"];?>/<?php echo $row["endTime"];?></option>
        <?php
        }
      }
      ?>
      </select>
      <?php

      // List branches
      $sql = "SELECT Branches.ID as branchID, Branches.name as branchName FROM Branches";

      $result = $conn->query($sql);
      ?>
      <select name ="branchID">
      <?php
      if ($result)
      {

        // output data of each row
        while($row = $result->fetch_assoc()) {
        ?>
          <option name = "<?php echo $row["branchID"];?>" value="<?php echo $row["branchID"];?>"><?php echo $row["branchName"];?></option>
        <?php
        }
      }
      ?>
      </select>
      <?php
    }
    ?>
    <br><br>
    <input type="submit" name="submit" value="Search">
    <br><br>
  </form>

  <?php

  session_start();
  if(isset($_SESSION['username']) && isset($_GET["appointmentDate"]))
  {
    $_SESSION["appointmentDate"] = $_GET["appointmentDate"];
    $_SESSION["timeSlotID"] = $_GET["timeSlotID"];
    $_SESSION["branchID"] = $_GET["branchID"];

    $conn = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }else{

      ?>
      <form name="createAppointment" action="create_appointment.php" method="GET">
        <?php

        // List branches
        $sql = "CALL list_available_doctors('" . $_GET["appointmentDate"] . "'," . $_GET["timeSlotID"] . "," . $_GET["branchID"] . ")";

        $result = $conn->query($sql);
        ?>
        <select name ="doctorID">
        <?php
        if ($result)
        {

          // output data of each row
          while($row = $result->fetch_assoc()) {
          ?>
            <option name = "<?php echo $row["doctorID"];?>" value="<?php echo $row["doctorID"];?>"><?php echo $row["doctorName"];?> <?php echo $row["doctorSurname"];?></option>
          <?php
          }
        }
        ?>
        </select>
        <br><br>
        <input type="submit" name="submit" value="Create">
      </form>
      <?php
    }

  }

  if(isset($_GET['doctorID']))
  {
    $conn = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }else{
      $sql = "INSERT INTO Appointments(date, timeSlotID, doctorID, patientID) VALUES ('" . $_SESSION["appointmentDate"] .
      "'," . $_SESSION["timeSlotID"] . "," . $_GET["doctorID"] . "," . $_SESSION['ID'] . ")";

      if ($conn->query($sql) === TRUE) {
        echo "Appointment created successfully";
        ?>
        <br>
        <a href="https://localhost/hw3/homepage.php">Go Back Home Page</a>
        <?php

      } else {
      echo "Error: " . $sql . "<br>" . $con->error;
      }
    }
  }

  ?>
</body>
</html>
