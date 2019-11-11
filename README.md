# doorbell
 
## send udp packets
echo -n "hello" > /dev/udp/192.168.178.44/5060
echo -n `date` > /dev/udp/192.168.178.49/5060
date && echo -n `date` > /dev/udp/192.168.178.49/5060
date && echo -n `date` > /dev/udp/172.20.10.3/5060

## filter packets
sudo tcpdump  -Al udp and host 192.168.178.49
sudo tcpdump  -Al udp and port 5060

## cppcheck
/Users/wkeller/Downloads/cppcheck-1.89/cppcheck --std=c++11 --platform=native --enable=all --inconclusive -i .pio/ -I ./lib/FSMachine/src/ -I ./lib/NetworkClient/src/ -I ./lib/Packet/src/ -I ./lib/Protocol/src/.

C:\Users\eedwoke\Downloads\cppcheck-1.89\cppcheck-1.89\cppcheck --std=c++11 --platform=native --enable=all --inconclusive -i .pio\ -I .\lib\FSMachine\src\ -I .\lib\NetworkClient\src\ -I .\lib\Packet\src\ -I .\lib\Protocol\src\ .

## echo server (UNIX)
ncat -v -l 5060 --keep-open --udp --exec "/bin/cat"

## unit test
pio test
pio test -e native
pio test -e native -i common
pio test -e native -f native

## pio version
pip uninstall platformio 
pip install -U "platformio<4.1" --user

## debug: esp-prog
JTAG    Board Pin	lolin    Description
1       VDD         3.3v     Positive Supply Voltage — Power supply for JTAG interface drivers
3       GND         GND      Digital ground
2       ESP_TMS     14       Test Mode State
4       ESP_TCK     13       JTAG Return Test Clock
6       ESP_TDO     15       Test Data Out
8       ESP_TDI     12       Test Data In

Program Board Pin   lolin
1       ESP_EN      EN
2       VDD         3.3v
3       ESP_TXD     TX
4       GND         GND
5       ESP_RXD     RX
6       ESP_IO      0