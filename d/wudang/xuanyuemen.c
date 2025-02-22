// /d/wudang/xuanyuemen.c 玄岳门
// by ydh and shang

#include <ansi.h>
#include <wanted.h>

inherit ROOM;

void create()
{
        set("short", "玄岳门");
        set("long", @LONG
你的面前就是天下闻名的武当山，它是一座林木繁茂的高山，几座
山峰被云雾笼罩，难见全貌。一条石阶盘延向上，隐约可见几个进香客。
一座古牌石坊(fang)面山而立。武当山又名太和山，为七十二福地之一，
有二十七峰、三十六岩、二十四涧、五台、五井、三潭、三天门、三洞
天和一福地，百里内密树森罗，蔽日参天，景物幽绝。而这玄岳门是武
当派迎接来客的第一站。
LONG
        );
        set("exits", ([
                "east" : __DIR__"wdroad8",
                "west" : __DIR__"yaofang.c",
                "southup" :__DIR__"shijie1",
        ]));

        set("item_desc", ([
                "fang" : RED "武当山\n"NOR,
        ]));

        set("no_clean_up", 0);

        set("coor/x",20);
  set("coor/y",30);
   set("coor/z",0);
   setup();

}

int valid_leave(object me, string dir)
{
	if (dir == "southup" && is_wanted(me))
		return 0;
	return ::valid_leave(me, dir);
}
