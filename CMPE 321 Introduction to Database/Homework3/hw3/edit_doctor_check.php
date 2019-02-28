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
   $doctorID = $_REQUEST['doctorID'];
   $doctorName = $_REQUEST['doctorName'];
   $doctorSurname = $_REQUEST['doctorSurname'];
   $doctorBranchName = $_REQUEST['doctorBranchName'];

   if (empty($doctorID)) {
     echo "Please enter doctor's ID ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Update Doctor Page</a>
     <?php
   }
   else if (empty($doctorName)) {
     echo "Please enter doctor's name ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Update Doctor Page</a>
     <?php
   }
   else if (empty($doctorSurname)) {
     echo "Please enter doctor's surname ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Update Doctor Page</a>
     <?php
   }
   else if (empty($doctorBranchName)) {
     echo "Please enter doctor's branch ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Update Doctor Page</a>
     <?php
   }
   else {
     $doctorID = test_input($doctorID);
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
          <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Update Doctor Page</a>
          <?php
        }
        else {
          $row = $result->fetch_assoc();

          $sql = "UPDATE Doctors SET name = '" . $doctorName . "', surname = '" . $doctorSurname . "', branchID = '" . $row["branchID"] . "' WHERE ID = " .$doctorID ;

          if ($con->query($sql) === TRUE) {
             echo "Doctor updated successfully";
             ?>
             <br>
             <a href="https://localhost/hw3/homepage.php">Go Back Home Page</a>
             <?php
          } else {
             echo "Error updating record: " . $conn->error;
             ?>
             <br>
             <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Edit Doctor Page</a>
             <?php
          }
      }
   }
}
}
?>

</body>
</html>
