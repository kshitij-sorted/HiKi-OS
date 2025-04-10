# kernel
Building Kernel from scratch .. cause why not do hard stuff... ehehehee


# How To Run A Assembly File
1. write the code in your code editor .. nano / vim / vscode
2. open terminal / if in vs code click (ctrl + `)
3. nasm -f elf64 -o {file-name}.o {file-name}.asm
4. ld {file-name}.o -o {file-name}
5. ./{file-name}
