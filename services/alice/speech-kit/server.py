#!/bin/python
from flask import Flask, jsonify, request
import subprocess
import os

app = Flask(__name__)

text = ""
greetings = "'/play' and '/replay'\n"

@app.route('/')
def index():
    return greetings

@app.route('/play', methods=['POST'])
def play():
    global text
    text = request.data.decode('utf-8') 
    os.system('./play.sh "' + text + '"')
    return jsonify({'played': True, "text" : text}), 201

@app.route('/replay')
def replay():
    global text
    os.system('./replay.sh')
    return jsonify({'replayed': True, "text" : text}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
