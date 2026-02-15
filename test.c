void foo(void) __attribute__((shortcall));
void foo(void) {}
int main() { foo(); return 0; }
