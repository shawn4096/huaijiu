inherit ROOM;

void create()
{
	set("short", "青石官道");
        set("long",@long
你走在一条青石大道上，人来人往显得非常繁忙，不时地有人骑着马匆匆
而过，大道两旁有一些小货摊，似乎是一处集市。东边通向苏州城。
long);
	set("outdoors", "suzhou");
	set("exits",([
		"east" : __DIR__"qsgdao3",
		"west" : __DIR__"qsgdao5",
	]));
	set("coor/x",70);
  set("coor/y",-210);
   set("coor/z",0);
   setup();
}
