# Heimdallr Terminal Emulator

A terminal,
We are focused on its lightness and speed!
Finally, it can be a permanent terminal for you!
this terminal witten in C and Gtk framework
because HEIMDALLR must be a SUPER lightweight.


# SIZE 


* Fedora : 15KB

* Manjaro/Arch : ~19K

* Ubuntu/Debian : 19K


# screenshots

![screenshots](screenshots/1.png)

![screenshots](screenshots/2.png)

![screenshots](screenshots/3.png)


# installation (Debian)
    $ cd debian
    $ ./preinstallRequirementsDebian.sh
    $ ./install-heimdallr-debian.py
    

# installation (Manjaro/Arch)
    $ cd manjaro-Arch
    $ sudo pacman -Syu strip
    $ ./preinstallRequirementsManjaroArch.sh
    $ ./install-heimdallr-manjaro-Arch.py


# installation (Fedora)
    $ cd fedora
    $ ./preinstallRequirementsFedora.sh
    $ ./install-heimdallr-fedora.py


# update
    $ heimdallr-update

# exec (local)
    $ cd debian OR cd fedora
    $ ./preinstallRequirementsFedora.sh OR ./preinstallRequirementsDebian.sh
    $ make
    $ ./heimdallr

