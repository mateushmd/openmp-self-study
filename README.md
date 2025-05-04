# OpenMP Self-Study

A self-study repository focused on learning parallel computing using the OpenMP API.

## Navigation Guide

1. [Fork-join pattern](./fork-join/) 
2. [Private resources](./private-resources)
3. [Map pattern](./map)
4. [Critical sections](./critical-sections)
5. [Reduce pattern](./reduce)

---

## Dependencies 

If you are using the `Nix` package manager, you can automatically resolve all dependencies by running the following command from the repository root:

```sh
nix-shell
```

---

## Compiling

Once dependencies are available (via `shell.nix` or your own `GCC` setup), you can compile a `C` source file with OpenMP support like this:

```sh
gcc example.c -o example -fopenmp
```

Replace `example.c` with the name of your source file.
