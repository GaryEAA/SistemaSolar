# Sistema Solar en OpenGL

Simulación 3D con **OpenGL 3.3, GLFW, GLEW, GLM y stb_image** (mismo estilo que la clase). Incluye el Sol, los 8 planetas, la Luna y Plutón. La tecla **P** alterna entre el **sistema antiguo** (9 planetas, con Plutón) y el **moderno** (8 planetas): Plutón y su órbita se achican hasta desaparecer.

Cada cuerpo tiene textura, rotación (gira sobre su eje) y traslación (da vueltas al Sol; la Luna, a la Tierra). Hay órbitas, anillos en Saturno, estrellas, luz del Sol y cámara libre.

---

## Controles

| Tecla | Acción | Tarea |
|---|---|---|
| Mouse (clic izq.) / rueda | Girar / acercar la cámara | B4 |
| W S A D / Q E | Girar / acercar la cámara | B4 |
| 0 al 9, L | Seguir: Sol, Mercurio, Venus, Tierra, Marte, Júpiter, Saturno, Urano, Neptuno, Plutón, Luna | B4 |
| V / R | Vista general / reiniciar | B4 |
| Espacio, + / -, O | Pausa, velocidad, órbitas | B8 |
| P | Sistema antiguo / moderno | B9 |
| Esc | Salir | ya funciona |

## Cómo funciona

- Todo lo compartido está declarado en `src/Contratos.h`. La versión inicial trae una versión sencilla de cada parte, así que **cada tarea reemplaza la suya sin esperar a nadie**.
- **Ficha del cuerpo** (`struct Cuerpo`) y **estado global** (`estado()`: `tiempo`, `escalaTiempo`, `pausa`, `mostrarOrbitas`, `sistemaAntiguo`, `transicionPluton`).
- **Vértice** = 8 números: `x, y, z, r, g, b, u, v`. Mallas con `Malla3D` → `subirMalla(malla, primitiva)` → `dibujarObjeto`.
- **Shader:** uniforms `projection, view, model, textura, modo, emisivo, luzPos, brillo`. `modo`: `0` textura con luz, `1` color del vértice (órbitas, estrellas), `2` sin luz (anillos).
- **Tiempo comprimido:** vuelta al Sol `6·√(días/365,25)` s; giro `3·√(|horas|/24)` s.

## Cómo trabajamos

Nadie tiene partes asignadas: cada uno elige y reserva una tarea.

1. **Primera ronda:** cada uno toma una tarea de la **Parte A** (un cuerpo).
2. **Después:** quien termina su parte puede tomar otra de la **Parte A** o **B** (de arriba hacia abajo).
3. **Cada tarea solo toca sus archivos.** `Contratos.h`, `Sistema.h` y `Shader.*` no se tocan sin avisar. `SistemaSolar.cpp` solo en B12.
4. **Orden de subida:** cada persona sube una **rama por tarea** (`A4-tierra`, `B1-esfera`), que se une cuando está lista, tras compilar y ejecutar. No hay orden obligatorio entre tareas.

---

## Parte A: cuerpos (elegir uno)

Cada una consiste en llenar la ficha en `src/Cuerpo_X.h`, conseguir una imagen para su respectiva textura y guardarla en `res/Texture/` y comprobar que se ve bien.

| Dato de la ficha | Unidad | Significado |
|---|---|---|
| `radio` / `distancia` | escena | Tamaño / distancia al cuerpo que orbita |
| `periodoOrbital` | días | Una vuelta. `0` = no se mueve (Sol) |
| `periodoRotacion` | horas | Un giro sobre sí mismo |
| `inclinacionEje` | grados | Más de 90° = gira al revés |
| `inclinacionOrbita` | grados | Inclinación de la órbita |
| `faseInicial` | grados | Dónde empieza en la órbita |
| `padre` | índice | `TIERRA` para la Luna; por defecto el Sol |
| `emisivo` / `sincrona` | bool | Brilla solo (Sol) / siempre muestra la misma cara (Luna) |
| `rutaTextura` | texto | Ej. `"res/Texture/marte.jpg"` |

