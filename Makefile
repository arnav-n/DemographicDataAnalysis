#CXX=clang++
CXX=g++

CXXFLAGS= -g -std=c++14 

BINARIES=dataProj testStats1 testStatsData1

all: ${BINARIES}

tests: ${BINARIES}
	./testStats1
	./testStatsData1

dataProj: placeData.o racialDemog.o rating.o stats.o comboHospitalData.o hospitalData.o comboDemogData.o demogData.o parse.o  main.o
	${CXX} $^ -o $@

testStats1: placeData.o racialDemog.o rating.o testStats1.o stats.o comboHospitalData.o hospitalData.o comboDemogData.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@

testStatsData1: placeData.o racialDemog.o rating.o testStatsData1.o stats.o comboHospitalData.o hospitalData.o comboDemogData.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@


clean:
	/bin/rm -f ${BINARIES} *.o 
