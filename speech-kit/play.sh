if [ $# -eq 0 ]; then
  echo "Usage: $0 text"
  exit -1
fi

TEXT=$1

curl "https://tts.voicetech.yandex.net/generate?format=wav&lang=ru-RU&speaker=alyss&emotion=good&key=$KEY" -G --data-urlencode "text=$TEXT" | tee cache.wav |  cvlc --play-and-exit -  
