<html>
    
    <head>
        
        <title>Tecno 3F</title>
    
    </head>
    
    <body>
        
        <!--En mitad del HTML podemos escribir código PHP, siempre y cuando lo hagamos entre las dos llaves características de PHP.  En este caso lo usamos para incluir el script EstadoESP.php donde están las variables almacenadas traidas de la base de datos, que ahora vamos a usar para mostrar en el HTML-->
        <?php 
        
        include 'EstadoESP.php'; 
        
        ?>
    
    <!--A cada h1 le ponemos una id. ¿Por qué? Para poder identificarlos y luego en CSS modificar sus propiedades, como el color, la posición, etc.-->
    <h1 id="titulo">Temperatura y Humedad</h1>
    
    <br>
    <br>
    
    <!--Entre medio del h1 llamamos a la función "echo" de PHP para que nos tire el valor de la variable temperatura que almacenamos en el otro script. Usamos php dentro de una etiqueta HTML, eso es realmente muy bueno, por eso PHP es un lenguaje muy utilizado en desarrollos webs.-->
    <h1 id="temp"><?php echo "Temperatura: " .$Temperatura ." °C"; ?></h1>
    
    <br>
    <br>
    
    <h1 id="hum"><?php echo "Humedad: " .$Humedad ." %"; ?></h1>
    
    <!--En el mismo HTML, usamos el código CSS mediante la etiqueta <style>. -->
    <style>
        
        /*Con el numeral "#" podemos llamar a las "id" que establecimos en el HTML.*/
        #titulo {
            text-align: center;
        }
        
        #temp {
            color: blue;
        }
        
        #hum {
            color:blue;
        }
        
    </style>
    
    </body>
    
</html>