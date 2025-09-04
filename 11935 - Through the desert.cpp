#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int gasto = 1; // Variable para controlar el bucle principal

int main() {
    
    while (gasto != 0){

        int km, gasto = 0, ultimo_fuel = 0;
        vector<int> leak;
        string evento, nada;
        vector<int> res;

        cin>> km >> evento >> nada >> gasto;
        
        while(evento != "Goal"){
            int tanque = 0;

            cin>> km >> evento;
            if (evento == "Leak") leak.push_back(km);

            if (evento == "Mechanic") {
                for (int i = 0; i < leak.size(); i++) tanque += km - leak[i];
                leak.clear();}

            if (evento == "Fuel") {
                cin>> nada;
                tanque += (km - ultimo_fuel) * gasto;
                ultimo_fuel = km;
                cin >> gasto;
            }

            if (evento == "Gas") {
                cin>> nada;
                for (int i = 0; i < leak.size(); i++) {
                    tanque += km - leak[i];
                    leak[i] = km;
                }
                res.push_back(tanque);
                tanque = 0;
            }
        }
    //ahora imprimo el maximo numero en res, redondeado a 3 decimales
    cout.precision(3);
    cout.setf(ios::fixed);
    cout<< *max_element(res.begin(), res.end()) << "." << endl;
    }
    return 0;
}