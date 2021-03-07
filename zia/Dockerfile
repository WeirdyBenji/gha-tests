FROM epitechcontent/epitest-docker:latest

WORKDIR /app/zia

RUN pip install conan --upgrade &&\
#conan remote add conan-center https://bintray.com/conan/conan-center &&\
conan remote add epitech https://bintray.com/epitech/public-conan &&\
#https://bintray.com/conan/bincrafters/public-conan &&\
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan &&\
conan profile new default --detect &&\
conan profile update settings.compiler.libcxx=libstdc++11 default

RUN mkdir build &&\
cd build &&\
conan install ../zia --build=missing &&\
cmake ../zia -G “Unix Makefiles” &&
RUN cmake --build .
RUN make tests_run >> result.txt
RUN make coverage >> result.txt