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

  <?php
  session_start();
  if(isset($_SESSION['username']))
  {
    if(isset($_SESSION['oldDate']))
      unset($_SESSION['oldDate']);

    if(isset($_SESSION['oldTimeSlotID']))
      unset($_SESSION['oldTimeSlotID']);

    if(isset($_SESSION['oldDoctorID']))
      unset($_SESSION['oldDoctorID']);

    echo "Welcome " . $_SESSION['name'] . " " . $_SESSION['surname'];
    ?>
    <a href = "logout.php"> Logout</a><br />
    <br>
    <?php
    if(!strcmp($_SESSION['userType'], "patient"))
    {
      // Create connection
      $conn = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

      // Check connection
      if ($conn->connect_error) {
          die("Connection failed: " . $conn->connect_error);
      }else{

          // List records
          $sql = "CALL show_user_appointments_info(" . $_SESSION['ID'] . ")";

          $result = $conn->query($sql);

          if ($result) {
              ?>
              <table border = 1>
                  <tr>
                      <th>Operations</th>
                      <th>Date</th>
                      <th>Start Time</th>
                      <th>End Time</th>
                      <th>Doctor Name</th>
                      <th>Doctor Surname</th>
                      <th>Branch Name</th>
              <?php

              // output data of each row
              while($row = $result->fetch_assoc()) {
                  ?>
                  <tr>
                      <td>
                          <a href = "delete_appointment.php?date=<?php echo $row["appointmentDate"];?>&timeSlotID=<?php echo $row["timeSlotID"];?>&doctorID=<?php echo $row["doctorID"];?>">
                          <img src = "img/delete.jpg" alt = "Delete" style="float:right;width:50px;height:30px;"/></a>
                          <a href = "edit_appointment.php?oldDate=<?php echo $row["appointmentDate"];?>&oldTimeSlotID=<?php echo $row["timeSlotID"];?>&oldDoctorID=<?php echo $row["doctorID"];?>">
                          <img src = "img/edit.png" alt = "Edit" style="float:right;width:50px;height:30px;"/></a>
                      </td>
                      <td><?php echo $row["appointmentDate"]; ?></td>
                      <td><?php echo $row["appointmentStartTime"]; ?></td>
                      <td><?php echo $row["appointmentEndTime"]; ?></td>
                      <td><?php echo $row["doctorName"]; ?></td>
                      <td><?php echo $row["doctorSurname"]; ?></td>
                      <td><?php echo $row["branchName"]; ?></td>
                  </tr>
                  <?php
              }

              ?>
              </table>
              <a href = "create_appointment.php">Make a new appointment</a><br />
              <?php
          } else {
              echo "You haven't got any appointment yet";
          }
      }
      $conn->close();
    }
    elseif (!strcmp($_SESSION['userType'], "admin")) {

      // Create connection
      $conn = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

      // Check connection
      if ($conn->connect_error) {
          die("Connection failed: " . $conn->connect_error);
      }else{
        ?>
          <table border = 1>
              <tr>
                  <th>Operations</th>
                  <th>Doctor Name</th>
                  <th>Doctor Surname</th>
                  <th>Branch Name</th>
          <?php
          // List records
          $sql = "SELECT Doctors.ID as doctorID, Doctors.name as doctorName, Doctors.surname as doctorSurname, Branches.name as branchName
          FROM (Doctors
          LEFT JOIN Branches ON Doctors.branchID = Branches.ID)";

          $result = $conn->query($sql);

          if ($result)
          {

              // output data of each row
              while($row = $result->fetch_assoc()) {
                  ?>
                  <tr>
                      <td>
                          <a href = "delete_doctor.php?doctorID=<?php echo $row["doctorID"];?>">
                          <img src = "img/delete.jpg" alt = "Delete" style="float:right;width:50px;height:30px;"/></a>
                          <a href = "edit_doctor.php?doctorID=<?php echo $row["doctorID"];?>&doctorName=<?php echo $row["doctorName"];?>&doctorSurname=<?php echo $row["doctorSurname"];?>&branchName=<?php echo $row["branchName"];?>">
                          <img src = "img/edit.png" alt = "Edit" style="float:right;width:50px;height:30px;"/></a>
                      </td>
                      <td><?php echo $row["doctorName"]; ?></td>
                      <td><?php echo $row["doctorSurname"]; ?></td>
                      <td><?php echo $row["branchName"]; ?></td>
                  </tr>
                  <?php
              }
          }
          ?>
          </table>
          <a href = "create_doctor.php">Register new doctor</a><br />

          <br>
          <br>
          <table border = 1>
              <tr>
                <th>Operations</th>
                <th>Branch ID</th>
                <th>Branch Name</th>
          <?php
          // List branches
          $sql = "SELECT Branches.ID as branchID, Branches.name as branchName FROM Branches";

          $result = $conn->query($sql);

          if ($result)
          {
            // output data of each row
            while($row = $result->fetch_assoc()) {
                ?>
                </tr>
                    <td>
                        <a href = "delete_branch.php?branchID=<?php echo $row["branchID"];?>">
                        <img src = "img/delete.jpg" alt = "Delete" style="float:right;width:50px;height:30px;"/></a>
                        <a href = "edit_branch.php?branchID=<?php echo $row["branchID"];?>&branchName=<?php echo $row["branchName"];?>">
                        <img src = "img/edit.png" alt = "Edit" style="float:right;width:50px;height:30px;"/></a>
                    </td>
                    <td><?php echo $row["branchID"]; ?></td>
                    <td><?php echo $row["branchName"]; ?></td>
                </tr>
                <?php
            }

          }

        ?>
        </table>
        <a href = "create_branch.php">Create new branch</a><br />
        <?php
      }
      $conn->close();
      $page = null;
      ?>
      <br><br>

      List Appointments:
      <br>
      <form method="get" action="https://localhost/hw3/homepage.php">
        <?php
        // Create connection
        $conn = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }else{

          // List branches
          $sql = "SELECT Branches.ID as branchID, Branches.name as branchName FROM Branches";

          $result = $conn->query($sql);
          ?>
          <select name ="branchName">
          <?php
          if ($result)
          {
            ?>
            <option name = "All" value="All">All</option>
            <?php
            // output data of each row
            while($row = $result->fetch_assoc()) {
            ?>
              <option name = "<?php echo $row["branchName"];?>" value="<?php echo $row["branchName"];?>"><?php echo $row["branchName"];?></option>
            <?php
            }
          }
          ?>
          </select>
        <?php
        }
        ?>
        <select name ="SP_Type">
          <option name = "Past" value="Past">Past</option>
          <option name = "Future" value="Future">Future</option>
        </select>
        <input type="submit" name="submit" value="List">
      </form>
      <?php

      if(isset($_GET["SP_Type"]))
      {
        if($_GET["SP_Type"] == "Past")
        {
          echo "Past Appointments for " . $_GET["branchName"];

          $conn = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

          // Check connection
          if ($conn->connect_error) {
              die("Connection failed: " . $conn->connect_error);
          }else{
            // List records
            $sql = "CALL list_past_appointments('" . $_GET["branchName"] . "')";

            $result = $conn->query($sql);

            if ($result) {

                ?>
                <table border = 1>
                    <tr>
                        <th>Operations</th>
                        <th>Date</th>
                        <th>Start Time</th>
                        <th>End Time</th>
                        <th>Doctor Name</th>
                        <th>Doctor Surname</th>
                        <th>Branch Name</th>
                        <th>Patient Username</th>
                        <th>Patient Name</th>
                        <th>Patient Surname</th>
                <?php

                // output data of each row
                while($row = $result->fetch_assoc()) {
                    ?>
                    <tr>
                        <td>
                            <a href = "delete_appointment.php?date=<?php echo $row["appointmentDate"];?>&timeSlotID=<?php echo $row["timeSlotID"];?>&doctorID=<?php echo $row["doctorID"];?>">
                            <img src = "img/delete.jpg" alt = "Delete" style="float:right;width:50px;height:30px;"/></a>
                            <a href = "edit_appointment.php?oldDate=<?php echo $row["appointmentDate"];?>&oldTimeSlotID=<?php echo $row["timeSlotID"];?>&oldDoctorID=<?php echo $row["doctorID"];?>">
                            <img src = "img/edit.png" alt = "Edit" style="float:right;width:50px;height:30px;"/></a>
                        </td>
                        <td><?php echo $row["appointmentDate"]; ?></td>
                        <td><?php echo $row["appointmentStartTime"]; ?></td>
                        <td><?php echo $row["appointmentEndTime"]; ?></td>
                        <td><?php echo $row["doctorName"]; ?></td>
                        <td><?php echo $row["doctorSurname"]; ?></td>
                        <td><?php echo $row["branchName"]; ?></td>
                        <td><?php echo $row["patientUsername"]; ?></td>
                        <td><?php echo $row["patientName"]; ?></td>
                        <td><?php echo $row["patientSurname"]; ?></td>
                    </tr>
                    <?php
                }

                ?>
                </table>
                <a href = "create_appointment.php">Make a new appointment</a><br />
                <?php
            }

          }

        }
        else if($_GET["SP_Type"] == "Future")
        {
          echo "Future Appointments : " . $_GET["branchName"];

          $conn = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

          // Check connection
          if ($conn->connect_error) {
              die("Connection failed: " . $conn->connect_error);
          }else{
            // List records
            $sql = "CALL list_future_appointments('" . $_GET["branchName"] . "')";

            $result = $conn->query($sql);

            if ($result) {

                ?>
                <table border = 1>
                    <tr>
                        <th>Operations</th>
                        <th>Date</th>
                        <th>Start Time</th>
                        <th>End Time</th>
                        <th>Doctor Name</th>
                        <th>Doctor Surname</th>
                        <th>Branch Name</th>
                        <th>Patient Username</th>
                        <th>Patient Name</th>
                        <th>Patient Surname</th>
                <?php

                // output data of each row
                while($row = $result->fetch_assoc()) {
                    ?>
                    <tr>
                        <td>
                            <a href = "delete_appointment.php?date=<?php echo $row["appointmentDate"];?>&timeSlotID=<?php echo $row["timeSlotID"];?>&doctorID=<?php echo $row["doctorID"];?>">
                            <img src = "img/delete.jpg" alt = "Delete" style="float:right;width:50px;height:30px;"/></a>
                            <a href = "edit_appointment.php?oldDate=<?php echo $row["appointmentDate"];?>&oldTimeSlotID=<?php echo $row["timeSlotID"];?>&oldDoctorID=<?php echo $row["doctorID"];?>">
                            <img src = "img/edit.png" alt = "Edit" style="float:right;width:50px;height:30px;"/></a>
                        </td>
                        <td><?php echo $row["appointmentDate"]; ?></td>
                        <td><?php echo $row["appointmentStartTime"]; ?></td>
                        <td><?php echo $row["appointmentEndTime"]; ?></td>
                        <td><?php echo $row["doctorName"]; ?></td>
                        <td><?php echo $row["doctorSurname"]; ?></td>
                        <td><?php echo $row["branchName"]; ?></td>
                        <td><?php echo $row["patientUsername"]; ?></td>
                        <td><?php echo $row["patientName"]; ?></td>
                        <td><?php echo $row["patientSurname"]; ?></td>
                    </tr>
                    <?php
                }

                ?>
                </table>
                <a href = "create_appointment.php">Make a new appointment</a><br />
                <?php
            }

          }
        }
      }

    }
  }
  else {
    echo "Please Login First";
    ?>
    <br>
    <a href="https://localhost/hw3/login.php">Go Back Login Page</a>
    <?php
    // remove all session variables
    session_unset();

    // destroy the session
    session_destroy();
  }
  ?>

</body>
</html>
