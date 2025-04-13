CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lpigpio -lrt -lpthread

TARGET = fan_control
SRC = fan.c


all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


clean:
	rm -f $(TARGET)


install: $(TARGET)
	cp $(TARGET) $(HOME)/
	sudo cp fan_control.service /etc/systemd/system/
	sudo systemctl daemon-reload
	sudo systemctl enable fan_control.service
	sudo systemctl start fan_control.service


uninstall:
	sudo systemctl stop fan_control.service
	sudo systemctl disable fan_control.service
	sudo rm /etc/systemd/system/fan_control.service
	sudo systemctl daemon-reload
	rm -f $(HOME)/$(TARGET)

.PHONY: all clean install uninstall