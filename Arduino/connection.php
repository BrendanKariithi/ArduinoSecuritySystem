<?php
$username = "root";
$pass = "root";
$host = "localhost";
$db_name = "Arduino";
$con = mysqli_connect ($host, $username, $pass);
$db = mysqli_select_db ( $con, $db_name );
?>
