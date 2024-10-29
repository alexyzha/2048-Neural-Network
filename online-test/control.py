import subprocess
import time

SERVER = subprocess.Popen(["server/server","server/bot/infile.txt"])
time.sleep(1)
subprocess.run(["python","scraper.py"])
SERVER.terminate()