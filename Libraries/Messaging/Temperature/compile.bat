
protoc --proto_path=./ -otemperature.pb temperature.proto -I ../
python "../../NanoPB\generator\nanopb_generator.py" temperature.pb