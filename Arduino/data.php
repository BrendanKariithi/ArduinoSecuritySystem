<?php
include ('connection.php');
$sql_insert = "INSERT INTO data (temperature, humidity, gas) VALUES ('".$_GET["temperature"]."', '".$_GET["humidity"]."', '".$_GET["gas"]."')";
if(mysqli_query($con,$sql_insert))
{
echo "Done";
mysqli_close($con);
}
else
{
echo "error is ".mysqli_error($con );
}
?>
