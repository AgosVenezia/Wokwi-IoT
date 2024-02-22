<?php
    
    //Estas van a ser las credenciales de acceso a la base de datos.
    $user = "id21913209_agosveneziaiotdb";
    $pass = "Tecno3Fdb2.";
    $server = "localhost"; //Link del servidor.
    $db ="id21913209_agosveneziaiotdb"; //Nombre de la base de datos.
    
    //Y con el método mysqli_connect podemos conectarnos a la base de datos que creamos.
    //Eso se guarda dentro de la variable "con".
    $con = mysqli_connect($server, $user, $pass, $db);
    
?>