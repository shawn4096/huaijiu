inherit ROOM;

void create()
{
        set("short", "青石官道");
        set("long",@long
你走在一条青石大道上，人来人往显得非常繁忙，不时地有人骑着马匆匆
而过，大道两旁有一些小货摊，似乎是一处集市。东边通向苏州城。西北通向
寒山寺，南边有条土路。
long);
	set("outdoors", "suzhou");
	set("exits",([
		"east" : __DIR__"qsgdao4",
		"northwest" : __DIR__"hanshansi",
		"south" : __DIR__"tulu1",
	]));
	set("coor/x",60);
  set("coor/y",-210);
   set("coor/z",0);
   setup();
}
