<?php
session_start();
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
   $username = $_REQUEST['userName'];
   $name = $_REQUEST['name'];
   $surname = $_REQUEST['surname'];
   $password = $_REQUEST['password'];
   $confirmPassword = $_REQUEST['confirmPassword'];

   if (empty($username)) {
     echo "Please enter username ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Signup Page</a>
     <?php
   }
   else if(empty($name)) {
     echo "Please enter your name";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Signup Page</a>
     <?php
   }
   else if(empty($surname)) {
     echo "Please enter your surname";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Signup Page</a>
     <?php
   }
   else if(empty($password)) {
     echo "Please enter password";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back SignUp Page</a>
     <?php
   }
   else if(empty($confirmPassword)) {
     echo "Please enter your password twice to confirm";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back SignUp Page</a>
     <?php
   }
   else if(strcmp($password,$confirmPassword)) {
     echo "Two passwords should be same";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back SignUp Page</a>
     <?php
   }
   else {
     $username = test_input($username);
     $name = test_input($name);
     $surname = test_input($surname);
     $password = test_input($password);

     $con = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

     if($con->connect_error) {
       die("Connection failed" . $con->connect_error);
     }
     else {
       $sql = "SELECT username from Patients WHERE username = '" . $username . "'";
       $sql2 = "SELECT username from Admins WHERE username = '" . $username . "'";

       $result = $con->query($sql);
       $result2 = $con->query($sql2);

       if(!$result || !$result2) {
          echo "You have already an account."
          ?>
          <br>
          <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back SignUp Page</a>
          <?php
        }
        else {
          $sql = "INSERT INTO Patients (username, name, surname, password)
VALUES ('" . $username . "', '" . $name . "', '" . $surname . "', '" . $password . "')";

          if ($con->query($sql) === TRUE) {
            echo "Signed up successfully";
            ?>
            <br>
            <a href="https://localhost/hw3/login.php">Go Back Login Page</a>
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
