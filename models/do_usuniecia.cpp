#include<iostream>
#include<fstream>
using namespace std;


main(){
    
    fstream plik;
    plik.open("goniec.obj",std::ios::in);

    string dane;
    if(plik.good()) cout<<"udalo sie otworzyc plik"<<endl;
    else cout<<"nie udalo sie otworzyc pliku"<<endl;
    while(!plik.eof()){
        plik>>dane;
        cout<<dane<<endl;
        
    }
   
    plik.close();
}
