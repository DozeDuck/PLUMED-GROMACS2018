PLUMED_RUNTIME_LOAD= "/home/dozeduck/workspace/PLUMED/lib/libplumedWrapper.a" -ldl  
PLUMED_STATIC_LOAD= "/home/dozeduck/workspace/PLUMED/lib/plumed/obj/kernel.o" "/home/dozeduck/workspace/PLUMED/lib/plumed/obj/PlumedStatic.o" -ldl  -lstdc++ -lgsl -lgslcblas -lz -ldl  -static -rdynamic -fopenmp 
PLUMED_SHARED_LOAD= "/home/dozeduck/workspace/PLUMED/lib/libplumed." -ldl  
PLUMED_RUNTIME_DEPENDENCIES=
PLUMED_STATIC_DEPENDENCIES= "/home/dozeduck/workspace/PLUMED/lib/plumed/obj/kernel.o" "/home/dozeduck/workspace/PLUMED/lib/plumed/obj/PlumedStatic.o"
PLUMED_SHARED_DEPENDENCIES= "/home/dozeduck/workspace/PLUMED/lib/libplumed."
