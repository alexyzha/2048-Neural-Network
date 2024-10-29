import re
import socket as sk
import util
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
from bs4 import BeautifulSoup
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

import numpy as np
import time

##  Socket setup (127.0.0.1 == localhost)
SERVER_ADDRESS = '127.0.0.1'
SERVER_PORT = 8080
CLIENT_SOCKET = sk.socket(sk.AF_INET,sk.SOCK_STREAM);
CLIENT_SOCKET.connect((SERVER_ADDRESS,SERVER_PORT))

##  Chromedriver setup
service = Service(ChromeDriverManager().install())
driver = webdriver.Chrome(service=service)
actions = ActionChains(driver)

##  Load page + init waiting
driver.get("https://2048.io")
time.sleep(1)

##  Get all tile containers using div location
tile_loc = driver.find_element(By.CSS_SELECTOR,'body > div > div.game-container > div.tile-container')

playing = True

while playing:
    ##  Parse using bs4
    tiles_html = tile_loc.get_attribute('outerHTML')
    soup = BeautifulSoup(tiles_html,'html.parser')
    ##  Get all tiles by class name
    tiles = soup.find_all(class_='tile')
    ##  Simple print board (flattened)
    board = bytearray(16)
    for tile in tiles:
        tile_value = tile.find(class_='tile-inner').text
        match = re.search(r'tile-position-(\d)-(\d)',' '.join(tile['class']))
        if match:
            row = int(match.group(1))-1
            col = int(match.group(2))-1
            board[col*4+row] = util.log2char(tile_value)
    ##  Send to server
    CLIENT_SOCKET.sendall(board)
    ##  Receive from server
    RESPONSE = CLIENT_SOCKET.recv(1)
    if RESPONSE[0] == 101:
        playing = 0
    ##  Wait for no tweak
    old_html = tile_loc.get_attribute('outerHTML')
    ##  Send key
    actions.send_keys(chr(RESPONSE[0])).perform()
    try:
        WebDriverWait(driver,10).until(lambda d: tile_loc.get_attribute('outerHTML') != old_html)
    except Exception as e:
        print(f"Error: {e}")

##  Close
CLIENT_SOCKET.close()
time.sleep(10)
driver.quit()