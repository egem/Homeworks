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

  <form method="post" action="create_branch_check.php">
    Branch Name <input type="text" name="branchName">
    <br><br>
    <input type="submit" name="submit" value="Create">
  </form>

</body>
</html>
