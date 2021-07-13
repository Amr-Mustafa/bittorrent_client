#include <iostream>
#include <fstream>
#include <variant>
#include <vector>
#include <map>

using namespace std;

/* The structure of an example .torrent file
d
    8:announce  43:udp://tracker.coppersurfer.tk:6969/announce

    13:announce-list
    l
        l   43:udp://tracker.coppersurfer.tk:6969/announce  e
        l   31:udp://9.rarbg.com:2710/announce              e
        l   26:udp://p4p.arenabg.com:1337                   e
        l   40:udp://tracker.leechers-paradise.org:6969     e
        l   39:udp://tracker.internetwarriors.net:1337      e
        l   42:udp://tracker.opentrackr.org:1337/announce   e
    e

    7:comment           65:Torrentdownloadedfromhttps://yts.am(former:https://yts.ag)
    10:createdby        6:YTS.AG
    13:creationdate     i1536703602e
    4:info
        d
            5:files
            l
                d
                    6:length    i2121134119e
                    4:path      l   62:Sicario.Day.Of.The.Soldado.2018.1080p.WEBRip.x264-[YTS.AM].mp4   e
                e
                d
                    6:length    i58132e
                    4:path      l   14:www.YTS.AM.jpg   e
                e
            e

            4:name          59:SicarioDayOfTheSoldado(2018)[WEBRip][1080p][YTS.AM]
            12:piecelength  i524288e
            6:pieces        80920: ...
        e
e
*/
struct TorrentMetaInfo {
    int creation_date;
    std::string announce;
    std::string comment;
    std::string created_by;
    std::vector<std::string> announce_list;
    std::map<std::string, std::variant<int, std::string>> info;
};

int main() {
    ifstream torrent;
    torrent.open("DEE400967F93C24A5BA1631C392ABA48AA8FC180.torrent", ios::binary);
    for(char c; torrent >> c; )
        cout << c;
    return 0;
}
