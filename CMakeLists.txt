cmake_minimum_required(VERSION 3.10)

# Proje Adı
project(EcommerceSystem)

# C++ Standardı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header (.h) dosyalarının nerede olduğunu belirtiyoruz
include_directories(include)

# Executable dosyasını src altındaki main.cpp ile oluşturuyoruz
add_executable(EcommerceSystem src/main.cpp)

# Çalıştırılabilir dosyanın 'data' klasörüne erişebilmesi için kopyalama işlemi
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})