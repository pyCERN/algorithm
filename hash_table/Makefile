CXX := /depotbld/RHEL7.0/gcc-9.5.0/bin/g++
CPPFLAGS := --std=c++11

AVLTree: tree.o AVLTree.o treeMain.cc
	$(CXX) $(CPPFLAGS) tree.o AVLTree.o treeMain.cc -o AVLTree

AVLTree.o: AVLTree.h AVLTree.cc
	$(CXX) $(CPPFLAGS) -c AVLTree.h AVLTree.cc

tree.o: tree.h tree.cc
	$(CXX) $(CPPFLAGS) -c tree.h tree.cc

clean:
	rm -f *tree.o *Tree.o
