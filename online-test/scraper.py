import re
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
from bs4 import BeautifulSoup
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains  # For sending keystrokes
import numpy as np
import time

##  Chromedriver setup
service = Service(ChromeDriverManager().install())
driver = webdriver.Chrome(service=service)

##  Load page + init waiting
driver.get("https://2048.io")
time.sleep(1)

##  Get all tile containers using div location
tile_loc = driver.find_element(By.CSS_SELECTOR,'body > div > div.game-container > div.tile-container')

##  Parse using bs4
tiles_html = tile_loc.get_attribute('outerHTML')
soup = BeautifulSoup(tiles_html,'html.parser')

##  Get all tiles by class name
tiles = soup.find_all(class_='tile')

##  Simple print board (flattened)
board = [0] * 16
for tile in tiles:
    tile_value = tile.find(class_='tile-inner').text
    match = re.search(r'tile-position-(\d)-(\d)',' '.join(tile['class']))
    if match:
        row = int(match.group(1))-1
        col = int(match.group(2))-1
        board[col*4+row] = tile_value

##  Print board (flattened)
print(board)

##  Send keystroke a (left)
actions = ActionChains(driver)
actions.send_keys("a").perform()

time.sleep(1)
driver.quit()
