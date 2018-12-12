cmake_minimum_required(VERSION 3.12)
project(ft_ssl)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CMAKE_C_FLAGS} -g -DDEBUG")

add_subdirectory(libft)

add_executable(${PROJECT_NAME}
		source/ft_md5.c
		source/ft_sha256.c
		source/ft_ssl.c
		source/main.c
		source/md5_helpers.c
		source/sha256_helpers.c
		source/ssl_flags.c
		source/ssl_print.c
		source/ssl_process.c)
target_link_libraries(${PROJECT_NAME} ft)
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_include_directories(${PROJECT_NAME} PRIVATE ${libft_INCLUDES})
