#include<iostream>
#include<string>
using namespace std;
/**************************************
* Welcome to visit http://dna049.com
**************************************/
string a[20];
int main(){
a[0]="#include<iostream>";
a[1]="#include<string>";
a[2]="using namespace std;";
a[3]="/**************************************";
a[4]="* Welcome to visit http://dna049.com";
a[5]="**************************************/";
a[6]="string a[20];";
a[7]="int main(){";
a[8]="for(int i=0;i<8;++i) cout<<a[i]<<endl;";
a[9]="for(int i=0;i<=12;++i) cout<<char(97)<<char(91)<<i<<char(93)<<char(61)<<char(34)<<a[i]<<char(34)<<char(59)<<endl;";
a[10]="for(int i=8;i<=12;++i) cout<<a[i]<<endl;";
a[11]="return 0;";
a[12]="}";
for(int i=0;i<8;++i) cout<<a[i]<<endl;
for(int i=0;i<=12;++i) cout<<char(97)<<char(91)<<i<<char(93)<<char(61)<<char(34)<<a[i]<<char(34)<<char(59)<<endl;
for(int i=8;i<=12;++i) cout<<a[i]<<endl;
return 0;
}
