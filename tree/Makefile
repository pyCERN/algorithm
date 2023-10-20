CXX := g++
CPPFLAGS := --std=c++20

AVLTree: tree.o AVLTree.o treeMain.cpp
	$(CXX) $(CPPFLAGS) tree.o AVLTree.o treeMain.cpp -o AVLTree

AVLTree.o: AVLTree.h AVLTree.cpp
	$(CXX) $(CPPFLAGS) -c AVLTree.h AVLTree.cpp

tree.o: tree.h tree.cpp
	$(CXX) $(CPPFLAGS) -c tree.h tree.cpp

clean:
	rm -f *.o
	