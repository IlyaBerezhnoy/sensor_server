if [ $# -eq 0 ]; then
  echo "Usage: $0 name text"
  exit -1
fi

KEY=29c86f78-e6f0-4ce4-ac8b-bccbca3b4ac6
NAME=$1
TEXT=$2

curl "https://tts.voicetech.yandex.net/generate?format=wav&lang=ru-RU&speaker=alyss&emotion=good&key=$KEY" -G --data-urlencode "text=$TEXT" > $NAME.wav
