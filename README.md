# Szürkeárnyalatos Kép Konverzió

Ez a projekt az **Adatpárhuzamos programozás** kurzus keretében készült, és egy CPU-alapú megoldást kínál bitmap képek szürkeárnyalatossá alakítására.

## Funkciók

- **Bitmap fájlok olvasása és írása**: A program képes BMP formátumú képek beolvasására és módosított képek mentésére.
- **Szürkeárnyalatos konverzió**:
  - A konverzió a következő egyenlet alapján történik:
    \
    int greyValue = 0.299f * inputImage[pixelIndex] + 0.587f * inputImage[pixelIndex + 1] + 0.114f * inputImage[pixelIndex + 2];
    \
  - A számítás minden pixelre külön történik.
- **CPU-alapú feldolgozás**:
  - A konverzió egyszerű, iteratív algoritmussal történik, amely minden pixel színértékét módosítja.

## Technológiák

### Nyelv
- **C++**

### Algoritmus
- **Szürkeárnyalatos konverzió**: Iteratív algoritmus, amely a színek fényességi értékei alapján számítja a szürkeárnyalatot.


## Használati Útmutató

1. **Bemeneti kép**:
   - Helyezd el a bemeneti BMP fájlt a program mappájában `inputc.bmp` néven.

2. **Futtatás**:
   - Indítsd el a programot. A kimeneti BMP kép `output.bmp` néven kerül mentésre a program futtatási mappájában.

3. **Eredmény**:
   - A konzolon megjelenik egy értesítés a sikeres konverzióról:
     ```
     A szürkeárnyalatos kép elkészült.
     ```

## Megjegyzések

- **BMP Formátum**: A program csak a 24 bites BMP formátumú képeket támogatja.
- **Fejléc**: A BMP fejléc az eredeti fájlból kerül átmásolásra, a pixeladatok viszont módosítottak.

## Licence

Ez a projekt az [MIT Licence](LICENSE) feltételei szerint használható és módosítható.
