#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// vectori mej kareli e pahel elementner arnc chapseri haytararman https://ru.wikipedia.org/wiki/Vector_(C%2B%2B)
vector<double> ScanX;
vector<double> ScanMethodRoots;
vector<double> BisectionMethodRoots;

double Epsilon;

double myFunction(double x){
    return pow(x,3) - 6 * x + 2;
}
void scanMethod(double range_start ,double range_end ){
    double sc_eps = Epsilon * 100;
    double x = range_start;
    double f1 = myFunction(x);
    double f2;
    int i = 0;
    while(x <= range_end){
        x += sc_eps;
        f2 = myFunction(x);
        if (f1 * f2 < 0){
            ScanX.push_back(x - sc_eps);
            ScanX.push_back(x);
            ScanMethodRoots.push_back((2 * x - sc_eps) / 2);
            i++;
        }
        f1 = f2;
    }
}

double solveBisectionMethod(double range_start ,double range_end){
    double root = (range_start + range_end) / 2;
    if (myFunction(root) < Epsilon)
        return root;

    if (myFunction(range_start)*myFunction(range_end))
        return solveBisectionMethod(root ,range_end);

    return solveBisectionMethod(range_start ,root);
}

void bisectionScanX(){
    for (int i = 0; i < ScanX.size() / 2 ; i++) {
        BisectionMethodRoots.push_back(solveBisectionMethod(ScanX[i],ScanX[i+1]));
    }
}
void roots(double a, double b){
    scanMethod(a ,b);
    bisectionScanX();
    cout << "ScanMethodRoots" << '\n';
    for(double i : ScanMethodRoots)
        cout << i << '\t';
    cout << '\n';
    cout << "BisectionMethodRoots" << '\n';
    for(double i : BisectionMethodRoots)
        cout << i << '\t';
}

int main() {
    int a , b;
    cin >> a >> b >> Epsilon;
    roots(a ,b);
    return 0;
}