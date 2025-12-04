# OS Lab 4 — Dynamic Libraries (WSL/Linux)

This lab demonstrates two implementations of contracts provided via shared libraries (`.so`) and two test programs:

- libv1.so: rectangle method for `SinIntegral` + bubble sort for `Sort`
- libv2.so: trapezoid method for `SinIntegral` + quicksort for `Sort`
- prog1: compile-time linked to one library (v1 by default)
- prog2: runtime loads/switches between `libv1.so` and `libv2.so`

## Build (WSL/Linux)

In WSL terminal:

```bash
make
```

Artifacts:
- `libv1.so`, `libv2.so`
- `prog1`, `prog2`

## Usage

Input format for both programs:
- `1 A B e`: computes integral of `sin(x)` on `[A,B]` with step `e`
- `2 n x1 x2 ... xn`: sorts `n` integers and prints the result
- Additionally for `prog2.exe`: `0` toggles implementation between `libv1.dll` and `libv2.dll`

### Examples

```powershell
# Program 1 (linked to libv1)
./prog1.exe
1 0 3.14159 0.01
2 5 5 3 4 1 2
```

```bash
./prog1
1 0 3.14159 0.01
2 5 5 3 4 1 2

./prog2
1 0 3.14159 0.01
0
1 0 3.14159 0.01
2 6 10 -1 5 0 7 2
```

You should see different integral results after toggling, reflecting rectangle vs trapezoid methods.

## Notes

- The functions use C linkage and are available via `dlsym`.
- `prog1` линкуется с `libv1.so` по умолчанию; чтобы линковаться с `libv2.so`, измените цель `prog1` в `Makefile` на `-lv2`.
- Step `e` must be positive; if `A > B`, the interval is swapped internally.
