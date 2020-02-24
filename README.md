# Override

This school project is the last of a serie of 3 "introdution to Security" projects (see [SnowCrash](https://github.com/julienhache/SnowCrash) and [RainFall](https://github.com/julienhache/RainFall)).
Here is how it works:

- A Linux VM is provided, with several users.
- For each users, their is a way to access to the `.pass` file of the next user.
- The goal is to gain access to every user of the VM.

Override is focused on static analysis of the executables.
I learned to attack an executable with several approaches (Format String attack, Ret2Libc, shellcode injection ...) and to read assembly more efficiently.

---

The repo is built in the following form:
- For each user, there is a corresponding folder.
- You can find 3 files in a folder:
  - `flag`: the password to the next user,
  - `source.c`: a C-written approximation of the exploited executable,
  - `writeup.txt`: a quick explanation about how we found a correct exploit.

The virtual machine is not provided in this repo, because it is a property of the 42 School.
