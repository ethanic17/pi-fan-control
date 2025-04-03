# pi-fan-control

Controls a PWM fan connected to a Raspberry Pi 4B. Uses pigpio library and tweaks PWM signal/fan speed accordingly depending on APU temperature. Make sure your fan's PWM output wire is connected to GPIO18 (Pin #12)

You can compile the C file using ```gcc fan.c -o fan_control -lpigpio -lrt -lpthread``` which gives you a fan_control executable. The service daemon (```fan_control.service```) should be placed in ```/etc/systemd/system/fan_control.service```. Once the daemon is started, it calls the executable file which should be in your home directory. 

Installation:
- Install pigpio by running ```sudo apt install pigpio```
- Clone the repository to your Pi
- You can choose to use the already compiled exectuable or compile on your own using ```gcc fan.c -o fan_control -lpigpio -lrt -lpthread```
  - Make sure to delete the downloaded fan_control executable beforehand if you do choose to compile yourself
- Next, place the service file inside of the ```/etc/systemd/system``` directory.
- Then, reload the daemon and start the service
  - ```sudo systemctl daemon-reload```
  - ```sudo systemctl enable fan_control.service```
  - ```sudo systemctl start fan_control.service```


Default settings that may need to be changed:
- If your username isn't `pi`, open the service file and change `pi` to your username
- If your executable is placed in a different directory, make sure to change that in the service file as well
- Currently the fan is set to run at 40%, 50%, 70%, and 100% at 55, 60, 65, and 66+ degreees (C°) respectively. These values can be changed in the C file.
- If your fan's PWM output wire is connected to a different pin, make sure to change that in the C file (```PWM_PIN```)


<img src="https://github.com/user-attachments/assets/42c32ce6-fb34-4e88-aff4-a74f7622b429" width="500" height="500">
<img src="https://github.com/user-attachments/assets/d30685da-6a06-471b-b40b-dc22f2f69979" width="500" height="500">
