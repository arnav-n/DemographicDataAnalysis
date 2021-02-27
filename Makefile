#CXX=clang++
CXX=g++

CXXFLAGS= -g -std=c++14 

BINARIES=dataProj testStats1 testStatsData1 testStatsData2 testPrint

all: ${BINARIES}

tests: ${BINARIES}
	./testStats1
	./testStatsData1
	./testStatsData2
	./testPrint

dataProj: statTool.o placeData.o rating.o stats.o comboHospitalData.o hospitalData.o comboDemogData.o demogData.o parse.o  main.o
	${CXX} $^ -o $@

testStats1: placeData.o rating.o testStats1.o stats.o comboHospitalData.o hospitalData.o comboDemogData.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@

testStatsData1: placeData.o rating.o testStatsData1.o stats.o comboHospitalData.o hospitalData.o comboDemogData.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@

testStatsData2: placeData.o rating.o testStatsData2.o stats.o comboHospitalData.o hospitalData.o comboDemogData.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@

testPrint: placeData.o rating.o testPrint.o stats.o comboHospitalData.o hospitalData.o comboDemogData.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o 
