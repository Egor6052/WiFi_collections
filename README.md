
**A program for finding and creating a database of Wi-Fi networks and their attributes. Created for educational purposes.**


## How to send file to Raspberry?
```sh
scp '/home/user/Desktop/WiFi_collections.zip' pi@192.168.0.112:~/Programs
```


---
## Daemon Management

##### Reload Daemons
```sh
sudo systemctl daemon-reload
```

##### Restart Daemon
```sh
sudo systemctl restart wifi-scanner.service
```

##### Check Daemon Status
```sh
sudo systemctl status wifi-scanner.service
```

##### Disable Daemon
```sh
sudo systemctl disable wifi-scanner.service
```

##### Enable Daemon
```sh
sudo systemctl enable wifi-scanner.service
```

##### Stop Daemon
```sh
sudo systemctl stop wifi-scanner.service
```
##### Start Daemon
```sh
sudo systemctl start wifi-scanner.service
```

##### Delete Daemon
```sh
sudo rm /etc/systemd/system/wifi-scanner.service
```
