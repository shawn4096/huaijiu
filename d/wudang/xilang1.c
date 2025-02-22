// xilang.c 西厢走廊
// by shang 97/6

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "西厢走廊");
        set("long", @LONG
你走在一条走廊上，南边是一座楼阁，再往西是一间炼丹房, 西北是一小径。
这儿是武当禁地, 非常安静, 有一武当弟子看守着。
LONG
        );

        set("exits", ([
                "southup" : __DIR__"cangjingge",
                "east" : __DIR__"xiaolu1",
                "west" : __DIR__"liandanfang",
                "northwest" : __DIR__"xiaolu7",

        ]));

        set("objects", ([
                "/kungfu/class/wudang/xi" : 1]));

   setup();
} 
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("family");

        if ((!myfam || myfam["family_name"] != "武当派") && dir != "east" &&
                objectp(present("zhang songxi", environment(me))))
           return notify_fail("张松溪喝道：武当重地，外人不得入内。\n");
                
        return ::valid_leave(me, dir);
}
