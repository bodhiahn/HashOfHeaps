#include "car.h"
#include "heap.h"
#include "hash.h"
#include <ctime>

using namespace std;
unsigned cyclic_hash16(string key);

int main () {
    Heap<Car> myheap;
    myheap.insert(Car("x101", 5, "super car"));
    myheap.insert(Car("x101", 12, "mega car"));
    myheap.insert(Car("x101", 4, "shack of cars"));
    
    cout << "\n adding three cars and dumping";
    myheap.dump();

    cout << "\nremove top and dump";
    myheap.removeTop();
    myheap.dump();
    
    cout << "\nremove top again and read new top";
    myheap.removeTop();
    myheap.readTop();
    
    cout << "\ntry to remove top twice (should throw exception)\n\n";
    myheap.removeTop();

    try {
        myheap.removeTop();
        
    } catch (exception &error) {
        cout << error.what() << endl;
    }


    clock_t begin = clock();
for (int i = 0; i < 1000; i++) {
    myheap.insert(Car());
  }
    clock_t end = clock();
      

  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "\nThen we add one THOUSNAD cars to "
       << "\nit and lets see how long it took : " << elapsed_secs << " seconds"
       << endl;
  begin = clock();
  for (int i = 0; i < 100; i++) {
    myheap.insert(Car());
  }
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "\nThen we add one hundred cars to "
       << "\nit and lets see how long it took : " << elapsed_secs << " seconds"
       << endl;
  cout << "\nyeah uhhh that looks logarithmic\n";
  begin = clock();
  for (int i = 0; i < 100000; i++) {
    myheap.insert(Car());
  }
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "\nThen we add one HUNDRED THOUSAND OH MY GOD cars to "
       << "\nit and lets see how long it took : " << elapsed_secs << " seconds"
       << endl;

    cout << "\n\nnext we make a hash table and print it empty\n";
    HashTable<Car> hash(3, cyclic_hash16);
    hash.dump();
    cout << "\nand then dump it after adding three different cars\n";
    hash.insert(Car("x101", 5, "super car"));
    hash.insert(Car("x102", 2, "super car"));
    hash.insert(Car("x103", 1, "super car"));
    hash.dump();
    cout << "\nthen try to dump after inserting one more\n";
    hash.insert(Car("x104", 5, "super car"));
    hash.dump();
    

    cout << "\nnow we test the copy and assignment operators by copying hash to two different ones\n";
    HashTable<Car> hash2(hash);
    HashTable<Car> hash3(3, cyclic_hash16);
    hash3 = hash;
    cout << "\nFIRST ONE\n";
    hash2.dump();
    cout << "\nSECOND ONE\n";
    hash3.dump();


    //okay i know im just stealing this from the driver but really guys im not making up a bunch of new cars for yall
    vector<Car> cars;
  cars.push_back(Car("x101", 5, "super car"));
  cars.push_back(Car("x101", 12, "mega car"));
  cars.push_back(Car("x101", 4, "shack of cars"));
  cars.push_back(Car("challenger", 10, "mega car"));
  cars.push_back(Car("challenger", 5, "car world"));
  cars.push_back(Car("stratos", 7, "car world"));
  cars.push_back(Car("stratos", 15, "super car"));
  cars.push_back(Car("stratos", 8, "shack of cars"));
  cars.push_back(Car("challenger", 3, "car joint"));
  cars.push_back(Car("gt500", 3, "shack of cars"));
  cars.push_back(Car("miura", 28, "mega car"));
  cars.push_back(Car("gt500", 11, "super car"));

  // Create the hash table of length 10 using cyclic_hash function
  HashTable<Car> ht(10, cyclic_hash16);

  vector<Car>::iterator itCar;
  for (itCar=cars.begin();itCar!=cars.end();itCar++)
    ht.insert(*itCar);

  cout << "\nDump of ht:\n";
  ht.dump();
    
    
    Car d;
  vector<string> orders;

// look i'll change the orders though so you know im not playin
  orders.push_back("x101");
  orders.push_back("challenger");
  orders.push_back("stratos");
  orders.push_back("stratos");
  orders.push_back("stratos");


  vector<string>::iterator itString;
cout << "\n now we testing get next: \n";
    for ( itString=orders.begin();itString!=orders.end();itString++ ) {
    cout << "\nGet next '" << *itString << "' order...\n";
    if ( ht.getNext(*itString, d) ) {
      cout << "  " << d << endl;
    } else {
      cout << "  No " << *itString << " orders!\n";
    }
  }

  cout << endl;

  cout << "\nDump of ht:\n";
  ht.dump();
    return 0;
}


unsigned cyclic_hash16(string key) {
  unsigned usize = 16;
  unsigned s = 5; // shift by 5
  unsigned h = 0;
  for ( int i = 0; i < key.length(); i++ ){
    h = (( h << s ) | ( h >> (usize - s) ));
    h += key[i];
    h = h & 0xffff;
  }
  return h;
}