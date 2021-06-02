

void setup() {
 Serial.begin(9600);

}

void loop() {
  static char buffer[1024];
    static size_t length = 0;
  if (Serial.available() > 0) {
    // read the incoming byte:
    char c = Serial.read();

        // On carriage return, process the received data.
        if (c == '\r') {
            Serial.println();  // echo

            // Properly terminate the string.
            buffer[length] = '\0';

            // Convert the hex data to a byte array.
            size_t byte_count = length/2;
            uint8_t data[byte_count];
            hex2bin(data, buffer, &byte_count);

            // Echo back the byte array in hex.
            for (size_t i = 0; i < byte_count; i++) {
                Serial.print(data[i], HEX);
                Serial.print(" ");
            }
            Serial.println();

            // Reset the buffer for next line.
            length = 0;
        }

        // Otherwise buffer the incoming byte.
        else if (length < sizeof buffer - 1) {
            Serial.write(c);  // echo
            buffer[length++] = c;
        }
  }

}


static void hex2bin(uint8_t *out, const char *in, size_t *size)
{
    size_t sz = 0;
    while (*in) {
        while (*in == ' ') in++;  // skip spaces
        if (!*in) break;
        uint8_t c = *in>='a' ? *in-'a'+10 : *in>='A' ? *in-'A'+10 : *in-'0';
        in++;
        c <<= 4;
        if (!*in) break;
        c |= *in>='a' ? *in-'a'+10 : *in>='A' ? *in-'A'+10 : *in-'0';
        in++;
        *out++ = c;
        sz++;
    }
    *size = sz;
}
