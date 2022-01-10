
EXEC = GtestDemo

XX = gcc
CPPXX = g++


C_SRCS = \
		
		
CPP_SRCS = \
		functions.cpp \
		functionsTest.cpp \
		TestAll.cpp 

CFLAGS = \
		-I./../gtest/include \
		-I./

LDFLAGS =  \
		  -L./../gtest/lib -lgtest \
		  -lpthread  \
		  -Wl,-rpath="./"


OBJS = $(C_SRCS:.c=.o) $(CPP_SRCS:.cpp=.o) 

#链接用g++编译器
start:$(OBJS)
	$(CPPXX) -o $(EXEC) $(OBJS) $(LDFLAGS)
	

.c.o:
	$(XX) $(CFLAGS) -o $@ -c $<	
	
.cpp.o:
	$(CPPXX) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)