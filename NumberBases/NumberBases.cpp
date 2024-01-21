#include <iostream>
#include <string>
#include <math.h>
#include <cmath>

using namespace std;

int intBaseRBase10(int intNumber, int base);
string intBase10BaseS(int intNumber, int base);
double doubleBaseRBase10(int intNumber, double doubleNumber, int base, int maxDigitos);
string doubleBase10BaseS(int intNumber, double doubleNumber , int base, int maxDigitos);


int main()
{   
    // Declarando variables que ocuparemos en el proceso de conversión de las bases
    int opt, base, intNumber, maxDigits; 
    double number, doubleNumber;

    do
    {
        cout << "\n====== CONVERSOR DE BASES NUMERICAS ======" << endl;

        cout << "\n=== Menú principal ===" << endl;
        cout << "1. Convertir un Entero Base R a Base 10 " << endl;
        cout << "2. Convertir un Entero Base 10 a Base S " << endl;
        cout << "3. Convertir un Entero Fraccionario Base R a Base 10 " << endl;
        cout << "4. Convertir un Entero Fraccionario Base 10 a Base S " << endl;
        cout << "5. Salir " << endl;

        cout << "\nIngrese la operación a realizar: "; // Recibiendo la opción elegida
        cin >> opt;

        if (opt > 0 & opt < 5){  // si la opción elegida esta dentro de los parametros 1,2,3,4 pedimos los datos  
            cout << "\n=== Ingresando Datos ==="; // para realizar la conversión correspondiente
            if (opt == 1 || opt == 3){
                cout << "\n Ingrese el numero: "; cin >> number;
                cout << " Ingrese la base del numero: "; cin >> base;
            }else{
                cout << "\n Ingrese el numero en base 10: "; cin >> number;
                cout << "Ingrese la base a la que desea convertir: "; cin >> base;
            }
            // Damos por hecho que se ingresa un numero decimal
            intNumber = static_cast<int>(number);  // Extraemos la parte entera del numero decimal
            doubleNumber = number - intNumber;  // Restando el numero con la parte entera obtenemos la parte decimal
        }

        switch (opt) { 
            case 1: {  // Convertimos un número base R a vase 10. 
                int result = intBaseRBase10(intNumber, base); // Procedemos con la conversion
                cout << "\nNumero en Base 10: " << result << endl; // Entregamos resultados 
                break;
            }
            case 2: {  // Convertimos un número base 10 a vase R. 
                string result = intBase10BaseS(intNumber,base); // Procedemos con la conversion 
                cout << "\nNumero en Base " << base << ": " << result << endl; // Entregamos resultados
                break;
            }
            case 3: {  // Convertimos un número decimal base R a base 10 
                cout << "Cuantos decimales desea tomar: "; cin >> maxDigits;
                double result = doubleBaseRBase10(intNumber, doubleNumber, base, maxDigits); // Procedemos con la conversion
                cout << "\nNumero en Base 10: " << result << endl; // Entregamos resultados

                break;
            }
            case 4: {  // Convertimos un número decimal base 10 a base R
                cout << "Cuantos decimales desea tomar: "; cin >> maxDigits;
                string result = doubleBase10BaseS(intNumber,doubleNumber, base, maxDigits); // Procedemos con la conversion
                cout << "\nNumero en Base " << base << ": " << result << endl; // Entregamos resultados

                break;
            }
            case 5: { // Salida del programa
                cout << "\nSaliendo del programa. Hasta luego." << endl;
                break;
            }
            default: { // La opción no esta disponible, retornamos mensaje. 
                cout << "\nOpción no válida, intente de nuevo" << endl;
                break;
            }
        }

    } while (opt != 5 ); // Mantenemos el programa mientras no se decida salir del mismo

    return 0;
    
}
// Convertimos un número base R a vase 10
int intBaseRBase10(int intNumber, int base){
    int convertedNumber = 0, exp = 0;

    while (intNumber > 0) { // Mientras el numero sea mayor a cero precedemos: 
        int digit = intNumber % 10;  // Obtenemos el último dígito del numero 
        convertedNumber += digit * pow(base, exp); // Ese digito lo multiplicamos por la base elevada a un exponente
        intNumber /= 10; // Dividimos entre 10, para deshacernos de ese último dígito utilizado
        exp++;  // Aumentamos el exponente
    }
    return convertedNumber; // Retornamos el numero ya convertido
}
// Convertimos un número base 10 a vase R.
string intBase10BaseS(int intNumber, int base) {
    string convertedNumber = "";

    while (intNumber > 0) { // Mientras el numero entero sea mayor a cero procedemos: 
        int waste  = intNumber % base; // Obtenemos el residou del modulo entre numero y la base.
        convertedNumber = to_string(waste) + convertedNumber; // Ese resuido lo convertimos en string y agregamos al resultado
        intNumber/= base;  // Dividimos el numero por la base, esto para obtener el siguiente residuo 
    }
    return (convertedNumber == "") ? "0" : convertedNumber;  // Retornamos el numero ya convertido
}
// Convertimos un número decimal base R a base 10 
double doubleBaseRBase10(int intNumber, double doubleNumber, int base, int maxDigits) {
    double convertedNumber, exp = maxDigits;
    // convertimos el numero decimal a entero dependiendo de la cantidad de decimales a redondear
    int decimalNumber = doubleNumber * pow(10, maxDigits); 

    for (int i = 1; i <= maxDigits; i++) { // Repetimos por cantidad de decimales a tomar
        int digit = decimalNumber % 10;  // Obtenemos el dígito del numero
        convertedNumber += digit / pow(base, exp); // Ese digito lo dividos por la base elevada al exponente máximo
        decimalNumber /= 10; // Nos deshacemos de ese último digito
        exp--; // El exponente comienza por el más grande al más pequeño, diminuimos el exponente
    }

    // Mandamos a convertir la parte entera del numero, posterior a ello le sumamos la parte decimal convertida
    convertedNumber = intBaseRBase10(intNumber, base) + convertedNumber; 
    return convertedNumber; // Retornamos el numero ya convertido
}
// Convertimos un número decimal base R a base 10 
string doubleBase10BaseS(int intNumber, double doubleNumber , int base, int maxDigits){
    // Mandamos a convertir la parte entera y le agregamos el punto decimal
    string convertedNumber = intBase10BaseS(intNumber,base) + ".";

    for (int i = 0; i < maxDigits; ++i) { // Repertimos de acuerdo el numero de decimales a redondear
        doubleNumber *= base;  // Multiplicamos la Base por el numero decimal
        int intNumber = static_cast<int>(doubleNumber);  // Obtenemos la parte entera del producto
        convertedNumber += to_string(intNumber); // convertimos el resultado en string y agregamos al resultado
        doubleNumber -= intNumber; // Restamos el decimal por la parte obtenida en el proceso
    }

    return convertedNumber;  // Retornamos el numero ya convertido
}
