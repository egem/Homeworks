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
    if($_SESSION['userType'] == "patient" || $_SESSION['userType'] = "admin")
    {
      $con = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

      if($con->connect_error) {
        die("Connection failed" . $con->connect_error);
      }
      else {
        // sql to delete a record
        $sql = "DELETE FROM Appointments WHERE date = '" . $_GET['date'] . "' AND timeSlotID =
        '" . $_GET['timeSlotID'] . "' AND doctorID = '" . $_GET['doctorID'] . "'";

        if ($con->query($sql) == TRUE) {
            echo "Appointment cancelled successfully";
            ?>
            <br>
            <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back HomePage</a>
            <?php
        } else {
            echo "Error deleting record: " . $conn->error;
            ?>
            <br>
            <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back HomePage</a>
            <?php
        }

        $con->close();
      }
    }
?>

</body>
</html>
