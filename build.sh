#!/usr/bin/env bash
set -e

echo "🛠️  Comprobando raylib..."

# Verifica si raylib está instalada
if pkg-config --exists raylib; then
    echo "✅ raylib ya está instalada."
else
    echo "🔍 raylib no encontrada. Intentando instalar..."

    # Detecta la distribución
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        distro=$ID
    else
        echo "❌ No se pudo detectar la distribución de Linux."
        exit 1
    fi

    case "$distro" in
        fedora)
            echo "📦 Instalando raylib en Fedora..."
            sudo dnf install -y raylib-devel
            ;;
        ubuntu|debian)
            echo "📦 Instalando raylib en Ubuntu/Debian..."
            sudo apt update
            sudo apt install -y libraylib-dev
            ;;
        arch|manjaro)
            echo "📦 Instalando raylib en Arch/Manjaro..."
            sudo pacman -Sy --noconfirm raylib
            ;;
        *)
            echo "❌ Distro no soportada automáticamente: $distro"
            echo "📚 Instala raylib manualmente o usa una copia local en tu proyecto."
            exit 1
            ;;
    esac
fi

echo "🧱 Compilando proyecto..."

cd "$(dirname "$0")"

mkdir -p build
cd build
cmake ..
make

echo "🚀 Ejecutando..."

# Verifica si gamemoderun está disponible
if command -v gamemoderun >/dev/null 2>&1; then
    echo "✅ GameMode encontrado. Ejecutando con gamemoderun..."
    gamemoderun ./bitra
else
    echo "⚠️  GameMode no encontrado. Ejecutando normalmente..."
    ./bitra
fi
