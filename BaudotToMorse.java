import java.io.*;
import java.util.*;

public class BaudotToMorse {
    static Scanner in;
    static PrintWriter out;

    // '.' - 0
    // '-' - 1

    static byte[][] table = { {}, // CNTRL + SHIFT
            { 0 }, // E
            {}, // ENTER
            { 0, 1 }, // A
            {}, // SPACE
            { 0, 0, 0 }, // S
            { 0, 0 }, // I
            { 0, 0, 1 }, // U
            {}, // BACKSPASE
            { 1, 0, 0 }, // D
            { 0, 1, 0 }, // R
            { 0, 1, 1, 1 }, // J
            { 1, 0 }, // N
            { 0, 0, 1, 0 }, // F
            { 1, 0, 1, 0 }, // C
            { 1, 0, 1 }, // K
            { 1 }, // T
            { 1, 1, 0, 0 }, // Z
            { 0, 1, 0, 0 }, // L
            { 0, 1, 1 }, // W
            { 0, 0, 0, 0 }, // H
            { 1, 0, 1, 1 }, // Y
            { 0, 1, 1, 0 }, // P
            { 1, 1, 0, 1 }, // Q
            { 1, 1, 1 }, // O
            { 1, 0, 0, 0 }, // B
            { 1, 1, 0 }, // G
            {}, // NUMBERS
            { 1, 1 }, // M
            { 1, 0, 0, 1 }, // X
            { 0, 0, 0, 1 }, // V
            {} // CNTRL + SHIFT
    };

    public static void main(String[] args) {
        in = new Scanner(System.in);
        out = new PrintWriter(System.out);

        solve();

        in.close();
        out.close();

    }

    private static void solve() {
        String str = in.next();

        while (str.length() == 5) {
            baudotToMorse(str);

            str = in.next();
        }
    }

    private static void baudotToMorse(String st) {
        byte[] str = new byte[5];

        for (byte i = 0; i < 5; i++) {
            str[i] = (byte) (((char) st.charAt(i) == '0') ? 0 : 1);
        }

        byte number = 0;
        byte power = 16;

        for (byte i = 0; i < 5; i++) {
            number += str[i] * power;
            power /= 2;
        }

        for (byte c : table[number]) {
            out.print(c == 1 ? "-" : ".");
        }

        out.println();
        out.flush();
    }
}