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

    // BMP k�p beolvas�sa a mem�ri�ba
    std::ifstream inputFile(inputFileName, std::ios::binary);
    // Ellen�rizd, hogy a f�jl megnyithat�-e
    if (!inputFile.is_open()) {
        std::cerr << "Hiba: A bemeneti f�jl nem nyithat� meg." << std::endl;
        return 1; // Visszat�r�si k�d hibak�d jelz�s�re
    }

    // F�jl hossz�nak meghat�roz�sa
    inputFile.seekg(0, std::ios::end);
    std::streamsize size = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    // Vektor l�trehoz�sa �s m�ret�nek be�ll�t�sa
    std::vector<unsigned char> imageData(size);
    if (inputFile.read(reinterpret_cast<char*>(imageData.data()), size)) {
        // Sikeres beolvas�s

        int width = *(int*)&imageData[18];
        int height = *(int*)&imageData[22];
        int imageSize = (width * height) * 3;

        // Sz�rke�rnyalatos konverzi�
        std::vector<unsigned char> outputImage(imageSize);
        convertToGreyscaleCPU(imageData, outputImage, width, height);

        // Kimeneti k�p ment�se BMP form�tumban
        std::ofstream outputFile(outputFileName, std::ios::binary);
        // BMP fejl�c m�sol�sa
        outputFile.write(reinterpret_cast<char*>(&imageData[0]), 54);
        // Sz�rke�rnyalatos k�p m�sol�sa
        outputFile.write(reinterpret_cast<char*>(outputImage.data()), imageSize);

        std::cout << "A sz�rke�rnyalatos k�p elk�sz�lt." << std::endl;
    }
    else {
        std::cerr << "Hiba: A bemeneti f�jl nem olvashat� be." << std::endl;
        return 1; // Visszat�r�si k�d hibak�d jelz�s�re
    }

    return 0;
}
