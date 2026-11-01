# TP4: Trabajo Práctico Integrador

## Analizador léxico, sintáctico y semántico de C

El programa analiza un subconjunto de ANSI C (C89/C90) a partir de un archivo
fuente `.i` ya preprocesado. Utiliza Flex para el análisis léxico, Bison para
el análisis sintáctico y una tabla de símbolos para las validaciones semánticas.
El resultado se imprime en la salida estándar.

### Ficha técnica

- **Estándar del código de implementación:** GNU C11 (`-std=gnu11`).
- **Compilador de C utilizado:** `gcc`; en este equipo, el comando ejecuta Apple Clang.
- **Versión mínima del compilador de C probada:** Apple Clang 21.0.0.
- **Versión mínima de Flex probada:** 2.6.4.
- **Versión mínima de Bison probada:** 2.3.
- **Herramienta de construcción:** GNU Make, mediante `GNUmakefile`.

Estas son las versiones verificadas en este equipo; no se determinó si el
proyecto funciona con versiones anteriores.

### Compilación y uso

Desde la carpeta del TP4:

```bash
make all
./bin/tp4 tests/input/test_1.i
```

El ejecutable recibe exactamente una ruta de entrada. También se puede
analizar un archivo propio y guardar el reporte:

```bash
./bin/tp4 ruta/al/archivo.i > salida.txt
```

La entrada debe estar preparada para este analizador: sin comentarios ni
directivas de preprocesador. El archivo `archivo.i` de la raíz está vacío y
solo sirve como marcador; los ejemplos están en `tests/input/`.

### Reporte

La salida presenta, en este orden, variables declaradas, funciones declaradas
o definidas, errores semánticos, errores sintácticos y errores léxicos. Cuando
una sección no tiene elementos, muestra `-`. Los errores semánticos indican
línea y columna; los sintácticos, línea; y los léxicos, línea y columna.

### Pruebas

Después de compilar, ejecutar:

```bash
sh tests/run_testsuite.sh ./bin/tp4
```

La suite procesa los cinco archivos `tests/input/test_*.i`, guarda la salida
en `tests/output/` y la compara con `tests/output/expected/`. Para aprobar,
los cinco casos deben coincidir al 100% tras normalizar espacios y líneas
vacías. El porcentaje llamado "cobertura" por el script mide coincidencia de
salida, no cobertura de código.

### Archivos principales

- `src/scanner.l`: reconocimiento de tokens y errores léxicos.
- `src/parser.y`: gramática y recuperación de errores sintácticos.
- `src/semantic.c` y `src/symbol_table.c`: validaciones y tabla de símbolos.
- `src/report.c`: almacenamiento e impresión del reporte.
- `src/main.c`: lectura del archivo y ejecución del analizador.
