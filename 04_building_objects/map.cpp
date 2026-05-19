#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<string, int> mp;

    cout << "Testing map class\n";
    mp["z"] = 8;
    mp["z"] = 1;
    mp["y"] = 2;
    mp["b"] = 3;
    mp["a"] = 4;

    cout << "z = " << (mp.count("z") ? mp["z"] : 42) << endl;
    cout << "x = " << (mp.count("x") ? mp["x"] : 42) << endl;

    cout << "Iterate" << endl;
    for (auto cur = mp.begin(); cur != mp.end(); cur++)
        cout << " " << cur->first.c_str() << " = " << cur->second << endl;

    return 0;
}