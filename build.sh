
set -e  

echo "🛠️  Compilando bitra..."

cd "$(dirname "$0")"

mkdir -p build
cd build
cmake ..
make

echo "🚀 Ejecutando con GameMode..."
gamemoderun ./bitra
