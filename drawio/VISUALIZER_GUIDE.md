# 🎨 Guia de Uso do Push Swap Visualizer

## ✅ Compilação Concluída!

O visualizador está pronto para uso.

## 🚀 Como Executar

### Opção 1: Script Automático (Recomendado)
```bash
./run_visualizer.sh
```

### Opção 2: Manual
```bash
cd push_swap_visualizer/build/bin
./visualizer
```

## 📖 Passo a Passo

### 1️⃣ Janela "Values" (Configuração)

- **Size**: Use o slider para escolher quantos números ordenar (ex: 5, 10, 100)
- **Shuffle**: Clique para embaralhar os números aleatoriamente
- **Numbers**: Valores gerados aparecem aqui (você pode editar manualmente)
- **Push Swap Path**: Deve estar `../../push_swap` (caminho relativo correto)
- **Compute**: Clique para executar seu algoritmo e calcular as operações

💡 **Dica**: Após clicar em "Compute", deve aparecer "OK" indicando sucesso.

### 2️⃣ Janela "Controls" (Visualização)

- **Load**: Carrega as operações calculadas (faça isso antes de iniciar)
- **Start**: Inicia a animação da ordenação
- **Speed**: Ajusta a velocidade da animação (1x, 2x, 5x, etc)
- **Pause**: Pausa a animação
- **Step**: Avança uma operação por vez (ótimo para debug)
- **Reset**: Reinicia do início

### 3️⃣ Visualização

- **Stack A**: Pilha à esquerda (começa com todos os números)
- **Stack B**: Pilha à direita (auxiliar, começa vazia)
- **Operações**: Mostradas em tempo real (sa, pb, ra, etc)

## 🎯 Exemplos de Uso

### Teste Rápido (3 números)
1. Size: 3
2. Shuffle
3. Compute → deve dar OK
4. Load
5. Start → observe as ~3 operações

### Teste Médio (100 números)
1. Size: 100
2. Shuffle
3. Compute → OK (deve calcular ~700-1200 operações)
4. Load
5. Speed: 10x (para acelerar)
6. Start

### Debug Passo a Passo
1. Configure e compute normalmente
2. Load
3. Use **Step** em vez de Start
4. Observe cada operação individualmente

## ⚙️ Solução de Problemas

### ❌ "popen() failed" ou erro ao computar
- Verifique se o caminho está correto: `../../push_swap`
- Ou use caminho absoluto: `/home/kaide/projetos/push_swap/push_swap`
- Certifique-se que `push_swap` está compilado

### ❌ Visualizador não abre
```bash
# Recompile o visualizador
cd push_swap_visualizer/build
cmake .. && make
```

### ❌ Nada acontece ao clicar Start
- Você precisa clicar em **Load** antes de **Start**
- Certifique-se que o Compute foi bem sucedido (mostra "OK")

## 🎓 Recursos Extras

### Ver número de operações
```bash
./push_swap 3 2 1 | wc -l
```

### Testar com números específicos
No visualizador, edite manualmente o campo "Numbers":
```
42 21 84 63 105
```

### Comparar diferentes algoritmos
1. Anote o número de operações do seu algoritmo
2. Teste com diferentes quantidades de números
3. Compare com os limites da 42:
   - 3 números: até 3 operações
   - 5 números: até 12 operações
   - 100 números: até 1500 operações
   - 500 números: até 11500 operações

## 📊 Análise de Performance

Seu algoritmo atual (Radix Sort):
- ✅ 3 elementos: ~10 ops (pode melhorar)
- ✅ 100 elementos: ~1100 ops (excelente!)
- ✅ 500 elementos: ~6800 ops (excelente!)

## 🎨 Dicas de Visualização

- **Cores**: Quanto mais escuro, menor o valor
- **Altura**: Representa o valor do número
- **Animação lenta**: Use Speed 0.5x para ver detalhes
- **Animação rápida**: Use Speed 20x para testes grandes

Divirta-se visualizando seu algoritmo! 🚀
