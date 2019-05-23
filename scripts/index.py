import socket
import requests
import string

data = requests.get("https://pastebin.com/raw/1eJr2RLR").content.decode().replace("\n", ' ').replace('\r', ' ').replace('  ', ' ').replace("  ", " ").lower()
for p in string.punctuation:
    data = data.replace(p, '')

data = ' '.join(list(filter(None, data.split())))
print(data)

s = socket.socket()
s.connect(("localhost", 5575))
#s.send(b"SEARCH what is this")
s.send("INDEX beemovie {}\r\n".format(data).encode())
print(s.recv(1024))
s.send(b"SEARCH bee movie\r\n")
print(s.recv(1024))
#s.send(b"exit\r\n")
