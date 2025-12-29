cmake_minimum_required(VERSION 3.26)
project(KutuphaneYonetim C)

set(CMAKE_C_STANDARD 11)

add_executable(KutuphaneYonetim
        main.c
        kitap.c
        menu.c
        avl.c
        trie.c
        sort.c
        stack.c
        search.c
        filtre.c
        graph.c
        dosya.c
        gui.c
)

if (WIN32)
    target_link_libraries(KutuphaneYonetim user32 gdi32)
endif ()
