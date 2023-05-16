void f() {}

void g();

extern "C"
{
    void ef() {}

    void eg();
}

/* Prevent g and eg from being optimized away. */
void h() {
    g();
    eg();
}
