# Copyright 2020 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

CC := clang
CXX := clang++
RM := rm -rf

CFLAGS := -g -Wall -Wno-deprecated-declarations -fPIC -std=c++11

# The following paths setting works for self-built libs from source code
# https://github.com/oneapi-src/oneCCL. If oneCCL package in oneAPI Toolkit is used,
# Should change paths to ${CCL_ROOT}/{include,lib}/cpu_icc instead
INCS := -I $(JAVA_HOME)/include \
        -I $(JAVA_HOME)/include/linux \
        -I ${CCL_ROOT}/include \
        -I $(DAALROOT)/include \
        -I ./javah \
        -I ./

# Use static link if possible, TBB is only available as dynamic libs
LIBS := -L${CCL_ROOT}/lib -lccl \
        -L$(DAALROOT)/lib/intel64 -l:libdaal_core.a -l:libdaal_thread.a \
        -L$(TBBROOT)/lib/intel64/gcc4.8 -ltbb -ltbbmalloc

CPP_SRCS += \
  ./OneCCL.cpp ./OneDAL.cpp ./service.cpp ./error_handling.cpp \
  ./KMeansDALImpl.cpp \
  ./PCADALImpl.cpp \
  ./ALSDALImpl.cpp ./ALSShuffle.cpp \
  ./NaiveBayesDALImpl.cpp \
  ./LinearRegressionDALImpl.cpp

OBJS += \
  ./OneCCL.o ./OneDAL.o ./service.o ./error_handling.o \
  ./KMeansDALImpl.o \
  ./PCADALImpl.o \
  ./ALSDALImpl.o ./ALSShuffle.o \
  ./NaiveBayesDALImpl.o \
  ./LinearRegressionDALImpl.o

# Output Binary
OUTPUT = ../../../target/libMLlibDAL.so

all: $(OUTPUT)

# Compile
%.o: %.cpp
	@echo 'Building file: $<'
	$(CXX) $(CFLAGS) $(INCS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Link
$(OUTPUT): $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(CXX) $(CFLAGS) -shared -o $(OUTPUT) $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

clean:
	@echo 'Cleaning up'
	-$(RM) $(OBJS) $(OUTPUT)
	-@echo ' '

.PHONY: all clean
