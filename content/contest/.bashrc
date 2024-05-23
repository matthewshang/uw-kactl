function c() {
    g++ -Wall -Wconversion -Wfatal-errors -g -std=c++20 -fsanitize=undefined,address -o ${1}.exe ${1}.cpp
}
