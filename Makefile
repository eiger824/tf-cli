CXX 	 := g++
CXXFLAGS := -Wall -Wextra -std=c++1z -g -lcurl

PROGRAMS := tf-monitor \
	tf-config \
	tf-query \
	tf-configdb

all: $(PROGRAMS)

deps:
	sudo apt install -y libcurl4-openssl-dev g++ jq

tf-monitor: cmd.cc monitor.cc common.cc url.cc
	$(CXX) -o $@ $^ $(CXXFLAGS)

tf-config: config.cc cmd.cc
	$(CXX) -o $@ $^ $(CXXFLAGS)

tf-query: query.cc cmd.cc
	$(CXX) -o $@ $^ $(CXXFLAGS)

tf-configdb: configdb.cc cmd.cc
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm -f $(PROGRAMS) *~ *exe
