// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
	set("short", "升仙坊");
	set("long", @LONG
这里是十八盘的中间，从龙门至此的一段称为缓十八，从这里
直上南天门的一段称为紧十八。由此刻攀石而上，后面的人可以看
到前面的人的鞋底，前面的人回头则可见到后面的人的发顶。在这
里一般人每走十来步便要稍一休息。
LONG
	);

	set("exits", ([
		"northup" : __DIR__"nantian",
		"southdown" : __DIR__"longmen",
	]));
set("objects",([
__DIR__"npc/qinbing1" : 2,
__DIR__"npc/yujizi" : 1,
__DIR__"npc/jianchu" :1,
]));
	set("outdoors", "taishan");
	set("coor/x",170);
  set("coor/y",200);
   set("coor/z",90);
   setup();
}

