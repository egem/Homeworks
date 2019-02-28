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

if($_REQUEST['submit'] == 'signup')
{
  header("Location:https://localhost/hw3/register.php");
  die();

}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
   // collect value of input field
   $username = $_REQUEST['username'];
   $password = $_REQUEST['password'];
   if (empty($username)) {
     echo "Please enter username ";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Login Page</a>
     <?php
   }
   else if(empty($password)) {
     echo "Please enter password";
     ?>
     <br>
     <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Login Page</a>
     <?php
   }
   else {
     $username = test_input($username);
     $password = test_input($password);
     $con = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

     if($con->connect_error) {
       die("Connection failed" . $con->connect_error);
     }
     else {

       $sql = "SELECT ID, username, name, surname from Patients
       WHERE username = '" . $username . "' AND password = '" . $password . "'";

        $result = $con->query($sql);

        if($result->num_rows > 0) {

          $row = $result->fetch_assoc();
          session_start();
          $_SESSION['ID'] = $row["ID"];
          $_SESSION['username'] = $row['username'];
          $_SESSION['name'] = $row['name'];
          $_SESSION['surname'] = $row['surname'];
          $_SESSION['userType'] = "patient";
          $con->close();
          header("Location:https://localhost/hw3/homepage.php");
          die();
        }
        else {

          $sql = "SELECT ID, username, name, surname from Admins
          WHERE username = '" . $username . "' AND password = '" . $password . "'";

           $result = $con->query($sql);

           if($result->num_rows > 0) {

             $row = $result->fetch_assoc();
             session_start();
             $_SESSION['ID'] = $row["ID"];
             $_SESSION['username'] = $row['username'];
             $_SESSION['name'] = $row['name'];
             $_SESSION['surname'] = $row['surname'];
             $_SESSION['userType'] = "admin";
             $con->close();
             header("Location:https://localhost/hw3/homepage.php");
             die();
           }
           else {
             $con->close();
             echo "Wrong username or password";
             ?>
             <br>
             <a href="<?php echo $_SERVER['HTTP_REFERER'];?>">Go Back Login Page</a>
             <?php
          }
        }
     }
   }
}
?>

</body>
</html>
