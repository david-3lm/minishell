#!/bin/bash

# Archivo Makefile donde se hará la actualización
MAKEFILE="Makefile"

# Buscar todos los archivos .c en src y subcarpetas, y unirlos con espacios
SRC_FILES=$(find ./src -type f -name "*.c" | tr '\n' ' ')
HEAD_FILES=$(find ./inc -type f -name "*.h" | tr '\n' ' ')

# Escapar caracteres especiales para evitar problemas en sed
ESCAPED_SRC=$(echo "$SRC_FILES" | sed 's/\//\\\//g')
ESCAPED_HEAD=$(echo "$HEAD_FILES" | sed 's/\//\\\//g')

# Reemplazar la línea que comienza con "SRC = " en el Makefile
sed -i "s/^SRC = .*/SRC = $ESCAPED_SRC/" "$MAKEFILE"
sed -i "s/^HEADERS = .*/HEADERS = $ESCAPED_HEAD/" "$MAKEFILE"

echo "Makefile actualizado con los archivos fuente:"
echo "$SRC_FILES"
