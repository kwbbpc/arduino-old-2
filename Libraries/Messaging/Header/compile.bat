
::REM the -I /NanoPB/generator/proto allows you to import nanopb.proto, which defines sometimes needed options.
protoc --proto_path=./ -oheader.pb header.proto -I ../ -I ../NanoPB/generator/proto
python "../../NanoPB\generator\nanopb_generator.py" header.pb