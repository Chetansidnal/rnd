### To compile and Run NodeA ,B , C

### For A

`g++ -std=c++14 -I/usr/local/include -L/usr/local/lib/ -I diaglib.o -o nodeA nodeA.cpp -lzmq -lpthread -ljsoncpp`

### For B

`g++ -std=c++14 -I/usr/local/include -L/usr/local/lib/ -I diaglib.o -o nodeB nodeB.cpp -lzmq -lpthread -ljsoncpp`

### For C

`g++ -std=c++14 -I/usr/local/include -L/usr/local/lib/ -I diaglib.o -o nodeC nodeC.cpp -lzmq -lpthread -ljsoncpp`