# Name of executable
PRODUCT := main.out

# Directories
BINDIR := bin
INCDIR := inc
SRCDIR := src
OBJDIR := obj

# Which compiler to use
CXX := g++
# Which linker to use
LINKER := g++
# In which directories should the compiler look for #include header files
# Default: ./inc/
INCDIRS := -I$(INCDIR)
# Compiler flags - INCLUDES DEBUGGING FLAG -g, for production remove this!
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -g
# Linker flags
# If you use SDL2, uncomment the following line
LINKERFLAGS := -lSDL2

# Basically 'ls ./src/*.cpp', returns a list of all cpp files in the src directory and saves it in SRCFILES
SRCFILES := $(wildcard $(SRCDIR)/*.cpp)
# 'Search-and-replace' the .cpp with .o/.d in the SRCFILES list of cpp files and saves the result in OBJFILES/DEPFILES
OBJFILES := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES))
DEPFILES := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.d,$(SRCFILES))

# Rules that make follows
# This rule (because it is the first rule in the makefile, it is the default rule, invoked when you simply type make at the command line prompt) says that the product we are trying to produce is dependent on the files in the list OBJFILES. It also says that to build the product Make needs to invoke the LINKER (i.e. g++) command. The special symbols $^ and $@ are special Make variables – the first evaluates to the list of dependencies, and the second to the name of the product. So, what this rule expands to when variable contents are used is for example:
#		main.out: main.o dice.o
#			g++ main.o dice.o -o main.out
$(BINDIR)/$(PRODUCT): $(OBJFILES)
	$(LINKER) $(CXXFLAGS) $^ -o $@ $(LINKERFLAGS)

# "A file with a .o suffix is dependent on a file with the same name, but with a .cpp suffix, and here’s how you build one from the other". This rule will be applied following the first rule if either main.o or dice.o needs to be re-built. With variable expansion, the command to do the re-build will be (for main.o):
#		g++ -std=c++11 -Wall -Wextra -I. -c main.cpp -o main.o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

# The last rule says how to use the –MM option of GCC to generate the .d dependency files. Here’s the command it produces (for main.d):
#		g++ -I. -MM main.cpp > main.d
# Here we use shell indirection to write the output the –MM option to a file. This generates a .d dependency files which looks like this:
#		main.o: main.cpp dice.h report.h
# which says that main.o is dependent on main.cpp, dice.h and report.h. A similar .d file is generated for the dice.cpp source file.
$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
	$(CXX) $(INCDIRS) -MM $< \
		| sed -e 's%^%$@ %' -e 's% % $(OBJDIR)/%'\ > $@

# Pulls in the .d files, much like #include works in a C or C++ program. However, this isn’t exactly what happens. If the .d files already exist, then they are simply included in the makefile, and Make reads the dependency information from them. However, if they don’t exist (as they won’t the first time Make is run using this makefile) Make will look to see if there is a rule to create them. There is (the last rule) so Make runs the command associated with that rule to create the .d files and then re-reads the whole makefile. This time the .d files do exist (because we just created them), so they are read by the simple include mechanism.
-include $(DEPFILES)

clean:
	rm $(OBJDIR)/*.{o,d}
	rm $(BINDIR)/main.out
