// xiaolu1.c 林间小径
// by shang 97/6

inherit ROOM;

void create()
{
	set("short", "林间小径");
	set("long", @LONG
你走在一条小径上，两旁种满了竹子，修篁森森，绿荫满地，除
了竹叶声和鸟鸣声，听不到别的动静。东西两侧是走廊。
LONG
	);

	set("exits", ([
                "east" : __DIR__"donglang2",
                "west" : __DIR__"xilang1",
                "south" : __DIR__"xiaolu2",
                "north" : __DIR__"sanqingdian",
	]));
        set("objects",([
                "/kungfu/class/wudang/wanqing" : 1,
//       "/u/dubei/npc/weitian" : 1,
//        "/clone/npc/zhangzz" : 1,
        ]));

	set("coor/x",-20);
  set("coor/y",-80);
   set("coor/z",100);
   setup();
}

