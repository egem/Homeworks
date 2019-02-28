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
    if(!strcmp($_SERVER['HTTP_REFERER'],"https://localhost/hw3/homepage.php"))
    {
      $con = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

      if($con->connect_error) {
        die("Connection failed" . $con->connect_error);
      }
      else {
        // sql to delete a record
        $sql = "DELETE FROM Doctors WHERE ID = '" . $_GET['doctorID'] . "'";

        if ($con->query($sql) === TRUE) {
            echo "Doctor deleted successfully";
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
