## TODO:
1. Si no hay infile ni outfile, que será el caso normal, debería leer el output de la terminal (STDOUT) y pasar ese output al siguiente comando, y así hasta que no haya pipes, y ese último comando, el resultado lo sacas por STDOUT por defecto, si no hay outfile
	- No debería se rtan complicado, quizá solo sea necesario cambiar lo del dup2 para que no se escriba en outfile ni se lea de infile???
	- probar que pueda usar el pipex como función
2. Heredoc por separado
3. (MÁS ADELANTE) --> cuando el input en consola termina en pipe |, aparece el > como de heredoc y le puedes introducir el siguiente comando así

4. Lo primero que hay que tener en cuenta en la ejecución es la gestión de las redirecciones: 
	- '>' redirecciona STDOUT hacia un archivo. Si no existe, lo crea, sie xiste, sobreescribe
	- '>>' redirecciona STDOUT a un archivo. Si existe, concatena (APPEND)
	- '<' redirecciona STDIN desde un archivo. Este contenido es el input del comando
	- '<<' Heredoc


-----
5. Aunque no haya pipes, los comandos tienen que ser interpretados como comandos y sacar la ejecución por la terminal por defecto
 -----

- "no singular function to print the output"--> varios pippex
- 