if [ $# -eq 0 ]; then
  echo "Usage: $0 text"
  exit -1
fi

KEY=29c86f78-e6f0-4ce4-ac8b-bccbca3b4ac6
TEXT=$1

curl "https://tts.voicetech.yandex.net/generate?format=wav&lang=ru-RU&speaker=zahar&emotion=evil&key=$KEY" -G --data-urlencode "text=$TEXT" | tee cache.wav |  cvlc --play-and-exit -  
