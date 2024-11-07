#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void convertToGreyscaleCPU(const std::vector<unsigned char>& inputImage, std::vector<unsigned char>& outputImage, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int pixelIndex = (y * width + x) * 3;
            int greyValue = 0.299f * inputImage[pixelIndex] + 0.587f * inputImage[pixelIndex + 1] + 0.114f * inputImage[pixelIndex + 2];
            outputImage[pixelIndex] = greyValue;
            outputImage[pixelIndex + 1] = greyValue;
            outputImage[pixelIndex + 2] = greyValue;
        }
    }
}


int main() {
    const std::string inputFileName = "inputc.bmp";
    const char* outputFileName = "output.bmp";

    // BMP kép beolvasása a memóriába
    std::ifstream inputFile(inputFileName, std::ios::binary);
    // Ellenõrizd, hogy a fájl megnyitható-e
    if (!inputFile.is_open()) {
        std::cerr << "Hiba: A bemeneti fájl nem nyitható meg." << std::endl;
        return 1; // Visszatérési kód hibakód jelzésére
    }

    // Fájl hosszának meghatározása
    inputFile.seekg(0, std::ios::end);
    std::streamsize size = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    // Vektor létrehozása és méretének beállítása
    std::vector<unsigned char> imageData(size);
    if (inputFile.read(reinterpret_cast<char*>(imageData.data()), size)) {
        // Sikeres beolvasás

        int width = *(int*)&imageData[18];
        int height = *(int*)&imageData[22];
        int imageSize = (width * height) * 3;

        // Szürkeárnyalatos konverzió
        std::vector<unsigned char> outputImage(imageSize);
        convertToGreyscaleCPU(imageData, outputImage, width, height);

        // Kimeneti kép mentése BMP formátumban
        std::ofstream outputFile(outputFileName, std::ios::binary);
        // BMP fejléc másolása
        outputFile.write(reinterpret_cast<char*>(&imageData[0]), 54);
        // Szürkeárnyalatos kép másolása
        outputFile.write(reinterpret_cast<char*>(outputImage.data()), imageSize);

        std::cout << "A szürkeárnyalatos kép elkészült." << std::endl;
    }
    else {
        std::cerr << "Hiba: A bemeneti fájl nem olvasható be." << std::endl;
        return 1; // Visszatérési kód hibakód jelzésére
    }

    return 0;
}
