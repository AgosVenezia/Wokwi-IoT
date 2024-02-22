<?php
        //Incluimos la librería de conexión con la Base de Datos.
        include'conexion.php';
        
        //Carga de datos en la base de datos.
        //Esta línea verifica si el campo "temperatura" se envió a través de una
        //solicitud POST. Si el campo "temperatura" está presente en la solicitud
        //POST, isset devuelve true; de lo contrario, devuelve false.
        if(isset($_POST['temperatura'])) {
            
            $temperatura = $_POST['temperatura'];
            echo " Temperaura : ".$temperatura;
            
        }
        
        
        if(isset($_POST['humedad'])) {
            $humedad = $_POST['humedad'];
            echo " humedad : ".$humedad;
            
        //Guardamos en una variable la fecha y hora de alguna ciudad, en este caso, de Buenos Aires.
        date_default_timezone_set('america/Argentina/Buenos_Aires');
        $fecha_actual = date("Y-m-d H:i:s");
        
        //Realizamos la consulta SQL para introducir los valores en la base de datos.
        $consulta = "INSERT INTO Clase2(Temperatura, Humedad, fecha_actual) VALUES ('$temperatura','$humedad', '$fecha_actual')";
        
        //Enviamos la consulta con mysqli_query y si se realizó correctamente envía un true, sino un false.
        //Ese valor de true o false, se almacena en la variable "resultado"
        $resultado = mysqli_query($con, $consulta);
        
            if ($resultado){
                echo " Registo en base de datos OK! ";
            } else {
                echo " Falla! Registro BD";
            }
        
        }
        
        

        //Ahora leemos los valores que están almacenados en la Base de datos para después utilizarlos en el HTML.
        
        //Creamos la consulta. Seleccionamos todos los datos de la Base de Datos.
        $consulta2 = "SELECT * FROM Clase2";
        
        //Al igual que antes, enviamos la consulta a la base de datos y lo almacenamos en la variable $resultado2.
        $resultado2 = mysqli_query($con,$consulta2);
        
        if ($resultado2) { //Si se estableció la conexión y se realizó la operación, entonces se ejecuta ese if.
        /*Esta parte realmente es muy dificil de explicar, no se preocupen si no entienden.
        En la consulta seleccioné todos los datos de la tabla. En la variable $resultado2 están entonces
        almacenados todos los datos de toda la base de datos en filas. Con la función fetch_array() recorre fila por
        fila, y las va almacenando en la variable $row en cada iteración.
        En esa fila, va almacenando en estas variables, los valores de las columnas que contengan la palabra Id,
        Temperatura y Humedad, de esa fila.
        El While se sigue ejecutando mientras siga habiendo filas debajo. Hasta cuando? Hasta llegar a la última fila y
        ya no queden más filas debajo. Entonces el While termina cuando almacenó los últimos valores de la última fila
        los registros de la base de datos. Que en definitiva, es el último valor que envió la ESP32.*/
        
            while($row = $resultado2->fetch_array()) {
                $Id = $row['Id'];
                $Temperatura = $row['Temperatura'];
                $Humedad = $row['Humedad'];
            }
        }
        
?>