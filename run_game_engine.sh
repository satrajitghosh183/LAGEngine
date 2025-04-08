
#!/bin/bash

PROJECT_DIR="/mnt/d/Master Things/Spring Sem Classes/ComputerGraphics/MasterThesis_FinalProject"

echo "➡️  Building and running GameEngine3D from: $PROJECT_DIR"
cd "$PROJECT_DIR" || exit 1

echo "🧹 Cleaning build directory..."
rm -rf build
mkdir build
cd build || exit 1

echo "🔧 Running CMake..."
cmake .. || { echo "❌ CMake failed"; exit 1; }

echo "🔨 Running Make..."
make || { echo "❌ Make failed"; exit 1; }


# echo "🚀 Running GameEngine3D..."
# ./bin/GameEngine3D || echo "❌ GameEngine3D crashed"