| Código | Cuerpo (archivo) | radio | distancia | orbital (días) | rotación (h) | eje (°) | órbita (°) | fase | Especial | Estado | Quién |
|---|---|---|---|---|---|---|---|---|---|---|---|
| A1 | Sol (`Cuerpo_Sol.h`) | 3,0 | 0 | 0 | 609 | 7,25 | 0 | 0 | `emisivo = true` | ✅ | Gary Añanga |
| A2 | Mercurio | 0,25 | 6 | 88 | 1407,6 | 0,03 | 7,0 | 40 | El más rápido en orbitar | ✅ | Jhon Velasquez |
| A3 | Venus | 0,48 | 8,5 | 224,7 | 5832,5 | 177,4 | 3,4 | 250 | Gira al revés (por el eje, no con tiempo negativo) | ✅ | Jhon Velasquez |
| A4 | Tierra | 0,5 | 11 | 365,25 | 23,93 | 23,4 | 0 | 120 | Continentes sin espejo | 🔄 | Jadhe Sotelo |
| A5 | Luna | 0,14 | 1,1 | 27,3 | — | 6,7 | 5,1 | 0 | `padre = TIERRA`, `sincrona = true` | 🔄 | Alejandra Galvez |
| A6 | Marte | 0,27 | 14 | 687 | 24,6 | 25,2 | 1,85 | 200 | | 🔄 | Jadhe Sotelo |
| A7 | Júpiter | 1,6 | 20 | 4333 | 9,93 | 3,1 | 1,3 | 300 | El que gira más rápido | ✅ | Jhon Velasquez |
| A8 | Saturno | 1,35 | 27 | 10759 | 10,7 | 26,7 | 2,5 | 70 | Anillos son la B6 | ✅ | Jadhe Sotelo |
| A9 | Urano | 0,85 | 33 | 30687 | 17,2 | 97,8 | 0,8 | 150 | Eje casi acostado | ✅ | Miguel Clavo |
| A10 | Neptuno | 0,82 | 38 | 60190 | 16,1 | 28,3 | 1,8 | 250 | | ⬜ | |
| A11 | Plutón | 0,18 | 43 | 90560 | 153,3 | 122,5 | 17,2 | 20 | Planeta enano; solo en modo antiguo | 🔄 | Alexander Gabino |

**Hecho cuando:** el cuerpo se ve con su imagen real, proporcionado, y gira y orbita como indica su fila.

**A12 Estrellas** (✅ libre) : "n" puntos repartidos parejo sobre una esfera de radio 400. *Hecho cuando* se ven estrellas quietas de distinto brillo al fondo.

---

## Parte B: sistema (tareas libres)

Las firmas ya están en `Contratos.h` y en cada archivo: **no cambiar nombres ni parámetros**, solo el cuerpo de la función.

| Código | Tarea | Archivo | Estado | Quién |
|---|---|---|---|---|
| B1 | Esfera | `Esfera.h` | ✅ | Gary Añanga |
| B2 | Texturas | `Texturas.h` | ✅ | Gary Añanga |
| B3 | Movimiento | `Movimiento.h` | ✅ | Gary Añanga |
| B4 | Cámara | `Camara.h` | ✅ | Gary Añanga |
| B5 | Órbitas | `Orbitas.h` | ✅ | Gary Añanga |
| B6 | Anillos | `Anillos.h` | ✅ | Jadhe Sotelo |
| B7 | Luz del Sol | `res/Shader/fragmentShader.glsl` | ✅ | Gary Añanga |
| B8 | Controles | `Controles.h` | ✅ | Jhon Velasquez |
| B9 | Modo antiguo/moderno | `ModoPluton.h` | ✅ | Gary Añanga |
| B10 | Título de ventana | `Titulo.h` | ✅ | Jhon Velasquez |

## Lista final

- [ ] Se ven el Sol, los 8 planetas, la Luna y (modo antiguo) Plutón; P funciona y el título indica el modo.
- [ ] Cada cuerpo tiene su imagen real, derecha y sin espejo.
- [ ] Rotación y traslación correctas; Venus, Urano y Plutón giran al revés.
- [ ] Anillos de Saturno con transparencia; estrellas y órbitas visibles.
- [ ] Cámara con mouse/teclado y seguimiento de cada cuerpo.
- [ ] Lado iluminado hacia el Sol, lado oscuro no negro total. (opcional)
- [ ] Espacio, `+`/`-` y O funcionan.
- [ ] Todo compila y ejecuta sin errores.
