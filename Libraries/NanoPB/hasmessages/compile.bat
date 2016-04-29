
D:\Code\HAS\Arduino\Libraries\NanoPB\protoc.exe -ID:\Code\HAS\Arduino\Libraries\NanoPB\generator -ID:\Code\HAS\Arduino\Libraries\NanoPB\protobuf-2.5.0\src\ -I. -oDiscoverMessage.pb DiscoverMessage.proto
python D:\Code\HAS\Arduino\Libraries\NanoPB\generator\nanopb_generator.py DiscoverMessage.pb

D:\Code\HAS\Arduino\Libraries\NanoPB\protoc.exe -ID:\Code\HAS\Arduino\Libraries\NanoPB\generator -ID:\Code\HAS\Arduino\Libraries\NanoPB\protobuf-2.5.0\src\ -I. -oTemperatureMessage.pb TemperatureMessage.proto
python D:\Code\HAS\Arduino\Libraries\NanoPB\generator\nanopb_generator.py TemperatureMessage.pb


D:\Code\HAS\Arduino\Libraries\NanoPB\protoc.exe -ID:\Code\HAS\Arduino\Libraries\NanoPB\generator -ID:\Code\HAS\Arduino\Libraries\NanoPB\protobuf-2.5.0\src\ -I. -oHeader.pb Header.proto
python D:\Code\HAS\Arduino\Libraries\NanoPB\generator\nanopb_generator.py Header.pb