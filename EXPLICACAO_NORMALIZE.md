# 📚 EXPLICAÇÃO DETALHADA: `normalize_values()`

## 🎯 Propósito

A função `normalize_values()` transforma os valores originais em **índices ordinais** (0, 1, 2, 3...), representando a posição relativa de cada número quando ordenados.

**Por quê?** O algoritmo Radix Sort trabalha melhor com números pequenos e sequenciais!

---

## 📝 Código

```c
void	normalize_values(t_stack *stack)
{
	t_stack	*current;
	t_stack	*compare;
	int		count;

	if (!stack)
		return;
	current = stack;
	while (current)
	{
		count = 0;
		compare = stack; 
		while (compare)
		{
			if (compare->value < current->value)
				count++;
			compare = compare->next;
		}
		current->index = count;
		current = current->next;
	}
}
```

---

## 🔍 Análise Linha por Linha

### 1️⃣ **Assinatura**
```c
void normalize_values(t_stack *stack)
```

**Entrada:** Ponteiro para o primeiro nó da stack  
**Saída:** Nenhuma (void) - modifica a stack diretamente  
**Efeito colateral:** Altera o campo `index` de cada nó

---

### 2️⃣ **Declaração de Variáveis**
```c
t_stack	*current;   // Nó sendo normalizado
t_stack	*compare;   // Nó usado para comparação
int		count;      // Contador de valores menores
```

---

### 3️⃣ **Proteção Contra NULL**
```c
if (!stack)
    return;
```

Se a stack está vazia, não há nada a normalizar.

---

### 4️⃣ **Loop Externo: Para cada nó**
```c
current = stack;
while (current)
{
    // ... processar current
    current = current->next;
}
```

Percorre **TODOS** os nós da lista, um por vez.

---

### 5️⃣ **Resetar Contador**
```c
count = 0;
```

Para cada nó, começamos contando do zero.

---

### 6️⃣ **Loop Interno: Comparar com todos**
```c
compare = stack;
while (compare)
{
    if (compare->value < current->value)
        count++;
    compare = compare->next;
}
```

**O que faz:**
- Percorre **TODA** a lista novamente
- Compara cada valor com o valor de `current`
- Se encontrar valor **menor**, incrementa `count`

**Resultado:** `count` = quantos valores são menores que `current->value`

---

### 7️⃣ **Atribuir Índice**
```c
current->index = count;
```

O índice é igual ao número de valores menores!

**Exemplo:**
- Se `count = 0` → nenhum valor menor → é o MENOR → índice 0
- Se `count = 1` → 1 valor menor → é o 2º menor → índice 1
- Se `count = 2` → 2 valores menores → é o 3º menor → índice 2

---

## 🎨 Exemplo Completo Passo a Passo

### Entrada:
```bash
./push_swap 42 21 84 63
```

### Stack inicial (após parse):
```
[42, -1] → [21, -1] → [84, -1] → [63, -1] → NULL
 │value    │value     │value     │value
 │index    │index     │index     │index
```

---

### Iteração 1: Normalizar o nó com value = 42

```c
current = [42, -1]  // Primeiro nó
count = 0

compare = [42, -1]  → 42 < 42? NÃO → count = 0
compare = [21, -1]  → 21 < 42? SIM → count = 1
compare = [84, -1]  → 84 < 42? NÃO → count = 1
compare = [63, -1]  → 63 < 42? NÃO → count = 1

current->index = 1  // 1 valor menor que 42
```

**Resultado parcial:**
```
[42, 1] → [21, -1] → [84, -1] → [63, -1]
 ✓ feito
```

---

### Iteração 2: Normalizar o nó com value = 21
 
```c
current = [21, -1]  // Segundo nó
count = 0

compare = [42, -1]  → 42 < 21? NÃO → count = 0
compare = [21, -1]  → 21 < 21? NÃO → count = 0
compare = [84, -1]  → 84 < 21? NÃO → count = 0
compare = [63, -1]  → 63 < 21? NÃO → count = 0

current->index = 0  // NENHUM valor menor que 21
```
 >> i) &
**Resultado parcial:**
```
[42, 1] → [21, 0] → [84, -1] → [63, -1]
          ✓ feito
```

---

### Iteração 3: Normalizar o nó com value = 84

