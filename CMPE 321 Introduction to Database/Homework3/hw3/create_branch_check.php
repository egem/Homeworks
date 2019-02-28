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
   $branchName = $_REQUEST['branchName'];

   if (empty($branchName)) {
     echo "Please enter branch name ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Home Page</a>
     <?php
   }
   else {
     $branchName = test_input($branchName);

     $con = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

     if($con->connect_error) {
       die("Connection failed" . $con->connect_error);
     }
     else {

       $sql = "SELECT name as branchName from Branches WHERE branchName = '" . $branchName . "'";

       $result = $con->query($sql);

       if($result) {
          echo "Branch has already exist"
          ?>
          <br>
          <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Home Page</a>
          <?php
        }
        else {
          $sql = "INSERT INTO Branches (name) VALUES ('" . $branchName . "')";

          if ($con->query($sql) === TRUE) {
            echo "Branch created successfully";
            ?>
            <br>
            <a href="https://localhost/hw3/homepage.php">Go Back Home Page</a>
            <?php

          } else {
          echo "Error: " . $sql . "<br>" . $con->error;
          }
        }
        $con->close();
     }
   }
}
?>

</body>
</html>
