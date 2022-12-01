import dotenv
import requests
import os

current_dir = os.path.basename(os.getcwd())

day = int(current_dir)

main_dir = os.path.dirname(os.path.realpath(__file__))
print(main_dir)
env = dotenv.dotenv_values(os.path.join(main_dir, ".env"))
session = env["SESSION"]
year = env["YEAR"]

req = requests.get(
    f"https://adventofcode.com/{year}/day/{day}/input",
    cookies={'session': session})

with open("input", "w") as f:
    f.write(req.content.decode('utf-8'))

