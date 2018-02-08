** Install ** 
    mkdir build && cd build
	g++ -std=c++11 -fPIC -shared ../src/object_detector_class.cpp -o libobject_detector.so.1.0 -Wl,-soname=libobject_detector.so.1 -L XXX -lcaffe -I XXX -Wl,-rpath=XXX -lboost_system -lopencv_core -lopencv_highgui
	ldconfig -n .
    ln -s libobject_detector.so.1 libobject_detector.so
    g++ -std=c++11 ../src/demo.cpp -o demo1 -L. -lobject_detector -lopencv_core -lopencv_highgui
	
	mkdir /usr/local/include/objdet
	cp -r ../../include/api/* /usr/local/include/objdet
	cp ../src/object_detector_class.h /usr/local/include/objdet
	cp -d *.so.* /usr/local/lib/
