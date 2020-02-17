#include <iostream>
#include <fstream>
#include <string>
#include <vector>
 
using namespace std;
struct laptop {
    int id;
    string brand;
    int hdd;
    int ram;
    string cpu;
    float inch;
};
struct node {
    laptop data;
    node *min;
    node *max;
};
typedef vector<laptop> laptops;

class ParseFile {
    string path;
    laptops data;
    public: 
        ParseFile(string path) {
            this->path = path;
            data = this->parse();
        }
        laptops getData() {
            return this->data;
        }
        laptops parse() {
            ifstream file(path);
            laptops arr;
            laptop tmp;
            while(file >> tmp.id >> tmp.brand >> tmp.hdd >> tmp.ram >> tmp.cpu >> tmp.inch) 
                arr.push_back(tmp);
            file.close();
            return arr;
        }
    ~ParseFile() {
        data.clear();
    }
};
class Sort {
    laptops data;
    public:
        Sort(laptops data) {
            this->data = data;
        }
        laptops bubbleByRam() {
            for (int i = 0; i < data.size() - 1; i++)
                for (int j = 0; j < data.size()-i-1; j++) {
                    if (data[j].ram > data[j+1].ram) {
                        laptop tmp = data[j];
                        data[j] = data[j+1];
                        data[j+1] = tmp;
                    }
                }
            cout << "\n<========Bubble sort========>\n";
            return data;      
        }

};
class Search {
    laptops data;
    public:
        Search(laptops data) {
            this->data = data;
        }
        laptop binaryById(int id) {
            cout << "\n<========Binary Search========>\n";
            id = id -1;
            int leftBound = 0;
            int rightBound = data.size() - 1;
            while(true) {
                if (leftBound == id) return data[id];
                else if (rightBound == id) return data[id];
                int center = (rightBound - leftBound) / 2 + leftBound;
                if (center > id) rightBound = center;
                else leftBound = center;
            }
        }
        laptop fibonacciById(int id) {
            cout << "\n<========Fibonacci Search========>\n";
            int len = data.size();
            int fib1 = 1;
            int fib2 = 0;
            int fib = 1;
            int offset = -1;

            while (fib < len) {
                fib2 = fib1;
                fib1 = fib;
                fib = fib2 + fib1;
            }

            while (fib > 1) {
                int i = (offset+fib2 < len-1) ? offset+fib2 : len-1;
                
                if (data[i].id < id) {
                    fib = fib1;
                    fib1 = fib2;
                    fib2 = fib - fib1;
                    offset = i;
                } else if (data[i].id > id) {
                    fib = fib2;
                    fib1 = fib1 - fib2;
                    fib2 = fib - fib1;
                } else return data[i];
            }

            if (fib1 && data[offset+1].id == id) return data[offset+1];
            return data[0];
        }
        laptop sequentialByRam(int ram) {
            cout << "\n<========Sequential Search========>\n";
            for (laptop el:data) {
                if (el.ram == ram) return el;
            }
            return data[0];
        }
        laptop static arbore(node *head, int ram) {
            while (true) {
                int val = head->data.ram;
                if (val == ram) return head->data; 
                else if (val > ram) head = head->min;
                else head = head->max;
            }
        }

};
class Arbore {
    laptops data;
    node *head;
    public:
        Arbore(laptops data) {
            this->data = data;
            load();
        }
        void load() {
            head = new node;
            head->data = data[0];
            head->min = NULL;
            head->max = NULL;
            for (int i = 1;  i < data.size(); i++) {
                node *tmp = head;
                laptop val = data[i];
                while (true) {
                    if (tmp->data.ram < val.ram) {
                        if (tmp->max == NULL)  {
                            tmp->max = new node;
                            tmp = tmp->max;
                            tmp->data = val;
                            tmp->min = NULL;
                            tmp->max = NULL;
                            break;
                        } else tmp = tmp->max; 
                    } else {
                        if (tmp->min == NULL)  {
                            tmp->min = new node;
                            tmp = tmp->min;
                            tmp->data = val;
                            tmp->min = NULL;
                            tmp->max = NULL;
                            break;
                        } else tmp = tmp->min; 
                    }
                }
            }
        }
        node *getNode() {
            return head;
        }
};
void printHeader() {
    cout << "\nid\tbrand\thdd\tram\tcpu\tinch\n";
}
void printAll(laptops data) {
    printHeader();
    for (int i = 0; i < data.size(); i++) {
        cout << data[i].id  <<'\t' 
             << data[i].brand  <<'\t'
             << data[i].hdd  <<'\t'
             << data[i].ram  <<'\t'
             << data[i].cpu  <<'\t'
             << data[i].inch  <<'\n';

    }
}
void print(laptop data) {
    printHeader();
    cout << data.id  <<'\t' 
         << data.brand  <<'\t'
         << data.hdd  <<'\t'
         << data.ram  <<'\t'
         << data.cpu  <<'\t'
         << data.inch  <<'\n';
}


int main() {
    ParseFile file("./text.txt");
    laptops arr = file.getData();
    // Sort sort(arr);
    // Search search(arr);
    // printAll(sort.bubbleByRam());
    // print(search.binaryById(30));
    // print(search.fibonacciById(15));
    Arbore arbore(arr);
    node *head = arbore.getNode();
    print(Search::arbore(head, 52));
    return 0;
}