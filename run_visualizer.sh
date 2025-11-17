#!/bin/bash

# Script para facilitar o uso do Push Swap Visualizer
# Uso: ./run_visualizer.sh

echo "🎨 Push Swap Visualizer"
echo "======================="
echo ""

# Verificar se o visualizador está compilado
if [ ! -f "push_swap_visualizer/build/bin/visualizer" ]; then
    echo "❌ Visualizador não encontrado!"
    echo "Compilando o visualizador..."
    cd push_swap_visualizer/build
    cmake .. && make
    cd ../..
fi

# Verificar se o push_swap está compilado
if [ ! -f "push_swap" ]; then
    echo "❌ push_swap não encontrado!"
    echo "Compilando push_swap..."
    make
fi

echo "✅ Iniciando visualizador..."
echo ""
echo "📝 Como usar:"
echo "   1. Na janela 'Values':"
echo "      - Use o slider para escolher a quantidade de números"
echo "      - Clique em 'Shuffle' para embaralhar"
echo "      - Verifique o caminho: '../../push_swap'"
echo "      - Clique em 'Compute' para calcular"
echo ""
echo "   2. Na janela 'Controls':"
echo "      - Clique em 'Load' para carregar as operações"
echo "      - Clique em 'Start' para iniciar a animação"
echo "      - Use 'Speed' para ajustar a velocidade"
echo "      - Use 'Step' para avançar passo a passo"
echo ""

cd push_swap_visualizer/build/bin
./visualizer
