find USER -name \*.c -exec clang-format -i {} \;
find awtk-port -name \*.c -exec clang-format -i {} \;
find USER -name \*.h -exec clang-format -i {} \;
find awtk-port -name \*.h -exec clang-format -i {} \;

