project(BitMRC CXX)
cmake_minimum_required(VERSION 2.8.11) # 2.8.11 learned target_include_directories
include(GNUInstallDirs)
set(CRYPTOPP_INC ${CMAKE_SOURCE_DIR}/libcryptopp)
set(CRYPTOPP_SRC ${CMAKE_SOURCE_DIR}/libcryptopp)
set(CMAKE_VERBOSE_MAKEFILE false)
 
add_definitions("-DDEBUG_UQK")
 
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/include/cryptopp
 	${CMAKE_SOURCE_DIR}/BitMRC/include ${CMAKE_SOURCE_DIR}/BitMRC/Storage/include
 	/usr/include/c++/4.9.3 /usr/include/c++)

execute_process(COMMAND ${CMAKE_CXX_COMPILER} --version OUTPUT_VARIABLE CXX_VER)

if("${CXX_VER}" MATCHES " 4.9." OR  "${CXX_VER}" MATCHES " 5.")
	message("c++ version is okay")
else()
	message(FATAL_ERROR "\n***** ERROR: Need g++ >= 4.9 for this... (shared_timed_mutex)")
endif()
if(${CMAKE_SYSTEM} MATCHES "Linux")
	# TODO: check 'permissive' flag.
	add_definitions(-DLINUX -std=c++1y -fpermissive -o0 -ggdb)
	find_library(LIBCPPTEST_PATH NAMES cpptest libcpptest.a)
	if(${LIBCPPTEST_PATH} MATCHES NOTFOUND)
		message(FATAL_ERROR "\n***** ERROR: Need libcpptest-dev\n")
	endif()
else()
	# TODO: add windows definition
	# TODO: add find_library libcpptest for windows
endif()
#message("System Type ${CMAKE_SYSTEM} CXXVER IS : ${CXX_VER} CPPTEST is at ${LIBCPPTEST_PATH}")


include(ExternalProject)
ExternalProject_Add(libcryptopp 
		GIT_REPOSITORY https://github.com/weidai11/cryptopp.git
		# FOR TESTING: use a local bare repo
		#GIT_REPOSITORY ${CMAKE_SOURCE_DIR}/../libcryptopp.git
		PREFIX ${CRYPTOPP_SRC}
		BUILD_IN_SOURCE 1
		CONFIGURE_COMMAND cmake . -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/3rdparty/
		INSTALL_COMMAND make install PREFIX=${CMAKE_SOURCE_DIR}/3rdparty/
		STAMP_DIR ${CRYPTOPP_SRC}
		)
add_subdirectory(BitMRC)
#
# todo: move this to ccmake config 
# for now enable by cmake -DENABLE_TRIALS=1
if(${ENABLE_TRIALS})
  add_subdirectory(trial)
endif()

