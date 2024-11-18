#!/bin/bash

# Ruta del archivo Makefile para actualizar
MAKEFILE="Makefile"

# Parámetro de entrada: archivo .h donde se guardarán las funciones
HEADER_FILE="$1"

# Verificar que se ha proporcionado el archivo de encabezado
if [[ -z "$HEADER_FILE" ]]; then
  echo "Error: Debes proporcionar la ruta a un archivo .h"
  exit 1
fi

# Obtener la lista de archivos fuente
SRC_FILES=$(find ./src -type f -name "*.c")

# Escapar caracteres especiales para sed
ESCAPED_SRC=$(echo "$SRC_FILES" | sed 's/\//\\\//g')

# Actualizar el Makefile con los archivos fuente
sed -i "s/^SRC = .*/SRC = $ESCAPED_SRC/" "$MAKEFILE"
echo "Makefile actualizado con los archivos fuente:"
echo "$SRC_FILES"

# Encabezado del archivo .h
echo "#ifndef MINISHELL_H" > "$HEADER_FILE"
echo "# define MINISHELL_H" >> "$HEADER_FILE"
echo "# include \"../libimp/libft.h\"" >> "$HEADER_FILE"
echo "# include <readline/readline.h>" >> "$HEADER_FILE"
echo "# include <readline/history.h>" >> "$HEADER_FILE"
echo "# include <sys/types.h>" >> "$HEADER_FILE"
echo "# include <sys/stat.h>" >> "$HEADER_FILE"
echo "# include <termios.h>" >> "$HEADER_FILE"
echo "# include <curses.h>" >> "$HEADER_FILE"
echo "# include <unistd.h>" >> "$HEADER_FILE"
echo "# include <string.h>" >> "$HEADER_FILE"
echo "# include <dirent.h>" >> "$HEADER_FILE"
echo "# include <stdio.h>" >> "$HEADER_FILE"
echo "# include <term.h>" >> "$HEADER_FILE"
echo "" >> "$HEADER_FILE"

# Extraer funciones de cada archivo .c y añadirlas al archivo de encabezado
for file in $SRC_FILES; do
  # Buscar todas las funciones en el archivo y extraer su tipo, nombre y argumentos
sed -nE 's/^([a-zA-Z_][a-zA-Z0-9_]*[ \t]+\**)([a-zA-Z_][a-zA-Z0-9_]*)[ \t]*\((.*)\)[ \t]*$/\1\2(\3);/p' "$file" >> "$HEADER_FILE"
done

# Cerrar el archivo .h
echo "#endif" >> "$HEADER_FILE"

echo "Archivo de encabezado actualizado con las funciones encontradas en $HEADER_FILE"
