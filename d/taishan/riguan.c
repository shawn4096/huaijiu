// Room: /d/taishan/.c
// Date: pishou 97/6

inherit ROOM;

void create()
{
	set("short", "月观峰");
	set("long", @LONG
这里是位于南天门西面的山岭，怪石攒簇，最高的地方一石
卓立，名为君子峰。往北走便是泰山的西天门。
LONG
	);

	set("exits", ([
		"westup" : __DIR__"yuhuang",
		"eastup" : __DIR__"tanhai",
	]));

        set("objects",([
                __DIR__"npc/wei-shi2" : 3,
        ]));


	set("outdoors", "taishan");
	set("coor/x",180);
  set("coor/y",220);
   set("coor/z",100);
   setup();
}

