from flask import Flask
import sys
import webbrowser
import threading
import subprocess

app = Flask(__name__)

@app.route("/")
def hello():
    return "Hello World!"

def index():
    return subprocess.Popen(["./executables/sfs", "index"], stdout=subprocess.PIPE).communicate()[0]

def search(query):
    split_query = query.split()
    result = subprocess.Popen(["./executables/sfs", "search"] + split_query, stdout=subprocess.PIPE).communicate()[0]
    return result

if __name__ == "__main__":
    threading.Timer(1.25, lambda: webbrowser.open("http://127.0.0.1:5000/")).start()
    app.run()