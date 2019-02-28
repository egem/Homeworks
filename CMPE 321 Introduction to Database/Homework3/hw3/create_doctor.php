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

  <form method="post" action="create_doctor_check.php">
    Doctor Name <input type="text" name="doctorName">
    <br><br>
    Doctor Surname <input type="text" name="doctorSurname">
    <br><br>

    Branch Name
    <?php
    // Create connection
    $conn = new mysqli($dbServername, $dbUsername, $dbPassword, $dbName);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }else{

      // List branches
      $sql = "SELECT Branches.ID as branchID, Branches.name as branchName FROM Branches";

      $result = $conn->query($sql);
      ?>
      <select name ="doctorBranchName">
      <?php
      if ($result)
      {

        // output data of each row
        while($row = $result->fetch_assoc()) {
        ?>
          <option name = "<?php echo $row["branchName"];?>" value="<?php echo $row["branchName"];?>"><?php echo $row["branchName"];?></option>
        <?php
        }
      }
      ?>
      </select>
    <?php
    }
    ?>
    <br>
    <br>
    <input type="submit" name="submit" value="Create">
  </form>

</body>
</html>
