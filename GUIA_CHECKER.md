# 🔍 Guia de Uso do Checker

## ✅ O que é o Checker?

O **checker_linux** é um programa fornecido pela 42 que valida se as operações geradas pelo seu `push_swap` realmente ordenam os números corretamente.

---

## 🚀 Como Usar

### 1️⃣ Compilar seu push_swap
```bash
make
```

### 2️⃣ Tornar o checker executável (só precisa fazer uma vez)
```bash
chmod +x checker_linux
```

### 3️⃣ Testar com o checker
```bash
./push_swap [números] | ./checker_linux [números]
```

---

## 📝 Exemplos Práticos

### Teste básico (3 números)
```bash
./push_swap 3 2 1 | ./checker_linux 3 2 1
```
**Saída esperada:** `OK` ✅

### Teste com 5 números
```bash
./push_swap 5 4 3 2 1 | ./checker_linux 5 4 3 2 1
```
**Saída esperada:** `OK` ✅

### Teste com números aleatórios
```bash
./push_swap 42 21 84 63 105 | ./checker_linux 42 21 84 63 105
```
**Saída esperada:** `OK` ✅

### Números já ordenados (não deve imprimir nada)
```bash
./push_swap 1 2 3 4 5 | ./checker_linux 1 2 3 4 5
```
**Saída esperada:** `OK` ✅ (sem operações, mas ainda OK)

---

## 🎯 Como Funciona?

```
┌─────────────────┐
│  ./push_swap    │  → Gera operações (sa, pb, ra...)
└────────┬────────┘
         │ (pipe |)
         ↓
┌─────────────────┐
│ ./checker_linux │  → Executa operações e verifica
└────────┬────────┘
         ↓
    OK ou KO
```

---

## 📊 Resultados Possíveis

| Saída | Significado |
|-------|-------------|
| **OK** | ✅ Stack A está ordenada e Stack B está vazia |
| **KO** | ❌ Algo deu errado (não ordenou ou ficou em B) |
| **Error** | ❌ Operação inválida ou argumentos errados |

---

## 🧪 Testes Avançados

### Contar operações E validar
```bash
./push_swap 3 2 1 | tee /dev/tty | ./checker_linux 3 2 1
```
Isso mostra as operações E valida ao mesmo tempo.

### Teste com 100 números aleatórios
```bash
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ')
./push_swap $ARG | ./checker_linux $ARG
```

### Teste em lote (10 testes de 100 números)
```bash
for i in {1..10}; do
    ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
    RESULT=$(./push_swap $ARG | ./checker_linux $ARG)
    OPS=$(./push_swap $ARG | wc -l)
    echo "Teste $i: $RESULT ($OPS operações)"
done
```

---

## 🎓 Scripts Úteis

### Script de teste automático
Crie um arquivo `test.sh`:
```bash
#!/bin/bash

echo "🧪 Testando Push Swap..."
echo "========================"

# Teste 1: 3 números
echo -n "3 números: "
RESULT=$(./push_swap 3 2 1 | ./checker_linux 3 2 1)
OPS=$(./push_swap 3 2 1 | wc -l)
echo "$RESULT ($OPS ops)"

# Teste 2: 5 números
echo -n "5 números: "
RESULT=$(./push_swap 5 4 3 2 1 | ./checker_linux 5 4 3 2 1)
OPS=$(./push_swap 5 4 3 2 1 | wc -l)
echo "$RESULT ($OPS ops)"

# Teste 3: 100 números aleatórios
echo -n "100 números: "
ARG=$(shuf -i 1-5000 -n 100 | tr '\n' ' ')
RESULT=$(./push_swap $ARG | ./checker_linux $ARG)
OPS=$(./push_swap $ARG | wc -l)
echo "$RESULT ($OPS ops)"

# Teste 4: 500 números aleatórios
echo -n "500 números: "
ARG=$(shuf -i 1-5000 -n 500 | tr '\n' ' ')
RESULT=$(./push_swap $ARG | ./checker_linux $ARG)
OPS=$(./push_swap $ARG | wc -l)
echo "$RESULT ($OPS ops)"

echo "========================"
echo "✅ Testes concluídos!"
```

Tornar executável e rodar:
```bash
chmod +x test.sh
./test.sh
```

---

## 📈 Limites da 42

| Tamanho | Nota Max | Nota Média | Nota Mínima |
|---------|----------|------------|-------------|
| 3 números | ≤ 3 ops | ≤ 3 ops | > 3 ops |
| 5 números | ≤ 12 ops | ≤ 12 ops | > 12 ops |
| 100 números | < 700 ops | < 900 ops | < 1500 ops |
| 500 números | < 5500 ops | < 7000 ops | < 11500 ops |

---

## 🔧 Troubleshooting

### Problema: `Permission denied`
```bash
chmod +x checker_linux
```

### Problema: `KO` quando deveria ser `OK`
- Verifique se há operações inválidas
- Teste manualmente as operações
- Use o visualizador para ver o que está acontecendo

### Problema: `Error`
- Argumentos inválidos (duplicatas, não-números, etc)
- Operação inválida gerada

### Problema: Muitas operações
- Seu algoritmo precisa de otimização
- Para casos pequenos (2-3 números), implemente casos específicos

---

## 🎯 Workflow Completo

```bash
# 1. Limpar compilações antigas
make fclean

# 2. Compilar
make

# 3. Teste rápido
./push_swap 3 2 1 | ./checker_linux 3 2 1

# 4. Ver operações
./push_swap 3 2 1

# 5. Contar operações
./push_swap 3 2 1 | wc -l

# 6. Teste complexo
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ')
./push_swap $ARG | ./checker_linux $ARG
```

---

## 💡 Dicas

✅ **Sempre teste com o checker** após mudanças no código  
✅ **Conte as operações** para verificar performance  
✅ **Use o visualizador** para entender o algoritmo  
✅ **Teste casos extremos**: já ordenado, ordem reversa, duplicatas  
✅ **Automatize testes** com scripts bash  

---

## 📋 Checklist de Validação

```
□ Compila sem erros (make)
□ Testa com 3 números → OK
□ Testa com 5 números → OK
□ Testa com 100 números → OK
□ Testa com 500 números → OK
□ Rejeita duplicatas → Error
□ Rejeita não-números → Error
□ Números já ordenados → OK (sem operações)
□ Performance dentro dos limites da 42
```

---

## 🎨 Exemplo Visual

```
Terminal 1: Ver operações
$ ./push_swap 5 2 1 3 4
pb
pb
ra
pa
pa
...

Terminal 2: Validar
$ ./push_swap 5 2 1 3 4 | ./checker_linux 5 2 1 3 4
OK

Terminal 3: Contar
$ ./push_swap 5 2 1 3 4 | wc -l
25
```

---

## 🚀 Pronto para Testar!

Agora você pode:
1. Compilar: `make`
2. Testar: `./push_swap 3 2 1 | ./checker_linux 3 2 1`
3. Verificar: Se retornar `OK`, está funcionando! ✅

**Boa sorte!** 🎉
