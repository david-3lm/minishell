
las redirecciones que vamos a trabajar son de cuatro tipos:
1 - > -- redirecciona stdout hacia una rchivo. Crea si no existe, si existe, sobreescribe.

> PARA CREAR ARCHIVOS VACIOS
Utilizar el comando touch para crear un archivo vació es una práctica común que también puede realizarse con el operador de redireccionamiento >:

2 - >> -- redirecciona stdout hacia un archivo. Lo crea si no existe, si existe, concatena al final del archivo
3 - < -- redirecciona STDIN desde un archivo. El contenido del archivo es el input del comando.

## en las redirecciones de tipo 1 2 y 3, el siguiente elemento, palabra, string o lo que sea, es el nombre del archivo de lectura o escritura. 

4 - << -- HereDoc. 
	Es cuando un bloque de texto puede ser redireccionado a un comando o archivo de una manera interactiva. El here document funciona indicando un DELIMITADOR que no es más que una palabra o cadena cualquiera que cierra el bloque de texto que se desea redireccionar.

Entonces, en la estructura de redir necesitaria:
	- saber si hay redirecciones
	- saber si hay in, out o ambas (básicamente, el tipo de las redirecciones)
	- si es heredoc, necesito también el limitador
	- el nombre del archivo de lectura o escritura (el elemento que hay tras la redireccion '<' '>' '>>' )