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

  <form method="post" action="edit_branch_check.php">
    Branch ID: <input type="text" name="branchID" value="<?php echo $_REQUEST["branchID"] ?>" readonly>
    <br><br>
    Branch Name <input type="text" name="branchName" value = "<?php echo $_REQUEST["branchName"] ?>">
    <br><br>
    <input type="submit" name="submit" value="Update">
  </form>

</body>
</html>
