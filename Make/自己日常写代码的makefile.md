# 自己日常写代码的makefile

## 1. 例子一

文件结构：

```bash
$ tree
.
├── makefile
├── stand.cpp
└── test.cpp

0 directories, 3 files
```

makefile文件：

```makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# 从cpp生成.o文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# 从.o文件生成可执行文件
%: %.o
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f *.o
```

执行`make test`

```bash
$ make test
g++ -std=c++11 -Wall -g    test.cpp   -o test

$ tree
.
├── makefile
├── stand.cpp
├── test
└── test.cpp

0 directories, 4 files
```

执行`make stand`

```bash
$ make stand
g++ -std=c++11 -Wall -g    stand.cpp   -o stand

$ tree
.
├── makefile
├── stand
├── stand.cpp
├── test
└── test.cpp

0 directories, 5 files
```

## 2. 例子二

文件结构：

```bash
$ tree
.
├── bin
├── makefile
├── stand.cpp
└── test.cpp

1 directory, 3 files
```

makefile文件：

```makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
BINDIR = ./bin

# 从cpp生成.o文件
$(BINDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# 从.o文件生成可执行文件
$(BINDIR)/%: $(BINDIR)/%.o
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f $(BINDIR)/*
```

执行`make ./bin/test`

```bash
$ make ./bin/test
g++ -std=c++11 -Wall -g -c -o bin/test.o test.cpp
g++ -std=c++11 -Wall -g -o bin/test bin/test.o
rm bin/test.o

$ tree
.
├── bin
│   └── test
├── makefile
├── stand.cpp
└── test.cpp

1 directory, 4 files
```

执行`make ./bin/stand`

```bash
$ make ./bin/stand
g++ -std=c++11 -Wall -g -c -o bin/stand.o stand.cpp
g++ -std=c++11 -Wall -g -o bin/stand bin/stand.o
rm bin/stand.o

$ tree
.
├── bin
│   ├── stand
│   └── test
├── makefile
├── stand.cpp
└── test.cpp

1 directory, 5 files
```

