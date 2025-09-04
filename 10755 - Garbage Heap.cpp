#include <iostream>
#include <climits>

using namespace std;

const int LIMITE = 21;
long long volumen[LIMITE][LIMITE][LIMITE];

long long mejorSubarray1D(long long secuencia[], int longitud) {
    long long sumaTemporal = 0;
    long long mejorSuma = LLONG_MIN;

    for (int i = 1; i <= longitud; ++i) {
        sumaTemporal += secuencia[i];
        mejorSuma = max(mejorSuma, sumaTemporal);

        if (sumaTemporal < 0) {
            sumaTemporal = 0;
        }
    }

    return mejorSuma;
}

long long mejorSubcubo3D(int ancho, int alto, int profundidad) {
    long long mejorResultado = LLONG_MIN;

    for (int iniX = 1; iniX <= ancho; ++iniX) {
        for (int finX = iniX; finX <= ancho; ++finX) {
            for (int iniY = 1; iniY <= alto; ++iniY) {
                for (int finY = iniY; finY <= alto; ++finY) {

                    long long colapsado[LIMITE];

                    for (int z = 1; z <= profundidad; ++z) {
                        long long acumulado = 0;

                        for (int x = iniX; x <= finX; ++x) {
                            for (int y = iniY; y <= finY; ++y) {
                                acumulado += volumen[x][y][z];
                            }
                        }

                        colapsado[z] = acumulado;
                    }

                    mejorResultado = max(mejorResultado, mejorSubarray1D(colapsado, profundidad));
                }
            }
        }
    }

    return mejorResultado;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int casos;
    cin >> casos;

    while (casos--) {
        int dimA, dimB, dimC;
        cin >> dimA >> dimB >> dimC;

        for (int i = 1; i <= dimA; ++i) {
            for (int j = 1; j <= dimB; ++j) {
                for (int k = 1; k <= dimC; ++k) {
                    cin >> volumen[i][j][k];
                }
            }
        }

        cout << mejorSubcubo3D(dimA, dimB, dimC) << '\n';

        if (casos > 0) cout << '\n';
    }

    return 0;
}
