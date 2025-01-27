# Interpreter Math C

Welcome to **Interpreter Math C**, a C program designed to evaluate mathematical expressions, manipulate variables, support mathematical functions, and display a history of previous calculations.

---

## 🚀 Features

- **Mathematical Expression Evaluation**:
  - Supports basic operations: `+`, `-`, `*`, `/`, `^`, `%`.
  - Supports logical operators: `&&` (AND), `||` (OR).
  - Factorial calculation using `!`.

- **Mathematical Functions**:
  - `sin(x)`, `cos(x)`, `tan(x)`, `log(x)`, `sqrt(x)`.

- **Variable Management**:
  - Define variables: `x = 5`.
  - Use variables in expressions: `x + 10`.

- **Calculation History**:
  - View the history of previous calculations.
  - Export the history to a `.txt` file.

- **Simple and User-Friendly Interface**:
  - Clear menus and commands to interact with the program.

---

## 🖥️ How to Use

### 🟢 Available Commands:
- `q` or `exit`: Exit the program.
- `help`: Display available operators and functions.
- `clear`: Clear the screen.
- `history`: View past calculations.
- `export`: Save the history to a file named `historical_calculations.txt`.

### 🟢 Usage Examples:
1. Basic operations:
   - `2 + 3 * 4`
   - `(2 + 3) * 4`
2. Mathematical functions:
   - `sin(pi/2)`
   - `sqrt(16)`
3. Defining variables:
   - `x = 10`
   - `y = x + 5`
4. Using constants:
   - `pi * 2`
   - `e^2`

---

## 🧩 Code Structure

### **Main Components**
1. **Stack Manipulation**:
   - Structures to manage numbers and operators.
2. **History**:
   - Stores the last 10 evaluated expressions and their results.
   - Exports the history to a file.
3. **Variables**:
   - Stores up to 10 variables.
   - Supports operations involving variables.
4. **Mathematical Functions**:
   - Includes support for functions like sine, cosine, logarithm, etc.

---

## 📄 History Export
The calculation history can be saved to a file called `historical_calculations.txt` for future reference. The file will contain all the evaluated expressions along with their results.

---

## ⚙️ Requirements
- C Compiler (e.g., GCC).
- Operating system: Windows, Linux, or macOS.

---

## 🛠️ Compilation and Execution

### **Compile**:
```bash
gcc -o interpreter_math_c main.c -lm
```

### **Run**:
```bash
./interpreter_math_c
```
