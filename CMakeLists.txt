cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Назва проекту
project(start LANGUAGES CXX)

# Встановлення стандарту C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опція для використання статичних бібліотек
option(USE_STATIC "Use static library" ON)

# Вивід повідомлення про систему
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compile with static library? ${USE_STATIC}")

# Шлях до вихідних файлів

set(SOURCE_FILES
    src/main.cpp
    src/Wifi_Scanner/Wifi_Scanner.cpp
    src/Wifi_Scanner/getHomeDirectory.cpp
    src/Daemon/addToStartup.cpp
    src/Daemon/Daemon.cpp
    src/Daemon/removeFromAutostart.cpp
)


# Додавання виконуваного файлу
add_executable(start
    ${SOURCE_FILES}
)

# Компіляторні опції
target_compile_options(start
    PRIVATE
        -Wall -fPIC
)

# Підключення include-шляхів
target_include_directories(start
    PRIVATE
        include
        src/headers
        ${CMAKE_SOURCE_DIR}/lib/json
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CURL_INCLUDE_DIR}
)

# Лінкування бібліотек
target_link_libraries(start
    PRIVATE
        ${CURL_LIBRARY}
)

