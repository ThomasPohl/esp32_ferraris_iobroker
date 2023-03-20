#include <ESPAsyncWebServer.h>
#include "reader.h"
class Webserver
{
private:
    AsyncWebServer server = AsyncWebServer(80);
    Reader *reader;
    void initFilesystem();

public:
    Webserver(Reader *reader);
};