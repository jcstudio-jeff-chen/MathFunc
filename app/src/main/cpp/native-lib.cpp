#include <jni.h>
#include <string>

double _tuningFunc(double p, double q, double t, double x){
    return p*x/(q-t*x);
}

//通過 (0,0), (1,1) 及 (1-a, a) 的雙曲線
double tuningFunc(double a, double x){
    double p = a*a;
    double q = (1-a)*(1-a);
    double t = 1-2*a;
    return _tuningFunc(p, q, t, x);
}

//將 0 到 n-1 的整數對應至 0 到 1 的小數
double normalMapping(int n, int x){
    return (x + 0.5)/n;
}

//將 0 到 <1 的小數無條件捨棄為 0 到 n-1 的整數
double inverseNormalMapping(int n, double x){
    return int(x*n);
}

//建立快速存取表格
const int tableSize = 256;
double normalMappingTable[tableSize];
void initNormalMappingTable(){
    for(int i = 0; i < tableSize; i++){
        normalMappingTable[i] = normalMapping(tableSize, i);
    }
}

double tuningFuncTable[tableSize][tableSize];
double initTuningFuncTable(){
    for(int i = 0; i < tableSize; i++){
        double a = normalMappingTable[i];
        double p = a*a;
        double q = (1-a)*(1-a);
        double t = 1-2*a;
        for(int j = 0; j < tableSize; j++){
            double x = normalMappingTable[j];
            tuningFuncTable[i][j] = _tuningFunc(p, q, t, x);
        }
    }
}

double initAllMathFunc(){
    initNormalMappingTable();
    initTuningFuncTable();
}