```c
current = [84, -1]  // Terceiro nó
count = 0

compare = [42, -1]  → 42 < 84? SIM → count = 1
compare = [21, -1]  → 21 < 84? SIM → count = 2
compare = [84, -1]  → 84 < 84? NÃO → count = 2
compare = [63, -1]  → 63 < 84? SIM → count = 3

current->index = 3  // 3 valores menores que 84
```

**Resultado parcial:**
```
[42, 1] → [21, 0] → [84, 3] → [63, -1]
                    ✓ feito
```

---

### Iteração 4: Normalizar o nó com value = 63

```c
current = [63, -1]  // Quarto nó
count = 0

compare = [42, -1]  → 42 < 63? SIM → count = 1
compare = [21, -1]  → 21 < 63? SIM → count = 2
compare = [84, -1]  → 84 < 63? NÃO → count = 2
compare = [63, -1]  → 63 < 63? NÃO → count = 2

current->index = 2  // 2 valores menores que 63
```

**Resultado FINAL:**
```
[42, 1] → [21, 0] → [84, 3] → [63, 2] → NULL
 ✓         ✓         ✓         ✓
```

---

## 📊 Tabela Resumo

| Posição | Value | Menor que? | Count | Index | Significado |
|---------|-------|------------|-------|-------|-------------|
| 1ª | 42 | 21 | 1 | **1** | 2º menor valor |
| 2ª | 21 | nenhum | 0 | **0** | MENOR valor |
| 3ª | 84 | 21, 42, 63 | 3 | **3** | MAIOR valor |
| 4ª | 63 | 21, 42 | 2 | **2** | 3º menor valor |

### Ordenação conceitual:
```
21 (idx=0) < 42 (idx=1) < 63 (idx=2) < 84 (idx=3)
  menor                                   maior
```

---

## 🔄 Visualização do Processo

### Estado Inicial:
```
Stack:  42 → 21 → 84 → 63
Index:  -1   -1   -1   -1   (não normalizado)
```

### Depois da Normalização:
```
Stack:  42 → 21 → 84 → 63
Index:   1 →  0 →  3 →  2   (normalizado!)

Interpretação:
  42 é o 2º menor (1)
  21 é o 1º menor (0) 
  84 é o 4º menor (3)
  63 é o 3º menor (2)
```

---

## 💡 Por que Normalizar?

### ❌ SEM Normalização (usando valores originais):

**Problema com Radix Sort:**
```c
Valores: 42, 21, 84, 63
Bits necessários:
  84 em binário = 1010100 (7 bits!)
  Radix precisa iterar 7 vezes
```

### ✅ COM Normalização (usando índices):

**Eficiência:**
```c
Índices: 1, 0, 3, 2
Bits necessários:
  3 em binário = 11 (2 bits!)
  Radix precisa iterar apenas 2 vezes!
```

**Resultado:** Algoritmo **3.5x mais rápido**! 🚀

---

## 🧪 Mais Exemplos

### Exemplo 1: Números negativos
```
Input:    -5  10  -2   3
Values:   -5  10  -2   3
Índices:   0   3   1   2

Ordenação: -5 < -2 < 3 < 10
           0    1   2   3
```

### Exemplo 2: Números grandes
```
Input:     999  1  5000  42
Values:    999  1  5000  42
Índices:     2  0     3   1

Ordenação: 1 < 42 < 999 < 5000
           0   1    2     3
```

### Exemplo 3: Já ordenado
```
Input:    1  2  3  4  5
Values:   1  2  3  4  5
Índices:  0  1  2  3  4

Ordenação: já em ordem!
```

---

## ⚡ Complexidade

### Tempo: **O(n²)**
```c
while (current)           // n iterações
{
    while (compare)       // n iterações
    {
        if (...)          // O(1)
            count++;
    }
}
// Total: n × n = O(n²)
```

**Por que está OK:**
- Executado apenas UMA vez no início
- O Radix Sort depois é O(n × bits), muito mais eficiente
- Para n pequeno (< 1000), O(n²) é aceitável

### Espaço: **O(1)**
- Não aloca memória adicional
- Apenas modifica índices in-place

---

## 🔍 Casos Especiais

### 1. Stack vazia
```c
if (!stack)
    return;  // Não faz nada
```

### 2. Um único elemento
```c
Stack: [42, -1]

Iteração:
  compare [42] → 42 < 42? NÃO → count = 0
  
Resultado: [42, 0]  // Único elemento = índice 0
```

