# compile all
make all
# run server
./server&
# uses port 5500 / 127.0.0.1 host
# run system
./program

# kill server
SYSPROGSERVER=$(pgrep server)
kill $SYSPROGSERVER
unset SYSPROGSERVER