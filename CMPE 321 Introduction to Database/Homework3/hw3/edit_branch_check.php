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
   $branchID = $_REQUEST['branchID'];
   $branchName = $_REQUEST['branchName'];

   if (empty($branchID)) {
     echo "Please enter branch's ID ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Update Branch Page</a>
     <?php
   }
   else if (empty($branchName)) {
     echo "Please enter branch name ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Update Branch Page</a>
     <?php
   }
   else {
     $branchID = test_input($branchID);
     $branchName = test_input($branchName);

     $con = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

     if($con->connect_error) {
       die("Connection failed" . $con->connect_error);
     }
     else {

        $sql = "UPDATE Branches SET name = '" . $branchName . "' WHERE ID = " .$branchID ;

        if ($con->query($sql) === TRUE) {
           echo "Branch updated successfully";
           ?>
           <br>
           <a href="https://localhost/hw3/homepage.php">Go Back Home Page</a>
           <?php
        } else {
           echo "Error updating record: " . $conn->error;
           ?>
           <br>
           <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Edit Branch Page</a>
           <?php
        }
   }
}
}
?>

</body>
</html>