### 3. Todos iguais (nunca acontece - duplicatas são rejeitadas)
```c
// has_duplicates() impede isso
Stack: [5, 5, 5]  ❌ Erro antes de chegar aqui
```

---

## 🎓 Conceitos-Chave

| Conceito | Explicação |
|----------|------------|
| **Normalização** | Transformar valores em posições ordinais (0, 1, 2...) |
| **Índice Ordinal** | Posição relativa quando ordenado |
| **Loop Aninhado** | Loop dentro de loop = O(n²) |
| **Comparação** | < retorna quantos são menores |
| **In-place** | Modifica dados sem alocar memória extra |

---

## 🎯 Comparação Visual

### Antes da Normalização:
```
┌──────────────────────────────────────┐
│ Values: 42    21    84    63         │
│ Index:  -1    -1    -1    -1         │
│                                       │
│ ❌ Valores originais                 │
│ ❌ Não otimizado para Radix          │
└──────────────────────────────────────┘
```

### Depois da Normalização:
```
┌──────────────────────────────────────┐
│ Values: 42    21    84    63         │
│ Index:   1     0     3     2         │
│          ↓     ↓     ↓     ↓         │
│        2nd   1st   4th   3rd         │
│                                       │
│ ✅ Índices ordinais                  │
│ ✅ Otimizado para Radix Sort         │
│ ✅ Menos bits = mais rápido          │
└──────────────────────────────────────┘
```

---

## 🚀 Fluxo Completo no Programa

```
./push_swap 42 21 84 63
    ↓
1. Parse: cria stack com values
   [42,-1] → [21,-1] → [84,-1] → [63,-1]
    ↓
2. Normalize: calcula indices
   [42, 1] → [21, 0] → [84, 3] → [63, 2]
    ↓
3. Radix Sort: usa os índices para ordenar
   Bit 0: separa índices com bit 0 = 0/1
   Bit 1: separa índices com bit 1 = 0/1
    ↓
4. Resultado: stack ordenada
   [21, 0] → [42, 1] → [63, 2] → [84, 3]
```

---

## 💻 Teste de Mesa

### Input: `./push_swap 5 2 9 1`

| current | compare (todos) | value < current? | count | index final |
|---------|-----------------|------------------|-------|-------------|
| **5** | 5, 2, 9, 1 | não, sim, não, sim | 2 | **2** |
| **2** | 5, 2, 9, 1 | não, não, não, sim | 1 | **1** |
| **9** | 5, 2, 9, 1 | sim, sim, não, sim | 3 | **3** |
| **1** | 5, 2, 9, 1 | não, não, não, não | 0 | **0** |

**Resultado:**
```
Stack:  [5,2] → [2,1] → [9,3] → [1,0]
         ↓       ↓       ↓       ↓
Ordem:  3º      2º      4º      1º
```

---

## ❓ Perguntas e Respostas

### Q: Por que comparar com TODOS os elementos?
**A:** Para saber quantos são menores. É a única forma de determinar a posição ordinal.

### Q: E se houver duplicatas?
**A:** `has_duplicates()` é chamado antes, então nunca chegamos aqui com duplicatas.

### Q: Por que não ordenar diretamente?
**A:** O objetivo NÃO é ordenar, mas sim **atribuir índices** sem mover os nós.

### Q: O count pode ser igual ao value?
**A:** Não! Count é quantidade de menores (0 a n-1), value é o número original.

### Q: Posso otimizar para O(n log n)?
**A:** Sim, usando merge sort + reassign indices, mas O(n²) é aceitável aqui.

---

## 🏆 Resumo

**TL;DR:**
```
normalize_values():
  Para cada nó:
    conta = quantos valores são menores
    índice = essa contagem
    
Resultado: índices de 0 a n-1
```

**3 passos:**
1. 🔄 **Loop externo:** Para cada elemento
2. 🔍 **Loop interno:** Compara com todos
3. 📝 **Atribui:** index = count

**Usado para:** Preparar dados para o Radix Sort funcionar eficientemente!

---

**Analogia:** É como dar números de ordem de chegada numa corrida:
- 1º lugar = índice 0 (mais rápido)
- 2º lugar = índice 1
- 3º lugar = índice 2
- ...

Não importa o tempo real (values), importa a **posição relativa** (indices)! 🏃‍♂️🏃‍♀️🏃
