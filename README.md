# SundryCode

### Projects :
| Project             | ProjectBuildName | Desc                                  |
| :------------------ | :--------------- | :------------------------------------ |
| Finder              | FINDER           | Path find algorithm                   |
| TestDllSharedMemory | SHAREDMEM        |                                       |
| ParseCmdLine        | PCL              | Boost::program_options use example    |
| ProducerConsumer    | PC               | Multi thread concurrent queue example |
| Log                 | LOG              | spdlog                                |

### build:
```
mkdir build
cd build
cmake .. -D PNAME=ProjectBuildName [-D LIB=1]
cmake --build . -j 8
```

##### build TestDllSharedMemory :
```
mkdir build
cd build
#build lib
cmake .. -D PNAME=SHAREDMEM -D LIB=1
cmake --build . -j 8
#build exeutable (LIB=0 update cmake cache)
cmake .. -D PNAME=SHAREDMEM -D LIB=0
cmake --build . -j 8
```
