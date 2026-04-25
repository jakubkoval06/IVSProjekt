# IVS Calculator {#mainpage}

A team C++ project for VUT FIT, focused on the development of a simple calculator application and the teamwork behind it.

---

## Components

| Module | Description |
|--------|-------------|
| **math_lib** | Arithmetic library (add, subtract, multiply, divide, factorial, power, root, sum) |
| **parser** | Parser for longer math input (1+2-3*5), returns final evaluation|
| **stddev** | Profiling program — reads numbers from stdin and computes sample standard deviation using math_lib |
| **gui** | Qt GUI for the calculator|
| **math_lib_tests** | Google Test unit tests covering every math_lib function, including edge cases and expected exceptions. |

---

## Build
```
    make         - Build calculator + stddev
    make help    - Show available targets
    make run     - Run the calculator
    make stddev  - Build stddev program
    make test    - Run math library tests
    make doc     - Generate Doxygen docs
    make pack    - Create submission zip
    make clean   - Remove build files
```

---

## Dependencies

- Qt6
- Google Test
- Doxygen
- GNU Make

---

---

## Authors

**Team:** Bear_Together_Stronk

- Patrik Kadleček   (xkadlep01)
- Jakub Ferenčík    (xferenj00)  
- Jakub Kovaľ       (xkovalj00) 
