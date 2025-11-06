#include "../headers/Daemon.h"

void Daemon::removeFromAutostart() {
    system("systemctl disable wifi-scanner.service");
    system("rm -f /etc/systemd/system/wifi-scanner.service");
    system("systemctl daemon-reload");

    std::cout << "\033[1m\033[32mDaemon has been removed from autostart!\033[0m" << std::endl;
}
