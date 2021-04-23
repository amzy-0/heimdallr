#!/usr/bin/python
from os import system as syscall
syscall('#sudo pacman -Syyu ; ') # update and upgrade
syscall('sudo pip3 install tkintertable ; ') 
from os import getenv
import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk

syscall('mkdir -p ~/.heimdallr/makefile/ ; cp -rf ../* %s/.heimdallr/' % getenv('HOME'))
syscall('cp -rf ../.* %s/.heimdallr/' % getenv('HOME'))
syscall('cp -rf Makefile %s/.heimdallr/makefile/' % getenv('HOME'))
root = tk.Tk()
progress = ttk.Progressbar(root, length = 100, mode = 'determinate')

def installer_heimdallr():
    import time 
    
    progress['value'] = 20
    root.update_idletasks() 
    time.sleep(0.4) 
    syscall('make')
    syscall('sudo cp heimdallr /usr/bin/')
    syscall('sudo cp heimdallr-update /usr/bin/')
    
    progress['value'] = 50
    root.update_idletasks() 
    time.sleep(0.4)
    syscall('sudo cp -rf ../xdg/heimdallr.desktop /usr/share/applications')
    syscall('cp -rf ../xdg/heimdallr.desktop ~/.local/share/applications')

    progress['value'] = 70
    root.update_idletasks() 
    time.sleep(0.4)
    syscall("sudo cp -rf ../icon/heimdallr.png /usr/share/icons/hicolor/256x256/apps/")
    syscall("sudo cp -rf ../icon/heimdallr.png /usr/share/icons/hicolor/256x256/apps/")
    syscall("sudo cp -rf ../icon/heimdallr.png /usr/share/icons/")

    progress['value'] = 100
    root.update_idletasks() 
    time.sleep(0.4)
    syscall('zenity --info --title Heimdallr --text "Heimdallr installed !"')
    exit(0)

img = ImageTk.PhotoImage(Image.open('../icon/heimdallr.png'))
panel = tk.Label(root, image=img)

# installer btn 
installerBtn = tk.Button(root, text='INSTALL Heimdallr', command=installer_heimdallr)
installerBtn.configure(fg='white', bg='black')

root.configure(bg='black')
root.geometry('400x400')
root.resizable(False, False)
panel.configure(bg='black')
root.iconphoto(False, img)
root.wm_title('Heimdallr installer')
root.title ='Heimdallr installer'
panel.pack(fill='both', expand='yes')
progress.pack(fill='x')
installerBtn.focus()
installerBtn.pack(fill='x')

root.mainloop()
