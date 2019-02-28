<?php
$dbServername = "localhost";
$dbUsername = "root";
$dbPassword = "";
$dbName = "cmpe321_hw3";
?>

<html>
<body>

<?php
function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
   // collect value of input field
   $doctorName = $_REQUEST['doctorName'];
   $doctorSurname = $_REQUEST['doctorSurname'];
   $doctorBranchName = $_REQUEST['doctorBranchName'];

   if (empty($doctorName)) {
     echo "Please enter doctor's name ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Create Doctor Page</a>
     <?php
   }
   else if (empty($doctorSurname)) {
     echo "Please enter doctor's surname ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Create Doctor Page</a>
     <?php
   }
   else if (empty($doctorBranchName)) {
     echo "Please enter doctor's branch ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Create Doctor Page</a>
     <?php
   }
   else {
     $doctorName = test_input($doctorName);
     $doctorSurname = test_input($doctorSurname);
     $doctorBranchName = test_input($doctorBranchName);

     $con = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

     if($con->connect_error) {
       die("Connection failed" . $con->connect_error);
     }
     else {

       $sql = "SELECT ID as branchID from Branches WHERE name = '" . $doctorBranchName . "'";

       $result = $con->query($sql);

       if(!$result) {
          echo "Branch does not exist";
          ?>
          <br>
          <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Create Doctor Page</a>
          <?php
        }
        else {
          $row = $result->fetch_assoc();
          $sql = "INSERT INTO Doctors (name, surname, branchID) VALUES ('" . $doctorName .
          "','" . $doctorSurname . "','" . $row["branchID"] . "')";

          if ($con->query($sql) === TRUE) {
            echo "Doctor created successfully";
            ?>
            <br>
            <a href="https://localhost/hw3/homepage.php">Go Back Home Page</a>
            <?php

          } else {
          echo "Error: " . $sql . "<br>" . $con->error;
          }

        $con->close();
     }
   }
}
}
?>

</body>
</html>
