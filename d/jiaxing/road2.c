inherit ROOM;

void create()
{
        set("short", "青石官道");
        set("long",@long
你走在一条青石大道上，人来人往非常繁忙，不时有人骑着马匆匆而过。
西北通向苏州城。东南面是嘉兴城。
long);
	set("outdoors", "嘉兴");                        
/*	set("objects",([
		__DIR__"npc/yetu" : 1,
	]));*/
	set("exits",([
        "northwest" : "/d/suzhou/qsgdao2",
		"southeast" : __DIR__"road1",
	]));
	set("coor/x",120);
  set("coor/y",-280);
   set("coor/z",0);
   setup();
}
