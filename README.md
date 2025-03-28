# LZW Compression Algorithm

This project implements **LZW (Lempel-Ziv-Welch) compression and decompression** in C++.

It supports:
- **Linux/macOS**: Uses `Makefile` for compilation.
- **Windows**: Uses **Visual Studio (`.sln` file)**.

---

## **How to Build and Run**

---

### **Linux/macOS (Makefile)**
#### **Install g++ (if not installed)**
```sh
sudo apt install g++  # Debian/Ubuntu
sudo dnf install g++  # Fedora
brew install gcc      # macOS (Homebrew)
```

#### **Compile the Program**
```sh
make
```

#### **Run the Program**
```sh
./lzw_compressor.out
```

#### **Clean Compiled Files**
```sh
make clean
```

#### **Compile & Run in One Step**
```sh
make run
```

---

### **Windows (Visual Studio)**
#### **Install Visual Studio**
1. Download [Visual Studio](https://visualstudio.microsoft.com/)
2. During installation, select C++ development tools.

#### **Open the .sln File**
Open the `.sln` file located in the root of the repo.

#### **Build the Project**
Click **Build** > **Build Solution** (`Ctrl + Shift + B`).

#### **Run the Program**
Click **Debug** > **Start Without Debugging** (`Ctrl + F5`).

or

Click **Debug** > **Start Debugging** (`F5`).
