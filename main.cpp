#include<bits/stdc++.h>
using namespace std;
class ride
{
	public:
	 int a,b,x,y,s,f;
	friend  ofstream & operator << (ofstream &out, const ride &c)
{
    out <<"ride is"<< c.a<<c.b<<c.x<<c.y<<c.s<<c.f;
 
    return out;
}
 
friend ifstream & operator >> (ifstream &in,  ride &c)
{
 
    in >> c.a>>c.b>>c.x>>c.y>>c.s>>c.f;
    
    return in;
}
	 
};
class solver
{
	public :
	 string input;
	 string output="";
	 int r,c,f,n,b,t;
	solver()
	{
		
	}
	void readinput() 
	{
		ifstream in(input);
		ofstream out(output);
		in>>r>>c>>f>>n>>b>>t;
		vector<ride> r(n);
		for(int i=0;i<n;i++)
		in>>r[i];
	}
};

int main ( int argc, char * argv[] ) {
	solver s;
     if (argc != 1 + 2) {
        cout << "no correct form main <inputfile> <outputfile> now use default input output" << endl;
        s.input="c_medium.in";
        s.output="small.out";

    }
    else
    {
    s. input .append(argv[1]);
    s. output .append(argv[2]);
    }
     s.readinput();
     return 0;
}
