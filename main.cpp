#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
//int array[1000][1000] isn't good in big number and have memory
//problem i use unsingned 

class rectangle
{
	public:

 
    int random(int min, int max) 
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) );  
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}
vector<pair<ui, ui>> findpairs(ui n) {
    vector<pair<ui, ui>> array;
    
    for (ui k = 1; k <= n; ++k) {
        if (k * (n / k) == n)  
            array.push_back(make_pair(1, n / sqrt(k)));
    }
    
    return array;
}
vector<pair<ui, ui>> findpairsgready(ui n) {
    vector<pair<ui, ui>> array;
    
    for (ui k = 1; k <= n; ++k) {
            if (k * (n / k) == n) //we need to sure k ,n/k is proper form of number
               array.push_back(make_pair(k, random(n,k)));
     
    }
    
    return array;
}
 
vector<pair<ui, ui>> find_allpairs(ui min, ui max) {
    vector<pair<ui,ui>> array;
    
    for (ui i = max; i >= min; --i) {
        auto tmp = findpairs(i);
       
        array.insert(end(array), begin(tmp), end(tmp));
    }
    
    return array;
}
vector<pair<ui, ui>> find_allpairsgreedy(ui min, ui max) {
    vector<pair<ui,ui>> array;
    
    for (ui i = max; i >= min; --i) {
        auto tmp = findpairsgready(i);
        
        
        
         array.insert(end(array), begin(tmp), end(tmp));
    }
    
    return array;
}
};
class Sl {
public:
    pair<ui, ui> rows;
    pair<ui, ui> cols;
    
    Sl(ui row_i, ui row_f, ui col_i, ui col_f) : rows(make_pair(row_i, row_f)), cols(make_pair(col_i, col_f)) {}
    
    friend ostream & operator<<(ostream & out, const Sl & s) {
        out << s.rows.first << " " << s.cols.first << " " << s.rows.second << " " << s.cols.second;
        return out;
    }
};

class Piz {
private:
    ui rows;
    rectangle s;
    ui cols;
    ui min_ings;	 
    ui max_cells;	  
    vector<string> contents; 
    vector<Sl> sls;
    vector< vector<bool> > visited;
    
    void markVisited(ui ri, ui rf, ui ci, ui cf) {
        for (ui row = ri; row <= rf; ++row) {
            for (ui col = ci; col <= cf; ++col) {
                visited[row][col] = true;
            }
        }
    }
    
    bool isValid(ui ri, ui rf, ui ci, ui cf) const {
        if (ri > rf || ci > cf || rf >= rows || cf >= cols)
            return false;
        
        ui tomatoes = 0, mushrooms = 0;
        
        for (ui row = ri; row <= rf; ++row) {
            for (ui col = ci; col <= cf; ++col) {
                if (visited[row][col]) {
                    return false;
                }
                if (contents[row][col] == 'T')
                    tomatoes++;
                else if (contents[row][col] == 'M')
                    mushrooms++;
            }
        }
        
        return (tomatoes >= min_ings && mushrooms >= min_ings);
    }
    
public:
    Piz(ifstream & ifs) {
        ifs >> rows >> cols >> min_ings >> max_cells;
        ifs.ignore(3, '\n');
        
        string line;
        for (ui i = 0; i < rows; ++i) {
            getline(ifs, line);
            contents.push_back(line);
        }
        
        visited = vector<vector<bool>>(rows, vector<bool>(cols, false));
    }
    
    friend ostream & operator<<(ostream & out, const Piz & p) {
        out << p.sls.size() << endl;
        
        for (const Sl & s : p.sls)
            out << s << endl;
        
        return out;
    }
    
 void divide() {
        sls.clear();
        auto sizes = s. find_allpairs(min_ings * 2, max_cells);
        bool finished = false, inner_finished = false;
        
        ui row = 0, col = 0;
        while (! finished) {
            
            while (! inner_finished) {
                if (col < cols && row < rows && visited[row][col] == false) {
                    inner_finished = true;
                    break;
                }
                if (col < cols)
                    col++;
                else if (row < rows) {
                    row++;
                    col = 0;
                }
                else {
                    finished = inner_finished = true;
                    break;
                }
            }
            
            for (auto choice : sizes) {
                if (! isValid(row, row + choice.first - 1, col, col + choice.second - 1))
                    continue;
                
                sls.emplace_back(row, row + choice.first - 1, col, col + choice.second - 1);
                markVisited(row, row + choice.first - 1, col, col + choice.second - 1);
                break;
            }
            col++;
            
            inner_finished = false;
        }
    }
    void divideg() {
        sls.clear();
        auto sizes = s. find_allpairsgreedy(min_ings * 2, max_cells);
        bool finished = false, inner_finished = false;
        
        ui row = 0, col = 0;
        while (! finished) {
            
            while (! inner_finished) {
                if (col < cols && row < rows && visited[row][col] == false) {
                    inner_finished = true;
                    break;
                }
                if (col < cols)
                    col++;
                else if (row < rows) {
                    row++;
                    col = 0;
                }
                else {
                    finished = inner_finished = true;
                    break;
                }
            }
            
            for (auto choice : sizes) {
                if (! isValid(row, row + choice.first - 1, col, col + choice.second - 1))
                    continue;
                
                sls.emplace_back(row, row + choice.first - 1, col, col + choice.second - 1);
                markVisited(row, row + choice.first - 1, col, col + choice.second - 1);
                break;
            }
            col++;
            
            inner_finished = false;
        }
    }
    
    void getbestscore() const {
        ui score = 0;
        for (ui r = 0; r < rows; ++r) {
            for (ui c = 0; c < cols; ++c) {
                if (visited[r][c])
                    score++;
            }
        }
        ui sliced = 0;
        for (const auto & s : sls) {
            sliced += (s.rows.second - s.rows.first + 1) * (s.cols.second - s.cols.first + 1);
        }
        
        cout << "score: " << score << endl;
        cout << "SLICED:" << score << endl;
        cout << "TOTAL - SLICED:" << rows * cols - sliced << endl;
        cout << "TOTAL:" << rows * cols << endl << endl;
        cout << "Rows: " << rows << ". Cols: " << cols << ". MinIngs: " << min_ings << ". Max cells: " << max_cells << endl;
    }
};

class solver
{
	public:
	 string input="";
    string output ="";
	public:
	greedysolver()
	{
		 ifstream ifs (input);
    if (! ifs.is_open()) {
        cout << "Input file not found! Was \"" << input << "\"" << endl;
        return 0;
    }
    
    Piz p(ifs);
    p.divideg();
    ofstream ofs (output);
    ofs << p;
    
    p.getbestscore();
		
	}
	dynamicsolver()
	{
		 ifstream ifs (input);
    if (! ifs.is_open()) {
        cout << "Input file not found! Was \"" << input << "\"" << endl;
        return 0;
    }
    
    Piz p(ifs);
    p.divide();
    ofstream ofs (output);
    ofs << p;
    
    p.getbestscore();
		
	}
};

int main ( int argc, char * argv[] ) {
	solver s;
     if (argc != 1 + 2) {
        cout << "no correct form main <inputfile> <outputfile> now use default input output" << endl;
        s.input="d_big.in";
        s.output="d_big.out";

    }
    else
    {
    s. input .append(argv[1]);
    s. output .append(argv[2]);
    }
     s.greedysolver();
   
     return 0;
}