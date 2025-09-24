SRC_DIR="src"
INCLUDE_DIR="include"
BIN_NAME="bitra"
EXEC_PATH="./$BIN_NAME"

echo "Compilando..."

g++ -I$INCLUDE_DIR $SRC_DIR/*.cpp -o $EXEC_PATH -lraylib -lm -lpthread -ldl -lrt -lX11

if [ $? -eq 0 ]; then
    echo "Compilación exitosa, abriendo el ejecutable..."
    ./$EXEC_PATH
else
    echo "Hubo un error en la compilación. Revisa los mensajes de error."
fi
