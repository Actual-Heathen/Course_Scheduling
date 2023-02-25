CC = clang++
CFLAGS = -g -Wall -o3 -o bin/courseScheduler

TARGET = resourceManager
SOURCES = source/$(TARGET).cpp source/course.cpp source/department.cpp source/engine.cpp source/instructor.cpp source/room.cpp

all: source/$(source)
	$(MAKE) clean
	mkdir bin
	$(CC) $(CFLAGS) $(SOURCES)

clean:
	$(RM) -r bin
