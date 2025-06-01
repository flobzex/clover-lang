import io;

// Validates escape sequences


fn main() {
    io.println("Hello,\n World!");
    io.println("\a\b\e\f\n\r\t\v\\\'\"");
    io.println('\x1b');
    io.println('\uabcd');
    io.println('\Uabcdef12');
}
