Originally written in 2023, published in 2025 for portfolio.

Example for encrypting the `.rodata` segment (can also encrypt any segment specified by the linker script) to hinder static analysis of ARM32 binaries. After compilation, encrypt.py will encrypt the rodata segment of the executable. On execution, the process will change the protections of rodata and decrypt before using any read only variables.

In dummy.cpp, we can see that it prints "Hello World!" after decryption. This string will be stored in rodata on compilation. So, if we encrypt `.rodata`, "Hello World" should no longer appear in the static binary.

# Comparison

`.rodata` segment before encryption:

<img width="646" height="303" alt="image" src="https://github.com/user-attachments/assets/962649c5-99a8-4a81-b560-4531eb762db3" />

`.rodata` segment after encryption:

<img width="668" height="314" alt="image" src="https://github.com/user-attachments/assets/a1a9e357-fd53-4867-b1e8-7e2d0c8613da" />

# How to Use

```
armv7a-linux-androideabi17-clang++.cmd -O0 -Wl,-T,sections.ld -o dummy dummy.cpp
g++ -shared -O2 -o encrypt.dll encrypt.cpp
python encrypt.py dummy out encrypt.dll
```
