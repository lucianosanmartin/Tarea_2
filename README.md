# Tarea 2

## Descripción

Este repositorio contiene un programa StreamFinder, este permite cargar un archivo CSV con cantidades masivas de datos sobre peliculas y organizar la informacion en distintos arboles binarios para poder facilitar la busqueda de peliculas en base a sus géneros, directores, decada de estreno y su ID, además, cuenta con una funcion para crear una watchlist en la que se puede agregar y eliminar peliculas y  mostrar todas las peliculas que esten guardadas en esta. La finalidad del programa es poder buscar facilmente ciertas peliculas entre grandes cantidades de datos para ser anexadas en una lista de pendientes. 

## Cómo compilar y ejecutar el programa

1-Para poder compilar y ejecutar el programa primero debera traspasar el codigo a Visual Studio code(si no lo tiene, puede instalarlo de manera gratuita desde google) o descomprimir el zip y despues abrir con Visual Studio Code el archivo con los codigos.

2-Luego, debe tener instalada las extensiones de Visual Studio Code C/C++ Extension Pack y C/C++ Compile Run(estas se instalan desde la seccion Extensions desde el mismo Visual Studio Code), además del compilador MinGW, esta se puede descargar desde google de manera gratuita.

Links a videos para instalar Visual Studio Code y MinGW, respectivamente:
 
 -https://www.youtube.com/watch?v=K8ATqLVFfpo
 
 -https://www.youtube.com/watch?v=GEZLjRSY_m8

3-Ya una vez tenga instalada todo, simplemente debe presionar F6 o Fn+F6, desde VSCode, y el programa se compilara y ejecutara automaticamente desde una terminal en esta misma aplicacion, otra opcion es presionar F8 o Fn+F8, esto abrira una terminal desde el mismo dispositivo que compilara y ejecutara el programa.

4-Recuerde que debe tener algun archivo CSV para poder usar el programa en su totalidad, además de verificar que la ruta del archivo este conectada con la del .exe, sino no se  podrá abrir el archivo y no se podran cargar los datos.

## Funcionalidades

La funcion Cargar Peliculas solo recibe archivos CSV que contengan los mismo parametros que el del archivo de ejemplo "Top1500.csv", estos son:

-Const

-Title

-Directors

-Genres

-Year

Si el archivo ingresado no cumple con estos parametros no se leeran los datos y se retornará NULL

## Ejemplo de uso

Al inicio se le mostrará un menú el cual le mostrara todas las opciones disponibles, para elegir una simplemente debe presionar el número deseado, y seguido, presionar la tecla Enter.

### Cargar Pelicula

Opcion seleccionada: 1)Cargar Pelicula

Nombre del archivo csv/: Top1500

Peliculas cargadas correctamente!

Peliculas cargadas: 1500

### Mostrar categorías

Opcion seleccionada: 3)Mostrar Categorias

Categorias existentes:

-Casa

### Registrar Pendiente

Opcion seleccionada: 4)Registrar Pendiente

Categoria: Casa

Descripcion: Lavar auto

Tarea registrada exitosamente

### Filtrado por categoría

Opcion seleccionada: 7)Filtrar por categoria

Categoria deseada: Casa

-Lavar auto (12:09:32)

### Visualizar tablero general

Opcion seleccionada: 6)Visualizacion del tablero general

-[Casa] Lavar auto (12:09:32)

### Atender Siguiente

Opcion seleccionada: 5)Atender Siguiente

Lavar Auto | Casa | 12:09:32

### Eliminar categoría

Opcion seleccionada: 2)Eliminar Categoria 

Categoria a eliminar: Casa
