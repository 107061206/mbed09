#include "mbed.h"
#include "mbed_rpc.h"

RpcDigitalOut myled1(LED1,"myled1");
RpcDigitalOut myled3(LED3,"myled3");
Serial pc(USBTX, USBRX);
void LEDControl(Arguments *in, Reply *out);
RPCFunction rpcLED(&LEDControl, "LEDControl");

int main() {
     
    char buf[256], outbuf[256];
    while(1) {
        memset(buf, 0, 256);
        for (int i = 0; ; i++) {
            char recv = pc.getc();
            if (recv == '\r') {
                pc.printf("\r\n");
                break;
            }

            buf[i] = pc.putc(recv);
        }

         
        RPC::call(buf, outbuf);
        pc.printf("%s\r\n", outbuf);
    }
}

void LEDControl (Arguments *in, Reply *out)   {
    bool success = true;

    char buffer[200], outbuf[256];
    char strings[20];
    int led = 1;
    int on = 1;
    int n;
    for (int i = 0; i < 50; i++){
        led = 1;
        on = 1;
        n = sprintf(strings, "/myled%d/write %d", led, on);
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control.");
        }
        wait(0.5);
        on = 0;
        n = sprintf(strings, "/myled%d/write %d", led, on);
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control.");
        }
        led = 3;
        on = 1;
        n = sprintf(strings, "/myled%d/write %d", led, on);
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control.");
        }
        wait(0.5);
        on = 0;
        n = sprintf(strings, "/myled%d/write %d", led, on);
        strcpy(buffer, strings);
        RPC::call(buffer, outbuf);
        if (success) {
            out->putData(buffer);
        } else {
            out->putData("Failed to execute LED control.");
        }
    }
}
